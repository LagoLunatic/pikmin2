#ifndef _PSAUTOBGM_CONDUCTOR_H
#define _PSAUTOBGM_CONDUCTOR_H

/*
    __vt__Q29PSAutoBgm9Conductor:
    .4byte 0
    .4byte 0
    .4byte __dt__Q29PSAutoBgm9ConductorFv
    .4byte appendAfter__Q210JADUtility10PrmSetBaseFv
    .4byte "load__Q210JADUtility28PrmSetRc<Q29PSAutoBgm5Track>FR20JSUMemoryInputStream"
    .4byte afterRemovingChildButton__Q210JADUtility10PrmSetBaseFPQ210JADUtility10PrmSetBase
    .4byte afterRemovingThisButton__Q210JADUtility10PrmSetBaseFPQ210JADUtility10PrmSetBase
    .4byte getEraseLink__Q29PSAutoBgm9ConductorFv
    .4byte afterGetFromFree__Q210JADUtility10PrmSetBaseFv
    .4byte "getPrmObjHeap__Q210JADUtility28PrmSetRc<Q29PSAutoBgm5Track>Fv"
*/

namespace JADUtility {
struct PrmSetBase {
	virtual ~PrmSetBase();                              // _08
	virtual void appendAfter();                         // _0C (weak)
	virtual void _10() = 0;                             // _10
	virtual void afterRemovingChildButton(PrmSetBase*); // _14 (weak)
	virtual void afterRemovingThisButton(PrmSetBase*);  // _18 (weak)
	virtual void getEraseLink();                        // _1C (weak)
	virtual void afterGetFromFree();                    // _20 (weak)
};
} // namespace JADUtility

namespace JADUtility {
struct PrmSetRc<PSAutoBgm::Track> {
	virtual ~PrmSetRc<Track>();               // _08
	virtual void _0C() = 0;                   // _0C
	virtual void load(JSUMemoryInputStream&); // _10 (weak)
	virtual void _14() = 0;                   // _14
	virtual void _18() = 0;                   // _18
	virtual void getEraseLink();              // _1C (weak)
	virtual void _20() = 0;                   // _20
	virtual void getPrmObjHeap();             // _24 (weak)
};
} // namespace JADUtility

namespace PSAutoBgm {
struct Conductor : public PrmSetBase, public PrmSetRc<PSAutoBgm::Track> {
	virtual ~Conductor();        // _08
	virtual void getEraseLink(); // _1C (weak)

	void removeCallback(unsigned char, void*);
	void seqCpuSync_AutoBgm(JASTrack*, unsigned short, unsigned long, JASTrack*);
	void createTables(JASTrack*);
};
} // namespace PSAutoBgm

#endif
