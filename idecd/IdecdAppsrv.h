/**
  * \file IdecdAppsrv.h
  * application server for Idec daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECDAPPSRV_H
#define IDECDAPPSRV_H

#ifndef _WIN32
	#include <arpa/inet.h>
#endif

#include "RootIdec.h"

/**
  * IdecdAppsrv
  */
namespace IdecdAppsrv {
	MHD_Daemon* start(XchgIdecd* xchg);
	void stop(MHD_Daemon* d);

	int MhdAccept(void* cls, const sockaddr* addr, socklen_t addrlen);
	int MhdCallback(void* cls, MHD_Connection* connection, const char* url, const char* method, const char* version, const char* upload_data, size_t* upload_data_size, void** con_cls);
#ifdef _WIN32
	int MhdFilesend(void* con_cls, uint64_t pos, char* buf, int max);
#else
	ssize_t MhdFilesend(void* con_cls, uint64_t pos, char* buf, size_t max);
#endif
	int MhdPostrecv(void* con_cls, MHD_ValueKind kind, const char* key, const char* filename, const char* content_type, const char* transfer_encoding, const char* data, uint64_t off, size_t size);
	void MhdComplete(void* cls, MHD_Connection* connection, void** con_cls, MHD_RequestTerminationCode toe);

	bool validateIp(XchgIdecd* xchg, ReqIdec* req);
	bool validateJrefNotify(XchgIdecd* xchg, ReqIdec* req);
	uint readDpchApp(XchgIdecd* xchg, ReqIdec* req);
	void writeDpchEng(XchgIdecd* xchg, ReqIdec* req);
};

#endif

