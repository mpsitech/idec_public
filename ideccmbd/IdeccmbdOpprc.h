/**
  * \file IdeccmbdOpprc.h
  * operation processor for Idec combined daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECCMBDOPPRC_H
#define IDECCMBDOPPRC_H

/**
  * IdeccmbdOpprc
  */
namespace IdeccmbdOpprc {
	void* run(void* arg);
	void cleanup(void* arg);
};

#endif

