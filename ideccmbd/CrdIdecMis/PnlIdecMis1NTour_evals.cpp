/**
  * \file PnlIdecMis1NTour_evals.cpp
  * job handler for job PnlIdecMis1NTour (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecMis1NTour::evalButViewAvail(
			DbsIdec* dbsidec
		) {
	// !sel()|(pre.ixUacTou()&pre.refMis())

	vector<bool> args;
	bool a, b;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);
	a = args.back(); args.pop_back();
	args.push_back(!a);
	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) != 0);
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

bool PnlIdecMis1NTour::evalButViewActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMis1NTour::evalButNewAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacTouIncl(edit)&pre.refMis()

	vector<bool> args;
	bool a, b;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);
	a = false; a = (xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref) != 0);
	args.push_back(a);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	args.push_back(a && b);

	return(args.back());
};

bool PnlIdecMis1NTour::evalButDeleteAvail(
			DbsIdec* dbsidec
		) {
	// pre.ixUacMisIncl(edit)

	vector<bool> args;
	bool a;

	a = false; a = (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref) & VecIdecWUiaccess::EDIT);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecMis1NTour::evalButDeleteActive(
			DbsIdec* dbsidec
		) {
	// sel()

	vector<bool> args;
	bool a;

	a = false; a = (qry->stgiac.jnum != 0);
	args.push_back(a);

	return(args.back());
};

