.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.fn __CARDCompareFileName, global
/* 800D961C 000D655C  38 A3 00 08 */	addi r5, r3, 8
/* 800D9620 000D6560  38 E0 00 20 */	li r7, 0x20
/* 800D9624 000D6564  48 00 00 3C */	b .L_800D9660
.L_800D9628:
/* 800D9628 000D6568  88 05 00 00 */	lbz r0, 0(r5)
/* 800D962C 000D656C  38 A5 00 01 */	addi r5, r5, 1
/* 800D9630 000D6570  88 C4 00 00 */	lbz r6, 0(r4)
/* 800D9634 000D6574  38 84 00 01 */	addi r4, r4, 1
/* 800D9638 000D6578  7C 03 07 74 */	extsb r3, r0
/* 800D963C 000D657C  7C C0 07 74 */	extsb r0, r6
/* 800D9640 000D6580  7C 03 00 00 */	cmpw r3, r0
/* 800D9644 000D6584  41 82 00 0C */	beq .L_800D9650
/* 800D9648 000D6588  38 60 00 00 */	li r3, 0
/* 800D964C 000D658C  4E 80 00 20 */	blr 
.L_800D9650:
/* 800D9650 000D6590  7C C0 07 75 */	extsb. r0, r6
/* 800D9654 000D6594  40 82 00 0C */	bne .L_800D9660
/* 800D9658 000D6598  38 60 00 01 */	li r3, 1
/* 800D965C 000D659C  4E 80 00 20 */	blr 
.L_800D9660:
/* 800D9660 000D65A0  34 E7 FF FF */	addic. r7, r7, -1
/* 800D9664 000D65A4  40 80 FF C4 */	bge .L_800D9628
/* 800D9668 000D65A8  88 04 00 00 */	lbz r0, 0(r4)
/* 800D966C 000D65AC  7C 00 07 75 */	extsb. r0, r0
/* 800D9670 000D65B0  40 82 00 0C */	bne .L_800D967C
/* 800D9674 000D65B4  38 60 00 01 */	li r3, 1
/* 800D9678 000D65B8  4E 80 00 20 */	blr 
.L_800D967C:
/* 800D967C 000D65BC  38 60 00 00 */	li r3, 0
/* 800D9680 000D65C0  4E 80 00 20 */	blr 
.endfn __CARDCompareFileName

.fn __CARDAccess, global
/* 800D9684 000D65C4  7C 08 02 A6 */	mflr r0
/* 800D9688 000D65C8  90 01 00 04 */	stw r0, 4(r1)
/* 800D968C 000D65CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800D9690 000D65D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800D9694 000D65D4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800D9698 000D65D8  7C 9E 23 78 */	mr r30, r4
/* 800D969C 000D65DC  88 04 00 00 */	lbz r0, 0(r4)
/* 800D96A0 000D65E0  83 E3 01 0C */	lwz r31, 0x10c(r3)
/* 800D96A4 000D65E4  28 00 00 FF */	cmplwi r0, 0xff
/* 800D96A8 000D65E8  40 82 00 0C */	bne .L_800D96B4
/* 800D96AC 000D65EC  38 60 FF FC */	li r3, -4
/* 800D96B0 000D65F0  48 00 00 50 */	b .L_800D9700
.L_800D96B4:
/* 800D96B4 000D65F4  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D96B8 000D65F8  38 03 5D 10 */	addi r0, r3, __CARDDiskNone@l
/* 800D96BC 000D65FC  7C 1F 00 40 */	cmplw r31, r0
/* 800D96C0 000D6600  41 82 00 34 */	beq .L_800D96F4
/* 800D96C4 000D6604  38 7E 00 00 */	addi r3, r30, 0
/* 800D96C8 000D6608  38 9F 00 00 */	addi r4, r31, 0
/* 800D96CC 000D660C  38 A0 00 04 */	li r5, 4
/* 800D96D0 000D6610  4B FE D9 19 */	bl memcmp
/* 800D96D4 000D6614  2C 03 00 00 */	cmpwi r3, 0
/* 800D96D8 000D6618  40 82 00 24 */	bne .L_800D96FC
/* 800D96DC 000D661C  38 7E 00 04 */	addi r3, r30, 4
/* 800D96E0 000D6620  38 9F 00 04 */	addi r4, r31, 4
/* 800D96E4 000D6624  38 A0 00 02 */	li r5, 2
/* 800D96E8 000D6628  4B FE D9 01 */	bl memcmp
/* 800D96EC 000D662C  2C 03 00 00 */	cmpwi r3, 0
/* 800D96F0 000D6630  40 82 00 0C */	bne .L_800D96FC
.L_800D96F4:
/* 800D96F4 000D6634  38 60 00 00 */	li r3, 0
/* 800D96F8 000D6638  48 00 00 08 */	b .L_800D9700
.L_800D96FC:
/* 800D96FC 000D663C  38 60 FF F6 */	li r3, -10
.L_800D9700:
/* 800D9700 000D6640  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800D9704 000D6644  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800D9708 000D6648  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800D970C 000D664C  38 21 00 18 */	addi r1, r1, 0x18
/* 800D9710 000D6650  7C 08 03 A6 */	mtlr r0
/* 800D9714 000D6654  4E 80 00 20 */	blr 
.endfn __CARDAccess

.fn __CARDIsWritable, global
/* 800D9718 000D6658  7C 08 02 A6 */	mflr r0
/* 800D971C 000D665C  90 01 00 04 */	stw r0, 4(r1)
/* 800D9720 000D6660  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D9724 000D6664  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 800D9728 000D6668  7C 9B 23 78 */	mr r27, r4
/* 800D972C 000D666C  88 04 00 00 */	lbz r0, 0(r4)
/* 800D9730 000D6670  83 A3 01 0C */	lwz r29, 0x10c(r3)
/* 800D9734 000D6674  28 00 00 FF */	cmplwi r0, 0xff
/* 800D9738 000D6678  40 82 00 0C */	bne .L_800D9744
/* 800D973C 000D667C  3B C0 FF FC */	li r30, -4
/* 800D9740 000D6680  48 00 00 50 */	b .L_800D9790
.L_800D9744:
/* 800D9744 000D6684  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D9748 000D6688  38 03 5D 10 */	addi r0, r3, __CARDDiskNone@l
/* 800D974C 000D668C  7C 1D 00 40 */	cmplw r29, r0
/* 800D9750 000D6690  41 82 00 34 */	beq .L_800D9784
/* 800D9754 000D6694  38 7B 00 00 */	addi r3, r27, 0
/* 800D9758 000D6698  38 9D 00 00 */	addi r4, r29, 0
/* 800D975C 000D669C  38 A0 00 04 */	li r5, 4
/* 800D9760 000D66A0  4B FE D8 89 */	bl memcmp
/* 800D9764 000D66A4  2C 03 00 00 */	cmpwi r3, 0
/* 800D9768 000D66A8  40 82 00 24 */	bne .L_800D978C
/* 800D976C 000D66AC  38 7B 00 04 */	addi r3, r27, 4
/* 800D9770 000D66B0  38 9D 00 04 */	addi r4, r29, 4
/* 800D9774 000D66B4  38 A0 00 02 */	li r5, 2
/* 800D9778 000D66B8  4B FE D8 71 */	bl memcmp
/* 800D977C 000D66BC  2C 03 00 00 */	cmpwi r3, 0
/* 800D9780 000D66C0  40 82 00 0C */	bne .L_800D978C
.L_800D9784:
/* 800D9784 000D66C4  3B C0 00 00 */	li r30, 0
/* 800D9788 000D66C8  48 00 00 08 */	b .L_800D9790
.L_800D978C:
/* 800D978C 000D66CC  3B C0 FF F6 */	li r30, -10
.L_800D9790:
/* 800D9790 000D66D0  2C 1E FF F6 */	cmpwi r30, -10
/* 800D9794 000D66D4  40 82 00 A0 */	bne .L_800D9834
/* 800D9798 000D66D8  88 7B 00 34 */	lbz r3, 0x34(r27)
/* 800D979C 000D66DC  88 0D 82 9A */	lbz r0, __CARDPermMask@sda21(r13)
/* 800D97A0 000D66E0  7C 60 00 38 */	and r0, r3, r0
/* 800D97A4 000D66E4  54 1C 06 3E */	clrlwi r28, r0, 0x18
/* 800D97A8 000D66E8  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 800D97AC 000D66EC  41 82 00 44 */	beq .L_800D97F0
/* 800D97B0 000D66F0  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D97B4 000D66F4  3B E3 5D 10 */	addi r31, r3, __CARDDiskNone@l
/* 800D97B8 000D66F8  38 7B 00 00 */	addi r3, r27, 0
/* 800D97BC 000D66FC  38 9F 00 00 */	addi r4, r31, 0
/* 800D97C0 000D6700  38 A0 00 04 */	li r5, 4
/* 800D97C4 000D6704  4B FE D8 25 */	bl memcmp
/* 800D97C8 000D6708  2C 03 00 00 */	cmpwi r3, 0
/* 800D97CC 000D670C  40 82 00 24 */	bne .L_800D97F0
/* 800D97D0 000D6710  38 7B 00 04 */	addi r3, r27, 4
/* 800D97D4 000D6714  38 9F 00 04 */	addi r4, r31, 4
/* 800D97D8 000D6718  38 A0 00 02 */	li r5, 2
/* 800D97DC 000D671C  4B FE D8 0D */	bl memcmp
/* 800D97E0 000D6720  2C 03 00 00 */	cmpwi r3, 0
/* 800D97E4 000D6724  40 82 00 0C */	bne .L_800D97F0
/* 800D97E8 000D6728  38 60 00 00 */	li r3, 0
/* 800D97EC 000D672C  48 00 00 4C */	b .L_800D9838
.L_800D97F0:
/* 800D97F0 000D6730  57 80 06 73 */	rlwinm. r0, r28, 0, 0x19, 0x19
/* 800D97F4 000D6734  41 82 00 40 */	beq .L_800D9834
/* 800D97F8 000D6738  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D97FC 000D673C  38 83 5D 10 */	addi r4, r3, __CARDDiskNone@l
/* 800D9800 000D6740  38 7B 00 00 */	addi r3, r27, 0
/* 800D9804 000D6744  38 A0 00 04 */	li r5, 4
/* 800D9808 000D6748  4B FE D7 E1 */	bl memcmp
/* 800D980C 000D674C  2C 03 00 00 */	cmpwi r3, 0
/* 800D9810 000D6750  40 82 00 24 */	bne .L_800D9834
/* 800D9814 000D6754  38 7B 00 04 */	addi r3, r27, 4
/* 800D9818 000D6758  38 9D 00 04 */	addi r4, r29, 4
/* 800D981C 000D675C  38 A0 00 02 */	li r5, 2
/* 800D9820 000D6760  4B FE D7 C9 */	bl memcmp
/* 800D9824 000D6764  2C 03 00 00 */	cmpwi r3, 0
/* 800D9828 000D6768  40 82 00 0C */	bne .L_800D9834
/* 800D982C 000D676C  38 60 00 00 */	li r3, 0
/* 800D9830 000D6770  48 00 00 08 */	b .L_800D9838
.L_800D9834:
/* 800D9834 000D6774  7F C3 F3 78 */	mr r3, r30
.L_800D9838:
/* 800D9838 000D6778  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 800D983C 000D677C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D9840 000D6780  38 21 00 28 */	addi r1, r1, 0x28
/* 800D9844 000D6784  7C 08 03 A6 */	mtlr r0
/* 800D9848 000D6788  4E 80 00 20 */	blr 
.endfn __CARDIsWritable

.fn __CARDIsReadable, global
/* 800D984C 000D678C  7C 08 02 A6 */	mflr r0
/* 800D9850 000D6790  90 01 00 04 */	stw r0, 4(r1)
/* 800D9854 000D6794  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800D9858 000D6798  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 800D985C 000D679C  7C 9B 23 78 */	mr r27, r4
/* 800D9860 000D67A0  83 83 01 0C */	lwz r28, 0x10c(r3)
/* 800D9864 000D67A4  4B FF FE 21 */	bl __CARDAccess
/* 800D9868 000D67A8  3B A3 00 00 */	addi r29, r3, 0
/* 800D986C 000D67AC  2C 1D FF F6 */	cmpwi r29, -10
/* 800D9870 000D67B0  40 82 00 9C */	bne .L_800D990C
/* 800D9874 000D67B4  88 7B 00 34 */	lbz r3, 0x34(r27)
/* 800D9878 000D67B8  88 0D 82 9A */	lbz r0, __CARDPermMask@sda21(r13)
/* 800D987C 000D67BC  7C 60 00 38 */	and r0, r3, r0
/* 800D9880 000D67C0  54 1E 06 3E */	clrlwi r30, r0, 0x18
/* 800D9884 000D67C4  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 800D9888 000D67C8  41 82 00 44 */	beq .L_800D98CC
/* 800D988C 000D67CC  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D9890 000D67D0  3B E3 5D 10 */	addi r31, r3, __CARDDiskNone@l
/* 800D9894 000D67D4  38 7B 00 00 */	addi r3, r27, 0
/* 800D9898 000D67D8  38 9F 00 00 */	addi r4, r31, 0
/* 800D989C 000D67DC  38 A0 00 04 */	li r5, 4
/* 800D98A0 000D67E0  4B FE D7 49 */	bl memcmp
/* 800D98A4 000D67E4  2C 03 00 00 */	cmpwi r3, 0
/* 800D98A8 000D67E8  40 82 00 24 */	bne .L_800D98CC
/* 800D98AC 000D67EC  38 7B 00 04 */	addi r3, r27, 4
/* 800D98B0 000D67F0  38 9F 00 04 */	addi r4, r31, 4
/* 800D98B4 000D67F4  38 A0 00 02 */	li r5, 2
/* 800D98B8 000D67F8  4B FE D7 31 */	bl memcmp
/* 800D98BC 000D67FC  2C 03 00 00 */	cmpwi r3, 0
/* 800D98C0 000D6800  40 82 00 0C */	bne .L_800D98CC
/* 800D98C4 000D6804  3B A0 00 00 */	li r29, 0
/* 800D98C8 000D6808  48 00 00 44 */	b .L_800D990C
.L_800D98CC:
/* 800D98CC 000D680C  57 C0 06 73 */	rlwinm. r0, r30, 0, 0x19, 0x19
/* 800D98D0 000D6810  41 82 00 3C */	beq .L_800D990C
/* 800D98D4 000D6814  3C 60 80 4F */	lis r3, __CARDDiskNone@ha
/* 800D98D8 000D6818  38 83 5D 10 */	addi r4, r3, __CARDDiskNone@l
/* 800D98DC 000D681C  38 7B 00 00 */	addi r3, r27, 0
/* 800D98E0 000D6820  38 A0 00 04 */	li r5, 4
/* 800D98E4 000D6824  4B FE D7 05 */	bl memcmp
/* 800D98E8 000D6828  2C 03 00 00 */	cmpwi r3, 0
/* 800D98EC 000D682C  40 82 00 20 */	bne .L_800D990C
/* 800D98F0 000D6830  38 7B 00 04 */	addi r3, r27, 4
/* 800D98F4 000D6834  38 9C 00 04 */	addi r4, r28, 4
/* 800D98F8 000D6838  38 A0 00 02 */	li r5, 2
/* 800D98FC 000D683C  4B FE D6 ED */	bl memcmp
/* 800D9900 000D6840  2C 03 00 00 */	cmpwi r3, 0
/* 800D9904 000D6844  40 82 00 08 */	bne .L_800D990C
/* 800D9908 000D6848  3B A0 00 00 */	li r29, 0
.L_800D990C:
/* 800D990C 000D684C  2C 1D FF F6 */	cmpwi r29, -10
/* 800D9910 000D6850  40 82 00 18 */	bne .L_800D9928
/* 800D9914 000D6854  88 1B 00 34 */	lbz r0, 0x34(r27)
/* 800D9918 000D6858  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 800D991C 000D685C  41 82 00 0C */	beq .L_800D9928
/* 800D9920 000D6860  38 60 00 00 */	li r3, 0
/* 800D9924 000D6864  48 00 00 08 */	b .L_800D992C
.L_800D9928:
/* 800D9928 000D6868  7F A3 EB 78 */	mr r3, r29
.L_800D992C:
/* 800D992C 000D686C  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 800D9930 000D6870  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800D9934 000D6874  38 21 00 28 */	addi r1, r1, 0x28
/* 800D9938 000D6878  7C 08 03 A6 */	mtlr r0
/* 800D993C 000D687C  4E 80 00 20 */	blr 
.endfn __CARDIsReadable

.fn CARDOpen, global
/* 800D9940 000D6880  7C 08 02 A6 */	mflr r0
/* 800D9944 000D6884  90 01 00 04 */	stw r0, 4(r1)
/* 800D9948 000D6888  38 00 FF FF */	li r0, -1
/* 800D994C 000D688C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800D9950 000D6890  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 800D9954 000D6894  3B 24 00 00 */	addi r25, r4, 0
/* 800D9958 000D6898  3B C5 00 00 */	addi r30, r5, 0
/* 800D995C 000D689C  3B A3 00 00 */	addi r29, r3, 0
/* 800D9960 000D68A0  38 81 00 14 */	addi r4, r1, 0x14
/* 800D9964 000D68A4  90 05 00 00 */	stw r0, 0(r5)
/* 800D9968 000D68A8  4B FF BC 65 */	bl __CARDGetControlBlock
/* 800D996C 000D68AC  2C 03 00 00 */	cmpwi r3, 0
/* 800D9970 000D68B0  40 80 00 08 */	bge .L_800D9978
/* 800D9974 000D68B4  48 00 00 D4 */	b .L_800D9A48
.L_800D9978:
/* 800D9978 000D68B8  83 41 00 14 */	lwz r26, 0x14(r1)
/* 800D997C 000D68BC  80 1A 00 00 */	lwz r0, 0(r26)
/* 800D9980 000D68C0  2C 00 00 00 */	cmpwi r0, 0
/* 800D9984 000D68C4  40 82 00 0C */	bne .L_800D9990
/* 800D9988 000D68C8  3B 40 FF FD */	li r26, -3
/* 800D998C 000D68CC  48 00 00 5C */	b .L_800D99E8
.L_800D9990:
/* 800D9990 000D68D0  7F 43 D3 78 */	mr r3, r26
/* 800D9994 000D68D4  4B FF D7 D5 */	bl __CARDGetDirBlock
/* 800D9998 000D68D8  3B 63 00 00 */	addi r27, r3, 0
/* 800D999C 000D68DC  3B 80 00 00 */	li r28, 0
.L_800D99A0:
/* 800D99A0 000D68E0  38 7A 00 00 */	addi r3, r26, 0
/* 800D99A4 000D68E4  38 9B 00 00 */	addi r4, r27, 0
/* 800D99A8 000D68E8  4B FF FC DD */	bl __CARDAccess
/* 800D99AC 000D68EC  2C 03 00 00 */	cmpwi r3, 0
/* 800D99B0 000D68F0  41 80 00 24 */	blt .L_800D99D4
/* 800D99B4 000D68F4  38 7B 00 00 */	addi r3, r27, 0
/* 800D99B8 000D68F8  38 99 00 00 */	addi r4, r25, 0
/* 800D99BC 000D68FC  4B FF FC 61 */	bl __CARDCompareFileName
/* 800D99C0 000D6900  2C 03 00 00 */	cmpwi r3, 0
/* 800D99C4 000D6904  41 82 00 10 */	beq .L_800D99D4
/* 800D99C8 000D6908  3B FC 00 00 */	addi r31, r28, 0
/* 800D99CC 000D690C  3B 40 00 00 */	li r26, 0
/* 800D99D0 000D6910  48 00 00 18 */	b .L_800D99E8
.L_800D99D4:
/* 800D99D4 000D6914  3B 9C 00 01 */	addi r28, r28, 1
/* 800D99D8 000D6918  2C 1C 00 7F */	cmpwi r28, 0x7f
/* 800D99DC 000D691C  3B 7B 00 40 */	addi r27, r27, 0x40
/* 800D99E0 000D6920  41 80 FF C0 */	blt .L_800D99A0
/* 800D99E4 000D6924  3B 40 FF FC */	li r26, -4
.L_800D99E8:
/* 800D99E8 000D6928  2C 1A 00 00 */	cmpwi r26, 0
/* 800D99EC 000D692C  41 80 00 50 */	blt .L_800D9A3C
/* 800D99F0 000D6930  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800D99F4 000D6934  4B FF D7 75 */	bl __CARDGetDirBlock
/* 800D99F8 000D6938  57 E0 30 32 */	slwi r0, r31, 6
/* 800D99FC 000D693C  7C A3 02 14 */	add r5, r3, r0
/* 800D9A00 000D6940  A0 85 00 36 */	lhz r4, 0x36(r5)
/* 800D9A04 000D6944  28 04 00 05 */	cmplwi r4, 5
/* 800D9A08 000D6948  41 80 00 14 */	blt .L_800D9A1C
/* 800D9A0C 000D694C  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800D9A10 000D6950  A0 03 00 10 */	lhz r0, 0x10(r3)
/* 800D9A14 000D6954  7C 04 00 40 */	cmplw r4, r0
/* 800D9A18 000D6958  41 80 00 0C */	blt .L_800D9A24
.L_800D9A1C:
/* 800D9A1C 000D695C  3B 40 FF FA */	li r26, -6
/* 800D9A20 000D6960  48 00 00 1C */	b .L_800D9A3C
.L_800D9A24:
/* 800D9A24 000D6964  93 BE 00 00 */	stw r29, 0(r30)
/* 800D9A28 000D6968  38 00 00 00 */	li r0, 0
/* 800D9A2C 000D696C  93 FE 00 04 */	stw r31, 4(r30)
/* 800D9A30 000D6970  90 1E 00 08 */	stw r0, 8(r30)
/* 800D9A34 000D6974  A0 05 00 36 */	lhz r0, 0x36(r5)
/* 800D9A38 000D6978  B0 1E 00 10 */	sth r0, 0x10(r30)
.L_800D9A3C:
/* 800D9A3C 000D697C  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800D9A40 000D6980  7F 44 D3 78 */	mr r4, r26
/* 800D9A44 000D6984  4B FF BC 41 */	bl __CARDPutControlBlock
.L_800D9A48:
/* 800D9A48 000D6988  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 800D9A4C 000D698C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800D9A50 000D6990  38 21 00 38 */	addi r1, r1, 0x38
/* 800D9A54 000D6994  7C 08 03 A6 */	mtlr r0
/* 800D9A58 000D6998  4E 80 00 20 */	blr 
.endfn CARDOpen

.fn CARDClose, global
/* 800D9A5C 000D699C  7C 08 02 A6 */	mflr r0
/* 800D9A60 000D69A0  90 01 00 04 */	stw r0, 4(r1)
/* 800D9A64 000D69A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800D9A68 000D69A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800D9A6C 000D69AC  7C 7F 1B 78 */	mr r31, r3
/* 800D9A70 000D69B0  38 81 00 0C */	addi r4, r1, 0xc
/* 800D9A74 000D69B4  80 63 00 00 */	lwz r3, 0(r3)
/* 800D9A78 000D69B8  4B FF BB 55 */	bl __CARDGetControlBlock
/* 800D9A7C 000D69BC  2C 03 00 00 */	cmpwi r3, 0
/* 800D9A80 000D69C0  40 80 00 08 */	bge .L_800D9A88
/* 800D9A84 000D69C4  48 00 00 18 */	b .L_800D9A9C
.L_800D9A88:
/* 800D9A88 000D69C8  38 00 FF FF */	li r0, -1
/* 800D9A8C 000D69CC  90 1F 00 00 */	stw r0, 0(r31)
/* 800D9A90 000D69D0  38 80 00 00 */	li r4, 0
/* 800D9A94 000D69D4  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800D9A98 000D69D8  4B FF BB ED */	bl __CARDPutControlBlock
.L_800D9A9C:
/* 800D9A9C 000D69DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800D9AA0 000D69E0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800D9AA4 000D69E4  38 21 00 18 */	addi r1, r1, 0x18
/* 800D9AA8 000D69E8  7C 08 03 A6 */	mtlr r0
/* 800D9AAC 000D69EC  4E 80 00 20 */	blr 
.endfn CARDClose
