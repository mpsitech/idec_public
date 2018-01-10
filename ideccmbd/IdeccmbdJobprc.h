/**
  * \file IdeccmbdJobprc.h
  * job processor for Idec combined daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECCMBDJOBPRC_H
#define IDECCMBDJOBPRC_H

/**
  * IdeccmbdJobprc
  */
namespace IdeccmbdJobprc {
	void* run(void* arg);
	void cleanup(void* arg);

	void accessJob(XchgIdeccmbd* xchg, DbsIdec* dbsidec, ReqIdec* req);
};

#endif



