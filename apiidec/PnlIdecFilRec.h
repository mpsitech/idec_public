/**
  * \file PnlIdecFilRec.h
  * API code for job PnlIdecFilRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECFILREC_H
#define PNLIDECFILREC_H

#include "ApiIdec_blks.h"

#define VecVIdecFilRecDo PnlIdecFilRec::VecVDo

#define ContInfIdecFilRec PnlIdecFilRec::ContInf
#define StatAppIdecFilRec PnlIdecFilRec::StatApp
#define StatShrIdecFilRec PnlIdecFilRec::StatShr
#define TagIdecFilRec PnlIdecFilRec::Tag

#define DpchAppIdecFilRecDo PnlIdecFilRec::DpchAppDo
#define DpchEngIdecFilRecData PnlIdecFilRec::DpchEngData

/**
  * PnlIdecFilRec
  */
namespace PnlIdecFilRec {
	/**
		* VecVDo (full: VecVIdecFilRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecFilRec)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTREF = 1;

	public:
		ContInf(const string& TxtRef = "");

	public:
		string TxtRef;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecFilRec)
	  */
	class StatApp : public Block {

	public:
		static const uint INITDONEDETAIL = 1;

	public:
		StatApp(const bool initdoneDetail = false);

	public:
		bool initdoneDetail;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecFilRec)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SCRJREFDETAIL = 2;
		static const uint BUTREGULARIZEACTIVE = 3;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const string& scrJrefDetail = "", const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		string scrJrefDetail;
		bool ButRegularizeActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecFilRec)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;

	public:
		Tag(const string& Cpt = "");

	public:
		string Cpt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecFilRecDo)
		*/
	class DpchAppDo : public DpchAppIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint IXVDO = 2;
		static const uint ALL = 3;

	public:
		DpchAppDo(const string& scrJref = "", const uint ixVDo = 0, const set<uint>& mask = {NONE});

	public:
		uint ixVDo;

	public:
		string getSrefsMask();

		void writeXML(xmlTextWriter* wr);
	};

	/**
		* DpchEngData (full: DpchEngIdecFilRecData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint STATAPP = 3;
		static const uint STATSHR = 4;
		static const uint TAG = 5;

	public:
		DpchEngData();

	public:
		ContInf continf;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

