
intrin1:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	push   0x2f8a(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 8b 2f 00 00 	bnd jmp *0x2f8b(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 8d 2f 00 00 	bnd jmp *0x2f8d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <clock@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 45 2f 00 00 	bnd jmp *0x2f45(%rip)        # 3fc0 <clock@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001080 <__stack_chk_fail@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 3d 2f 00 00 	bnd jmp *0x2f3d(%rip)        # 3fc8 <__stack_chk_fail@GLIBC_2.4>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001090 <__printf_chk@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 35 2f 00 00 	bnd jmp *0x2f35(%rip)        # 3fd0 <__printf_chk@GLIBC_2.3.4>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <main>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	4c 8d 54 24 08       	lea    0x8(%rsp),%r10
    10a9:	48 83 e4 e0          	and    $0xffffffffffffffe0,%rsp
    10ad:	41 ff 72 f8          	push   -0x8(%r10)
    10b1:	55                   	push   %rbp
    10b2:	48 89 e5             	mov    %rsp,%rbp
    10b5:	41 54                	push   %r12
    10b7:	41 52                	push   %r10
    10b9:	53                   	push   %rbx
    10ba:	48 83 ec 38          	sub    $0x38,%rsp
    10be:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    10c5:	00 00 
    10c7:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    10cb:	31 c0                	xor    %eax,%eax
    10cd:	48 8d 84 24 00 00 c3 	lea    -0x3d0000(%rsp),%rax
    10d4:	ff 
    10d5:	48 39 c4             	cmp    %rax,%rsp
    10d8:	74 15                	je     10ef <main+0x4f>
    10da:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    10e1:	48 83 8c 24 f8 0f 00 	orq    $0x0,0xff8(%rsp)
    10e8:	00 00 
    10ea:	48 39 c4             	cmp    %rax,%rsp
    10ed:	75 eb                	jne    10da <main+0x3a>
    10ef:	48 81 ec 00 09 00 00 	sub    $0x900,%rsp
    10f6:	48 83 8c 24 f8 08 00 	orq    $0x0,0x8f8(%rsp)
    10fd:	00 00 
    10ff:	e8 6c ff ff ff       	call   1070 <clock@plt>
    1104:	49 89 e4             	mov    %rsp,%r12
    1107:	c5 f9 ef c0          	vpxor  %xmm0,%xmm0,%xmm0
    110b:	48 89 c3             	mov    %rax,%rbx
    110e:	4c 89 e2             	mov    %r12,%rdx
    1111:	49 8d 8c 24 00 09 3d 	lea    0x3d0900(%r12),%rcx
    1118:	00 
    1119:	c5 fe 6f 0a          	vmovdqu (%rdx),%ymm1
    111d:	b8 a0 86 01 00       	mov    $0x186a0,%eax
    1122:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1128:	c5 fd fe c1          	vpaddd %ymm1,%ymm0,%ymm0
    112c:	83 e8 01             	sub    $0x1,%eax
    112f:	75 f7                	jne    1128 <main+0x88>
    1131:	48 83 c2 20          	add    $0x20,%rdx
    1135:	48 39 d1             	cmp    %rdx,%rcx
    1138:	75 df                	jne    1119 <main+0x79>
    113a:	c5 f9 6f c8          	vmovdqa %xmm0,%xmm1
    113e:	c4 e3 7d 39 c0 01    	vextracti128 $0x1,%ymm0,%xmm0
    1144:	c5 f1 fe c8          	vpaddd %xmm0,%xmm1,%xmm1
    1148:	c5 f9 73 d9 08       	vpsrldq $0x8,%xmm1,%xmm0
    114d:	c5 f1 fe c8          	vpaddd %xmm0,%xmm1,%xmm1
    1151:	c5 f9 7f 4d b0       	vmovdqa %xmm1,-0x50(%rbp)
    1156:	c5 f8 77             	vzeroupper 
    1159:	e8 12 ff ff ff       	call   1070 <clock@plt>
    115e:	c5 f8 57 c0          	vxorps %xmm0,%xmm0,%xmm0
    1162:	bf 01 00 00 00       	mov    $0x1,%edi
    1167:	48 8d 35 96 0e 00 00 	lea    0xe96(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    116e:	48 29 d8             	sub    %rbx,%rax
    1171:	c4 e1 fb 2a c0       	vcvtsi2sd %rax,%xmm0,%xmm0
    1176:	b8 01 00 00 00       	mov    $0x1,%eax
    117b:	c5 fb 5e 05 a5 0e 00 	vdivsd 0xea5(%rip),%xmm0,%xmm0        # 2028 <_IO_stdin_used+0x28>
    1182:	00 
    1183:	e8 08 ff ff ff       	call   1090 <__printf_chk@plt>
    1188:	c5 f9 6f 4d b0       	vmovdqa -0x50(%rbp),%xmm1
    118d:	31 c0                	xor    %eax,%eax
    118f:	48 8d 35 82 0e 00 00 	lea    0xe82(%rip),%rsi        # 2018 <_IO_stdin_used+0x18>
    1196:	bf 01 00 00 00       	mov    $0x1,%edi
    119b:	c5 f9 73 d9 04       	vpsrldq $0x4,%xmm1,%xmm0
    11a0:	c5 f1 fe c8          	vpaddd %xmm0,%xmm1,%xmm1
    11a4:	c5 f9 7e ca          	vmovd  %xmm1,%edx
    11a8:	e8 e3 fe ff ff       	call   1090 <__printf_chk@plt>
    11ad:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    11b1:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    11b8:	00 00 
    11ba:	75 11                	jne    11cd <main+0x12d>
    11bc:	48 8d 65 e8          	lea    -0x18(%rbp),%rsp
    11c0:	31 c0                	xor    %eax,%eax
    11c2:	5b                   	pop    %rbx
    11c3:	41 5a                	pop    %r10
    11c5:	41 5c                	pop    %r12
    11c7:	5d                   	pop    %rbp
    11c8:	49 8d 62 f8          	lea    -0x8(%r10),%rsp
    11cc:	c3                   	ret    
    11cd:	e8 ae fe ff ff       	call   1080 <__stack_chk_fail@plt>
    11d2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    11d9:	00 00 00 
    11dc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000000011e0 <_start>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	31 ed                	xor    %ebp,%ebp
    11e6:	49 89 d1             	mov    %rdx,%r9
    11e9:	5e                   	pop    %rsi
    11ea:	48 89 e2             	mov    %rsp,%rdx
    11ed:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    11f1:	50                   	push   %rax
    11f2:	54                   	push   %rsp
    11f3:	45 31 c0             	xor    %r8d,%r8d
    11f6:	31 c9                	xor    %ecx,%ecx
    11f8:	48 8d 3d a1 fe ff ff 	lea    -0x15f(%rip),%rdi        # 10a0 <main>
    11ff:	ff 15 d3 2d 00 00    	call   *0x2dd3(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1205:	f4                   	hlt    
    1206:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    120d:	00 00 00 

0000000000001210 <deregister_tm_clones>:
    1210:	48 8d 3d f9 2d 00 00 	lea    0x2df9(%rip),%rdi        # 4010 <__TMC_END__>
    1217:	48 8d 05 f2 2d 00 00 	lea    0x2df2(%rip),%rax        # 4010 <__TMC_END__>
    121e:	48 39 f8             	cmp    %rdi,%rax
    1221:	74 15                	je     1238 <deregister_tm_clones+0x28>
    1223:	48 8b 05 b6 2d 00 00 	mov    0x2db6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    122a:	48 85 c0             	test   %rax,%rax
    122d:	74 09                	je     1238 <deregister_tm_clones+0x28>
    122f:	ff e0                	jmp    *%rax
    1231:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1238:	c3                   	ret    
    1239:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001240 <register_tm_clones>:
    1240:	48 8d 3d c9 2d 00 00 	lea    0x2dc9(%rip),%rdi        # 4010 <__TMC_END__>
    1247:	48 8d 35 c2 2d 00 00 	lea    0x2dc2(%rip),%rsi        # 4010 <__TMC_END__>
    124e:	48 29 fe             	sub    %rdi,%rsi
    1251:	48 89 f0             	mov    %rsi,%rax
    1254:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1258:	48 c1 f8 03          	sar    $0x3,%rax
    125c:	48 01 c6             	add    %rax,%rsi
    125f:	48 d1 fe             	sar    %rsi
    1262:	74 14                	je     1278 <register_tm_clones+0x38>
    1264:	48 8b 05 85 2d 00 00 	mov    0x2d85(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    126b:	48 85 c0             	test   %rax,%rax
    126e:	74 08                	je     1278 <register_tm_clones+0x38>
    1270:	ff e0                	jmp    *%rax
    1272:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1278:	c3                   	ret    
    1279:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001280 <__do_global_dtors_aux>:
    1280:	f3 0f 1e fa          	endbr64 
    1284:	80 3d 85 2d 00 00 00 	cmpb   $0x0,0x2d85(%rip)        # 4010 <__TMC_END__>
    128b:	75 2b                	jne    12b8 <__do_global_dtors_aux+0x38>
    128d:	55                   	push   %rbp
    128e:	48 83 3d 62 2d 00 00 	cmpq   $0x0,0x2d62(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1295:	00 
    1296:	48 89 e5             	mov    %rsp,%rbp
    1299:	74 0c                	je     12a7 <__do_global_dtors_aux+0x27>
    129b:	48 8b 3d 66 2d 00 00 	mov    0x2d66(%rip),%rdi        # 4008 <__dso_handle>
    12a2:	e8 b9 fd ff ff       	call   1060 <__cxa_finalize@plt>
    12a7:	e8 64 ff ff ff       	call   1210 <deregister_tm_clones>
    12ac:	c6 05 5d 2d 00 00 01 	movb   $0x1,0x2d5d(%rip)        # 4010 <__TMC_END__>
    12b3:	5d                   	pop    %rbp
    12b4:	c3                   	ret    
    12b5:	0f 1f 00             	nopl   (%rax)
    12b8:	c3                   	ret    
    12b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000012c0 <frame_dummy>:
    12c0:	f3 0f 1e fa          	endbr64 
    12c4:	e9 77 ff ff ff       	jmp    1240 <register_tm_clones>

Disassembly of section .fini:

00000000000012cc <_fini>:
    12cc:	f3 0f 1e fa          	endbr64 
    12d0:	48 83 ec 08          	sub    $0x8,%rsp
    12d4:	48 83 c4 08          	add    $0x8,%rsp
    12d8:	c3                   	ret    
