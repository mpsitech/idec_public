/**
  * \file PnlIdecTouDetail.h
  * API code for job PnlIdecTouDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECTOUDETAIL_H
#define PNLIDECTOUDETAIL_H

#include "ApiIdec_blks.h"

#define VecVIdecTouDetailDo PnlIdecTouDetail::VecVDo

#define ContIacIdecTouDetail PnlIdecTouDetail::ContIac
#define ContInfIdecTouDetail PnlIdecTouDetail::ContInf
#define StatAppIdecTouDetail PnlIdecTouDetail::StatApp
#define StatShrIdecTouDetail PnlIdecTouDetail::StatShr
#define TagIdecTouDetail PnlIdecTouDetail::Tag

#define DpchAppIdecTouDetailData PnlIdecTouDetail::DpchAppData
#define DpchAppIdecTouDetailDo PnlIdecTouDetail::DpchAppDo
#define DpchEngIdecTouDetailData PnlIdecTouDetail::DpchEngData

/**
  * PnlIdecTouDetail
  */
namespace PnlIdecTouDetail {
	/**
		* VecVDo (full: VecVIdecTouDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTMISVIEWCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecTouDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFTIT = 1;
		static const uint TXFSTA = 2;
		static const uint TXFSTO = 3;
		static const uint TXFARE = 4;
		static const uint TXFTHE = 5;
		static const uint TXFPHI = 6;
		static const uint TXFCMT = 7;

	public:
		ContIac(const string& TxfTit = "", const string& TxfSta = "", const string& TxfSto = "", const string& TxfAre = "", const string& TxfThe = "", const string& TxfPhi = "", const string& TxfCmt = "");

	public:
		string TxfTit;
		string TxfSta;
		string TxfSto;
		string TxfAre;
		string TxfThe;
		string TxfPhi;
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecTouDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTMIS = 1;

	public:
		ContInf(const string& TxtMis = "");

	public:
		string TxtMis;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecTouDetail)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;

	public:
		StatApp(const uint ixIdecVExpstate = VecIdecVExpstate::MIND);

	public:
		uint ixIdecVExpstate;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecTouDetail)
	  */
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXFTITACTIVE = 3;
		static const uint TXTMISACTIVE = 4;
		static const uint BUTMISVIEWAVAIL = 5;
		static const uint BUTMISVIEWACTIVE = 6;
		static const uint TXFSTAACTIVE = 7;
		static const uint TXFSTOACTIVE = 8;
		static const uint TXFAREACTIVE = 9;
		static const uint TXFTHEACTIVE = 10;
		static const uint TXFPHIACTIVE = 11;
		static const uint TXFCMTACTIVE = 12;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxfTitActive = true, const bool TxtMisActive = true, const bool ButMisViewAvail = true, const bool ButMisViewActive = true, const bool TxfStaActive = true, const bool TxfStoActive = true, const bool TxfAreActive = true, const bool TxfTheActive = true, const bool TxfPhiActive = true, const bool TxfCmtActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxfTitActive;
		bool TxtMisActive;
		bool ButMisViewAvail;
		bool ButMisViewActive;
		bool TxfStaActive;
		bool TxfStoActive;
		bool TxfAreActive;
		bool TxfTheActive;
		bool TxfPhiActive;
		bool TxfCmtActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecTouDetail)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTTIT = 2;
		static const uint CPTMIS = 3;
		static const uint CPTSTA = 4;
		static const uint CPTSTO = 5;
		static const uint CPTARE = 6;
		static const uint CPTTHE = 7;
		static const uint CPTPHI = 8;
		static const uint CPTCMT = 9;

	public:
		Tag(const string& Cpt = "", const string& CptTit = "", const string& CptMis = "", const string& CptSta = "", const string& CptSto = "", const string& CptAre = "", const string& CptThe = "", const string& CptPhi = "", const string& CptCmt = "");

	public:
		string Cpt;
		string CptTit;
		string CptMis;
		string CptSta;
		string CptSto;
		string CptAre;
		string CptThe;
		string CptPhi;
		string CptCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecTouDetailData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint ALL = 3;

	public:
		DpchAppData(const string& scrJref = "", ContIac* contiac = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;

	public:
		string getSrefsMask();

		void writeXML(xmlTextWriter* wr);
	};

	/**
		* DpchAppDo (full: DpchAppIdecTouDetailDo)
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
		* DpchEngData (full: DpchEngIdecTouDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;

	public:
		DpchEngData();

	public:
		ContIac contiac;
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

