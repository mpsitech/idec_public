/**
  * \file PnlIdecScfRecord_evals.cpp
  * job handler for job PnlIdecScfRecord (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfRecord::evalPupFlrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkFlgActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupFrrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkFrgActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupFirActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkFqcActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkFstActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalSldVfrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupVlrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkVlgActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupVrrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkVrgActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupVirActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkVqcActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalChkVstActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfRecord::evalPupOwrActive(
			DbsIdec* dbsidec
		) {
	// jobrecord.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobrecord) a = (jobrecord->jrefMast == jobrecord->jref);
	args.push_back(a);

	return(args.back());
};

