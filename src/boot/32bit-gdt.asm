gdt_start:
	dq 0

	;; refer to page 34 of os-dev.pdf 
gdt_code:
	dw 0xffff		;segment limit(0-15)
	dw 0x0			;base address(0-15)
	db 0x0			;base address(16-23)
	db 10011010b		;flags(8 bits)
	db 11001111b		;flags(4 bits)+segment lim(16-19)
	db 0x0			;base address(24-31)

gdt_data:	
	dw 0xffff		;segment limit(0-15)
	dw 0x0			;base address(0-15)
	db 0x0			;base address(16-23)
	db 10010010b		;flags(8 bits)
	db 11001111b		;flags(4 bits)+segment lim(16-19)
	db 0x0			;base address(24-31)
	
gdt_end:

gdt_descriptor:
	dw gdt_end-gdt_start-1
	dd gdt_start

	CODE_SEG equ gdt_code-gdt_start
	DATA_SEG equ gdt_data-gdt_start
