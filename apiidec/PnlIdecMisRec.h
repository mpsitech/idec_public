/**
  * \file PnlIdecMisRec.h
  * API code for job PnlIdecMisRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISREC_H
#define PNLIDECMISREC_H

#include "ApiIdec_blks.h"

#define VecVIdecMisRecDo PnlIdecMisRec::VecVDo

#define ContInfIdecMisRec PnlIdecMisRec::ContInf
#define StatAppIdecMisRec PnlIdecMisRec::StatApp
#define StatShrIdecMisRec PnlIdecMisRec::StatShr
#define TagIdecMisRec PnlIdecMisRec::Tag

#define DpchAppIdecMisRecDo PnlIdecMisRec::DpchAppDo
#define DpchEngIdecMisRecData PnlIdecMisRec::DpchEngData

/**
  * PnlIdecMisRec
  */
namespace PnlIdecMisRec {
	/**
		* VecVDo (full: VecVIdecMisRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecMisRec)
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
	  * StatApp (full: StatAppIdecMisRec)
	  */
	class StatApp : public Block {

	public:
		static const uint INITDONEDETAIL = 1;
		static const uint INITDONE1NTOUR = 2;
		static const uint INITDONEREF1NFILE = 3;

	public:
		StatApp(const bool initdoneDetail = false, const bool initdone1NTour = false, const bool initdoneRef1NFile = false);

	public:
		bool initdoneDetail;
		bool initdone1NTour;
		bool initdoneRef1NFile;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecMisRec)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SCRJREFDETAIL = 2;
		static const uint SCRJREF1NTOUR = 3;
		static const uint SCRJREFREF1NFILE = 4;
		static const uint BUTREGULARIZEACTIVE = 5;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const string& scrJrefDetail = "", const string& scrJref1NTour = "", const string& scrJrefRef1NFile = "", const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		string scrJrefDetail;
		string scrJref1NTour;
		string scrJrefRef1NFile;
		bool ButRegularizeActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecMisRec)
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
		* DpchAppDo (full: DpchAppIdecMisRecDo)
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
		* DpchEngData (full: DpchEngIdecMisRecData)
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

