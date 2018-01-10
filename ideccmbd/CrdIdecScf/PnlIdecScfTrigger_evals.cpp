/**
  * \file PnlIdecScfTrigger_evals.cpp
  * job handler for job PnlIdecScfTrigger (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfTrigger::evalSldRdlActive(
			DbsIdec* dbsidec
		) {
	// jobtrigger.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobtrigger) a = (jobtrigger->jrefMast == jobtrigger->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfTrigger::evalSldIdlActive(
			DbsIdec* dbsidec
		) {
	// jobtrigger.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobtrigger) a = (jobtrigger->jrefMast == jobtrigger->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfTrigger::evalSldQdlActive(
			DbsIdec* dbsidec
		) {
	// jobtrigger.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobtrigger) a = (jobtrigger->jrefMast == jobtrigger->jref);
	args.push_back(a);

	return(args.back());
};

