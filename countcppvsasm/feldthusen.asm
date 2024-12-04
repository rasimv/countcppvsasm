.code

fhcount proc
;	push rax
	push rbx
	push rcx
	push rdx
	push rdi
	push rsi
	push rbp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	pushfq

	mov rdi, rcx ; rdi = buffer
	mov rsi, rdx ;
	sub rsi, rcx ; rsi = size

; ---------------------------------------------------------------------------

	; xor %%rcx, %%rcx;           // Clear count (rcx)
	xor rcx, rcx

	xor rdx, rdx ; <<< Added

	; mov %1, %%al;               // Load target_byte into AL
	mov rax, r8

	; "1:"                        // Loop label
main_loop:

	; cmp %%rcx, %2;              // Compare index (rcx) with size
	cmp rcx, rsi

	; jge 2f;                     // If index >= size, jump to end
	jge the_end

	; movb (%3, %%rcx, 1), %%bl;  // Load byte from buffer into BL
	mov bl, [rdi + rcx]

	inc rcx ; <<< Moved from below

	; cmp %%bl, %%al;             // Compare byte with target_byte
	cmp bl, al

	; jne 1b;                     // If not equal, continue looping
	jne main_loop

	; inc %%rdx;                  // Increment count (rdx)
	inc rdx

	; inc %%rcx;                  // Increment index
	; inc rcx ; <<< Moved above

	; jmp 1b;                     // Continue loop
	jmp main_loop

	; "2:"                        // End label
the_end:

; ---------------------------------------------------------------------------

	mov rax, rdx

	popfq
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbp
	pop rsi
	pop rdi
	pop rdx
	pop rcx
	pop rbx
;	pop rax

	ret

fhcount endp

end
