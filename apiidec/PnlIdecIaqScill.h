/**
  * \file PnlIdecIaqScill.h
  * API code for job PnlIdecIaqScill (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQSCILL_H
#define PNLIDECIAQSCILL_H

#include "ApiIdec_blks.h"

#define VecVIdecIaqScillDo PnlIdecIaqScill::VecVDo
#define VecVIdecIaqScillMode PnlIdecIaqScill::VecVMode

#define ContIacIdecIaqScill PnlIdecIaqScill::ContIac
#define ContInfIdecIaqScill PnlIdecIaqScill::ContInf
#define StatAppIdecIaqScill PnlIdecIaqScill::StatApp
#define StatShrIdecIaqScill PnlIdecIaqScill::StatShr
#define TagIdecIaqScill PnlIdecIaqScill::Tag

#define DpchAppIdecIaqScillData PnlIdecIaqScill::DpchAppData
#define DpchAppIdecIaqScillDo PnlIdecIaqScill::DpchAppDo
#define DpchEngIdecIaqScillData PnlIdecIaqScill::DpchEngData

/**
  * PnlIdecIaqScill
  */
namespace PnlIdecIaqScill {
	/**
		* VecVDo (full: VecVIdecIaqScillDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqScillMode)
		*/
	class VecVMode {

	public:
		static const uint MANUAL = 1;
		static const uint AUTOLIVE = 2;
		static const uint AUTOREC = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecIaqScill)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTHR = 2;
		static const uint SLDFLD = 3;
		static const uint SLDSPT = 4;

	public:
		ContIac(const uint numFPupMod = 2, const double SldThr = 0.0, const double SldFld = 0.0, const double SldSpt = 0.0);

	public:
		uint numFPupMod;
		double SldThr;
		double SldFld;
		double SldSpt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqScill)
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
	  * StatApp (full: StatAppIdecIaqScill)
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
	  * StatShr (full: StatShrIdecIaqScill)
	  */
	class StatShr : public Block {

	public:
		static const uint PUPMODACTIVE = 1;
		static const uint SLDTHRAVAIL = 2;
		static const uint SLDTHRACTIVE = 3;
		static const uint SLDTHRMIN = 4;
		static const uint SLDTHRMAX = 5;
		static const uint SLDFLDACTIVE = 6;
		static const uint SLDFLDMIN = 7;
		static const uint SLDFLDMAX = 8;
		static const uint SLDSPTACTIVE = 9;
		static const uint SLDSPTMIN = 10;
		static const uint SLDSPTMAX = 11;

	public:
		StatShr(const bool PupModActive = true, const bool SldThrAvail = true, const bool SldThrActive = true, const double SldThrMin = 0.0, const double SldThrMax = 1.0, const bool SldFldActive = true, const double SldFldMin = 0.0, const double SldFldMax = 1.0, const bool SldSptActive = true, const double SldSptMin = 0.0, const double SldSptMax = 1.0);

	public:
		bool PupModActive;
		bool SldThrAvail;
		bool SldThrActive;
		double SldThrMin;
		double SldThrMax;
		bool SldFldActive;
		double SldFldMin;
		double SldFldMax;
		bool SldSptActive;
		double SldSptMin;
		double SldSptMax;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecIaqScill)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTMOD = 2;
		static const uint CPTTHR = 3;
		static const uint CPTFLD = 4;
		static const uint CPTSPT = 5;

	public:
		Tag(const string& Cpt = "", const string& CptMod = "", const string& CptThr = "", const string& CptFld = "", const string& CptSpt = "");

	public:
		string Cpt;
		string CptMod;
		string CptThr;
		string CptFld;
		string CptSpt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqScillData)
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
		* DpchAppDo (full: DpchAppIdecIaqScillDo)
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
		* DpchEngData (full: DpchEngIdecIaqScillData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPMOD = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupMod;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

