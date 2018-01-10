/**
  * \file PnlIdecIaqMech_evals.cpp
  * job handler for job PnlIdecIaqMech (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecIaqMech::evalCusTheAnsActive(
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

bool PnlIdecIaqMech::evalButTheCcwActive(
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

bool PnlIdecIaqMech::evalButTheCcwstActive(
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

bool PnlIdecIaqMech::evalButTheCwstActive(
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

bool PnlIdecIaqMech::evalButTheCwActive(
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

bool PnlIdecIaqMech::evalCusPhiAnsActive(
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

bool PnlIdecIaqMech::evalButPhiCcwActive(
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

bool PnlIdecIaqMech::evalButPhiCcwstActive(
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

bool PnlIdecIaqMech::evalButPhiCwstActive(
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

bool PnlIdecIaqMech::evalButPhiCwActive(
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

