/**
  * \file PnlIdecUsgDetail.h
  * API code for job PnlIdecUsgDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSGDETAIL_H
#define PNLIDECUSGDETAIL_H

#include "ApiIdec_blks.h"

#define VecVIdecUsgDetailDo PnlIdecUsgDetail::VecVDo

#define ContIacIdecUsgDetail PnlIdecUsgDetail::ContIac
#define ContInfIdecUsgDetail PnlIdecUsgDetail::ContInf
#define StatAppIdecUsgDetail PnlIdecUsgDetail::StatApp
#define StatShrIdecUsgDetail PnlIdecUsgDetail::StatShr
#define TagIdecUsgDetail PnlIdecUsgDetail::Tag

#define DpchAppIdecUsgDetailData PnlIdecUsgDetail::DpchAppData
#define DpchAppIdecUsgDetailDo PnlIdecUsgDetail::DpchAppDo
#define DpchEngIdecUsgDetailData PnlIdecUsgDetail::DpchEngData

/**
  * PnlIdecUsgDetail
  */
namespace PnlIdecUsgDetail {
	/**
		* VecVDo (full: VecVIdecUsgDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUsgDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFCMT = 1;

	public:
		ContIac(const string& TxfCmt = "");

	public:
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUsgDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTSRF = 1;

	public:
		ContInf(const string& TxtSrf = "");

	public:
		string TxtSrf;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecUsgDetail)
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
	  * StatShr (full: StatShrIdecUsgDetail)
	  */
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXTSRFACTIVE = 3;
		static const uint TXFCMTACTIVE = 4;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxtSrfActive = true, const bool TxfCmtActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxtSrfActive;
		bool TxfCmtActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUsgDetail)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTSRF = 2;
		static const uint CPTCMT = 3;

	public:
		Tag(const string& Cpt = "", const string& CptSrf = "", const string& CptCmt = "");

	public:
		string Cpt;
		string CptSrf;
		string CptCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsgDetailData)
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
		* DpchAppDo (full: DpchAppIdecUsgDetailDo)
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
		* DpchEngData (full: DpchEngIdecUsgDetailData)
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

