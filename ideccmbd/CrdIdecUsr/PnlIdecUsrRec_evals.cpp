/**
  * \file PnlIdecUsrRec_evals.cpp
  * job handler for job PnlIdecUsrRec (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsrRec::evalButRegularizeActive(
			DbsIdec* dbsidec
		) {
	// pre.refUsr()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref) != 0);
	args.push_back(a);

	return(args.back());
};

