/**
  * \file PnlIdecUsgRec.h
  * API code for job PnlIdecUsgRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSGREC_H
#define PNLIDECUSGREC_H

#include "ApiIdec_blks.h"

#define VecVIdecUsgRecDo PnlIdecUsgRec::VecVDo

#define ContInfIdecUsgRec PnlIdecUsgRec::ContInf
#define StatAppIdecUsgRec PnlIdecUsgRec::StatApp
#define StatShrIdecUsgRec PnlIdecUsgRec::StatShr
#define TagIdecUsgRec PnlIdecUsgRec::Tag

#define DpchAppIdecUsgRecDo PnlIdecUsgRec::DpchAppDo
#define DpchEngIdecUsgRecData PnlIdecUsgRec::DpchEngData

/**
  * PnlIdecUsgRec
  */
namespace PnlIdecUsgRec {
	/**
		* VecVDo (full: VecVIdecUsgRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecUsgRec)
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
	  * StatApp (full: StatAppIdecUsgRec)
	  */
	class StatApp : public Block {

	public:
		static const uint INITDONEDETAIL = 1;
		static const uint INITDONEAACCESS = 2;
		static const uint INITDONEMNUSER = 3;

	public:
		StatApp(const bool initdoneDetail = false, const bool initdoneAAccess = false, const bool initdoneMNUser = false);

	public:
		bool initdoneDetail;
		bool initdoneAAccess;
		bool initdoneMNUser;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecUsgRec)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SCRJREFDETAIL = 2;
		static const uint SCRJREFAACCESS = 3;
		static const uint SCRJREFMNUSER = 4;
		static const uint BUTREGULARIZEACTIVE = 5;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const string& scrJrefDetail = "", const string& scrJrefAAccess = "", const string& scrJrefMNUser = "", const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		string scrJrefDetail;
		string scrJrefAAccess;
		string scrJrefMNUser;
		bool ButRegularizeActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUsgRec)
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
		* DpchAppDo (full: DpchAppIdecUsgRecDo)
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
		* DpchEngData (full: DpchEngIdecUsgRecData)
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

