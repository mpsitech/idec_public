/**
  * \file VecIdecVCall.h
  * vector VecIdecVCall (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCALL_H
#define VECIDECVCALL_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVCall
	*/
namespace VecIdecVCall {
	const uint CALLIDECACCESS = 1;
	const uint CALLIDECBOOLVALPRESET = 2;
	const uint CALLIDECCRDACTIVE = 3;
	const uint CALLIDECCRDCLOSE = 4;
	const uint CALLIDECCRDOPEN = 5;
	const uint CALLIDECCTLAPARMOD_USREQ = 6;
	const uint CALLIDECDBLVALPRESET = 7;
	const uint CALLIDECDESCR = 8;
	const uint CALLIDECDEVIDHW = 9;
	const uint CALLIDECDLGCLOSE = 10;
	const uint CALLIDECFIL_CLUEQ = 11;
	const uint CALLIDECFIL_RETEQ = 12;
	const uint CALLIDECFIL_REUEQ = 13;
	const uint CALLIDECFILMOD = 14;
	const uint CALLIDECFILMOD_CLUEQ = 15;
	const uint CALLIDECFILMOD_RETREUEQ = 16;
	const uint CALLIDECFILUPD_REFEQ = 17;
	const uint CALLIDECHUSRRUNVMOD_CRDUSREQ = 18;
	const uint CALLIDECIBITRDY = 19;
	const uint CALLIDECIMGRDY = 20;
	const uint CALLIDECINTVALPRESET = 21;
	const uint CALLIDECIXPRESET = 22;
	const uint CALLIDECKAKJKEYMOD_KLSAKEYEQ = 23;
	const uint CALLIDECKLSAKEYMOD_KLSEQ = 24;
	const uint CALLIDECKLSAKEYMOD_KLSMTBURFEQ = 25;
	const uint CALLIDECLOG = 26;
	const uint CALLIDECLOGOUT = 27;
	const uint CALLIDECMASTCLAIM = 28;
	const uint CALLIDECMASTSLVCHG = 29;
	const uint CALLIDECMISMOD = 30;
	const uint CALLIDECMISUPD_REFEQ = 31;
	const uint CALLIDECMONSTATCHG = 32;
	const uint CALLIDECNODECHG = 33;
	const uint CALLIDECPRSJLNMMOD_PRSEQ = 34;
	const uint CALLIDECPRSMOD = 35;
	const uint CALLIDECPRSUPD_REFEQ = 36;
	const uint CALLIDECREFPRESET = 37;
	const uint CALLIDECREFSPRESET = 38;
	const uint CALLIDECSCR = 39;
	const uint CALLIDECSESMOD = 40;
	const uint CALLIDECSESMOD_USREQ = 41;
	const uint CALLIDECSESUPD_REFEQ = 42;
	const uint CALLIDECSPTFND = 43;
	const uint CALLIDECSREFPRESET = 44;
	const uint CALLIDECSTART = 45;
	const uint CALLIDECSTATCHG = 46;
	const uint CALLIDECSTGCHG = 47;
	const uint CALLIDECSTOP = 48;
	const uint CALLIDECSTUBCHG = 49;
	const uint CALLIDECTOU_MISEQ = 50;
	const uint CALLIDECTOUMOD = 51;
	const uint CALLIDECTOUMOD_MISEQ = 52;
	const uint CALLIDECTOUUPD_REFEQ = 53;
	const uint CALLIDECTRIGLWIR = 54;
	const uint CALLIDECTRIGQCD = 55;
	const uint CALLIDECTRIGVISL = 56;
	const uint CALLIDECTRIGVISR = 57;
	const uint CALLIDECTXTVALPRESET = 58;
	const uint CALLIDECUSGAACCMOD_USGEQ = 59;
	const uint CALLIDECUSGMOD = 60;
	const uint CALLIDECUSGUPD_REFEQ = 61;
	const uint CALLIDECUSR_USGEQ = 62;
	const uint CALLIDECUSRAACCMOD_USREQ = 63;
	const uint CALLIDECUSRJSTEMOD_USREQ = 64;
	const uint CALLIDECUSRMOD = 65;
	const uint CALLIDECUSRRUSGMOD_USGEQ = 66;
	const uint CALLIDECUSRRUSGMOD_USREQ = 67;
	const uint CALLIDECUSRUPD_REFEQ = 68;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

