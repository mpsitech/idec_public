/**
  * \file IdecdAppsrv.cpp
  * application server for Idec daemon (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Idecd.h"

#include "IdecdAppsrv.h"

/******************************************************************************
 namespace IdecdAppsrv
 ******************************************************************************/

MHD_Daemon* IdecdAppsrv::start(
			XchgIdecd* xchg
		) {
//	return MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, xchg->stgidecd.appsrvport, &MhdAccept, (void*) xchg, &MhdCallback, (void*) xchg, MHD_OPTION_NOTIFY_COMPLETED, &MhdComplete, (void*) xchg, MHD_OPTION_THREAD_POOL_SIZE, 16, MHD_OPTION_END);
	return MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, xchg->stgidecd.appsrvport, &MhdAccept, (void*) xchg, &MhdCallback, (void*) xchg, MHD_OPTION_NOTIFY_COMPLETED, &MhdComplete, (void*) xchg, MHD_OPTION_END);
};

void IdecdAppsrv::stop(
			MHD_Daemon* d
		) {
	MHD_stop_daemon(d);
};

int IdecdAppsrv::MhdAccept(
			void* cls
			, const sockaddr* addr
			, socklen_t addrlen
		) {
	return MHD_YES;
};

int IdecdAppsrv::MhdCallback(
			void* cls
			, MHD_Connection* connection
			, const char* url
			, const char* method
			, const char* version
			, const char* upload_data
			, size_t* upload_data_size
			, void** con_cls
		) {
	XchgIdec* xchg = (XchgIdec*) cls;

  MHD_Response* response;
	int retval = MHD_YES;

	ReqIdec* req;
	uint ixVBasetype = ReqIdec::VecVBasetype::NONE;

	sockaddr* addr;

	string ip;
#ifndef _WIN32
	char ipstr[64];
#endif

	string mimetype;
	size_t ptr;

	uint ixIdecVDpch;

	ubigint jrefNotify;

	DcolIdec* dcol;

	char empty[] = "\n";
	char invalid[] = "<html><head><title>Invalid request</title></head><body><p>Invalid request!</p></body></html>";

	string s, s2;

	bool valid;

	if (*con_cls == NULL) {
		// new request
		s = string(url);

		if (strcmp(method, "GET") == 0) {
			// cout << "have GET request, url is '" << s << "'" << endl;

			if (s.find("/web/") != string::npos) {
				// cout << "request for '" << s.substr(4) << "' by html transfer" << endl;

				// ex. "/web/CrdIdecNav/CrdIdecNav.html" ; note that eventual parameters such as "?scrJref=abcd1234efgh5678" are not included in url

				// inhibit requests to ../ directories
				if (s.find("../") == string::npos) {

					// check if file exists
					s2 = xchg->stgidecpath.webpath + s.substr(4);
					if (access(s2.c_str(), R_OK) == 0) {
						ixVBasetype = ReqIdec::VecVBasetype::WEB;
						// cout << "MhdCallback() WEB request for '" << s2 << "'" << endl;
					};
				};

			} else if (s.find("/notify") != string::npos) {
				// always "/notify/abcd1234efgh5678/..."
				ixVBasetype = ReqIdec::VecVBasetype::NOTIFY;

			} else if (s.find("/poll") != string::npos) {
				// always "/poll/abcd1234efgh5678/..."
				ixVBasetype = ReqIdec::VecVBasetype::POLL;

			} else if (s.find("/download/") != string::npos) {
				// ex. "/download/abcd1234efgh5678/..."
				ixVBasetype = ReqIdec::VecVBasetype::DOWNLOAD;
			};

		} else if (strcmp(method, "POST") == 0) {
			if (s.find("/dpch") != string::npos) {
				// always "/dpch"
				ixVBasetype = ReqIdec::VecVBasetype::REGULAR;

			} else if (s.find("/upload/") != string::npos) {
				// ex. "/upload/abcd1234efgh5678"
				ixVBasetype = ReqIdec::VecVBasetype::UPLOAD;
			};
		};

		if (ixVBasetype == ReqIdec::VecVBasetype::NONE) {
			// not a valid request
			response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
			//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
			retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
			MHD_destroy_response(response);

		} else {
			addr = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS)->client_addr;

			if (addr->sa_family == AF_INET) {
#ifdef _WIN32
				ip = inet_ntoa(((sockaddr_in*)addr)->sin_addr);
#else
				inet_ntop(AF_INET, &(((sockaddr_in*)addr)->sin_addr), ipstr, 64);
				ip = ipstr;
#endif
			};

			req = new ReqIdec(ixVBasetype, ReqIdec::VecVState::RECEIVE, ip);

			*con_cls = req;

			if (req->ixVBasetype == ReqIdec::VecVBasetype::WEB) {
				// --- open file and initiate transmission
				req->filename = xchg->stgidecpath.webpath + s.substr(4);

				req->file = new fstream();
				req->file->open(req->filename.c_str(), fstream::in | fstream::binary);

				// get file length
				req->file->seekg(0, ios::end);
				req->filelen = req->file->tellg();
				req->file->seekg(0, ios::beg);

				if (req->filelen == 0) {
					// empty files require special handling
					response = MHD_create_response_from_buffer(strlen(empty), empty, MHD_RESPMEM_PERSISTENT);
					//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
					retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
					MHD_destroy_response(response);

				} else {
					response = MHD_create_response_from_callback(req->filelen, 8*1024, &MhdFilesend, req, NULL);

					// determine MIME type from file extension
					ptr = req->filename.rfind('.');
					if (ptr != string::npos) mimetype = VecIdecVMimetype::getTitle(VecIdecVMimetype::getIx(req->filename.substr(ptr+1)));
					if (mimetype.length() == 0) mimetype = VecIdecVMimetype::getTitle(VecIdecVMimetype::TXT);
					MHD_add_response_header(response, "Content-Type", mimetype.c_str());					

					//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
					retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
					MHD_destroy_response(response);
				};

			} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
				// --- prepare POST processor
				req->pp = MHD_create_post_processor(connection, 8*1024, MhdPostrecv, req);

			} else if (req->ixVBasetype == ReqIdec::VecVBasetype::NOTIFY) {
				// --- notify on dispatch in dispatch collector
				req->jref = Scr::descramble(&(xchg->mScr), xchg->descr, s.substr(s.find("/notify/")+8));
				valid = (req->jref != 0);

				if (valid) valid = validateIp(xchg, req);

				if (valid) {
					jrefNotify = xchg->getRefPreset(VecIdecVPreset::PREIDECJREFNOTIFY, req->jref);

					dcol = xchg->getDcolByJref(req->jref);
					if (!dcol) {
						dcol = xchg->addDcol(req->jref);
						if (dcol) jrefNotify = req->jref;
					};

					valid = dcol;
				};

				if (valid) {
					req->ixIdecVLocale = dcol->ixIdecVLocale;

					if (dcol->dpchs.empty()) {
						if (dcol->hot) {
							// send default reply immediately
							req->dpcheng = new DpchEngIdecAck(req->jref);

							dcol->hot = false;
							dcol->unlockAccess("IdecdAppsrv", "MhdCallback[1]");

						} else if (jrefNotify != dcol->jref) {
							// ask client to resort to POLL mode
							req->dpcheng = new DpchEngIdecSuspend(req->jref);

							dcol->unlockAccess("IdecdAppsrv", "MhdCallback[2]");

						} else {
							// wait for next notification to arrive in dispatch collector
							
							// default req->dpcheng to be overwritten
							req->dpcheng = new DpchEngIdecAck(req->jref);
							dcol->req = req;

							// note: when dcol with req != NULL is deleted, req->cReady will be broadcast
							Mutex::lock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[1]");
							dcol->unlockAccess("IdecdAppsrv", "MhdCallback[3]");
							Cond::timedwait(&(req->cReady), &(req->mcReady), 15000000, "req->cReady", "IdecdAppsrv", "MhdCallback");
							// cout << "got one after timedwait" << endl;
							Mutex::unlock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[1]");

							dcol = xchg->getDcolByJref(req->jref);
							if (dcol) {
								// note: the destructor of dcol is called after dcol is removed from the list from which it can be found by getDcolByJref()
								dcol->req = NULL;
								dcol->unlockAccess("IdecdAppsrv", "MhdCallback[4]");

							} else {
								delete req->dpcheng;
								req->dpcheng = new DpchEngIdecConfirm(false, req->jref);
							};
						};

						writeDpchEng(xchg, req);
						req->ixVState = ReqIdec::VecVState::REPLY;

						// send reply ; note that the result of Cond::timedwait() doesn't matter
						response = MHD_create_response_from_buffer(req->replylen, req->reply, MHD_RESPMEM_PERSISTENT);
						retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
						MHD_destroy_response(response);

					} else {
						req->dpcheng = xchg->pullFirstDpch(dcol);
						// cout << "pulled one" << endl;

						dcol->hot = true;
						dcol->unlockAccess("IdecdAppsrv", "MhdCallback[5]");

						writeDpchEng(xchg, req);
						req->ixVState = ReqIdec::VecVState::REPLY;

						// send first dispatch available in dispatch collector
						response = MHD_create_response_from_buffer(req->replylen, req->reply, MHD_RESPMEM_PERSISTENT);
						retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
						MHD_destroy_response(response);
					};
				};

				if (!valid) {
					response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
					retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
					MHD_destroy_response(response);
				};

			} else if (req->ixVBasetype == ReqIdec::VecVBasetype::POLL) {
				// --- send first dispatch available in dispatch collector
				req->jref = Scr::descramble(&(xchg->mScr), xchg->descr, s.substr(s.find("/poll/")+6));
				valid = (req->jref != 0);

				if (valid) valid = validateIp(xchg, req);

				if (valid) {
					dcol = xchg->getDcolByJref(req->jref);
					if (!dcol) dcol = xchg->addDcol(req->jref);

					valid = dcol;
				};

				if (valid) {
					req->ixIdecVLocale = dcol->ixIdecVLocale;
					dcol->hot = false;

					if (dcol->dpchs.empty()) {
						// send default reply
						req->dpcheng = new DpchEngIdecAck(req->jref);

					} else {
						req->dpcheng = xchg->pullFirstDpch(dcol);
						// cout << "pulled one" << endl;
					};

					dcol->unlockAccess("IdecdAppsrv", "MhdCallback[6]");

					writeDpchEng(xchg, req);
					req->ixVState = ReqIdec::VecVState::REPLY;

					// send reply
					response = MHD_create_response_from_buffer(req->replylen, req->reply, MHD_RESPMEM_PERSISTENT);
					retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
					MHD_destroy_response(response);
				};

				if (!valid) {
					response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
					retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
					MHD_destroy_response(response);
				};

			} else if (req->ixVBasetype == ReqIdec::VecVBasetype::UPLOAD) {
				req->jref = Scr::descramble(&(xchg->mScr), xchg->descr, s.substr(s.find("/upload/")+8));

				// generate file in tmp directory, and open it
				req->filename = xchg->stgidecpath.tmppath + "/" + Tmp::newfile(xchg->stgidecpath.tmppath, "");

				req->pp = MHD_create_post_processor(connection, 8*1024, MhdPostrecv, req);

			} else if (req->ixVBasetype == ReqIdec::VecVBasetype::DOWNLOAD) {
				// --- pass request to jobprc, to ask for filename in tmp directory ; then proceed sending - same procedure as for HTML
				req->jref = Scr::descramble(&(xchg->mScr), xchg->descr, s.substr(s.find("/download/")+10));
				valid = validateIp(xchg, req);

				if (valid) {
					validateJrefNotify(xchg, req);

					xchg->addReq(req);

					// wait for reply
					Mutex::lock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[2]");
					Cond::wait(&(req->cReady), &(req->mcReady), "req->cReady", "IdecdAppsrv", "MhdCallback[1]");
					Mutex::unlock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[2]");

					// cout << "preparing '" << req->filename << "' for download transfer" << endl;

					valid = (access(req->filename.c_str(), R_OK) == 0);
				};

				if (valid) {
					req->file = new fstream();
					req->file->open(req->filename.c_str(), fstream::in | fstream::binary);

					// get file length
					req->file->seekg(0, ios::end);
					req->filelen = req->file->tellg();
					req->file->seekg(0, ios::beg);

					if (req->filelen == 0) {
						// empty files require special handling
						response = MHD_create_response_from_buffer(strlen(empty), empty, MHD_RESPMEM_PERSISTENT);
						//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
						retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
						MHD_destroy_response(response);

					} else {
						response = MHD_create_response_from_callback(req->filelen, 8*1024, &MhdFilesend, req, NULL);
						//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
						retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
						MHD_destroy_response(response);
					};
				};

				if (!valid) {
					response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
					//MHD_add_response_header(response, MHD_HTTP_HEADER_CONNECTION, "close");
					retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
					MHD_destroy_response(response);
				};
			};
		};

	} else {
		// active/old request (GET: should not go through here ; POST: REGULAR, UPLOAD)
		req = (ReqIdec*) *con_cls;

		if (strcmp(method, "POST") == 0) {
			if (*upload_data_size != 0) {
				MHD_post_process(req->pp, upload_data, *upload_data_size);
				*upload_data_size = 0;

			} else {
				// POST done
				if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
					// --- read dispatch, pass on to job processor, and wait for reply to be transmitted
					// cout << "MhdCallback() REGULAR request complete" << endl;
					valid = req->request;
					
					if (valid) {
						//cout << req->request << endl;
						ixIdecVDpch = readDpchApp(xchg, req);
						valid = req->dpchapp;
					};

					if (valid) {
						req->jref = req->dpchapp->jref;
						valid = validateIp(xchg, req);

						if (ixIdecVDpch == VecIdecVDpch::DPCHAPPROOTIDECLOGIN) req->jref = xchg->jrefRoot;
					};

					if (valid) {
						validateJrefNotify(xchg, req);

						xchg->addReq(req);

						// wait for reply
						Mutex::lock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[3]");
						if (req->ixVState != ReqIdec::VecVState::REPLY) Cond::wait(&(req->cReady), &(req->mcReady), "req->cReady", "IdecdAppsrv", "MhdCallback[2]");
						Mutex::unlock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[3]");

						if (req->dpcheng) {
							writeDpchEng(xchg, req);
							response = MHD_create_response_from_buffer(req->replylen, req->reply, MHD_RESPMEM_PERSISTENT);
							retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
							MHD_destroy_response(response);
						} else {
							response = MHD_create_response_from_buffer(strlen(empty), empty, MHD_RESPMEM_PERSISTENT);
							retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
							MHD_destroy_response(response);
						};
					};
					
					if (!valid) {
						response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
						retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
						MHD_destroy_response(response);
					};

				} else if (req->ixVBasetype == ReqIdec::VecVBasetype::UPLOAD) {
					// --- pass notification concerning uploaded file to job processor, and wait for acknowledgement
					valid = validateIp(xchg, req);

					if (valid) {
						validateJrefNotify(xchg, req);

						xchg->addReq(req);

						// wait for reply (usually empty)
						Mutex::lock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[4]");
						Cond::wait(&(req->cReady), &(req->mcReady), "req->cReady", "IdecdAppsrv", "MhdCallback[3]");
						Mutex::unlock(&(req->mcReady), "req->mcReady", "IdecdAppsrv", "MhdCallback[4]");

						if (req->reply) {
							response = MHD_create_response_from_buffer(req->replylen, req->reply, MHD_RESPMEM_PERSISTENT);
							retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
							MHD_destroy_response(response);
						} else {
							response = MHD_create_response_from_buffer(strlen(empty), empty, MHD_RESPMEM_PERSISTENT);
							retval = MHD_queue_response(connection, MHD_HTTP_OK, response);
							MHD_destroy_response(response);
						};
					};

					if (!valid) {
						response = MHD_create_response_from_buffer(strlen(invalid), invalid, MHD_RESPMEM_PERSISTENT);
						retval = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
						MHD_destroy_response(response);
					};
				};
			};
		};
	};

	return retval;
};

#ifdef _WIN32
int IdecdAppsrv::MhdFilesend(
			void* con_cls
			, uint64_t pos
			, char* buf
			, int max
		) {
#else
ssize_t IdecdAppsrv::MhdFilesend(
			void* con_cls
			, uint64_t pos
			, char* buf
			, size_t max
		) {
#endif
	ReqIdec* req = (ReqIdec*) con_cls;

	int64_t spos = pos;
	int64_t len;

	if (req) {
		// determine length remaining
		req->file->seekg(0, ios::end);
		len = req->file->tellg();
		if (len != -1) {

			if (len > spos) {
				req->file->seekg(spos);
				req->file->read(buf, max);

				// check for errors
				if (req->file->bad()) return 0;

				if (len < (max+spos))
					return (len-spos);
				else
					return max;
			};
		};
	};

	return 0;
};

int IdecdAppsrv::MhdPostrecv(
			void* con_cls
			, MHD_ValueKind kind
			, const char* key
			, const char* filename
			, const char* content_type
			, const char* transfer_encoding
			, const char* data
			, uint64_t off
			, size_t size
		) {
	ReqIdec* req = (ReqIdec*) con_cls;

	//cout << "MhdPostrecv() with size = " << ((unsigned int) size) << endl;

	char* olddata;

	if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
		// --- copy data into req->request (append if required)
		if (strcmp(key, "xml") != 0) return MHD_NO;

		if (size > 0) {
			if (!req->request) {
				req->request = new char[size];
				memcpy(req->request, data, size);
				req->requestlen = size;

			} else {
				olddata = req->request;

				req->request = new char[req->requestlen + size];
				memcpy(req->request, olddata, req->requestlen);
				memcpy(&(req->request[req->requestlen]), data, size);
				req->requestlen = req->requestlen + size;

				delete[] olddata;
			};
		};

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::UPLOAD) {
		// --- write data into file
		if (strcmp(key, "file") != 0) return MHD_NO;

		if (size > 0) {
			req->file = new fstream();

			req->file->open(req->filename.c_str(), fstream::app | fstream::out | fstream::binary);
			req->file->write(data, size);
			req->file->close();

			delete(req->file);
			req->file = NULL;
		};

	} else {
		return MHD_NO;
	};

	return MHD_YES;
};

void IdecdAppsrv::MhdComplete(
			void* cls
			, MHD_Connection* connection
			, void** con_cls
			, MHD_RequestTerminationCode toe
		) {
	ReqIdec* req;

	//cout << "MhdComplete()" << endl;

	if (*con_cls != NULL) {
		req = (ReqIdec*) *con_cls;
		delete req;
	};

	*con_cls = NULL;
};

bool IdecdAppsrv::validateIp(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	bool retval = true;

	string ip;

	if (req->jref != 0) {
		ip = xchg->getTxtvalPreset(VecIdecVPreset::PREIDECIP, req->jref);
		if (ip != req->ip) retval = false;
	};

	return retval;
};

bool IdecdAppsrv::validateJrefNotify(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	bool retval = false;

	ubigint jrefNotify;

	DcolIdec* dcol = NULL;

	jrefNotify = xchg->getRefPreset(VecIdecVPreset::PREIDECJREFNOTIFY, req->jref);

	dcol = xchg->getDcolByJref(req->jref);

	if (dcol) {
		retval = (jrefNotify == dcol->jref);
		if (!retval) xchg->triggerIxRefCall(NULL, VecIdecVCall::CALLIDECREFPRESET, dcol->jref, VecIdecVPreset::PREIDECJREFNOTIFY, dcol->jref);

		dcol->unlockAccess("IdecdAppsrv", "validateJrefNotify");
	};

	return retval;
};

uint IdecdAppsrv::readDpchApp(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;

	parseBuffer(req->request, req->requestlen, &doc, &docctx);

	uint ixIdecVDpch = VecIdecVDpch::getIx(extractRoot(doc));

	if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECFILEXTRMEDDATA) {
		req->dpchapp = new DlgIdecFilExtrmed::DpchAppData();
		((DlgIdecFilExtrmed::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECFILEXTRMEDDO) {
		req->dpchapp = new DlgIdecFilExtrmed::DpchAppDo();
		((DlgIdecFilExtrmed::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECMISNEWDATA) {
		req->dpchapp = new DlgIdecMisNew::DpchAppData();
		((DlgIdecMisNew::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECMISNEWDO) {
		req->dpchapp = new DlgIdecMisNew::DpchAppDo();
		((DlgIdecMisNew::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDATA) {
		req->dpchapp = new DlgIdecNavLoaini::DpchAppData();
		((DlgIdecNavLoaini::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDO) {
		req->dpchapp = new DlgIdecNavLoaini::DpchAppDo();
		((DlgIdecNavLoaini::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDATA) {
		req->dpchapp = new DlgIdecTouNew::DpchAppData();
		((DlgIdecTouNew::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDO) {
		req->dpchapp = new DlgIdecTouNew::DpchAppDo();
		((DlgIdecTouNew::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLFUSIONDATA) {
		req->dpchapp = new DlgIdecUtlFusion::DpchAppData();
		((DlgIdecUtlFusion::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLFUSIONDO) {
		req->dpchapp = new DlgIdecUtlFusion::DpchAppDo();
		((DlgIdecUtlFusion::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLPHIDATA) {
		req->dpchapp = new DlgIdecUtlPhi::DpchAppData();
		((DlgIdecUtlPhi::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLPHIDO) {
		req->dpchapp = new DlgIdecUtlPhi::DpchAppDo();
		((DlgIdecUtlPhi::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDALNDATA) {
		req->dpchapp = new DlgIdecUtlQcdaln::DpchAppData();
		((DlgIdecUtlQcdaln::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDALNDO) {
		req->dpchapp = new DlgIdecUtlQcdaln::DpchAppDo();
		((DlgIdecUtlQcdaln::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDNUCDATA) {
		req->dpchapp = new DlgIdecUtlQcdnuc::DpchAppData();
		((DlgIdecUtlQcdnuc::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLQCDNUCDO) {
		req->dpchapp = new DlgIdecUtlQcdnuc::DpchAppDo();
		((DlgIdecUtlQcdnuc::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLSTEREODATA) {
		req->dpchapp = new DlgIdecUtlStereo::DpchAppData();
		((DlgIdecUtlStereo::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLSTEREODO) {
		req->dpchapp = new DlgIdecUtlStereo::DpchAppDo();
		((DlgIdecUtlStereo::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLTHETADATA) {
		req->dpchapp = new DlgIdecUtlTheta::DpchAppData();
		((DlgIdecUtlTheta::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECUTLTHETADO) {
		req->dpchapp = new DlgIdecUtlTheta::DpchAppDo();
		((DlgIdecUtlTheta::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECAD1CONTROLDATA) {
		req->dpchapp = new PnlIdecAd1Control::DpchAppData();
		((PnlIdecAd1Control::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECAD1CONTROLDO) {
		req->dpchapp = new PnlIdecAd1Control::DpchAppDo();
		((PnlIdecAd1Control::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECAD1DO) {
		req->dpchapp = new CrdIdecAd1::DpchAppDo();
		((CrdIdecAd1::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
		req->dpchapp = new DpchAppIdecAlert();
		((DpchAppIdecAlert*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDETAILDATA) {
		req->dpchapp = new PnlIdecFilDetail::DpchAppData();
		((PnlIdecFilDetail::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDETAILDO) {
		req->dpchapp = new PnlIdecFilDetail::DpchAppDo();
		((PnlIdecFilDetail::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDO) {
		req->dpchapp = new CrdIdecFil::DpchAppDo();
		((CrdIdecFil::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILLISTDATA) {
		req->dpchapp = new PnlIdecFilList::DpchAppData();
		((PnlIdecFilList::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILLISTDO) {
		req->dpchapp = new PnlIdecFilList::DpchAppDo();
		((PnlIdecFilList::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILRECDO) {
		req->dpchapp = new PnlIdecFilRec::DpchAppDo();
		((PnlIdecFilRec::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQDO) {
		req->dpchapp = new CrdIdecIaq::DpchAppDo();
		((CrdIdecIaq::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQLIVEDATA) {
		req->dpchapp = new PnlIdecIaqLive::DpchAppData();
		((PnlIdecIaqLive::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQLIVEDO) {
		req->dpchapp = new PnlIdecIaqLive::DpchAppDo();
		((PnlIdecIaqLive::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQMECHDATA) {
		req->dpchapp = new PnlIdecIaqMech::DpchAppData();
		((PnlIdecIaqMech::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQMECHDO) {
		req->dpchapp = new PnlIdecIaqMech::DpchAppDo();
		((PnlIdecIaqMech::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQQCDSPDATA) {
		req->dpchapp = new PnlIdecIaqQcdsp::DpchAppData();
		((PnlIdecIaqQcdsp::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQQCDSPDO) {
		req->dpchapp = new PnlIdecIaqQcdsp::DpchAppDo();
		((PnlIdecIaqQcdsp::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQSCILLDATA) {
		req->dpchapp = new PnlIdecIaqScill::DpchAppData();
		((PnlIdecIaqScill::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQSCILLDO) {
		req->dpchapp = new PnlIdecIaqScill::DpchAppDo();
		((PnlIdecIaqScill::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECINIT) {
		req->dpchapp = new DpchAppIdecInit();
		((DpchAppIdecInit*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMIS1NTOURDATA) {
		req->dpchapp = new PnlIdecMis1NTour::DpchAppData();
		((PnlIdecMis1NTour::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMIS1NTOURDO) {
		req->dpchapp = new PnlIdecMis1NTour::DpchAppDo();
		((PnlIdecMis1NTour::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISDETAILDATA) {
		req->dpchapp = new PnlIdecMisDetail::DpchAppData();
		((PnlIdecMisDetail::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISDETAILDO) {
		req->dpchapp = new PnlIdecMisDetail::DpchAppDo();
		((PnlIdecMisDetail::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISDO) {
		req->dpchapp = new CrdIdecMis::DpchAppDo();
		((CrdIdecMis::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISLISTDATA) {
		req->dpchapp = new PnlIdecMisList::DpchAppData();
		((PnlIdecMisList::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISLISTDO) {
		req->dpchapp = new PnlIdecMisList::DpchAppDo();
		((PnlIdecMisList::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISRECDO) {
		req->dpchapp = new PnlIdecMisRec::DpchAppDo();
		((PnlIdecMisRec::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISREF1NFILEDATA) {
		req->dpchapp = new PnlIdecMisRef1NFile::DpchAppData();
		((PnlIdecMisRef1NFile::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISREF1NFILEDO) {
		req->dpchapp = new PnlIdecMisRef1NFile::DpchAppDo();
		((PnlIdecMisRef1NFile::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVDO) {
		req->dpchapp = new CrdIdecNav::DpchAppDo();
		((CrdIdecNav::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVMAINTDATA) {
		req->dpchapp = new PnlIdecNavMaint::DpchAppData();
		((PnlIdecNavMaint::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVMAINTDO) {
		req->dpchapp = new PnlIdecNavMaint::DpchAppDo();
		((PnlIdecNavMaint::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVOPRDATA) {
		req->dpchapp = new PnlIdecNavOpr::DpchAppData();
		((PnlIdecNavOpr::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVOPRDO) {
		req->dpchapp = new PnlIdecNavOpr::DpchAppDo();
		((PnlIdecNavOpr::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVPREDO) {
		req->dpchapp = new PnlIdecNavPre::DpchAppDo();
		((PnlIdecNavPre::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECRESUME) {
		req->dpchapp = new DpchAppIdecResume();
		((DpchAppIdecResume*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFCONNDATA) {
		req->dpchapp = new PnlIdecScfConn::DpchAppData();
		((PnlIdecScfConn::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFCONNDO) {
		req->dpchapp = new PnlIdecScfConn::DpchAppDo();
		((PnlIdecScfConn::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFDO) {
		req->dpchapp = new CrdIdecScf::DpchAppDo();
		((CrdIdecScf::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFLWIRDATA) {
		req->dpchapp = new PnlIdecScfLwir::DpchAppData();
		((PnlIdecScfLwir::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFLWIRDO) {
		req->dpchapp = new PnlIdecScfLwir::DpchAppDo();
		((PnlIdecScfLwir::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFMECHDATA) {
		req->dpchapp = new PnlIdecScfMech::DpchAppData();
		((PnlIdecScfMech::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFMECHDO) {
		req->dpchapp = new PnlIdecScfMech::DpchAppDo();
		((PnlIdecScfMech::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFOPTICSDATA) {
		req->dpchapp = new PnlIdecScfOptics::DpchAppData();
		((PnlIdecScfOptics::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFOPTICSDO) {
		req->dpchapp = new PnlIdecScfOptics::DpchAppDo();
		((PnlIdecScfOptics::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFQCDDATA) {
		req->dpchapp = new PnlIdecScfQcd::DpchAppData();
		((PnlIdecScfQcd::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFQCDDO) {
		req->dpchapp = new PnlIdecScfQcd::DpchAppDo();
		((PnlIdecScfQcd::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFRECORDDATA) {
		req->dpchapp = new PnlIdecScfRecord::DpchAppData();
		((PnlIdecScfRecord::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFRECORDDO) {
		req->dpchapp = new PnlIdecScfRecord::DpchAppDo();
		((PnlIdecScfRecord::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFSTATUSDO) {
		req->dpchapp = new PnlIdecScfStatus::DpchAppDo();
		((PnlIdecScfStatus::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDATA) {
		req->dpchapp = new PnlIdecScfTrigger::DpchAppData();
		((PnlIdecScfTrigger::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDO) {
		req->dpchapp = new PnlIdecScfTrigger::DpchAppDo();
		((PnlIdecScfTrigger::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDETAILDATA) {
		req->dpchapp = new PnlIdecTouDetail::DpchAppData();
		((PnlIdecTouDetail::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDETAILDO) {
		req->dpchapp = new PnlIdecTouDetail::DpchAppDo();
		((PnlIdecTouDetail::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDO) {
		req->dpchapp = new CrdIdecTou::DpchAppDo();
		((CrdIdecTou::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOULISTDATA) {
		req->dpchapp = new PnlIdecTouList::DpchAppData();
		((PnlIdecTouList::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOULISTDO) {
		req->dpchapp = new PnlIdecTouList::DpchAppDo();
		((PnlIdecTouList::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOURECDO) {
		req->dpchapp = new PnlIdecTouRec::DpchAppDo();
		((PnlIdecTouRec::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUREF1NFILEDATA) {
		req->dpchapp = new PnlIdecTouRef1NFile::DpchAppData();
		((PnlIdecTouRef1NFile::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUREF1NFILEDO) {
		req->dpchapp = new PnlIdecTouRef1NFile::DpchAppDo();
		((PnlIdecTouRef1NFile::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGAACCESSDATA) {
		req->dpchapp = new PnlIdecUsgAAccess::DpchAppData();
		((PnlIdecUsgAAccess::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGAACCESSDO) {
		req->dpchapp = new PnlIdecUsgAAccess::DpchAppDo();
		((PnlIdecUsgAAccess::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGDETAILDATA) {
		req->dpchapp = new PnlIdecUsgDetail::DpchAppData();
		((PnlIdecUsgDetail::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGDETAILDO) {
		req->dpchapp = new PnlIdecUsgDetail::DpchAppDo();
		((PnlIdecUsgDetail::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGDO) {
		req->dpchapp = new CrdIdecUsg::DpchAppDo();
		((CrdIdecUsg::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGLISTDATA) {
		req->dpchapp = new PnlIdecUsgList::DpchAppData();
		((PnlIdecUsgList::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGLISTDO) {
		req->dpchapp = new PnlIdecUsgList::DpchAppDo();
		((PnlIdecUsgList::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGMNUSERDATA) {
		req->dpchapp = new PnlIdecUsgMNUser::DpchAppData();
		((PnlIdecUsgMNUser::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGMNUSERDO) {
		req->dpchapp = new PnlIdecUsgMNUser::DpchAppDo();
		((PnlIdecUsgMNUser::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGRECDO) {
		req->dpchapp = new PnlIdecUsgRec::DpchAppDo();
		((PnlIdecUsgRec::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSR1NSESSIONDATA) {
		req->dpchapp = new PnlIdecUsr1NSession::DpchAppData();
		((PnlIdecUsr1NSession::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSR1NSESSIONDO) {
		req->dpchapp = new PnlIdecUsr1NSession::DpchAppDo();
		((PnlIdecUsr1NSession::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRAACCESSDATA) {
		req->dpchapp = new PnlIdecUsrAAccess::DpchAppData();
		((PnlIdecUsrAAccess::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRAACCESSDO) {
		req->dpchapp = new PnlIdecUsrAAccess::DpchAppDo();
		((PnlIdecUsrAAccess::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRDETAILDATA) {
		req->dpchapp = new PnlIdecUsrDetail::DpchAppData();
		((PnlIdecUsrDetail::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRDETAILDO) {
		req->dpchapp = new PnlIdecUsrDetail::DpchAppDo();
		((PnlIdecUsrDetail::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRDO) {
		req->dpchapp = new CrdIdecUsr::DpchAppDo();
		((CrdIdecUsr::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRLISTDATA) {
		req->dpchapp = new PnlIdecUsrList::DpchAppData();
		((PnlIdecUsrList::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRLISTDO) {
		req->dpchapp = new PnlIdecUsrList::DpchAppDo();
		((PnlIdecUsrList::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRMNUSERGROUPDATA) {
		req->dpchapp = new PnlIdecUsrMNUsergroup::DpchAppData();
		((PnlIdecUsrMNUsergroup::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRMNUSERGROUPDO) {
		req->dpchapp = new PnlIdecUsrMNUsergroup::DpchAppDo();
		((PnlIdecUsrMNUsergroup::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRRECDO) {
		req->dpchapp = new PnlIdecUsrRec::DpchAppDo();
		((PnlIdecUsrRec::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLDO) {
		req->dpchapp = new CrdIdecUtl::DpchAppDo();
		((CrdIdecUtl::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLSPITERMDATA) {
		req->dpchapp = new PnlIdecUtlSpiterm::DpchAppData();
		((PnlIdecUtlSpiterm::DpchAppData*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLSPITERMDO) {
		req->dpchapp = new PnlIdecUtlSpiterm::DpchAppDo();
		((PnlIdecUtlSpiterm::DpchAppDo*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHAPPROOTIDECLOGIN) {
		req->dpchapp = new RootIdec::DpchAppLogin();
		((RootIdec::DpchAppLogin*) (req->dpchapp))->readXML(&(xchg->mScr), xchg->descr, docctx, "/", true);
	};

	if (docctx) xmlXPathFreeContext(docctx);
	if (doc) xmlFreeDoc(doc);
	
	return ixIdecVDpch;
};

void IdecdAppsrv::writeDpchEng(
			XchgIdecd* xchg
			, ReqIdec* req
		) {
	xmlBuffer* buf = NULL;
	xmlTextWriter* wr = NULL;

	startwriteBuffer(&wr, &buf);

	if (req->dpcheng) {
		req->dpcheng->writeXML(req->ixIdecVLocale, &(xchg->mScr), xchg->scr, xchg->descr, wr);
	} else {
		DpchEngIdecConfirm dpchconfirm(false, req->jref, "");
		dpchconfirm.writeXML(req->ixIdecVLocale, &(xchg->mScr), xchg->scr, xchg->descr, wr);
	};

	closewriteBuffer(wr);

	req->replylen = buf->use;
	req->reply = new char[req->replylen];
	memcpy(req->reply, buf->content, req->replylen);

	xmlBufferFree(buf);
};

