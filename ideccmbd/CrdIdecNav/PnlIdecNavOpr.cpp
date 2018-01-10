/**
  * \file PnlIdecNavOpr.cpp
  * job handler for job PnlIdecNavOpr (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecNavOpr.h"

#include "PnlIdecNavOpr_blks.cpp"
#include "PnlIdecNavOpr_evals.cpp"

/******************************************************************************
 class PnlIdecNavOpr
 ******************************************************************************/

PnlIdecNavOpr::PnlIdecNavOpr(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECNAVOPR, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFLstFil.tag = "FeedFLstFil";
	feedFLstMis.tag = "FeedFLstMis";
	feedFLstTou.tag = "FeedFLstTou";

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refreshMis(dbsidec, moditems);
	refreshTou(dbsidec, moditems);
	refreshFil(dbsidec, moditems);
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	xchg->addIxRefClstn(VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVCard::CRDIDECMIS, xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), Clstn::VecVJactype::LOCK);
	xchg->addIxRefClstn(VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVCard::CRDIDECTOU, xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), Clstn::VecVJactype::LOCK);
	xchg->addIxRefClstn(VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVCard::CRDIDECFIL, xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), Clstn::VecVJactype::LOCK);
};

PnlIdecNavOpr::~PnlIdecNavOpr() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecNavOpr::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &feedFLstFil, &feedFLstMis, &feedFLstTou, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecNavOpr::refreshLstMis(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstMisAvail = evalLstMisAvail(dbsidec);
	statshr.ButMisViewActive = evalButMisViewActive(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavOpr::refreshMis(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);

	ListIdecHistRMUserUniversal rst;
	IdecHistRMUserUniversal* rec = NULL;

	// contiac
	contiac.numFLstMis = 0;

	// feedFLstMis
	feedFLstMis.clear();

	dbsidec->tblidechistrmuseruniversal->loadRstByUsrCrd(xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), VecIdecVCard::CRDIDECMIS, false, rst);

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		feedFLstMis.appendRefTitles(rec->ref, StubIdec::getStubMisStd(dbsidec, rec->unvUref, ixIdecVLocale));
	};

	insert(moditems, DpchEngData::FEEDFLSTMIS);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshLstMis(dbsidec, moditems);
};

void PnlIdecNavOpr::refreshLstTou(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstTouAvail = evalLstTouAvail(dbsidec);
	statshr.ButTouViewActive = evalButTouViewActive(dbsidec);
	statshr.ButTouNewcrdActive = evalButTouNewcrdActive(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavOpr::refreshTou(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);

	ListIdecHistRMUserUniversal rst;
	IdecHistRMUserUniversal* rec = NULL;

	// contiac
	contiac.numFLstTou = 0;

	// feedFLstTou
	feedFLstTou.clear();

	dbsidec->tblidechistrmuseruniversal->loadRstByUsrCrd(xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), VecIdecVCard::CRDIDECTOU, false, rst);

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		feedFLstTou.appendRefTitles(rec->ref, StubIdec::getStubTouStd(dbsidec, rec->unvUref, ixIdecVLocale));
	};

	insert(moditems, DpchEngData::FEEDFLSTTOU);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshLstTou(dbsidec, moditems);
};

void PnlIdecNavOpr::refreshLstFil(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstFilAvail = evalLstFilAvail(dbsidec);
	statshr.ButFilViewActive = evalButFilViewActive(dbsidec);
	statshr.ButFilNewcrdActive = evalButFilNewcrdActive(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavOpr::refreshFil(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);

	ListIdecHistRMUserUniversal rst;
	IdecHistRMUserUniversal* rec = NULL;

	// contiac
	contiac.numFLstFil = 0;

	// feedFLstFil
	feedFLstFil.clear();

	dbsidec->tblidechistrmuseruniversal->loadRstByUsrCrd(xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), VecIdecVCard::CRDIDECFIL, false, rst);

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		feedFLstFil.appendRefTitles(rec->ref, StubIdec::getStubFilStd(dbsidec, rec->unvUref, ixIdecVLocale));
	};

	insert(moditems, DpchEngData::FEEDFLSTFIL);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshLstFil(dbsidec, moditems);
};

void PnlIdecNavOpr::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// statshr
	statshr.ButIaqNewcrdActive = evalButIaqNewcrdActive(dbsidec);
	statshr.ButAd1NewcrdActive = evalButAd1NewcrdActive(dbsidec);
	// IP refresh --- END

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavOpr::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	refresh(dbsidec, moditems);

	refreshLstMis(dbsidec, moditems);
	refreshLstTou(dbsidec, moditems);
	refreshLstFil(dbsidec, moditems);
	if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	// IP updatePreset --- END
};

void PnlIdecNavOpr::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
		if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECINIT) {
			handleDpchAppIdecInit(dbsidec, (DpchAppIdecInit*) (req->dpchapp), &(req->dpcheng));

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVOPRDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVOPRDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMISVIEWCLICK) {
					handleDpchAppDoButMisViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMISNEWCRDCLICK) {
					handleDpchAppDoButMisNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTOUVIEWCLICK) {
					handleDpchAppDoButTouViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTOUNEWCRDCLICK) {
					handleDpchAppDoButTouNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTIAQNEWCRDCLICK) {
					handleDpchAppDoButIaqNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTAD1NEWCRDCLICK) {
					handleDpchAppDoButAd1NewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTFILVIEWCLICK) {
					handleDpchAppDoButFilViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTFILNEWCRDCLICK) {
					handleDpchAppDoButFilNewcrdClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecNavOpr::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecNavOpr::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	ubigint ref;

	if (has(diffitems, ContIac::NUMFLSTMIS)) {
		contiac.numFLstMis = _contiac->numFLstMis;
		if (dbsidec->tblidechistrmuseruniversal->loadUnuByRef(feedFLstMis.getRefByNum(contiac.numFLstMis), ref)) xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFMIS, ref);
		refreshLstMis(dbsidec, moditems);
	};

	if (has(diffitems, ContIac::NUMFLSTTOU)) {
		contiac.numFLstTou = _contiac->numFLstTou;
		if (dbsidec->tblidechistrmuseruniversal->loadUnuByRef(feedFLstTou.getRefByNum(contiac.numFLstTou), ref)) xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFTOU, ref);
		refreshLstTou(dbsidec, moditems);
	};

	if (has(diffitems, ContIac::NUMFLSTFIL)) {
		contiac.numFLstFil = _contiac->numFLstFil;
		refreshLstFil(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecNavOpr::handleDpchAppDoButMisViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	IdecHistRMUserUniversal* husrRunv = NULL;
	ubigint jrefNew = 0;

	if (statshr.LstMisAvail && statshr.ButMisViewActive) {
		if (dbsidec->tblidechistrmuseruniversal->loadRecByRef(feedFLstMis.getRefByNum(contiac.numFLstMis), &husrRunv)) {
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, husrRunv->ixIdecVPreset, husrRunv->preUref, "CrdIdecMis", husrRunv->unvUref, jrefNew);
			delete husrRunv;
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecMis");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButMisNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecMis", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecMis");
};

void PnlIdecNavOpr::handleDpchAppDoButTouViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	IdecHistRMUserUniversal* husrRunv = NULL;
	ubigint jrefNew = 0;

	if (statshr.LstTouAvail && statshr.ButTouViewActive) {
		if (dbsidec->tblidechistrmuseruniversal->loadRecByRef(feedFLstTou.getRefByNum(contiac.numFLstTou), &husrRunv)) {
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, husrRunv->ixIdecVPreset, husrRunv->preUref, "CrdIdecTou", husrRunv->unvUref, jrefNew);
			delete husrRunv;
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecTou");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButTouNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	if (statshr.ButTouNewcrdActive) {
		xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecTou", 0, jrefNew);

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecTou");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButIaqNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	if (statshr.ButIaqNewcrdActive) {
		xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecIaq", 0, jrefNew);

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecIaq");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButAd1NewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	if (statshr.ButAd1NewcrdActive) {
		xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecAd1", 0, jrefNew);

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecAd1");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButFilViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	IdecHistRMUserUniversal* husrRunv = NULL;
	ubigint jrefNew = 0;

	if (statshr.LstFilAvail && statshr.ButFilViewActive) {
		if (dbsidec->tblidechistrmuseruniversal->loadRecByRef(feedFLstFil.getRefByNum(contiac.numFLstFil), &husrRunv)) {
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, husrRunv->ixIdecVPreset, husrRunv->preUref, "CrdIdecFil", husrRunv->unvUref, jrefNew);
			delete husrRunv;
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecFil");
	};
};

void PnlIdecNavOpr::handleDpchAppDoButFilNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	if (statshr.ButFilNewcrdActive) {
		xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecFil", 0, jrefNew);

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecFil");
	};
};

void PnlIdecNavOpr::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ) {
		call->abort = handleCallIdecHusrRunvMod_crdUsrEq(dbsidec, call->jref, call->argInv.ix, call->argInv.ref);
	};
};

bool PnlIdecNavOpr::handleCallIdecHusrRunvMod_crdUsrEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;
	set<uint> moditems;

	if (ixInv == VecIdecVCard::CRDIDECMIS) {
		refreshMis(dbsidec, moditems);
	} else if (ixInv == VecIdecVCard::CRDIDECTOU) {
		refreshTou(dbsidec, moditems);
	} else if (ixInv == VecIdecVCard::CRDIDECFIL) {
		refreshFil(dbsidec, moditems);
	};

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

