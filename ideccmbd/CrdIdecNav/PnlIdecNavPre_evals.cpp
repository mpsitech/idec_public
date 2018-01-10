/**
  * \file PnlIdecNavPre_evals.cpp
  * job handler for job PnlIdecNavPre (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecNavPre::evalTxtMisAvail(
			DbsIdec* dbsidec
		) {
	// pre.refMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavPre::evalTxtTouAvail(
			DbsIdec* dbsidec
		) {
	// pre.refTou()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);

	return(args.back());
};

