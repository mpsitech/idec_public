/**
  * \file PnlIdecTouRec_evals.cpp
  * job handler for job PnlIdecTouRec (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecTouRec::evalButRegularizeActive(
			DbsIdec* dbsidec
		) {
	// pre.refTou()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);

	return(args.back());
};

