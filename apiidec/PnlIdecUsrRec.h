/**
  * \file PnlIdecUsrRec.h
  * API code for job PnlIdecUsrRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSRREC_H
#define PNLIDECUSRREC_H

#include "ApiIdec_blks.h"

#define VecVIdecUsrRecDo PnlIdecUsrRec::VecVDo

#define ContInfIdecUsrRec PnlIdecUsrRec::ContInf
#define StatAppIdecUsrRec PnlIdecUsrRec::StatApp
#define StatShrIdecUsrRec PnlIdecUsrRec::StatShr
#define TagIdecUsrRec PnlIdecUsrRec::Tag

#define DpchAppIdecUsrRecDo PnlIdecUsrRec::DpchAppDo
#define DpchEngIdecUsrRecData PnlIdecUsrRec::DpchEngData

/**
  * PnlIdecUsrRec
  */
namespace PnlIdecUsrRec {
	/**
		* VecVDo (full: VecVIdecUsrRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecUsrRec)
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
	  * StatApp (full: StatAppIdecUsrRec)
	  */
	class StatApp : public Block {

	public:
		static const uint INITDONEDETAIL = 1;
		static const uint INITDONEAACCESS = 2;
		static const uint INITDONE1NSESSION = 3;
		static const uint INITDONEMNUSERGROUP = 4;

	public:
		StatApp(const bool initdoneDetail = false, const bool initdoneAAccess = false, const bool initdone1NSession = false, const bool initdoneMNUsergroup = false);

	public:
		bool initdoneDetail;
		bool initdoneAAccess;
		bool initdone1NSession;
		bool initdoneMNUsergroup;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecUsrRec)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SCRJREFDETAIL = 2;
		static const uint SCRJREFAACCESS = 3;
		static const uint SCRJREF1NSESSION = 4;
		static const uint SCRJREFMNUSERGROUP = 5;
		static const uint BUTREGULARIZEACTIVE = 6;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const string& scrJrefDetail = "", const string& scrJrefAAccess = "", const string& scrJref1NSession = "", const string& scrJrefMNUsergroup = "", const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		string scrJrefDetail;
		string scrJrefAAccess;
		string scrJref1NSession;
		string scrJrefMNUsergroup;
		bool ButRegularizeActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUsrRec)
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
		* DpchAppDo (full: DpchAppIdecUsrRecDo)
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
		* DpchEngData (full: DpchEngIdecUsrRecData)
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

