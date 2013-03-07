section .text
org 0x7c3e

call clearscreen
call printString

loopforever:
	jmp loopforever

;--------------------------------
;clears screen to black
;--------------------------------

clearscreen:
	call loadvideo

	mov cx, 2000 ;loop 2000 times
	cld ;increment string register
	mov ah, 00010000b ;attribute byte
	mov al, ' '
	repnz stosw 
	ret

;--------------------------------
;loads start of video memory into es:di
;--------------------------------

loadvideo:
	mov ax, 0B800h
	mov es, ax ;es = start of video memory
	xor di, di ;di = offset 0
	ret

;--------------------------------
;prints hello string to the screen
;--------------------------------

printString:
	mov ax, cs
	mov es, ax

	mov bp, hello
	mov ah, 13h
	mov al, 01h ;update cursor, all attribute bl	
	mov bh, 0   ;display page 0
	mov bl, 00010111b ;attribute
	mov cx, length   ;string length
	mov dh, 12
	mov dl, 10
	push bp
	int 10h
	pop ax

	ret

section .data
hello: db "ur a faget"
length: equ $-hello
