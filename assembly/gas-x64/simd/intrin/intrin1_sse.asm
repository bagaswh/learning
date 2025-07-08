
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
    10a4:	55                   	push   %rbp
    10a5:	48 89 e5             	mov    %rsp,%rbp
    10a8:	41 54                	push   %r12
    10aa:	53                   	push   %rbx
    10ab:	48 83 ec 20          	sub    $0x20,%rsp
    10af:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    10b6:	00 00 
    10b8:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    10bc:	31 c0                	xor    %eax,%eax
    10be:	48 8d 84 24 00 00 c3 	lea    -0x3d0000(%rsp),%rax
    10c5:	ff 
    10c6:	48 39 c4             	cmp    %rax,%rsp
    10c9:	74 15                	je     10e0 <main+0x40>
    10cb:	48 81 ec 00 10 00 00 	sub    $0x1000,%rsp
    10d2:	48 83 8c 24 f8 0f 00 	orq    $0x0,0xff8(%rsp)
    10d9:	00 00 
    10db:	48 39 c4             	cmp    %rax,%rsp
    10de:	75 eb                	jne    10cb <main+0x2b>
    10e0:	48 81 ec 00 09 00 00 	sub    $0x900,%rsp
    10e7:	48 83 8c 24 f8 08 00 	orq    $0x0,0x8f8(%rsp)
    10ee:	00 00 
    10f0:	e8 7b ff ff ff       	call   1070 <clock@plt>
    10f5:	49 89 e4             	mov    %rsp,%r12
    10f8:	66 0f ef c0          	pxor   %xmm0,%xmm0
    10fc:	48 89 c3             	mov    %rax,%rbx
    10ff:	4c 89 e2             	mov    %r12,%rdx
    1102:	49 8d 8c 24 00 09 3d 	lea    0x3d0900(%r12),%rcx
    1109:	00 
    110a:	f3 0f 6f 0a          	movdqu (%rdx),%xmm1
    110e:	b8 a0 86 01 00       	mov    $0x186a0,%eax
    1113:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
    1118:	66 0f fe c1          	paddd  %xmm1,%xmm0
    111c:	83 e8 01             	sub    $0x1,%eax
    111f:	75 f7                	jne    1118 <main+0x78>
    1121:	48 83 c2 10          	add    $0x10,%rdx
    1125:	48 39 d1             	cmp    %rdx,%rcx
    1128:	75 e0                	jne    110a <main+0x6a>
    112a:	66 0f 6f c8          	movdqa %xmm0,%xmm1
    112e:	66 0f 73 d9 08       	psrldq $0x8,%xmm1
    1133:	66 0f fe c8          	paddd  %xmm0,%xmm1
    1137:	0f 29 4d d0          	movaps %xmm1,-0x30(%rbp)
    113b:	e8 30 ff ff ff       	call   1070 <clock@plt>
    1140:	66 0f ef c0          	pxor   %xmm0,%xmm0
    1144:	bf 01 00 00 00       	mov    $0x1,%edi
    1149:	48 8d 35 b4 0e 00 00 	lea    0xeb4(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    1150:	48 29 d8             	sub    %rbx,%rax
    1153:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
    1158:	b8 01 00 00 00       	mov    $0x1,%eax
    115d:	f2 0f 5e 05 c3 0e 00 	divsd  0xec3(%rip),%xmm0        # 2028 <_IO_stdin_used+0x28>
    1164:	00 
    1165:	e8 26 ff ff ff       	call   1090 <__printf_chk@plt>
    116a:	66 0f 6f 4d d0       	movdqa -0x30(%rbp),%xmm1
    116f:	31 c0                	xor    %eax,%eax
    1171:	48 8d 35 a0 0e 00 00 	lea    0xea0(%rip),%rsi        # 2018 <_IO_stdin_used+0x18>
    1178:	bf 01 00 00 00       	mov    $0x1,%edi
    117d:	66 0f 6f c1          	movdqa %xmm1,%xmm0
    1181:	66 0f 73 d8 04       	psrldq $0x4,%xmm0
    1186:	66 0f fe c1          	paddd  %xmm1,%xmm0
    118a:	66 0f 7e c2          	movd   %xmm0,%edx
    118e:	e8 fd fe ff ff       	call   1090 <__printf_chk@plt>
    1193:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1197:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    119e:	00 00 
    11a0:	75 0b                	jne    11ad <main+0x10d>
    11a2:	48 8d 65 f0          	lea    -0x10(%rbp),%rsp
    11a6:	31 c0                	xor    %eax,%eax
    11a8:	5b                   	pop    %rbx
    11a9:	41 5c                	pop    %r12
    11ab:	5d                   	pop    %rbp
    11ac:	c3                   	ret    
    11ad:	e8 ce fe ff ff       	call   1080 <__stack_chk_fail@plt>
    11b2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    11b9:	00 00 00 
    11bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000000011c0 <_start>:
    11c0:	f3 0f 1e fa          	endbr64 
    11c4:	31 ed                	xor    %ebp,%ebp
    11c6:	49 89 d1             	mov    %rdx,%r9
    11c9:	5e                   	pop    %rsi
    11ca:	48 89 e2             	mov    %rsp,%rdx
    11cd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    11d1:	50                   	push   %rax
    11d2:	54                   	push   %rsp
    11d3:	45 31 c0             	xor    %r8d,%r8d
    11d6:	31 c9                	xor    %ecx,%ecx
    11d8:	48 8d 3d c1 fe ff ff 	lea    -0x13f(%rip),%rdi        # 10a0 <main>
    11df:	ff 15 f3 2d 00 00    	call   *0x2df3(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    11e5:	f4                   	hlt    
    11e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    11ed:	00 00 00 

00000000000011f0 <deregister_tm_clones>:
    11f0:	48 8d 3d 19 2e 00 00 	lea    0x2e19(%rip),%rdi        # 4010 <__TMC_END__>
    11f7:	48 8d 05 12 2e 00 00 	lea    0x2e12(%rip),%rax        # 4010 <__TMC_END__>
    11fe:	48 39 f8             	cmp    %rdi,%rax
    1201:	74 15                	je     1218 <deregister_tm_clones+0x28>
    1203:	48 8b 05 d6 2d 00 00 	mov    0x2dd6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    120a:	48 85 c0             	test   %rax,%rax
    120d:	74 09                	je     1218 <deregister_tm_clones+0x28>
    120f:	ff e0                	jmp    *%rax
    1211:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1218:	c3                   	ret    
    1219:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001220 <register_tm_clones>:
    1220:	48 8d 3d e9 2d 00 00 	lea    0x2de9(%rip),%rdi        # 4010 <__TMC_END__>
    1227:	48 8d 35 e2 2d 00 00 	lea    0x2de2(%rip),%rsi        # 4010 <__TMC_END__>
    122e:	48 29 fe             	sub    %rdi,%rsi
    1231:	48 89 f0             	mov    %rsi,%rax
    1234:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1238:	48 c1 f8 03          	sar    $0x3,%rax
    123c:	48 01 c6             	add    %rax,%rsi
    123f:	48 d1 fe             	sar    %rsi
    1242:	74 14                	je     1258 <register_tm_clones+0x38>
    1244:	48 8b 05 a5 2d 00 00 	mov    0x2da5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    124b:	48 85 c0             	test   %rax,%rax
    124e:	74 08                	je     1258 <register_tm_clones+0x38>
    1250:	ff e0                	jmp    *%rax
    1252:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1258:	c3                   	ret    
    1259:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001260 <__do_global_dtors_aux>:
    1260:	f3 0f 1e fa          	endbr64 
    1264:	80 3d a5 2d 00 00 00 	cmpb   $0x0,0x2da5(%rip)        # 4010 <__TMC_END__>
    126b:	75 2b                	jne    1298 <__do_global_dtors_aux+0x38>
    126d:	55                   	push   %rbp
    126e:	48 83 3d 82 2d 00 00 	cmpq   $0x0,0x2d82(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1275:	00 
    1276:	48 89 e5             	mov    %rsp,%rbp
    1279:	74 0c                	je     1287 <__do_global_dtors_aux+0x27>
    127b:	48 8b 3d 86 2d 00 00 	mov    0x2d86(%rip),%rdi        # 4008 <__dso_handle>
    1282:	e8 d9 fd ff ff       	call   1060 <__cxa_finalize@plt>
    1287:	e8 64 ff ff ff       	call   11f0 <deregister_tm_clones>
    128c:	c6 05 7d 2d 00 00 01 	movb   $0x1,0x2d7d(%rip)        # 4010 <__TMC_END__>
    1293:	5d                   	pop    %rbp
    1294:	c3                   	ret    
    1295:	0f 1f 00             	nopl   (%rax)
    1298:	c3                   	ret    
    1299:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000012a0 <frame_dummy>:
    12a0:	f3 0f 1e fa          	endbr64 
    12a4:	e9 77 ff ff ff       	jmp    1220 <register_tm_clones>

Disassembly of section .fini:

00000000000012ac <_fini>:
    12ac:	f3 0f 1e fa          	endbr64 
    12b0:	48 83 ec 08          	sub    $0x8,%rsp
    12b4:	48 83 c4 08          	add    $0x8,%rsp
    12b8:	c3                   	ret    
