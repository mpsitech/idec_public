/**
  * \file PnlIdecUsrDetail_evals.cpp
  * job handler for job PnlIdecUsrDetail (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUsrDetail::evalButSaveAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalButSaveActive(
			DbsIdec* dbsidec
		) {
	// dirty()

	vector<bool> args;
	bool a;

	a = false; a = dirty;
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalTxtPrsActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalTxtSrfActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalTxtUsgActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalButUsgViewAvail(
			DbsIdec* dbsidec
		) {
	// usr.usgEq(0)|(pre.ixUacUsg())

	vector<bool> args;
	bool a, b;

	a = false; a = (recUsr.refIdecMUsergroup == 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecUsrDetail::evalButUsgViewActive(
			DbsIdec* dbsidec
		) {
	// !usr.usgEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (recUsr.refIdecMUsergroup == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalPupJActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalButJEditAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalPupSteActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalPupLclActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalPupUlvActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUsrDetail::evalTxfPwdActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsrIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

