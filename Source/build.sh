
 gcc main.c                              \
      -c                                 \
      -fno-stack-protector               \
      -fpic                              \
      -fshort-wchar                      \
      -mno-red-zone                      \
	  -I /usr/include/efi/x86_64         \
      -DEFI_FUNCTION_WRAPPER             \
      -o main.o

 ld main.o                          \
     /usr/lib/crt0-efi-x86_64.o     \
     -nostdlib                      \
     -znocombreloc                  \
     -T /usr/lib/elf_x86_64_efi.lds \
     -shared                        \
     -Bsymbolic                     \
     -L /usr/lib                    \
     -l:libgnuefi.a                 \
     -l:libefi.a                    \
     -o main.so

dd if=/dev/zero of=./uefi.img bs=512 count=93750


gdisk ./uefi.img
# o
# y
# n
# 1
# 2048
# 93716
# ef00
# w
# y

# SUDO
su
losetup --offset 1048576 --sizelimit 46934528 /dev/loop0 /path/to/uefi.img
mkdosfs -F 32 /dev/loop0
mount /dev/loop0 /mnt
cp /path/to/main.efi /mnt/
umount /mnt
losetup -d /dev/loop0

# END SUDU

# RUN
qemu-system-x86_64 -cpu qemu64 -bios OVMF.fd -drive file=uefi.img,if=ide
