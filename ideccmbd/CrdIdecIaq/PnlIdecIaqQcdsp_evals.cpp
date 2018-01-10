/**
  * \file PnlIdecIaqQcdsp_evals.cpp
  * job handler for job PnlIdecIaqQcdsp (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecIaqQcdsp::evalPupModActive(
			DbsIdec* dbsidec
		) {
	// jobqcdacq.mast()

	vector<bool> args;
	bool a;

	a = false; if (jobqcdacq) a = (jobqcdacq->jrefMast == jobqcdacq->jref);
	args.push_back(a);

	return(args.back());
};

