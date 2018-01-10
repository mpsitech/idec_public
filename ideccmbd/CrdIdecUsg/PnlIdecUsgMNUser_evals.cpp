/**
  * \file PnlIdecUsgMNUser_evals.cpp
  * job handler for job PnlIdecUsgMNUser (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsgMNUser::evalButViewAvail(
			DbsIdec* dbsidec
		) {
	// !sel()|(pre.ixUacUsr())

	vector<bool> args;
	bool a, b;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecUsgMNUser::evalButViewActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgMNUser::evalButAddAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsgIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgMNUser::evalButSubAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsgIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgMNUser::evalButSubActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

