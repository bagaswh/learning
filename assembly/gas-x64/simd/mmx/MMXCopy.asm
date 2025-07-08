.intel_syntax noprefix
.text

.global MMXCopy

/* void MMXCopy(char *rdi, char *rsi, int byte_count) */
/* ================================================== */
/* Copies byte_count (rdx) bytes of data from the second array (source, passed in *rsi) */
/* to the first (destination, passed in *rdi). */
MMXCopy:
    cmp     rdx, 0              /* Check that there's at least 1 byte in the array */
    jle     MMXCopy_Finished

    xor     r9, r9     /* Zero the offset pointer */
    mov     rbx, rdx    

    shr     rdx, 3     /* Divide the byte count by 8, we're copying 8 at once */
                       /* A lil question. Why not decrement by 8? */
                       /* 1. Bitwise shift right is faster than division. */
                       /* 2. The purpose of this is to know how many 8-byte chunk we can copy. */

    cmp     rdx, 0     /* Make sure we've at least 8 bytes to copy */
    je      MMXCopy_HasNothingLeftToDo
    
MMXCopy_Loop:
    movq    mm0, qword ptr [rsi+r9] /* Copy 8 bytes from source (*rsi) into MM0 */
    movq    qword ptr [rdi+r9], mm0 /* Copy 8 bytes from MM0 into the destination (*rdi) */
    add     r9, 8   /* Moev offset pointer to the next 8 bytes */
    dec     rdx     /* Decrement the counter */
    jnz     MMXCopy_Loop

/* We need to figure out how many bytes MMX actually copied. */
/* To do this we use integer arithmetic and divide the total byte count by 8 */
/* then multiply it again. */
/* This works because in integer arithmetic any digits after the decimal  */
/* place are truncated and lost (ie. it always rounds down). */
/* For example 100 / 8 = 12, the 0.5 is lost. Then when we multiply */
/* this by 8 again we get 96. So we'd know if the byte_count was 100 */
/* that MMX has done 96 bytes so far. */
MMXCopy_HasNothingLeftToDo:
    mov     rdx, rbx  /* Put the original byte count back into rdx */
    shr     rdx, 3    /* Divide by 8 with SHR because it's simpler and faster than IDIV */
    shl     rdx, 3    /* Multiply by 8 with SHL because it's simpler and faster than IMUL */
    sub     rbx, rdx  /* Sub this from the original byte_count that we saved in rbx and we've */
                      /* got the number of bytes left to do. rbx = byte-count % 8. */
    cmp     rbx, 0
    jz      MMXCopy_Finished

/* This loop copies the remaining bytes 1 at a time */
MMXCopy_ResidualLoop:
    mov     r8b,                byte ptr [rsi+r9]
    mov     byte ptr [rdi+r9],  r8b
    inc     r9
    dec     rbx                     /* dec affects ZF (zero flag). jnz checks the ZF. */
    jnz     MMXCopy_ResidualLoop     



MMXCopy_Finished:
    emms
    ret
