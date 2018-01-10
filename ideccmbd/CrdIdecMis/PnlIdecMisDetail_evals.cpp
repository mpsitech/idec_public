/**
  * \file PnlIdecMisDetail_evals.cpp
  * job handler for job PnlIdecMisDetail (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecMisDetail::evalButSaveAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalButSaveActive(
			DbsIdec* dbsidec
		) {
	// dirty()

	vector<bool> args;
	bool a;

	a = false; a = dirty;
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfTitActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfStaActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfStoActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalPupCryActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalButCryEditAvail(
			DbsIdec* dbsidec
		) {
	// pre.adm()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getBoolvalPreset(VecIdecVPreset::PREIDECADM, jref));
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfRegActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfMunActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisDetail::evalTxfCmtActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

