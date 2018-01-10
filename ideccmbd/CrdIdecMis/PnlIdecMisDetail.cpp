/**
  * \file PnlIdecMisDetail.cpp
  * job handler for job PnlIdecMisDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecMisDetail.h"

#include "PnlIdecMisDetail_blks.cpp"
#include "PnlIdecMisDetail_evals.cpp"

/******************************************************************************
 class PnlIdecMisDetail
 ******************************************************************************/

PnlIdecMisDetail::PnlIdecMisDetail(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECMISDETAIL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupCry.tag = "FeedFPupCry";
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY, ixIdecVLocale, feedFPupCry);

	// IP constructor.cust1 --- INSERT

	dirty = false;

	// IP constructor.cust2 --- INSERT

	// IP constructor.cust3 --- INSERT

	xchg->addIxClstn(VecIdecVCall::CALLIDECKLSAKEYMOD_KLSEQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY, Clstn::VecVJactype::LOCK);

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFMIS, jref);
};

PnlIdecMisDetail::~PnlIdecMisDetail() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecMisDetail::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &feedFPupCry, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecMisDetail::refreshPupCry(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupCry = 0;

	for (unsigned int i=0;i<feedFPupCry.size();i++) {
		if (feedFPupCry.getSrefByNum(i+1) == contiac.TxfCry) {
			contiac.numFPupCry = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfCryValid = (contiac.numFPupCry != 0);
	statshr.PupCryActive = evalPupCryActive(dbsidec);
	statshr.ButCryEditAvail = evalButCryEditAvail(dbsidec);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecMisDetail::refreshTxfCry(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfCry = feedFPupCry.getSrefByNum(contiac.numFPupCry);

	// statshr
	statshr.TxfCryValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecMisDetail::refreshCry(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	// feedFPupCry
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY, ixIdecVLocale, feedFPupCry);

	insert(moditems, DpchEngData::FEEDFPUPCRY);

	refreshPupCry(dbsidec, moditems);
};

void PnlIdecMisDetail::refreshRecMis(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	IdecMMission* _recMis = NULL;

	if (dbsidec->tblidecmmission->loadRecByRef(recMis.ref, &_recMis)) {
		recMis = *_recMis;
		delete _recMis;
	} else recMis = IdecMMission();

	dirty = false;

	contiac.TxfTit = recMis.Title;
	contiac.TxfSta = Ftm::date(recMis.startd);
	contiac.TxfSto = Ftm::date(recMis.stopd);
	contiac.TxfCry = recMis.srefKCountry;
	contiac.TxfReg = recMis.Region;
	contiac.TxfMun = recMis.Municipality;
	contiac.TxfCmt = recMis.Comment;

	statshr.TxfTitActive = evalTxfTitActive(dbsidec);
	statshr.TxfStaActive = evalTxfStaActive(dbsidec);
	statshr.TxfStoActive = evalTxfStoActive(dbsidec);
	statshr.TxfRegActive = evalTxfRegActive(dbsidec);
	statshr.TxfMunActive = evalTxfMunActive(dbsidec);
	statshr.TxfCmtActive = evalTxfCmtActive(dbsidec);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

	refreshPupCry(dbsidec, moditems);

};

void PnlIdecMisDetail::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// statshr
	statshr.ButSaveAvail = evalButSaveAvail(dbsidec);
	statshr.ButSaveActive = evalButSaveActive(dbsidec);
	// IP refresh --- END

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecMisDetail::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFMIS) {
		recMis.ref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);
		refreshRecMis(dbsidec, moditems);

		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecMisDetail::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISDETAILDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISDETAILDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTSAVECLICK) {
					handleDpchAppDoButSaveClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCRYEDITCLICK) {
					handleDpchAppDoButCryEditClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecMisDetail::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecMisDetail::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (hasAny(diffitems, {ContIac::TXFTIT, ContIac::TXFSTA, ContIac::TXFSTO, ContIac::TXFREG, ContIac::TXFMUN, ContIac::TXFCMT})) {
		if (has(diffitems, ContIac::TXFTIT)) contiac.TxfTit = _contiac->TxfTit;
		if (has(diffitems, ContIac::TXFSTA)) contiac.TxfSta = _contiac->TxfSta;
		if (has(diffitems, ContIac::TXFSTO)) contiac.TxfSto = _contiac->TxfSto;
		if (has(diffitems, ContIac::TXFREG)) contiac.TxfReg = _contiac->TxfReg;
		if (has(diffitems, ContIac::TXFMUN)) contiac.TxfMun = _contiac->TxfMun;
		if (has(diffitems, ContIac::TXFCMT)) contiac.TxfCmt = _contiac->TxfCmt;
	};

	if (has(diffitems, ContIac::TXFCRY)) {
		contiac.TxfCry = _contiac->TxfCry;
		refreshPupCry(dbsidec, moditems);
	} else if (has(diffitems, ContIac::NUMFPUPCRY)) {
		contiac.numFPupCry = _contiac->numFPupCry;
		refreshTxfCry(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecMisDetail::handleDpchAppDoButSaveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSaveClick --- INSERT
};

void PnlIdecMisDetail::handleDpchAppDoButCryEditClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCryEditClick --- INSERT
};

void PnlIdecMisDetail::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECMISUPD_REFEQ) {
		call->abort = handleCallIdecMisUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECKLSAKEYMOD_KLSEQ) {
		call->abort = handleCallIdecKlsAkeyMod_klsEq(dbsidec, call->jref, call->argInv.ix);
	};
};

bool PnlIdecMisDetail::handleCallIdecMisUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecMisUpd_refEq --- INSERT
	return retval;
};

bool PnlIdecMisDetail::handleCallIdecKlsAkeyMod_klsEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
		) {
	bool retval = false;
	set<uint> moditems;

	if (ixInv == VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY) {
		refreshCry(dbsidec, moditems);
	};

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

