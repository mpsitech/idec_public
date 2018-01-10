/**
  * \file PnlIdecUsrDetail.h
  * API code for job PnlIdecUsrDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSRDETAIL_H
#define PNLIDECUSRDETAIL_H

#include "ApiIdec_blks.h"

#define VecVIdecUsrDetailDo PnlIdecUsrDetail::VecVDo

#define ContIacIdecUsrDetail PnlIdecUsrDetail::ContIac
#define ContInfIdecUsrDetail PnlIdecUsrDetail::ContInf
#define StatAppIdecUsrDetail PnlIdecUsrDetail::StatApp
#define StatShrIdecUsrDetail PnlIdecUsrDetail::StatShr
#define TagIdecUsrDetail PnlIdecUsrDetail::Tag

#define DpchAppIdecUsrDetailData PnlIdecUsrDetail::DpchAppData
#define DpchAppIdecUsrDetailDo PnlIdecUsrDetail::DpchAppDo
#define DpchEngIdecUsrDetailData PnlIdecUsrDetail::DpchEngData

/**
  * PnlIdecUsrDetail
  */
namespace PnlIdecUsrDetail {
	/**
		* VecVDo (full: VecVIdecUsrDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTUSGVIEWCLICK = 2;
		static const uint BUTJEDITCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUsrDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPJ = 1;
		static const uint NUMFPUPSTE = 2;
		static const uint NUMFPUPLCL = 3;
		static const uint NUMFPUPULV = 4;
		static const uint TXFPWD = 5;

	public:
		ContIac(const uint numFPupJ = 1, const uint numFPupSte = 1, const uint numFPupLcl = 1, const uint numFPupUlv = 1, const string& TxfPwd = "");

	public:
		uint numFPupJ;
		uint numFPupSte;
		uint numFPupLcl;
		uint numFPupUlv;
		string TxfPwd;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUsrDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTPRS = 1;
		static const uint TXTSRF = 2;
		static const uint TXTUSG = 3;

	public:
		ContInf(const string& TxtPrs = "", const string& TxtSrf = "", const string& TxtUsg = "");

	public:
		string TxtPrs;
		string TxtSrf;
		string TxtUsg;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecUsrDetail)
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
	  * StatShr (full: StatShrIdecUsrDetail)
	  */
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXTPRSACTIVE = 3;
		static const uint TXTSRFACTIVE = 4;
		static const uint TXTUSGACTIVE = 5;
		static const uint BUTUSGVIEWAVAIL = 6;
		static const uint BUTUSGVIEWACTIVE = 7;
		static const uint PUPJACTIVE = 8;
		static const uint BUTJEDITAVAIL = 9;
		static const uint PUPSTEACTIVE = 10;
		static const uint PUPLCLACTIVE = 11;
		static const uint PUPULVACTIVE = 12;
		static const uint TXFPWDACTIVE = 13;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxtPrsActive = true, const bool TxtSrfActive = true, const bool TxtUsgActive = true, const bool ButUsgViewAvail = true, const bool ButUsgViewActive = true, const bool PupJActive = true, const bool ButJEditAvail = true, const bool PupSteActive = true, const bool PupLclActive = true, const bool PupUlvActive = true, const bool TxfPwdActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxtPrsActive;
		bool TxtSrfActive;
		bool TxtUsgActive;
		bool ButUsgViewAvail;
		bool ButUsgViewActive;
		bool PupJActive;
		bool ButJEditAvail;
		bool PupSteActive;
		bool PupLclActive;
		bool PupUlvActive;
		bool TxfPwdActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUsrDetail)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTPRS = 2;
		static const uint CPTSRF = 3;
		static const uint CPTUSG = 4;
		static const uint CPTSTE = 5;
		static const uint CPTLCL = 6;
		static const uint CPTULV = 7;
		static const uint CPTPWD = 8;

	public:
		Tag(const string& Cpt = "", const string& CptPrs = "", const string& CptSrf = "", const string& CptUsg = "", const string& CptSte = "", const string& CptLcl = "", const string& CptUlv = "", const string& CptPwd = "");

	public:
		string Cpt;
		string CptPrs;
		string CptSrf;
		string CptUsg;
		string CptSte;
		string CptLcl;
		string CptUlv;
		string CptPwd;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsrDetailData)
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
		* DpchAppDo (full: DpchAppIdecUsrDetailDo)
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
		* DpchEngData (full: DpchEngIdecUsrDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPJ = 4;
		static const uint FEEDFPUPLCL = 5;
		static const uint FEEDFPUPSTE = 6;
		static const uint FEEDFPUPULV = 7;
		static const uint STATAPP = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupJ;
		Feed feedFPupLcl;
		Feed feedFPupSte;
		Feed feedFPupUlv;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

