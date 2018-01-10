/**
  * \file PnlIdecMisDetail.h
  * API code for job PnlIdecMisDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISDETAIL_H
#define PNLIDECMISDETAIL_H

#include "ApiIdec_blks.h"

#define VecVIdecMisDetailDo PnlIdecMisDetail::VecVDo

#define ContIacIdecMisDetail PnlIdecMisDetail::ContIac
#define StatAppIdecMisDetail PnlIdecMisDetail::StatApp
#define StatShrIdecMisDetail PnlIdecMisDetail::StatShr
#define TagIdecMisDetail PnlIdecMisDetail::Tag

#define DpchAppIdecMisDetailData PnlIdecMisDetail::DpchAppData
#define DpchAppIdecMisDetailDo PnlIdecMisDetail::DpchAppDo
#define DpchEngIdecMisDetailData PnlIdecMisDetail::DpchEngData

/**
  * PnlIdecMisDetail
  */
namespace PnlIdecMisDetail {
	/**
		* VecVDo (full: VecVIdecMisDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTCRYEDITCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecMisDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFTIT = 1;
		static const uint TXFSTA = 2;
		static const uint TXFSTO = 3;
		static const uint NUMFPUPCRY = 4;
		static const uint TXFCRY = 5;
		static const uint TXFREG = 6;
		static const uint TXFMUN = 7;
		static const uint TXFCMT = 8;

	public:
		ContIac(const string& TxfTit = "", const string& TxfSta = "", const string& TxfSto = "", const uint numFPupCry = 1, const string& TxfCry = "", const string& TxfReg = "", const string& TxfMun = "", const string& TxfCmt = "");

	public:
		string TxfTit;
		string TxfSta;
		string TxfSto;
		uint numFPupCry;
		string TxfCry;
		string TxfReg;
		string TxfMun;
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * StatApp (full: StatAppIdecMisDetail)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint PUPCRYALT = 2;

	public:
		StatApp(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupCryAlt = false);

	public:
		uint ixIdecVExpstate;
		bool PupCryAlt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecMisDetail)
	  */
	class StatShr : public Block {

	public:
		static const uint TXFCRYVALID = 1;
		static const uint BUTSAVEAVAIL = 2;
		static const uint BUTSAVEACTIVE = 3;
		static const uint TXFTITACTIVE = 4;
		static const uint TXFSTAACTIVE = 5;
		static const uint TXFSTOACTIVE = 6;
		static const uint PUPCRYACTIVE = 7;
		static const uint BUTCRYEDITAVAIL = 8;
		static const uint TXFREGACTIVE = 9;
		static const uint TXFMUNACTIVE = 10;
		static const uint TXFCMTACTIVE = 11;

	public:
		StatShr(const bool TxfCryValid = false, const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxfTitActive = true, const bool TxfStaActive = true, const bool TxfStoActive = true, const bool PupCryActive = true, const bool ButCryEditAvail = true, const bool TxfRegActive = true, const bool TxfMunActive = true, const bool TxfCmtActive = true);

	public:
		bool TxfCryValid;
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxfTitActive;
		bool TxfStaActive;
		bool TxfStoActive;
		bool PupCryActive;
		bool ButCryEditAvail;
		bool TxfRegActive;
		bool TxfMunActive;
		bool TxfCmtActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecMisDetail)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTTIT = 2;
		static const uint CPTSTA = 3;
		static const uint CPTSTO = 4;
		static const uint CPTCRY = 5;
		static const uint CPTREG = 6;
		static const uint CPTMUN = 7;
		static const uint CPTCMT = 8;

	public:
		Tag(const string& Cpt = "", const string& CptTit = "", const string& CptSta = "", const string& CptSto = "", const string& CptCry = "", const string& CptReg = "", const string& CptMun = "", const string& CptCmt = "");

	public:
		string Cpt;
		string CptTit;
		string CptSta;
		string CptSto;
		string CptCry;
		string CptReg;
		string CptMun;
		string CptCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecMisDetailData)
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
		* DpchAppDo (full: DpchAppIdecMisDetailDo)
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
		* DpchEngData (full: DpchEngIdecMisDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFPUPCRY = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		Feed feedFPupCry;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

