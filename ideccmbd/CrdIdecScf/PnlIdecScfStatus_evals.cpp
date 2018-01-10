/**
  * \file PnlIdecScfStatus_evals.cpp
  * job handler for job PnlIdecScfStatus (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfStatus::evalButTheClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecmechctltheta.tcalibEq(0)&jobmechctl.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButPhiClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecmechctlphi.tcalibEq(0)&jobmechctl.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButSteClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecstereo.tcalibEq(0)&jobstereo.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecstereo.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobstereo) a = (jobstereo->jrefMast == jobstereo->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButFusClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecfusion.tcalibEq(0)&jobfusion.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecfusion.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobfusion) a = (jobfusion->jrefMast == jobfusion->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButQnuClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecqcdacq.tcalnucEq(0)&jobqcdacq.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButQalClearActive(
			DbsIdec* dbsidec
		) {
	// !stgjobidecqcdacq.tcalalnEq(0)&jobqcdacq.mast()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfStatus::evalButAcvClearActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

