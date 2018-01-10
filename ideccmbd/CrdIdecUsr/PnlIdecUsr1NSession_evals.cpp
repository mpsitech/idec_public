/**
  * \file PnlIdecUsr1NSession_evals.cpp
  * job handler for job PnlIdecUsr1NSession (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsr1NSession::evalButDeleteAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsr1NSession::evalButDeleteActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

