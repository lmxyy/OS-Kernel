[org0x7c00]
	mov bp, 0x9000
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print

	call switch_to_pm
	jmp $

	%include "boot_sect_print"
	$include "32bit-gdt.asm"
	$include "32bit-print.asm"
	$include "32bit-switch.asm"

[bit3 32]
BIGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	jmp $

	MSG_REAL_MODE db "Start in 16-bit real mode", 0
	MSG_PROT_MODE db "Loaded 32-bit protected mode", 0

	times 510-($-$$) db 0
	dw 0xaa55
