#ifndef _GAME_VSGAME_STATE_H
#define _GAME_VSGAME_STATE_H

/*
    __vt__Q34Game6VsGame5State:
    .4byte 0
    .4byte 0
    .4byte "init__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSectionPQ24Game8StateArg"
    .4byte "exec__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSection"
    .4byte "cleanup__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSection"
    .4byte "resume__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSection"
    .4byte "restart__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSection"
    .4byte "transit__Q24Game32FSMState<Q24Game13VsGameSection>FPQ24Game13VsGameSectioniPQ24Game8StateArg"
    .4byte draw__Q34Game6VsGame5StateFPQ24Game13VsGameSectionR8Graphics
    .4byte pre2dDraw__Q34Game6VsGame5StateFR8GraphicsPQ24Game13VsGameSection
    .4byte onOrimaDown__Q34Game6VsGame5StateFPQ24Game13VsGameSectioni
    .4byte onMovieStart__Q34Game6VsGame5StateFPQ24Game13VsGameSectionPQ24Game11MovieConfigUlUl
    .4byte onMovieDone__Q34Game6VsGame5StateFPQ24Game13VsGameSectionPQ24Game11MovieConfigUlUl
    .4byte onNextFloor__Q34Game6VsGame5StateFPQ24Game13VsGameSectionPQ34Game8ItemHole4Item
    .4byte on_section_fadeout__Q34Game6VsGame5StateFPQ24Game13VsGameSection
    .4byte goingToCave__Q34Game6VsGame5StateFPQ24Game13VsGameSection
    .4byte onBattleFinished__Q34Game6VsGame5StateFPQ24Game13VsGameSectionib
    .4byte onRedOrBlueSuckStart__Q34Game6VsGame5StateFPQ24Game13VsGameSectionib
    .4byte isCardUsable__Q34Game6VsGame5StateFPQ24Game13VsGameSection
*/

namespace Game {
struct FSMState<Game::VsGameSection> {
	virtual void FSMState<VsGameSection>::init(VsGameSection*, StateArg*);         // _08 (weak)
	virtual void FSMState<VsGameSection>::exec(VsGameSection*);                    // _0C (weak)
	virtual void FSMState<VsGameSection>::cleanup(VsGameSection*);                 // _10 (weak)
	virtual void FSMState<VsGameSection>::resume(VsGameSection*);                  // _14 (weak)
	virtual void FSMState<VsGameSection>::restart(VsGameSection*);                 // _18 (weak)
	virtual void FSMState<VsGameSection>::transit(VsGameSection*, int, StateArg*); // _1C (weak)
};
} // namespace Game

namespace Game {
namespace VsGame {
struct State : public FSMState<Game::VsGameSection> {
	virtual void Vsdraw(VsGameSection*, Graphics&);                                          // _20 (weak)
	virtual void Vspre2dDraw(Graphics&, VsGameSection*);                                     // _24 (weak)
	virtual void VsonOrimaDown(VsGameSection*, int);                                         // _28 (weak)
	virtual void VsonMovieStart(VsGameSection*, MovieConfig*, unsigned long, unsigned long); // _2C (weak)
	virtual void VsonMovieDone(VsGameSection*, MovieConfig*, unsigned long, unsigned long);  // _30 (weak)
	virtual void VsonNextFloor(VsGameSection*, ItemHole::Item*);                             // _34 (weak)
	virtual void Vson_section_fadeout(VsGameSection*);                                       // _38 (weak)
	virtual void VsgoingToCave(VsGameSection*);                                              // _3C (weak)
	virtual void VsonBattleFinished(VsGameSection*, int, bool);                              // _40 (weak)
	virtual void VsonRedOrBlueSuckStart(VsGameSection*, int, bool);                          // _44 (weak)
	virtual void VsisCardUsable(VsGameSection*);                                             // _48 (weak)
};
} // namespace VsGame
} // namespace Game

#endif
