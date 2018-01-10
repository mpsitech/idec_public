/**
  * \file PnlIdecFilDetail.cpp
  * job handler for job PnlIdecFilDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecFilDetail.h"

#include "PnlIdecFilDetail_blks.cpp"
#include "PnlIdecFilDetail_evals.cpp"

/******************************************************************************
 class PnlIdecFilDetail
 ******************************************************************************/

PnlIdecFilDetail::PnlIdecFilDetail(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECFILDETAIL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFLstClu.tag = "FeedFLstClu";
	feedFPupCnt.tag = "FeedFPupCnt";
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMFILECONTENT, ixIdecVLocale, feedFPupCnt);
	feedFPupMim.tag = "FeedFPupMim";
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMFILEMIMETYPE, ixIdecVLocale, feedFPupMim);
	feedFPupRet.tag = "FeedFPupRet";
	VecIdecVMFileRefTbl::fillFeed(ixIdecVLocale, feedFPupRet);

	// IP constructor.cust1 --- INSERT

	dirty = false;

	// IP constructor.cust2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECFIL_CLUEQ, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECFIL_RETEQ, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECFIL_REUEQ, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	xchg->addIxClstn(VecIdecVCall::CALLIDECKLSAKEYMOD_KLSEQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVKeylist::KLSTIDECKMFILECONTENT, Clstn::VecVJactype::LOCK);
	xchg->addIxClstn(VecIdecVCall::CALLIDECKLSAKEYMOD_KLSEQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVKeylist::KLSTIDECKMFILEMIMETYPE, Clstn::VecVJactype::LOCK);

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFFIL, jref);
};

PnlIdecFilDetail::~PnlIdecFilDetail() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecFilDetail::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFLstClu, &feedFPupCnt, &feedFPupMim, &feedFPupRet, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecFilDetail::refreshLstClu(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	statshr.LstCluActive = evalLstCluActive(dbsidec);
	statshr.ButCluViewActive = evalButCluViewActive(dbsidec);
	statshr.ButCluClusterAvail = evalButCluClusterAvail(dbsidec);
	statshr.ButCluUnclusterAvail = evalButCluUnclusterAvail(dbsidec);

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecFilDetail::refreshClu(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	ContInf oldContinf(continf);

	vector<ubigint> refs;

	bool first;

	// contiac
	contiac.numFLstClu = 0;

	// feedFLstClu, continf
	feedFLstClu.clear();
	continf.TxtClu = "";

	if (recFil.refIdecCFile != 0) dbsidec->tblidecmfile->loadRefsByClu(recFil.refIdecCFile, false, refs);

	first = true;
	for (unsigned int i=0;i<refs.size();i++) {
		if (refs[i] != recFil.ref) {
			feedFLstClu.appendRefTitles(refs[i], StubIdec::getStubFilStd(dbsidec, refs[i], ixIdecVLocale));

			if (first) first = false;
			else continf.TxtClu += ";";

			continf.TxtClu += StubIdec::getStubFilStd(dbsidec, refs[i], ixIdecVLocale);
		};
	};
	if (first) continf.TxtClu = "-";

	insert(moditems, DpchEngData::FEEDFLSTCLU);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	refreshLstClu(dbsidec, moditems);
};

void PnlIdecFilDetail::refreshPupCnt(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupCnt = 0;

	for (unsigned int i=0;i<feedFPupCnt.size();i++) {
		if (feedFPupCnt.getSrefByNum(i+1) == contiac.TxfCnt) {
			contiac.numFPupCnt = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfCntValid = (contiac.numFPupCnt != 0);
	statshr.PupCntActive = evalPupCntActive(dbsidec);
	statshr.ButCntEditAvail = evalButCntEditAvail(dbsidec);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecFilDetail::refreshTxfCnt(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfCnt = feedFPupCnt.getSrefByNum(contiac.numFPupCnt);

	// statshr
	statshr.TxfCntValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecFilDetail::refreshCnt(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	// feedFPupCnt
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMFILECONTENT, ixIdecVLocale, feedFPupCnt);

	insert(moditems, DpchEngData::FEEDFPUPCNT);

	refreshPupCnt(dbsidec, moditems);
};

void PnlIdecFilDetail::refreshPupMim(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupMim = 0;

	for (unsigned int i=0;i<feedFPupMim.size();i++) {
		if (feedFPupMim.getSrefByNum(i+1) == contiac.TxfMim) {
			contiac.numFPupMim = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfMimValid = (contiac.numFPupMim != 0);
	statshr.PupMimActive = evalPupMimActive(dbsidec);
	statshr.ButMimEditAvail = evalButMimEditAvail(dbsidec);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecFilDetail::refreshTxfMim(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfMim = feedFPupMim.getSrefByNum(contiac.numFPupMim);

	// statshr
	statshr.TxfMimValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecFilDetail::refreshMim(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	// feedFPupMim
	dbsidec->fillFeedFromKlst(VecIdecVKeylist::KLSTIDECKMFILEMIMETYPE, ixIdecVLocale, feedFPupMim);

	insert(moditems, DpchEngData::FEEDFPUPMIM);

	refreshPupMim(dbsidec, moditems);
};

void PnlIdecFilDetail::refreshRecFil(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	IdecMFile* _recFil = NULL;

	if (dbsidec->tblidecmfile->loadRecByRef(recFil.ref, &_recFil)) {
		recFil = *_recFil;
		delete _recFil;
	} else recFil = IdecMFile();

	dirty = false;

	xchg->removeClstns(VecIdecVCall::CALLIDECFILMOD_CLUEQ, jref);
	if (recFil.refIdecCFile != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECFILMOD_CLUEQ, jref, Clstn::VecVJobmask::ALL, 0, recFil.refIdecCFile, Clstn::VecVJactype::LOCK);

	contiac.TxfFnm = recFil.Filename;
	contiac.numFPupRet = feedFPupRet.getNumByIx(recFil.refIxVTbl);
	if (recFil.refIxVTbl == VecIdecVMFileRefTbl::MIS) continf.TxtReu = StubIdec::getStubMisStd(dbsidec, recFil.refUref, ixIdecVLocale, Stub::VecVNonetype::FULL);
	else if (recFil.refIxVTbl == VecIdecVMFileRefTbl::TOU) continf.TxtReu = StubIdec::getStubTouStd(dbsidec, recFil.refUref, ixIdecVLocale, Stub::VecVNonetype::FULL);
	else continf.TxtReu = "-";
	contiac.TxfCnt = recFil.osrefKContent;
	contiac.TxfAcv = Ftm::stamp(recFil.Archived);
	contiac.TxfAnm = recFil.Archivename;
	contiac.TxfMim = recFil.srefKMimetype;
	contiac.TxfSiz = to_string(recFil.Size);
	contiac.TxfCmt = recFil.Comment;

	statshr.TxfFnmActive = evalTxfFnmActive(dbsidec);
	statshr.TxtReuActive = evalTxtReuActive(dbsidec);
	statshr.ButReuViewAvail = evalButReuViewAvail(dbsidec);
	statshr.ButReuViewActive = evalButReuViewActive(dbsidec);
	statshr.TxfAcvActive = evalTxfAcvActive(dbsidec);
	statshr.TxfAnmActive = evalTxfAnmActive(dbsidec);
	statshr.TxfSizActive = evalTxfSizActive(dbsidec);
	statshr.TxfCmtActive = evalTxfCmtActive(dbsidec);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

	refreshClu(dbsidec, moditems);
	refreshPupCnt(dbsidec, moditems);
	refreshPupMim(dbsidec, moditems);

};

void PnlIdecFilDetail::refresh(
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

void PnlIdecFilDetail::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFFIL) {
		recFil.ref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFFIL, jref);
		refreshRecFil(dbsidec, moditems);

		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecFilDetail::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDETAILDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDETAILDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTSAVECLICK) {
					handleDpchAppDoButSaveClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCLUVIEWCLICK) {
					handleDpchAppDoButCluViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCLUCLUSTERCLICK) {
					handleDpchAppDoButCluClusterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCLUUNCLUSTERCLICK) {
					handleDpchAppDoButCluUnclusterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREUVIEWCLICK) {
					handleDpchAppDoButReuViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCNTEDITCLICK) {
					handleDpchAppDoButCntEditClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMIMEDITCLICK) {
					handleDpchAppDoButMimEditClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecFilDetail::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecFilDetail::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (hasAny(diffitems, {ContIac::TXFFNM, ContIac::TXFACV, ContIac::TXFANM, ContIac::TXFSIZ, ContIac::TXFCMT})) {
		if (has(diffitems, ContIac::TXFFNM)) contiac.TxfFnm = _contiac->TxfFnm;
		if (has(diffitems, ContIac::TXFACV)) contiac.TxfAcv = _contiac->TxfAcv;
		if (has(diffitems, ContIac::TXFANM)) contiac.TxfAnm = _contiac->TxfAnm;
		if (has(diffitems, ContIac::TXFSIZ)) contiac.TxfSiz = _contiac->TxfSiz;
		if (has(diffitems, ContIac::TXFCMT)) contiac.TxfCmt = _contiac->TxfCmt;
	};

	if (has(diffitems, ContIac::NUMFLSTCLU)) {
		contiac.numFLstClu = _contiac->numFLstClu;
		refreshLstClu(dbsidec, moditems);
	};

	if (has(diffitems, ContIac::TXFCNT)) {
		contiac.TxfCnt = _contiac->TxfCnt;
		refreshPupCnt(dbsidec, moditems);
	} else if (has(diffitems, ContIac::NUMFPUPCNT)) {
		contiac.numFPupCnt = _contiac->numFPupCnt;
		refreshTxfCnt(dbsidec, moditems);
	};

	if (has(diffitems, ContIac::TXFMIM)) {
		contiac.TxfMim = _contiac->TxfMim;
		refreshPupMim(dbsidec, moditems);
	} else if (has(diffitems, ContIac::NUMFPUPMIM)) {
		contiac.numFPupMim = _contiac->numFPupMim;
		refreshTxfMim(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecFilDetail::handleDpchAppDoButSaveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSaveClick --- INSERT
};

void PnlIdecFilDetail::handleDpchAppDoButCluViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCluViewClick --- INSERT
};

void PnlIdecFilDetail::handleDpchAppDoButCluClusterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCluClusterClick --- INSERT
};

void PnlIdecFilDetail::handleDpchAppDoButCluUnclusterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCluUnclusterClick --- INSERT
};

void PnlIdecFilDetail::handleDpchAppDoButReuViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	uint ixPre = xchg->getIxPreset(VecIdecVPreset::PREIDECIXPRE, jref);
	ubigint refPre = ((ixPre) ? xchg->getRefPreset(ixPre, jref) : 0);

	if (statshr.ButReuViewAvail && statshr.ButReuViewActive) {
		if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref)) if (recFil.refIxVTbl == VecIdecVMFileRefTbl::MIS) {
			sref = "CrdIdecMis";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, sref, recFil.refUref, jrefNew);
		};
		if (jrefNew == 0) {
			if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref)) if (recFil.refIxVTbl == VecIdecVMFileRefTbl::TOU) if (ixPre == VecIdecVPreset::PREIDECREFMIS) {
				sref = "CrdIdecTou";
				xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, ixPre, refPre, sref, recFil.refUref, jrefNew);
			};
		};
		if (jrefNew == 0) {
			if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref)) if (recFil.refIxVTbl == VecIdecVMFileRefTbl::TOU) {
				sref = "CrdIdecTou";
				xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, sref, recFil.refUref, jrefNew);
			};
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecFilDetail::handleDpchAppDoButCntEditClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCntEditClick --- INSERT
};

void PnlIdecFilDetail::handleDpchAppDoButMimEditClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMimEditClick --- INSERT
};

void PnlIdecFilDetail::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECFIL_CLUEQ) {
		call->abort = handleCallIdecFil_cluEq(dbsidec, call->jref, call->argInv.ref, call->argRet.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFIL_RETEQ) {
		call->abort = handleCallIdecFil_retEq(dbsidec, call->jref, call->argInv.ix, call->argRet.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFIL_REUEQ) {
		call->abort = handleCallIdecFil_reuEq(dbsidec, call->jref, call->argInv.ref, call->argRet.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFILUPD_REFEQ) {
		call->abort = handleCallIdecFilUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECKLSAKEYMOD_KLSEQ) {
		call->abort = handleCallIdecKlsAkeyMod_klsEq(dbsidec, call->jref, call->argInv.ix);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFILMOD_CLUEQ) {
		call->abort = handleCallIdecFilMod_cluEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecFilDetail::handleCallIdecFil_cluEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
			, bool& boolvalRet
		) {
	bool retval = false;
	// IP handleCallIdecFil_cluEq --- BEGIN
	boolvalRet = (recFil.refIdecCFile == refInv);
	// IP handleCallIdecFil_cluEq --- END
	return retval;
};

bool PnlIdecFilDetail::handleCallIdecFil_retEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, bool& boolvalRet
		) {
	bool retval = false;
	// IP handleCallIdecFil_retEq --- BEGIN
	boolvalRet = (recFil.refIxVTbl == ixInv);
	// IP handleCallIdecFil_retEq --- END
	return retval;
};

bool PnlIdecFilDetail::handleCallIdecFil_reuEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
			, bool& boolvalRet
		) {
	bool retval = false;
	// IP handleCallIdecFil_reuEq --- BEGIN
	boolvalRet = (recFil.refUref == refInv);
	// IP handleCallIdecFil_reuEq --- END
	return retval;
};

bool PnlIdecFilDetail::handleCallIdecFilUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecFilUpd_refEq --- INSERT
	return retval;
};

bool PnlIdecFilDetail::handleCallIdecKlsAkeyMod_klsEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
		) {
	bool retval = false;
	set<uint> moditems;

	if (ixInv == VecIdecVKeylist::KLSTIDECKMFILECONTENT) {
		refreshCnt(dbsidec, moditems);
	} else if (ixInv == VecIdecVKeylist::KLSTIDECKMFILEMIMETYPE) {
		refreshMim(dbsidec, moditems);
	};

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

bool PnlIdecFilDetail::handleCallIdecFilMod_cluEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	set<uint> moditems;

	refreshClu(dbsidec, moditems);

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

