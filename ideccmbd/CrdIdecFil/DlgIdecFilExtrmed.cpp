/**
  * \file DlgIdecFilExtrmed.cpp
  * job handler for job DlgIdecFilExtrmed (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "DlgIdecFilExtrmed.h"

#include "DlgIdecFilExtrmed_blks.cpp"

/******************************************************************************
 class DlgIdecFilExtrmed
 ******************************************************************************/

DlgIdecFilExtrmed::DlgIdecFilExtrmed(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::DLGIDECFILEXTRMED, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFDse.tag = "FeedFDse";
	VecVDit::fillFeed(ixIdecVLocale, feedFDse);
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	// IP constructor.cust1 --- INSERT

	ixVDit = VecVDit::PVW;

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

DlgIdecFilExtrmed::~DlgIdecFilExtrmed() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* DlgIdecFilExtrmed::getNewDpchEng(
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

void DlgIdecFilExtrmed::refreshPvw(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {

	// IP refreshPvw --- BEGIN
	// IP refreshPvw --- END
};

void DlgIdecFilExtrmed::refreshSel(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {

	// IP refreshSel --- BEGIN
	// IP refreshSel --- END
};

void DlgIdecFilExtrmed::refreshFia(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {

	// IP refreshFia --- BEGIN
	// IP refreshFia --- END
};

void DlgIdecFilExtrmed::refresh(
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

	refreshPvw(dbsidec, moditems);
	refreshSel(dbsidec, moditems);
	refreshFia(dbsidec, moditems);
};

void DlgIdecFilExtrmed::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECFILEXTRMEDDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECFILEXTRMEDDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTDNECLICK) {
					handleDpchAppDoButDneClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void DlgIdecFilExtrmed::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void DlgIdecFilExtrmed::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (has(diffitems, ContIac::NUMFDSE)) {
		if ((_contiac->numFDse >= VecVDit::PVW) && (_contiac->numFDse <= VecVDit::FIA)) ixVDit = _contiac->numFDse;
		refresh(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void DlgIdecFilExtrmed::handleDpchAppDoButDneClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDneClick --- IBEGIN
	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECDLGCLOSE, jref);
	// IP handleDpchAppDoButDneClick --- IEND
};


