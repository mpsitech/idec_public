/**
  * \file IdecdOpengcli.cpp
  * operation engine client for Idec daemon (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Idecd.h"

#include "IdecdOpengcli.h"

/******************************************************************************
 namespace IdecdOpengcli
 ******************************************************************************/

void* IdecdOpengcli::run(
			void* arg
		) {
	XchgIdecd* xchg = (XchgIdecd*) arg;

	DpchInvIdec* inv = NULL;
	NodeIdec* node = NULL;

	pthread_t sub = 0;
	IdecdOpengcli_argsub* argsub = NULL;

	// thread settings
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
	pthread_cleanup_push(&cleanup, arg);

	// main loop: wait for ops in execution list
	while (true) {
		// see if an inv is already here
		xchg->pullFirstInv(&inv, &node);

		while (inv == NULL) {
			// no inv is here ; wait for it
			Mutex::lock(&(xchg->mcOpengcli), "xchg->mcOpengcli", "IdecdOpengcli", "run");
			Cond::wait(&(xchg->cOpengcli), &(xchg->mcOpengcli), "xchg->cOpengcli", "IdecdOpengcli", "run");

			xchg->pullFirstInv(&inv, &node);

			Mutex::unlock(&(xchg->mcOpengcli), "xchg->mcOpengcli", "IdecdOpengcli", "run");
		};

		// launch thread to perform op remotely
		argsub = new IdecdOpengcli_argsub;
		argsub->xchg = xchg;
		argsub->inv = inv;
		argsub->node = node;

		// the sub-thread will not be joined, thus no corresponding attribute
		pthread_create(&sub, 0, &IdecdOpengcli_sub::run, (void*) argsub);
	};

	pthread_cleanup_pop(0);

	return(NULL);
};

void IdecdOpengcli::cleanup(
			void* arg
		) {
	XchgIdecd* xchg = (XchgIdecd*) arg;

	Mutex::unlock(&(xchg->mcOpengcli), "xchg->mcOpengcli", "IdecdOpengcli", "cleanup");
};

/******************************************************************************
 namespace IdecdOpengcli_sub
 ******************************************************************************/

void* IdecdOpengcli_sub::run(
			void* _arg
		) {
	IdecdOpengcli_argsub* arg = (IdecdOpengcli_argsub*) _arg;

	// thread settings
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);

	// copy content of arg and delete wrapping structure
	XchgIdecd* xchg = arg->xchg;
	NodeIdec* node = arg->node;
	DpchInvIdec* inv = arg->inv;

	delete arg;

	// get connection (existing if possible)
	ConopengIdec* con = node->getCon();

	// reply of cURL operation is to be written in ret
	ReqIdec* req = new ReqIdec(ReqIdec::VecVBasetype::RET);

	req->dpchinv = inv;
	writeDpchInv(xchg, req);

	CURLcode curlres;

	// curl_easy_setopt(con->curl, CURLOPT_VERBOSE, 1);

	curl_easy_setopt(con->curl, CURLOPT_POST, 1);
	curl_easy_setopt(con->curl, CURLOPT_POSTFIELDS, req->request);
	curl_easy_setopt(con->curl, CURLOPT_POSTFIELDSIZE, req->requestlen);

	curl_easy_setopt(con->curl, CURLOPT_WRITEFUNCTION, CurlPostrecv);
	curl_easy_setopt(con->curl, CURLOPT_WRITEDATA, req);

	curlres = curl_easy_perform(con->curl);

	// on transfer done, un-busy connection and node
	Mutex::lock(&(xchg->mNodes), "xchg->mNodes", "IdecdOpengcli_sub", "run");
	Mutex::lock(&(node->mCons), "node->mCons", "IdecdOpengcli_sub", "run");

	con->busy = false;

	node->opprcbusy--;
	node->err = (curlres != 0);

	Mutex::unlock(&(node->mCons), "node->mCons", "IdecdOpengcli_sub", "run");
	Mutex::unlock(&(xchg->mNodes), "xchg->mNodes", "IdecdOpengcli_sub", "run");

	// an additional node is available for pending ops
	Cond::signal(&(xchg->cOpengcli), &(xchg->mcOpengcli), "xchg->cOpengcli", "xchg->mcOpengcli", "IdecdOpengcli_sub", "run");

	if ((curlres == 0) && req->reply) {
		// cout << req->reply << endl;
		readDpchRet(xchg, req);
		req->jref = req->dpchret->jref;
		xchg->addReq(req);

	} else {
		// something went wrong, return inv to list
		xchg->returnInv(inv);

		req->dpchinv = NULL;
		delete req;
	};

	return(NULL);
};

uint IdecdOpengcli_sub::CurlPostrecv(
			void* data
			, uint size
			, uint blocksize
			, void* _req
		) {
	ReqIdec* req = (ReqIdec*) _req;

	char* olddata;

	if (size > 0) {
		if (!req->reply) {
			req->reply = new char[size*blocksize];
			memcpy(req->reply, data, size*blocksize);
			req->replylen = size*blocksize;

		} else {
			olddata = req->reply;

			req->reply = new char[req->replylen + size*blocksize];
			memcpy(req->reply, olddata, req->replylen);
			memcpy(&(req->reply[req->replylen]), data, size*blocksize);
			req->replylen = req->replylen + size*blocksize;

			delete[] olddata;
		};
	};

  return(size*blocksize);
};

uint IdecdOpengcli_sub::readDpchRet(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;

	parseBuffer(req->reply, req->replylen, &doc, &docctx);

	uint ixIdecVDpch = VecIdecVDpch::getIx(extractRoot(doc));

	if (ixIdecVDpch == VecIdecVDpch::DPCHRETIDEC) {
		req->dpchret = new DpchRetIdec();
		((DpchRetIdec*) (req->dpchret))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	};

	if (docctx) xmlXPathFreeContext(docctx);
	if (doc) xmlFreeDoc(doc);
	
	return ixIdecVDpch;
};

void IdecdOpengcli_sub::writeDpchInv(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	xmlBuffer* buf = NULL;
	xmlTextWriter* wr = NULL;

	startwriteBuffer(&wr, &buf);
		req->dpchinv->writeXML(&(xchg->mScr), xchg->scr, xchg->descr, wr);
	closewriteBuffer(wr);

	req->requestlen = buf->use;
	req->request = new char[req->requestlen];
	memcpy(req->request, buf->content, req->requestlen);

		// string to be sent is "xml=<xbuf>"
	req->requestlen = buf->use + 4;
	req->request = new char[req->requestlen];
	req->request[0] = 'x'; req->request[1] = 'm'; req->request[2] = 'l'; req->request[3] = '=';
	memcpy(&(req->request[4]), buf->content, buf->use);

	// strip '\r' and '\n' characters
	for (size_t i=0;i<req->requestlen;) {
		if ((req->request[i] == '\r') || (req->request[i] == '\n')) {
			memmove(&(req->request[i]), &(req->request[i+1]), req->requestlen-i-1);
			req->requestlen--;
		} else i++;
	};

	xmlBufferFree(buf);
};

