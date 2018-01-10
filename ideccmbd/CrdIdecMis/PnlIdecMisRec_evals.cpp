/**
  * \file PnlIdecMisRec_evals.cpp
  * job handler for job PnlIdecMisRec (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecMisRec::evalButRegularizeActive(
			DbsIdec* dbsidec
		) {
	// pre.refMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

