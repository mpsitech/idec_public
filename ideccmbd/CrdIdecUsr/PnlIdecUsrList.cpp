/**
  * \file PnlIdecUsrList.cpp
  * job handler for job PnlIdecUsrList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUsrList.h"

#include "PnlIdecUsrList_blks.cpp"
#include "PnlIdecUsrList_evals.cpp"

/******************************************************************************
 class PnlIdecUsrList
 ******************************************************************************/

PnlIdecUsrList::PnlIdecUsrList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUSRLIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiQst.tag = "FeedFCsiQst";
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::MNR, "ong", VecIdecVQrystate::getTitle(VecIdecVQrystate::MNR, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::OOD, "red", VecIdecVQrystate::getTitle(VecIdecVQrystate::OOD, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::SLM, "yel", VecIdecVQrystate::getTitle(VecIdecVQrystate::SLM, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::UTD, "grn", VecIdecVQrystate::getTitle(VecIdecVQrystate::UTD, ixIdecVLocale));
	feedFTos.tag = "FeedFTos";
	QryIdecUsrList::VecVOrd::fillFeed(feedFTos);

	qry = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXORD, jref, QryIdecUsrList::VecVOrd::SRF);

	qry = new QryIdecUsrList(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	statshr.ixIdecVExpstate = ((xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref)) ? VecIdecVExpstate::MIND : VecIdecVExpstate::REGD);
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecUsrList::~PnlIdecUsrList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecUsrList::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFCsiQst, &feedFTos, &statshr, &stgiac, &(qry->rst), &(qry->statshr), &(qry->stgiac), items);
	};

	return dpcheng;
};

void PnlIdecUsrList::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	ContIac oldContiac(contiac);

	// IP refresh --- BEGIN
	// continf
	continf.numFCsiQst = feedFCsiQst.getNumByIx(qry->ixIdecVQrystate);

	// contiac
	contiac.numFTos = xchg->getIxPreset(VecIdecVPreset::PREIDECIXORD, jref);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
};

void PnlIdecUsrList::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSR) {
		xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref));
		qry->refreshJnum();
		refresh(dbsidec, moditems);

		insert(moditems, DpchEngData::STGIACQRY);

		if ((jrefTrig != jref) && notif) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecUsrList::minimize(
			DbsIdec* dbsidec
			, const bool notif
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	if (statshr.ixIdecVExpstate != VecIdecVExpstate::MIND) {
		statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
		insert(moditems, DpchEngData::STATSHR);
	};

	if (notif) {
		if (dpcheng) *dpcheng = getNewDpchEng(moditems);
		else if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
};

void PnlIdecUsrList::regularize(
			DbsIdec* dbsidec
			, const bool notif
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	if (statshr.ixIdecVExpstate != VecIdecVExpstate::REGD) {
		statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
		insert(moditems, DpchEngData::STATSHR);
	};

	if (notif) {
		if (dpcheng) *dpcheng = getNewDpchEng(moditems);
		else if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
};

void PnlIdecUsrList::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRLISTDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			} else if (dpchappdata->has(DpchAppData::STGIAC)) {
				handleDpchAppDataStgiac(dbsidec, &(dpchappdata->stgiac), &(req->dpcheng));
			} else if (dpchappdata->has(DpchAppData::STGIACQRY)) {
				handleDpchAppDataStgiacqry(dbsidec, &(dpchappdata->stgiacqry), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRLISTDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTNEWCLICK) {
					handleDpchAppDoButNewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTDELETECLICK) {
					handleDpchAppDoButDeleteClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTFILTERCLICK) {
					handleDpchAppDoButFilterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREFRESHCLICK) {
					handleDpchAppDoButRefreshClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecUsrList::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUsrList::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	muteRefresh = true;

	if (has(diffitems, ContIac::NUMFTOS)) {
		if ((_contiac->numFTos >= QryIdecUsrList::VecVOrd::PRS) && (_contiac->numFTos <= QryIdecUsrList::VecVOrd::STE)) {
			xchg->addIxPreset(VecIdecVPreset::PREIDECIXORD, jref, _contiac->numFTos);

			qry->rerun(dbsidec);
			refresh(dbsidec, moditems);
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::STGIACQRY, DpchEngData::RST});
		};
	};

	muteRefresh = false;

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecUsrList::handleDpchAppDataStgiac(
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

void PnlIdecUsrList::handleDpchAppDataStgiacqry(
			DbsIdec* dbsidec
			, QryIdecUsrList::StgIac* _stgiacqry
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _stgiacqry->diff(&(qry->stgiac));

	ubigint refSelNew = 0;

	muteRefresh = true;

	if (!diffitems.empty()) {
		qry->stgiac = *_stgiacqry;

		if (has(diffitems, QryIdecUsrList::StgIac::JNUM)) refSelNew = qry->getRefByJnum(_stgiacqry->jnum);

		if (!has(diffitems, QryIdecUsrList::StgIac::JNUM) || (diffitems.size() > 1)) {
			qry->rerun(dbsidec);
			refresh(dbsidec, moditems);
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::RST});
		};

		if (has(diffitems, QryIdecUsrList::StgIac::JNUM)) {
			if (refSelNew == 0) refSelNew = qry->getRefByJnum(_stgiacqry->jnum);
			xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFUSR, refSelNew);
		};
	};

	muteRefresh = false;

	insert(moditems, DpchEngData::STGIACQRY);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecUsrList::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	minimize(dbsidec, true, dpcheng);
};

void PnlIdecUsrList::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	regularize(dbsidec, true, dpcheng);
};

void PnlIdecUsrList::handleDpchAppDoButNewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButNewClick --- INSERT
};

void PnlIdecUsrList::handleDpchAppDoButDeleteClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDeleteClick --- INSERT
};

void PnlIdecUsrList::handleDpchAppDoButFilterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButFilterClick --- INSERT
};

void PnlIdecUsrList::handleDpchAppDoButRefreshClick(
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

void PnlIdecUsrList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	};
};

bool PnlIdecUsrList::handleCallIdecStatChg(
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

