/**
  * \file PnlIdecUsrDetail.cpp
  * job handler for job PnlIdecUsrDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUsrDetail.h"

#include "PnlIdecUsrDetail_blks.cpp"
#include "PnlIdecUsrDetail_evals.cpp"

/******************************************************************************
 class PnlIdecUsrDetail
 ******************************************************************************/

PnlIdecUsrDetail::PnlIdecUsrDetail(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUSRDETAIL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupJ.tag = "FeedFPupJ";
	feedFPupLcl.tag = "FeedFPupLcl";
	VecIdecVLocale::fillFeed(ixIdecVLocale, feedFPupLcl);
	feedFPupSte.tag = "FeedFPupSte";
	VecIdecVMUserState::fillFeed(ixIdecVLocale, feedFPupSte);
	feedFPupUlv.tag = "FeedFPupUlv";
	VecIdecVUserlevel::fillFeed(ixIdecVLocale, feedFPupUlv);

	// IP constructor.cust1 --- INSERT

	dirty = false;

	// IP constructor.cust2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECUSR_USGEQ, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFUSR, jref);
};

PnlIdecUsrDetail::~PnlIdecUsrDetail() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecUsrDetail::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupJ, &feedFPupLcl, &feedFPupSte, &feedFPupUlv, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecUsrDetail::refreshJ(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ListIdecJMUserState usrJstes;
	IdecJMUserState* usrJste = NULL;

	string s;

	// feedFPupJ
	feedFPupJ.clear();

	dbsidec->tblidecjmuserstate->loadRstByUsr(recUsr.ref, false, usrJstes);

	for (unsigned int i=0;i<usrJstes.nodes.size();i++) {
		usrJste = usrJstes.nodes[i];

		s = "";
		if (usrJste->x1Startd != 0) {
			s = Ftm::date(usrJste->x1Startd) + " -";
			if ((i+2) < usrJstes.nodes.size()) if (usrJstes.nodes[i+1]->x1Startd != 0) s += " " + Ftm::date(usrJstes.nodes[i+1]->x1Startd);
		} else s = "(" + VecIdecVTag::getTitle(VecIdecVTag::ALWAYS, ixIdecVLocale) + ")";
		feedFPupJ.appendRefTitles(usrJste->ref, s);
	};

	insert(moditems, DpchEngData::FEEDFPUPJ);

	refreshRecUsrJste(dbsidec, moditems);

};

void PnlIdecUsrDetail::refreshRecUsr(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	IdecMUser* _recUsr = NULL;

	if (dbsidec->tblidecmuser->loadRecByRef(recUsr.ref, &_recUsr)) {
		recUsr = *_recUsr;
		delete _recUsr;
	} else recUsr = IdecMUser();

	dirty = false;

	recUsrJste.ref = recUsr.refJState;
	xchg->removeClstns(VecIdecVCall::CALLIDECUSRJSTEMOD_USREQ, jref);
	if (recUsr.ref != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECUSRJSTEMOD_USREQ, jref, Clstn::VecVJobmask::ALL, 0, recUsr.ref, Clstn::VecVJactype::LOCK);

	continf.TxtPrs = StubIdec::getStubPrsStd(dbsidec, recUsr.refIdecMPerson, ixIdecVLocale, Stub::VecVNonetype::FULL);
	continf.TxtSrf = recUsr.sref;
	continf.TxtUsg = StubIdec::getStubUsgStd(dbsidec, recUsr.refIdecMUsergroup, ixIdecVLocale, Stub::VecVNonetype::FULL);
	contiac.numFPupLcl = feedFPupLcl.getNumByIx(recUsr.ixIdecVLocale);
	contiac.numFPupUlv = feedFPupUlv.getNumByIx(recUsr.ixIdecVUserlevel);
	contiac.TxfPwd = recUsr.Password;

	statshr.TxtPrsActive = evalTxtPrsActive(dbsidec);
	statshr.TxtSrfActive = evalTxtSrfActive(dbsidec);
	statshr.TxtUsgActive = evalTxtUsgActive(dbsidec);
	statshr.ButUsgViewAvail = evalButUsgViewAvail(dbsidec);
	statshr.ButUsgViewActive = evalButUsgViewActive(dbsidec);
	statshr.PupLclActive = evalPupLclActive(dbsidec);
	statshr.PupUlvActive = evalPupUlvActive(dbsidec);
	statshr.TxfPwdActive = evalTxfPwdActive(dbsidec);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

	refreshJ(dbsidec, moditems);

};

void PnlIdecUsrDetail::refreshRecUsrJste(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	IdecJMUserState* _recUsrJste = NULL;

	if (dbsidec->tblidecjmuserstate->loadRecByRef(recUsrJste.ref, &_recUsrJste)) {
		recUsrJste = *_recUsrJste;
		delete _recUsrJste;
	} else recUsrJste = IdecJMUserState();

	contiac.numFPupJ = feedFPupJ.getNumByRef(recUsrJste.ref);
	contiac.numFPupSte = feedFPupSte.getNumByIx(recUsrJste.ixVState);

	statshr.PupJActive = evalPupJActive(dbsidec);
	statshr.ButJEditAvail = evalButJEditAvail(dbsidec);
	statshr.PupSteActive = evalPupSteActive(dbsidec);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

};

void PnlIdecUsrDetail::refresh(
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

void PnlIdecUsrDetail::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSR) {
		recUsr.ref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref);
		refreshRecUsr(dbsidec, moditems);

		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecUsrDetail::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRDETAILDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRDETAILDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTSAVECLICK) {
					handleDpchAppDoButSaveClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTUSGVIEWCLICK) {
					handleDpchAppDoButUsgViewClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTJEDITCLICK) {
					handleDpchAppDoButJEditClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecUsrDetail::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUsrDetail::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (hasAny(diffitems, {ContIac::NUMFPUPSTE, ContIac::NUMFPUPLCL, ContIac::NUMFPUPULV, ContIac::TXFPWD})) {
		if (has(diffitems, ContIac::NUMFPUPSTE)) contiac.numFPupSte = _contiac->numFPupSte;
		if (has(diffitems, ContIac::NUMFPUPLCL)) contiac.numFPupLcl = _contiac->numFPupLcl;
		if (has(diffitems, ContIac::NUMFPUPULV)) contiac.numFPupUlv = _contiac->numFPupUlv;
		if (has(diffitems, ContIac::TXFPWD)) contiac.TxfPwd = _contiac->TxfPwd;
	};

	if (has(diffitems, ContIac::NUMFPUPJ)) {
		recUsrJste.ref = feedFPupJ.getRefByNum(_contiac->numFPupJ);
		refreshRecUsrJste(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecUsrDetail::handleDpchAppDoButSaveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSaveClick --- INSERT
};

void PnlIdecUsrDetail::handleDpchAppDoButUsgViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	if (statshr.ButUsgViewAvail && statshr.ButUsgViewActive) {
		if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref)) {
			sref = "CrdIdecUsg";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, sref, recUsr.refIdecMUsergroup, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecUsrDetail::handleDpchAppDoButJEditClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButJEditClick --- INSERT
};

void PnlIdecUsrDetail::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECUSR_USGEQ) {
		call->abort = handleCallIdecUsr_usgEq(dbsidec, call->jref, call->argInv.ref, call->argRet.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRUPD_REFEQ) {
		call->abort = handleCallIdecUsrUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRJSTEMOD_USREQ) {
		call->abort = handleCallIdecUsrJsteMod_usrEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecUsrDetail::handleCallIdecUsr_usgEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
			, bool& boolvalRet
		) {
	bool retval = false;
	// IP handleCallIdecUsr_usgEq --- BEGIN
	boolvalRet = (recUsr.refIdecMUsergroup == refInv);
	// IP handleCallIdecUsr_usgEq --- END
	return retval;
};

bool PnlIdecUsrDetail::handleCallIdecUsrUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecUsrUpd_refEq --- INSERT
	return retval;
};

bool PnlIdecUsrDetail::handleCallIdecUsrJsteMod_usrEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	set<uint> moditems;

	refreshJ(dbsidec, moditems);

	xchg->submitDpch(getNewDpchEng(moditems));
	return retval;
};

