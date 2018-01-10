/**
  * \file PnlIdecMis1NTour.cpp
  * job handler for job PnlIdecMis1NTour (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecMis1NTour.h"

#include "PnlIdecMis1NTour_blks.cpp"
#include "PnlIdecMis1NTour_evals.cpp"

/******************************************************************************
 class PnlIdecMis1NTour
 ******************************************************************************/

PnlIdecMis1NTour::PnlIdecMis1NTour(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECMIS1NTOUR, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiQst.tag = "FeedFCsiQst";
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::MNR, "ong", VecIdecVQrystate::getTitle(VecIdecVQrystate::MNR, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::OOD, "red", VecIdecVQrystate::getTitle(VecIdecVQrystate::OOD, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::SLM, "yel", VecIdecVQrystate::getTitle(VecIdecVQrystate::SLM, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::UTD, "grn", VecIdecVQrystate::getTitle(VecIdecVQrystate::UTD, ixIdecVLocale));

	qry = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, 0);

	qry = new QryIdecMis1NTour(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecMis1NTour::~PnlIdecMis1NTour() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecMis1NTour::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &continf, &feedFCsiQst, &statshr, &stgiac, &(qry->rst), &(qry->statshr), &(qry->stgiac), items);
	};

	return dpcheng;
};

void PnlIdecMis1NTour::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.numFCsiQst = feedFCsiQst.getNumByIx(qry->ixIdecVQrystate);

	// statshr
	statshr.ButViewAvail = evalButViewAvail(dbsidec);
	statshr.ButViewActive = evalButViewActive(dbsidec);
	statshr.ButNewAvail = evalButNewAvail(dbsidec);
	statshr.ButDeleteAvail = evalButDeleteAvail(dbsidec);
	statshr.ButDeleteActive = evalButDeleteActive(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecMis1NTour::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFMIS) {
		recTou = IdecMTour();

		xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, 0);

		qry->stgiac.jnumFirstload = 1;

		qry->rerun(dbsidec);
		refresh(dbsidec, moditems);

		if (notif) {
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::STGIACQRY, DpchEngData::RST});
			xchg->submitDpch(getNewDpchEng(moditems));
		};
	};
	// IP updatePreset --- END
};

void PnlIdecMis1NTour::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMIS1NTOURDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::STGIAC)) {
				handleDpchAppDataStgiac(dbsidec, &(dpchappdata->stgiac), &(req->dpcheng));
			} else if (dpchappdata->has(DpchAppData::STGIACQRY)) {
				handleDpchAppDataStgiacqry(dbsidec, &(dpchappdata->stgiacqry), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMIS1NTOURDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTVIEWCLICK) {
					handleDpchAppDoButViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTNEWCLICK) {
					handleDpchAppDoButNewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTDELETECLICK) {
					handleDpchAppDoButDeleteClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREFRESHCLICK) {
					handleDpchAppDoButRefreshClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecMis1NTour::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecMis1NTour::handleDpchAppDataStgiac(
			DbsIdec* dbsidec
			, StgIac* _stgiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _stgiac->diff(&stgiac);
	// IP handleDpchAppDataStgiac --- INSERT
	insert(moditems, DpchEngData::STGIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecMis1NTour::handleDpchAppDataStgiacqry(
			DbsIdec* dbsidec
			, QryIdecMis1NTour::StgIac* _stgiacqry
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _stgiacqry->diff(&(qry->stgiac));

	IdecQMis1NTour* recSelNew = NULL;

	IdecMTour* _recTou = NULL;

	muteRefresh = true;

	if (!diffitems.empty()) {
		qry->stgiac = *_stgiacqry;

		if (has(diffitems, QryIdecMis1NTour::StgIac::JNUM)) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

		if (!has(diffitems, QryIdecMis1NTour::StgIac::JNUM) || (diffitems.size() > 1)) {
			qry->rerun(dbsidec);
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::RST});
		};

		if (has(diffitems, QryIdecMis1NTour::StgIac::JNUM)) {
			if (!recSelNew) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

			recTou = IdecMTour();

			if (recSelNew) {
				if (dbsidec->tblidecmtour->loadRecByRef(recSelNew->ref, &_recTou)) {
					recTou = *_recTou;
					delete _recTou;
				};
			};

			xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, ((recSelNew) ? recSelNew->ref : 0));
			qry->refreshJnum();
		};

		refresh(dbsidec, moditems);
	};

	muteRefresh = false;

	insert(moditems, DpchEngData::STGIACQRY);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecMis1NTour::handleDpchAppDoButViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	ubigint refMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);

	if (statshr.ButViewAvail && statshr.ButViewActive) {
		if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref)) if (refMis != 0) {
			sref = "CrdIdecTou";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, VecIdecVPreset::PREIDECREFMIS, refMis, sref, recTou.ref, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecMis1NTour::handleDpchAppDoButNewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	ubigint refMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);

	if (statshr.ButNewAvail) {
		if ((xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT) != 0) if (refMis != 0) {
			sref = "CrdIdecTou";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, VecIdecVPreset::PREIDECREFMIS, refMis, sref, -1, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecMis1NTour::handleDpchAppDoButDeleteClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDeleteClick --- INSERT
};

void PnlIdecMis1NTour::handleDpchAppDoButRefreshClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	muteRefresh = true;

	qry->rerun(dbsidec, false);
	refresh(dbsidec, moditems);

	muteRefresh = false;

	insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::STGIACQRY, DpchEngData::RST});
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecMis1NTour::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	};
};

bool PnlIdecMis1NTour::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- BEGIN

	set<uint> moditems;

	if (jrefTrig == qry->jref) {
		if (!muteRefresh) {
			refresh(dbsidec, moditems);
			if (qry->ixIdecVQrystate == VecIdecVQrystate::UTD) insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::STGIACQRY, DpchEngData::RST});
			if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
		};
	};

	// IP handleCallIdecStatChg --- END
	return retval;
};

