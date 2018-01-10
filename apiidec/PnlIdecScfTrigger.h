/**
  * \file PnlIdecScfTrigger.h
  * API code for job PnlIdecScfTrigger (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFTRIGGER_H
#define PNLIDECSCFTRIGGER_H

#include "ApiIdec_blks.h"

#define VecVIdecScfTriggerDo PnlIdecScfTrigger::VecVDo

#define ContIacIdecScfTrigger PnlIdecScfTrigger::ContIac
#define ContInfIdecScfTrigger PnlIdecScfTrigger::ContInf
#define StatAppIdecScfTrigger PnlIdecScfTrigger::StatApp
#define StatShrIdecScfTrigger PnlIdecScfTrigger::StatShr
#define TagIdecScfTrigger PnlIdecScfTrigger::Tag

#define DpchAppIdecScfTriggerData PnlIdecScfTrigger::DpchAppData
#define DpchAppIdecScfTriggerDo PnlIdecScfTrigger::DpchAppDo
#define DpchEngIdecScfTriggerData PnlIdecScfTrigger::DpchEngData

/**
  * PnlIdecScfTrigger
  */
namespace PnlIdecScfTrigger {
	/**
		* VecVDo (full: VecVIdecScfTriggerDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfTrigger)
	  */
	class ContIac : public Block {

	public:
		static const uint SLDRDL = 1;
		static const uint SLDIDL = 2;
		static const uint SLDQDL = 3;

	public:
		ContIac(const double SldRdl = 0.0, const double SldIdl = 0.0, const double SldQdl = 0.0);

	public:
		double SldRdl;
		double SldIdl;
		double SldQdl;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfTrigger)
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
	  * StatApp (full: StatAppIdecScfTrigger)
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
	  * StatShr (full: StatShrIdecScfTrigger)
	  */
	class StatShr : public Block {

	public:
		static const uint SLDRDLACTIVE = 1;
		static const uint SLDRDLMIN = 2;
		static const uint SLDRDLMAX = 3;
		static const uint SLDRDLRAST = 4;
		static const uint SLDIDLACTIVE = 5;
		static const uint SLDIDLMIN = 6;
		static const uint SLDIDLMAX = 7;
		static const uint SLDIDLRAST = 8;
		static const uint SLDQDLACTIVE = 9;
		static const uint SLDQDLMIN = 10;
		static const uint SLDQDLMAX = 11;
		static const uint SLDQDLRAST = 12;

	public:
		StatShr(const bool SldRdlActive = true, const double SldRdlMin = -100, const double SldRdlMax = 100, const double SldRdlRast = 0.1, const bool SldIdlActive = true, const double SldIdlMin = -100, const double SldIdlMax = 100, const double SldIdlRast = 0.1, const bool SldQdlActive = true, const double SldQdlMin = -100, const double SldQdlMax = 100, const double SldQdlRast = 0.1);

	public:
		bool SldRdlActive;
		double SldRdlMin;
		double SldRdlMax;
		double SldRdlRast;
		bool SldIdlActive;
		double SldIdlMin;
		double SldIdlMax;
		double SldIdlRast;
		bool SldQdlActive;
		double SldQdlMin;
		double SldQdlMax;
		double SldQdlRast;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfTrigger)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTREF = 2;
		static const uint CPTRDL = 3;
		static const uint CPTIDL = 4;
		static const uint CPTQDL = 5;

	public:
		Tag(const string& Cpt = "", const string& CptRef = "", const string& CptRdl = "", const string& CptIdl = "", const string& CptQdl = "");

	public:
		string Cpt;
		string CptRef;
		string CptRdl;
		string CptIdl;
		string CptQdl;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfTriggerData)
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
		* DpchAppDo (full: DpchAppIdecScfTriggerDo)
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
		* DpchEngData (full: DpchEngIdecScfTriggerData)
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

