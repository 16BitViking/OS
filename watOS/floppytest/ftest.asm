section .text
org 0x7c00

mov ax, ds
mov es, ax ;es = ds

mov ah, 13h ;video - write string
mov al, 0 ;write mode
mov bh, 0 ;page number
mov bl, 0 ;attribute
mov dx, 0 ;dh = row, dx = column
mov cx, length ;length of string
mov bp, hello ;string located at es:bp
int 10h

hlt

section .data
hello: db 'Hello, world!'
length: equ $-hello
