/**
  * \file PnlIdecIaqLive_evals.cpp
  * job handler for job PnlIdecIaqLive (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecIaqLive::evalSldFrrActive(
			DbsIdec* dbsidec
		) {
	// jobtrigger.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobtrigger) a = (jobtrigger->jrefMast == jobtrigger->jref);
	args.push_back(a);

	return(args.back());
};

