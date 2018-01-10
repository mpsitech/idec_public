/**
  * \file PnlIdecIaqQcdsp.cpp
  * job handler for job PnlIdecIaqQcdsp (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecIaqQcdsp.h"

#include "PnlIdecIaqQcdsp_blks.cpp"
#include "PnlIdecIaqQcdsp_evals.cpp"

/******************************************************************************
 class PnlIdecIaqQcdsp
 ******************************************************************************/

PnlIdecIaqQcdsp::PnlIdecIaqQcdsp(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECIAQQCDSP, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiImgSte.tag = "FeedFCsiImgSte";
	feedFCsiImgSte.appendIxSrefTitles(VecIdecVQcdste::NC, "gry", VecIdecVQcdste::getTitle(VecIdecVQcdste::NC, ixIdecVLocale));
	feedFCsiImgSte.appendIxSrefTitles(VecIdecVQcdste::COOL, "ong", VecIdecVQcdste::getTitle(VecIdecVQcdste::COOL, ixIdecVLocale));
	feedFCsiImgSte.appendIxSrefTitles(VecIdecVQcdste::READY, "grn", VecIdecVQcdste::getTitle(VecIdecVQcdste::READY, ixIdecVLocale));
	feedFCsiImgSte.appendIxSrefTitles(VecIdecVQcdste::ACTIVE, "grn.fl", VecIdecVQcdste::getTitle(VecIdecVQcdste::ACTIVE, ixIdecVLocale));
	feedFPupMod.tag = "FeedFPupMod";
	VecVMode::fillFeed(ixIdecVLocale, feedFPupMod);

	joblwiracq = NULL;
	jobqcdacq = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecIaqQcdsp::~PnlIdecIaqQcdsp() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void PnlIdecIaqQcdsp::refreshLive(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);

	continf.TxtImgDxi = "0.0";
	continf.TxtImgDyi = "0.0";
	continf.numFCsiImgSte = feedFCsiImgSte.getNumByIx(xchg->datajobidecqcdacq.ixIdecVQcdste);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};
// IP cust --- IEND
DpchEngIdec* PnlIdecIaqQcdsp::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFCsiImgSte, &feedFPupMod, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecIaqQcdsp::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN

	// contiac
	ContIac oldContiac(contiac);

//	contiac.numFPupMod;
//	contiac.SldTin;
//	contiac.CusImgPxs;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (continf.ButMasterOn && joblwiracq) continf.ButMasterOn = (joblwiracq->jref == joblwiracq->jrefMast);
	if (continf.ButMasterOn && jobqcdacq) continf.ButMasterOn = (jobqcdacq->jref == jobqcdacq->jrefMast);

	continf.TxtImgIl0 = to_string(xchg->stgjobideclwiracq.lam0);
	continf.TxtImgIl1 = to_string(xchg->stgjobideclwiracq.lam1);
	continf.TxtImgQwh = to_string(xchg->stgjobidecqcdacq.width);
	continf.TxtImgQhp = to_string(xchg->stgjobidecqcdacq.hpix);
	continf.TxtImgQdp = to_string(xchg->stgjobidecqcdacq.dpix);
	continf.TxtImgSiq = to_string(xchg->stgjobideclwiracq.hpix*xchg->stgjobidecqcdacq.f/xchg->stgjobidecqcdacq.hpix/xchg->stgjobideclwiracq.f); // about 0.75
	continf.TxtImgQlm = to_string(xchg->stgjobidecqcdacq.lam0);
	continf.TxtImgQdl = to_string(xchg->stgjobidecqcdacq.dlam);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	refreshLive(dbsidec, moditems);

	// statshr
	statshr.PupModActive = evalPupModActive(dbsidec);

	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecIaqQcdsp::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQQCDSPDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQQCDSPDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecIaqQcdsp::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecIaqQcdsp::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	if (has(diffitems, ContIac::NUMFPUPMOD)) contiac.numFPupMod = _contiac->numFPupMod;
	if (has(diffitems, ContIac::SLDTIN)) contiac.SldTin = _contiac->SldTin;
	if (has(diffitems, ContIac::CUSIMGPXS)) contiac.CusImgPxs = _contiac->CusImgPxs;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecIaqQcdsp::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButRegularizeClick --- BEGIN
	statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
	*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	// IP handleDpchAppDoButRegularizeClick --- END
};

void PnlIdecIaqQcdsp::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMinimizeClick --- BEGIN
	statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
	*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	// IP handleDpchAppDoButMinimizeClick --- END
};

void PnlIdecIaqQcdsp::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (joblwiracq) if (joblwiracq->jref != joblwiracq->jrefMast) xchg->claimMaster(dbsidec, joblwiracq->jref);
	if (jobqcdacq) if (jobqcdacq->jref != jobqcdacq->jrefMast) xchg->claimMaster(dbsidec, jobqcdacq->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecIaqQcdsp::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecIaqQcdsp::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- IBEGIN
	if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) {
	};
	// IP handleCallIdecImgrdy --- IEND
	return retval;
};

bool PnlIdecIaqQcdsp::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool PnlIdecIaqQcdsp::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


