/**
  * \file PnlIdecAd1Headbar.h
  * API code for job PnlIdecAd1Headbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECAD1HEADBAR_H
#define PNLIDECAD1HEADBAR_H

#include "ApiIdec_blks.h"

#define StgInfIdecAd1Headbar PnlIdecAd1Headbar::StgInf
#define TagIdecAd1Headbar PnlIdecAd1Headbar::Tag

#define DpchEngIdecAd1HeadbarData PnlIdecAd1Headbar::DpchEngData

/**
  * PnlIdecAd1Headbar
  */
namespace PnlIdecAd1Headbar {
	/**
	  * StgInf (full: StgInfIdecAd1Headbar)
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
	  * Tag (full: TagIdecAd1Headbar)
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
		* DpchEngData (full: DpchEngIdecAd1HeadbarData)
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

