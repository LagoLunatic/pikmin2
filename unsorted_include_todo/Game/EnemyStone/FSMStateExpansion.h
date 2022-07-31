#ifndef _GAME_ENEMYSTONE_FSMSTATEEXPANSION_H
#define _GAME_ENEMYSTONE_FSMSTATEEXPANSION_H

/*
    __vt__Q34Game10EnemyStone17FSMStateExpansion:
    .4byte 0
    .4byte 0
    .4byte init__Q34Game10EnemyStone17FSMStateExpansionFPQ34Game10EnemyStone8DrawInfoPQ24Game8StateArg
    .4byte exec__Q34Game10EnemyStone17FSMStateExpansionFPQ34Game10EnemyStone8DrawInfo
    .4byte cleanup__Q34Game10EnemyStone17FSMStateExpansionFPQ34Game10EnemyStone8DrawInfo
    .4byte "resume__Q24Game38FSMState<Q34Game10EnemyStone8DrawInfo>FPQ34Game10EnemyStone8DrawInfo"
    .4byte "restart__Q24Game38FSMState<Q34Game10EnemyStone8DrawInfo>FPQ34Game10EnemyStone8DrawInfo"
    .4byte "transit__Q24Game38FSMState<Q34Game10EnemyStone8DrawInfo>FPQ34Game10EnemyStone8DrawInfoiPQ24Game8StateArg"
    .4byte makeMatrix__Q34Game10EnemyStone17FSMStateExpansionFPQ34Game10EnemyStone8DrawInfoP7Matrixf
*/

namespace Game {
struct FSMState<Game::EnemyStone::DrawInfo> {
	virtual void init(DrawInfo*, StateArg*);                                                     // _08
	virtual void exec(DrawInfo*);                                                                // _0C
	virtual void cleanup(DrawInfo*);                                                             // _10
	virtual void FSMState<EnemyStone::DrawInfo>::resume(EnemyStone::DrawInfo*);                  // _14 (weak)
	virtual void FSMState<EnemyStone::DrawInfo>::restart(EnemyStone::DrawInfo*);                 // _18 (weak)
	virtual void FSMState<EnemyStone::DrawInfo>::transit(EnemyStone::DrawInfo*, int, StateArg*); // _1C (weak)
};
} // namespace Game

namespace Game {
namespace EnemyStone {
struct FSMStateExpansion : public FSMState<Game::EnemyStone::DrawInfo> {
	virtual void init(DrawInfo*, StateArg*);      // _08
	virtual void exec(DrawInfo*);                 // _0C
	virtual void cleanup(DrawInfo*);              // _10
	virtual void makeMatrix(DrawInfo*, Matrixf*); // _20
};
} // namespace EnemyStone
} // namespace Game

#endif
