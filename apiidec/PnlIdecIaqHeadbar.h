/**
  * \file PnlIdecIaqHeadbar.h
  * API code for job PnlIdecIaqHeadbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQHEADBAR_H
#define PNLIDECIAQHEADBAR_H

#include "ApiIdec_blks.h"

#define StgInfIdecIaqHeadbar PnlIdecIaqHeadbar::StgInf
#define TagIdecIaqHeadbar PnlIdecIaqHeadbar::Tag

#define DpchEngIdecIaqHeadbarData PnlIdecIaqHeadbar::DpchEngData

/**
  * PnlIdecIaqHeadbar
  */
namespace PnlIdecIaqHeadbar {
	/**
	  * StgInf (full: StgInfIdecIaqHeadbar)
	  */
	class StgInf : public Block {

	public:
		static const uint MENAPPCPTWIDTH = 1;
		static const uint MENAPPWIDTH = 2;

	public:
		StgInf(const uint MenAppCptwidth = 100, const uint MenAppWidth = 100);

	public:
		uint MenAppCptwidth;
		uint MenAppWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StgInf* comp);
		set<uint> diff(const StgInf* comp);
	};

	/**
	  * Tag (full: TagIdecIaqHeadbar)
	  */
	class Tag : public Block {

	public:
		static const uint MENAPP = 1;

	public:
		Tag(const string& MenApp = "");

	public:
		string MenApp;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngData (full: DpchEngIdecIaqHeadbarData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint STGINF = 2;
		static const uint TAG = 3;

	public:
		DpchEngData();

	public:
		StgInf stginf;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

