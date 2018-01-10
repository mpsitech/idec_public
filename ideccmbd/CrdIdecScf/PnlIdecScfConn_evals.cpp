/**
  * \file PnlIdecScfConn_evals.cpp
  * job handler for job PnlIdecScfConn (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfConn::evalPupTspActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupPspActive(
			DbsIdec* dbsidec
		) {
	// jobmechctl.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobmechctl) a = (jobmechctl->jrefMast == jobmechctl->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupVtyActive(
			DbsIdec* dbsidec
		) {
	// jobvislacq.mast()&jobvisracq.mast()

	vector<bool> args;
	bool a, b;

	a = false; if (jobvislacq) a = (jobvislacq->jrefMast == jobvislacq->jref);
	args.push_back(a);
	a = false; if (jobvisracq) a = (jobvisracq->jrefMast == jobvisracq->jref);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecScfConn::evalPupLsnAvail(
			DbsIdec* dbsidec
		) {
	// stgjobidecvislacq.ixidecvcamtypeEq(pgcmln)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecvislacq.ixIdecVCamtype == VecIdecVCamtype::PGCMLN);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupLsnActive(
			DbsIdec* dbsidec
		) {
	// jobvislacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvislacq) a = (jobvislacq->jrefMast == jobvislacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupLpaAvail(
			DbsIdec* dbsidec
		) {
	// stgjobidecvislacq.ixidecvcamtypeEq(mslife)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecvislacq.ixIdecVCamtype == VecIdecVCamtype::MSLIFE);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupLpaActive(
			DbsIdec* dbsidec
		) {
	// jobvislacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvislacq) a = (jobvislacq->jrefMast == jobvislacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupLtrActive(
			DbsIdec* dbsidec
		) {
	// jobvislacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvislacq) a = (jobvislacq->jrefMast == jobvislacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupRsnAvail(
			DbsIdec* dbsidec
		) {
	// stgjobidecvisracq.ixidecvcamtypeEq(pgcmln)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecvisracq.ixIdecVCamtype == VecIdecVCamtype::PGCMLN);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupRsnActive(
			DbsIdec* dbsidec
		) {
	// jobvisracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvisracq) a = (jobvisracq->jrefMast == jobvisracq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupRpaAvail(
			DbsIdec* dbsidec
		) {
	// stgjobidecvisracq.ixidecvcamtypeEq(mslife)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->stgjobidecvisracq.ixIdecVCamtype == VecIdecVCamtype::MSLIFE);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupRpaActive(
			DbsIdec* dbsidec
		) {
	// jobvisracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvisracq) a = (jobvisracq->jrefMast == jobvisracq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupRtrActive(
			DbsIdec* dbsidec
		) {
	// jobvisracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobvisracq) a = (jobvisracq->jrefMast == jobvisracq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalTxtIsnActive(
			DbsIdec* dbsidec
		) {
	// joblwiracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (joblwiracq) a = (joblwiracq->jrefMast == joblwiracq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupQspActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupFldActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfConn::evalPupSptActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

