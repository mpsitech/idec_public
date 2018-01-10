/**
  * \file PnlIdecAd1Control.h
  * API code for job PnlIdecAd1Control (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECAD1CONTROL_H
#define PNLIDECAD1CONTROL_H

#include "ApiIdec_blks.h"

#define VecVIdecAd1ControlDo PnlIdecAd1Control::VecVDo
#define VecVIdecAd1ControlSge PnlIdecAd1Control::VecVSge

#define ContIacIdecAd1Control PnlIdecAd1Control::ContIac
#define ContInfIdecAd1Control PnlIdecAd1Control::ContInf
#define StatAppIdecAd1Control PnlIdecAd1Control::StatApp
#define StatShrIdecAd1Control PnlIdecAd1Control::StatShr
#define TagIdecAd1Control PnlIdecAd1Control::Tag

#define DpchAppIdecAd1ControlData PnlIdecAd1Control::DpchAppData
#define DpchAppIdecAd1ControlDo PnlIdecAd1Control::DpchAppDo
#define DpchEngIdecAd1ControlData PnlIdecAd1Control::DpchEngData

/**
  * PnlIdecAd1Control
  */
namespace PnlIdecAd1Control {
	/**
		* VecVDo (full: VecVIdecAd1ControlDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;
		static const uint BUTRUNCLICK = 2;
		static const uint BUTSTOCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecAd1ControlSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRGUM = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecAd1Control)
	  */
	class ContIac : public Block {

	public:
		static const uint SLDTLL = 1;
		static const uint SLDTUL = 2;
		static const uint UPDMCT = 3;

	public:
		ContIac(const double SldTll = 0.0, const double SldTul = 0.0, const int UpdMct = 0);

	public:
		double SldTll;
		double SldTul;
		int UpdMct;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecAd1Control)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint BUTMASTERON = 2;
		static const uint TXTPRG = 3;

	public:
		ContInf(const uint numFSge = 1, const bool ButMasterOn = false, const string& TxtPrg = "");

	public:
		uint numFSge;
		bool ButMasterOn;
		string TxtPrg;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecAd1Control)
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
	  * StatShr (full: StatShrIdecAd1Control)
	  */
	class StatShr : public Block {

	public:
		static const uint SLDTLLMIN = 1;
		static const uint SLDTLLMAX = 2;
		static const uint SLDTULMIN = 3;
		static const uint SLDTULMAX = 4;
		static const uint UPDMCTMIN = 5;
		static const uint UPDMCTMAX = 6;
		static const uint BUTRUNACTIVE = 7;
		static const uint BUTSTOACTIVE = 8;

	public:
		StatShr(const double SldTllMin = 25.0, const double SldTllMax = 45.0, const double SldTulMin = 25.0, const double SldTulMax = 45.0, const int UpdMctMin = 1, const int UpdMctMax = 10, const bool ButRunActive = true, const bool ButStoActive = true);

	public:
		double SldTllMin;
		double SldTllMax;
		double SldTulMin;
		double SldTulMax;
		int UpdMctMin;
		int UpdMctMax;
		bool ButRunActive;
		bool ButStoActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecAd1Control)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint HDGROI = 2;
		static const uint CPTTLL = 3;
		static const uint CPTTUL = 4;
		static const uint CPTMCT = 5;
		static const uint CPTPRG = 6;
		static const uint BUTRUN = 7;
		static const uint BUTSTO = 8;

	public:
		Tag(const string& Cpt = "", const string& HdgRoi = "", const string& CptTll = "", const string& CptTul = "", const string& CptMct = "", const string& CptPrg = "", const string& ButRun = "", const string& ButSto = "");

	public:
		string Cpt;
		string HdgRoi;
		string CptTll;
		string CptTul;
		string CptMct;
		string CptPrg;
		string ButRun;
		string ButSto;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecAd1ControlData)
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
		* DpchAppDo (full: DpchAppIdecAd1ControlDo)
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
		* DpchEngData (full: DpchEngIdecAd1ControlData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFSGE = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFSge;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

