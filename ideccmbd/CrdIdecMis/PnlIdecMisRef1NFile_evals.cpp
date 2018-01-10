/**
  * \file PnlIdecMisRef1NFile_evals.cpp
  * job handler for job PnlIdecMisRef1NFile (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecMisRef1NFile::evalButViewAvail(
			DbsIdec* dbsidec
		) {
	// !sel()|(pre.ixUacFil()&pre.refMis())

	vector<bool> args;
	bool a, b;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) != 0);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a || b);

	return(args.back());
};

bool PnlIdecMisRef1NFile::evalButViewActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisRef1NFile::evalButNewAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacFilIncl(edit)&pre.refMis()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecMisRef1NFile::evalButDeleteAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMisRef1NFile::evalButDeleteActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

