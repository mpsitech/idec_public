/**
  * \file PnlIdecIaqScill_evals.cpp
  * job handler for job PnlIdecIaqScill (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecIaqScill::evalPupModActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecIaqScill::evalSldThrActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecIaqScill::evalSldFldActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecIaqScill::evalSldSptActive(
			DbsIdec* dbsidec
		) {
	// jobillum.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobillum) a = (jobillum->jrefMast == jobillum->jref);
	args.push_back(a);

	return(args.back());
};

