/**
  * \file PnlIdecUsrList.h
  * API code for job PnlIdecUsrList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSRLIST_H
#define PNLIDECUSRLIST_H

#include "ApiIdec_blks.h"

#include "IdecQUsrList.h"

#include "QryIdecUsrList.h"

#define VecVIdecUsrListDo PnlIdecUsrList::VecVDo

#define ContIacIdecUsrList PnlIdecUsrList::ContIac
#define ContInfIdecUsrList PnlIdecUsrList::ContInf
#define StatShrIdecUsrList PnlIdecUsrList::StatShr
#define StgIacIdecUsrList PnlIdecUsrList::StgIac
#define TagIdecUsrList PnlIdecUsrList::Tag

#define DpchAppIdecUsrListData PnlIdecUsrList::DpchAppData
#define DpchAppIdecUsrListDo PnlIdecUsrList::DpchAppDo
#define DpchEngIdecUsrListData PnlIdecUsrList::DpchEngData

/**
  * PnlIdecUsrList
  */
namespace PnlIdecUsrList {
	/**
		* VecVDo (full: VecVIdecUsrListDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;
		static const uint BUTNEWCLICK = 3;
		static const uint BUTDELETECLICK = 4;
		static const uint BUTFILTERCLICK = 5;
		static const uint BUTREFRESHCLICK = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUsrList)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFTOS = 1;

	public:
		ContIac(const uint numFTos = 1);

	public:
		uint numFTos;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUsrList)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTFILTERON = 1;
		static const uint NUMFCSIQST = 2;

	public:
		ContInf(const bool ButFilterOn = false, const uint numFCsiQst = 1);

	public:
		bool ButFilterOn;
		uint numFCsiQst;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecUsrList)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint BUTDELETEACTIVE = 2;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool ButDeleteActive = true);

	public:
		uint ixIdecVExpstate;
		bool ButDeleteActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * StgIac (full: StgIacIdecUsrList)
	  */
	class StgIac : public Block {

	public:
		static const uint TCOPRSWIDTH = 1;
		static const uint TCOSRFWIDTH = 2;
		static const uint TCOUSGWIDTH = 3;
		static const uint TCOSTEWIDTH = 4;
		static const uint TCOLCLWIDTH = 5;
		static const uint TCOULVWIDTH = 6;

	public:
		StgIac(const uint TcoPrsWidth = 100, const uint TcoSrfWidth = 100, const uint TcoUsgWidth = 100, const uint TcoSteWidth = 100, const uint TcoLclWidth = 100, const uint TcoUlvWidth = 100);

	public:
		uint TcoPrsWidth;
		uint TcoSrfWidth;
		uint TcoUsgWidth;
		uint TcoSteWidth;
		uint TcoLclWidth;
		uint TcoUlvWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

	/**
	  * Tag (full: TagIdecUsrList)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint TRS = 2;
		static const uint TXTSHOWING1 = 3;
		static const uint TXTSHOWING2 = 4;
		static const uint TCOPRS = 5;
		static const uint TCOSRF = 6;
		static const uint TCOUSG = 7;
		static const uint TCOSTE = 8;
		static const uint TCOLCL = 9;
		static const uint TCOULV = 10;

	public:
		Tag(const string& Cpt = "", const string& Trs = "", const string& TxtShowing1 = "", const string& TxtShowing2 = "", const string& TcoPrs = "", const string& TcoSrf = "", const string& TcoUsg = "", const string& TcoSte = "", const string& TcoLcl = "", const string& TcoUlv = "");

	public:
		string Cpt;
		string Trs;
		string TxtShowing1;
		string TxtShowing2;
		string TcoPrs;
		string TcoSrf;
		string TcoUsg;
		string TcoSte;
		string TcoLcl;
		string TcoUlv;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsrListData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint STGIAC = 3;
		static const uint STGIACQRY = 4;
		static const uint ALL = 5;

	public:
		DpchAppData(const string& scrJref = "", ContIac* contiac = NULL, StgIac* stgiac = NULL, QryIdecUsrList::StgIac* stgiacqry = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		StgIac stgiac;
		QryIdecUsrList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void writeXML(xmlTextWriter* wr);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUsrListDo)
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
		* DpchEngData (full: DpchEngIdecUsrListData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIQST = 4;
		static const uint FEEDFTOS = 5;
		static const uint STATSHR = 6;
		static const uint STGIAC = 7;
		static const uint TAG = 8;
		static const uint RST = 9;
		static const uint STATAPPQRY = 10;
		static const uint STATSHRQRY = 11;
		static const uint STGIACQRY = 12;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiQst;
		Feed feedFTos;
		StatShr statshr;
		StgIac stgiac;
		Tag tag;
		ListIdecQUsrList rst;
		QryIdecUsrList::StatApp statappqry;
		QryIdecUsrList::StatShr statshrqry;
		QryIdecUsrList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

