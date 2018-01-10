/**
  * \file PnlIdecScfOptics.cpp
  * job handler for job PnlIdecScfOptics (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecScfOptics.h"

#include "PnlIdecScfOptics_blks.cpp"
#include "PnlIdecScfOptics_evals.cpp"

/******************************************************************************
 class PnlIdecScfOptics
 ******************************************************************************/

PnlIdecScfOptics::PnlIdecScfOptics(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECSCFOPTICS, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupIsg.tag = "FeedFPupIsg";
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R0, feedFPupIsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R2, feedFPupIsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S0, feedFPupIsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S2, feedFPupIsg);
	feedFPupLsg.tag = "FeedFPupLsg";
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R0, feedFPupLsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R2, feedFPupLsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S0, feedFPupLsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S2, feedFPupLsg);
	feedFPupQsg.tag = "FeedFPupQsg";
	VecIdecVSqrgrp::fillFeed(feedFPupQsg);
	feedFPupRsg.tag = "FeedFPupRsg";
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R0, feedFPupRsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::R2, feedFPupRsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S0, feedFPupRsg);
	VecIdecVSqrgrp::appendToFeed(VecIdecVSqrgrp::S2, feedFPupRsg);

	jobfusion = NULL;
	joblwiracq = NULL;
	jobqcdacq = NULL;
	jobstereo = NULL;
	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobfusion = new JobIdecFusion(xchg, dbsidec, jref, ixIdecVLocale, true);
	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobstereo = new JobIdecStereo(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobvisracq = new JobIdecVisracq(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecScfOptics::~PnlIdecScfOptics() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecScfOptics::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupIsg, &feedFPupLsg, &feedFPupQsg, &feedFPupRsg, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecScfOptics::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	// contiac
	ContIac oldContiac(contiac);

	contiac.TxfDst = to_string(xchg->stgjobidecstereo.dstereo);
	contiac.TxfIdx = to_string(xchg->stgjobidecfusion.dxlwir);
	contiac.TxfIdy = to_string(xchg->stgjobidecfusion.dylwir);
	contiac.TxfQdx = to_string(xchg->stgjobidecqcdacq.dxqcd);
	contiac.TxfQdy = to_string(xchg->stgjobidecqcdacq.dyqcd);
	contiac.TxfAdx = to_string(xchg->stgjobidecqcdacq.dxalign);
	contiac.TxfAdy = to_string(xchg->stgjobidecqcdacq.dyalign);
	contiac.numFPupLsg = feedFPupLsg.getNumByIx(xchg->stgjobidecvislacq.ixIdecVSqrgrp);
	contiac.numFPupRsg = feedFPupRsg.getNumByIx(xchg->stgjobidecvisracq.ixIdecVSqrgrp);
	contiac.numFPupIsg = feedFPupIsg.getNumByIx(xchg->stgjobideclwiracq.ixIdecVSqrgrp);
	contiac.UpdQwh = xchg->stgjobidecqcdacq.width;
	contiac.TxfQhp = to_string(xchg->stgjobidecqcdacq.hpix);
	contiac.TxfQdp = to_string(xchg->stgjobidecqcdacq.dpix);
	contiac.TxfQfl = to_string(xchg->stgjobidecqcdacq.f);
	contiac.TxfQfn = to_string(xchg->stgjobidecqcdacq.fn);
	contiac.numFPupQsg = feedFPupQsg.getNumByIx(xchg->stgjobidecqcdacq.ixIdecVSqrgrp);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (jobfusion) continf.ButMasterOn = (jobfusion->jref == jobfusion->jrefMast);
	if (continf.ButMasterOn && joblwiracq) continf.ButMasterOn = (joblwiracq->jref == joblwiracq->jrefMast);
	if (continf.ButMasterOn && jobqcdacq) continf.ButMasterOn = (jobqcdacq->jref == jobqcdacq->jrefMast);
	if (continf.ButMasterOn && jobstereo) continf.ButMasterOn = (jobstereo->jref == jobstereo->jrefMast);
	if (continf.ButMasterOn && jobvislacq) continf.ButMasterOn = (jobvislacq->jref == jobvislacq->jrefMast);
	if (continf.ButMasterOn && jobvisracq) continf.ButMasterOn = (jobvisracq->jref == jobvisracq->jrefMast);

	continf.TxtVwi = to_string(xchg->stgjobidecvislacq.width);
	continf.TxtVhe = to_string(xchg->stgjobidecvislacq.height);
	continf.TxtVhp = to_string(xchg->stgjobidecvislacq.hpix);
	continf.TxtVfl = to_string(xchg->stgjobidecvislacq.f);
	continf.TxtVfn = to_string(xchg->stgjobidecvislacq.fn);
	continf.TxtIwi = to_string(xchg->stgjobideclwiracq.width);
	continf.TxtIhe = to_string(xchg->stgjobideclwiracq.height);
	continf.TxtIhp = to_string(xchg->stgjobideclwiracq.hpix);
	continf.TxtIfl = to_string(xchg->stgjobideclwiracq.f);
	continf.TxtIfn = to_string(xchg->stgjobideclwiracq.fn);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.TxfDstActive = evalTxfDstActive(dbsidec);
	statshr.TxfIdxActive = evalTxfIdxActive(dbsidec);
	statshr.TxfIdyActive = evalTxfIdyActive(dbsidec);
	statshr.TxfQdxActive = evalTxfQdxActive(dbsidec);
	statshr.TxfQdyActive = evalTxfQdyActive(dbsidec);
	statshr.TxfAdxActive = evalTxfAdxActive(dbsidec);
	statshr.TxfAdyActive = evalTxfAdyActive(dbsidec);
	statshr.PupLsgActive = evalPupLsgActive(dbsidec);
	statshr.PupRsgActive = evalPupRsgActive(dbsidec);
	statshr.PupIsgActive = evalPupIsgActive(dbsidec);
	statshr.UpdQwhActive = evalUpdQwhActive(dbsidec);
	statshr.TxfQhpActive = evalTxfQhpActive(dbsidec);
	statshr.TxfQdpActive = evalTxfQdpActive(dbsidec);
	statshr.TxfQflActive = evalTxfQflActive(dbsidec);
	statshr.TxfQfnActive = evalTxfQfnActive(dbsidec);
	statshr.PupQsgActive = evalPupQsgActive(dbsidec);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfOptics::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFOPTICSDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFOPTICSDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecScfOptics::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecScfOptics::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	if (has(diffitems, ContIac::TXFDST)) contiac.TxfDst = _contiac->TxfDst;
	if (has(diffitems, ContIac::TXFIDX)) contiac.TxfIdx = _contiac->TxfIdx;
	if (has(diffitems, ContIac::TXFIDY)) contiac.TxfIdy = _contiac->TxfIdy;
	if (has(diffitems, ContIac::TXFQDX)) contiac.TxfQdx = _contiac->TxfQdx;
	if (has(diffitems, ContIac::TXFQDY)) contiac.TxfQdy = _contiac->TxfQdy;
	if (has(diffitems, ContIac::TXFADX)) contiac.TxfAdx = _contiac->TxfAdx;
	if (has(diffitems, ContIac::TXFADY)) contiac.TxfAdy = _contiac->TxfAdy;

	if (has(diffitems, ContIac::NUMFPUPLSG)) {
		// preliminary
		contiac.numFPupLsg = _contiac->numFPupLsg;
		jobvislacq->changeSqrgrp(feedFPupLsg.getIxByNum(contiac.numFPupLsg));
	};

	if (has(diffitems, ContIac::NUMFPUPRSG)) {
		// preliminary
		contiac.numFPupRsg = _contiac->numFPupRsg;
		jobvisracq->changeSqrgrp(feedFPupRsg.getIxByNum(contiac.numFPupRsg));
	};

	if (has(diffitems, ContIac::NUMFPUPISG)) contiac.numFPupIsg = _contiac->numFPupIsg;
	if (has(diffitems, ContIac::UPDQWH)) contiac.UpdQwh = _contiac->UpdQwh;
	if (has(diffitems, ContIac::TXFQHP)) contiac.TxfQhp = _contiac->TxfQhp;
	if (has(diffitems, ContIac::TXFQDP)) contiac.TxfQdp = _contiac->TxfQdp;
	if (has(diffitems, ContIac::TXFQFL)) contiac.TxfQfl = _contiac->TxfQfl;
	if (has(diffitems, ContIac::TXFQFN)) contiac.TxfQfn = _contiac->TxfQfn;
	if (has(diffitems, ContIac::NUMFPUPQSG)) contiac.numFPupQsg = _contiac->numFPupQsg;

	refresh(dbsidec, moditems);

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecScfOptics::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobfusion) if (jobfusion->jref != jobfusion->jrefMast) xchg->claimMaster(dbsidec, jobfusion->jref);
	if (joblwiracq) if (joblwiracq->jref != joblwiracq->jrefMast) xchg->claimMaster(dbsidec, joblwiracq->jref);
	if (jobqcdacq) if (jobqcdacq->jref != jobqcdacq->jrefMast) xchg->claimMaster(dbsidec, jobqcdacq->jref);
	if (jobstereo) if (jobstereo->jref != jobstereo->jrefMast) xchg->claimMaster(dbsidec, jobstereo->jref);
	if (jobvislacq) if (jobvislacq->jref != jobvislacq->jrefMast) xchg->claimMaster(dbsidec, jobvislacq->jref);
	if (jobvisracq) if (jobvisracq->jref != jobvisracq->jrefMast) xchg->claimMaster(dbsidec, jobvisracq->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecScfOptics::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecScfOptics::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool PnlIdecScfOptics::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


