	.file	"memcpy.c"
	.intel_syntax noprefix
# GNU C17 (Ubuntu 14.2.0-19ubuntu2) version 14.2.0 (x86_64-linux-gnu)
#	compiled by GNU C version 14.2.0, GMP version 6.3.0, MPFR version 4.2.2, MPC version 1.3.1, isl version isl-0.27-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -masm=intel -mtune=generic -march=x86-64 -O0 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.section	.rodata
.LC0:
	.string	"usage: ./prog <bigfile path>"
	.align 8
.LC1:
	.string	"------- zero values of a -----------"
.LC2:
	.string	"%d - %d\n"
.LC3:
	.string	"r"
.LC4:
	.string	"failed to open bigfile: %s"
.LC5:
	.string	"fread() failed: %zu\n"
	.align 8
.LC6:
	.string	"------- a after fread -----------"
	.align 8
.LC7:
	.string	"------- b after fread -----------"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64	
	push	rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp	#,
	.cfi_def_cfa_register 6
	sub	rsp, 48	#,
	mov	DWORD PTR -36[rbp], edi	# argc, argc
	mov	QWORD PTR -48[rbp], rsi	# argv, argv
# musl_vs_glibc/memcpy.c:13:     if (argc < 2) {
	cmp	DWORD PTR -36[rbp], 1	# argc,
	jg	.L2	#,
# musl_vs_glibc/memcpy.c:14:         fprintf(stderr, "usage: ./prog <bigfile path>");
	mov	rax, QWORD PTR stderr[rip]	# stderr.0_1, stderr
	mov	rcx, rax	#, stderr.0_1
	mov	edx, 28	#,
	mov	esi, 1	#,
	lea	rax, .LC0[rip]	# tmp123,
	mov	rdi, rax	#, tmp123
	call	fwrite@PLT	#
# musl_vs_glibc/memcpy.c:15:         return 1;
	mov	eax, 1	# _24,
	jmp	.L3	#
.L2:
# musl_vs_glibc/memcpy.c:18:     char *a = malloc(SIZE), *b = malloc(SIZE);
	mov	edi, 104857600	#,
	call	malloc@PLT	#
	mov	QWORD PTR -32[rbp], rax	# a, tmp124
# musl_vs_glibc/memcpy.c:18:     char *a = malloc(SIZE), *b = malloc(SIZE);
	mov	edi, 104857600	#,
	call	malloc@PLT	#
	mov	QWORD PTR -24[rbp], rax	# b, tmp125
# musl_vs_glibc/memcpy.c:19:     memset(a, 0, SIZE);
	mov	rax, QWORD PTR -32[rbp]	# tmp126, a
	mov	edx, 104857600	#,
	mov	esi, 0	#,
	mov	rdi, rax	#, tmp126
	call	memset@PLT	#
# musl_vs_glibc/memcpy.c:20:     memset(b, 0, SIZE);
	mov	rax, QWORD PTR -24[rbp]	# tmp127, b
	mov	edx, 104857600	#,
	mov	esi, 0	#,
	mov	rdi, rax	#, tmp127
	call	memset@PLT	#
# musl_vs_glibc/memcpy.c:22:     printf("------- zero values of a -----------");
	lea	rax, .LC1[rip]	# tmp128,
	mov	rdi, rax	#, tmp128
	mov	eax, 0	#,
	call	printf@PLT	#
# musl_vs_glibc/memcpy.c:23:     printf("%d - %d\n", a[0], a[SIZE-1]);
	mov	rax, QWORD PTR -32[rbp]	# tmp129, a
	add	rax, 104857599	# _2,
	movzx	eax, BYTE PTR [rax]	# _3, *_2
# musl_vs_glibc/memcpy.c:23:     printf("%d - %d\n", a[0], a[SIZE-1]);
	movsx	edx, al	# _4, _3
# musl_vs_glibc/memcpy.c:23:     printf("%d - %d\n", a[0], a[SIZE-1]);
	mov	rax, QWORD PTR -32[rbp]	# tmp130, a
	movzx	eax, BYTE PTR [rax]	# _5, *a_30
# musl_vs_glibc/memcpy.c:23:     printf("%d - %d\n", a[0], a[SIZE-1]);
	movsx	eax, al	# _6, _5
	mov	esi, eax	#, _6
	lea	rax, .LC2[rip]	# tmp131,
	mov	rdi, rax	#, tmp131
	mov	eax, 0	#,
	call	printf@PLT	#
# musl_vs_glibc/memcpy.c:25:     const FILE *bigfile = fopen(argv[1], "r");
	mov	rax, QWORD PTR -48[rbp]	# tmp132, argv
	add	rax, 8	# _7,
# musl_vs_glibc/memcpy.c:25:     const FILE *bigfile = fopen(argv[1], "r");
	mov	rax, QWORD PTR [rax]	# _8, *_7
	lea	rdx, .LC3[rip]	# tmp133,
	mov	rsi, rdx	#, tmp133
	mov	rdi, rax	#, _8
	call	fopen@PLT	#
	mov	QWORD PTR -16[rbp], rax	# bigfile, tmp134
# musl_vs_glibc/memcpy.c:26:     if (bigfile == NULL) {
	cmp	QWORD PTR -16[rbp], 0	# bigfile,
	jne	.L4	#,
# musl_vs_glibc/memcpy.c:27:         fprintf(stderr, "failed to open bigfile: %s", strerror(errno));
	call	__errno_location@PLT	#
# musl_vs_glibc/memcpy.c:27:         fprintf(stderr, "failed to open bigfile: %s", strerror(errno));
	mov	eax, DWORD PTR [rax]	# _10, *_9
	mov	edi, eax	#, _10
	call	strerror@PLT	#
	mov	rdx, rax	# _11,
# musl_vs_glibc/memcpy.c:27:         fprintf(stderr, "failed to open bigfile: %s", strerror(errno));
	mov	rax, QWORD PTR stderr[rip]	# stderr.1_12, stderr
	lea	rcx, .LC4[rip]	# tmp135,
	mov	rsi, rcx	#, tmp135
	mov	rdi, rax	#, stderr.1_12
	mov	eax, 0	#,
	call	fprintf@PLT	#
# musl_vs_glibc/memcpy.c:28:         return 1;
	mov	eax, 1	# _24,
	jmp	.L3	#
.L4:
# musl_vs_glibc/memcpy.c:31:     size_t n = fread(a, 1, SIZE, bigfile);
	mov	rdx, QWORD PTR -16[rbp]	# tmp136, bigfile
	mov	rax, QWORD PTR -32[rbp]	# tmp137, a
	mov	rcx, rdx	#, tmp136
	mov	edx, 104857600	#,
	mov	esi, 1	#,
	mov	rdi, rax	#, tmp137
	call	fread@PLT	#
	mov	QWORD PTR -8[rbp], rax	# n, tmp138
# musl_vs_glibc/memcpy.c:32:     if (n != SIZE) {
	cmp	QWORD PTR -8[rbp], 104857600	# n,
	je	.L5	#,
# musl_vs_glibc/memcpy.c:33:         fprintf(stderr, "fread() failed: %zu\n", n);
	mov	rax, QWORD PTR stderr[rip]	# stderr.2_13, stderr
	mov	rdx, QWORD PTR -8[rbp]	# tmp139, n
	lea	rcx, .LC5[rip]	# tmp140,
	mov	rsi, rcx	#, tmp140
	mov	rdi, rax	#, stderr.2_13
	mov	eax, 0	#,
	call	fprintf@PLT	#
.L5:
# musl_vs_glibc/memcpy.c:36:     printf("------- a after fread -----------");
	lea	rax, .LC6[rip]	# tmp141,
	mov	rdi, rax	#, tmp141
	mov	eax, 0	#,
	call	printf@PLT	#
# musl_vs_glibc/memcpy.c:37:     printf("%d - %d\n", a[0], a[SIZE-1]);
	mov	rax, QWORD PTR -32[rbp]	# tmp142, a
	add	rax, 104857599	# _14,
	movzx	eax, BYTE PTR [rax]	# _15, *_14
# musl_vs_glibc/memcpy.c:37:     printf("%d - %d\n", a[0], a[SIZE-1]);
	movsx	edx, al	# _16, _15
# musl_vs_glibc/memcpy.c:37:     printf("%d - %d\n", a[0], a[SIZE-1]);
	mov	rax, QWORD PTR -32[rbp]	# tmp143, a
	movzx	eax, BYTE PTR [rax]	# _17, *a_30
# musl_vs_glibc/memcpy.c:37:     printf("%d - %d\n", a[0], a[SIZE-1]);
	movsx	eax, al	# _18, _17
	mov	esi, eax	#, _18
	lea	rax, .LC2[rip]	# tmp144,
	mov	rdi, rax	#, tmp144
	mov	eax, 0	#,
	call	printf@PLT	#
# musl_vs_glibc/memcpy.c:39:     memcpy(b, a, SIZE);
	mov	rcx, QWORD PTR -32[rbp]	# tmp145, a
	mov	rax, QWORD PTR -24[rbp]	# tmp146, b
	mov	edx, 104857600	#,
	mov	rsi, rcx	#, tmp145
	mov	rdi, rax	#, tmp146
	call	memcpy@PLT	#
# musl_vs_glibc/memcpy.c:41:     printf("------- b after fread -----------");
	lea	rax, .LC7[rip]	# tmp147,
	mov	rdi, rax	#, tmp147
	mov	eax, 0	#,
	call	printf@PLT	#
# musl_vs_glibc/memcpy.c:42:     printf("%d - %d\n", b[0], b[SIZE-1]);
	mov	rax, QWORD PTR -24[rbp]	# tmp148, b
	add	rax, 104857599	# _19,
	movzx	eax, BYTE PTR [rax]	# _20, *_19
# musl_vs_glibc/memcpy.c:42:     printf("%d - %d\n", b[0], b[SIZE-1]);
	movsx	edx, al	# _21, _20
# musl_vs_glibc/memcpy.c:42:     printf("%d - %d\n", b[0], b[SIZE-1]);
	mov	rax, QWORD PTR -24[rbp]	# tmp149, b
	movzx	eax, BYTE PTR [rax]	# _22, *b_32
# musl_vs_glibc/memcpy.c:42:     printf("%d - %d\n", b[0], b[SIZE-1]);
	movsx	eax, al	# _23, _22
	mov	esi, eax	#, _23
	lea	rax, .LC2[rip]	# tmp150,
	mov	rdi, rax	#, tmp150
	mov	eax, 0	#,
	call	printf@PLT	#
	mov	eax, 0	# _24,
.L3:
# musl_vs_glibc/memcpy.c:43: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 14.2.0-19ubuntu2) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
