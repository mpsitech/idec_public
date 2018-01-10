/**
  * \file PnlIdecIaqLive.h
  * API code for job PnlIdecIaqLive (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQLIVE_H
#define PNLIDECIAQLIVE_H

#include "ApiIdec_blks.h"

#define VecVIdecIaqLiveDo PnlIdecIaqLive::VecVDo
#define VecVIdecIaqLiveSge PnlIdecIaqLive::VecVSge
#define VecVIdecIaqLiveSource PnlIdecIaqLive::VecVSource

#define ContIacIdecIaqLive PnlIdecIaqLive::ContIac
#define ContInfIdecIaqLive PnlIdecIaqLive::ContInf
#define StatShrIdecIaqLive PnlIdecIaqLive::StatShr
#define TagIdecIaqLive PnlIdecIaqLive::Tag

#define DpchAppIdecIaqLiveData PnlIdecIaqLive::DpchAppData
#define DpchAppIdecIaqLiveDo PnlIdecIaqLive::DpchAppDo
#define DpchEngIdecIaqLiveData PnlIdecIaqLive::DpchEngData
#define DpchEngIdecIaqLiveLive PnlIdecIaqLive::DpchEngLive

/**
  * PnlIdecIaqLive
  */
namespace PnlIdecIaqLive {
	/**
		* VecVDo (full: VecVIdecIaqLiveDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;
		static const uint BUTSNAPCLICK = 4;
		static const uint BUTRECCLICK = 5;
		static const uint BUTPLAYCLICK = 6;
		static const uint BUTSTOPCLICK = 7;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecIaqLiveSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRGUM = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSource (full: VecVIdecIaqLiveSource)
		*/
	class VecVSource {

	public:
		static const uint VISL = 1;
		static const uint VISR = 2;
		static const uint LWIR = 3;
		static const uint STEREO = 4;
		static const uint FUSION = 5;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecIaqLive)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPSRC = 1;
		static const uint NUMFPUPRES = 2;
		static const uint CHKGRS = 3;
		static const uint SLDFRR = 4;
		static const uint SLDEXT = 5;

	public:
		ContIac(const uint numFPupSrc = 1, const uint numFPupRes = 1, const bool ChkGrs = false, const double SldFrr = 1.0, const double SldExt = 0.0);

	public:
		uint numFPupSrc;
		uint numFPupRes;
		bool ChkGrs;
		double SldFrr;
		double SldExt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqLive)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTSTE = 2;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtSte = "");

	public:
		bool ButMasterOn;
		string TxtSte;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecIaqLive)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint CUSIMGHEIGHT = 2;
		static const uint CHKGRSAVAIL = 3;
		static const uint SLDCONAVAIL = 4;
		static const uint SLDCONMIN = 5;
		static const uint SLDCONMAX = 6;
		static const uint SLDBRIAVAIL = 7;
		static const uint SLDBRIMIN = 8;
		static const uint SLDBRIMAX = 9;
		static const uint SLDFRRACTIVE = 10;
		static const uint SLDFRRMIN = 11;
		static const uint SLDFRRMAX = 12;
		static const uint SLDFRRRAST = 13;
		static const uint SLDEXTAVAIL = 14;
		static const uint SLDEXTACTIVE = 15;
		static const uint SLDEXTMIN = 16;
		static const uint SLDEXTMAX = 17;
		static const uint SLDEXTRAST = 18;
		static const uint BUTPLAYACTIVE = 19;
		static const uint BUTSTOPACTIVE = 20;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const uint CusImgHeight = 480, const bool ChkGrsAvail = true, const bool SldConAvail = true, const double SldConMin = 1.0, const double SldConMax = 100.0, const bool SldBriAvail = true, const double SldBriMin = 0.0, const double SldBriMax = 1.0, const bool SldFrrActive = true, const double SldFrrMin = 1.0, const double SldFrrMax = 15.0, const double SldFrrRast = 0.1, const bool SldExtAvail = true, const bool SldExtActive = true, const double SldExtMin = 0.01, const double SldExtMax = 1.0, const double SldExtRast = 1.25893, const bool ButPlayActive = true, const bool ButStopActive = true);

	public:
		uint ixIdecVExpstate;
		uint CusImgHeight;
		bool ChkGrsAvail;
		bool SldConAvail;
		double SldConMin;
		double SldConMax;
		bool SldBriAvail;
		double SldBriMin;
		double SldBriMax;
		bool SldFrrActive;
		double SldFrrMin;
		double SldFrrMax;
		double SldFrrRast;
		bool SldExtAvail;
		bool SldExtActive;
		double SldExtMin;
		double SldExtMax;
		double SldExtRast;
		bool ButPlayActive;
		bool ButStopActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecIaqLive)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTSRC = 2;
		static const uint CPTRES = 3;
		static const uint CPTGRS = 4;
		static const uint CPTCON = 5;
		static const uint CPTBRI = 6;
		static const uint CPTFRR = 7;
		static const uint CPTEXT = 8;
		static const uint CPTSTE = 9;

	public:
		Tag(const string& Cpt = "", const string& CptSrc = "", const string& CptRes = "", const string& CptGrs = "", const string& CptCon = "", const string& CptBri = "", const string& CptFrr = "", const string& CptExt = "", const string& CptSte = "");

	public:
		string Cpt;
		string CptSrc;
		string CptRes;
		string CptGrs;
		string CptCon;
		string CptBri;
		string CptFrr;
		string CptExt;
		string CptSte;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqLiveData)
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
		* DpchAppDo (full: DpchAppIdecIaqLiveDo)
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
		* DpchEngData (full: DpchEngIdecIaqLiveData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPRES = 4;
		static const uint FEEDFPUPSRC = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupRes;
		Feed feedFPupSrc;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqLiveLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint RGB = 3;
		static const uint RED = 4;
		static const uint GREEN = 5;
		static const uint BLUE = 6;
		static const uint GRAY = 7;
		static const uint DEPTH = 8;

	public:
		DpchEngLive();

	public:
		ContInf continf;
		vector<utinyint> rgb;
		vector<utinyint> red;
		vector<utinyint> green;
		vector<utinyint> blue;
		vector<usmallint> gray;
		vector<float> depth;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

