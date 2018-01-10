/**
  * \file PnlIdecScfLwir_evals.cpp
  * job handler for job PnlIdecScfLwir (implementation of availability/activation evaluation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

bool PnlIdecScfLwir::evalTxfLm0Active(
			DbsIdec* dbsidec
		) {
	// joblwiracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (joblwiracq) a = (joblwiracq->jrefMast == joblwiracq->jref);
	args.push_back(a);

	return(args.back());
};

bool PnlIdecScfLwir::evalTxfLm1Active(
			DbsIdec* dbsidec
		) {
	// joblwiracq.mast()

	vector<bool> args;
	bool a;

	a = false; if (joblwiracq) a = (joblwiracq->jrefMast == joblwiracq->jref);
	args.push_back(a);

	return(args.back());
};

