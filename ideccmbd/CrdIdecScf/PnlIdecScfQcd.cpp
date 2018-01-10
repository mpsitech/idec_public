/**
  * \file PnlIdecScfQcd.cpp
  * job handler for job PnlIdecScfQcd (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecScfQcd.h"

#include "PnlIdecScfQcd_blks.cpp"
#include "PnlIdecScfQcd_evals.cpp"

/******************************************************************************
 class PnlIdecScfQcd
 ******************************************************************************/

PnlIdecScfQcd::PnlIdecScfQcd(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECSCFQCD, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupFan.tag = "FeedFPupFan";
	VecVJobIdecQcdacqFan::fillFeed(ixIdecVLocale, feedFPupFan);

	jobqcdacq = NULL;
	jobspotfind = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobspotfind = new JobIdecSpotfind(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecScfQcd::~PnlIdecScfQcd() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecScfQcd::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupFan, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecScfQcd::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	// contiac
	ContIac oldContiac(contiac);

	contiac.TxfLam = to_string(xchg->stgjobidecqcdacq.lam0);
	contiac.TxfDlm = to_string(xchg->stgjobidecqcdacq.dlam);
	contiac.ChkAon = xchg->stgjobidecqcdacq.on;
	contiac.SldTof = xchg->stgjobidecqcdacq.tturnoff;
	contiac.SldTmp = xchg->stgjobidecqcdacq.Tdet;
	contiac.numFPupFan = feedFPupFan.getNumByIx(xchg->stgjobidecqcdacq.ixVFan);
	contiac.SldFmd = xchg->stgjobidecqcdacq.Tdet;
	contiac.SldVdd = xchg->stgjobidecqcdacq.Vdd;
//	contiac.ChkVd2;
	contiac.SldVrf = xchg->stgjobidecqcdacq.Vref;
	contiac.UpdAsl = xchg->stgjobidecspotfind.seqlen;
	contiac.SldAmo = xchg->stgjobidecspotfind.Pmax;
	contiac.ChkAad = xchg->stgjobidecspotfind.adapt;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (jobqcdacq) continf.ButMasterOn = (jobqcdacq->jref == jobqcdacq->jrefMast);
	if (continf.ButMasterOn && jobspotfind) continf.ButMasterOn = (jobspotfind->jref == jobspotfind->jrefMast);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.TxfLamActive = evalTxfLamActive(dbsidec);
	statshr.TxfDlmActive = evalTxfDlmActive(dbsidec);
	statshr.ChkAonActive = evalChkAonActive(dbsidec);
	statshr.SldTofActive = evalSldTofActive(dbsidec);
	statshr.SldTmpActive = evalSldTmpActive(dbsidec);
	statshr.PupFanActive = evalPupFanActive(dbsidec);
	statshr.SldFmdActive = evalSldFmdActive(dbsidec);
	statshr.SldVddActive = evalSldVddActive(dbsidec);
	statshr.ChkVd2Active = evalChkVd2Active(dbsidec);
	statshr.SldVrfActive = evalSldVrfActive(dbsidec);
	statshr.UpdAslActive = evalUpdAslActive(dbsidec);
	statshr.SldAmoActive = evalSldAmoActive(dbsidec);
	statshr.ChkAadActive = evalChkAadActive(dbsidec);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfQcd::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFQCDDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFQCDDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecScfQcd::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecScfQcd::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	if (has(diffitems, ContIac::TXFLAM)) contiac.TxfLam = _contiac->TxfLam;
	if (has(diffitems, ContIac::TXFDLM)) contiac.TxfDlm = _contiac->TxfDlm;
	if (has(diffitems, ContIac::CHKAON)) contiac.ChkAon = _contiac->ChkAon;
	if (has(diffitems, ContIac::SLDTOF)) contiac.SldTof = _contiac->SldTof;
	if (has(diffitems, ContIac::SLDTMP)) contiac.SldTmp = _contiac->SldTmp;
	if (has(diffitems, ContIac::NUMFPUPFAN)) contiac.numFPupFan = _contiac->numFPupFan;
	if (has(diffitems, ContIac::SLDFMD)) contiac.SldFmd = _contiac->SldFmd;
	if (has(diffitems, ContIac::SLDVDD)) contiac.SldVdd = _contiac->SldVdd;
	if (has(diffitems, ContIac::CHKVD2)) contiac.ChkVd2 = _contiac->ChkVd2;
	if (has(diffitems, ContIac::SLDVRF)) contiac.SldVrf = _contiac->SldVrf;
	if (has(diffitems, ContIac::UPDASL)) contiac.UpdAsl = _contiac->UpdAsl;
	if (has(diffitems, ContIac::SLDAMO)) contiac.SldAmo = _contiac->SldAmo;
	if (has(diffitems, ContIac::CHKAAD)) contiac.ChkAad = _contiac->ChkAad;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecScfQcd::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobqcdacq) if (jobqcdacq->jref != jobqcdacq->jrefMast) xchg->claimMaster(dbsidec, jobqcdacq->jref);
	if (jobspotfind) if (jobspotfind->jref != jobspotfind->jrefMast) xchg->claimMaster(dbsidec, jobspotfind->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecScfQcd::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecScfQcd::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool PnlIdecScfQcd::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


