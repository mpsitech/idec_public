/**
  * \file PnlIdecUsgAAccess.cpp
  * job handler for job PnlIdecUsgAAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUsgAAccess.h"

#include "PnlIdecUsgAAccess_blks.cpp"
#include "PnlIdecUsgAAccess_evals.cpp"

/******************************************************************************
 class PnlIdecUsgAAccess
 ******************************************************************************/

PnlIdecUsgAAccess::PnlIdecUsgAAccess(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUSGAACCESS, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiQst.tag = "FeedFCsiQst";
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::MNR, "ong", VecIdecVQrystate::getTitle(VecIdecVQrystate::MNR, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::OOD, "red", VecIdecVQrystate::getTitle(VecIdecVQrystate::OOD, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::SLM, "yel", VecIdecVQrystate::getTitle(VecIdecVQrystate::SLM, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::UTD, "grn", VecIdecVQrystate::getTitle(VecIdecVQrystate::UTD, ixIdecVLocale));

	qry = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, 0);

	qry = new QryIdecUsgAAccess(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecUsgAAccess::~PnlIdecUsgAAccess() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecUsgAAccess::getNewDpchEng(
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

void PnlIdecUsgAAccess::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.numFCsiQst = feedFCsiQst.getNumByIx(qry->ixIdecVQrystate);

	// statshr
	statshr.ButNewAvail = evalButNewAvail(dbsidec);
	statshr.ButDuplicateAvail = evalButDuplicateAvail(dbsidec);
	statshr.ButDuplicateActive = evalButDuplicateActive(dbsidec);
	statshr.ButDeleteAvail = evalButDeleteAvail(dbsidec);
	statshr.ButDeleteActive = evalButDeleteActive(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecUsgAAccess::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSG) {
		recUsgAacc = IdecAMUsergroupAccess();

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

void PnlIdecUsgAAccess::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGAACCESSDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::STGIAC)) {
				handleDpchAppDataStgiac(dbsidec, &(dpchappdata->stgiac), &(req->dpcheng));
			} else if (dpchappdata->has(DpchAppData::STGIACQRY)) {
				handleDpchAppDataStgiacqry(dbsidec, &(dpchappdata->stgiacqry), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGAACCESSDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTNEWCLICK) {
					handleDpchAppDoButNewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTDUPLICATECLICK) {
					handleDpchAppDoButDuplicateClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTDELETECLICK) {
					handleDpchAppDoButDeleteClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREFRESHCLICK) {
					handleDpchAppDoButRefreshClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecUsgAAccess::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUsgAAccess::handleDpchAppDataStgiac(
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

void PnlIdecUsgAAccess::handleDpchAppDataStgiacqry(
			DbsIdec* dbsidec
			, QryIdecUsgAAccess::StgIac* _stgiacqry
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _stgiacqry->diff(&(qry->stgiac));

	IdecQUsgAAccess* recSelNew = NULL;

	IdecAMUsergroupAccess* _recUsgAacc = NULL;

	muteRefresh = true;

	if (!diffitems.empty()) {
		qry->stgiac = *_stgiacqry;

		if (has(diffitems, QryIdecUsgAAccess::StgIac::JNUM)) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

		if (!has(diffitems, QryIdecUsgAAccess::StgIac::JNUM) || (diffitems.size() > 1)) {
			qry->rerun(dbsidec);
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::RST});
		};

		if (has(diffitems, QryIdecUsgAAccess::StgIac::JNUM)) {
			if (!recSelNew) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

			recUsgAacc = IdecAMUsergroupAccess();

			if (recSelNew) {
				if (dbsidec->tblidecamusergroupaccess->loadRecByRef(recSelNew->ref, &_recUsgAacc)) {
					recUsgAacc = *_recUsgAacc;
					delete _recUsgAacc;
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

void PnlIdecUsgAAccess::handleDpchAppDoButNewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButNewClick --- INSERT
};

void PnlIdecUsgAAccess::handleDpchAppDoButDuplicateClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDuplicateClick --- INSERT
};

void PnlIdecUsgAAccess::handleDpchAppDoButDeleteClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDeleteClick --- INSERT
};

void PnlIdecUsgAAccess::handleDpchAppDoButRefreshClick(
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

void PnlIdecUsgAAccess::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	};
};

bool PnlIdecUsgAAccess::handleCallIdecStatChg(
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

