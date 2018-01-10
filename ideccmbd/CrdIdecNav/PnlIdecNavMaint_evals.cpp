/**
  * \file PnlIdecNavMaint_evals.cpp
  * job handler for job PnlIdecNavMaint (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecNavMaint::evalLstUsgAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsg()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavMaint::evalButUsgViewActive(
			DbsIdec* dbsidec
		) {
	// LstUsg.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstUsg != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavMaint::evalLstUsrAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsr()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavMaint::evalButUsrViewActive(
			DbsIdec* dbsidec
		) {
	// LstUsr.sel()

	vector<bool> args;
	bool a;

	a = false; a = (contiac.numFLstUsr != 0);
	args.push_back(a);

	return(args.back());
};

