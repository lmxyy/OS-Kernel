	%ifndef KERNEL_ENTRY_ASM
	%define KERNEL_ENTRY_ASM
	
[bits 32]
[extern main]
	call main
	jmp $

	%endif
