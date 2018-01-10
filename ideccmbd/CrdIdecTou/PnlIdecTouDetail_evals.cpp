/**
  * \file PnlIdecTouDetail_evals.cpp
  * job handler for job PnlIdecTouDetail (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecTouDetail::evalButSaveAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalButSaveActive(
			DbsIdec* dbsidec
		) {
	// dirty()

	vector<bool> args;
	bool a;

	a = false; a = dirty;
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfTitActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxtMisActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalButMisViewAvail(
			DbsIdec* dbsidec
		) {
	// tou.misEq(0)|(pre.ixUacMis())

	vector<bool> args;
	bool a, b;

	a = false; a = (recTou.refIdecMMission == 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecTouDetail::evalButMisViewActive(
			DbsIdec* dbsidec
		) {
	// !tou.misEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (recTou.refIdecMMission == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfStaActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfStoActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfAreActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfTheActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfPhiActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecTouDetail::evalTxfCmtActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

