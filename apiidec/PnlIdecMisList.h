/**
  * \file PnlIdecMisList.h
  * API code for job PnlIdecMisList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISLIST_H
#define PNLIDECMISLIST_H

#include "ApiIdec_blks.h"

#include "IdecQMisList.h"

#include "QryIdecMisList.h"

#define VecVIdecMisListDo PnlIdecMisList::VecVDo

#define ContIacIdecMisList PnlIdecMisList::ContIac
#define ContInfIdecMisList PnlIdecMisList::ContInf
#define StatShrIdecMisList PnlIdecMisList::StatShr
#define StgIacIdecMisList PnlIdecMisList::StgIac
#define TagIdecMisList PnlIdecMisList::Tag

#define DpchAppIdecMisListData PnlIdecMisList::DpchAppData
#define DpchAppIdecMisListDo PnlIdecMisList::DpchAppDo
#define DpchEngIdecMisListData PnlIdecMisList::DpchEngData

/**
  * PnlIdecMisList
  */
namespace PnlIdecMisList {
	/**
		* VecVDo (full: VecVIdecMisListDo)
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
	  * ContIac (full: ContIacIdecMisList)
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
	  * ContInf (full: ContInfIdecMisList)
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
	  * StatShr (full: StatShrIdecMisList)
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
	  * StgIac (full: StgIacIdecMisList)
	  */
	class StgIac : public Block {

	public:
		static const uint TCOTITWIDTH = 1;
		static const uint TCOGRPWIDTH = 2;
		static const uint TCOOWNWIDTH = 3;
		static const uint TCOSTAWIDTH = 4;
		static const uint TCOSTOWIDTH = 5;
		static const uint TCOCRYWIDTH = 6;
		static const uint TCOREGWIDTH = 7;
		static const uint TCOMUNWIDTH = 8;

	public:
		StgIac(const uint TcoTitWidth = 100, const uint TcoGrpWidth = 100, const uint TcoOwnWidth = 100, const uint TcoStaWidth = 100, const uint TcoStoWidth = 100, const uint TcoCryWidth = 100, const uint TcoRegWidth = 100, const uint TcoMunWidth = 100);

	public:
		uint TcoTitWidth;
		uint TcoGrpWidth;
		uint TcoOwnWidth;
		uint TcoStaWidth;
		uint TcoStoWidth;
		uint TcoCryWidth;
		uint TcoRegWidth;
		uint TcoMunWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

	/**
	  * Tag (full: TagIdecMisList)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint TRS = 2;
		static const uint TXTSHOWING1 = 3;
		static const uint TXTSHOWING2 = 4;
		static const uint TCOTIT = 5;
		static const uint TCOGRP = 6;
		static const uint TCOOWN = 7;
		static const uint TCOSTA = 8;
		static const uint TCOSTO = 9;
		static const uint TCOCRY = 10;
		static const uint TCOREG = 11;
		static const uint TCOMUN = 12;

	public:
		Tag(const string& Cpt = "", const string& Trs = "", const string& TxtShowing1 = "", const string& TxtShowing2 = "", const string& TcoTit = "", const string& TcoGrp = "", const string& TcoOwn = "", const string& TcoSta = "", const string& TcoSto = "", const string& TcoCry = "", const string& TcoReg = "", const string& TcoMun = "");

	public:
		string Cpt;
		string Trs;
		string TxtShowing1;
		string TxtShowing2;
		string TcoTit;
		string TcoGrp;
		string TcoOwn;
		string TcoSta;
		string TcoSto;
		string TcoCry;
		string TcoReg;
		string TcoMun;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecMisListData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint STGIAC = 3;
		static const uint STGIACQRY = 4;
		static const uint ALL = 5;

	public:
		DpchAppData(const string& scrJref = "", ContIac* contiac = NULL, StgIac* stgiac = NULL, QryIdecMisList::StgIac* stgiacqry = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		StgIac stgiac;
		QryIdecMisList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void writeXML(xmlTextWriter* wr);
	};

	/**
		* DpchAppDo (full: DpchAppIdecMisListDo)
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
		* DpchEngData (full: DpchEngIdecMisListData)
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
		ListIdecQMisList rst;
		QryIdecMisList::StatApp statappqry;
		QryIdecMisList::StatShr statshrqry;
		QryIdecMisList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

