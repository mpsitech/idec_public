/**
  * \file PnlIdecNavHeadbar_evals.cpp
  * job handler for job PnlIdecNavHeadbar (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecNavHeadbar::evalMenCrdAvail(
			DbsIdec* dbsidec
		) {
	// MspCrd1Avail()|MspCrd2Avail()

	vector<bool> args;
	bool a, b;

	a = false; a = evalMspCrd1Avail(dbsidec);
	args.push_back(a);
	a = false; a = evalMspCrd2Avail(dbsidec);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMspCrd1Avail(
			DbsIdec* dbsidec
		) {
	// MitCrdUsgAvail()|MitCrdUsrAvail()|MitCrdScfAvail()|MitCrdUtlAvail()

	vector<bool> args;
	bool a, b;

	a = false; a = evalMitCrdUsgAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdUsrAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdScfAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdUtlAvail(dbsidec);
	args.push_back(a);
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

bool PnlIdecNavHeadbar::evalMitCrdUsgAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsg()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdUsrAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsr()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdScfAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacScf()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACSCF, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdUtlAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUtl()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUTL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMspCrd2Avail(
			DbsIdec* dbsidec
		) {
	// MitCrdMisAvail()|MitCrdTouAvail()|MitCrdIaqAvail()|MitCrdAd1Avail()|MitCrdFilAvail()

	vector<bool> args;
	bool a, b;

	a = false; a = evalMitCrdMisAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdTouAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdIaqAvail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdAd1Avail(dbsidec);
	args.push_back(a);
	a = false; a = evalMitCrdFilAvail(dbsidec);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);
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

bool PnlIdecNavHeadbar::evalMitCrdMisAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdTouAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTou()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdIaqAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacIaq()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACIAQ, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdAd1Avail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacAd1()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACAD1, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecNavHeadbar::evalMitCrdFilAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFil()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

