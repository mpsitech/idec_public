/**
  * \file SessIdec.h
  * API code for job SessIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef SESSIDEC_H
#define SESSIDEC_H

#include "ApiIdec_blks.h"

#define StatShrSessIdec SessIdec::StatShr

#define DpchEngSessIdecData SessIdec::DpchEngData

/**
  * SessIdec
  */
namespace SessIdec {
	/**
	  * StatShr (full: StatShrSessIdec)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFCRDNAV = 1;

	public:
		StatShr(const string& scrJrefCrdnav = "");

	public:
		string scrJrefCrdnav;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* DpchEngData (full: DpchEngSessIdecData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint STATSHR = 2;

	public:
		DpchEngData();

	public:
		StatShr statshr;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

