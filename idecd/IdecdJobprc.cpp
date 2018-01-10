/**
  * \file IdecdJobprc.cpp
  * job processor for Idec daemon (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Idecd.h"

#include "IdecdJobprc.h"

/******************************************************************************
 namespace IdecdJobprc
 ******************************************************************************/

void* IdecdJobprc::run(
			void* arg
		) {
	XchgIdecd* xchg = (XchgIdecd*) arg;

	ReqIdec* req = NULL;
	JobIdec* job = NULL;

	ubigint eref;

	// thread settings
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
	pthread_cleanup_push(&cleanup, arg);

	// open database connection
	DbsIdec dbsidec;
	int contry = 10;

	while (contry > 0) {
		try {
			dbsidec.init(xchg->stgidecdatabase.ixDbsVDbstype, xchg->stgidecdatabase.dbspath, xchg->stgidecdatabase.dbsname, xchg->stgidecdatabase.ip,
						xchg->stgidecdatabase.port, xchg->stgidecdatabase.username, xchg->stgidecdatabase.password);
			break;
		} catch (DbsException e) {
			contry--;
			if (contry == 0) throw;
		};
	};

	// main loop: wait for requests
	while (true) {
		// req is already here
		req = xchg->pullFirstReq();

		while (req == NULL) {
			// no req here ; wait for it
			Mutex::lock(&(xchg->mcJobprcs), "xchg->mcJobprcs", "IdecdJobprc", "run");
			Cond::wait(&(xchg->cJobprcs), &(xchg->mcJobprcs), "xchg->cJobprcs", "IdecdJobprc", "run");

			req = xchg->pullFirstReq();

			Mutex::unlock(&(xchg->mcJobprcs), "xchg->mcJobprcs", "IdecdJobprc", "run");
		};

		// re-signal condition to avoid using broadcast
		Cond::signal(&(xchg->cJobprcs), &(xchg->mcJobprcs), "xchg->cJobprcs", "xchg->mcJobprcs", "IdecdJobprc", "run");

		// --- handle request
		if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
			xchg->mon.eventHandleReqCmd(req->jref, req->cmd);

			// pass on to job
			accessJob(xchg, &dbsidec, req);

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
			if (req->dpchapp) {
				//cout << "IdecdJobprc::run() REGULAR request: '" << VecIdecVDpch::getSref(req->dpchapp->ixIdecVDpch) << "'" << endl;
				eref = xchg->mon.eventHandleReqRegular(req->jref, VecIdecVDpch::getSref(req->dpchapp->ixIdecVDpch), req->dpchapp->getSrefsMask(), "");

				// pass on to job
				accessJob(xchg, &dbsidec, req);
			};

			if (!req->dpcheng) req->dpcheng = new DpchEngIdecAck(req->jref);
			xchg->mon.eventReplyReqRegular(eref, req->jref, VecIdecVDpch::getSref(req->dpcheng->ixIdecVDpch), req->dpcheng->getSrefsMask(), "");

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::UPLOAD) {
			//cout << "IdecdJobprc::run() UPLOAD request file name: '" << req->filename << "'" << endl;
			xchg->mon.eventHandleReqUpload(req->jref, req->filename);

			// pass on to job
			accessJob(xchg, &dbsidec, req);

			// usually the job leaves req unchanged

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::DOWNLOAD) {
			eref = xchg->mon.eventHandleReqDownload(req->jref);

			// pass on to job
			accessJob(xchg, &dbsidec, req);

			xchg->mon.eventReplyReqDownload(eref, req->jref, req->filename);

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::RET) {
			if (req->dpchret) {
				//cout << "IdecdJobprc::run() RET request: '" << VecIdecVDpch::getSref(req->dpchret->ixIdecVDpch) << "'" << endl;

				job = xchg->getJobByJref(req->jref);
				if (job) job->removeOp(req->dpchret->oref);

				xchg->mon.eventHandleReqRet(req->jref, VecIdecVDpch::getSref(req->dpchret->ixIdecVDpch), "", req->dpchret->oref);

				accessJob(xchg, &dbsidec, req);
			};

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
			// pass on to job
			job = xchg->getJobByJref(req->jref);

			if (job) if (req->wref >= job->wrefMin) {
				xchg->mon.eventHandleReqTimer(req->jref, req->sref);
				accessJob(xchg, &dbsidec, req);
			};

		} else if (req->ixVBasetype == ReqIdec::VecVBasetype::EXTCALL) {
			xchg->triggerCall(&dbsidec, req->call);
		};

		if ((req->ixVBasetype == ReqIdec::VecVBasetype::RET) || (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) || (req->ixVBasetype == ReqIdec::VecVBasetype::EXTCALL)) {
			// ret, timer and extcall requests can be deleted here
			delete req;

		} else {
			// all other requests are being waited for for further processing
			if (!(req->retain)) req->setStateReply();
		};
	};

	pthread_cleanup_pop(0);

	return(NULL);
};

void IdecdJobprc::cleanup(
			void* arg
		) {
	XchgIdecd* xchg = (XchgIdecd*) arg;

	Mutex::unlock(&(xchg->mcJobprcs), "xchg->mcJobprcs", "IdecdJobprc", "cleanup");
};

void IdecdJobprc::accessJob(
			XchgIdecd* xchg
			, DbsIdec* dbsidec
			, ReqIdec* req
		) {
	JobIdec* job = NULL;
	
	job = xchg->getJobByJref(req->jref);
	if (job) {
		if (!req->weak) job->lockAccess("IdecdJobprc", "accessJob");

		req->ixIdecVLocale = job->ixIdecVLocale;
		job->handleRequest(dbsidec, req);
	};

	if (!req->weak) {
		job = xchg->getJobByJref(req->jref);
		if (job) job->unlockAccess("IdecdJobprc", "accessJob");
	};
};

