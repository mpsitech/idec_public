/**
  * \file IdecdOpengconsrv.h
  * op engine connection server for Idec daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECDOPENGCONSRV_H
#define IDECDOPENGCONSRV_H

#ifndef _WIN32
	#include <arpa/inet.h>
#endif

/**
  * IdecdOpengconsrv
  */
namespace IdecdOpengconsrv {
	MHD_Daemon* start(XchgIdec* xchg);
	void stop(MHD_Daemon* d);

	int MhdAccept(void* cls, const sockaddr* addr, socklen_t addrlen);
	int MhdCallback(void* cls, MHD_Connection* connection, const char* url, const char* method, const char* version, const char* upload_data, size_t* upload_data_size, void** con_cls);
	int MhdPostrecv(void* con_cls, MHD_ValueKind kind, const char* key, const char* filename, const char* content_type, const char* transfer_encoding, const char* data, uint64_t off, size_t size);
	void MhdComplete(void* cls, MHD_Connection* connection, void** con_cls, MHD_RequestTerminationCode toe);

	uint readDpch(XchgIdecd* xchg, ReqopengconIdec* req);
	void writeDpchAck(ReqopengconIdec* req);
	void writeDpchReg(XchgIdecd* xchg, ReqopengconIdec* req, const ubigint nref);
};

#endif

