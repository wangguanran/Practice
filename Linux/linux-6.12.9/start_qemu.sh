# 解析命令行参数
ARCH="x86_64"
SERIAL="mon:stdio"
DUMP_DTB=false
while [[ "$#" -gt 0 ]]; do
    case $1 in
    --arch)
        ARCH="$2"
        shift
        ;;
    --serial)
        if [ "$2" == "file" ]; then
            SERIAL="file:kernel.log"
        elif [ "$2" == "console" ]; then
            SERIAL="mon:stdio"
        else
            echo "Unsupported serial option: $2"
            exit 1
        fi
        shift
        ;;
    --dump)
        DUMP_DTB=true
        ;;
    --help)
        echo "Usage: $0 [--arch ARCH] [--serial SERIAL] [--dump]"
        echo "Options:"
        echo "  --arch ARCH       Set the architecture (default: x86_64)"
        echo "  --serial SERIAL   Set the serial output (file or console, default: console)"
        echo "  --dump            Dump the dtb file to the root directory and convert it to dts"
        exit 0
        ;;
    *)
        echo "Unknown parameter passed: $1"
        exit 1
        ;;
    esac
    shift
done

INITRAMFS_DIR="initramfs.$ARCH"

echo -e "\e[32mUsing architecture: $ARCH\e[0m"
echo -e "Using serial output: $SERIAL"
echo -e "INITRAMFS_DIR: $INITRAMFS_DIR"

# 拷贝驱动ko
echo -e "Copying driver modules..."
rm -rf $INITRAMFS_DIR/lib/modules/kernel/
mkdir -p $INITRAMFS_DIR/lib/modules/kernel/
# find . -name 'leds-demo.ko' -exec cp {} $INITRAMFS_DIR/lib/modules/kernel/ \;
# find . -name 'leds-gpio.ko' -exec cp {} $INITRAMFS_DIR/lib/modules/kernel/ \;

# 打包initramfs
echo -e "Packing initramfs..."
cd $INITRAMFS_DIR
find . -name '.gitkeep' -prune -o -print | cpio -H newc -o >../initramfs.cpio
cd -

# 启动内核
echo -e "\e[32mStarting kernel with QEMU...\e[0m"
if [ "$ARCH" == "x86_64" ]; then
    qemu-system-x86_64 \
        -kernel arch/x86/boot/bzImage \
        -initrd initramfs.cpio \
        -append "console=ttyS0,921600" \
        -serial $SERIAL \
        -nographic
elif [ "$ARCH" == "arm64" ]; then
    DTB_FILE="arch/arm64/boot/dts/qemu-arm64.dtb"
    DTS_FILE="arch/arm64/boot/dts/qemu-arm64.dts"

    # 编译设备树
    dtc -I dts -O dtb -o "$DTB_FILE" "$DTS_FILE"

    qemu-system-aarch64 \
        -kernel arch/arm64/boot/Image \
        -initrd initramfs.cpio \
        -append "console=ttyAMA0" \
        -serial $SERIAL \
        -nographic \
        -machine virt$([ "$DUMP_DTB" == "true" ] && echo ",dumpdtb=$DTB_FILE") \
        -cpu cortex-a53 \
        -dtb $DTB_FILE

    if [ "$DUMP_DTB" == true ]; then
        echo -e "DTB file dumped and converted to DTS."
        dtc -I dtb -O dts -o "$DTS_FILE" "$DTB_FILE"
    fi
else
    echo "Unsupported architecture: $ARCH"
    exit 1
fi

echo -e "\e[32mQEMU execution finished.\e[0m"
