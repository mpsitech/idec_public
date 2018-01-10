/**
  * \file PnlIdecNavMaint.cpp
  * job handler for job PnlIdecNavMaint (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecNavMaint.h"

#include "PnlIdecNavMaint_blks.cpp"
#include "PnlIdecNavMaint_evals.cpp"

/******************************************************************************
 class PnlIdecNavMaint
 ******************************************************************************/

PnlIdecNavMaint::PnlIdecNavMaint(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECNAVMAINT, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFLstUsg.tag = "FeedFLstUsg";
	feedFLstUsr.tag = "FeedFLstUsr";

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refreshUsg(dbsidec, moditems);
	refreshUsr(dbsidec, moditems);
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	xchg->addIxRefClstn(VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVCard::CRDIDECUSG, xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), Clstn::VecVJactype::LOCK);
	xchg->addIxRefClstn(VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVCard::CRDIDECUSR, xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), Clstn::VecVJactype::LOCK);
};

PnlIdecNavMaint::~PnlIdecNavMaint() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecNavMaint::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &feedFLstUsg, &feedFLstUsr, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecNavMaint::refreshLstUsg(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstUsgAvail = evalLstUsgAvail(dbsidec);
	statshr.ButUsgViewActive = evalButUsgViewActive(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavMaint::refreshUsg(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);

	ListIdecHistRMUserUniversal rst;
	IdecHistRMUserUniversal* rec = NULL;

	// contiac
	contiac.numFLstUsg = 0;

	// feedFLstUsg
	feedFLstUsg.clear();

	dbsidec->tblidechistrmuseruniversal->loadRstByUsrCrd(xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), VecIdecVCard::CRDIDECUSG, false, rst);

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		feedFLstUsg.appendRefTitles(rec->ref, StubIdec::getStubUsgStd(dbsidec, rec->unvUref, ixIdecVLocale));
	};

	insert(moditems, DpchEngData::FEEDFLSTUSG);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshLstUsg(dbsidec, moditems);
};

void PnlIdecNavMaint::refreshLstUsr(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstUsrAvail = evalLstUsrAvail(dbsidec);
	statshr.ButUsrViewActive = evalButUsrViewActive(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavMaint::refreshUsr(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);

	ListIdecHistRMUserUniversal rst;
	IdecHistRMUserUniversal* rec = NULL;

	// contiac
	contiac.numFLstUsr = 0;

	// feedFLstUsr
	feedFLstUsr.clear();

	dbsidec->tblidechistrmuseruniversal->loadRstByUsrCrd(xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref), VecIdecVCard::CRDIDECUSR, false, rst);

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		feedFLstUsr.appendRefTitles(rec->ref, StubIdec::getStubUsrStd(dbsidec, rec->unvUref, ixIdecVLocale));
	};

	insert(moditems, DpchEngData::FEEDFLSTUSR);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshLstUsr(dbsidec, moditems);
};

void PnlIdecNavMaint::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	// IP refresh --- INSERT
};

void PnlIdecNavMaint::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	refresh(dbsidec, moditems);

	refreshLstUsg(dbsidec, moditems);
	refreshLstUsr(dbsidec, moditems);
	if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	// IP updatePreset --- END
};

void PnlIdecNavMaint::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVMAINTDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVMAINTDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTUSGVIEWCLICK) {
					handleDpchAppDoButUsgViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTUSGNEWCRDCLICK) {
					handleDpchAppDoButUsgNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTUSRVIEWCLICK) {
					handleDpchAppDoButUsrViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTUSRNEWCRDCLICK) {
					handleDpchAppDoButUsrNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTSCFNEWCRDCLICK) {
					handleDpchAppDoButScfNewcrdClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTUTLNEWCRDCLICK) {
					handleDpchAppDoButUtlNewcrdClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecNavMaint::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecNavMaint::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (has(diffitems, ContIac::NUMFLSTUSG)) {
		contiac.numFLstUsg = _contiac->numFLstUsg;
		refreshLstUsg(dbsidec, moditems);
	};

	if (has(diffitems, ContIac::NUMFLSTUSR)) {
		contiac.numFLstUsr = _contiac->numFLstUsr;
		refreshLstUsr(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecNavMaint::handleDpchAppDoButUsgViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	IdecHistRMUserUniversal* husrRunv = NULL;
	ubigint jrefNew = 0;

	if (statshr.LstUsgAvail && statshr.ButUsgViewActive) {
		if (dbsidec->tblidechistrmuseruniversal->loadRecByRef(feedFLstUsg.getRefByNum(contiac.numFLstUsg), &husrRunv)) {
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, husrRunv->ixIdecVPreset, husrRunv->preUref, "CrdIdecUsg", husrRunv->unvUref, jrefNew);
			delete husrRunv;
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsg");
	};
};

void PnlIdecNavMaint::handleDpchAppDoButUsgNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUsg", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsg");
};

void PnlIdecNavMaint::handleDpchAppDoButUsrViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	IdecHistRMUserUniversal* husrRunv = NULL;
	ubigint jrefNew = 0;

	if (statshr.LstUsrAvail && statshr.ButUsrViewActive) {
		if (dbsidec->tblidechistrmuseruniversal->loadRecByRef(feedFLstUsr.getRefByNum(contiac.numFLstUsr), &husrRunv)) {
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, husrRunv->ixIdecVPreset, husrRunv->preUref, "CrdIdecUsr", husrRunv->unvUref, jrefNew);
			delete husrRunv;
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsr");
	};
};

void PnlIdecNavMaint::handleDpchAppDoButUsrNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUsr", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsr");
};

void PnlIdecNavMaint::handleDpchAppDoButScfNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecScf", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecScf");
};

void PnlIdecNavMaint::handleDpchAppDoButUtlNewcrdClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUtl", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUtl");
};

void PnlIdecNavMaint::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ) {
		call->abort = handleCallIdecHusrRunvMod_crdUsrEq(dbsidec, call->jref, call->argInv.ix, call->argInv.ref);
	};
};

bool PnlIdecNavMaint::handleCallIdecHusrRunvMod_crdUsrEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;
	set<uint> moditems;

	if (ixInv == VecIdecVCard::CRDIDECUSG) {
		refreshUsg(dbsidec, moditems);
	} else if (ixInv == VecIdecVCard::CRDIDECUSR) {
		refreshUsr(dbsidec, moditems);
	};

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

