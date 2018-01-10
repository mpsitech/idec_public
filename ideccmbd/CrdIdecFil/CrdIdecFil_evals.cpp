/**
  * \file CrdIdecFil_evals.cpp
  * job handler for job CrdIdecFil (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool CrdIdecFil::evalMitCrdExmActive(
			DbsIdec* dbsidec
		) {
	// pre.refFil()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFFIL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

