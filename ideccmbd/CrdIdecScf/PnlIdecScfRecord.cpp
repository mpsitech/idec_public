/**
  * \file PnlIdecScfRecord.cpp
  * job handler for job PnlIdecScfRecord (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecScfRecord.h"

#include "PnlIdecScfRecord_blks.cpp"
#include "PnlIdecScfRecord_evals.cpp"

/******************************************************************************
 class PnlIdecScfRecord
 ******************************************************************************/

PnlIdecScfRecord::PnlIdecScfRecord(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECSCFRECORD, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupFir.tag = "FeedFPupFir";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupFir);
	feedFPupFlr.tag = "FeedFPupFlr";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupFlr);
	feedFPupFrr.tag = "FeedFPupFrr";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupFrr);
	feedFPupOwr.tag = "FeedFPupOwr";
	VecVJobIdecRecordOverwrite::fillFeed(ixIdecVLocale, feedFPupOwr);
	feedFPupVir.tag = "FeedFPupVir";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupVir);
	feedFPupVlr.tag = "FeedFPupVlr";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupVlr);
	feedFPupVrr.tag = "FeedFPupVrr";
	VecIdecVCamres::fillFeed(ixIdecVLocale, feedFPupVrr);

	jobrecord = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobrecord = new JobIdecRecord(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecScfRecord::~PnlIdecScfRecord() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecScfRecord::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupFir, &feedFPupFlr, &feedFPupFrr, &feedFPupOwr, &feedFPupVir, &feedFPupVlr, &feedFPupVrr, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecScfRecord::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// statshr
	statshr.PupFlrActive = evalPupFlrActive(dbsidec);
	statshr.ChkFlgActive = evalChkFlgActive(dbsidec);
	statshr.PupFrrActive = evalPupFrrActive(dbsidec);
	statshr.ChkFrgActive = evalChkFrgActive(dbsidec);
	statshr.PupFirActive = evalPupFirActive(dbsidec);
	statshr.ChkFqcActive = evalChkFqcActive(dbsidec);
	statshr.ChkFstActive = evalChkFstActive(dbsidec);
	statshr.SldVfrActive = evalSldVfrActive(dbsidec);
	statshr.PupVlrActive = evalPupVlrActive(dbsidec);
	statshr.ChkVlgActive = evalChkVlgActive(dbsidec);
	statshr.PupVrrActive = evalPupVrrActive(dbsidec);
	statshr.ChkVrgActive = evalChkVrgActive(dbsidec);
	statshr.PupVirActive = evalPupVirActive(dbsidec);
	statshr.ChkVqcActive = evalChkVqcActive(dbsidec);
	statshr.ChkVstActive = evalChkVstActive(dbsidec);
	statshr.PupOwrActive = evalPupOwrActive(dbsidec);
	// IP refresh --- END

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfRecord::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFRECORDDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFRECORDDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecScfRecord::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecScfRecord::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	if (has(diffitems, ContIac::NUMFPUPFLR)) contiac.numFPupFlr = _contiac->numFPupFlr;
	if (has(diffitems, ContIac::CHKFLG)) contiac.ChkFlg = _contiac->ChkFlg;
	if (has(diffitems, ContIac::NUMFPUPFRR)) contiac.numFPupFrr = _contiac->numFPupFrr;
	if (has(diffitems, ContIac::CHKFRG)) contiac.ChkFrg = _contiac->ChkFrg;
	if (has(diffitems, ContIac::NUMFPUPFIR)) contiac.numFPupFir = _contiac->numFPupFir;
	if (has(diffitems, ContIac::CHKFQC)) contiac.ChkFqc = _contiac->ChkFqc;
	if (has(diffitems, ContIac::CHKFST)) contiac.ChkFst = _contiac->ChkFst;
	if (has(diffitems, ContIac::SLDVFR)) contiac.SldVfr = _contiac->SldVfr;
	if (has(diffitems, ContIac::NUMFPUPVLR)) contiac.numFPupVlr = _contiac->numFPupVlr;
	if (has(diffitems, ContIac::CHKVLG)) contiac.ChkVlg = _contiac->ChkVlg;
	if (has(diffitems, ContIac::NUMFPUPVRR)) contiac.numFPupVrr = _contiac->numFPupVrr;
	if (has(diffitems, ContIac::CHKVRG)) contiac.ChkVrg = _contiac->ChkVrg;
	if (has(diffitems, ContIac::NUMFPUPVIR)) contiac.numFPupVir = _contiac->numFPupVir;
	if (has(diffitems, ContIac::CHKVQC)) contiac.ChkVqc = _contiac->ChkVqc;
	if (has(diffitems, ContIac::CHKVST)) contiac.ChkVst = _contiac->ChkVst;
	if (has(diffitems, ContIac::NUMFPUPOWR)) contiac.numFPupOwr = _contiac->numFPupOwr;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecScfRecord::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobrecord) if (jobrecord->jref != jobrecord->jrefMast) xchg->claimMaster(dbsidec, jobrecord->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecScfRecord::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecScfRecord::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool PnlIdecScfRecord::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN

	if (!muteRefresh) refreshWithDpchEng(dbsidec);

	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


