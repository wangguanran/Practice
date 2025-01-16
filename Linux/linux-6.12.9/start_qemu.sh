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
echo -e "\e[32mUsing serial output: $SERIAL\e[0m"
echo -e "\e[32mINITRAMFS_DIR: $INITRAMFS_DIR\e[0m"

# 拷贝驱动ko
echo -e "\e[32mCopying driver modules...\e[0m"
rm -rf $INITRAMFS_DIR/lib/modules/kernel/
mkdir -p $INITRAMFS_DIR/lib/modules/kernel/
# find ./drivers -name '*.ko' -exec cp {} $INITRAMFS_DIR/lib/modules/kernel/ \;

# 打包initramfs
echo -e "\e[32mPacking initramfs...\e[0m"
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
    qemu-system-aarch64 \
        -machine virt \
        -cpu cortex-a57 \
        -kernel arch/arm64/boot/Image \
        -initrd initramfs.cpio \
        -append "console=ttyAMA0" \
        -serial $SERIAL \
        -nographic \
        $([ "$DUMP_DTB" == true ] && echo "-machine dumpdtb=default-$ARCH.dtb") \

        # $([ "$DUMP_DTB" == false ] && echo "-dtb default-$ARCH.dtb")

    if [ "$DUMP_DTB" == true ]; then
        echo -e "\e[32mDumping dtb file...\e[0m"
        DTB_FILE="default-$ARCH.dtb"
        DTS_FILE="default-$ARCH.dts"
        dtc -I dtb -O dts -o "$DTS_FILE" "$DTB_FILE"
        echo -e "\e[32mDTB file dumped and converted to DTS.\e[0m"
    fi
else
    echo "Unsupported architecture: $ARCH"
    exit 1
fi

echo -e "\e[32mQEMU execution finished.\e[0m"
