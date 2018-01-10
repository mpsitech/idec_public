/**
  * \file PnlIdecScfMech_evals.cpp
  * job handler for job PnlIdecScfMech (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfMech::evalCusTheAnsActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButTheCcwActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButTheCcwstActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButTheCwstActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButTheCwActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalTxfTgrActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfMech::evalSldTllActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfMech::evalSldTulActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctltheta.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctltheta.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfMech::evalCusPhiAnsActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButPhiCcwActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButPhiCcwstActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButPhiCwstActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalButPhiCwActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()&!stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfMech::evalTxfPgrActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfMech::evalSldPllActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfMech::evalSldPulActive(
			DbsIdec* dbsidec
		) {
	// stgjobidecmechctlphi.tcalibEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecmechctlphi.tcalib == 0);
	args.push_back(a);

	return(args.back());
};

