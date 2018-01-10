/**
  * \file PnlIdecIaqQcdsp.h
  * API code for job PnlIdecIaqQcdsp (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQQCDSP_H
#define PNLIDECIAQQCDSP_H

#include "ApiIdec_blks.h"

#define VecVIdecIaqQcdspDo PnlIdecIaqQcdsp::VecVDo
#define VecVIdecIaqQcdspMode PnlIdecIaqQcdsp::VecVMode

#define ContIacIdecIaqQcdsp PnlIdecIaqQcdsp::ContIac
#define ContInfIdecIaqQcdsp PnlIdecIaqQcdsp::ContInf
#define StatShrIdecIaqQcdsp PnlIdecIaqQcdsp::StatShr
#define TagIdecIaqQcdsp PnlIdecIaqQcdsp::Tag

#define DpchAppIdecIaqQcdspData PnlIdecIaqQcdsp::DpchAppData
#define DpchAppIdecIaqQcdspDo PnlIdecIaqQcdsp::DpchAppDo
#define DpchEngIdecIaqQcdspData PnlIdecIaqQcdsp::DpchEngData
#define DpchEngIdecIaqQcdspLive PnlIdecIaqQcdsp::DpchEngLive

/**
  * PnlIdecIaqQcdsp
  */
namespace PnlIdecIaqQcdsp {
	/**
		* VecVDo (full: VecVIdecIaqQcdspDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqQcdspMode)
		*/
	class VecVMode {

	public:
		static const uint OFF = 1;
		static const uint PIX = 2;
		static const uint FRM = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecIaqQcdsp)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTIN = 2;
		static const uint CUSIMGPXS = 3;

	public:
		ContIac(const uint numFPupMod = 1, const double SldTin = 0.0, const usmallint CusImgPxs = 0);

	public:
		uint numFPupMod;
		double SldTin;
		usmallint CusImgPxs;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqQcdsp)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTIMGIL0 = 2;
		static const uint TXTIMGIL1 = 3;
		static const uint TXTIMGQWH = 4;
		static const uint TXTIMGQHP = 5;
		static const uint TXTIMGQDP = 6;
		static const uint TXTIMGSIQ = 7;
		static const uint TXTIMGDXI = 8;
		static const uint TXTIMGDYI = 9;
		static const uint TXTIMGQLM = 10;
		static const uint TXTIMGQDL = 11;
		static const uint NUMFCSIIMGSTE = 12;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtImgIl0 = "", const string& TxtImgIl1 = "", const string& TxtImgQwh = "", const string& TxtImgQhp = "", const string& TxtImgQdp = "", const string& TxtImgSiq = "", const string& TxtImgDxi = "", const string& TxtImgDyi = "", const string& TxtImgQlm = "", const string& TxtImgQdl = "", const uint numFCsiImgSte = 1);

	public:
		bool ButMasterOn;
		string TxtImgIl0;
		string TxtImgIl1;
		string TxtImgQwh;
		string TxtImgQhp;
		string TxtImgQdp;
		string TxtImgSiq;
		string TxtImgDxi;
		string TxtImgDyi;
		string TxtImgQlm;
		string TxtImgQdl;
		uint numFCsiImgSte;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecIaqQcdsp)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint PUPMODACTIVE = 2;
		static const uint SLDTINMIN = 3;
		static const uint SLDTINMAX = 4;
		static const uint SLDTINRAST = 5;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupModActive = true, const double SldTinMin = 1, const double SldTinMax = 1024, const double SldTinRast = 2);

	public:
		uint ixIdecVExpstate;
		bool PupModActive;
		double SldTinMin;
		double SldTinMax;
		double SldTinRast;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecIaqQcdsp)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTMOD = 2;
		static const uint BUTIMGSHOW = 3;
		static const uint CPTTIN = 4;

	public:
		Tag(const string& Cpt = "", const string& CptMod = "", const string& ButImgShow = "", const string& CptTin = "");

	public:
		string Cpt;
		string CptMod;
		string ButImgShow;
		string CptTin;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqQcdspData)
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
		* DpchAppDo (full: DpchAppIdecIaqQcdspDo)
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
		* DpchEngData (full: DpchEngIdecIaqQcdspData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIIMGSTE = 4;
		static const uint FEEDFPUPMOD = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiImgSte;
		Feed feedFPupMod;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqQcdspLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint TLWIR = 3;
		static const uint TQCD = 4;
		static const uint DELTATQCD = 5;

	public:
		DpchEngLive();

	public:
		ContInf continf;
		vector<double> Tlwir;
		vector<double> Tqcd;
		vector<double> DeltaTqcd;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

