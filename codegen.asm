extern printf
extern scanf

section .bss
	d3:	resb	8
	b5b567:	resb	8
	c3bd:	resb	8
	buffer0:	resb	8
	buffer1:	resb	8
	buffer2:	resb	8
	buffer3:	resb	8
	buffer4:	resb	8
	buffer5:	resb	8
	buffer6:	resb	8
	buffer7:	resb	8
	buffer8:	resb	8
	buffer9:	resb	8

section .data
	scanint:	dw "%d", 0
	ft:	db "a=%d", 10, 0

section .text

global main
main:


	push rbp
	mov rax,1
	push rax
	mov [b5b567],rax
	pop rax

	mov rax,0
	push rax
	mov [d3],rax
	pop rax



loop0:
	mov rax,[b5b567]
	push rax
	mov rax,7
	mov rbx,rax
	pop rax
	cmp rax,rbx
	jle true0
false0:
	mov rax,0
	jmp next0
true0:
	mov rax,1
next0:
	cmp rax, 0
	je endloop0
	mov	rsi,c3bd
	mov	rdi,scanint
	call scanf

	mov rax,[d3]
	push rax
	mov rax,[c3bd]
	push rax
	pop rbx
	pop rax
	add	rax,rbx
	push rax
	mov [d3],rax
	pop rax

	mov rax,[b5b567]
	push rax
	mov rax,1
	push rax
	pop rbx
	pop rax
	add	rax,rbx
	push rax
	mov [b5b567],rax
	pop rax

	jmp loop0
endloop0:
	mov	rsi,[d3]
	mov	rdi,scanint
	call printf


	pop rbp
	ret
