/**
  * \file PnlIdecUsgRec_evals.cpp
  * job handler for job PnlIdecUsgRec (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsgRec::evalButRegularizeActive(
			DbsIdec* dbsidec
		) {
	// pre.refUsg()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSG, jref) != 0);
	args.push_back(a);

	return(args.back());
};

