/**
  * \file CrdIdecNav_evals.cpp
  * job handler for job CrdIdecNav (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool CrdIdecNav::evalPnlpreAvail(
			DbsIdec* dbsidec
		) {
	// pre.refMis()|pre.refTou()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool CrdIdecNav::evalPnlmaintAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsg()|pre.ixUacUsr()|pre.ixUacScf()|pre.ixUacUtl()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACSCF, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUTL, jref) != 0);
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

bool CrdIdecNav::evalPnloprAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMis()|pre.ixUacTou()|pre.ixUacIaq()|pre.ixUacAd1()|pre.ixUacFil()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACIAQ, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACAD1, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) != 0);
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

bool CrdIdecNav::evalMspCrd1Avail(
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

bool CrdIdecNav::evalMitCrdUsgAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsg()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdUsrAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUsr()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdScfAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacScf()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACSCF, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdUtlAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacUtl()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUTL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMspCrd2Avail(
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

bool CrdIdecNav::evalMitCrdMisAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMis()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdTouAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTou()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdIaqAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacIaq()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACIAQ, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdIaqActive(
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

bool CrdIdecNav::evalMitCrdAd1Avail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacAd1()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACAD1, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitCrdAd1Active(
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

bool CrdIdecNav::evalMitCrdFilAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFil()

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) != 0);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMspApp2Avail(
			DbsIdec* dbsidec
		) {
	// MitAppLoiAvail()

	vector<bool> args;
	bool a;

	a = false; a = evalMitAppLoiAvail(dbsidec);
	args.push_back(a);

	return(args.back());
};

bool CrdIdecNav::evalMitAppLoiAvail(
			DbsIdec* dbsidec
		) {
	// virgin()

	vector<bool> args;
	bool a;

	a = false; {uint cnt = 0; dbsidec->loadUintBySQL("SELECT COUNT(ref) FROM TblIdecMUser WHERE sref <> 'temp'", cnt); a = (cnt == 0);};
	args.push_back(a);

	return(args.back());
};

