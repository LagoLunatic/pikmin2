.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.fn FormatCallback, local
/* 800D8E2C 000D5D6C  7C 08 02 A6 */	mflr r0
/* 800D8E30 000D5D70  90 01 00 04 */	stw r0, 4(r1)
/* 800D8E34 000D5D74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800D8E38 000D5D78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800D8E3C 000D5D7C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800D8E40 000D5D80  3B C3 00 00 */	addi r30, r3, 0
/* 800D8E44 000D5D84  3C 60 80 4F */	lis r3, __CARDBlock@ha
/* 800D8E48 000D5D88  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800D8E4C 000D5D8C  1C BE 01 10 */	mulli r5, r30, 0x110
/* 800D8E50 000D5D90  93 81 00 10 */	stw r28, 0x10(r1)
/* 800D8E54 000D5D94  38 03 5A F0 */	addi r0, r3, __CARDBlock@l
/* 800D8E58 000D5D98  7C 9C 23 79 */	or. r28, r4, r4
/* 800D8E5C 000D5D9C  7F E0 2A 14 */	add r31, r0, r5
/* 800D8E60 000D5DA0  41 80 00 C4 */	blt .L_800D8F24
/* 800D8E64 000D5DA4  80 7F 00 28 */	lwz r3, 0x28(r31)
/* 800D8E68 000D5DA8  38 03 00 01 */	addi r0, r3, 1
/* 800D8E6C 000D5DAC  90 1F 00 28 */	stw r0, 0x28(r31)
/* 800D8E70 000D5DB0  80 9F 00 28 */	lwz r4, 0x28(r31)
/* 800D8E74 000D5DB4  2C 04 00 05 */	cmpwi r4, 5
/* 800D8E78 000D5DB8  40 80 00 28 */	bge .L_800D8EA0
/* 800D8E7C 000D5DBC  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800D8E80 000D5DC0  3C 60 80 0E */	lis r3, FormatCallback@ha
/* 800D8E84 000D5DC4  38 A3 8E 2C */	addi r5, r3, FormatCallback@l
/* 800D8E88 000D5DC8  7C 80 21 D6 */	mullw r4, r0, r4
/* 800D8E8C 000D5DCC  38 7E 00 00 */	addi r3, r30, 0
/* 800D8E90 000D5DD0  4B FF C5 71 */	bl __CARDEraseSector
/* 800D8E94 000D5DD4  7C 7C 1B 79 */	or. r28, r3, r3
/* 800D8E98 000D5DD8  41 80 00 8C */	blt .L_800D8F24
/* 800D8E9C 000D5DDC  48 00 00 B4 */	b .L_800D8F50
.L_800D8EA0:
/* 800D8EA0 000D5DE0  2C 04 00 0A */	cmpwi r4, 0xa
/* 800D8EA4 000D5DE4  40 80 00 3C */	bge .L_800D8EE0
/* 800D8EA8 000D5DE8  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 800D8EAC 000D5DEC  38 C4 FF FB */	addi r6, r4, -5
/* 800D8EB0 000D5DF0  3C 60 80 0E */	lis r3, FormatCallback@ha
/* 800D8EB4 000D5DF4  80 BF 00 80 */	lwz r5, 0x80(r31)
/* 800D8EB8 000D5DF8  7C 80 31 D6 */	mullw r4, r0, r6
/* 800D8EBC 000D5DFC  54 C0 68 24 */	slwi r0, r6, 0xd
/* 800D8EC0 000D5E00  38 E3 8E 2C */	addi r7, r3, FormatCallback@l
/* 800D8EC4 000D5E04  7C C5 02 14 */	add r6, r5, r0
/* 800D8EC8 000D5E08  38 7E 00 00 */	addi r3, r30, 0
/* 800D8ECC 000D5E0C  38 A0 20 00 */	li r5, 0x2000
/* 800D8ED0 000D5E10  4B FF DE CD */	bl __CARDWrite
/* 800D8ED4 000D5E14  7C 7C 1B 79 */	or. r28, r3, r3
/* 800D8ED8 000D5E18  41 80 00 4C */	blt .L_800D8F24
/* 800D8EDC 000D5E1C  48 00 00 74 */	b .L_800D8F50
.L_800D8EE0:
/* 800D8EE0 000D5E20  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 800D8EE4 000D5E24  38 A0 20 00 */	li r5, 0x2000
/* 800D8EE8 000D5E28  38 03 20 00 */	addi r0, r3, 0x2000
/* 800D8EEC 000D5E2C  90 1F 00 84 */	stw r0, 0x84(r31)
/* 800D8EF0 000D5E30  80 9F 00 80 */	lwz r4, 0x80(r31)
/* 800D8EF4 000D5E34  80 7F 00 84 */	lwz r3, 0x84(r31)
/* 800D8EF8 000D5E38  38 84 40 00 */	addi r4, r4, 0x4000
/* 800D8EFC 000D5E3C  4B F2 C2 A1 */	bl memcpy
/* 800D8F00 000D5E40  80 7F 00 80 */	lwz r3, 0x80(r31)
/* 800D8F04 000D5E44  38 A0 20 00 */	li r5, 0x2000
/* 800D8F08 000D5E48  38 03 60 00 */	addi r0, r3, 0x6000
/* 800D8F0C 000D5E4C  90 1F 00 88 */	stw r0, 0x88(r31)
/* 800D8F10 000D5E50  80 9F 00 80 */	lwz r4, 0x80(r31)
/* 800D8F14 000D5E54  80 7F 00 88 */	lwz r3, 0x88(r31)
/* 800D8F18 000D5E58  3C 84 00 01 */	addis r4, r4, 1
/* 800D8F1C 000D5E5C  38 84 80 00 */	addi r4, r4, -32768
/* 800D8F20 000D5E60  4B F2 C2 7D */	bl memcpy
.L_800D8F24:
/* 800D8F24 000D5E64  83 BF 00 D0 */	lwz r29, 0xd0(r31)
/* 800D8F28 000D5E68  38 00 00 00 */	li r0, 0
/* 800D8F2C 000D5E6C  38 7F 00 00 */	addi r3, r31, 0
/* 800D8F30 000D5E70  90 1F 00 D0 */	stw r0, 0xd0(r31)
/* 800D8F34 000D5E74  7F 84 E3 78 */	mr r4, r28
/* 800D8F38 000D5E78  4B FF C7 4D */	bl __CARDPutControlBlock
/* 800D8F3C 000D5E7C  39 9D 00 00 */	addi r12, r29, 0
/* 800D8F40 000D5E80  7D 88 03 A6 */	mtlr r12
/* 800D8F44 000D5E84  38 7E 00 00 */	addi r3, r30, 0
/* 800D8F48 000D5E88  38 9C 00 00 */	addi r4, r28, 0
/* 800D8F4C 000D5E8C  4E 80 00 21 */	blrl 
.L_800D8F50:
/* 800D8F50 000D5E90  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800D8F54 000D5E94  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800D8F58 000D5E98  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800D8F5C 000D5E9C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800D8F60 000D5EA0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 800D8F64 000D5EA4  38 21 00 20 */	addi r1, r1, 0x20
/* 800D8F68 000D5EA8  7C 08 03 A6 */	mtlr r0
/* 800D8F6C 000D5EAC  4E 80 00 20 */	blr 
.endfn FormatCallback

.fn __CARDFormatRegionAsync, global
/* 800D8F70 000D5EB0  7C 08 02 A6 */	mflr r0
/* 800D8F74 000D5EB4  90 01 00 04 */	stw r0, 4(r1)
/* 800D8F78 000D5EB8  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800D8F7C 000D5EBC  BE 41 00 20 */	stmw r18, 0x20(r1)
/* 800D8F80 000D5EC0  3A 84 00 00 */	addi r20, r4, 0
/* 800D8F84 000D5EC4  3A C3 00 00 */	addi r22, r3, 0
/* 800D8F88 000D5EC8  3A 65 00 00 */	addi r19, r5, 0
/* 800D8F8C 000D5ECC  38 81 00 18 */	addi r4, r1, 0x18
/* 800D8F90 000D5ED0  4B FF C6 3D */	bl __CARDGetControlBlock
/* 800D8F94 000D5ED4  2C 03 00 00 */	cmpwi r3, 0
/* 800D8F98 000D5ED8  40 80 00 08 */	bge .L_800D8FA0
/* 800D8F9C 000D5EDC  48 00 06 18 */	b .L_800D95B4
.L_800D8FA0:
/* 800D8FA0 000D5EE0  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800D8FA4 000D5EE4  38 80 00 FF */	li r4, 0xff
/* 800D8FA8 000D5EE8  38 A0 20 00 */	li r5, 0x2000
/* 800D8FAC 000D5EEC  83 63 00 80 */	lwz r27, 0x80(r3)
/* 800D8FB0 000D5EF0  7F 63 DB 78 */	mr r3, r27
/* 800D8FB4 000D5EF4  4B F2 C1 01 */	bl memset
/* 800D8FB8 000D5EF8  3C 60 CC 00 */	lis r3, 0xCC00206E@ha
/* 800D8FBC 000D5EFC  A2 43 20 6E */	lhz r18, 0xCC00206E@l(r3)
/* 800D8FC0 000D5F00  B2 9B 00 24 */	sth r20, 0x24(r27)
/* 800D8FC4 000D5F04  48 01 7D 6D */	bl __OSLockSram
/* 800D8FC8 000D5F08  80 03 00 0C */	lwz r0, 0xc(r3)
/* 800D8FCC 000D5F0C  90 1B 00 14 */	stw r0, 0x14(r27)
/* 800D8FD0 000D5F10  88 03 00 12 */	lbz r0, 0x12(r3)
/* 800D8FD4 000D5F14  38 60 00 00 */	li r3, 0
/* 800D8FD8 000D5F18  90 1B 00 18 */	stw r0, 0x18(r27)
/* 800D8FDC 000D5F1C  48 01 81 49 */	bl __OSUnlockSram
/* 800D8FE0 000D5F20  48 01 9B B1 */	bl OSGetTime
/* 800D8FE4 000D5F24  3A A4 00 00 */	addi r21, r4, 0
/* 800D8FE8 000D5F28  3A 83 00 00 */	addi r20, r3, 0
/* 800D8FEC 000D5F2C  3B 55 00 00 */	addi r26, r21, 0
/* 800D8FF0 000D5F30  3B D4 00 00 */	addi r30, r20, 0
/* 800D8FF4 000D5F34  48 01 7D 99 */	bl __OSLockSramEx
/* 800D8FF8 000D5F38  1C 16 00 0C */	mulli r0, r22, 0xc
/* 800D8FFC 000D5F3C  7F 23 02 14 */	add r25, r3, r0
/* 800D9000 000D5F40  3C 60 41 C6 */	lis r3, 0x41C64E6D@ha
/* 800D9004 000D5F44  3B 19 00 00 */	addi r24, r25, 0
/* 800D9008 000D5F48  3B E3 4E 6D */	addi r31, r3, 0x41C64E6D@l
/* 800D900C 000D5F4C  3B 80 00 00 */	li r28, 0
/* 800D9010 000D5F50  3A E0 00 04 */	li r23, 4
/* 800D9014 000D5F54  48 00 03 74 */	b .L_800D9388
.L_800D9018:
/* 800D9018 000D5F58  7C BE F9 D6 */	mullw r5, r30, r31
/* 800D901C 000D5F5C  7C 7A F8 16 */	mulhwu r3, r26, r31
/* 800D9020 000D5F60  3B C0 00 00 */	li r30, 0
/* 800D9024 000D5F64  7C A5 1A 14 */	add r5, r5, r3
/* 800D9028 000D5F68  7C 7A F1 D6 */	mullw r3, r26, r30
/* 800D902C 000D5F6C  7C 1A F9 D6 */	mullw r0, r26, r31
/* 800D9030 000D5F70  3B A0 30 39 */	li r29, 0x3039
/* 800D9034 000D5F74  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9038 000D5F78  7C 05 1A 14 */	add r0, r5, r3
/* 800D903C 000D5F7C  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9040 000D5F80  38 A0 00 10 */	li r5, 0x10
/* 800D9044 000D5F84  4B FE 90 F1 */	bl __shr2i
/* 800D9048 000D5F88  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D904C 000D5F8C  88 18 00 00 */	lbz r0, 0(r24)
/* 800D9050 000D5F90  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D9054 000D5F94  7C C6 2A 14 */	add r6, r6, r5
/* 800D9058 000D5F98  7D 04 00 14 */	addc r8, r4, r0
/* 800D905C 000D5F9C  7F 87 07 34 */	extsh r7, r28
/* 800D9060 000D5FA0  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D9064 000D5FA4  7D 1B 39 AE */	stbx r8, r27, r7
/* 800D9068 000D5FA8  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D906C 000D5FAC  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9070 000D5FB0  7C 06 2A 14 */	add r0, r6, r5
/* 800D9074 000D5FB4  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9078 000D5FB8  38 A0 00 10 */	li r5, 0x10
/* 800D907C 000D5FBC  4B FE 90 B9 */	bl __shr2i
/* 800D9080 000D5FC0  3B 40 7F FF */	li r26, 0x7fff
/* 800D9084 000D5FC4  7C 60 F0 38 */	and r0, r3, r30
/* 800D9088 000D5FC8  7C 84 D0 38 */	and r4, r4, r26
/* 800D908C 000D5FCC  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D9090 000D5FD0  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D9094 000D5FD4  7C A5 1A 14 */	add r5, r5, r3
/* 800D9098 000D5FD8  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D909C 000D5FDC  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D90A0 000D5FE0  7C 80 E8 14 */	addc r4, r0, r29
/* 800D90A4 000D5FE4  7C 05 1A 14 */	add r0, r5, r3
/* 800D90A8 000D5FE8  7C 60 F1 14 */	adde r3, r0, r30
/* 800D90AC 000D5FEC  38 A0 00 10 */	li r5, 0x10
/* 800D90B0 000D5FF0  4B FE 90 85 */	bl __shr2i
/* 800D90B4 000D5FF4  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D90B8 000D5FF8  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D90BC 000D5FFC  39 3C 00 01 */	addi r9, r28, 1
/* 800D90C0 000D6000  7D 29 07 34 */	extsh r9, r9
/* 800D90C4 000D6004  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D90C8 000D6008  7C C6 2A 14 */	add r6, r6, r5
/* 800D90CC 000D600C  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D90D0 000D6010  7C E4 00 14 */	addc r7, r4, r0
/* 800D90D4 000D6014  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D90D8 000D6018  7C FB 49 AE */	stbx r7, r27, r9
/* 800D90DC 000D601C  7C 80 E8 14 */	addc r4, r0, r29
/* 800D90E0 000D6020  7C 06 2A 14 */	add r0, r6, r5
/* 800D90E4 000D6024  7C 60 F1 14 */	adde r3, r0, r30
/* 800D90E8 000D6028  38 A0 00 10 */	li r5, 0x10
/* 800D90EC 000D602C  4B FE 90 49 */	bl __shr2i
/* 800D90F0 000D6030  7C 60 F0 38 */	and r0, r3, r30
/* 800D90F4 000D6034  7C 84 D0 38 */	and r4, r4, r26
/* 800D90F8 000D6038  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D90FC 000D603C  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D9100 000D6040  7C A5 1A 14 */	add r5, r5, r3
/* 800D9104 000D6044  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D9108 000D6048  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D910C 000D604C  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9110 000D6050  7C 05 1A 14 */	add r0, r5, r3
/* 800D9114 000D6054  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9118 000D6058  38 A0 00 10 */	li r5, 0x10
/* 800D911C 000D605C  4B FE 90 19 */	bl __shr2i
/* 800D9120 000D6060  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D9124 000D6064  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D9128 000D6068  39 3C 00 02 */	addi r9, r28, 2
/* 800D912C 000D606C  7D 29 07 34 */	extsh r9, r9
/* 800D9130 000D6070  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D9134 000D6074  7C C6 2A 14 */	add r6, r6, r5
/* 800D9138 000D6078  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D913C 000D607C  7C E4 00 14 */	addc r7, r4, r0
/* 800D9140 000D6080  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9144 000D6084  7C FB 49 AE */	stbx r7, r27, r9
/* 800D9148 000D6088  7C 80 E8 14 */	addc r4, r0, r29
/* 800D914C 000D608C  7C 06 2A 14 */	add r0, r6, r5
/* 800D9150 000D6090  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9154 000D6094  38 A0 00 10 */	li r5, 0x10
/* 800D9158 000D6098  4B FE 8F DD */	bl __shr2i
/* 800D915C 000D609C  7C 60 F0 38 */	and r0, r3, r30
/* 800D9160 000D60A0  7C 84 D0 38 */	and r4, r4, r26
/* 800D9164 000D60A4  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D9168 000D60A8  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D916C 000D60AC  7C A5 1A 14 */	add r5, r5, r3
/* 800D9170 000D60B0  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D9174 000D60B4  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9178 000D60B8  7C 80 E8 14 */	addc r4, r0, r29
/* 800D917C 000D60BC  7C 05 1A 14 */	add r0, r5, r3
/* 800D9180 000D60C0  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9184 000D60C4  38 A0 00 10 */	li r5, 0x10
/* 800D9188 000D60C8  4B FE 8F AD */	bl __shr2i
/* 800D918C 000D60CC  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D9190 000D60D0  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D9194 000D60D4  39 3C 00 03 */	addi r9, r28, 3
/* 800D9198 000D60D8  7D 29 07 34 */	extsh r9, r9
/* 800D919C 000D60DC  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D91A0 000D60E0  7C C6 2A 14 */	add r6, r6, r5
/* 800D91A4 000D60E4  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D91A8 000D60E8  7C E4 00 14 */	addc r7, r4, r0
/* 800D91AC 000D60EC  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D91B0 000D60F0  7C FB 49 AE */	stbx r7, r27, r9
/* 800D91B4 000D60F4  7C 80 E8 14 */	addc r4, r0, r29
/* 800D91B8 000D60F8  7C 06 2A 14 */	add r0, r6, r5
/* 800D91BC 000D60FC  7C 60 F1 14 */	adde r3, r0, r30
/* 800D91C0 000D6100  38 A0 00 10 */	li r5, 0x10
/* 800D91C4 000D6104  4B FE 8F 71 */	bl __shr2i
/* 800D91C8 000D6108  7C 60 F0 38 */	and r0, r3, r30
/* 800D91CC 000D610C  7C 84 D0 38 */	and r4, r4, r26
/* 800D91D0 000D6110  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D91D4 000D6114  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D91D8 000D6118  7C A5 1A 14 */	add r5, r5, r3
/* 800D91DC 000D611C  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D91E0 000D6120  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D91E4 000D6124  7C 80 E8 14 */	addc r4, r0, r29
/* 800D91E8 000D6128  7C 05 1A 14 */	add r0, r5, r3
/* 800D91EC 000D612C  7C 60 F1 14 */	adde r3, r0, r30
/* 800D91F0 000D6130  38 A0 00 10 */	li r5, 0x10
/* 800D91F4 000D6134  4B FE 8F 41 */	bl __shr2i
/* 800D91F8 000D6138  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D91FC 000D613C  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D9200 000D6140  39 3C 00 04 */	addi r9, r28, 4
/* 800D9204 000D6144  7D 29 07 34 */	extsh r9, r9
/* 800D9208 000D6148  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D920C 000D614C  7C C6 2A 14 */	add r6, r6, r5
/* 800D9210 000D6150  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D9214 000D6154  7C E4 00 14 */	addc r7, r4, r0
/* 800D9218 000D6158  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D921C 000D615C  7C FB 49 AE */	stbx r7, r27, r9
/* 800D9220 000D6160  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9224 000D6164  7C 06 2A 14 */	add r0, r6, r5
/* 800D9228 000D6168  7C 60 F1 14 */	adde r3, r0, r30
/* 800D922C 000D616C  38 A0 00 10 */	li r5, 0x10
/* 800D9230 000D6170  4B FE 8F 05 */	bl __shr2i
/* 800D9234 000D6174  7C 60 F0 38 */	and r0, r3, r30
/* 800D9238 000D6178  7C 84 D0 38 */	and r4, r4, r26
/* 800D923C 000D617C  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D9240 000D6180  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D9244 000D6184  7C A5 1A 14 */	add r5, r5, r3
/* 800D9248 000D6188  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D924C 000D618C  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9250 000D6190  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9254 000D6194  7C 05 1A 14 */	add r0, r5, r3
/* 800D9258 000D6198  7C 60 F1 14 */	adde r3, r0, r30
/* 800D925C 000D619C  38 A0 00 10 */	li r5, 0x10
/* 800D9260 000D61A0  4B FE 8E D5 */	bl __shr2i
/* 800D9264 000D61A4  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D9268 000D61A8  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D926C 000D61AC  39 3C 00 05 */	addi r9, r28, 5
/* 800D9270 000D61B0  7D 29 07 34 */	extsh r9, r9
/* 800D9274 000D61B4  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D9278 000D61B8  7C C6 2A 14 */	add r6, r6, r5
/* 800D927C 000D61BC  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D9280 000D61C0  7C E4 00 14 */	addc r7, r4, r0
/* 800D9284 000D61C4  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9288 000D61C8  7C FB 49 AE */	stbx r7, r27, r9
/* 800D928C 000D61CC  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9290 000D61D0  7C 06 2A 14 */	add r0, r6, r5
/* 800D9294 000D61D4  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9298 000D61D8  38 A0 00 10 */	li r5, 0x10
/* 800D929C 000D61DC  4B FE 8E 99 */	bl __shr2i
/* 800D92A0 000D61E0  7C 60 F0 38 */	and r0, r3, r30
/* 800D92A4 000D61E4  7C 84 D0 38 */	and r4, r4, r26
/* 800D92A8 000D61E8  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D92AC 000D61EC  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D92B0 000D61F0  7C A5 1A 14 */	add r5, r5, r3
/* 800D92B4 000D61F4  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D92B8 000D61F8  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D92BC 000D61FC  7C 80 E8 14 */	addc r4, r0, r29
/* 800D92C0 000D6200  7C 05 1A 14 */	add r0, r5, r3
/* 800D92C4 000D6204  7C 60 F1 14 */	adde r3, r0, r30
/* 800D92C8 000D6208  38 A0 00 10 */	li r5, 0x10
/* 800D92CC 000D620C  4B FE 8E 69 */	bl __shr2i
/* 800D92D0 000D6210  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D92D4 000D6214  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D92D8 000D6218  39 3C 00 06 */	addi r9, r28, 6
/* 800D92DC 000D621C  7D 29 07 34 */	extsh r9, r9
/* 800D92E0 000D6220  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D92E4 000D6224  7C C6 2A 14 */	add r6, r6, r5
/* 800D92E8 000D6228  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D92EC 000D622C  7C E4 00 14 */	addc r7, r4, r0
/* 800D92F0 000D6230  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D92F4 000D6234  7C FB 49 AE */	stbx r7, r27, r9
/* 800D92F8 000D6238  7C 80 E8 14 */	addc r4, r0, r29
/* 800D92FC 000D623C  7C 06 2A 14 */	add r0, r6, r5
/* 800D9300 000D6240  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9304 000D6244  38 A0 00 10 */	li r5, 0x10
/* 800D9308 000D6248  4B FE 8E 2D */	bl __shr2i
/* 800D930C 000D624C  7C 60 F0 38 */	and r0, r3, r30
/* 800D9310 000D6250  7C 84 D0 38 */	and r4, r4, r26
/* 800D9314 000D6254  7C A0 F9 D6 */	mullw r5, r0, r31
/* 800D9318 000D6258  7C 64 F8 16 */	mulhwu r3, r4, r31
/* 800D931C 000D625C  7C A5 1A 14 */	add r5, r5, r3
/* 800D9320 000D6260  7C 64 F1 D6 */	mullw r3, r4, r30
/* 800D9324 000D6264  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9328 000D6268  7C 80 E8 14 */	addc r4, r0, r29
/* 800D932C 000D626C  7C 05 1A 14 */	add r0, r5, r3
/* 800D9330 000D6270  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9334 000D6274  38 A0 00 10 */	li r5, 0x10
/* 800D9338 000D6278  4B FE 8D FD */	bl __shr2i
/* 800D933C 000D627C  7C C3 F9 D6 */	mullw r6, r3, r31
/* 800D9340 000D6280  7C A4 F8 16 */	mulhwu r5, r4, r31
/* 800D9344 000D6284  39 3C 00 07 */	addi r9, r28, 7
/* 800D9348 000D6288  7D 29 07 34 */	extsh r9, r9
/* 800D934C 000D628C  7C 19 48 AE */	lbzx r0, r25, r9
/* 800D9350 000D6290  7C C6 2A 14 */	add r6, r6, r5
/* 800D9354 000D6294  7C A4 F1 D6 */	mullw r5, r4, r30
/* 800D9358 000D6298  7C E4 00 14 */	addc r7, r4, r0
/* 800D935C 000D629C  7C 04 F9 D6 */	mullw r0, r4, r31
/* 800D9360 000D62A0  7C FB 49 AE */	stbx r7, r27, r9
/* 800D9364 000D62A4  7C 80 E8 14 */	addc r4, r0, r29
/* 800D9368 000D62A8  7C 06 2A 14 */	add r0, r6, r5
/* 800D936C 000D62AC  7C 60 F1 14 */	adde r3, r0, r30
/* 800D9370 000D62B0  38 A0 00 10 */	li r5, 0x10
/* 800D9374 000D62B4  4B FE 8D C1 */	bl __shr2i
/* 800D9378 000D62B8  7C 9A D0 38 */	and r26, r4, r26
/* 800D937C 000D62BC  7C 7E F0 38 */	and r30, r3, r30
/* 800D9380 000D62C0  3B 18 00 08 */	addi r24, r24, 8
/* 800D9384 000D62C4  3B 9C 00 08 */	addi r28, r28, 8
.L_800D9388:
/* 800D9388 000D62C8  7F 80 07 34 */	extsh r0, r28
/* 800D938C 000D62CC  7C 00 B8 00 */	cmpw r0, r23
/* 800D9390 000D62D0  41 80 FC 88 */	blt .L_800D9018
/* 800D9394 000D62D4  48 00 02 18 */	b .L_800D95AC
.L_800D9398:
/* 800D9398 000D62D8  3C 60 41 C6 */	lis r3, 0x41C64E6D@ha
/* 800D939C 000D62DC  3B 23 4E 6D */	addi r25, r3, 0x41C64E6D@l
/* 800D93A0 000D62E0  48 00 00 80 */	b .L_800D9420
.L_800D93A4:
/* 800D93A4 000D62E4  7C BE C9 D6 */	mullw r5, r30, r25
/* 800D93A8 000D62E8  7C 7A C8 16 */	mulhwu r3, r26, r25
/* 800D93AC 000D62EC  3B 00 00 00 */	li r24, 0
/* 800D93B0 000D62F0  7C A5 1A 14 */	add r5, r5, r3
/* 800D93B4 000D62F4  7C 7A C1 D6 */	mullw r3, r26, r24
/* 800D93B8 000D62F8  7C 1A C9 D6 */	mullw r0, r26, r25
/* 800D93BC 000D62FC  3A E0 30 39 */	li r23, 0x3039
/* 800D93C0 000D6300  7C 80 B8 14 */	addc r4, r0, r23
/* 800D93C4 000D6304  7C 05 1A 14 */	add r0, r5, r3
/* 800D93C8 000D6308  7C 60 C1 14 */	adde r3, r0, r24
/* 800D93CC 000D630C  38 A0 00 10 */	li r5, 0x10
/* 800D93D0 000D6310  4B FE 8D 65 */	bl __shr2i
/* 800D93D4 000D6314  7C C3 C9 D6 */	mullw r6, r3, r25
/* 800D93D8 000D6318  88 1D 00 00 */	lbz r0, 0(r29)
/* 800D93DC 000D631C  7C A4 C8 16 */	mulhwu r5, r4, r25
/* 800D93E0 000D6320  7C C6 2A 14 */	add r6, r6, r5
/* 800D93E4 000D6324  7D 04 00 14 */	addc r8, r4, r0
/* 800D93E8 000D6328  7F 87 07 34 */	extsh r7, r28
/* 800D93EC 000D632C  7C A4 C1 D6 */	mullw r5, r4, r24
/* 800D93F0 000D6330  7D 1B 39 AE */	stbx r8, r27, r7
/* 800D93F4 000D6334  7C 04 C9 D6 */	mullw r0, r4, r25
/* 800D93F8 000D6338  7C 80 B8 14 */	addc r4, r0, r23
/* 800D93FC 000D633C  7C 06 2A 14 */	add r0, r6, r5
/* 800D9400 000D6340  7C 60 C1 14 */	adde r3, r0, r24
/* 800D9404 000D6344  38 A0 00 10 */	li r5, 0x10
/* 800D9408 000D6348  4B FE 8D 2D */	bl __shr2i
/* 800D940C 000D634C  38 00 7F FF */	li r0, 0x7fff
/* 800D9410 000D6350  7C 9A 00 38 */	and r26, r4, r0
/* 800D9414 000D6354  7C 7E C0 38 */	and r30, r3, r24
/* 800D9418 000D6358  3B BD 00 01 */	addi r29, r29, 1
/* 800D941C 000D635C  3B 9C 00 01 */	addi r28, r28, 1
.L_800D9420:
/* 800D9420 000D6360  7F 80 07 34 */	extsh r0, r28
/* 800D9424 000D6364  2C 00 00 0C */	cmpwi r0, 0xc
/* 800D9428 000D6368  41 80 FF 7C */	blt .L_800D93A4
/* 800D942C 000D636C  38 60 00 00 */	li r3, 0
/* 800D9430 000D6370  48 01 7D 19 */	bl __OSUnlockSramEx
/* 800D9434 000D6374  92 5B 00 1C */	stw r18, 0x1c(r27)
/* 800D9438 000D6378  3A 40 00 00 */	li r18, 0
/* 800D943C 000D637C  38 7B 00 00 */	addi r3, r27, 0
/* 800D9440 000D6380  92 BB 00 10 */	stw r21, 0x10(r27)
/* 800D9444 000D6384  38 BB 01 FC */	addi r5, r27, 0x1fc
/* 800D9448 000D6388  38 DB 01 FE */	addi r6, r27, 0x1fe
/* 800D944C 000D638C  92 9B 00 0C */	stw r20, 0xc(r27)
/* 800D9450 000D6390  38 80 01 FC */	li r4, 0x1fc
/* 800D9454 000D6394  B2 5B 00 20 */	sth r18, 0x20(r27)
/* 800D9458 000D6398  80 E1 00 18 */	lwz r7, 0x18(r1)
/* 800D945C 000D639C  A0 07 00 08 */	lhz r0, 8(r7)
/* 800D9460 000D63A0  B0 1B 00 22 */	sth r0, 0x22(r27)
/* 800D9464 000D63A4  4B FF DF 69 */	bl __CARDCheckSum
/* 800D9468 000D63A8  48 00 00 4C */	b .L_800D94B4
.L_800D946C:
/* 800D946C 000D63AC  80 81 00 18 */	lwz r4, 0x18(r1)
/* 800D9470 000D63B0  7E 43 07 34 */	extsh r3, r18
/* 800D9474 000D63B4  38 03 00 01 */	addi r0, r3, 1
/* 800D9478 000D63B8  80 64 00 80 */	lwz r3, 0x80(r4)
/* 800D947C 000D63BC  54 00 68 24 */	slwi r0, r0, 0xd
/* 800D9480 000D63C0  38 80 00 FF */	li r4, 0xff
/* 800D9484 000D63C4  7E 83 02 14 */	add r20, r3, r0
/* 800D9488 000D63C8  38 74 00 00 */	addi r3, r20, 0
/* 800D948C 000D63CC  38 A0 20 00 */	li r5, 0x2000
/* 800D9490 000D63D0  4B F2 BC 25 */	bl memset
/* 800D9494 000D63D4  38 94 1F C0 */	addi r4, r20, 0x1fc0
/* 800D9498 000D63D8  B2 54 1F FA */	sth r18, 0x1ffa(r20)
/* 800D949C 000D63DC  38 74 00 00 */	addi r3, r20, 0
/* 800D94A0 000D63E0  38 A4 00 3C */	addi r5, r4, 0x3c
/* 800D94A4 000D63E4  38 C4 00 3E */	addi r6, r4, 0x3e
/* 800D94A8 000D63E8  38 80 1F FC */	li r4, 0x1ffc
/* 800D94AC 000D63EC  4B FF DF 21 */	bl __CARDCheckSum
/* 800D94B0 000D63F0  3A 52 00 01 */	addi r18, r18, 1
.L_800D94B4:
/* 800D94B4 000D63F4  7E 40 07 34 */	extsh r0, r18
/* 800D94B8 000D63F8  2C 00 00 02 */	cmpwi r0, 2
/* 800D94BC 000D63FC  41 80 FF B0 */	blt .L_800D946C
/* 800D94C0 000D6400  3A 40 00 00 */	li r18, 0
/* 800D94C4 000D6404  48 00 00 60 */	b .L_800D9524
.L_800D94C8:
/* 800D94C8 000D6408  80 81 00 18 */	lwz r4, 0x18(r1)
/* 800D94CC 000D640C  7E 43 07 34 */	extsh r3, r18
/* 800D94D0 000D6410  38 03 00 03 */	addi r0, r3, 3
/* 800D94D4 000D6414  80 64 00 80 */	lwz r3, 0x80(r4)
/* 800D94D8 000D6418  54 00 68 24 */	slwi r0, r0, 0xd
/* 800D94DC 000D641C  38 80 00 00 */	li r4, 0
/* 800D94E0 000D6420  7E 83 02 14 */	add r20, r3, r0
/* 800D94E4 000D6424  38 74 00 00 */	addi r3, r20, 0
/* 800D94E8 000D6428  38 A0 20 00 */	li r5, 0x2000
/* 800D94EC 000D642C  4B F2 BB C9 */	bl memset
/* 800D94F0 000D6430  B2 54 00 04 */	sth r18, 4(r20)
/* 800D94F4 000D6434  38 00 00 04 */	li r0, 4
/* 800D94F8 000D6438  38 B4 00 00 */	addi r5, r20, 0
/* 800D94FC 000D643C  80 81 00 18 */	lwz r4, 0x18(r1)
/* 800D9500 000D6440  38 74 00 04 */	addi r3, r20, 4
/* 800D9504 000D6444  38 D4 00 02 */	addi r6, r20, 2
/* 800D9508 000D6448  A0 E4 00 10 */	lhz r7, 0x10(r4)
/* 800D950C 000D644C  38 80 1F FC */	li r4, 0x1ffc
/* 800D9510 000D6450  38 E7 FF FB */	addi r7, r7, -5
/* 800D9514 000D6454  B0 F4 00 06 */	sth r7, 6(r20)
/* 800D9518 000D6458  B0 14 00 08 */	sth r0, 8(r20)
/* 800D951C 000D645C  4B FF DE B1 */	bl __CARDCheckSum
/* 800D9520 000D6460  3A 52 00 01 */	addi r18, r18, 1
.L_800D9524:
/* 800D9524 000D6464  7E 40 07 34 */	extsh r0, r18
/* 800D9528 000D6468  2C 00 00 02 */	cmpwi r0, 2
/* 800D952C 000D646C  41 80 FF 9C */	blt .L_800D94C8
/* 800D9530 000D6470  28 13 00 00 */	cmplwi r19, 0
/* 800D9534 000D6474  41 82 00 0C */	beq .L_800D9540
/* 800D9538 000D6478  7E 60 9B 78 */	mr r0, r19
/* 800D953C 000D647C  48 00 00 0C */	b .L_800D9548
.L_800D9540:
/* 800D9540 000D6480  3C 60 80 0D */	lis r3, __CARDDefaultApiCallback@ha
/* 800D9544 000D6484  38 03 46 6C */	addi r0, r3, __CARDDefaultApiCallback@l
.L_800D9548:
/* 800D9548 000D6488  80 A1 00 18 */	lwz r5, 0x18(r1)
/* 800D954C 000D648C  3C 60 00 01 */	lis r3, 0x0000A000@ha
/* 800D9550 000D6490  38 83 A0 00 */	addi r4, r3, 0x0000A000@l
/* 800D9554 000D6494  90 05 00 D0 */	stw r0, 0xd0(r5)
/* 800D9558 000D6498  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800D955C 000D649C  80 63 00 80 */	lwz r3, 0x80(r3)
/* 800D9560 000D64A0  48 01 31 E9 */	bl DCStoreRange
/* 800D9564 000D64A4  80 81 00 18 */	lwz r4, 0x18(r1)
/* 800D9568 000D64A8  38 00 00 00 */	li r0, 0
/* 800D956C 000D64AC  3C 60 80 0E */	lis r3, FormatCallback@ha
/* 800D9570 000D64B0  90 04 00 28 */	stw r0, 0x28(r4)
/* 800D9574 000D64B4  38 A3 8E 2C */	addi r5, r3, FormatCallback@l
/* 800D9578 000D64B8  38 76 00 00 */	addi r3, r22, 0
/* 800D957C 000D64BC  80 C1 00 18 */	lwz r6, 0x18(r1)
/* 800D9580 000D64C0  80 86 00 0C */	lwz r4, 0xc(r6)
/* 800D9584 000D64C4  80 06 00 28 */	lwz r0, 0x28(r6)
/* 800D9588 000D64C8  7C 84 01 D6 */	mullw r4, r4, r0
/* 800D958C 000D64CC  4B FF BE 75 */	bl __CARDEraseSector
/* 800D9590 000D64D0  7C 72 1B 79 */	or. r18, r3, r3
/* 800D9594 000D64D4  40 80 00 10 */	bge .L_800D95A4
/* 800D9598 000D64D8  80 61 00 18 */	lwz r3, 0x18(r1)
/* 800D959C 000D64DC  7E 44 93 78 */	mr r4, r18
/* 800D95A0 000D64E0  4B FF C0 E5 */	bl __CARDPutControlBlock
.L_800D95A4:
/* 800D95A4 000D64E4  7E 43 93 78 */	mr r3, r18
/* 800D95A8 000D64E8  48 00 00 0C */	b .L_800D95B4
.L_800D95AC:
/* 800D95AC 000D64EC  7F B9 02 14 */	add r29, r25, r0
/* 800D95B0 000D64F0  4B FF FD E8 */	b .L_800D9398
.L_800D95B4:
/* 800D95B4 000D64F4  BA 41 00 20 */	lmw r18, 0x20(r1)
/* 800D95B8 000D64F8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800D95BC 000D64FC  38 21 00 58 */	addi r1, r1, 0x58
/* 800D95C0 000D6500  7C 08 03 A6 */	mtlr r0
/* 800D95C4 000D6504  4E 80 00 20 */	blr 
.endfn __CARDFormatRegionAsync

.fn CARDFormat, global
/* 800D95C8 000D6508  7C 08 02 A6 */	mflr r0
/* 800D95CC 000D650C  90 01 00 04 */	stw r0, 4(r1)
/* 800D95D0 000D6510  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800D95D4 000D6514  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800D95D8 000D6518  7C 7F 1B 78 */	mr r31, r3
/* 800D95DC 000D651C  4B FF BF B1 */	bl __CARDGetFontEncode
/* 800D95E0 000D6520  3C A0 80 0D */	lis r5, __CARDSyncCallback@ha
/* 800D95E4 000D6524  38 83 00 00 */	addi r4, r3, 0
/* 800D95E8 000D6528  38 A5 46 70 */	addi r5, r5, __CARDSyncCallback@l
/* 800D95EC 000D652C  38 7F 00 00 */	addi r3, r31, 0
/* 800D95F0 000D6530  4B FF F9 81 */	bl __CARDFormatRegionAsync
/* 800D95F4 000D6534  2C 03 00 00 */	cmpwi r3, 0
/* 800D95F8 000D6538  40 80 00 08 */	bge .L_800D9600
/* 800D95FC 000D653C  48 00 00 0C */	b .L_800D9608
.L_800D9600:
/* 800D9600 000D6540  7F E3 FB 78 */	mr r3, r31
/* 800D9604 000D6544  4B FF C2 35 */	bl __CARDSync
.L_800D9608:
/* 800D9608 000D6548  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800D960C 000D654C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800D9610 000D6550  38 21 00 18 */	addi r1, r1, 0x18
/* 800D9614 000D6554  7C 08 03 A6 */	mtlr r0
/* 800D9618 000D6558  4E 80 00 20 */	blr 
.endfn CARDFormat
