# 拷贝驱动ko
mkdir -p initramfs/lib/modules/kernel/
find ./drivers -name '*demo*.ko' -exec cp {} initramfs/lib/modules/kernel/ \;
# 打包initramfs
cd initramfs
find . | cpio -H newc -o > ../initramfs.cpio
cd -
# 启动内核
qemu-system-x86_64 \
	-kernel arch/x86/boot/bzImage \
	-initrd initramfs.cpio
