/**
  * \file PnlIdecMisRef1NFile.cpp
  * job handler for job PnlIdecMisRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecMisRef1NFile.h"

#include "PnlIdecMisRef1NFile_blks.cpp"
#include "PnlIdecMisRef1NFile_evals.cpp"

/******************************************************************************
 class PnlIdecMisRef1NFile
 ******************************************************************************/

PnlIdecMisRef1NFile::PnlIdecMisRef1NFile(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECMISREF1NFILE, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiQst.tag = "FeedFCsiQst";
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::MNR, "ong", VecIdecVQrystate::getTitle(VecIdecVQrystate::MNR, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::OOD, "red", VecIdecVQrystate::getTitle(VecIdecVQrystate::OOD, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::SLM, "yel", VecIdecVQrystate::getTitle(VecIdecVQrystate::SLM, ixIdecVLocale));
	feedFCsiQst.appendIxSrefTitles(VecIdecVQrystate::UTD, "grn", VecIdecVQrystate::getTitle(VecIdecVQrystate::UTD, ixIdecVLocale));

	qry = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addRefPreset(VecIdecVPreset::PREIDECREFSEL, jref, 0);

	qry = new QryIdecMisRef1NFile(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecMisRef1NFile::~PnlIdecMisRef1NFile() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecMisRef1NFile::getNewDpchEng(
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

void PnlIdecMisRef1NFile::refresh(
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

void PnlIdecMisRef1NFile::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFMIS) {
		recFil = IdecMFile();

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

void PnlIdecMisRef1NFile::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISREF1NFILEDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::STGIAC)) {
				handleDpchAppDataStgiac(dbsidec, &(dpchappdata->stgiac), &(req->dpcheng));
			} else if (dpchappdata->has(DpchAppData::STGIACQRY)) {
				handleDpchAppDataStgiacqry(dbsidec, &(dpchappdata->stgiacqry), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISREF1NFILEDO) {
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

void PnlIdecMisRef1NFile::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecMisRef1NFile::handleDpchAppDataStgiac(
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

void PnlIdecMisRef1NFile::handleDpchAppDataStgiacqry(
			DbsIdec* dbsidec
			, QryIdecMisRef1NFile::StgIac* _stgiacqry
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _stgiacqry->diff(&(qry->stgiac));

	IdecQMisRef1NFile* recSelNew = NULL;

	IdecMFile* _recFil = NULL;

	muteRefresh = true;

	if (!diffitems.empty()) {
		qry->stgiac = *_stgiacqry;

		if (has(diffitems, QryIdecMisRef1NFile::StgIac::JNUM)) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

		if (!has(diffitems, QryIdecMisRef1NFile::StgIac::JNUM) || (diffitems.size() > 1)) {
			qry->rerun(dbsidec);
			insert(moditems, {DpchEngData::STATSHRQRY, DpchEngData::RST});
		};

		if (has(diffitems, QryIdecMisRef1NFile::StgIac::JNUM)) {
			if (!recSelNew) recSelNew = qry->getRecByJnum(_stgiacqry->jnum);

			recFil = IdecMFile();

			if (recSelNew) {
				if (dbsidec->tblidecmfile->loadRecByRef(recSelNew->ref, &_recFil)) {
					recFil = *_recFil;
					delete _recFil;
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

void PnlIdecMisRef1NFile::handleDpchAppDoButViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	ubigint refMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);

	if (statshr.ButViewAvail && statshr.ButViewActive) {
		if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref)) if (refMis != 0) {
			sref = "CrdIdecFil";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, VecIdecVPreset::PREIDECREFMIS, refMis, sref, recFil.ref, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecMisRef1NFile::handleDpchAppDoButNewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	ubigint refMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);

	if (statshr.ButNewAvail) {
		if ((xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT) != 0) if (refMis != 0) {
			sref = "CrdIdecFil";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, VecIdecVPreset::PREIDECREFMIS, refMis, sref, -1, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecMisRef1NFile::handleDpchAppDoButDeleteClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDeleteClick --- INSERT
};

void PnlIdecMisRef1NFile::handleDpchAppDoButRefreshClick(
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

void PnlIdecMisRef1NFile::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	};
};

bool PnlIdecMisRef1NFile::handleCallIdecStatChg(
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

