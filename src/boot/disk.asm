	;; for more details, see http://stanislavs.org/helppc/int_13-2.html
disk_load:
	pusha
	push dx
	
	mov ah, 0x02  ;A signal
	mov al, dh		;number of sectors to read	(1-128 dec.)
	mov cl, 0x02 		;sector number  (1-17 dec.)
	mov ch, 0x00		;track/cylinder number  (0-1023 dec., see below)
	mov dh, 0x00		;head number  (0-15 dec.)
	;; dl <- drive number (0=A:, 1=2nd floppy, 80h=drive 0, 81h=drive 1), was set by bios
	;; ES:BX = pointer to buffer
	
	int 0x13
	jc disk_error
	
	pop dx
	cmp al, dh
	jne sectors_error

	mov bx, LOAD_SUCCESS
	call print
	call print_nl
	
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
	db "Disk read error.",0
SECTORS_ERROR:
	db "Incorrect number of sectors read.",0
LOAD_SUCCESS:
	db "Load disk successfully!",0
