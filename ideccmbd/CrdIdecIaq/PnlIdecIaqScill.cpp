/**
  * \file PnlIdecIaqScill.cpp
  * job handler for job PnlIdecIaqScill (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecIaqScill.h"

#include "PnlIdecIaqScill_blks.cpp"
#include "PnlIdecIaqScill_evals.cpp"

/******************************************************************************
 class PnlIdecIaqScill
 ******************************************************************************/

PnlIdecIaqScill::PnlIdecIaqScill(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECIAQSCILL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupMod.tag = "FeedFPupMod";
	VecVMode::fillFeed(ixIdecVLocale, feedFPupMod);

	jobillum = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobillum = new JobIdecIllum(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecIaqScill::~PnlIdecIaqScill() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecIaqScill::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupMod, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecIaqScill::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN

	// contiac
	ContIac oldContiac(contiac);

//	contiac.numFPupMod;
//	contiac.SldThr;

	contiac.SldFld = xchg->datajobidecillum.pFlood;
	contiac.SldSpt = xchg->datajobidecillum.pSpot;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (continf.ButMasterOn && jobillum) continf.ButMasterOn = (jobillum->jref == jobillum->jrefMast);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.PupModActive = evalPupModActive(dbsidec);
	//statshr.SldThrAvail = CUSTOM;
	statshr.SldThrActive = evalSldThrActive(dbsidec);
	statshr.SldFldActive = evalSldFldActive(dbsidec);
	statshr.SldSptActive = evalSldSptActive(dbsidec);

	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecIaqScill::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQSCILLDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQSCILLDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecIaqScill::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecIaqScill::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	muteRefresh = true;

	if (has(diffitems, ContIac::NUMFPUPMOD)) contiac.numFPupMod = _contiac->numFPupMod;
	if (has(diffitems, ContIac::SLDTHR)) contiac.SldThr = _contiac->SldThr;

	if (has(diffitems, ContIac::SLDFLD)) jobillum->setPFlood(dbsidec, _contiac->SldFld);
	if (has(diffitems, ContIac::SLDSPT)) jobillum->setPSpot(dbsidec, _contiac->SldSpt);

///
		contiac.SldSpt = _contiac->SldSpt;
///

	refresh(dbsidec, moditems);

	muteRefresh = false;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecIaqScill::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobillum) if (jobillum->jref != jobillum->jrefMast) xchg->claimMaster(dbsidec, jobillum->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecIaqScill::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecIaqScill::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecStatChg --- IEND
	return retval;
};

bool PnlIdecIaqScill::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


