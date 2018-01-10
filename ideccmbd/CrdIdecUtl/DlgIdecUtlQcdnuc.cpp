/**
  * \file DlgIdecUtlQcdnuc.cpp
  * job handler for job DlgIdecUtlQcdnuc (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "DlgIdecUtlQcdnuc.h"

#include "DlgIdecUtlQcdnuc_blks.cpp"

/******************************************************************************
 class DlgIdecUtlQcdnuc
 ******************************************************************************/

DlgIdecUtlQcdnuc::DlgIdecUtlQcdnuc(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::DLGIDECUTLQCDNUC, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFDse.tag = "FeedFDse";
	VecVDit::fillFeed(ixIdecVLocale, feedFDse);
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	joblwiracq = NULL;
	jobqcdacq = NULL;
	jobspotfind = NULL;
	jobtrigger = NULL;

	// IP constructor.cust1 --- INSERT

	ixVDit = VecVDit::PRP;

	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobspotfind = new JobIdecSpotfind(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

DlgIdecUtlQcdnuc::~DlgIdecUtlQcdnuc() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* DlgIdecUtlQcdnuc::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFDse, &feedFSge, items);
	};

	return dpcheng;
};

void DlgIdecUtlQcdnuc::refreshPrp(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {

	// IP refreshPrp --- BEGIN
	// IP refreshPrp --- END
};

void DlgIdecUtlQcdnuc::refreshCal(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {

	// IP refreshCal --- BEGIN
	// IP refreshCal --- END
};

void DlgIdecUtlQcdnuc::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	ContIac oldContiac(contiac);

	// IP refresh --- BEGIN
	// continf
	continf.numFSge = ixVSge;

	// contiac
	contiac.numFDse = ixVDit;

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	refreshPrp(dbsidec, moditems);
	refreshCal(dbsidec, moditems);
};

void DlgIdecUtlQcdnuc::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDNUCDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDNUCDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTDNECLICK) {
					handleDpchAppDoButDneClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void DlgIdecUtlQcdnuc::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void DlgIdecUtlQcdnuc::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (has(diffitems, ContIac::NUMFDSE)) {
		if ((_contiac->numFDse >= VecVDit::PRP) && (_contiac->numFDse <= VecVDit::CAL)) ixVDit = _contiac->numFDse;
		refresh(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void DlgIdecUtlQcdnuc::handleDpchAppDoButDneClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDneClick --- INSERT
};

void DlgIdecUtlQcdnuc::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool DlgIdecUtlQcdnuc::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};

