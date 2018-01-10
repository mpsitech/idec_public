/**
  * \file DlgIdecMisNew.cpp
  * job handler for job DlgIdecMisNew (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "DlgIdecMisNew.h"

#include "DlgIdecMisNew_blks.cpp"
#include "DlgIdecMisNew_evals.cpp"

/******************************************************************************
 class DlgIdecMisNew
 ******************************************************************************/

DlgIdecMisNew::DlgIdecMisNew(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::DLGIDECMISNEW, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFDetPupCry.tag = "FeedFDetPupCry";
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY, ixIdecVLocale, feedFDetPupCry);
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	// IP constructor.cust1 --- INSERT

	valid = false;

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

DlgIdecMisNew::~DlgIdecMisNew() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* DlgIdecMisNew::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFDetPupCry, &feedFSge, &statshr, items);
	};

	return dpcheng;
};

void DlgIdecMisNew::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.numFSge = ixVSge;

	// contiac

	// statshr
	statshr.ButCncActive = evalButCncActive(dbsidec);
	statshr.ButCreActive = evalButCreActive(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void DlgIdecMisNew::changeStage(
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

uint DlgIdecMisNew::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void DlgIdecMisNew::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint DlgIdecMisNew::enterSgeCreate(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CREATE;
	nextIxVSge = VecVSge::DONE;
	// IP enterSgeCreate --- IBEGIN

	IdecMMission mis;

	mis.grp = xchg->getRefPreset(VecIdecVPreset::PREIDECGRP, jref);
	mis.own = xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref);
	mis.Title = contiac.DetTxfTit;
	mis.startd = xchg->getIntvalPreset(VecIdecVPreset::PREIDECSYSDATE, jref);
//	mis.stopd = ;
	mis.srefKCountry = feedFDetPupCry.getSrefByNum(contiac.numFDetPupCry);
	mis.Region = contiac.DetTxfReg;
	mis.Municipality = contiac.DetTxfMun;
//	mis.Comment = ;

	dbsidec->tblidecmmission->insertRec(&mis);

	xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECMISMOD, jref);
	xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFMIS, mis.ref);

	// IP enterSgeCreate --- IEND
	retval = nextIxVSge;
	return retval;
};

void DlgIdecMisNew::leaveSgeCreate(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeCreate --- INSERT
};

uint DlgIdecMisNew::enterSgeDone(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::DONE;
	nextIxVSge = retval;
	// IP enterSgeDone --- INSERT
	return retval;
};

void DlgIdecMisNew::leaveSgeDone(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeDone --- INSERT
};

string DlgIdecMisNew::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void DlgIdecMisNew::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECMISNEWDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECMISNEWDO) {
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

void DlgIdecMisNew::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void DlgIdecMisNew::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN
	
	ubigint ref;

	if (has(diffitems, ContIac::DETTXFTIT)) {
		if (dbsidec->loadRefBySQL("SELECT ref FROM TblIdecMMission WHERE Title = '" + _contiac->DetTxfTit + "'", ref)) contiac.DetTxfTit = "";
		else contiac.DetTxfTit = _contiac->DetTxfTit;
	};

	if (has(diffitems, ContIac::NUMFDETPUPCRY)) {
		if (_contiac->numFDetPupCry <= feedFDetPupCry.size()) contiac.numFDetPupCry = _contiac->numFDetPupCry;
		else contiac.numFDetPupCry = 0;
	};

	if (has(diffitems, ContIac::DETTXFREG)) contiac.DetTxfReg = _contiac->DetTxfReg;
	if (has(diffitems, ContIac::DETTXFMUN)) contiac.DetTxfMun = _contiac->DetTxfMun;

	valid = (contiac.DetTxfTit.length() > 3);

	refresh(dbsidec, moditems);

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void DlgIdecMisNew::handleDpchAppDoButCncClick(
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

void DlgIdecMisNew::handleDpchAppDoButCreClick(
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


