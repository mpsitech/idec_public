/**
  * \file DlgIdecTouNew.cpp
  * job handler for job DlgIdecTouNew (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "DlgIdecTouNew.h"

#include "DlgIdecTouNew_blks.cpp"
#include "DlgIdecTouNew_evals.cpp"

/******************************************************************************
 class DlgIdecTouNew
 ******************************************************************************/

DlgIdecTouNew::DlgIdecTouNew(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::DLGIDECTOUNEW, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFDetPupMis.tag = "FeedFDetPupMis";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	// IP constructor.cust1 --- IBEGIN
	ListIdecMMission miss;
	IdecMMission* mis = NULL;

	ubigint refMis;

	dbsidec->tblidecmmission->loadRstBySQL("SELECT * FROM TblIdecMMission ORDER BY startd ASC", false, miss);
	for (unsigned int i=0;i<miss.nodes.size();i++) {
		mis = miss.nodes[i];
		feedFDetPupMis.appendRefTitles(mis->ref, StubIdec::getStubMisStd(dbsidec, mis->ref));
	};

	refMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);
	if (refMis != 0) contiac.numFDetPupMis = feedFDetPupMis.getNumByRef(refMis);
	// IP constructor.cust1 --- IEND

	valid = false;

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

DlgIdecTouNew::~DlgIdecTouNew() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* DlgIdecTouNew::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFDetPupMis, &feedFSge, &statshr, items);
	};

	return dpcheng;
};

void DlgIdecTouNew::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);
	ContIac oldContiac(contiac);

	// IP refresh --- BEGIN
	// continf
	continf.numFSge = ixVSge;

	// statshr
	statshr.DetPupMisActive = evalDetPupMisActive(dbsidec);
	statshr.ButCncActive = evalButCncActive(dbsidec);
	statshr.ButCreActive = evalButCreActive(dbsidec);

	// contiac

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
};

void DlgIdecTouNew::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::CREATE: leaveSgeCreate(dbsidec); break;
				case VecVSge::DONE: leaveSgeDone(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::CREATE: _ixVSge = enterSgeCreate(dbsidec, reenter); break;
			case VecVSge::DONE: _ixVSge = enterSgeDone(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint DlgIdecTouNew::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void DlgIdecTouNew::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint DlgIdecTouNew::enterSgeCreate(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CREATE;
	nextIxVSge = VecVSge::DONE;
	// IP enterSgeCreate --- IBEGIN

	IdecMTour tou;

	tou.refIdecMMission = feedFDetPupMis.getRefByNum(contiac.numFDetPupMis);
	tou.Title = contiac.DetTxfTit;
	tou.start = xchg->getIntvalPreset(VecIdecVPreset::PREIDECSYSSTAMP, jref);
//	tou.stop = ;
	tou.Area = contiac.DetTxfAre;
	tou.theta = atof(contiac.DetTxfThe.c_str());
	tou.phi = atof(contiac.DetTxfPhi.c_str());
//	tou.Comment = ;

	dbsidec->tblidecmtour->insertRec(&tou);

	xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECTOUMOD, jref);
	xchg->triggerRefCall(dbsidec, VecIdecVCall::CALLIDECTOUMOD_MISEQ, jref, tou.refIdecMMission);
	xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFTOU, tou.ref);

	// IP enterSgeCreate --- IEND
	retval = nextIxVSge;
	return retval;
};

void DlgIdecTouNew::leaveSgeCreate(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeCreate --- INSERT
};

uint DlgIdecTouNew::enterSgeDone(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::DONE;
	nextIxVSge = retval;
	// IP enterSgeDone --- INSERT
	return retval;
};

void DlgIdecTouNew::leaveSgeDone(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeDone --- INSERT
};

string DlgIdecTouNew::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void DlgIdecTouNew::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTCNCCLICK) {
					handleDpchAppDoButCncClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCRECLICK) {
					handleDpchAppDoButCreClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void DlgIdecTouNew::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void DlgIdecTouNew::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	ubigint ref;

	double d;

	if (has(diffitems, ContIac::NUMFDETPUPMIS)) {
		if (feedFDetPupMis.getRefByNum(_contiac->numFDetPupMis) != 0) contiac.numFDetPupMis = _contiac->numFDetPupMis;
		else contiac.numFDetPupMis = 0;
	};

	if (has(diffitems, ContIac::DETTXFTIT)) {
		if (dbsidec->loadRefBySQL("SELECT ref FROM TblIdecMTour WHERE refIdecMMission = " + to_string(feedFDetPupMis.getRefByNum(contiac.numFDetPupMis)) + " AND Title = '" + _contiac->DetTxfTit + "'", ref)) contiac.DetTxfTit = "";
		else contiac.DetTxfTit = _contiac->DetTxfTit;
	};

	if (has(diffitems, ContIac::DETTXFARE)) contiac.DetTxfAre = _contiac->DetTxfAre;

	if (has(diffitems, ContIac::DETTXFTHE)) {
		if (_contiac->DetTxfThe.length() > 0) {
			d = atof(_contiac->DetTxfThe.c_str());
			contiac.DetTxfThe = to_string(d);
		} else contiac.DetTxfThe = "";
	};

	if (has(diffitems, ContIac::DETTXFPHI)) {
		if (_contiac->DetTxfPhi.length() > 0) {
			d = atof(_contiac->DetTxfPhi.c_str());
			contiac.DetTxfPhi = to_string(d);
		} else contiac.DetTxfPhi = "";
	};

	valid = ((contiac.numFDetPupMis > 0) && (contiac.DetTxfTit.length() > 0) && (contiac.DetTxfAre.length() > 0));

	refresh(dbsidec, moditems);

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void DlgIdecTouNew::handleDpchAppDoButCncClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCncClick --- IBEGIN
	if (statshr.ButCncActive) {
		*dpcheng = new DpchEngIdecConfirm(true, jref, "");
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECDLGCLOSE, jref);
	};
	// IP handleDpchAppDoButCncClick --- IEND
};

void DlgIdecTouNew::handleDpchAppDoButCreClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCreClick --- RBEGIN
	if (statshr.ButCreActive) {
		if (ixVSge == VecVSge::IDLE) {
			changeStage(dbsidec, VecVSge::CREATE);
		};

		if (ixVSge == VecVSge::DONE) {
			if (!*dpcheng) *dpcheng = new DpchEngIdecConfirm(true, jref, "");
			xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECDLGCLOSE, jref);
		};
	};
	// IP handleDpchAppDoButCreClick --- REND
};


