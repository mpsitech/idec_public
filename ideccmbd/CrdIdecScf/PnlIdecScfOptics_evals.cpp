/**
  * \file PnlIdecScfOptics_evals.cpp
  * job handler for job PnlIdecScfOptics (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfOptics::evalTxfDstActive(
			DbsIdec* dbsidec
		) {
	// jobstereo.mast()&stgjobidecstereo.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobstereo) a = (jobstereo->jrefMast == jobstereo->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecstereo.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfIdxActive(
			DbsIdec* dbsidec
		) {
	// jobfusion.mast()&stgjobidecfusion.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobfusion) a = (jobfusion->jrefMast == jobfusion->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecfusion.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfIdyActive(
			DbsIdec* dbsidec
		) {
	// jobfusion.mast()&stgjobidecfusion.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobfusion) a = (jobfusion->jrefMast == jobfusion->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecfusion.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQdxActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQdyActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfAdxActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfAdyActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalPupLsgActive(
			DbsIdec* dbsidec
		) {
	// jobvislacq.mast()&stgjobidecstereo.tcalibEq(0)&stgjobidecfusion.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobvislacq) a = (jobvislacq->jrefMast == jobvislacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecstereo.tcalib == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecfusion.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalPupRsgActive(
			DbsIdec* dbsidec
		) {
	// jobvisracq.mast()&stgjobidecstereo.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobvisracq) a = (jobvisracq->jrefMast == jobvisracq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecstereo.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalPupIsgActive(
			DbsIdec* dbsidec
		) {
	// joblwiracq.mast()&stgjobidecfusion.tcalibEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (joblwiracq) a = (joblwiracq->jrefMast == joblwiracq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecfusion.tcalib == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalUpdQwhActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQhpActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQdpActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQflActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalTxfQfnActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfOptics::evalPupQsgActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()&stgjobidecqcdacq.tcalnucEq(0)&stgjobidecqcdacq.tcalalnEq(0)

	vector<bool> args;
	bool a, b;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalnuc == 0);
	args.push_back(a);
	a = false; a = (xchg->stgjobidecqcdacq.tcalaln == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

