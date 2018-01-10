/**
  * \file CrdIdecMis_evals.cpp
  * job handler for job CrdIdecMis (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool CrdIdecMis::evalMspCrd1Avail(
			DbsIdec* dbsidec
		) {
	// MitCrdNewAvail()

	vector<bool> args;
	bool a;

	a = false; a = evalMitCrdNewAvail(dbsidec);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecMis::evalMitCrdNewAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

