/**
  * \file IdecdOpengcli.h
  * operation engine client for Idec daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECDOPENGCLI_H
#define IDECDOPENGCLI_H

#include "Idecd.h"

/**
  * IdecdOpengcli
  */
namespace IdecdOpengcli {
	void* run(void* arg);
	void cleanup(void* arg);
};

/**
  * IdecdOpengcli_argsub
  */
struct IdecdOpengcli_argsub {
	XchgIdecd* xchg;
	NodeIdec* node;
	DpchInvIdec* inv;
};

/**
  * IdecdOpengcli_sub
  */
namespace IdecdOpengcli_sub {
	void* run(void* _arg);

	uint CurlPostrecv(void* data, uint size, uint blocksize, void* _ret);

	uint readDpchRet(XchgIdecd* xchg, ReqIdec* req);
	void writeDpchInv(XchgIdecd* xchg, ReqIdec* req);
};

#endif

