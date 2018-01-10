/**
  * \file VecIdecVCall.cpp
  * vector VecIdecVCall (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVCall.h"

/******************************************************************************
 namespace VecIdecVCall
 ******************************************************************************/

uint VecIdecVCall::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "callidecaccess") return CALLIDECACCESS;
	else if (s == "callidecboolvalpreset") return CALLIDECBOOLVALPRESET;
	else if (s == "callideccrdactive") return CALLIDECCRDACTIVE;
	else if (s == "callideccrdclose") return CALLIDECCRDCLOSE;
	else if (s == "callideccrdopen") return CALLIDECCRDOPEN;
	else if (s == "callidecctlaparmod.usreq") return CALLIDECCTLAPARMOD_USREQ;
	else if (s == "callidecdblvalpreset") return CALLIDECDBLVALPRESET;
	else if (s == "callidecdescr") return CALLIDECDESCR;
	else if (s == "callidecdevidhw") return CALLIDECDEVIDHW;
	else if (s == "callidecdlgclose") return CALLIDECDLGCLOSE;
	else if (s == "callidecfil.clueq") return CALLIDECFIL_CLUEQ;
	else if (s == "callidecfil.reteq") return CALLIDECFIL_RETEQ;
	else if (s == "callidecfil.reueq") return CALLIDECFIL_REUEQ;
	else if (s == "callidecfilmod") return CALLIDECFILMOD;
	else if (s == "callidecfilmod.clueq") return CALLIDECFILMOD_CLUEQ;
	else if (s == "callidecfilmod.retreueq") return CALLIDECFILMOD_RETREUEQ;
	else if (s == "callidecfilupd.refeq") return CALLIDECFILUPD_REFEQ;
	else if (s == "callidechusrrunvmod.crdusreq") return CALLIDECHUSRRUNVMOD_CRDUSREQ;
	else if (s == "callidecibitrdy") return CALLIDECIBITRDY;
	else if (s == "callidecimgrdy") return CALLIDECIMGRDY;
	else if (s == "callidecintvalpreset") return CALLIDECINTVALPRESET;
	else if (s == "callidecixpreset") return CALLIDECIXPRESET;
	else if (s == "callideckakjkeymod.klsakeyeq") return CALLIDECKAKJKEYMOD_KLSAKEYEQ;
	else if (s == "callidecklsakeymod.klseq") return CALLIDECKLSAKEYMOD_KLSEQ;
	else if (s == "callidecklsakeymod.klsmtburfeq") return CALLIDECKLSAKEYMOD_KLSMTBURFEQ;
	else if (s == "callideclog") return CALLIDECLOG;
	else if (s == "callideclogout") return CALLIDECLOGOUT;
	else if (s == "callidecmastclaim") return CALLIDECMASTCLAIM;
	else if (s == "callidecmastslvchg") return CALLIDECMASTSLVCHG;
	else if (s == "callidecmismod") return CALLIDECMISMOD;
	else if (s == "callidecmisupd.refeq") return CALLIDECMISUPD_REFEQ;
	else if (s == "callidecmonstatchg") return CALLIDECMONSTATCHG;
	else if (s == "callidecnodechg") return CALLIDECNODECHG;
	else if (s == "callidecprsjlnmmod.prseq") return CALLIDECPRSJLNMMOD_PRSEQ;
	else if (s == "callidecprsmod") return CALLIDECPRSMOD;
	else if (s == "callidecprsupd.refeq") return CALLIDECPRSUPD_REFEQ;
	else if (s == "callidecrefpreset") return CALLIDECREFPRESET;
	else if (s == "callidecrefspreset") return CALLIDECREFSPRESET;
	else if (s == "callidecscr") return CALLIDECSCR;
	else if (s == "callidecsesmod") return CALLIDECSESMOD;
	else if (s == "callidecsesmod.usreq") return CALLIDECSESMOD_USREQ;
	else if (s == "callidecsesupd.refeq") return CALLIDECSESUPD_REFEQ;
	else if (s == "callidecsptfnd") return CALLIDECSPTFND;
	else if (s == "callidecsrefpreset") return CALLIDECSREFPRESET;
	else if (s == "callidecstart") return CALLIDECSTART;
	else if (s == "callidecstatchg") return CALLIDECSTATCHG;
	else if (s == "callidecstgchg") return CALLIDECSTGCHG;
	else if (s == "callidecstop") return CALLIDECSTOP;
	else if (s == "callidecstubchg") return CALLIDECSTUBCHG;
	else if (s == "callidectou.miseq") return CALLIDECTOU_MISEQ;
	else if (s == "callidectoumod") return CALLIDECTOUMOD;
	else if (s == "callidectoumod.miseq") return CALLIDECTOUMOD_MISEQ;
	else if (s == "callidectouupd.refeq") return CALLIDECTOUUPD_REFEQ;
	else if (s == "callidectriglwir") return CALLIDECTRIGLWIR;
	else if (s == "callidectrigqcd") return CALLIDECTRIGQCD;
	else if (s == "callidectrigvisl") return CALLIDECTRIGVISL;
	else if (s == "callidectrigvisr") return CALLIDECTRIGVISR;
	else if (s == "callidectxtvalpreset") return CALLIDECTXTVALPRESET;
	else if (s == "callidecusgaaccmod.usgeq") return CALLIDECUSGAACCMOD_USGEQ;
	else if (s == "callidecusgmod") return CALLIDECUSGMOD;
	else if (s == "callidecusgupd.refeq") return CALLIDECUSGUPD_REFEQ;
	else if (s == "callidecusr.usgeq") return CALLIDECUSR_USGEQ;
	else if (s == "callidecusraaccmod.usreq") return CALLIDECUSRAACCMOD_USREQ;
	else if (s == "callidecusrjstemod.usreq") return CALLIDECUSRJSTEMOD_USREQ;
	else if (s == "callidecusrmod") return CALLIDECUSRMOD;
	else if (s == "callidecusrrusgmod.usgeq") return CALLIDECUSRRUSGMOD_USGEQ;
	else if (s == "callidecusrrusgmod.usreq") return CALLIDECUSRRUSGMOD_USREQ;
	else if (s == "callidecusrupd.refeq") return CALLIDECUSRUPD_REFEQ;

	return(0);
};

string VecIdecVCall::getSref(
			const uint ix
		) {
	if (ix == CALLIDECACCESS) return("CallIdecAccess");
	else if (ix == CALLIDECBOOLVALPRESET) return("CallIdecBoolvalPreSet");
	else if (ix == CALLIDECCRDACTIVE) return("CallIdecCrdActive");
	else if (ix == CALLIDECCRDCLOSE) return("CallIdecCrdClose");
	else if (ix == CALLIDECCRDOPEN) return("CallIdecCrdOpen");
	else if (ix == CALLIDECCTLAPARMOD_USREQ) return("CallIdecCtlAparMod.usrEq");
	else if (ix == CALLIDECDBLVALPRESET) return("CallIdecDblvalPreSet");
	else if (ix == CALLIDECDESCR) return("CallIdecDescr");
	else if (ix == CALLIDECDEVIDHW) return("CallIdecDevidhw");
	else if (ix == CALLIDECDLGCLOSE) return("CallIdecDlgClose");
	else if (ix == CALLIDECFIL_CLUEQ) return("CallIdecFil.cluEq");
	else if (ix == CALLIDECFIL_RETEQ) return("CallIdecFil.retEq");
	else if (ix == CALLIDECFIL_REUEQ) return("CallIdecFil.reuEq");
	else if (ix == CALLIDECFILMOD) return("CallIdecFilMod");
	else if (ix == CALLIDECFILMOD_CLUEQ) return("CallIdecFilMod.cluEq");
	else if (ix == CALLIDECFILMOD_RETREUEQ) return("CallIdecFilMod.retReuEq");
	else if (ix == CALLIDECFILUPD_REFEQ) return("CallIdecFilUpd.refEq");
	else if (ix == CALLIDECHUSRRUNVMOD_CRDUSREQ) return("CallIdecHusrRunvMod.crdUsrEq");
	else if (ix == CALLIDECIBITRDY) return("CallIdecIbitrdy");
	else if (ix == CALLIDECIMGRDY) return("CallIdecImgrdy");
	else if (ix == CALLIDECINTVALPRESET) return("CallIdecIntvalPreSet");
	else if (ix == CALLIDECIXPRESET) return("CallIdecIxPreSet");
	else if (ix == CALLIDECKAKJKEYMOD_KLSAKEYEQ) return("CallIdecKakJkeyMod.klsAkeyEq");
	else if (ix == CALLIDECKLSAKEYMOD_KLSEQ) return("CallIdecKlsAkeyMod.klsEq");
	else if (ix == CALLIDECKLSAKEYMOD_KLSMTBURFEQ) return("CallIdecKlsAkeyMod.klsMtbUrfEq");
	else if (ix == CALLIDECLOG) return("CallIdecLog");
	else if (ix == CALLIDECLOGOUT) return("CallIdecLogout");
	else if (ix == CALLIDECMASTCLAIM) return("CallIdecMastClaim");
	else if (ix == CALLIDECMASTSLVCHG) return("CallIdecMastslvChg");
	else if (ix == CALLIDECMISMOD) return("CallIdecMisMod");
	else if (ix == CALLIDECMISUPD_REFEQ) return("CallIdecMisUpd.refEq");
	else if (ix == CALLIDECMONSTATCHG) return("CallIdecMonstatChg");
	else if (ix == CALLIDECNODECHG) return("CallIdecNodeChg");
	else if (ix == CALLIDECPRSJLNMMOD_PRSEQ) return("CallIdecPrsJlnmMod.prsEq");
	else if (ix == CALLIDECPRSMOD) return("CallIdecPrsMod");
	else if (ix == CALLIDECPRSUPD_REFEQ) return("CallIdecPrsUpd.refEq");
	else if (ix == CALLIDECREFPRESET) return("CallIdecRefPreSet");
	else if (ix == CALLIDECREFSPRESET) return("CallIdecRefsPreSet");
	else if (ix == CALLIDECSCR) return("CallIdecScr");
	else if (ix == CALLIDECSESMOD) return("CallIdecSesMod");
	else if (ix == CALLIDECSESMOD_USREQ) return("CallIdecSesMod.usrEq");
	else if (ix == CALLIDECSESUPD_REFEQ) return("CallIdecSesUpd.refEq");
	else if (ix == CALLIDECSPTFND) return("CallIdecSptfnd");
	else if (ix == CALLIDECSREFPRESET) return("CallIdecSrefPreSet");
	else if (ix == CALLIDECSTART) return("CallIdecStart");
	else if (ix == CALLIDECSTATCHG) return("CallIdecStatChg");
	else if (ix == CALLIDECSTGCHG) return("CallIdecStgChg");
	else if (ix == CALLIDECSTOP) return("CallIdecStop");
	else if (ix == CALLIDECSTUBCHG) return("CallIdecStubChg");
	else if (ix == CALLIDECTOU_MISEQ) return("CallIdecTou.misEq");
	else if (ix == CALLIDECTOUMOD) return("CallIdecTouMod");
	else if (ix == CALLIDECTOUMOD_MISEQ) return("CallIdecTouMod.misEq");
	else if (ix == CALLIDECTOUUPD_REFEQ) return("CallIdecTouUpd.refEq");
	else if (ix == CALLIDECTRIGLWIR) return("CallIdecTrigLwir");
	else if (ix == CALLIDECTRIGQCD) return("CallIdecTrigQcd");
	else if (ix == CALLIDECTRIGVISL) return("CallIdecTrigVisl");
	else if (ix == CALLIDECTRIGVISR) return("CallIdecTrigVisr");
	else if (ix == CALLIDECTXTVALPRESET) return("CallIdecTxtvalPreSet");
	else if (ix == CALLIDECUSGAACCMOD_USGEQ) return("CallIdecUsgAaccMod.usgEq");
	else if (ix == CALLIDECUSGMOD) return("CallIdecUsgMod");
	else if (ix == CALLIDECUSGUPD_REFEQ) return("CallIdecUsgUpd.refEq");
	else if (ix == CALLIDECUSR_USGEQ) return("CallIdecUsr.usgEq");
	else if (ix == CALLIDECUSRAACCMOD_USREQ) return("CallIdecUsrAaccMod.usrEq");
	else if (ix == CALLIDECUSRJSTEMOD_USREQ) return("CallIdecUsrJsteMod.usrEq");
	else if (ix == CALLIDECUSRMOD) return("CallIdecUsrMod");
	else if (ix == CALLIDECUSRRUSGMOD_USGEQ) return("CallIdecUsrRusgMod.usgEq");
	else if (ix == CALLIDECUSRRUSGMOD_USREQ) return("CallIdecUsrRusgMod.usrEq");
	else if (ix == CALLIDECUSRUPD_REFEQ) return("CallIdecUsrUpd.refEq");

	return("");
};

