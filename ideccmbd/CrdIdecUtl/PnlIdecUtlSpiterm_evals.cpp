/**
  * \file PnlIdecUtlSpiterm_evals.cpp
  * job handler for job PnlIdecUtlSpiterm (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecUtlSpiterm::evalPupTrgActive(
			DbsIdec* dbsidec
		) {
	// sge(idle)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::IDLE);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalButCctActive(
			DbsIdec* dbsidec
		) {
	// sge(idle)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::IDLE);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalButDctActive(
			DbsIdec* dbsidec
		) {
	// !sge(idle)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::IDLE);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalButOsmActive(
			DbsIdec* dbsidec
		) {
	// sge(ctd)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::CTD);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalRbuPetActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalPupPcmActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalTxfPcsActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalTxfPhsActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalTxfPfnActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalSldPinActive(
			DbsIdec* dbsidec
		) {
	// !sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalButPrnActive(
			DbsIdec* dbsidec
		) {
	// sge(ctd)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::CTD);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecUtlSpiterm::evalButPstActive(
			DbsIdec* dbsidec
		) {
	// sge(prdexec)

	vector<bool> args;
	bool a;

	a = false; a = (ixVSge == VecVSge::PRDEXEC);
	args.push_back(a);

	return(args.back());
};

