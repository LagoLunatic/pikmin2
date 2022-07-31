#ifndef _EFX_TDENKIPOLE_H
#define _EFX_TDENKIPOLE_H

/*
    __vt__Q23efx10TDenkiPole:
    .4byte 0
    .4byte 0
    .4byte "create__Q23efx28TSyncGroup2<Q23efx8TForever>FPQ23efx3Arg"
    .4byte "forceKill__Q23efx28TSyncGroup2<Q23efx8TForever>Fv"
    .4byte "fade__Q23efx28TSyncGroup2<Q23efx8TForever>Fv"
    .4byte "startDemoDrawOff__Q23efx28TSyncGroup2<Q23efx8TForever>Fv"
    .4byte "endDemoDrawOn__Q23efx28TSyncGroup2<Q23efx8TForever>Fv"
*/

namespace efx {
struct TSyncGroup2<efx::TForever> {
	virtual void TSyncGroup2<TForever>::create(Arg*);       // _08 (weak)
	virtual void TSyncGroup2<TForever>::forceKill();        // _0C (weak)
	virtual void TSyncGroup2<TForever>::fade();             // _10 (weak)
	virtual void TSyncGroup2<TForever>::startDemoDrawOff(); // _14 (weak)
	virtual void TSyncGroup2<TForever>::endDemoDrawOn();    // _18 (weak)
};
} // namespace efx

namespace efx {
struct TDenkiPole : public TSyncGroup2<efx::TForever> {

	~TDenkiPole();
	TDenkiPole();
};
} // namespace efx

#endif
