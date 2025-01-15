# 拷贝驱动ko
mkdir -p initramfs/lib/modules/kernel/
find ./drivers -name '*.ko' -exec cp {} initramfs/lib/modules/kernel/ \;
# 打包initramfs
cd initramfs
find . | cpio -H newc -o > ../initramfs.cpio
cd -
# 启动内核 输出日志到控制台
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd initramfs.cpio \
    -append "console=ttyS0,921600" \
    -serial mon:stdio \
    -nographic
# 输出日志到文件中
# qemu-system-x86_64 \
#		-kernel arch/x86/boot/bzImage \
#		-initrd /path/to/initramfs.cpio \
#		-append "console=ttyS0,921600" \
#		-serial file:kernel.log
