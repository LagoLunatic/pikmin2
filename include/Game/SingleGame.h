#ifndef _GAME_SINGLEGAME_H
#define _GAME_SINGLEGAME_H

#include "DvdThreadCommand.h"
#include "Game/IllustratedBook.h"
#include "Game/PelletList.h"
#include "Game/PikiContainer.h"
#include "Game/Result.h"
#include "Game/ResultTexMgr.h"
#include "Game/SingleGameSection.h"
#include "Game/StateMachine.h"
#include "Game/THPPlayer.h"
#include "GenericObjectMgr.h"
#include "IDelegate.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "ObjectMgr.h"
#include "ebi/FileSelect.h"

namespace kh {
namespace Screen {
struct IncP;
struct TotalResultData;
struct WorldMap;
} // namespace Screen
} // namespace kh

namespace Game {

namespace SingleGame {
struct State;

/**
 * @fabricated
 */
enum StateID {
	SGS_File       = 0,
	SGS_Select     = 1,
	SGS_Load       = 2,
	SGS_Game       = 3,
	SGS_Cave       = 4,
	SGS_DayEnd     = 5,
	SGS_CaveDayEnd = 6,
	SGS_MainResult = 7,
	SGS_CaveResult = 8,
	SGS_Movie      = 9,
	SGS_Zukan      = 10,
	SGS_Ending     = 11,
	SGS_StateCount,
};

struct FSM : public StateMachine<SingleGameSection> {
	virtual void init(SingleGameSection*);                    // _08
	virtual void transit(SingleGameSection*, int, StateArg*); // _14

	void draw(Game::SingleGameSection*, Graphics&); // UNUSED
	State* getState(int);

	// _00     = VTBL
	// _00-_1C = StateMachine
};

struct State : public FSMState<SingleGameSection> {
	inline State(int id)
	    : FSMState(id)
	{
	}

	virtual void draw(SingleGameSection*, Graphics&) { }                          // _20 (weak)
	virtual void onOrimaDown(SingleGameSection*, int) { }                         // _24 (weak)
	virtual void onMovieStart(SingleGameSection*, MovieConfig*, u32, u32) { }     // _28 (weak)
	virtual void onMovieDone(SingleGameSection*, MovieConfig*, u32, u32) { }      // _2C (weak)
	virtual void onMovieCommand(SingleGameSection*, int) { }                      // _30 (weak)
	virtual void onHoleIn(SingleGameSection*, ItemCave::Item*) { }                // _34 (weak)
	virtual void onNextFloor(SingleGameSection*, ItemHole::Item*) { }             // _38 (weak)
	virtual void onFountainReturn(SingleGameSection*, ItemBigFountain::Item*) { } // _3C (weak)
	virtual void on_section_fadeout(SingleGameSection*) { }                       // _40 (weak)
	virtual void on_demo_timer(SingleGameSection*, u32) { }                       // _44 (weak)

	State* accountEarnings(SingleGameSection*, PelletCropMemory*, bool);

	// _00     = VTBL
	// _00-_0C = FSMState
	u8 _0C[4]; // _0C
};

/**
 * @size{0x14}
 */
struct CaveDayEndState : public State {
	inline CaveDayEndState()
	    : State(SGS_CaveDayEnd)
	{
	}

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	// _00     = VTBL
	// _00-_10 = State
	f32 _10; // _10
};

struct CaveResultArg : public StateArg {
	u16 _00; // _00 make enum eventually, 1 = geyser, 2 = navis down, 3 = extinction, 4 = giveup
};

/**
 * @size{0x100}
 */
struct CaveResultState : public State {
	CaveResultState();

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	void createResultNodes();
	void loadResource();

	// Unused/inlined:
	void initNext(SingleGameSection*);
	unknown open2D(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	u16 _10;                        //_10
	u16 _12;                        //_12
	unknown _14;                    //_14
	f32 _18;                        //_18
	Controller* _1C;                //_1C
	Result::TNode _20;              //_20
	ResultTexMgr::Mgr* _70;         //_70
	JKRHeap* _74;                   //_74
	u8 _78[4];                      // _78
	Delegate<CaveResultState>* _7C; // _7C
	DvdThreadCommand _80;           // _80
	SingleGameSection* mSection;    // _EC
	JKRHeap* _F0;                   // _F0
	JKRHeap* _F4;                   // _F4
	u8 _F8;                         // _F8
	u32 : 0;
	u8 _FC[4]; // _FC
};

/**
 * @size{0x1C}
 */
struct CaveState : public State {
	inline CaveState()
	    : State(SGS_Cave)
	{
	}

	virtual void init(SingleGameSection*, StateArg*);                          // _08
	virtual void exec(SingleGameSection*);                                     // _0C
	virtual void cleanup(SingleGameSection*);                                  // _10
	virtual void draw(SingleGameSection*, Graphics&);                          // _20
	virtual void onOrimaDown(SingleGameSection*, int);                         // _24
	virtual void onMovieStart(SingleGameSection*, MovieConfig*, u32, u32);     // _28
	virtual void onMovieDone(SingleGameSection*, MovieConfig*, u32, u32);      // _2C
	virtual void onMovieCommand(SingleGameSection*, int);                      // _30
	virtual void onNextFloor(SingleGameSection*, ItemHole::Item*);             // _38
	virtual void onFountainReturn(SingleGameSection*, ItemBigFountain::Item*); // _3C
	virtual void on_section_fadeout(SingleGameSection*);                       // _40

	void check_SMenu(SingleGameSection*);

	// Unused/inlined:
	void gameStart(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	bool mLosePellets; // _10
	bool mFadeout;     // _11
	u32 _14;           // _14, unknown
	bool mDrawSave;    // _18
};

struct DayEndArg : public StateArg {
	DayEndArg(u16 p1)
	    : _00(p1)
	{
	}

	u16 _00;
};

/**
 * @size{0x20}
 */
struct DayEndState : public State {
	inline DayEndState()
	    : State(SGS_DayEnd)
	{
	}

	virtual void init(SingleGameSection*, StateArg*);                      // _08
	virtual void exec(SingleGameSection*);                                 // _0C
	virtual void cleanup(SingleGameSection*);                              // _10
	virtual void draw(SingleGameSection*, Graphics&);                      // _20
	virtual void onMovieStart(SingleGameSection*, MovieConfig*, u32, u32); // _28
	virtual void onMovieDone(SingleGameSection*, MovieConfig*, u32, u32);  // _2C
	virtual void onMovieCommand(SingleGameSection*, int);                  // _30

	// _00     = VTBL
	// _00-_10 = State
	u16 _10;           // _10
	s16 _12;           // _12
	f32 _14;           // _14
	PikiContainer _18; // _18
};

struct EndingArg : public StateArg {
	EndingArg(int state) { mState = state; }
	u8 mState;
};

/**
 * @size{0x30}
 */
struct EndingState : public State {
	EndingState();

	enum EndingFlag {
		Ending_SkipMovie  = 1, // unset = play thp file, set = skip thp file
		Ending_IsComplete = 2  // unset = pay debt, set = all treasures
	};

	enum EndingStatus {
		EndingStatus_InitLoad                 = 0,
		EndingStatus_LoadStart                = 1,
		EndingStatus_LoadFirstMovie           = 2,
		EndingStatus_PlayMoviePayDebt         = 3,
		EndingStatus_PlayMovieCredits         = 4,
		EndingStatus_ShowFinalResultsDebt     = 5,
		EndingStatus_ShowContinueMesg         = 6,
		EndingStatus_PlayMoviePostDebtStart   = 7,
		EndingStatus_PlayMovieAllTreasure     = 8,
		EndingStatus_Unused9                  = 9, // seems to be a copy of state 8? never reached normally
		EndingStatus_ShowFinalResultsComplete = 10
	};

	virtual void init(SingleGameSection* game, StateArg* arg); // _08
	virtual void exec(SingleGameSection* game);                // _0C
	virtual void cleanup(SingleGameSection* game);             // _10
	virtual void draw(SingleGameSection* game, Graphics& gfx); // _20
	virtual void do_dvdload();                                 // _48 (weak)

	void dvdload();

	// Unused/inlined:
	void initNext(SingleGameSection* game);

	// _00     = VTBL
	// _00-_10 = State
	u8 mFlag;                                 // _10
	u8 mStatus;                               // _11
	JKRHeap* mMainHeap;                       // _14
	JKRHeap* mBackupHeap;                     // _18
	THPPlayer* mTHPPlayer;                    // _1C
	u8 mThpState;                             // _20
	Delegate<EndingState>* mDelegate;         // _24
	Controller* mController;                  // _28
	kh::Screen::TotalResultData* mResultData; // _2C
};

/**
 * @size{0x38}
 */
struct FileState : public State {
	FileState();

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	void dvdload();
	void startGame(SingleGameSection*);

	// Unused/inlined:
	void first_init(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	u32 _10;                            // _10
	Controller* mMainController;        // _14
	Delegate<FileState>* mLoadDelegate; // _18
	JKRExpHeap* mMainHeap;              // _1C
	JKRHeap* mBackupHeap;               // _20
	bool mIsNotInitialized;             // _24
	u32 _28;                            // _28, unknown
	ebi::FileSelect::TMgr* mFSMgr;      // _2C
	u8 _30[4];                          // _30
	Controller* mDebugController;       // _34
};

struct GameArg : public StateArg {
	inline GameArg(bool check, u16 val)
	    : _00(check)
	    , _02(val)
	{
	}

	bool _00; // _00
	u16 _02;  // _02
};

/**
 * @size{0x24}
 */
struct GameState : public State {
	/**
	 * @fabricated
	 */
	enum RepayDemoState { RDS_0 = 0, RRD_1, RDS_2, RDS_3, RDS_4 };

	inline GameState()
	    : State(SGS_Game)
	{
	}

	virtual void init(SingleGameSection*, StateArg*);                      // _08
	virtual void exec(SingleGameSection*);                                 // _0C
	virtual void cleanup(SingleGameSection*);                              // _10
	virtual void draw(SingleGameSection*, Graphics&);                      // _20
	virtual void onOrimaDown(SingleGameSection*, int);                     // _24
	virtual void onMovieStart(SingleGameSection*, MovieConfig*, u32, u32); // _28
	virtual void onMovieDone(SingleGameSection*, MovieConfig*, u32, u32);  // _2C
	virtual void onMovieCommand(SingleGameSection*, int);                  // _30
	virtual void onHoleIn(SingleGameSection*, ItemCave::Item*);            // _34
	virtual void on_section_fadeout(SingleGameSection*);                   // _40
	virtual void on_demo_timer(SingleGameSection*, u32);                   // _44

	bool check_DemoInout(SingleGameSection*);
	bool needRepayDemo();
	void startRepayDemo();
	RepayDemoState updateRepayDemo();

	// Unused/inlined:
	void drawRepayDemo(Graphics&);
	unknown gameStart(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	u8 _10;  // _10
	u8 _11;  // _11
	f32 _14; // _14
	u8 _18;  // _18
	u8 _19;  // _19
	u32 : 0;
	u8 _1C[4]; // _1C
	u8 _20;    // _20
};

struct LoadArg : public StateArg {
	inline LoadArg() { }

	inline LoadArg(u16 a, bool b, bool c, bool d)
	    : _04(a)
	    , mInCave(b)
	    , _01(c)
	    , _02(d)
	{
	}

	bool mInCave; // _00
	bool _01;     // _01
	bool _02;     // _02
	u16 _04;      // _04
};

/**
 * @size{0x2C}
 */
struct LoadState : public State {

	inline LoadState()
	    : State(SGS_Load)
	{
	}

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	// Unused/inlined:
	void initNext(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	u32 _10;     // _10, unknown
	bool _14;    // _14
	bool _15;    // _15
	u8 _16[0x2]; // _16, probably padding
	u8 _18[0xC]; // _18, unknown
	u16 _24;     // _24
	bool _26;    // _26
	bool _27;    // _27
	bool _28;    // _28
	bool _29;    // _29
};

/**
 * @size{0x140}
 */
struct MainResultState : public State {
	MainResultState();

	virtual void init(SingleGameSection*, StateArg*);                     // _08
	virtual void exec(SingleGameSection*);                                // _0C
	virtual void cleanup(SingleGameSection*);                             // _10
	virtual void draw(SingleGameSection*, Graphics&);                     // _20
	virtual void onMovieDone(SingleGameSection*, MovieConfig*, u32, u32); // _2C

	void beforeSave();
	void createResultNodes();
	void loadResource();

	// Unused/inlined:
	unknown open2D(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	s16 _10;                            // _10
	f32 _14;                            // _14
	Controller* _18;                    // _18
	u8 _1C;                             // _1C
	u8 _1D[0x3];                        // _1D, unknown/probably padding
	u8 _20[4];                          // _20
	ResultTexMgr::Mgr _24;              // _24
	u8 _64[4];                          // _64
	Result::TNode _68;                  // _68
	kh::Screen::IncP* _B8;              // _B8
	u8 _BC[4];                          // _BC
	JKRHeap* _C0;                       // _C0
	TObjectNode<GenericObjectMgr>* _C4; // _C4
	Delegate<MainResultState>* _C8;     // _C8
	DvdThreadCommand _CC;               // _CC
	SingleGameSection* _138;            // _138
	Delegate<MainResultState>* _13C;    // _13C
};

struct MovieArg : public StateArg {
	MovieArg(THPPlayer::EMovieIndex id) { mMovieIndex = id; }
	THPPlayer::EMovieIndex mMovieIndex; // _00
};

/**
 * @size{0x28}
 */
struct MovieState : public State {
	MovieState();

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	// _00     = VTBL
	// _00-_10 = State
	THPPlayer::EMovieIndex _10; // _10
	Controller* _14;            // _14
	JKRHeap* _18;               // _18
	JKRHeap* _1C;               // _1C
	THPPlayer* _20;             // _20
	bool _24;                   // _24
};

/**
 * @size{0x30}
 */
struct SelectState : public State {
	enum StateID {
		SELECTSTATE_Init = 0,
		SELECTSTATE_Load = 1,
		SELECTSTATE_Draw = 2,
	};

	SelectState();

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	void dvdload();
	void initNext(SingleGameSection*);

	// _00     = VTBL
	// _00-_10 = State
	kh::Screen::WorldMap* mWorldMap;         // _10
	Delegate<SelectState>* mDvdLoadCallback; // _14
	JKRExpHeap* mWMapHeap;                   // _18
	JKRHeap* mParentHeap;                    // _1C
	Controller* mController;                 // _20
	StateID mState;                          // _24
	int mPreviousCourseID;                   // _28
	bool mNewLevelOpen;                      // _2C
};

struct ZukanStateArg : public StateArg {
	u8 mZukanType;
	int mCourseID;
};

/**
 * @size{0x118}
 */
struct ZukanState : public State {
	/**
	 * @real
	 */
	enum CMode { ZSCM_0 = 0, ZSCM_1, ZSCM_2, ZSCM_3, ZSCM_4, ZSCM_5, ZSCM_6, ZSCM_7, ZSCM_8 };

	/**
	 * @fabricated
	 */
	struct Arg {
		u8 _00;           // _00
		int mCourseIndex; // _04
	};

	ZukanState();

	virtual void init(SingleGameSection*, StateArg*); // _08
	virtual void exec(SingleGameSection*);            // _0C
	virtual void cleanup(SingleGameSection*);         // _10
	virtual void draw(SingleGameSection*, Graphics&); // _20

	void clearHeapB_common();
	void clearHeapB_pellet();
	void clearHeapB_teki();
	unknown clearHeaps();
	PelletList::cKind convertPelletID(int&, int);
	void createEnemy(int);
	void createPellet(int);
	void createTeki(int);
	void drawGradationEffect(SingleGameSection*, Graphics&);
	void drawLightEffect(SingleGameSection*, Graphics&);
	unknown dvdloadA();
	void dvdloadB_pellet();
	void dvdloadB_teki();
	void execChangePellet(SingleGameSection*);
	void execChangeTeki(SingleGameSection*);
	void execModeChange(SingleGameSection*, CMode);
	unknown execPellet(SingleGameSection*);
	unknown execTeki(SingleGameSection*);
	void setMode(CMode);
	void startWipe(f32);

	static int getMaxPelletID();
	static PelletConfig* getCurrentPelletConfig(int);

	// Unused/inlined:
	unknown startTekiMode(bool);
	unknown startPelletMode(bool);
	void createItem(int);
	unknown debugDraw(Graphics&);
	void dvdloadB_common();

	// _00     = VTBL
	// _00-_10 = State
	IDelegate* _10;                    // _10
	IDelegate* _14;                    // _14
	IDelegate* _18;                    // _18
	DvdThreadCommand _1C;              // _1C
	u8 _88;                            // _88
	CourseInfo* _8C;                   // _8C
	Controller* _90;                   // _90
	BaseGameSection* _94;              // _94
	IllustratedBook::Camera* _98;      // _98
	CMode _9C;                         // _9C
	int mTekiInfoIndex;                // _A0
	Creature* _A4;                     // _A4
	int _A8;                           // _A8
	Creature* _AC;                     // _AC
	JUTTexture* _B0;                   // _B0
	Rectf _B4;                         // _B4
	u8 _C4[4];                         // _C4
	f32 _C8;                           // _C8
	JUTTexture* _CC;                   // _CC
	u8 _D0[4];                         // _D0
	JKRExpHeap* _D4;                   // _D4
	JKRHeap* _D8;                      // _D8
	JKRExpHeap* _DC;                   // _DC
	JKRHeap* _E0;                      // _E0
	u32 _E4;                           // _E4
	ResultTexMgr::Mgr* _E8;            // _E8
	IllustratedBook::EnemyTexMgr* _EC; // _EC
	JKRExpHeap* _F0;                   // _F0
	f32 _F4;                           // _F4
	f32 _F8;                           // _F8
	unknown _FC;                       // _FC
	IllustratedBook::Parms* _100;      // _100
	IllustratedBook::DebugParms* _104; // _104
	f32 _108;                          // _108
	unknown _10C;                      // _10C
	int _110;                          // _110
	int _114;                          // _114
};
} // namespace SingleGame
} // namespace Game

#endif
