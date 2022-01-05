#ifndef _TAGPARM_H
#define _TAGPARM_H

#include "CNode.h"
#include "Dolphin/string.h"
#include "stream.h"
#include "types.h"

struct TagParm;

struct TagParameters : public CNode {
	TagParameters(char*);

	virtual ~TagParameters() { } // _00

	void read(Stream&);

	// Unused/inlined:
	bool isEndToken(char* token)
	{
		// UNUSED FUNCTION
		int strLen = strlen("end");
		return (strncmp("end", token, strLen)) == 0;
	}
	void add(TagParm*);
	void write(Stream&);
	void dump();

	TagParm* m_head; // _18
};

struct TagParm {
	TagParm(TagParameters*, char*);

	/**
	 * @reifiedAddress{8041BD30}
	 * @reifiedFile{sysCommonU/tagparams.cpp}
	 */
	virtual void doWrite(Stream&) { } // _00
	/**
	 * @reifiedAddress{8041BD2C}
	 * @reifiedFile{sysCommonU/tagparams.cpp}
	 */
	virtual void doRead(Stream&) { } // _04
	/**
	 * @reifiedAddress{801B4730}
	 * @reifiedFile{plugProjectKandoU/pelletConfig.cpp}
	 */
	virtual void flushValue() { } // _08
	/**
	 * @reifiedAddress{8041BD34}
	 * @reifiedFile{sysCommonU/tagparams.cpp}
	 */
	virtual void doDump() { } // _0C

	// Unused/inlined:
	void read(Stream&);
	void write(Stream&);
	void dump();

	// _00 VTBL
	char* m_name;    // _04
	TagParm* m_next; // _08
};

struct StringTagParm : public TagParm {
	StringTagParm(TagParameters*, char*);

	virtual void doWrite(Stream&); // _00
	virtual void doRead(Stream&);  // _04
	virtual void flushValue();     // _08
	virtual void doDump();         // _0C

	char* m_data; // _0C
};

template <typename T> struct PrimTagParm : public TagParm {
	PrimTagParm(TagParameters* a, char* name)
	    : TagParm(a, name)
	{
	}

	virtual void doWrite(Stream&); // _00
	virtual void doRead(Stream&);  // _04
	virtual void doDump();         // _0C

	T m_data; // _0C
};

#endif
