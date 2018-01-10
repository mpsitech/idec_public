/**
  * \file PnlIdecUsrMNUsergroup_evals.cpp
  * job handler for job PnlIdecUsrMNUsergroup (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsrMNUsergroup::evalButViewAvail(
			DbsIdec* dbsidec
		) {
	// !sel()|(pre.ixUacUsg())

	vector<bool> args;
	bool a, b;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecUsrMNUsergroup::evalButViewActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrMNUsergroup::evalButAddAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrMNUsergroup::evalButSubAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrMNUsergroup::evalButSubActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

