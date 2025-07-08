
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
    10f8:	c5 f9 ef c0          	vpxor  %xmm0,%xmm0,%xmm0
    10fc:	48 89 c3             	mov    %rax,%rbx
    10ff:	4c 89 e2             	mov    %r12,%rdx
    1102:	49 8d 8c 24 00 09 3d 	lea    0x3d0900(%r12),%rcx
    1109:	00 
    110a:	c5 fa 6f 0a          	vmovdqu (%rdx),%xmm1
    110e:	b8 a0 86 01 00       	mov    $0x186a0,%eax
    1113:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
    1118:	c5 f9 fe c1          	vpaddd %xmm1,%xmm0,%xmm0
    111c:	83 e8 01             	sub    $0x1,%eax
    111f:	75 f7                	jne    1118 <main+0x78>
    1121:	48 83 c2 10          	add    $0x10,%rdx
    1125:	48 39 d1             	cmp    %rdx,%rcx
    1128:	75 e0                	jne    110a <main+0x6a>
    112a:	c5 f1 73 d8 08       	vpsrldq $0x8,%xmm0,%xmm1
    112f:	c5 f9 fe c9          	vpaddd %xmm1,%xmm0,%xmm1
    1133:	c5 f9 7f 4d d0       	vmovdqa %xmm1,-0x30(%rbp)
    1138:	e8 33 ff ff ff       	call   1070 <clock@plt>
    113d:	c5 f8 57 c0          	vxorps %xmm0,%xmm0,%xmm0
    1141:	bf 01 00 00 00       	mov    $0x1,%edi
    1146:	48 8d 35 b7 0e 00 00 	lea    0xeb7(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    114d:	48 29 d8             	sub    %rbx,%rax
    1150:	c4 e1 fb 2a c0       	vcvtsi2sd %rax,%xmm0,%xmm0
    1155:	b8 01 00 00 00       	mov    $0x1,%eax
    115a:	c5 fb 5e 05 c6 0e 00 	vdivsd 0xec6(%rip),%xmm0,%xmm0        # 2028 <_IO_stdin_used+0x28>
    1161:	00 
    1162:	e8 29 ff ff ff       	call   1090 <__printf_chk@plt>
    1167:	c5 f9 6f 4d d0       	vmovdqa -0x30(%rbp),%xmm1
    116c:	31 c0                	xor    %eax,%eax
    116e:	48 8d 35 a3 0e 00 00 	lea    0xea3(%rip),%rsi        # 2018 <_IO_stdin_used+0x18>
    1175:	bf 01 00 00 00       	mov    $0x1,%edi
    117a:	c5 f9 73 d9 04       	vpsrldq $0x4,%xmm1,%xmm0
    117f:	c5 f1 fe c0          	vpaddd %xmm0,%xmm1,%xmm0
    1183:	c5 f9 7e c2          	vmovd  %xmm0,%edx
    1187:	e8 04 ff ff ff       	call   1090 <__printf_chk@plt>
    118c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1190:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    1197:	00 00 
    1199:	75 0b                	jne    11a6 <main+0x106>
    119b:	48 8d 65 f0          	lea    -0x10(%rbp),%rsp
    119f:	31 c0                	xor    %eax,%eax
    11a1:	5b                   	pop    %rbx
    11a2:	41 5c                	pop    %r12
    11a4:	5d                   	pop    %rbp
    11a5:	c3                   	ret    
    11a6:	e8 d5 fe ff ff       	call   1080 <__stack_chk_fail@plt>
    11ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011b0 <_start>:
    11b0:	f3 0f 1e fa          	endbr64 
    11b4:	31 ed                	xor    %ebp,%ebp
    11b6:	49 89 d1             	mov    %rdx,%r9
    11b9:	5e                   	pop    %rsi
    11ba:	48 89 e2             	mov    %rsp,%rdx
    11bd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    11c1:	50                   	push   %rax
    11c2:	54                   	push   %rsp
    11c3:	45 31 c0             	xor    %r8d,%r8d
    11c6:	31 c9                	xor    %ecx,%ecx
    11c8:	48 8d 3d d1 fe ff ff 	lea    -0x12f(%rip),%rdi        # 10a0 <main>
    11cf:	ff 15 03 2e 00 00    	call   *0x2e03(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    11d5:	f4                   	hlt    
    11d6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    11dd:	00 00 00 

00000000000011e0 <deregister_tm_clones>:
    11e0:	48 8d 3d 29 2e 00 00 	lea    0x2e29(%rip),%rdi        # 4010 <__TMC_END__>
    11e7:	48 8d 05 22 2e 00 00 	lea    0x2e22(%rip),%rax        # 4010 <__TMC_END__>
    11ee:	48 39 f8             	cmp    %rdi,%rax
    11f1:	74 15                	je     1208 <deregister_tm_clones+0x28>
    11f3:	48 8b 05 e6 2d 00 00 	mov    0x2de6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    11fa:	48 85 c0             	test   %rax,%rax
    11fd:	74 09                	je     1208 <deregister_tm_clones+0x28>
    11ff:	ff e0                	jmp    *%rax
    1201:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1208:	c3                   	ret    
    1209:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001210 <register_tm_clones>:
    1210:	48 8d 3d f9 2d 00 00 	lea    0x2df9(%rip),%rdi        # 4010 <__TMC_END__>
    1217:	48 8d 35 f2 2d 00 00 	lea    0x2df2(%rip),%rsi        # 4010 <__TMC_END__>
    121e:	48 29 fe             	sub    %rdi,%rsi
    1221:	48 89 f0             	mov    %rsi,%rax
    1224:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1228:	48 c1 f8 03          	sar    $0x3,%rax
    122c:	48 01 c6             	add    %rax,%rsi
    122f:	48 d1 fe             	sar    %rsi
    1232:	74 14                	je     1248 <register_tm_clones+0x38>
    1234:	48 8b 05 b5 2d 00 00 	mov    0x2db5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    123b:	48 85 c0             	test   %rax,%rax
    123e:	74 08                	je     1248 <register_tm_clones+0x38>
    1240:	ff e0                	jmp    *%rax
    1242:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1248:	c3                   	ret    
    1249:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001250 <__do_global_dtors_aux>:
    1250:	f3 0f 1e fa          	endbr64 
    1254:	80 3d b5 2d 00 00 00 	cmpb   $0x0,0x2db5(%rip)        # 4010 <__TMC_END__>
    125b:	75 2b                	jne    1288 <__do_global_dtors_aux+0x38>
    125d:	55                   	push   %rbp
    125e:	48 83 3d 92 2d 00 00 	cmpq   $0x0,0x2d92(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1265:	00 
    1266:	48 89 e5             	mov    %rsp,%rbp
    1269:	74 0c                	je     1277 <__do_global_dtors_aux+0x27>
    126b:	48 8b 3d 96 2d 00 00 	mov    0x2d96(%rip),%rdi        # 4008 <__dso_handle>
    1272:	e8 e9 fd ff ff       	call   1060 <__cxa_finalize@plt>
    1277:	e8 64 ff ff ff       	call   11e0 <deregister_tm_clones>
    127c:	c6 05 8d 2d 00 00 01 	movb   $0x1,0x2d8d(%rip)        # 4010 <__TMC_END__>
    1283:	5d                   	pop    %rbp
    1284:	c3                   	ret    
    1285:	0f 1f 00             	nopl   (%rax)
    1288:	c3                   	ret    
    1289:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001290 <frame_dummy>:
    1290:	f3 0f 1e fa          	endbr64 
    1294:	e9 77 ff ff ff       	jmp    1210 <register_tm_clones>

Disassembly of section .fini:

000000000000129c <_fini>:
    129c:	f3 0f 1e fa          	endbr64 
    12a0:	48 83 ec 08          	sub    $0x8,%rsp
    12a4:	48 83 c4 08          	add    $0x8,%rsp
    12a8:	c3                   	ret    
