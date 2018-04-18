
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
 objcopy -j .text                \
          -j .sdata               \
          -j .data                \
          -j .dynamic             \
          -j .dynsym              \
          -j .rel                 \
          -j .rela                \
          -j .reloc               \
          --target=efi-app-x86_64 \
          main.so                 \
          main.efi

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
sudo losetup --offset 1048576 --sizelimit 46934528 /dev/loop0 ./uefi.img
sudo mkdosfs -F 32 /dev/loop0
sudo mount /dev/loop0 /mnt
sudo cp ./main.efi /mnt/
sudo umount /mnt
sudo losetup -d /dev/loop0

# END SUDU

# RUN
qemu-system-x86_64 -cpu qemu64 -bios OVMF.fd -drive file=uefi.img,if=ide -vnc :1
