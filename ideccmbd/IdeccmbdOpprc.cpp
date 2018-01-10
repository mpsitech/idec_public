/**
  * \file IdeccmbdOpprc.cpp
  * operation processor for Idec combined daemon (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Ideccmbd.h"

#include "IdeccmbdOpprc.h"

/******************************************************************************
 namespace IdeccmbdOpprc
 ******************************************************************************/

void* IdeccmbdOpprc::run(
			void* arg
		) {
	XchgIdeccmbd* xchg = (XchgIdeccmbd*) arg;

	ReqIdec* req = NULL;
	DpchInvIdec* inv = NULL;

	// thread settings
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
	pthread_cleanup_push(&cleanup, arg);

	// open database connection
	DbsIdec dbsidec;
	int contry = 10;

	while (contry > 0) {
		try {
			dbsidec.init(xchg->stgidecdatabase.ixDbsVDbstype, xchg->stgidecdatabase.dbspath, xchg->stgidecdatabase.dbsname, xchg->stgidecdatabase.ip
						, xchg->stgidecdatabase.port, xchg->stgidecdatabase.username, xchg->stgidecdatabase.password);
			break;
		} catch (DbsException e) {
			contry--;
			if (contry == 0) throw;
		};
	};

	// main loop: wait for operation invocations
	while (true) {
		// an inv is already here
		inv = xchg->pullFirstInv();

		while (inv == NULL) {
			// no req is here ; wait for it
			Mutex::lock(&(xchg->mcOpprcs), "xchg->mcOpprcs", "IdeccmbdOpprc", "run");
			Cond::wait(&(xchg->cOpprcs), &(xchg->mcOpprcs), "xchg->cOpprcs", "IdeccmbdOpprc", "run");

			inv = xchg->pullFirstInv();

			Mutex::unlock(&(xchg->mcOpprcs), "xchg->mcOpprcs", "IdeccmbdOpprc", "run");
		};

		// re-signal condition to avoid using broadcast
		Cond::signal(&(xchg->cOpprcs), &(xchg->mcOpprcs), "xchg->cOpprcs", "xchg->mcOpprcs", "IdeccmbdOpprc", "run");

		// prepare request
		req = new ReqIdec(ReqIdec::VecVBasetype::RET);

		req->jref = inv->jref;
		req->dpchinv = inv;

		// perform op

		if (req->dpchret) {
			req->dpchret->oref = req->dpchinv->oref;
			req->dpchret->jref = req->dpchinv->jref;

			xchg->addReq(req);

		} else {
			delete req;
		};
	};

	pthread_cleanup_pop(0);

	return(NULL);
};

void IdeccmbdOpprc::cleanup(
			void* arg
		) {
	XchgIdeccmbd* xchg = (XchgIdeccmbd*) arg;

	Mutex::unlock(&(xchg->mcOpprcs), "xchg->mcOpprcs", "IdeccmbdOpprc", "cleanup");
};

