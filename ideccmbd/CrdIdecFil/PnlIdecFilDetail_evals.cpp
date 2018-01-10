/**
  * \file PnlIdecFilDetail_evals.cpp
  * job handler for job PnlIdecFilDetail (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecFilDetail::evalButSaveAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButSaveActive(
			DbsIdec* dbsidec
		) {
	// dirty()

	vector<bool> args;
	bool a;

	a = false; a = dirty;
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxfFnmActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalLstCluActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButCluViewActive(
			DbsIdec* dbsidec
		) {
	// LstClu.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstClu != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButCluClusterAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)&fil.cluEq(0)

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);
	a = false; a = (recFil.refIdecCFile == 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecFilDetail::evalButCluUnclusterAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)&!fil.cluEq(0)

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);
	a = false; a = (recFil.refIdecCFile == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxtReuActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButReuViewAvail(
			DbsIdec* dbsidec
		) {
	// fil.reuEq(0)|((pre.ixUacMis()&fil.retEq(mis))|(pre.ixUacTou()&fil.retEq(tou)&pre.refMis())|(pre.ixUacTou()&fil.retEq(tou)))

	vector<bool> args;
	bool a, b;

	a = false; a = (recFil.refUref == 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);
	a = false; a = (recFil.refIxVTbl == VecIdecVMFileRefTbl::MIS);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (recFil.refIxVTbl == VecIdecVMFileRefTbl::TOU);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (recFil.refIxVTbl == VecIdecVMFileRefTbl::TOU);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecFilDetail::evalButReuViewActive(
			DbsIdec* dbsidec
		) {
	// !fil.reuEq(0)

	vector<bool> args;
	bool a;

	a = false; a = (recFil.refUref == 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecFilDetail::evalPupCntActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButCntEditAvail(
			DbsIdec* dbsidec
		) {
	// pre.adm()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getBoolvalPreset(VecIdecVPreset::PREIDECADM, jref));
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxfAcvActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxfAnmActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalPupMimActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalButMimEditAvail(
			DbsIdec* dbsidec
		) {
	// pre.adm()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getBoolvalPreset(VecIdecVPreset::PREIDECADM, jref));
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxfSizActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecFilDetail::evalTxfCmtActive(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

