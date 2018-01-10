/**
  * \file PnlIdecNavPre.cpp
  * job handler for job PnlIdecNavPre (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecNavPre.h"

#include "PnlIdecNavPre_blks.cpp"
#include "PnlIdecNavPre_evals.cpp"

/******************************************************************************
 class PnlIdecNavPre
 ******************************************************************************/

PnlIdecNavPre::PnlIdecNavPre(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECNAVPRE, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

};

PnlIdecNavPre::~PnlIdecNavPre() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecNavPre::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &continf, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecNavPre::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.TxtMis = StubIdec::getStubMisStd(dbsidec, xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref), ixIdecVLocale);
	continf.TxtTou = StubIdec::getStubTouStd(dbsidec, xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref), ixIdecVLocale);

	// statshr
	statshr.TxtMisAvail = evalTxtMisAvail(dbsidec);
	statshr.TxtTouAvail = evalTxtTouAvail(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecNavPre::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	refresh(dbsidec, moditems);

	if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	// IP updatePreset --- END
};

void PnlIdecNavPre::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVPREDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMISREMOVECLICK) {
					handleDpchAppDoButMisRemoveClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTOUREMOVECLICK) {
					handleDpchAppDoButTouRemoveClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecNavPre::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecNavPre::handleDpchAppDoButMisRemoveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFMIS, 0);

	refresh(dbsidec, moditems);

	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecNavPre::handleDpchAppDoButTouRemoveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECREFTOU, 0);

	refresh(dbsidec, moditems);

	*dpcheng = getNewDpchEng(moditems);
};

