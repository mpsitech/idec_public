/**
  * \file PnlIdecNavOpr.h
  * API code for job PnlIdecNavOpr (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVOPR_H
#define PNLIDECNAVOPR_H

#include "ApiIdec_blks.h"

#define VecVIdecNavOprDo PnlIdecNavOpr::VecVDo

#define ContIacIdecNavOpr PnlIdecNavOpr::ContIac
#define StatAppIdecNavOpr PnlIdecNavOpr::StatApp
#define StatShrIdecNavOpr PnlIdecNavOpr::StatShr
#define TagIdecNavOpr PnlIdecNavOpr::Tag

#define DpchAppIdecNavOprData PnlIdecNavOpr::DpchAppData
#define DpchAppIdecNavOprDo PnlIdecNavOpr::DpchAppDo
#define DpchEngIdecNavOprData PnlIdecNavOpr::DpchEngData

/**
  * PnlIdecNavOpr
  */
namespace PnlIdecNavOpr {
	/**
		* VecVDo (full: VecVIdecNavOprDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMISVIEWCLICK = 1;
		static const uint BUTMISNEWCRDCLICK = 2;
		static const uint BUTTOUVIEWCLICK = 3;
		static const uint BUTTOUNEWCRDCLICK = 4;
		static const uint BUTIAQNEWCRDCLICK = 5;
		static const uint BUTAD1NEWCRDCLICK = 6;
		static const uint BUTFILVIEWCLICK = 7;
		static const uint BUTFILNEWCRDCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecNavOpr)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFLSTMIS = 1;
		static const uint NUMFLSTTOU = 2;
		static const uint NUMFLSTFIL = 3;

	public:
		ContIac(const uint numFLstMis = 1, const uint numFLstTou = 1, const uint numFLstFil = 1);

	public:
		uint numFLstMis;
		uint numFLstTou;
		uint numFLstFil;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * StatApp (full: StatAppIdecNavOpr)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint LSTMISALT = 2;
		static const uint LSTTOUALT = 3;
		static const uint LSTFILALT = 4;
		static const uint LSTMISNUMFIRSTDISP = 5;
		static const uint LSTTOUNUMFIRSTDISP = 6;
		static const uint LSTFILNUMFIRSTDISP = 7;

	public:
		StatApp(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool LstMisAlt = true, const bool LstTouAlt = true, const bool LstFilAlt = true, const uint LstMisNumFirstdisp = 1, const uint LstTouNumFirstdisp = 1, const uint LstFilNumFirstdisp = 1);

	public:
		uint ixIdecVExpstate;
		bool LstMisAlt;
		bool LstTouAlt;
		bool LstFilAlt;
		uint LstMisNumFirstdisp;
		uint LstTouNumFirstdisp;
		uint LstFilNumFirstdisp;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecNavOpr)
	  */
	class StatShr : public Block {

	public:
		static const uint LSTMISAVAIL = 1;
		static const uint BUTMISVIEWACTIVE = 2;
		static const uint LSTTOUAVAIL = 3;
		static const uint BUTTOUVIEWACTIVE = 4;
		static const uint BUTTOUNEWCRDACTIVE = 5;
		static const uint BUTIAQNEWCRDACTIVE = 6;
		static const uint BUTAD1NEWCRDACTIVE = 7;
		static const uint LSTFILAVAIL = 8;
		static const uint BUTFILVIEWACTIVE = 9;
		static const uint BUTFILNEWCRDACTIVE = 10;

	public:
		StatShr(const bool LstMisAvail = true, const bool ButMisViewActive = true, const bool LstTouAvail = true, const bool ButTouViewActive = true, const bool ButTouNewcrdActive = true, const bool ButIaqNewcrdActive = true, const bool ButAd1NewcrdActive = true, const bool LstFilAvail = true, const bool ButFilViewActive = true, const bool ButFilNewcrdActive = true);

	public:
		bool LstMisAvail;
		bool ButMisViewActive;
		bool LstTouAvail;
		bool ButTouViewActive;
		bool ButTouNewcrdActive;
		bool ButIaqNewcrdActive;
		bool ButAd1NewcrdActive;
		bool LstFilAvail;
		bool ButFilViewActive;
		bool ButFilNewcrdActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecNavOpr)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTMIS = 2;
		static const uint CPTTOU = 3;
		static const uint CPTIAQ = 4;
		static const uint CPTAD1 = 5;
		static const uint CPTFIL = 6;

	public:
		Tag(const string& Cpt = "", const string& CptMis = "", const string& CptTou = "", const string& CptIaq = "", const string& CptAd1 = "", const string& CptFil = "");

	public:
		string Cpt;
		string CptMis;
		string CptTou;
		string CptIaq;
		string CptAd1;
		string CptFil;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecNavOprData)
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
		* DpchAppDo (full: DpchAppIdecNavOprDo)
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
		* DpchEngData (full: DpchEngIdecNavOprData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFLSTFIL = 3;
		static const uint FEEDFLSTMIS = 4;
		static const uint FEEDFLSTTOU = 5;
		static const uint STATAPP = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		Feed feedFLstFil;
		Feed feedFLstMis;
		Feed feedFLstTou;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

