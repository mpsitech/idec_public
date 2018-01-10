/**
  * \file PnlIdecUsgDetail_evals.cpp
  * job handler for job PnlIdecUsgDetail (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsgDetail::evalButSaveAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsgIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgDetail::evalButSaveActive(
			DbsIdec* dbsidec
		) {
	// dirty()

	vector<bool> args;
	bool a;

	a = false; a = dirty;
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgDetail::evalTxtSrfActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsgIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsgDetail::evalTxfCmtActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsgIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

