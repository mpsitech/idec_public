/**
  * \file CrdIdecTou_evals.cpp
  * job handler for job CrdIdecTou (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool CrdIdecTou::evalMspCrd1Avail(
			DbsIdec* dbsidec
		) {
	// MitCrdNewAvail()

	vector<bool> args;
	bool a;

	a = false; a = evalMitCrdNewAvail(dbsidec);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecTou::evalMitCrdNewAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

