/**
  * \file PnlIdecScfQcd_evals.cpp
  * job handler for job PnlIdecScfQcd (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfQcd::evalTxfLamActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalTxfDlmActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalChkAonActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldTofActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldTmpActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalPupFanActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldFmdActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldVddActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalChkVd2Active(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldVrfActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalUpdAslActive(
			DbsIdec* dbsidec
		) {
	// jobspotfind.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobspotfind) a = (jobspotfind->jrefMast == jobspotfind->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalSldAmoActive(
			DbsIdec* dbsidec
		) {
	// jobspotfind.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobspotfind) a = (jobspotfind->jrefMast == jobspotfind->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfQcd::evalChkAadActive(
			DbsIdec* dbsidec
		) {
	// jobspotfind.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobspotfind) a = (jobspotfind->jrefMast == jobspotfind->jref);
	args.push_back(a);

	return(args.back());
};

