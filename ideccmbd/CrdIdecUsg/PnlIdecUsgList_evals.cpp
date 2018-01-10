/**
  * \file PnlIdecUsgList_evals.cpp
  * job handler for job PnlIdecUsgList (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsgList::evalButDeleteActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

