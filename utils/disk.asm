disk_load:
	pusha
	push dx
	
	mov ah, 0x02  ;A signal
	mov al, dh		;number of sectors to read	(1-128 dec.)
	mov cl, 0x02 		;sector number  (1-17 dec.)
	mov ch, 0x00		;track/cylinder number  (0-1023 dec., see below)
	mov dh, 0x00		;head number  (0-15 dec.)

	int 0x13
	jc disk_error
	
	pop dx
	cmp al, dh
	jne sectors_error
	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print
	call print_nl
	mov dh, ah		;ah is the error code
	call print_hex
	jmp disk_loop

sectors_error:
	mov bx, SECTORS_ERROR
	call print

disk_loop:
	jmp $

DISK_ERROR:
	db "Disk read error", 0
SECTORS_ERROR:
	db "Incorrect number of sectors read", 0
