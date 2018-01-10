/**
  * \file PnlIdecScfQcd.h
  * API code for job PnlIdecScfQcd (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFQCD_H
#define PNLIDECSCFQCD_H

#include "ApiIdec_blks.h"

#define VecVIdecScfQcdDo PnlIdecScfQcd::VecVDo

#define ContIacIdecScfQcd PnlIdecScfQcd::ContIac
#define ContInfIdecScfQcd PnlIdecScfQcd::ContInf
#define StatAppIdecScfQcd PnlIdecScfQcd::StatApp
#define StatShrIdecScfQcd PnlIdecScfQcd::StatShr
#define TagIdecScfQcd PnlIdecScfQcd::Tag

#define DpchAppIdecScfQcdData PnlIdecScfQcd::DpchAppData
#define DpchAppIdecScfQcdDo PnlIdecScfQcd::DpchAppDo
#define DpchEngIdecScfQcdData PnlIdecScfQcd::DpchEngData

/**
  * PnlIdecScfQcd
  */
namespace PnlIdecScfQcd {
	/**
		* VecVDo (full: VecVIdecScfQcdDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfQcd)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFLAM = 1;
		static const uint TXFDLM = 2;
		static const uint CHKAON = 3;
		static const uint SLDTOF = 4;
		static const uint SLDTMP = 5;
		static const uint NUMFPUPFAN = 6;
		static const uint SLDFMD = 7;
		static const uint SLDVDD = 8;
		static const uint CHKVD2 = 9;
		static const uint SLDVRF = 10;
		static const uint UPDASL = 11;
		static const uint SLDAMO = 12;
		static const uint CHKAAD = 13;

	public:
		ContIac(const string& TxfLam = "", const string& TxfDlm = "", const bool ChkAon = false, const double SldTof = 0.0, const double SldTmp = 0.0, const uint numFPupFan = 1, const double SldFmd = 0.0, const double SldVdd = 0.0, const bool ChkVd2 = false, const double SldVrf = 0.0, const int UpdAsl = 0, const double SldAmo = 0.0, const bool ChkAad = false);

	public:
		string TxfLam;
		string TxfDlm;
		bool ChkAon;
		double SldTof;
		double SldTmp;
		uint numFPupFan;
		double SldFmd;
		double SldVdd;
		bool ChkVd2;
		double SldVrf;
		int UpdAsl;
		double SldAmo;
		bool ChkAad;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfQcd)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;

	public:
		ContInf(const bool ButMasterOn = false);

	public:
		bool ButMasterOn;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecScfQcd)
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
	  * StatShr (full: StatShrIdecScfQcd)
	  */
	class StatShr : public Block {

	public:
		static const uint TXFLAMACTIVE = 1;
		static const uint TXFDLMACTIVE = 2;
		static const uint CHKAONACTIVE = 3;
		static const uint SLDTOFACTIVE = 4;
		static const uint SLDTOFMIN = 5;
		static const uint SLDTOFMAX = 6;
		static const uint SLDTOFRAST = 7;
		static const uint SLDTMPACTIVE = 8;
		static const uint SLDTMPMIN = 9;
		static const uint SLDTMPMAX = 10;
		static const uint SLDTMPRAST = 11;
		static const uint PUPFANACTIVE = 12;
		static const uint SLDFMDACTIVE = 13;
		static const uint SLDFMDMIN = 14;
		static const uint SLDFMDMAX = 15;
		static const uint SLDFMDRAST = 16;
		static const uint SLDVDDACTIVE = 17;
		static const uint SLDVDDMIN = 18;
		static const uint SLDVDDMAX = 19;
		static const uint SLDVDDRAST = 20;
		static const uint CHKVD2ACTIVE = 21;
		static const uint SLDVRFACTIVE = 22;
		static const uint SLDVRFMIN = 23;
		static const uint SLDVRFMAX = 24;
		static const uint SLDVRFRAST = 25;
		static const uint UPDASLACTIVE = 26;
		static const uint UPDASLMIN = 27;
		static const uint UPDASLMAX = 28;
		static const uint SLDAMOACTIVE = 29;
		static const uint SLDAMOMIN = 30;
		static const uint SLDAMOMAX = 31;
		static const uint SLDAMORAST = 32;
		static const uint CHKAADACTIVE = 33;

	public:
		StatShr(const bool TxfLamActive = true, const bool TxfDlmActive = true, const bool ChkAonActive = true, const bool SldTofActive = true, const double SldTofMin = 30, const double SldTofMax = 960, const double SldTofRast = 2, const bool SldTmpActive = true, const double SldTmpMin = -50, const double SldTmpMax = 10, const double SldTmpRast = 1, const bool PupFanActive = true, const bool SldFmdActive = true, const double SldFmdMin = 100, const double SldFmdMax = 300, const double SldFmdRast = 10, const bool SldVddActive = true, const double SldVddMin = 2.8, const double SldVddMax = 3.8, const double SldVddRast = 0.1, const bool ChkVd2Active = true, const bool SldVrfActive = true, const double SldVrfMin = 1.0, const double SldVrfMax = 3.0, const double SldVrfRast = 0.05, const bool UpdAslActive = true, const int UpdAslMin = 0, const int UpdAslMax = 100, const bool SldAmoActive = true, const double SldAmoMin = 0.5, const double SldAmoMax = 5.0, const double SldAmoRast = 0.5, const bool ChkAadActive = true);

	public:
		bool TxfLamActive;
		bool TxfDlmActive;
		bool ChkAonActive;
		bool SldTofActive;
		double SldTofMin;
		double SldTofMax;
		double SldTofRast;
		bool SldTmpActive;
		double SldTmpMin;
		double SldTmpMax;
		double SldTmpRast;
		bool PupFanActive;
		bool SldFmdActive;
		double SldFmdMin;
		double SldFmdMax;
		double SldFmdRast;
		bool SldVddActive;
		double SldVddMin;
		double SldVddMax;
		double SldVddRast;
		bool ChkVd2Active;
		bool SldVrfActive;
		double SldVrfMin;
		double SldVrfMax;
		double SldVrfRast;
		bool UpdAslActive;
		int UpdAslMin;
		int UpdAslMax;
		bool SldAmoActive;
		double SldAmoMin;
		double SldAmoMax;
		double SldAmoRast;
		bool ChkAadActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfQcd)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTLAM = 2;
		static const uint CPTDLM = 3;
		static const uint CPTAON = 4;
		static const uint CPTTOF = 5;
		static const uint CPTTMP = 6;
		static const uint CPTFAN = 7;
		static const uint CPTFMD = 8;
		static const uint CPTVDD = 9;
		static const uint CPTVD2 = 10;
		static const uint CPTVRF = 11;
		static const uint CPTALIGN = 12;
		static const uint CPTASL = 13;
		static const uint CPTAMO = 14;
		static const uint CPTAAD = 15;

	public:
		Tag(const string& Cpt = "", const string& CptLam = "", const string& CptDlm = "", const string& CptAon = "", const string& CptTof = "", const string& CptTmp = "", const string& CptFan = "", const string& CptFmd = "", const string& CptVdd = "", const string& CptVd2 = "", const string& CptVrf = "", const string& CptAlign = "", const string& CptAsl = "", const string& CptAmo = "", const string& CptAad = "");

	public:
		string Cpt;
		string CptLam;
		string CptDlm;
		string CptAon;
		string CptTof;
		string CptTmp;
		string CptFan;
		string CptFmd;
		string CptVdd;
		string CptVd2;
		string CptVrf;
		string CptAlign;
		string CptAsl;
		string CptAmo;
		string CptAad;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfQcdData)
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
		* DpchAppDo (full: DpchAppIdecScfQcdDo)
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
		* DpchEngData (full: DpchEngIdecScfQcdData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPFAN = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupFan;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

