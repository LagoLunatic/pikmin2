

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
 * Address:	8027D2B8
 * Size:	000050
 */
void Game::Armor::Mgr::__ct( (int, unsigned char))
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r3
  bl        -0x14E638
  lis       r3, 0x804D
  lis       r4, 0x8048
  subi      r5, r3, 0x7C04
  mr        r3, r31
  stw       r5, 0x0(r31)
  addi      r5, r5, 0x38
  addi      r0, r4, 0x7108
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
 * Address:	8027D308
 * Size:	000048
 */
void Game::Armor::Mgr::doAlloc(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr        r31, r3
  li        r3, 0x880
  bl        -0x25947C
  mr.       r4, r3
  beq-      .loc_0x2C
  bl        .loc_0x48
  mr        r4, r3

.loc_0x2C:
  mr        r3, r31
  bl        -0x14DA9C
  lwz       r0, 0x14(r1)
  lwz       r31, 0xC(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr       

.loc_0x48:
*/
}

/*
 * --INFO--
 * Address:	8027D350
 * Size:	000110
 */
void Game::Armor::Parms::__ct(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  lis       r4, 0x8048
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  addi      r31, r4, 0x70F8
  stw       r30, 0x8(r1)
  mr        r30, r3
  bl        -0x173BD4
  lis       r3, 0x804D
  lis       r5, 0x6670
  subi      r0, r3, 0x7C10
  addi      r4, r30, 0x87C
  stw       r0, 0xD8(r30)
  li        r7, 0
  addi      r0, r31, 0x28
  addi      r3, r30, 0x804
  stw       r4, 0x7F8(r30)
  addi      r4, r30, 0x7F8
  addi      r5, r5, 0x3031
  addi      r6, r31, 0x38
  stw       r7, 0x7FC(r30)
  stw       r0, 0x800(r30)
  bl        0x1962AC
  lis       r3, 0x804B
  lis       r5, 0x6670
  subi      r0, r3, 0x5344
  lfs       f0, -0x2E38(r2)
  stw       r0, 0x804(r30)
  addi      r3, r30, 0x82C
  lfs       f1, -0x2E34(r2)
  addi      r4, r30, 0x7F8
  stfs      f0, 0x81C(r30)
  addi      r5, r5, 0x3131
  lfs       f0, -0x2E30(r2)
  addi      r6, r31, 0x44
  stfs      f1, 0x824(r30)
  stfs      f0, 0x828(r30)
  bl        0x196270
  lis       r3, 0x804B
  lis       r5, 0x6670
  subi      r0, r3, 0x5344
  lfs       f1, -0x2E34(r2)
  stw       r0, 0x82C(r30)
  addi      r3, r30, 0x854
  lfs       f0, -0x2E2C(r2)
  addi      r4, r30, 0x7F8
  stfs      f1, 0x844(r30)
  addi      r5, r5, 0x3132
  addi      r6, r31, 0x54
  stfs      f1, 0x84C(r30)
  stfs      f0, 0x850(r30)
  bl        0x196238
  lis       r3, 0x804B
  lfs       f1, -0x2E28(r2)
  subi      r0, r3, 0x5344
  lfs       f0, -0x2E34(r2)
  stw       r0, 0x854(r30)
  mr        r3, r30
  stfs      f1, 0x86C(r30)
  stfs      f0, 0x874(r30)
  stfs      f1, 0x878(r30)
  lwz       r31, 0xC(r1)
  lwz       r30, 0x8(r1)
  lwz       r0, 0x14(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	8027D460
 * Size:	000060
 */
void Game::Armor::Mgr::createObj( (int))
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
  mulli     r3, r31, 0x2F4
  addi      r3, r3, 0x10
  bl        -0x2594D8
  lis       r4, 0x8028
  lis       r5, 0x8028
  subi      r4, r4, 0x2964
  mr        r7, r31
  subi      r5, r5, 0x2B40
  li        r6, 0x2F4
  bl        -0x1BBAB0
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
 * Address:	8027D4C0
 * Size:	0000BC
 */
void Game::Armor::Obj::__dt(void)
{
/*
.loc_0x0:
  stwu      r1, -0x10(r1)
  mflr      r0
  stw       r0, 0x14(r1)
  stw       r31, 0xC(r1)
  mr.       r31, r3
  stw       r30, 0x8(r1)
  mr        r30, r4
  beq-      .loc_0xA0
  lis       r3, 0x804D
  addi      r0, r31, 0x2E4
  subi      r4, r3, 0x7A84
  stw       r4, 0x0(r31)
  addi      r3, r4, 0x1B0
  addi      r4, r4, 0x2FC
  stw       r3, 0x178(r31)
  lwz       r3, 0x17C(r31)
  stw       r4, 0x0(r3)
  lwz       r3, 0x17C(r31)
  sub       r0, r0, r3
  stw       r0, 0xC(r3)
  beq-      .loc_0x90
  lis       r3, 0x804B
  addi      r0, r31, 0x2BC
  subi      r4, r3, 0x5CDC
  addi      r3, r31, 0x290
  stw       r4, 0x0(r31)
  addi      r5, r4, 0x1B0
  addi      r6, r4, 0x2F8
  li        r4, -0x1
  stw       r5, 0x178(r31)
  lwz       r5, 0x17C(r31)
  stw       r6, 0x0(r5)
  lwz       r5, 0x17C(r31)
  sub       r0, r0, r5
  stw       r0, 0xC(r5)
  bl        0x19403C

.loc_0x90:
  extsh.    r0, r30
  ble-      .loc_0xA0
  mr        r3, r31
  bl        -0x2594A8

.loc_0xA0:
  lwz       r0, 0x14(r1)
  mr        r3, r31
  lwz       r31, 0xC(r1)
  lwz       r30, 0x8(r1)
  mtlr      r0
  addi      r1, r1, 0x10
  blr
*/
}

/*
 * --INFO--
 * Address:	8027D57C
 * Size:	000010
 */
void Game::Armor::Mgr::getEnemy( (int))
{
/*
.loc_0x0:
  mulli     r0, r4, 0x2F4
  lwz       r3, 0x44(r3)
  add       r3, r3, r0
  blr
*/
}

/*
 * --INFO--
 * Address:	8027D58C
 * Size:	000050
 */
void Game::Armor::Parms::read( (Stream &))
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
  bl        0x19624C
  mr        r4, r31
  addi      r3, r30, 0xE0
  bl        0x196240
  mr        r4, r31
  addi      r3, r30, 0x7F8
  bl        0x196234
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
 * Address:	8027D5DC
 * Size:	0000B0
 */
void Game::Armor::Mgr::__dt(void)
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
  beq-      .loc_0x94
  lis       r3, 0x804D
  subi      r3, r3, 0x7C04
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x84
  lis       r3, 0x804B
  subi      r3, r3, 0x760
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x84
  lis       r3, 0x804B
  addic.    r0, r30, 0x4
  subi      r3, r3, 0x5304
  stw       r3, 0x0(r30)
  addi      r0, r3, 0x38
  stw       r0, 0x4(r30)
  beq-      .loc_0x84
  lis       r4, 0x804B
  addi      r3, r30, 0x4
  subi      r0, r4, 0x5324
  li        r4, 0
  stw       r0, 0x4(r30)
  bl        0x193F2C

.loc_0x84:
  extsh.    r0, r31
  ble-      .loc_0x94
  mr        r3, r30
  bl        -0x2595B8

.loc_0x94:
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
 * Address:	8027D68C
 * Size:	000008
 */
void Game::Armor::Mgr::getEnemyTypeID(void)
{
/*
.loc_0x0:
  li        r3, 0xF
  blr
*/
}

/*
 * --INFO--
 * Address:	8027D694
 * Size:	000008
 */
void @4@Game::Armor::Mgr::__dt(void)
{
/*
.loc_0x0:
  subi      r3, r3, 0x4
  b         -0xBC
*/
}
