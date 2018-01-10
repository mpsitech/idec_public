/**
  * \file CrdIdecUtl.cpp
  * job handler for job CrdIdecUtl (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecUtl.h"

#include "CrdIdecUtl_blks.cpp"

/******************************************************************************
 class CrdIdecUtl
 ******************************************************************************/

CrdIdecUtl::CrdIdecUtl(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::CRDIDECUTL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	dlgtheta = NULL;
	dlgphi = NULL;
	dlgstereo = NULL;
	dlgfusion = NULL;
	dlgqcdnuc = NULL;
	dlgqcdaln = NULL;
	pnlspiterm = NULL;
	pnlheadbar = NULL;

	// IP constructor.cust1 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	pnlspiterm = new PnlIdecUtlSpiterm(xchg, dbsidec, jref, ixIdecVLocale);
	pnlheadbar = new PnlIdecUtlHeadbar(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefSpiterm = pnlspiterm->jref;
	statshr.jrefHeadbar = pnlheadbar->jref;

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecUtl::~CrdIdecUtl() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecUtl::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &continf, &feedFSge, &statshr, items);
	};

	return dpcheng;
};

void CrdIdecUtl::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);

	// IP refresh --- BEGIN
	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecUtl/" + VecIdecVLocale::getSref(ixIdecVLocale);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

void CrdIdecUtl::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- INSERT
};

void CrdIdecUtl::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::ALRIDECABT: leaveSgeAlridecabt(dbsidec); break;
				case VecVSge::CLOSE: leaveSgeClose(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::ALRIDECABT: _ixVSge = enterSgeAlridecabt(dbsidec, reenter); break;
			case VecVSge::CLOSE: _ixVSge = enterSgeClose(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint CrdIdecUtl::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecUtl::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecUtl::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecUtl::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecUtl::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECUTL);
	return retval;
};

void CrdIdecUtl::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecUtl::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecUtl::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::CLOSE) {
					handleDpchAppDoClose(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPABTCLICK) {
					handleDpchAppDoMitAppAbtClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDTHECLICK) {
					handleDpchAppDoMitCrdTheClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDPHICLICK) {
					handleDpchAppDoMitCrdPhiClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDSTECLICK) {
					handleDpchAppDoMitCrdSteClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDFSNCLICK) {
					handleDpchAppDoMitCrdFsnClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDQNUCLICK) {
					handleDpchAppDoMitCrdQnuClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDQALCLICK) {
					handleDpchAppDoMitCrdQalClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void CrdIdecUtl::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecUtl::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecUtl::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecUtl::handleDpchAppDoMitCrdTheClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgtheta) {
		dlgtheta = new DlgIdecUtlTheta(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgtheta = dlgtheta->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppDoMitCrdPhiClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgphi) {
		dlgphi = new DlgIdecUtlPhi(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgphi = dlgphi->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppDoMitCrdSteClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgstereo) {
		dlgstereo = new DlgIdecUtlStereo(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgstereo = dlgstereo->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppDoMitCrdFsnClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgfusion) {
		dlgfusion = new DlgIdecUtlFusion(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgfusion = dlgfusion->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppDoMitCrdQnuClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgqcdnuc) {
		dlgqcdnuc = new DlgIdecUtlQcdnuc(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgqcdnuc = dlgqcdnuc->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppDoMitCrdQalClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgqcdaln) {
		dlgqcdaln = new DlgIdecUtlQcdaln(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgqcdaln = dlgqcdaln->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecUtl::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecUtl::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDLGCLOSE) {
		call->abort = handleCallIdecDlgClose(dbsidec, call->jref);
	};
};

bool CrdIdecUtl::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if (dlgfusion) {
		delete dlgfusion;
		dlgfusion = NULL;
		statshr.jrefDlgfusion = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	} else if (dlgphi) {
		delete dlgphi;
		dlgphi = NULL;
		statshr.jrefDlgphi = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	} else if (dlgqcdaln) {
		delete dlgqcdaln;
		dlgqcdaln = NULL;
		statshr.jrefDlgqcdaln = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	} else if (dlgqcdnuc) {
		delete dlgqcdnuc;
		dlgqcdnuc = NULL;
		statshr.jrefDlgqcdnuc = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	} else if (dlgstereo) {
		delete dlgstereo;
		dlgstereo = NULL;
		statshr.jrefDlgstereo = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	} else if (dlgtheta) {
		delete dlgtheta;
		dlgtheta = NULL;
		statshr.jrefDlgtheta = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	};

	return retval;
};

