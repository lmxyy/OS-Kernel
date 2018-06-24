	%ifndef BOOTSECT_ASM
	%define BOOTSECT_ASM

[org 0x7c00]
	KERNEL_OFFSET equ 0x1000

	mov [BOOT_DRIVE], dl
	
	;; set the stack
	mov bp, 0x9000
	mov sp, bp

	;; print the welcome info
	mov bx, MSG_WELCOME
	call print
	call print_nl
	mov bx, MSG_REAL_MODE
	call print
	call print_nl

	call load_kernel
	;; to protect mode
	call switch_to_pm

	%include "boot/print.asm"
	%include "boot/print_hex.asm"
	%include "boot/disk.asm"
	%include "boot/gdt.asm"
	%include "boot/32bit_print.asm"
	%include "boot/switch_pm.asm"
	
[bits 16]
load_kernel:	
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_nl

	mov bx, KERNEL_OFFSET
	mov dh, 2
	mov dl, [BOOT_DRIVE]

	call disk_load
	ret


[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET	;give kernel the control
	jmp $

	;; reseved dat
	BOOT_DRIVE db 0
	MSG_WELCOME db "Welcome to YYOS!",0
	MSG_REAL_MODE db "Start in 16-bit real mode.",0
	MSG_PROT_MODE db "Land in 32-bit protected mode.",0
	MSG_LOAD_KERNEL db "Load the kernel into memory.",0
	
	;; 0xaa55 is the magic number.
	times 510-($-$$) db 0
	dw 0xaa55

	%endif
