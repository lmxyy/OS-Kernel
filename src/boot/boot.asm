[org 0x7c00]
	
	mov ah, 0x0e		;enable the tty mode
	mov al, 'W'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, 'l'
	int 0x10
	mov al, 'c'
	int 0x10
	mov al, 'o'
	int 0x10
	mov al, 'm'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'o'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'Y'
	int 0x10
	mov al, 'Y'
	int 0x10
	mov al, 'O'
	int 0x10
	mov al, 'S'
	int 0x10
	mov al, '!'
	int 0x10
	call print_nl

	mov bp, 0x8000
	mov sp, bp

	mov bx, 0x9000		
	mov dh, 2 		;read
	call disk_load

	jmp $

	%include"../utils/print.asm"
	%include"../utils/print_hex.asm"
	%include"../utils/disk.asm"
	

	;; 0xaa55 is the magic number.
	times 510-($-$$) db 0
	dw 0xaa55

	times 256 dw 0xdada ; sector 2 = 512 bytes
	times 256 dw 0xface ; sector 3 = 512 bytes
