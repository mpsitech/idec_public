/**
  * \file PnlIdecIaqMech.h
  * API code for job PnlIdecIaqMech (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQMECH_H
#define PNLIDECIAQMECH_H

#include "ApiIdec_blks.h"

#define VecVIdecIaqMechDo PnlIdecIaqMech::VecVDo
#define VecVIdecIaqMechMode PnlIdecIaqMech::VecVMode
#define VecVIdecIaqMechSge PnlIdecIaqMech::VecVSge

#define ContIacIdecIaqMech PnlIdecIaqMech::ContIac
#define ContInfIdecIaqMech PnlIdecIaqMech::ContInf
#define StatShrIdecIaqMech PnlIdecIaqMech::StatShr
#define TagIdecIaqMech PnlIdecIaqMech::Tag

#define DpchAppIdecIaqMechData PnlIdecIaqMech::DpchAppData
#define DpchAppIdecIaqMechDo PnlIdecIaqMech::DpchAppDo
#define DpchEngIdecIaqMechData PnlIdecIaqMech::DpchEngData
#define DpchEngIdecIaqMechLive PnlIdecIaqMech::DpchEngLive

/**
  * PnlIdecIaqMech
  */
namespace PnlIdecIaqMech {
	/**
		* VecVDo (full: VecVIdecIaqMechDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;
		static const uint BUTTHECCWCLICK = 4;
		static const uint BUTTHECCWSTMDN = 5;
		static const uint BUTTHECCWSTMUP = 6;
		static const uint BUTTHECWSTMDN = 7;
		static const uint BUTTHECWSTMUP = 8;
		static const uint BUTTHECWCLICK = 9;
		static const uint BUTPHICCWCLICK = 10;
		static const uint BUTPHICCWSTMDN = 11;
		static const uint BUTPHICCWSTMUP = 12;
		static const uint BUTPHICWSTMDN = 13;
		static const uint BUTPHICWSTMUP = 14;
		static const uint BUTPHICWCLICK = 15;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqMechMode)
		*/
	class VecVMode {

	public:
		static const uint MANUAL = 1;
		static const uint INTACT = 2;
		static const uint AUTO = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecIaqMechSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecIaqMech)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTVV = 2;
		static const uint CUSTHEANS = 3;
		static const uint CUSPHIANS = 4;

	public:
		ContIac(const uint numFPupMod = 2, const double SldTvv = 0.0, const double CusTheAns = 0.0, const double CusPhiAns = 0.0);

	public:
		uint numFPupMod;
		double SldTvv;
		double CusTheAns;
		double CusPhiAns;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqMech)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTTHEANG = 2;
		static const uint TXTTHERPM = 3;
		static const uint NUMFCSITHESTE = 4;
		static const uint BUTTHECCWON = 5;
		static const uint BUTTHECWON = 6;
		static const uint TXTPHIANG = 7;
		static const uint TXTPHIRPM = 8;
		static const uint NUMFCSIPHISTE = 9;
		static const uint BUTPHICCWON = 10;
		static const uint BUTPHICWON = 11;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtTheAng = "", const string& TxtTheRpm = "", const uint numFCsiTheSte = 1, const bool ButTheCcwOn = false, const bool ButTheCwOn = false, const string& TxtPhiAng = "", const string& TxtPhiRpm = "", const uint numFCsiPhiSte = 1, const bool ButPhiCcwOn = false, const bool ButPhiCwOn = false);

	public:
		bool ButMasterOn;
		string TxtTheAng;
		string TxtTheRpm;
		uint numFCsiTheSte;
		bool ButTheCcwOn;
		bool ButTheCwOn;
		string TxtPhiAng;
		string TxtPhiRpm;
		uint numFCsiPhiSte;
		bool ButPhiCcwOn;
		bool ButPhiCwOn;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecIaqMech)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SLDTVVAVAIL = 2;
		static const uint SLDTVVMIN = 3;
		static const uint SLDTVVMAX = 4;
		static const uint CUSTHEANSACTIVE = 5;
		static const uint BUTTHECCWACTIVE = 6;
		static const uint BUTTHECCWSTACTIVE = 7;
		static const uint BUTTHECWSTACTIVE = 8;
		static const uint BUTTHECWACTIVE = 9;
		static const uint CUSPHIANSACTIVE = 10;
		static const uint BUTPHICCWACTIVE = 11;
		static const uint BUTPHICCWSTACTIVE = 12;
		static const uint BUTPHICWSTACTIVE = 13;
		static const uint BUTPHICWACTIVE = 14;
		static const uint CUSTHEANSMIN = 15;
		static const uint CUSTHEANSMAX = 16;
		static const uint CUSPHIANSMIN = 17;
		static const uint CUSPHIANSMAX = 18;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool SldTvvAvail = true, const double SldTvvMin = -10.0, const double SldTvvMax = 10.0, const bool CusTheAnsActive = true, const bool ButTheCcwActive = true, const bool ButTheCcwstActive = true, const bool ButTheCwstActive = true, const bool ButTheCwActive = true, const bool CusPhiAnsActive = true, const bool ButPhiCcwActive = true, const bool ButPhiCcwstActive = true, const bool ButPhiCwstActive = true, const bool ButPhiCwActive = true, const double CusTheAnsMin = -60.0, const double CusTheAnsMax = 60.0, const double CusPhiAnsMin = -45.0, const double CusPhiAnsMax = 45.0);

	public:
		uint ixIdecVExpstate;
		bool SldTvvAvail;
		double SldTvvMin;
		double SldTvvMax;
		bool CusTheAnsActive;
		bool ButTheCcwActive;
		bool ButTheCcwstActive;
		bool ButTheCwstActive;
		bool ButTheCwActive;
		bool CusPhiAnsActive;
		bool ButPhiCcwActive;
		bool ButPhiCcwstActive;
		bool ButPhiCwstActive;
		bool ButPhiCwActive;
		double CusTheAnsMin;
		double CusTheAnsMax;
		double CusPhiAnsMin;
		double CusPhiAnsMax;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecIaqMech)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTMOD = 2;
		static const uint CPTTVV = 3;

	public:
		Tag(const string& Cpt = "", const string& CptMod = "", const string& CptTvv = "");

	public:
		string Cpt;
		string CptMod;
		string CptTvv;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqMechData)
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
		* DpchAppDo (full: DpchAppIdecIaqMechDo)
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
		* DpchEngData (full: DpchEngIdecIaqMechData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIPHISTE = 4;
		static const uint FEEDFCSITHESTE = 5;
		static const uint FEEDFPUPMOD = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiPhiSte;
		Feed feedFCsiTheSte;
		Feed feedFPupMod;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqMechLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;

	public:
		DpchEngLive();

	public:
		ContInf continf;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

