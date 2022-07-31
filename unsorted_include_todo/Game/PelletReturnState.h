#ifndef _GAME_PELLETRETURNSTATE_H
#define _GAME_PELLETRETURNSTATE_H

/*
    __vt__Q24Game17PelletReturnState:
    .4byte 0
    .4byte 0
    .4byte init__Q24Game17PelletReturnStateFPQ24Game6PelletPQ24Game8StateArg
    .4byte exec__Q24Game17PelletReturnStateFPQ24Game6Pellet
    .4byte cleanup__Q24Game17PelletReturnStateFPQ24Game6Pellet
    .4byte "resume__Q24Game24FSMState<Q24Game6Pellet>FPQ24Game6Pellet"
    .4byte "restart__Q24Game24FSMState<Q24Game6Pellet>FPQ24Game6Pellet"
    .4byte "transit__Q24Game24FSMState<Q24Game6Pellet>FPQ24Game6PelletiPQ24Game8StateArg"
    .4byte isBuried__Q24Game11PelletStateFv
    .4byte appeared__Q24Game11PelletStateFv
    .4byte isPickable__Q24Game11PelletStateFv
*/

namespace Game {
struct FSMState<Game::Pellet> {
	virtual void init(Pellet*, StateArg*);                           // _08
	virtual void exec(Pellet*);                                      // _0C
	virtual void cleanup(Pellet*);                                   // _10
	virtual void FSMState<Pellet>::resume(Pellet*);                  // _14 (weak)
	virtual void FSMState<Pellet>::restart(Pellet*);                 // _18 (weak)
	virtual void FSMState<Pellet>::transit(Pellet*, int, StateArg*); // _1C (weak)
};
} // namespace Game

namespace Game {
struct PelletState {
	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10
	virtual void _14() = 0;                // _14
	virtual void _18() = 0;                // _18
	virtual void _1C() = 0;                // _1C
	virtual void isBuried();               // _20 (weak)
	virtual void appeared();               // _24 (weak)
	virtual void isPickable();             // _28 (weak)
};
} // namespace Game

namespace Game {
struct PelletReturnState : public FSMState<Game::Pellet>, public PelletState {
	virtual void init(Pellet*, StateArg*); // _08
	virtual void exec(Pellet*);            // _0C
	virtual void cleanup(Pellet*);         // _10

	PelletReturnState();
	void initPathfinding(Game::Pellet*);
	void execPathfinding(Game::Pellet*);
	void execMove(Game::Pellet*);
	void execMoveGoal(Game::Pellet*);
};
} // namespace Game

#endif
