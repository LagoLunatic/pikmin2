

/*
 * --INFO--
 * Address:	........
 * Size:	0000E4
 */
void _Print(char *, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80301688
 * Size:	000050
 */
void Game::FixMiniHoudai::Mgr::__ct( (int, unsigned char))
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r3
  bl        -0x15948
  lis       r3, 0x804D
  lis       r4, 0x8049
  addi      r5, r3, 0x79CC
  mr        r3, r31
  stw       r5, 0x0(r31)
  addi      r5, r5, 0x38
  subi      r0, r4, 0x2378
  stw       r5, 0x4(r31)
  stw       r0, 0x18(r31)
  lwz       r31, 0xC(r1)
  lwz       r0, 0x14(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	803016D8
 * Size:	000048
 */
void Game::FixMiniHoudai::Mgr::doAlloc(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r3
  li        r3, 0x858
  bl        -0x2DD84C
  mr.       r4, r3
  beq-      .loc_0x2C
  bl        -0x46C
  mr        r4, r3

.loc_0x2C:
  mr        r3, r31
  bl        -0x1D1E6C
  lwz       r0, 0x14(r1)
  lwz       r31, 0xC(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	80301720
 * Size:	000060
 */
void Game::FixMiniHoudai::Mgr::createObj( (int))
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r4
  stw       r30, 0x8(r1)
  mr        r30, r3
  mulli     r3, r31, 0x318
  addi      r3, r3, 0x10
  bl        -0x2DD798
  lis       r4, 0x8030
  lis       r5, 0x8030
  addi      r4, r4, 0x195C
  mr        r7, r31
  addi      r5, r5, 0x1780
  li        r6, 0x318
  bl        -0x23FD70
  stw       r3, 0x44(r30)
  lwz       r0, 0x14(r1)
  lwz       r31, 0xC(r1)
  lwz       r30, 0x8(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	80301780
 * Size:	0000EC
 */
void Game::FixMiniHoudai::Obj::__dt(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r4
  stw       r30, 0x8(r1)
  mr.       r30, r3
  beq-      .loc_0xD0
  lis       r3, 0x804D
  addi      r5, r30, 0x308
  addi      r4, r3, 0x76A0
  stw       r4, 0x0(r30)
  addi      r3, r4, 0x1B0
  addi      r0, r4, 0x2FC
  stw       r3, 0x178(r30)
  lwz       r3, 0x17C(r30)
  stw       r0, 0x0(r3)
  lwz       r3, 0x17C(r30)
  sub       r0, r5, r3
  stw       r0, 0xC(r3)
  beq-      .loc_0xC0
  lis       r3, 0x804D
  addi      r4, r3, 0x492C
  stw       r4, 0x0(r30)
  addi      r3, r4, 0x1B0
  addi      r0, r4, 0x2FC
  stw       r3, 0x178(r30)
  lwz       r3, 0x17C(r30)
  stw       r0, 0x0(r3)
  lwz       r3, 0x17C(r30)
  sub       r0, r5, r3
  stw       r0, 0xC(r3)
  beq-      .loc_0xC0
  lis       r3, 0x804B
  addi      r0, r30, 0x2BC
  subi      r4, r3, 0x5CDC
  addi      r3, r30, 0x290
  stw       r4, 0x0(r30)
  addi      r5, r4, 0x1B0
  addi      r6, r4, 0x2F8
  li        r4, -0x1
  stw       r5, 0x178(r30)
  lwz       r5, 0x17C(r30)
  stw       r6, 0x0(r5)
  lwz       r5, 0x17C(r30)
  sub       r0, r0, r5
  stw       r0, 0xC(r5)
  bl        0x10FD4C

.loc_0xC0:
  extsh.    r0, r31
  ble-      .loc_0xD0
  mr        r3, r30
  bl        -0x2DD798

.loc_0xD0:
  lwz       r0, 0x14(r1)
  mr        r3, r30
  lwz       r31, 0xC(r1)
  lwz       r30, 0x8(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	8030186C
 * Size:	000010
 */
void Game::FixMiniHoudai::Mgr::getEnemy( (int))
{
/*
.loc_0x0:
  mulli     r0, r4, 0x318
  lwz       r3, 0x44(r3)
  add       r3, r3, r0
  blr
*/
}

/*
 * --INFO--
 * Address:	8030187C
 * Size:	000008
 */
void Game::FixMiniHoudai::Obj::getEnemyTypeID(void)
{
/*
.loc_0x0:
  li        r3, 0x61
  blr
*/
}

/*
 * --INFO--
 * Address:	80301884
 * Size:	0000C8
 */
void Game::FixMiniHoudai::Mgr::__dt(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r4
  stw       r30, 0x8(r1)
  mr.       r30, r3
  beq-      .loc_0xAC
  lis       r3, 0x804D
  addi      r3, r3, 0x79CC
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x9C
  lis       r3, 0x804D
  addi      r3, r3, 0x4750
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x9C
  lis       r3, 0x804B
  subi      r3, r3, 0x760
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x9C
  lis       r3, 0x804B
  addic.    r0, r30, 0x4
  subi      r3, r3, 0x5304
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x9C
  lis       r4, 0x804B
  addi      r3, r30, 0x4
  subi      r0, r4, 0x5324
  li        r4, 0
  stw       r0, 0x4(r30)
  bl        0x10FC6C

.loc_0x9C:
  extsh.    r0, r31
  ble-      .loc_0xAC
  mr        r3, r30
  bl        -0x2DD878

.loc_0xAC:
  lwz       r0, 0x14(r1)
  mr        r3, r30
  lwz       r31, 0xC(r1)
  lwz       r30, 0x8(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	8030194C
 * Size:	000008
 */
void Game::FixMiniHoudai::Mgr::getEnemyTypeID(void)
{
/*
.loc_0x0:
  li        r3, 0x61
  blr
*/
}

/*
 * --INFO--
 * Address:	80301954
 * Size:	000008
 */
void @4@Game::FixMiniHoudai::Mgr::__dt(void)
{
/*
.loc_0x0:
  subi      r3, r3, 0x4
  b         -0xD4
*/
}
