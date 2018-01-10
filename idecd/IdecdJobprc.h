/**
  * \file IdecdJobprc.h
  * job processor for Idec daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECDJOBPRC_H
#define IDECDJOBPRC_H

/**
  * IdecdJobprc
  */
namespace IdecdJobprc {
	void* run(void* arg);
	void cleanup(void* arg);

	void accessJob(XchgIdecd* xchg, DbsIdec* dbsidec, ReqIdec* req);
};

#endif

