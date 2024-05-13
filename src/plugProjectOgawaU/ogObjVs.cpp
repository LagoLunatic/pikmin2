#include "og/newScreen/Vs.h"
#include "og/newScreen/Challenge.h"
#include "efx2d/Arg.h"
#include "efx2d/T2DSprayset.h"
#include "efx2d/T2DSensor.h"
#include "og/Sound.h"
#include "System.h"
#include "trig.h"

namespace og {
namespace newScreen {

/**
 * @note Address: 0x80325A40
 * @note Size: 0x15C
 */
ObjVs::ObjVs(char const* name)
{
	mFadeLevel = 0.0f;
	mScale     = 0.0f;
	mName      = name;
	mDisp      = nullptr;
	mBloGroup  = nullptr;

	for (int i = 0; i < 4; i++) {
		mPane_bedama1P[i]    = nullptr;
		mPane_nodama1P[i]    = nullptr;
		mPane_bedama2P[i]    = nullptr;
		mPane_nodama2P[i]    = nullptr;
		mScaleMgrP1_1[i]     = nullptr;
		mScaleMgrP2_1[i]     = nullptr;
		mScaleMgrP1_2[i]     = nullptr;
		mScaleMgrP2_2[i]     = nullptr;
		mBedamaGotFlagsP1[i] = false;
		mBedamaGotFlagsP2[i] = false;
	}

	mFinishTimer      = 4.016667f;
	mDoneState        = 0;
	mHasAllBedamaP1   = false;
	mHasAllBedamaP2   = false;
	mFirstBedamaGetP1 = false;
	mFirstBedamaGetP2 = false;
	mBedamaGetTimer   = 0.05f;
	mScreenIcons      = nullptr;
	mSetBedamaFlag    = true;
	mPaneObake1P      = nullptr;
	mPaneObake2P      = nullptr;
	mAlphaObakeP1     = 0.0f;
	mAlphaObakeP2     = 0.0f;
	mObakeEnabledP1   = false;
	mObakeEnabledP2   = false;
	mObakeMovePos     = 0.0f;
	mPlayWinSound     = false;
}

/**
 * @note Address: 0x80325B9C
 * @note Size: 0xAC
 */
ObjVs::~ObjVs() { }

/**
 * @note Address: 0x80325C48
 * @note Size: 0x800
 */
void ObjVs::doCreate(JKRArchive* arc)
{
	mScreenP1 = new ScreenSet;
	mScreenP2 = new ScreenSet;

	og::Screen::DispMemberVs* disp = static_cast<og::Screen::DispMemberVs*>(getDispMember());
	if (disp->isID(OWNER_OGA, MEMBER_VS)) {
		mDisp = disp;
	} else {
		if (disp->isID(OWNER_OGA, MEMBER_DUMMY)) {
			mDisp = new og::Screen::DispMemberVs;
		} else {
			JUT_PANICLINE(246, "ERR! in ObjVs Create���s�I\n");
		}
	}

	mBloGroup = new og::Screen::BloGroup(2);
	mBloGroup->addBlo("challenge_1P.blo", mScreenP1->mScreen, 0x1040000, arc);
	mBloGroup->addBlo("challenge_2P.blo", mScreenP2->mScreen, 0x1040000, arc);
	mScreenP1->init(&mDisp->mOlimarData, arc, &mDisp->mRedPikminCount);
	mScreenP2->init(&mDisp->mLouieData, arc, &mDisp->mBluePikminCount);

	P2DScreen::Mgr_tuning* bdamaScreen = new P2DScreen::Mgr_tuning;
	bdamaScreen->set("b_dama.blo", 0x1040000, arc);

	P2DScreen::Mgr_tuning* scrn1 = mScreenP1->mScreen;
	P2DScreen::Mgr_tuning* scrn2 = mScreenP2->mScreen;

	J2DPictureEx* paneBdamaR = static_cast<J2DPictureEx*>(bdamaScreen->search('Pb_red'));
	J2DPictureEx* paneBdamaY = static_cast<J2DPictureEx*>(bdamaScreen->search('Pb_yello'));
	J2DPictureEx* paneBdamaB = static_cast<J2DPictureEx*>(bdamaScreen->search('Pb_blue'));
	J2DPictureEx* panePcup   = static_cast<J2DPictureEx*>(bdamaScreen->search('Pcup'));

	J2DPane* root = scrn1->search('ROOT');
	int xoffs     = 0;
	for (int i = 0; i < 4; i++) {
		mPane_bedama1P[i]
		    = og::Screen::CopyPictureToPane(paneBdamaY, root, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP1YOffs, 'bd1P_000' + i);
		mPane_nodama1P[i]
		    = og::Screen::CopyPictureToPane(panePcup, root, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP1YOffs, 'nd1P_000' + i);
		mPane_windama1P[i]
		    = og::Screen::CopyPictureToPane(paneBdamaB, root, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP1YOffs, 'wd1P_000' + i);
		mScaleMgrP1_1[i] = new og::Screen::ScaleMgr;
		mScaleMgrP1_2[i] = new og::Screen::ScaleMgr;
		xoffs += 40;
		mPane_windama1P[i]->hide();
	}

	J2DPane* root2 = scrn2->search('ROOT');
	xoffs          = 0;
	for (int i = 0; i < 4; i++) {
		mPane_bedama2P[i]
		    = og::Screen::CopyPictureToPane(paneBdamaY, root2, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP2YOffs, 'bd2P_000' + i);
		mPane_nodama2P[i]
		    = og::Screen::CopyPictureToPane(panePcup, root2, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP2YOffs, 'nd2P_000' + i);
		mPane_windama2P[i]
		    = og::Screen::CopyPictureToPane(paneBdamaR, root2, msVal.mMarbleBaseXOffs + xoffs, msVal.mMarbleP2YOffs, 'wd2P_000' + i);
		mScaleMgrP2_1[i] = new og::Screen::ScaleMgr;
		mScaleMgrP2_2[i] = new og::Screen::ScaleMgr;
		xoffs += 40;
		mPane_windama2P[i]->hide();
	}

	mScreenIcons = new P2DScreen::Mgr_tuning;
	mScreenIcons->set("obake_icon.blo", 0x1040000, arc);

	J2DPictureEx* paneObake = static_cast<J2DPictureEx*>(mScreenIcons->search('obake'));
	mPaneObake1P            = og::Screen::CopyPictureToPane(paneObake, root, msVal.mRouletteXOffs, msVal.mRouletteP1YOffs, 'obake1P');
	mPaneObake2P            = og::Screen::CopyPictureToPane(paneObake, root, msVal.mRouletteXOffs, msVal.mRouletteP2YOffs, 'obake2P');
	mPaneObake1P->setAlpha(mAlphaObakeP1 * 255.0f);
	mPaneObake2P->setAlpha(mAlphaObakeP2 * 255.0f);
	setOnOffBdama(false);
	/*
	stwu     r1, -0x80(r1)
	mflr     r0
	stw      r0, 0x84(r1)
	stfd     f31, 0x70(r1)
	psq_st   f31, 120(r1), 0, qr0
	stmw     r14, 0x28(r1)
	lis      r5, lbl_8048F368@ha
	mr       r31, r3
	addi     r0, r5, lbl_8048F368@l
	mr       r14, r4
	stw      r0, 0x20(r1)
	li       r3, 0x1c
	bl       __nw__FUl
	or.      r15, r3, r3
	beq      lbl_80325D08
	li       r3, 0x148
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325C98
	bl       __ct__Q29P2DScreen10Mgr_tuningFv

lbl_80325C98:
	stw      r3, 0(r15)
	li       r3, 0x9c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325CB0
	bl       __ct__Q32og6Screen18CallBack_LifeGaugeFv

lbl_80325CB0:
	stw      r3, 4(r15)
	li       r3, 0x44
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325CC8
	bl       __ct__Q32og6Screen11DopingCheckFv

lbl_80325CC8:
	stw      r3, 8(r15)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325CE0
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80325CE0:
	stw      r3, 0xc(r15)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325CF8
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80325CF8:
	stw      r3, 0x10(r15)
	li       r0, 0
	stw      r0, 0x14(r15)
	stw      r0, 0x18(r15)

lbl_80325D08:
	stw      r15, 0x44(r31)
	li       r3, 0x1c
	bl       __nw__FUl
	or.      r15, r3, r3
	beq      lbl_80325DA0
	li       r3, 0x148
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325D30
	bl       __ct__Q29P2DScreen10Mgr_tuningFv

lbl_80325D30:
	stw      r3, 0(r15)
	li       r3, 0x9c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325D48
	bl       __ct__Q32og6Screen18CallBack_LifeGaugeFv

lbl_80325D48:
	stw      r3, 4(r15)
	li       r3, 0x44
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325D60
	bl       __ct__Q32og6Screen11DopingCheckFv

lbl_80325D60:
	stw      r3, 8(r15)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325D78
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80325D78:
	stw      r3, 0xc(r15)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325D90
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80325D90:
	stw      r3, 0x10(r15)
	li       r0, 0
	stw      r0, 0x14(r15)
	stw      r0, 0x18(r15)

lbl_80325DA0:
	stw      r15, 0x48(r31)
	mr       r3, r31
	bl       getDispMember__Q26Screen7ObjBaseFv
	lis      r4, 0x004F4741@ha
	mr       r15, r3
	li       r6, 0x5653
	li       r5, 0
	addi     r4, r4, 0x004F4741@l
	bl       isID__Q32og6Screen14DispMemberBaseFUlUx
	clrlwi.  r0, r3, 0x18
	beq      lbl_80325DD4
	stw      r15, 0x38(r31)
	b        lbl_80325EEC

lbl_80325DD4:
	lis      r4, 0x004F4741@ha
	lis      r6, 0x554D4D59@ha
	mr       r3, r15
	li       r5, 0x44
	addi     r4, r4, 0x004F4741@l
	addi     r6, r6, 0x554D4D59@l
	bl       isID__Q32og6Screen14DispMemberBaseFUlUx
	clrlwi.  r0, r3, 0x18
	beq      lbl_80325ED0
	li       r3, 0x74
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325EC8
	lis      r5, __vt__Q32og6Screen14DispMemberBase@ha
	lis      r4, __vt__Q32og6Screen12DispMemberVs@ha
	addi     r0, r5, __vt__Q32og6Screen14DispMemberBase@l
	li       r10, 0
	stw      r0, 0(r3)
	addi     r0, r4, __vt__Q32og6Screen12DispMemberVs@l
	lfs      f0, lbl_8051DD98@sda21(r2)
	li       r9, 0x4d2
	stw      r10, 4(r3)
	li       r8, 0x32
	lfs      f1, lbl_8051DDA4@sda21(r2)
	li       r7, 1
	stw      r0, 0(r3)
	li       r6, 2
	li       r5, 0xa
	li       r4, 0x6f
	stfs     f0, 0xc(r3)
	li       r0, 0xde
	lfs      f0, lbl_8051DDA8@sda21(r2)
	stw      r10, 0x10(r3)
	stw      r10, 0x18(r3)
	stw      r9, 0x14(r3)
	stw      r8, 0x1c(r3)
	stb      r10, 0x20(r3)
	stw      r10, 0x24(r3)
	stfs     f1, 0x28(r3)
	stw      r7, 0x2c(r3)
	stw      r6, 0x30(r3)
	stw      r5, 0x34(r3)
	stw      r5, 0x38(r3)
	stb      r7, 0x3c(r3)
	stfs     f1, 0x40(r3)
	stw      r7, 0x44(r3)
	stw      r6, 0x48(r3)
	stw      r5, 0x4c(r3)
	stw      r5, 0x50(r3)
	stb      r7, 0x54(r3)
	stw      r4, 0x58(r3)
	stw      r0, 0x5c(r3)
	stw      r10, 0x60(r3)
	stw      r10, 0x64(r3)
	stw      r10, 8(r3)
	stb      r10, 0x68(r3)
	stb      r10, 0x69(r3)
	stb      r10, 0x6a(r3)
	stb      r10, 0x6b(r3)
	stfs     f0, 0x6c(r3)
	stfs     f0, 0x70(r3)

lbl_80325EC8:
	stw      r3, 0x38(r31)
	b        lbl_80325EEC

lbl_80325ED0:
	lwz      r3, 0x20(r1)
	lwz      r4, 0x20(r1)
	addi     r3, r3, 0
	addi     r5, r4, 0xc
	li       r4, 0xf6
	crclr    6
	bl       panic_f__12JUTExceptionFPCciPCce

lbl_80325EEC:
	li       r3, 0xc
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80325F04
	li       r4, 2
	bl       __ct__Q32og6Screen8BloGroupFUs

lbl_80325F04:
	stw      r3, 0x3c(r31)
	mr       r7, r14
	lwz      r3, 0x20(r1)
	lis      r6, 0x104
	lwz      r5, 0x44(r31)
	addi     r4, r3, 0x28
	lwz      r3, 0x3c(r31)
	lwz      r5, 0(r5)
	bl
addBlo__Q32og6Screen8BloGroupFPcPQ29P2DScreen10Mgr_tuningUlP10JKRArchive lwz
r5, 0x48(r31) mr       r7, r14 lwz      r4, 0x20(r1) lis      r6, 0x104 lwz
r3, 0x3c(r31) lwz      r5, 0(r5) addi     r4, r4, 0x3c bl
addBlo__Q32og6Screen8BloGroupFPcPQ29P2DScreen10Mgr_tuningUlP10JKRArchive lwz
r6, 0x38(r31) mr       r5, r14 lwz      r3, 0x44(r31) addi     r4, r6, 0x28
	addi     r6, r6, 0x58
	bl
init__Q42og9newScreen5ObjVs9ScreenSetFPQ32og6Screen8DataNaviP10JKRArchivePUl
lwz r6, 0x38(r31) mr       r5, r14 lwz      r3, 0x48(r31) addi     r4, r6,
0x40 addi r6, r6, 0x5c bl
init__Q42og9newScreen5ObjVs9ScreenSetFPQ32og6Screen8DataNaviP10JKRArchivePUl
li r3, 0x148 bl       __nw__FUl or.      r15, r3, r3 beq      lbl_80325F90
bl
__ct__Q29P2DScreen10Mgr_tuningFv mr       r15, r3

lbl_80325F90:
	lwz      r4, 0x20(r1)
	mr       r3, r15
	mr       r6, r14
	lis      r5, 0x104
	addi     r4, r4, 0x50
	bl       set__9J2DScreenFPCcUlP10JKRArchive
	mr       r3, r15
	lwz      r8, 0x44(r31)
	lwz      r12, 0(r15)
	lis      r4, 0x5F726564@ha
	lwz      r7, 0x48(r31)
	addi     r6, r4, 0x5F726564@l
	lwz      r12, 0x3c(r12)
	li       r5, 0x5062
	lwz      r17, 0(r8)
	lwz      r29, 0(r7)
	mtctr    r12
	bctrl
	mr       r0, r3
	mr       r3, r15
	lwz      r12, 0(r15)
	lis      r5, 0x656C6C6F@ha
	lis      r4, 0x50625F79@ha
	mr       r16, r0
	lwz      r12, 0x3c(r12)
	addi     r6, r5, 0x656C6C6F@l
	addi     r5, r4, 0x50625F79@l
	mtctr    r12
	bctrl
	mr       r0, r3
	mr       r3, r15
	lwz      r12, 0(r15)
	lis      r5, 0x626C7565@ha
	lis      r4, 0x0050625F@ha
	mr       r20, r0
	lwz      r12, 0x3c(r12)
	addi     r6, r5, 0x626C7565@l
	addi     r5, r4, 0x0050625F@l
	mtctr    r12
	bctrl
	mr       r0, r3
	mr       r3, r15
	lwz      r12, 0(r15)
	lis      r4, 0x50637570@ha
	mr       r15, r0
	li       r5, 0
	lwz      r12, 0x3c(r12)
	addi     r6, r4, 0x50637570@l
	mtctr    r12
	bctrl
	mr       r0, r3
	mr       r3, r17
	lwz      r12, 0(r17)
	lis      r4, 0x524F4F54@ha
	mr       r19, r0
	li       r5, 0
	lwz      r12, 0x3c(r12)
	addi     r6, r4, 0x524F4F54@l
	mtctr    r12
	bctrl
	lis      r8, msVal__Q32og9newScreen5ObjVs@ha
	lis      r7, 0x5F303030@ha
	lis      r6, 0x62643150@ha
	lis      r5, 0x6E643150@ha
	lis      r4, 0x77643150@ha
	lfd      f31, lbl_8051DDB0@sda21(r2)
	mr       r30, r3
	mr       r26, r31
	addi     r23, r8, msVal__Q32og9newScreen5ObjVs@l
	addi     r22, r7, 0x5F303030@l
	addi     r21, r6, 0x62643150@l
	addi     r18, r5, 0x6E643150@l
	addi     r17, r4, 0x77643150@l
	li       r27, 0
	li       r25, 0
	lis      r24, 0x4330

lbl_803260C0:
	xoris    r0, r25, 0x8000
	srawi    r28, r27, 0x1f
	stw      r0, 0xc(r1)
	addc     r6, r27, r22
	lfs      f1, 0x10(r23)
	adde     r5, r28, r21
	stw      r24, 8(r1)
	mr       r3, r20
	lfs      f2, 0x14(r23)
	mr       r4, r30
	lfd      f0, 8(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	xoris    r0, r25, 0x8000
	stw      r3, 0x54(r26)
	addc     r6, r27, r22
	mr       r3, r19
	stw      r0, 0x14(r1)
	adde     r5, r28, r18
	lfs      f1, 0x10(r23)
	mr       r4, r30
	stw      r24, 0x10(r1)
	lfs      f2, 0x14(r23)
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	xoris    r0, r25, 0x8000
	stw      r3, 0x64(r26)
	addc     r6, r27, r22
	mr       r3, r15
	stw      r0, 0x1c(r1)
	adde     r5, r28, r17
	lfs      f1, 0x10(r23)
	mr       r4, r30
	stw      r24, 0x18(r1)
	lfs      f2, 0x14(r23)
	lfd      f0, 0x18(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	stw      r3, 0x74(r26)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80326180
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80326180:
	stw      r3, 0xb4(r26)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_80326198
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_80326198:
	stw      r3, 0xd4(r26)
	addi     r27, r27, 1
	cmpwi    r27, 4
	li       r0, 0
	lwz      r3, 0x74(r26)
	addi     r25, r25, 0x28
	addi     r26, r26, 4
	stb      r0, 0xb0(r3)
	blt      lbl_803260C0
	mr       r3, r29
	lis      r4, 0x524F4F54@ha
	lwz      r12, 0(r29)
	addi     r6, r4, 0x524F4F54@l
	li       r5, 0
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	lis      r8, msVal__Q32og9newScreen5ObjVs@ha
	lis      r7, 0x5F303030@ha
	lis      r6, 0x62643250@ha
	lis      r5, 0x6E643250@ha
	lis      r4, 0x77643250@ha
	lfd      f31, lbl_8051DDB0@sda21(r2)
	mr       r18, r3
	mr       r21, r31
	addi     r24, r8, msVal__Q32og9newScreen5ObjVs@l
	addi     r26, r7, 0x5F303030@l
	addi     r27, r6, 0x62643250@l
	addi     r28, r5, 0x6E643250@l
	addi     r29, r4, 0x77643250@l
	li       r17, 0
	li       r22, 0
	lis      r25, 0x4330

lbl_8032621C:
	xoris    r0, r22, 0x8000
	srawi    r15, r17, 0x1f
	stw      r0, 0x1c(r1)
	addc     r6, r17, r26
	lfs      f1, 0x10(r23)
	adde     r5, r15, r27
	stw      r25, 0x18(r1)
	mr       r3, r20
	lfs      f2, 0x18(r24)
	mr       r4, r18
	lfd      f0, 0x18(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	xoris    r0, r22, 0x8000
	stw      r3, 0x84(r21)
	addc     r6, r17, r26
	mr       r3, r19
	stw      r0, 0x14(r1)
	adde     r5, r15, r28
	lfs      f1, 0x10(r23)
	mr       r4, r18
	stw      r25, 0x10(r1)
	lfs      f2, 0x18(r24)
	lfd      f0, 0x10(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	xoris    r0, r22, 0x8000
	stw      r3, 0x94(r21)
	addc     r6, r17, r26
	mr       r3, r16
	stw      r0, 0xc(r1)
	adde     r5, r15, r29
	lfs      f1, 0x10(r23)
	mr       r4, r18
	stw      r25, 8(r1)
	lfs      f2, 0x18(r24)
	lfd      f0, 8(r1)
	fsubs    f0, f0, f31
	fadds    f1, f1, f0
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	stw      r3, 0xa4(r21)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_803262DC
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_803262DC:
	stw      r3, 0xc4(r21)
	li       r3, 0x1c
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_803262F4
	bl       __ct__Q32og6Screen8ScaleMgrFv

lbl_803262F4:
	stw      r3, 0xe4(r21)
	addi     r17, r17, 1
	cmpwi    r17, 4
	li       r0, 0
	lwz      r3, 0xa4(r21)
	addi     r22, r22, 0x28
	addi     r21, r21, 4
	stb      r0, 0xb0(r3)
	blt      lbl_8032621C
	li       r3, 0x148
	bl       __nw__FUl
	cmplwi   r3, 0
	beq      lbl_8032632C
	bl       __ct__Q29P2DScreen10Mgr_tuningFv

lbl_8032632C:
	stw      r3, 0x40(r31)
	mr       r6, r14
	lwz      r3, 0x20(r1)
	lis      r5, 0x104
	addi     r4, r3, 0x5c
	lwz      r3, 0x40(r31)
	bl       set__9J2DScreenFPCcUlP10JKRArchive
	lwz      r3, 0x40(r31)
	lis      r4, 0x62616B65@ha
	addi     r6, r4, 0x62616B65@l
	li       r5, 0x6f
	lwz      r12, 0(r3)
	lwz      r12, 0x3c(r12)
	mtctr    r12
	bctrl
	lis      r4, msVal__Q32og9newScreen5ObjVs@ha
	lis      r6, 0x6B653150@ha
	addi     r14, r4, msVal__Q32og9newScreen5ObjVs@l
	lis      r5, 0x006F6261@ha
	lfs      f1, 0x1c(r14)
	mr       r15, r3
	lfs      f2, 0x20(r14)
	mr       r4, r30
	addi     r6, r6, 0x6B653150@l
	addi     r5, r5, 0x006F6261@l
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	stw      r3, 0x110(r31)
	lis      r3, msVal__Q32og9newScreen5ObjVs@ha
	addi     r3, r3, msVal__Q32og9newScreen5ObjVs@l
	lis      r6, 0x6B653250@ha
	lis      r5, 0x006F6261@ha
	lfs      f1, 0x1c(r14)
	lfs      f2, 0x24(r3)
	mr       r3, r15
	mr       r4, r18
	addi     r6, r6, 0x6B653250@l
	addi     r5, r5, 0x006F6261@l
	bl       CopyPictureToPane__Q22og6ScreenFP12J2DPictureExP7J2DPaneffUx
	stw      r3, 0x114(r31)
	lfs      f1, lbl_8051DDAC@sda21(r2)
	lfs      f0, 0x118(r31)
	lwz      r3, 0x110(r31)
	fmuls    f0, f1, f0
	lwz      r12, 0(r3)
	fctiwz   f0, f0
	lwz      r12, 0x24(r12)
	stfd     f0, 0x18(r1)
	lwz      r4, 0x1c(r1)
	mtctr    r12
	bctrl
	lfs      f1, lbl_8051DDAC@sda21(r2)
	lfs      f0, 0x11c(r31)
	lwz      r3, 0x114(r31)
	fmuls    f0, f1, f0
	lwz      r12, 0(r3)
	fctiwz   f0, f0
	lwz      r12, 0x24(r12)
	stfd     f0, 0x10(r1)
	lwz      r4, 0x14(r1)
	mtctr    r12
	bctrl
	mr       r3, r31
	li       r4, 0
	bl       setOnOffBdama__Q32og9newScreen5ObjVsFb
	psq_l    f31, 120(r1), 0, qr0
	lfd      f31, 0x70(r1)
	lmw      r14, 0x28(r1)
	lwz      r0, 0x84(r1)
	mtlr     r0
	addi     r1, r1, 0x80
	blr
	*/
}

/**
 * @note Address: N/A
 * @note Size: 0x20
 */
void ObjVs::isCompBdama(int)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x138
 */
bool ObjVs::startGetBdama(J2DPane* pane)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0xC8
 */
void ObjVs::startBdamaComp(J2DPane*)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x124
 */
void ObjVs::startBdamaWinRed(J2DPane*)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: N/A
 * @note Size: 0x13C
 */
void ObjVs::startBdamaWinBlue(J2DPane*)
{
	// UNUSED FUNCTION
}

/**
 * @note Address: 0x80326448
 * @note Size: 0xA28
 */
void ObjVs::setOnOffBdama(bool doEfx)
{
	bool p1win = false;
	bool p2win = false;

	for (int i = 0; i < 4; i++) {
		f32 scale1 = mScaleMgrP1_1[i]->calc();
		f32 scale2 = mScaleMgrP2_1[i]->calc();
		f32 scale3 = mScaleMgrP1_2[i]->calc();
		f32 scale4 = mScaleMgrP2_2[i]->calc();

		mPane_windama1P[i]->updateScale(scale3);
		mPane_windama2P[i]->updateScale(scale4);

		if (mDisp->mFlags[0] && mDisp->mMarbleCountP1 == i && mBedamaGetTimer > 0.0f) {
			mBedamaGetTimer -= sys->mDeltaTime;
			if (mBedamaGetTimer <= 0.0f) {
				mPane_windama1P[i]->show();
				if (!mFirstBedamaGetP1) {
					mFirstBedamaGetP1 = true;
					if (doEfx) {
						Vector2f pos;
						og::Screen::calcGlbCenter(mPane_windama1P[i], &pos);

						JUtility::TColor colorA(0x20, 0x20, 255, 255);
						JUtility::TColor colorB(0x57, 0x87, 255, 255);
						efx2d::ArgScaleColorColor arg(pos, 1.0f, colorA, colorB);
						efx2d::T2DSprayset_forVS efx;
						efx.create(&arg);
						ogSound->setBdamaGet();
						mDoneState = 1;
						mScaleMgrP1_2[i]->up();
						p1win = true;
					}
				}
			}
		}

		if (mDisp->mFlags[1] && mDisp->mMarbleCountP2 == i && mBedamaGetTimer > 0.0f) {
			mBedamaGetTimer -= sys->mDeltaTime;
			if (mBedamaGetTimer <= 0.0f) {
				mPane_windama2P[i]->show();
				if (!mFirstBedamaGetP2) {
					mFirstBedamaGetP2 = true;
					if (doEfx) {
						Vector2f pos;
						og::Screen::calcGlbCenter(mPane_windama2P[i], &pos);

						JUtility::TColor colorA(255, 0, 0, 255);
						JUtility::TColor colorB(255, 0x87, 0x87, 255);
						efx2d::ArgScaleColorColor arg(pos, 1.0f, colorA, colorB);
						efx2d::T2DSprayset_forVS efx;
						efx.create(&arg);
						ogSound->setBdamaGet();
						mDoneState = 1;
						mScaleMgrP2_2[i]->up();
						p2win = true;
					}
				}
			}
		}

		if (!mFirstBedamaGetP1 && !mFirstBedamaGetP2) {
			if (mDisp->mMarbleCountP1 > i) {
				mPane_nodama1P[i]->hide();
				mPane_bedama1P[i]->show();
				mPane_bedama1P[i]->updateScale(scale1);
				if (!mBedamaGotFlagsP1[i]) {
					mHasAllBedamaP1 = false;
					if (i == 3) {
						mDoneState      = 1;
						mHasAllBedamaP1 = true;
					}
					if (doEfx) {
						if (mDoneState != 1) {
							ogSound->setBdamaGet();
							Vector2f pos;
							og::Screen::calcGlbCenter(mPane_bedama1P[i], &pos);

							JUtility::TColor colorA(0xcf, 0xcf, 0, 255);
							JUtility::TColor colorB(0xe7, 0xe7, 0x57, 255);
							efx2d::ArgScaleColorColor arg(pos, 1.0f, colorA, colorB);
							efx2d::T2DSprayset_forVS efx;
							efx.create(&arg);
						}
						mScaleMgrP1_1[i]->up();
					}
				}
				mBedamaGotFlagsP1[i] = true;
			} else {
				mPane_bedama1P[i]->hide();
				mPane_nodama1P[i]->show();
				mPane_nodama1P[i]->updateScale(scale1);
				mBedamaGotFlagsP1[i] = false;
			}

			if (mDisp->mMarbleCountP2 > i) {
				mPane_nodama2P[i]->hide();
				mPane_bedama2P[i]->show();
				mPane_bedama2P[i]->updateScale(scale1);
				if (!mBedamaGotFlagsP2[i]) {
					mHasAllBedamaP2 = false;
					if (i == 3) {
						mDoneState      = 1;
						mHasAllBedamaP2 = true;
					}
					if (doEfx) {
						if (mDoneState != 1) {
							ogSound->setBdamaGet();
							Vector2f pos;
							og::Screen::calcGlbCenter(mPane_bedama2P[i], &pos);

							JUtility::TColor colorA(0xcf, 0xcf, 0, 255);
							JUtility::TColor colorB(0xe7, 0xe7, 0x57, 255);
							efx2d::ArgScaleColorColor arg(pos, 1.0f, colorA, colorB);
							efx2d::T2DSprayset_forVS efx;
							efx.create(&arg);
						}
						mScaleMgrP2_1[i]->up();
					}
				}
				mBedamaGotFlagsP2[i] = true;
			} else {
				mPane_bedama2P[i]->hide();
				mPane_nodama2P[i]->show();
				mPane_nodama2P[i]->updateScale(scale2);
				mBedamaGotFlagsP2[i] = false;
			}
		}
	}

	if (mHasAllBedamaP1 && mBedamaGetTimer > 0.0f) {
		mBedamaGetTimer -= sys->mDeltaTime;
		if (mBedamaGetTimer <= 0.0f && doEfx) {
			ogSound->setBdamaGet();
			f32 scale = 0.6f;
			for (int i = 0; i < 4; i++) {
				mScaleMgrP1_1[i]->up();
				Vector2f pos;
				og::Screen::calcGlbCenter(mPane_bedama1P[i], &pos);

				efx2d::ArgScale arg(pos, scale);
				efx2d::T2DSensorGet_forVS efx;
				efx.create(&arg);
				p1win = true;
			}
		}
	}

	if (mHasAllBedamaP2 && mBedamaGetTimer > 0.0f) {
		mBedamaGetTimer -= sys->mDeltaTime;
		if (mBedamaGetTimer <= 0.0f && doEfx) {
			ogSound->setBdamaGet();
			f32 scale = 0.6f;
			for (int i = 0; i < 4; i++) {
				mScaleMgrP2_1[i]->up();
				Vector2f pos;
				og::Screen::calcGlbCenter(mPane_bedama2P[i], &pos);

				efx2d::ArgScale arg(pos, scale);
				efx2d::T2DSensorGet_forVS efx;
				efx.create(&arg);
				p2win = true;
			}
		}
	}

	if (!mPlayWinSound) {
		if (p1win && p2win) {
			ogSound->setVsDraw();
			mPlayWinSound = true;
		} else if (p1win) {
			ogSound->setVsWin1P();
			mPlayWinSound = true;
		} else if (p2win) {
			ogSound->setVsWin2P();
			mPlayWinSound = true;
		}
	}
	/*
	stwu     r1, -0x1f0(r1)
	mflr     r0
	stw      r0, 0x1f4(r1)
	stfd     f31, 0x1e0(r1)
	psq_st   f31, 488(r1), 0, qr0
	stfd     f30, 0x1d0(r1)
	psq_st   f30, 472(r1), 0, qr0
	stfd     f29, 0x1c0(r1)
	psq_st   f29, 456(r1), 0, qr0
	stfd     f28, 0x1b0(r1)
	psq_st   f28, 440(r1), 0, qr0
	stmw     r20, 0x180(r1)
	mr       r26, r3
	mr       r27, r4
	mr       r31, r26
	li       r30, 0
	li       r29, 0
	li       r28, 0

lbl_80326490:
	lwz      r3, 0xb4(r31)
	bl       calc__Q32og6Screen8ScaleMgrFv
	fmr      f30, f1
	lwz      r3, 0xc4(r31)
	bl       calc__Q32og6Screen8ScaleMgrFv
	fmr      f31, f1
	lwz      r3, 0xd4(r31)
	bl       calc__Q32og6Screen8ScaleMgrFv
	fmr      f28, f1
	lwz      r3, 0xe4(r31)
	bl       calc__Q32og6Screen8ScaleMgrFv
	lwz      r3, 0x74(r31)
	fmr      f29, f1
	stfs     f28, 0xcc(r3)
	stfs     f28, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0xa4(r31)
	stfs     f29, 0xcc(r3)
	stfs     f29, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x38(r26)
	lbz      r0, 0x68(r3)
	cmplwi   r0, 0
	beq      lbl_80326670
	lwz      r0, 0x60(r3)
	cmpw     r0, r28
	bne      lbl_80326670
	lfs      f2, 0x108(r26)
	lfs      f1, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f2, f1
	ble      lbl_80326670
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x54(r3)
	fsubs    f0, f2, f0
	stfs     f0, 0x108(r26)
	lfs      f0, 0x108(r26)
	fcmpo    cr0, f0, f1
	cror     2, 0, 2
	bne      lbl_80326670
	lwz      r3, 0x74(r31)
	li       r4, 1
	stb      r4, 0xb0(r3)
	lbz      r0, 0x10c(r26)
	cmplwi   r0, 0
	bne      lbl_80326670
	clrlwi.  r0, r27, 0x18
	stb      r4, 0x10c(r26)
	beq      lbl_80326670
	lwz      r3, 0x74(r31)
	addi     r4, r1, 0x80
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	lis      r3, __vt__Q25efx2d7TBaseIF@ha
	li       r21, 0xff
	addi     r0, r3, __vt__Q25efx2d7TBaseIF@l
	li       r8, 0
	lwz      r3, 0x80(r1)
	lis      r7, __vt__Q25efx2d5TBase@ha
	li       r12, 0x20
	lwz      r5, 0x84(r1)
	li       r23, 0x57
	li       r22, 0x87
	stw      r3, 0x50(r1)
	lis      r3, __vt__Q25efx2d3Arg@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	lfs      f0, lbl_8051DDA4@sda21(r2)
	stw      r5, 0x54(r1)
	addi     r11, r3, __vt__Q25efx2d3Arg@l
	lfs      f2, 0x50(r1)
	lis      r9, __vt__Q25efx2d18ArgScaleColorColor@ha
	lfs      f1, 0x54(r1)
	lis      r3, __vt__Q25efx2d17T2DSprayset_forVS@ha
	li       r6, 0x22
	li       r5, 0x23
	stw      r0, 0x16c(r1)
	addi     r0, r7, __vt__Q25efx2d5TBase@l
	addi     r7, r4, __vt__Q25efx2d8TSimple2@l
	addi     r10, r9, __vt__Q25efx2d18ArgScaleColorColor@l
	stw      r0, 0x16c(r1)
	addi     r0, r3, __vt__Q25efx2d17T2DSprayset_forVS@l
	addi     r3, r1, 0x16c
	addi     r4, r1, 0x154
	stw      r11, 0x15c(r1)
	stw      r7, 0x16c(r1)
	stb      r23, 0x20(r1)
	stb      r22, 0x21(r1)
	stb      r21, 0x22(r1)
	stb      r21, 0x23(r1)
	lwz      r9, 0x20(r1)
	stb      r12, 0x24(r1)
	stb      r12, 0x25(r1)
	stb      r21, 0x26(r1)
	stb      r21, 0x27(r1)
	lwz      r7, 0x24(r1)
	stfs     f2, 0x154(r1)
	stfs     f1, 0x158(r1)
	stw      r10, 0x15c(r1)
	stfs     f0, 0x160(r1)
	stw      r9, 0x164(r1)
	stw      r7, 0x168(r1)
	stb      r8, 0x170(r1)
	stb      r8, 0x171(r1)
	sth      r6, 0x174(r1)
	sth      r5, 0x176(r1)
	stw      r8, 0x178(r1)
	stw      r8, 0x17c(r1)
	stw      r0, 0x16c(r1)
	bl       create__Q25efx2d17T2DSprayset_forVSFPQ25efx2d3Arg
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	li       r0, 1
	stw      r0, 0x100(r26)
	lwz      r3, 0xd4(r31)
	bl       up__Q32og6Screen8ScaleMgrFv
	li       r30, 1

lbl_80326670:
	lwz      r3, 0x38(r26)
	lbz      r0, 0x69(r3)
	cmplwi   r0, 0
	beq      lbl_803267E0
	lwz      r0, 0x64(r3)
	cmpw     r0, r28
	bne      lbl_803267E0
	lfs      f2, 0x108(r26)
	lfs      f1, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f2, f1
	ble      lbl_803267E0
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x54(r3)
	fsubs    f0, f2, f0
	stfs     f0, 0x108(r26)
	lfs      f0, 0x108(r26)
	fcmpo    cr0, f0, f1
	cror     2, 0, 2
	bne      lbl_803267E0
	lwz      r3, 0xa4(r31)
	li       r4, 1
	stb      r4, 0xb0(r3)
	lbz      r0, 0x10d(r26)
	cmplwi   r0, 0
	bne      lbl_803267E0
	clrlwi.  r0, r27, 0x18
	stb      r4, 0x10d(r26)
	beq      lbl_803267E0
	lwz      r3, 0xa4(r31)
	addi     r4, r1, 0x78
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	lis      r3, __vt__Q25efx2d7TBaseIF@ha
	li       r11, 0
	addi     r0, r3, __vt__Q25efx2d7TBaseIF@l
	li       r21, 0xff
	lwz      r4, 0x78(r1)
	lis      r3, __vt__Q25efx2d5TBase@ha
	li       r12, 0x87
	lwz      r6, 0x7c(r1)
	stw      r4, 0x48(r1)
	lis      r5, __vt__Q25efx2d3Arg@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	addi     r8, r3, __vt__Q25efx2d5TBase@l
	stw      r0, 0x140(r1)
	addi     r10, r5, __vt__Q25efx2d3Arg@l
	lfs      f2, 0x48(r1)
	lis      r9, __vt__Q25efx2d18ArgScaleColorColor@ha
	stw      r6, 0x4c(r1)
	lis      r3, __vt__Q25efx2d17T2DSprayset_forVS@ha
	lfs      f0, lbl_8051DDA4@sda21(r2)
	li       r6, 0x22
	lfs      f1, 0x4c(r1)
	li       r5, 0x23
	stb      r21, 0x18(r1)
	addi     r7, r4, __vt__Q25efx2d8TSimple2@l
	addi     r9, r9, __vt__Q25efx2d18ArgScaleColorColor@l
	addi     r0, r3, __vt__Q25efx2d17T2DSprayset_forVS@l
	stw      r8, 0x140(r1)
	addi     r3, r1, 0x140
	addi     r4, r1, 0x128
	stw      r10, 0x130(r1)
	stw      r7, 0x140(r1)
	stb      r12, 0x19(r1)
	stb      r12, 0x1a(r1)
	stb      r21, 0x1b(r1)
	lwz      r8, 0x18(r1)
	stb      r21, 0x1c(r1)
	stb      r11, 0x1d(r1)
	stb      r11, 0x1e(r1)
	stb      r21, 0x1f(r1)
	lwz      r7, 0x1c(r1)
	stfs     f2, 0x128(r1)
	stfs     f1, 0x12c(r1)
	stw      r9, 0x130(r1)
	stfs     f0, 0x134(r1)
	stw      r8, 0x138(r1)
	stw      r7, 0x13c(r1)
	stb      r11, 0x144(r1)
	stb      r11, 0x145(r1)
	sth      r6, 0x148(r1)
	sth      r5, 0x14a(r1)
	stw      r11, 0x14c(r1)
	stw      r11, 0x150(r1)
	stw      r0, 0x140(r1)
	bl       create__Q25efx2d17T2DSprayset_forVSFPQ25efx2d3Arg
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	li       r0, 1
	stw      r0, 0x100(r26)
	lwz      r3, 0xe4(r31)
	bl       up__Q32og6Screen8ScaleMgrFv
	li       r29, 1

lbl_803267E0:
	lbz      r0, 0x10c(r26)
	cmplwi   r0, 0
	bne      lbl_80326B90
	lbz      r0, 0x10d(r26)
	cmplwi   r0, 0
	bne      lbl_80326B90
	lwz      r3, 0x38(r26)
	lwz      r0, 0x60(r3)
	cmpw     r0, r28
	ble      lbl_80326984
	lwz      r3, 0x64(r31)
	li       r4, 0
	li       r0, 1
	stb      r4, 0xb0(r3)
	lwz      r3, 0x54(r31)
	stb      r0, 0xb0(r3)
	lwz      r3, 0x54(r31)
	stfs     f30, 0xcc(r3)
	stfs     f30, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	addi     r25, r28, 0xf4
	lbzx     r0, r26, r25
	cmplwi   r0, 0
	bne      lbl_80326978
	cmpwi    r28, 3
	li       r3, 0
	bne      lbl_80326860
	li       r3, 1
	stw      r3, 0x100(r26)

lbl_80326860:
	clrlwi.  r0, r27, 0x18
	stb      r3, 0x104(r26)
	beq      lbl_80326978
	lwz      r0, 0x100(r26)
	lwz      r21, 0x54(r31)
	cmpwi    r0, 1
	beq      lbl_80326970
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	mr       r3, r21
	addi     r4, r1, 0x70
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	lis      r3, __vt__Q25efx2d7TBaseIF@ha
	li       r0, 0
	addi     r12, r3, __vt__Q25efx2d7TBaseIF@l
	li       r8, 0xe7
	lwz      r3, 0x70(r1)
	lis      r9, __vt__Q25efx2d5TBase@ha
	li       r6, 0xff
	li       r5, 0xcf
	lwz      r10, 0x74(r1)
	li       r7, 0x57
	stw      r3, 0x40(r1)
	lis      r3, __vt__Q25efx2d3Arg@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	lfs      f0, lbl_8051DDA4@sda21(r2)
	stw      r10, 0x44(r1)
	addi     r22, r3, __vt__Q25efx2d3Arg@l
	lfs      f2, 0x40(r1)
	lis      r21, __vt__Q25efx2d18ArgScaleColorColor@ha
	lfs      f1, 0x44(r1)
	lis      r3, __vt__Q25efx2d17T2DSprayset_forVS@ha
	li       r11, 0x22
	li       r10, 0x23
	stw      r12, 0x114(r1)
	addi     r9, r9, __vt__Q25efx2d5TBase@l
	addi     r12, r4, __vt__Q25efx2d8TSimple2@l
	addi     r21, r21, __vt__Q25efx2d18ArgScaleColorColor@l
	stw      r9, 0x114(r1)
	addi     r9, r3, __vt__Q25efx2d17T2DSprayset_forVS@l
	addi     r3, r1, 0x114
	addi     r4, r1, 0xfc
	stw      r22, 0x104(r1)
	stw      r12, 0x114(r1)
	stb      r8, 0x10(r1)
	stb      r8, 0x11(r1)
	stb      r7, 0x12(r1)
	stb      r6, 0x13(r1)
	lwz      r7, 0x10(r1)
	stb      r5, 0x14(r1)
	stb      r5, 0x15(r1)
	stb      r0, 0x16(r1)
	stb      r6, 0x17(r1)
	lwz      r5, 0x14(r1)
	stfs     f2, 0xfc(r1)
	stfs     f1, 0x100(r1)
	stw      r21, 0x104(r1)
	stfs     f0, 0x108(r1)
	stw      r7, 0x10c(r1)
	stw      r5, 0x110(r1)
	stb      r0, 0x118(r1)
	stb      r0, 0x119(r1)
	sth      r11, 0x11c(r1)
	sth      r10, 0x11e(r1)
	stw      r0, 0x120(r1)
	stw      r0, 0x124(r1)
	stw      r9, 0x114(r1)
	bl       create__Q25efx2d17T2DSprayset_forVSFPQ25efx2d3Arg

lbl_80326970:
	lwz      r3, 0xb4(r31)
	bl       up__Q32og6Screen8ScaleMgrFv

lbl_80326978:
	li       r0, 1
	stbx     r0, r26, r25
	b        lbl_803269C4

lbl_80326984:
	lwz      r3, 0x54(r31)
	li       r4, 0
	li       r0, 1
	stb      r4, 0xb0(r3)
	lwz      r3, 0x64(r31)
	stb      r0, 0xb0(r3)
	lwz      r3, 0x64(r31)
	stfs     f30, 0xcc(r3)
	stfs     f30, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	addi     r0, r28, 0xf4
	li       r3, 0
	stbx     r3, r26, r0

lbl_803269C4:
	lwz      r3, 0x38(r26)
	lwz      r0, 0x64(r3)
	cmpw     r0, r28
	ble      lbl_80326B50
	lwz      r3, 0x94(r31)
	li       r4, 0
	li       r0, 1
	stb      r4, 0xb0(r3)
	lwz      r3, 0x84(r31)
	stb      r0, 0xb0(r3)
	lwz      r3, 0x84(r31)
	stfs     f31, 0xcc(r3)
	stfs     f31, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	addi     r25, r28, 0xf8
	lbzx     r0, r26, r25
	cmplwi   r0, 0
	bne      lbl_80326B44
	cmpwi    r28, 3
	li       r3, 0
	bne      lbl_80326A2C
	li       r3, 1
	stw      r3, 0x100(r26)

lbl_80326A2C:
	clrlwi.  r0, r27, 0x18
	stb      r3, 0x105(r26)
	beq      lbl_80326B44
	lwz      r0, 0x100(r26)
	lwz      r21, 0x84(r31)
	cmpwi    r0, 1
	beq      lbl_80326B3C
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	mr       r3, r21
	addi     r4, r1, 0x68
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	lis      r3, __vt__Q25efx2d7TBaseIF@ha
	li       r0, 0
	addi     r12, r3, __vt__Q25efx2d7TBaseIF@l
	li       r8, 0xe7
	lwz      r3, 0x68(r1)
	lis      r9, __vt__Q25efx2d5TBase@ha
	li       r6, 0xff
	li       r5, 0xcf
	lwz      r10, 0x6c(r1)
	li       r7, 0x57
	stw      r3, 0x38(r1)
	lis      r3, __vt__Q25efx2d3Arg@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	lfs      f0, lbl_8051DDA4@sda21(r2)
	stw      r10, 0x3c(r1)
	addi     r22, r3, __vt__Q25efx2d3Arg@l
	lfs      f2, 0x38(r1)
	lis      r21, __vt__Q25efx2d18ArgScaleColorColor@ha
	lfs      f1, 0x3c(r1)
	lis      r3, __vt__Q25efx2d17T2DSprayset_forVS@ha
	li       r11, 0x22
	li       r10, 0x23
	stw      r12, 0xe8(r1)
	addi     r9, r9, __vt__Q25efx2d5TBase@l
	addi     r12, r4, __vt__Q25efx2d8TSimple2@l
	addi     r21, r21, __vt__Q25efx2d18ArgScaleColorColor@l
	stw      r9, 0xe8(r1)
	addi     r9, r3, __vt__Q25efx2d17T2DSprayset_forVS@l
	addi     r3, r1, 0xe8
	addi     r4, r1, 0xd0
	stw      r22, 0xd8(r1)
	stw      r12, 0xe8(r1)
	stb      r8, 8(r1)
	stb      r8, 9(r1)
	stb      r7, 0xa(r1)
	stb      r6, 0xb(r1)
	lwz      r7, 8(r1)
	stb      r5, 0xc(r1)
	stb      r5, 0xd(r1)
	stb      r0, 0xe(r1)
	stb      r6, 0xf(r1)
	lwz      r5, 0xc(r1)
	stfs     f2, 0xd0(r1)
	stfs     f1, 0xd4(r1)
	stw      r21, 0xd8(r1)
	stfs     f0, 0xdc(r1)
	stw      r7, 0xe0(r1)
	stw      r5, 0xe4(r1)
	stb      r0, 0xec(r1)
	stb      r0, 0xed(r1)
	sth      r11, 0xf0(r1)
	sth      r10, 0xf2(r1)
	stw      r0, 0xf4(r1)
	stw      r0, 0xf8(r1)
	stw      r9, 0xe8(r1)
	bl       create__Q25efx2d17T2DSprayset_forVSFPQ25efx2d3Arg

lbl_80326B3C:
	lwz      r3, 0xc4(r31)
	bl       up__Q32og6Screen8ScaleMgrFv

lbl_80326B44:
	li       r0, 1
	stbx     r0, r26, r25
	b        lbl_80326B90

lbl_80326B50:
	lwz      r3, 0x84(r31)
	li       r4, 0
	li       r0, 1
	stb      r4, 0xb0(r3)
	lwz      r3, 0x94(r31)
	stb      r0, 0xb0(r3)
	lwz      r3, 0x94(r31)
	stfs     f31, 0xcc(r3)
	stfs     f31, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	addi     r0, r28, 0xf8
	li       r3, 0
	stbx     r3, r26, r0

lbl_80326B90:
	addi     r28, r28, 1
	addi     r31, r31, 4
	cmpwi    r28, 4
	blt      lbl_80326490
	lbz      r0, 0x104(r26)
	cmplwi   r0, 0
	beq      lbl_80326CBC
	lfs      f2, 0x108(r26)
	lfs      f1, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f2, f1
	ble      lbl_80326CBC
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x54(r3)
	fsubs    f0, f2, f0
	stfs     f0, 0x108(r26)
	lfs      f0, 0x108(r26)
	fcmpo    cr0, f0, f1
	cror     2, 0, 2
	bne      lbl_80326CBC
	clrlwi.  r0, r27, 0x18
	beq      lbl_80326CBC
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	lis      r8, __vt__Q25efx2d3Arg@ha
	lis      r7, __vt__Q25efx2d8ArgScale@ha
	lis      r6, __vt__Q25efx2d7TBaseIF@ha
	lis      r5, __vt__Q25efx2d5TBase@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	lis      r3, __vt__Q25efx2d18T2DSensorGet_forVS@ha
	lfs      f30, lbl_8051DDB8@sda21(r2)
	mr       r25, r26
	addi     r31, r8, __vt__Q25efx2d3Arg@l
	addi     r28, r7, __vt__Q25efx2d8ArgScale@l
	addi     r21, r6, __vt__Q25efx2d7TBaseIF@l
	addi     r24, r5, __vt__Q25efx2d5TBase@l
	addi     r23, r4, __vt__Q25efx2d8TSimple2@l
	addi     r22, r3, __vt__Q25efx2d18T2DSensorGet_forVS@l
	li       r20, 0

lbl_80326C28:
	lwz      r3, 0xb4(r25)
	bl       up__Q32og6Screen8ScaleMgrFv
	lwz      r3, 0x54(r25)
	addi     r4, r1, 0x60
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	stw      r21, 0xbc(r1)
	li       r6, 0
	lwz      r3, 0x60(r1)
	li       r5, 0x1a
	lwz      r7, 0x64(r1)
	li       r0, 0x1b
	stw      r3, 0x30(r1)
	addi     r3, r1, 0xbc
	addi     r4, r1, 0x98
	stw      r7, 0x34(r1)
	lfs      f1, 0x30(r1)
	stw      r24, 0xbc(r1)
	lfs      f0, 0x34(r1)
	stw      r31, 0xa0(r1)
	stw      r23, 0xbc(r1)
	stfs     f1, 0x98(r1)
	stfs     f0, 0x9c(r1)
	stw      r28, 0xa0(r1)
	stfs     f30, 0xa4(r1)
	stb      r6, 0xc0(r1)
	stb      r6, 0xc1(r1)
	sth      r5, 0xc4(r1)
	sth      r0, 0xc6(r1)
	stw      r6, 0xc8(r1)
	stw      r6, 0xcc(r1)
	stw      r22, 0xbc(r1)
	bl       create__Q25efx2d18T2DSensorGet_forVSFPQ25efx2d3Arg
	addi     r20, r20, 1
	li       r30, 1
	cmpwi    r20, 4
	addi     r25, r25, 4
	blt      lbl_80326C28

lbl_80326CBC:
	lbz      r0, 0x105(r26)
	cmplwi   r0, 0
	beq      lbl_80326DD8
	lfs      f2, 0x108(r26)
	lfs      f1, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f2, f1
	ble      lbl_80326DD8
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x54(r3)
	fsubs    f0, f2, f0
	stfs     f0, 0x108(r26)
	lfs      f0, 0x108(r26)
	fcmpo    cr0, f0, f1
	cror     2, 0, 2
	bne      lbl_80326DD8
	clrlwi.  r0, r27, 0x18
	beq      lbl_80326DD8
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setBdamaGet__Q22og5SoundFv
	lis      r8, __vt__Q25efx2d3Arg@ha
	lis      r7, __vt__Q25efx2d8ArgScale@ha
	lis      r6, __vt__Q25efx2d7TBaseIF@ha
	lis      r5, __vt__Q25efx2d5TBase@ha
	lis      r4, __vt__Q25efx2d8TSimple2@ha
	lis      r3, __vt__Q25efx2d18T2DSensorGet_forVS@ha
	lfs      f30, lbl_8051DDB8@sda21(r2)
	mr       r25, r26
	addi     r27, r8, __vt__Q25efx2d3Arg@l
	addi     r22, r7, __vt__Q25efx2d8ArgScale@l
	addi     r23, r6, __vt__Q25efx2d7TBaseIF@l
	addi     r24, r5, __vt__Q25efx2d5TBase@l
	addi     r31, r4, __vt__Q25efx2d8TSimple2@l
	addi     r28, r3, __vt__Q25efx2d18T2DSensorGet_forVS@l
	li       r20, 0

lbl_80326D44:
	lwz      r3, 0xc4(r25)
	bl       up__Q32og6Screen8ScaleMgrFv
	lwz      r3, 0x84(r25)
	addi     r4, r1, 0x58
	bl       "calcGlbCenter__Q22og6ScreenFP7J2DPaneP10Vector2<f>"
	stw      r23, 0xa8(r1)
	li       r6, 0
	lwz      r3, 0x58(r1)
	li       r5, 0x1a
	lwz      r7, 0x5c(r1)
	li       r0, 0x1b
	stw      r3, 0x28(r1)
	addi     r3, r1, 0xa8
	addi     r4, r1, 0x88
	stw      r7, 0x2c(r1)
	lfs      f1, 0x28(r1)
	stw      r24, 0xa8(r1)
	lfs      f0, 0x2c(r1)
	stw      r27, 0x90(r1)
	stw      r31, 0xa8(r1)
	stfs     f1, 0x88(r1)
	stfs     f0, 0x8c(r1)
	stw      r22, 0x90(r1)
	stfs     f30, 0x94(r1)
	stb      r6, 0xac(r1)
	stb      r6, 0xad(r1)
	sth      r5, 0xb0(r1)
	sth      r0, 0xb2(r1)
	stw      r6, 0xb4(r1)
	stw      r6, 0xb8(r1)
	stw      r28, 0xa8(r1)
	bl       create__Q25efx2d18T2DSensorGet_forVSFPQ25efx2d3Arg
	addi     r20, r20, 1
	li       r29, 1
	cmpwi    r20, 4
	addi     r25, r25, 4
	blt      lbl_80326D44

lbl_80326DD8:
	lbz      r0, 0x128(r26)
	cmplwi   r0, 0
	bne      lbl_80326E3C
	clrlwi.  r0, r30, 0x18
	beq      lbl_80326E08
	clrlwi.  r0, r29, 0x18
	beq      lbl_80326E08
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setVsDraw__Q22og5SoundFv
	li       r0, 1
	stb      r0, 0x128(r26)
	b        lbl_80326E3C

lbl_80326E08:
	clrlwi.  r0, r30, 0x18
	beq      lbl_80326E24
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setVsWin1P__Q22og5SoundFv
	li       r0, 1
	stb      r0, 0x128(r26)
	b        lbl_80326E3C

lbl_80326E24:
	clrlwi.  r0, r29, 0x18
	beq      lbl_80326E3C
	lwz      r3, ogSound__2og@sda21(r13)
	bl       setVsWin2P__Q22og5SoundFv
	li       r0, 1
	stb      r0, 0x128(r26)

lbl_80326E3C:
	psq_l    f31, 488(r1), 0, qr0
	lfd      f31, 0x1e0(r1)
	psq_l    f30, 472(r1), 0, qr0
	lfd      f30, 0x1d0(r1)
	psq_l    f29, 456(r1), 0, qr0
	lfd      f29, 0x1c0(r1)
	psq_l    f28, 440(r1), 0, qr0
	lfd      f28, 0x1b0(r1)
	lmw      r20, 0x180(r1)
	lwz      r0, 0x1f4(r1)
	mtlr     r0
	addi     r1, r1, 0x1f0
	blr
	*/
}

/**
 * @note Address: 0x80326E70
 * @note Size: 0x2B8
 */
void ObjVs::ScreenSet::init(og::Screen::DataNavi* data, JKRArchive* arc, u32* pikis)
{
	og::Screen::CallBack_CatchPiki* cpiki = new og::Screen::CallBack_CatchPiki;
	cpiki->init(mScreen, 'piki', &data->mNextThrowPiki, arc);
	mScreen->addCallBack('piki', cpiki);

	og::Screen::setCallBack_CounterRV(mScreen, 'c_mr', 'c_ml', 'c_ml', &data->mFollowPikis, 3, 2, 1, arc);

	og::Screen::CallBack_CounterRV* counter = og::Screen::setCallBack_CounterRV(mScreen, 'c_lr', 'c_ll', 'c_ll', pikis, 3, 2, 1, arc);
	counter->mScaleUpSoundID                = PSSE_SY_PIKI_INCREMENT;
	counter->mScaleDownSoundID              = PSSE_SY_PIKI_DECREMENT;

	counter = og::Screen::setCallBack_CounterRV(mScreen, 'dr_r', 'dr_l', 'dr_l', &data->mDope1Count, 3, 2, 1, arc);
	counter->setCenteringMode(og::Screen::CallBack_CounterRV::ECM_Unknown1);
	mScreen->search('dr_c')->hide();

	counter = og::Screen::setCallBack_CounterRV(mScreen, 'dy_r', 'dy_l', 'dy_l', &data->mDope0Count, 3, 2, 1, arc);
	counter->setCenteringMode(og::Screen::CallBack_CounterRV::ECM_Unknown1);
	mScreen->search('dy_c')->hide();

	mPaneToyo01 = og::Screen::TagSearch(mScreen, 'toyo_01');
	mPaneToyo00 = og::Screen::TagSearch(mScreen, 'toyo_00');
	mDoping->init(mPaneToyo01, mPaneToyo00, mScaleMgr1, mScaleMgr2);
	mLifeGauge->init(mScreen, data, og::Screen::CallBack_LifeGauge::LIFEGAUGE_OLIMAR);
	mScreen->addCallBack('back', mLifeGauge);
	mLifeGauge->setOffset(msVal.mLifeGaugeXOffs, msVal.mLifeGaugeYOffs);
	og::Screen::setCallBack_DrawAfter(mScreen, 'mete');

	/*
	.loc_0x0:
	  stwu      r1, -0x40(r1)
	  mflr      r0
	  stw       r0, 0x44(r1)
	  stmw      r27, 0x2C(r1)
	  mr        r29, r3
	  mr        r30, r4
	  mr        r31, r5
	  mr        r27, r6
	  li        r3, 0x44
	  bl        -0x302FF0
	  mr.       r28, r3
	  beq-      .loc_0x38
	  bl        -0x1F680
	  mr        r28, r3

	.loc_0x38:
	  lis       r5, 0x7069
	  lwz       r4, 0x0(r29)
	  mr        r3, r28
	  mr        r8, r31
	  addi      r6, r5, 0x6B69
	  addi      r7, r30, 0x8
	  li        r5, 0
	  bl        -0x1F5E8
	  lis       r4, 0x7069
	  lwz       r3, 0x0(r29)
	  mr        r7, r28
	  li        r5, 0
	  addi      r6, r4, 0x6B69
	  bl        0x10DC48
	  addi      r0, r30, 0x4
	  lis       r3, 0x635F
	  stw       r0, 0x8(r1)
	  li        r0, 0x3
	  addi      r8, r3, 0x6D6C
	  li        r4, 0x2
	  stw       r0, 0xC(r1)
	  li        r0, 0x1
	  mr        r10, r8
	  addi      r6, r3, 0x6D72
	  stw       r4, 0x10(r1)
	  li        r5, 0
	  li        r7, 0
	  li        r9, 0
	  stw       r0, 0x14(r1)
	  stw       r31, 0x18(r1)
	  lwz       r3, 0x0(r29)
	  bl        -0x1A9F4
	  stw       r27, 0x8(r1)
	  lis       r3, 0x635F
	  li        r0, 0x3
	  li        r4, 0x2
	  stw       r0, 0xC(r1)
	  addi      r8, r3, 0x6C6C
	  li        r0, 0x1
	  addi      r6, r3, 0x6C72
	  stw       r4, 0x10(r1)
	  mr        r10, r8
	  li        r5, 0
	  li        r7, 0
	  stw       r0, 0x14(r1)
	  li        r9, 0
	  stw       r31, 0x18(r1)
	  lwz       r3, 0x0(r29)
	  bl        -0x1AA38
	  li        r0, 0x1828
	  lis       r4, 0x6472
	  stw       r0, 0x94(r3)
	  li        r0, 0x182A
	  addi      r8, r4, 0x5F6C
	  addi      r5, r30, 0xC
	  stw       r0, 0x98(r3)
	  li        r7, 0x3
	  li        r3, 0x2
	  li        r0, 0x1
	  stw       r5, 0x8(r1)
	  mr        r10, r8
	  addi      r6, r4, 0x5F72
	  li        r5, 0
	  stw       r7, 0xC(r1)
	  li        r7, 0
	  li        r9, 0
	  stw       r3, 0x10(r1)
	  stw       r0, 0x14(r1)
	  stw       r31, 0x18(r1)
	  lwz       r3, 0x0(r29)
	  bl        -0x1AA90
	  li        r4, 0x1
	  bl        -0x1B6EC
	  lwz       r3, 0x0(r29)
	  lis       r4, 0x6472
	  addi      r6, r4, 0x5F63
	  li        r5, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x3C(r12)
	  mtctr     r12
	  bctrl
	  li        r0, 0
	  lis       r4, 0x6479
	  stb       r0, 0xB0(r3)
	  addi      r0, r30, 0x10
	  addi      r8, r4, 0x5F6C
	  li        r5, 0x3
	  stw       r0, 0x8(r1)
	  li        r3, 0x2
	  li        r0, 0x1
	  mr        r10, r8
	  stw       r5, 0xC(r1)
	  addi      r6, r4, 0x5F72
	  li        r5, 0
	  li        r7, 0
	  stw       r3, 0x10(r1)
	  li        r9, 0
	  stw       r0, 0x14(r1)
	  stw       r31, 0x18(r1)
	  lwz       r3, 0x0(r29)
	  bl        -0x1AB08
	  li        r4, 0x1
	  bl        -0x1B764
	  lwz       r3, 0x0(r29)
	  lis       r4, 0x6479
	  addi      r6, r4, 0x5F63
	  li        r5, 0
	  lwz       r12, 0x0(r3)
	  lwz       r12, 0x3C(r12)
	  mtctr     r12
	  bctrl
	  li        r0, 0
	  lis       r5, 0x6F5F
	  stb       r0, 0xB0(r3)
	  lis       r4, 0x74
	  addi      r6, r5, 0x3031
	  lwz       r3, 0x0(r29)
	  addi      r5, r4, 0x6F79
	  bl        -0x241D4
	  stw       r3, 0x14(r29)
	  lis       r5, 0x6F5F
	  lis       r4, 0x74
	  lwz       r3, 0x0(r29)
	  addi      r6, r5, 0x3030
	  addi      r5, r4, 0x6F79
	  bl        -0x241F0
	  stw       r3, 0x18(r29)
	  lwz       r3, 0x8(r29)
	  lwz       r4, 0x14(r29)
	  lwz       r5, 0x18(r29)
	  lwz       r6, 0xC(r29)
	  lwz       r7, 0x10(r29)
	  bl        -0x232B4
	  lwz       r3, 0x4(r29)
	  mr        r5, r30
	  lwz       r4, 0x0(r29)
	  li        r6, 0
	  bl        -0x20ECC
	  lis       r4, 0x6261
	  lwz       r3, 0x0(r29)
	  lwz       r7, 0x4(r29)
	  addi      r6, r4, 0x636B
	  li        r5, 0
	  bl        0x10DA40
	  lis       r4, 0x8051
	  lwz       r3, 0x4(r29)
	  addi      r4, r4, 0x3F40
	  lfs       f1, 0x8(r4)
	  lfs       f2, 0xC(r4)
	  bl        -0x20804
	  lis       r4, 0x6D65
	  lwz       r3, 0x0(r29)
	  addi      r6, r4, 0x7465
	  li        r5, 0
	  bl        0x6674
	  lmw       r27, 0x2C(r1)
	  lwz       r0, 0x44(r1)
	  mtlr      r0
	  addi      r1, r1, 0x40
	  blr
	*/
}

/**
 * @note Address: N/A
 * @note Size: 0xEC
 */
void ObjVs::ScreenSet::update(og::Screen::DataNavi& data)
{
	f32 scale1 = mScaleMgr1->calc();
	f32 scale2 = mScaleMgr2->calc();
	if (mPaneToyo01)
		mPaneToyo01->updateScale(scale1);
	if (mPaneToyo00)
		mPaneToyo00->updateScale(scale2);

	og::Screen::DopingCheck* dope = mDoping;
	dope->mNaviLifeRatio          = data.mNaviLifeRatio;
	dope->mFollowPiki             = data.mFollowPikis;
	dope->mNextThrowPiki          = data.mNextThrowPiki;
	dope->mSpicySprayCount        = data.mDope1Count;
	dope->mBitterSprayCount       = data.mDope0Count;
	dope->mActiveNaviID           = data.mActiveNaviID;
	dope->update();
}

/**
 * @note Address: 0x80327128
 * @note Size: 0x56C
 */
void ObjVs::checkObake()
{
	if (mObakeEnabledP1) {
		mAlphaObakeP1 += sys->mDeltaTime;
		if (mAlphaObakeP1 > 1.0f)
			mAlphaObakeP1 = 1.0f;

		if (mDisp->mGhostIconTimerP1 <= 0.0f) {
			mObakeEnabledP1 = false;
		}
	} else {
		mAlphaObakeP1 -= sys->mDeltaTime;
		if (mAlphaObakeP1 < 0.0f)
			mAlphaObakeP1 = 0.0f;

		if (mDisp->mFlags[2]) {
			mObakeEnabledP1 = true;
		}
	}

	if (mObakeEnabledP2) {
		mAlphaObakeP2 += sys->mDeltaTime;
		if (mAlphaObakeP2 > 1.0f)
			mAlphaObakeP2 = 1.0f;

		if (mDisp->mGhostIconTimerP2 <= 0.0f) {
			mObakeEnabledP2 = false;
		}
	} else {
		mAlphaObakeP2 -= sys->mDeltaTime;
		if (mAlphaObakeP2 < 0.0f)
			mAlphaObakeP2 = 0.0f;

		if (mDisp->mFlags[3]) {
			mObakeEnabledP2 = true;
		}
	}

	f32 calc = mObakeMovePos * 2.0f;
	calc     = (sinf(calc) + 1.0f) * 0.5f;

	f32 mod1 = 1.0f;
	f32 mod2 = 1.0f;
	f32 angle1, angle2;
	if (mObakeEnabledP1) {
		f32 temp = mDisp->mGhostIconTimerP1;
		angle1   = 1.0f;
		if (temp <= 10.0f) {
			angle1 = temp / 10.0f;
			mod1   = calc * 0.6f + 0.4f;
		}
	} else {
		angle1 = 0.0f;
	}

	if (mObakeEnabledP2) {
		f32 temp = mDisp->mGhostIconTimerP2;
		angle2   = 1.0f;
		if (temp <= 10.0f) {
			angle2 = temp / 10.0f;
			mod2   = calc * 0.6f + 0.4f;
		}
	} else {
		angle2 = 0.0f;
	}

	mPaneObake1P->setAlpha(mAlphaObakeP1 * 255.0f * mod1);
	mPaneObake2P->setAlpha(mAlphaObakeP2 * 255.0f * mod2);

	mObakeMovePos += sys->mDeltaTime * TAU;
	if (mObakeMovePos > TAU) {
		mObakeMovePos -= TAU;
	}
	f32 sin = sinf(mObakeMovePos);
	f32 cos = -sinf(mObakeMovePos);
	mPaneObake1P->rotate(angle1 * sin * 20.0f);
	mPaneObake2P->rotate(angle2 * cos * 20.0f);

	cos = cosf(mObakeMovePos);

	mPaneObake1P->setOffset(msVal.mRouletteXOffs + (sin * angle1) * msVal.mRouletteXSpeed,
	                        msVal.mRouletteP1YOffs + (cos * angle1) * msVal.mRouletteYSpeed);
	mPaneObake2P->setOffset(msVal.mRouletteXOffs + (sin * angle2) * msVal.mRouletteXSpeed,
	                        msVal.mRouletteP2YOffs + (cos * angle2) * msVal.mRouletteYSpeed);

	mPaneObake1P->updateScale(msVal.mRouletteScale);
	mPaneObake2P->updateScale(msVal.mRouletteScale);

	/*
	stwu     r1, -0xa0(r1)
	mflr     r0
	stw      r0, 0xa4(r1)
	stfd     f31, 0x90(r1)
	psq_st   f31, 152(r1), 0, qr0
	stfd     f30, 0x80(r1)
	psq_st   f30, 136(r1), 0, qr0
	stfd     f29, 0x70(r1)
	psq_st   f29, 120(r1), 0, qr0
	stfd     f28, 0x60(r1)
	psq_st   f28, 104(r1), 0, qr0
	stfd     f27, 0x50(r1)
	psq_st   f27, 88(r1), 0, qr0
	stw      r31, 0x4c(r1)
	mr       r31, r3
	lbz      r0, 0x120(r3)
	cmplwi   r0, 0
	beq      lbl_803271BC
	lwz      r3, sys@sda21(r13)
	lfs      f2, 0x118(r31)
	lfs      f1, 0x54(r3)
	lfs      f0, lbl_8051DDA4@sda21(r2)
	fadds    f1, f2, f1
	stfs     f1, 0x118(r31)
	lfs      f1, 0x118(r31)
	fcmpo    cr0, f1, f0
	ble      lbl_80327198
	stfs     f0, 0x118(r31)

lbl_80327198:
	lwz      r3, 0x38(r31)
	lfs      f0, lbl_8051DD98@sda21(r2)
	lfs      f1, 0x6c(r3)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_803271FC
	li       r0, 0
	stb      r0, 0x120(r31)
	b        lbl_803271FC

lbl_803271BC:
	lwz      r3, sys@sda21(r13)
	lfs      f2, 0x118(r31)
	lfs      f1, 0x54(r3)
	lfs      f0, lbl_8051DD98@sda21(r2)
	fsubs    f1, f2, f1
	stfs     f1, 0x118(r31)
	lfs      f1, 0x118(r31)
	fcmpo    cr0, f1, f0
	bge      lbl_803271E4
	stfs     f0, 0x118(r31)

lbl_803271E4:
	lwz      r3, 0x38(r31)
	lbz      r0, 0x6a(r3)
	cmplwi   r0, 0
	beq      lbl_803271FC
	li       r0, 1
	stb      r0, 0x120(r31)

lbl_803271FC:
	lbz      r0, 0x121(r31)
	cmplwi   r0, 0
	beq      lbl_80327254
	lwz      r3, sys@sda21(r13)
	lfs      f2, 0x11c(r31)
	lfs      f1, 0x54(r3)
	lfs      f0, lbl_8051DDA4@sda21(r2)
	fadds    f1, f2, f1
	stfs     f1, 0x11c(r31)
	lfs      f1, 0x11c(r31)
	fcmpo    cr0, f1, f0
	ble      lbl_80327230
	stfs     f0, 0x11c(r31)

lbl_80327230:
	lwz      r3, 0x38(r31)
	lfs      f0, lbl_8051DD98@sda21(r2)
	lfs      f1, 0x70(r3)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_80327294
	li       r0, 0
	stb      r0, 0x121(r31)
	b        lbl_80327294

lbl_80327254:
	lwz      r3, sys@sda21(r13)
	lfs      f2, 0x11c(r31)
	lfs      f1, 0x54(r3)
	lfs      f0, lbl_8051DD98@sda21(r2)
	fsubs    f1, f2, f1
	stfs     f1, 0x11c(r31)
	lfs      f1, 0x11c(r31)
	fcmpo    cr0, f1, f0
	bge      lbl_8032727C
	stfs     f0, 0x11c(r31)

lbl_8032727C:
	lwz      r3, 0x38(r31)
	lbz      r0, 0x6b(r3)
	cmplwi   r0, 0
	beq      lbl_80327294
	li       r0, 1
	stb      r0, 0x121(r31)

lbl_80327294:
	lfs      f1, lbl_8051DDBC@sda21(r2)
	lfs      f0, 0x124(r31)
	lfs      f31, lbl_8051DDA4@sda21(r2)
	fmuls    f1, f1, f0
	lfs      f0, lbl_8051DD98@sda21(r2)
	fmr      f30, f31
	fmr      f2, f31
	fmr      f29, f31
	fcmpo    cr0, f1, f0
	bge      lbl_803272E8
	lfs      f0, lbl_8051DDC0@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 8(r1)
	lwz      r0, 0xc(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_8032730C

lbl_803272E8:
	lfs      f0, lbl_8051DDC4@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x10(r1)
	lwz      r0, 0x14(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_8032730C:
	fadds    f1, f31, f0
	lfs      f0, lbl_8051DDC8@sda21(r2)
	lbz      r0, 0x120(r31)
	cmplwi   r0, 0
	fmuls    f3, f1, f0
	beq      lbl_80327350
	lwz      r3, 0x38(r31)
	lfs      f0, lbl_8051DDCC@sda21(r2)
	lfs      f1, 0x6c(r3)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_80327354
	fdivs    f31, f1, f0
	lfs      f1, lbl_8051DDB8@sda21(r2)
	lfs      f0, lbl_8051DDD0@sda21(r2)
	fmadds   f2, f1, f3, f0
	b        lbl_80327354

lbl_80327350:
	lfs      f31, lbl_8051DD98@sda21(r2)

lbl_80327354:
	lbz      r0, 0x121(r31)
	cmplwi   r0, 0
	beq      lbl_8032738C
	lwz      r3, 0x38(r31)
	lfs      f0, lbl_8051DDCC@sda21(r2)
	lfs      f1, 0x70(r3)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_80327390
	fdivs    f30, f1, f0
	lfs      f1, lbl_8051DDB8@sda21(r2)
	lfs      f0, lbl_8051DDD0@sda21(r2)
	fmadds   f29, f1, f3, f0
	b        lbl_80327390

lbl_8032738C:
	lfs      f30, lbl_8051DD98@sda21(r2)

lbl_80327390:
	lfs      f1, lbl_8051DDAC@sda21(r2)
	lfs      f0, 0x118(r31)
	lwz      r3, 0x110(r31)
	fmuls    f0, f1, f0
	lwz      r12, 0(r3)
	fmuls    f0, f0, f2
	lwz      r12, 0x24(r12)
	fctiwz   f0, f0
	stfd     f0, 0x10(r1)
	lwz      r4, 0x14(r1)
	mtctr    r12
	bctrl
	lfs      f1, lbl_8051DDAC@sda21(r2)
	lfs      f0, 0x11c(r31)
	lwz      r3, 0x114(r31)
	fmuls    f0, f1, f0
	lwz      r12, 0(r3)
	fmuls    f0, f0, f29
	lwz      r12, 0x24(r12)
	fctiwz   f0, f0
	stfd     f0, 8(r1)
	lwz      r4, 0xc(r1)
	mtctr    r12
	bctrl
	lwz      r3, sys@sda21(r13)
	lfs      f2, lbl_8051DDD4@sda21(r2)
	lfs      f1, 0x54(r3)
	lfs      f0, 0x124(r31)
	fmadds   f0, f2, f1, f0
	stfs     f0, 0x124(r31)
	lfs      f0, 0x124(r31)
	fcmpo    cr0, f0, f2
	ble      lbl_8032741C
	fsubs    f0, f0, f2
	stfs     f0, 0x124(r31)

lbl_8032741C:
	lfs      f2, 0x124(r31)
	lfs      f0, lbl_8051DD98@sda21(r2)
	lfs      f1, lbl_8051DDD8@sda21(r2)
	fcmpo    cr0, f2, f0
	bge      lbl_8032745C
	lfs      f0, lbl_8051DDC0@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 0x10(r1)
	lwz      r0, 0x14(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f0, f0
	b        lbl_80327480

lbl_8032745C:
	lfs      f0, lbl_8051DDC4@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 8(r1)
	lwz      r0, 0xc(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0

lbl_80327480:
	fmuls    f1, f1, f0
	lfs      f0, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f2, f0
	fmuls    f1, f31, f1
	bge      lbl_803274C0
	lfs      f0, lbl_8051DDC0@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 0x18(r1)
	lwz      r0, 0x1c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f29, f0
	b        lbl_803274E4

lbl_803274C0:
	lfs      f0, lbl_8051DDC4@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f2, f0
	fctiwz   f0, f0
	stfd     f0, 0x20(r1)
	lwz      r0, 0x24(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f29, r3, r0

lbl_803274E4:
	lwz      r3, 0x110(r31)
	bl       rotate__7J2DPaneFf
	lfs      f0, lbl_8051DDD8@sda21(r2)
	lwz      r3, 0x114(r31)
	fmuls    f0, f0, f29
	fmuls    f1, f30, f0
	bl       rotate__7J2DPaneFf
	lfs      f2, 0x124(r31)
	lfs      f0, lbl_8051DD98@sda21(r2)
	fmr      f1, f2
	fcmpo    cr0, f2, f0
	bge      lbl_80327518
	fneg     f1, f2

lbl_80327518:
	lfs      f3, lbl_8051DDC4@sda21(r2)
	lis      r4, msVal__Q32og9newScreen5ObjVs@ha
	lfs      f0, lbl_8051DDBC@sda21(r2)
	addi     r5, r4, msVal__Q32og9newScreen5ObjVs@l
	fmuls    f1, f1, f3
	lis      r3, sincosTable___5JMath@ha
	fmuls    f5, f0, f2
	lfs      f0, lbl_8051DD98@sda21(r2)
	addi     r4, r3, sincosTable___5JMath@l
	lfs      f4, 0x2c(r5)
	fctiwz   f2, f1
	lfs      f1, 0x30(r5)
	fcmpo    cr0, f5, f0
	stfd     f2, 0x28(r1)
	lwz      r0, 0x2c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r4, r0
	lfs      f0, 4(r3)
	fmuls    f29, f4, f0
	bge      lbl_8032758C
	lfs      f0, lbl_8051DDC0@sda21(r2)
	fmuls    f0, f5, f0
	fctiwz   f0, f0
	stfd     f0, 0x30(r1)
	lwz      r0, 0x34(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0
	fneg     f0, f0
	b        lbl_803275A4

lbl_8032758C:
	fmuls    f0, f5, f3
	fctiwz   f0, f0
	stfd     f0, 0x38(r1)
	lwz      r0, 0x3c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r4, r0

lbl_803275A4:
	fmuls    f28, f1, f0
	lis      r3, msVal__Q32og9newScreen5ObjVs@ha
	addi     r4, r3, msVal__Q32og9newScreen5ObjVs@l
	fmuls    f1, f29, f31
	lfs      f27, 0x1c(r4)
	fmuls    f0, f28, f31
	lfs      f2, 0x20(r4)
	fadds    f1, f27, f1
	lwz      r3, 0x110(r31)
	lfs      f31, 0x24(r4)
	fadds    f0, f2, f0
	stfs     f1, 0xd4(r3)
	stfs     f0, 0xd8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	fmuls    f1, f29, f30
	lwz      r3, 0x114(r31)
	fmuls    f0, f28, f30
	fadds    f1, f27, f1
	fadds    f0, f31, f0
	stfs     f1, 0xd4(r3)
	stfs     f0, 0xd8(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	lis      r4, msVal__Q32og9newScreen5ObjVs@ha
	lwz      r3, 0x110(r31)
	addi     r4, r4, msVal__Q32og9newScreen5ObjVs@l
	lfs      f27, 0x28(r4)
	stfs     f27, 0xcc(r3)
	stfs     f27, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	lwz      r3, 0x114(r31)
	stfs     f27, 0xcc(r3)
	stfs     f27, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl
	psq_l    f31, 152(r1), 0, qr0
	lfd      f31, 0x90(r1)
	psq_l    f30, 136(r1), 0, qr0
	lfd      f30, 0x80(r1)
	psq_l    f29, 120(r1), 0, qr0
	lfd      f29, 0x70(r1)
	psq_l    f28, 104(r1), 0, qr0
	lfd      f28, 0x60(r1)
	psq_l    f27, 88(r1), 0, qr0
	lfd      f27, 0x50(r1)
	lwz      r0, 0xa4(r1)
	lwz      r31, 0x4c(r1)
	mtlr     r0
	addi     r1, r1, 0xa0
	blr
	*/
}

/**
 * @note Address: 0x80327694
 * @note Size: 0x2AC
 */
void ObjVs::doUpdateCommon()
{
	f32 scale = (cosf(mScale * PI) + 1.0f) * 0.5f;
	setOnOffBdama(mSetBedamaFlag == false);
	checkObake();
	switch (mDoneState) {
	case 0:
		break;
	case 1:
		if (mFinishTimer > 0.0f) {
			mFinishTimer -= sys->mDeltaTime;
		} else {
			mDoneState = 2;
		}
		break;
	}
	mDisp->mDoneState = mDoneState;
	mScreenP1->update(mDisp->mOlimarData);
	mScreenP2->update(mDisp->mLouieData);

	mScreenP1->mScreen->setXY(0.0f, scale * -300.0f);
	mScreenP2->mScreen->setXY(0.0f, scale * 300.0f);
	mBloGroup->update();

	/*
	stwu     r1, -0x50(r1)
	mflr     r0
	stw      r0, 0x54(r1)
	stfd     f31, 0x40(r1)
	psq_st   f31, 72(r1), 0, qr0
	stfd     f30, 0x30(r1)
	psq_st   f30, 56(r1), 0, qr0
	stfd     f29, 0x20(r1)
	psq_st   f29, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	stw      r30, 0x18(r1)
	stw      r29, 0x14(r1)
	lfs      f2, lbl_8051DDDC@sda21(r2)
	mr       r31, r3
	lfs      f1, 0x50(r3)
	lfs      f0, lbl_8051DD98@sda21(r2)
	fmuls    f1, f2, f1
	fcmpo    cr0, f1, f0
	bge      lbl_803276E4
	fneg     f1, f1

lbl_803276E4:
	lfs      f0, lbl_8051DDC4@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	lbz      r0, 0x10e(r31)
	addi     r5, r3, sincosTable___5JMath@l
	fmuls    f1, f1, f0
	lfs      f2, lbl_8051DDA4@sda21(r2)
	cntlzw   r0, r0
	lfs      f0, lbl_8051DDC8@sda21(r2)
	srwi     r4, r0, 5
	mr       r3, r31
	fctiwz   f1, f1
	stfd     f1, 8(r1)
	lwz      r0, 0xc(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r5, r5, r0
	lfs      f1, 4(r5)
	fadds    f1, f2, f1
	fmuls    f29, f1, f0
	bl       setOnOffBdama__Q32og9newScreen5ObjVsFb
	mr       r3, r31
	bl       checkObake__Q32og9newScreen5ObjVsFv
	lwz      r0, 0x100(r31)
	cmpwi    r0, 1
	beq      lbl_8032774C
	bge      lbl_80327778
	b        lbl_80327778

lbl_8032774C:
	lfs      f1, 0xfc(r31)
	lfs      f0, lbl_8051DD98@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_80327770
	lwz      r3, sys@sda21(r13)
	lfs      f0, 0x54(r3)
	fsubs    f0, f1, f0
	stfs     f0, 0xfc(r31)
	b        lbl_80327778

lbl_80327770:
	li       r0, 2
	stw      r0, 0x100(r31)

lbl_80327778:
	lwz      r0, 0x100(r31)
	lwz      r3, 0x38(r31)
	stw      r0, 8(r3)
	lwz      r29, 0x44(r31)
	lwz      r30, 0x38(r31)
	lwz      r3, 0xc(r29)
	bl       calc__Q32og6Screen8ScaleMgrFv
	fmr      f31, f1
	lwz      r3, 0x10(r29)
	bl       calc__Q32og6Screen8ScaleMgrFv
	lwz      r3, 0x14(r29)
	fmr      f30, f1
	cmplwi   r3, 0
	beq      lbl_803277C8
	stfs     f31, 0xcc(r3)
	stfs     f31, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl

lbl_803277C8:
	lwz      r3, 0x18(r29)
	cmplwi   r3, 0
	beq      lbl_803277EC
	stfs     f30, 0xcc(r3)
	stfs     f30, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl

lbl_803277EC:
	lwz      r3, 8(r29)
	lfs      f0, 0x28(r30)
	stfs     f0, 8(r3)
	lwz      r0, 0x2c(r30)
	stw      r0, 0xc(r3)
	lwz      r0, 0x30(r30)
	stw      r0, 0x10(r3)
	lwz      r0, 0x34(r30)
	stw      r0, 0x14(r3)
	lwz      r0, 0x38(r30)
	stw      r0, 0x18(r3)
	lbz      r0, 0x3c(r30)
	stb      r0, 0x1c(r3)
	bl       update__Q32og6Screen11DopingCheckFv
	lwz      r29, 0x48(r31)
	lwz      r30, 0x38(r31)
	lwz      r3, 0xc(r29)
	bl       calc__Q32og6Screen8ScaleMgrFv
	fmr      f30, f1
	lwz      r3, 0x10(r29)
	bl       calc__Q32og6Screen8ScaleMgrFv
	lwz      r3, 0x14(r29)
	fmr      f31, f1
	cmplwi   r3, 0
	beq      lbl_80327868
	stfs     f30, 0xcc(r3)
	stfs     f30, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl

lbl_80327868:
	lwz      r3, 0x18(r29)
	cmplwi   r3, 0
	beq      lbl_8032788C
	stfs     f31, 0xcc(r3)
	stfs     f31, 0xd0(r3)
	lwz      r12, 0(r3)
	lwz      r12, 0x2c(r12)
	mtctr    r12
	bctrl

lbl_8032788C:
	lwz      r3, 8(r29)
	lfs      f0, 0x40(r30)
	stfs     f0, 8(r3)
	lwz      r0, 0x44(r30)
	stw      r0, 0xc(r3)
	lwz      r0, 0x48(r30)
	stw      r0, 0x10(r3)
	lwz      r0, 0x4c(r30)
	stw      r0, 0x14(r3)
	lwz      r0, 0x50(r30)
	stw      r0, 0x18(r3)
	lbz      r0, 0x54(r30)
	stb      r0, 0x1c(r3)
	bl       update__Q32og6Screen11DopingCheckFv
	lfs      f1, lbl_8051DD98@sda21(r2)
	lfs      f0, mstTuningTransX__Q29P2DScreen10Mgr_tuning@sda21(r2)
	lwz      r3, 0x44(r31)
	fadds    f3, f1, f0
	lfs      f0, lbl_8051DDE0@sda21(r2)
	lfs      f2, mstTuningTransY__Q29P2DScreen10Mgr_tuning@sda21(r2)
	lwz      r3, 0(r3)
	fmadds   f1, f0, f29, f2
	lfs      f0, lbl_8051DDE4@sda21(r2)
	stfs     f3, 0x140(r3)
	fmadds   f0, f0, f29, f2
	stfs     f1, 0x144(r3)
	lwz      r3, 0x48(r31)
	lwz      r3, 0(r3)
	stfs     f3, 0x140(r3)
	stfs     f0, 0x144(r3)
	lwz      r3, 0x3c(r31)
	bl       update__Q32og6Screen8BloGroupFv
	psq_l    f31, 72(r1), 0, qr0
	lfd      f31, 0x40(r1)
	psq_l    f30, 56(r1), 0, qr0
	lfd      f30, 0x30(r1)
	psq_l    f29, 40(r1), 0, qr0
	lfd      f29, 0x20(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	lwz      r0, 0x54(r1)
	lwz      r29, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x50
	blr
	*/
}

/**
 * @note Address: 0x80327940
 * @note Size: 0x44
 */
bool ObjVs::doUpdate()
{
	doUpdateCommon();
	if (mSetBedamaFlag) {
		mSetBedamaFlag = false;
	}
	return false;
}

/**
 * @note Address: 0x80327984
 * @note Size: 0x130
 */
void ObjVs::doDraw(Graphics& gfx)
{
	J2DPerspGraph* graf = &gfx.mPerspGraph;
	graf->setPort();

	JUtility::TColor color1 = ObjChallenge2P::msVal.mDividerBarColor;
	int test                = (f32)color1.a * mScale;
	color1.a                = test;
	graf->setColor(color1);

	f32 baseY = (f32)ObjChallenge2P::msVal.mDividerBarYPos;
	JGeometry::TBox2f box(0.0f, baseY, 640.0f, baseY + (f32)ObjChallenge2P::msVal.mDividerBarHeight);

	graf->fillBox(box);

	mBloGroup->draw(graf);
}

/**
 * @note Address: 0x80327AB4
 * @note Size: 0x14
 */
bool ObjVs::doStart(::Screen::StartSceneArg const*)
{
	mFadeLevel = 0.0f;
	mScale     = 0.0f;
	return true;
}

/**
 * @note Address: 0x80327AC8
 * @note Size: 0x10
 */
bool ObjVs::doEnd(::Screen::EndSceneArg const*)
{
	mFadeLevel = 0.0f;
	return true;
}

/**
 * @note Address: 0x80327AD8
 * @note Size: 0x4
 */
void ObjVs::doUpdateFadeinFinish() { }

/**
 * @note Address: 0x80327ADC
 * @note Size: 0xC
 */
void ObjVs::doUpdateFinish() { mFadeLevel = 0.0f; }

/**
 * @note Address: 0x80327AE8
 * @note Size: 0x4
 */
void ObjVs::doUpdateFadeoutFinish() { }

/**
 * @note Address: 0x80327AEC
 * @note Size: 0x74
 */
bool ObjVs::doUpdateFadein()
{
	bool check = false;
	mFadeLevel += sys->mDeltaTime;

	if (mFadeLevel > msVal.mFadeInRate) {
		mFadeLevel = msVal.mFadeInRate;
		check      = true;
	}
	mScale = mFadeLevel / msVal.mFadeInRate;
	doUpdateCommon();
	return check;
}

/**
 * @note Address: 0x80327B60
 * @note Size: 0x7C
 */
bool ObjVs::doUpdateFadeout()
{
	bool check = false;
	mFadeLevel += sys->mDeltaTime;
	if (mFadeLevel > msVal.mFadeOutRate) {
		mFadeLevel = msVal.mFadeOutRate;
		check      = true;
	}
	mScale = 1.0f - mFadeLevel / msVal.mFadeOutRate;
	doUpdateCommon();
	return check;
}

ObjVs::StaticValues ObjVs::msVal;

} // namespace newScreen
} // namespace og
