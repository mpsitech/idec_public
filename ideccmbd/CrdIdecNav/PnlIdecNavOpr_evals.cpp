/**
  * \file PnlIdecNavOpr_evals.cpp
  * job handler for job PnlIdecNavOpr (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecNavOpr::evalLstMisAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButMisViewActive(
			DbsIdec* dbsidec
		) {
	// LstMis.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstMis != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalLstTouAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTou()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButTouViewActive(
			DbsIdec* dbsidec
		) {
	// LstTou.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstTou != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButTouNewcrdActive(
			DbsIdec* dbsidec
		) {
	// pre.refMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButIaqNewcrdActive(
			DbsIdec* dbsidec
		) {
	// pre.refTou()|pre.refMis()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecNavOpr::evalButAd1NewcrdActive(
			DbsIdec* dbsidec
		) {
	// pre.refTou()|pre.refMis()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecNavOpr::evalLstFilAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFil()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButFilViewActive(
			DbsIdec* dbsidec
		) {
	// LstFil.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstFil != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavOpr::evalButFilNewcrdActive(
			DbsIdec* dbsidec
		) {
	// pre.refTou()|pre.refMis()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

