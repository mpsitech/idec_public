/**
  * \file PnlIdecMisHeadbar.h
  * API code for job PnlIdecMisHeadbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISHEADBAR_H
#define PNLIDECMISHEADBAR_H

#include "ApiIdec_blks.h"

#define StgInfIdecMisHeadbar PnlIdecMisHeadbar::StgInf
#define TagIdecMisHeadbar PnlIdecMisHeadbar::Tag

#define DpchEngIdecMisHeadbarData PnlIdecMisHeadbar::DpchEngData

/**
  * PnlIdecMisHeadbar
  */
namespace PnlIdecMisHeadbar {
	/**
	  * StgInf (full: StgInfIdecMisHeadbar)
	  */
	class StgInf : public Block {

	public:
		static const uint MENAPPCPTWIDTH = 1;
		static const uint MENAPPWIDTH = 2;
		static const uint MENCRDCPTWIDTH = 3;
		static const uint MENCRDWIDTH = 4;

	public:
		StgInf(const uint MenAppCptwidth = 100, const uint MenAppWidth = 100, const uint MenCrdCptwidth = 100, const uint MenCrdWidth = 100);

	public:
		uint MenAppCptwidth;
		uint MenAppWidth;
		uint MenCrdCptwidth;
		uint MenCrdWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StgInf* comp);
		set<uint> diff(const StgInf* comp);
	};

	/**
	  * Tag (full: TagIdecMisHeadbar)
	  */
	class Tag : public Block {

	public:
		static const uint MENAPP = 1;
		static const uint MENCRD = 2;

	public:
		Tag(const string& MenApp = "", const string& MenCrd = "");

	public:
		string MenApp;
		string MenCrd;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngData (full: DpchEngIdecMisHeadbarData)
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

