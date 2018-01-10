/**
  * \file PnlIdecScfLwir.h
  * API code for job PnlIdecScfLwir (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFLWIR_H
#define PNLIDECSCFLWIR_H

#include "ApiIdec_blks.h"

#define VecVIdecScfLwirDo PnlIdecScfLwir::VecVDo

#define ContIacIdecScfLwir PnlIdecScfLwir::ContIac
#define ContInfIdecScfLwir PnlIdecScfLwir::ContInf
#define StatAppIdecScfLwir PnlIdecScfLwir::StatApp
#define StatShrIdecScfLwir PnlIdecScfLwir::StatShr
#define TagIdecScfLwir PnlIdecScfLwir::Tag

#define DpchAppIdecScfLwirData PnlIdecScfLwir::DpchAppData
#define DpchAppIdecScfLwirDo PnlIdecScfLwir::DpchAppDo
#define DpchEngIdecScfLwirData PnlIdecScfLwir::DpchEngData

/**
  * PnlIdecScfLwir
  */
namespace PnlIdecScfLwir {
	/**
		* VecVDo (full: VecVIdecScfLwirDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfLwir)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFLM0 = 1;
		static const uint TXFLM1 = 2;

	public:
		ContIac(const string& TxfLm0 = "", const string& TxfLm1 = "");

	public:
		string TxfLm0;
		string TxfLm1;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfLwir)
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
	  * StatApp (full: StatAppIdecScfLwir)
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
	  * StatShr (full: StatShrIdecScfLwir)
	  */
	class StatShr : public Block {

	public:
		static const uint TXFLM0ACTIVE = 1;
		static const uint TXFLM1ACTIVE = 2;

	public:
		StatShr(const bool TxfLm0Active = true, const bool TxfLm1Active = true);

	public:
		bool TxfLm0Active;
		bool TxfLm1Active;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfLwir)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTLM0 = 2;
		static const uint CPTLM1 = 3;

	public:
		Tag(const string& Cpt = "", const string& CptLm0 = "", const string& CptLm1 = "");

	public:
		string Cpt;
		string CptLm0;
		string CptLm1;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfLwirData)
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
		* DpchAppDo (full: DpchAppIdecScfLwirDo)
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
		* DpchEngData (full: DpchEngIdecScfLwirData)
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

