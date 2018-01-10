/**
  * \file PnlIdecScfHeadbar.h
  * API code for job PnlIdecScfHeadbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFHEADBAR_H
#define PNLIDECSCFHEADBAR_H

#include "ApiIdec_blks.h"

#define StgInfIdecScfHeadbar PnlIdecScfHeadbar::StgInf
#define TagIdecScfHeadbar PnlIdecScfHeadbar::Tag

#define DpchEngIdecScfHeadbarData PnlIdecScfHeadbar::DpchEngData

/**
  * PnlIdecScfHeadbar
  */
namespace PnlIdecScfHeadbar {
	/**
	  * StgInf (full: StgInfIdecScfHeadbar)
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
	  * Tag (full: TagIdecScfHeadbar)
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
		* DpchEngData (full: DpchEngIdecScfHeadbarData)
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

