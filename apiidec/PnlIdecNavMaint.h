/**
  * \file PnlIdecNavMaint.h
  * API code for job PnlIdecNavMaint (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVMAINT_H
#define PNLIDECNAVMAINT_H

#include "ApiIdec_blks.h"

#define VecVIdecNavMaintDo PnlIdecNavMaint::VecVDo

#define ContIacIdecNavMaint PnlIdecNavMaint::ContIac
#define StatAppIdecNavMaint PnlIdecNavMaint::StatApp
#define StatShrIdecNavMaint PnlIdecNavMaint::StatShr
#define TagIdecNavMaint PnlIdecNavMaint::Tag

#define DpchAppIdecNavMaintData PnlIdecNavMaint::DpchAppData
#define DpchAppIdecNavMaintDo PnlIdecNavMaint::DpchAppDo
#define DpchEngIdecNavMaintData PnlIdecNavMaint::DpchEngData

/**
  * PnlIdecNavMaint
  */
namespace PnlIdecNavMaint {
	/**
		* VecVDo (full: VecVIdecNavMaintDo)
		*/
	class VecVDo {

	public:
		static const uint BUTUSGVIEWCLICK = 1;
		static const uint BUTUSGNEWCRDCLICK = 2;
		static const uint BUTUSRVIEWCLICK = 3;
		static const uint BUTUSRNEWCRDCLICK = 4;
		static const uint BUTSCFNEWCRDCLICK = 5;
		static const uint BUTUTLNEWCRDCLICK = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecNavMaint)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFLSTUSG = 1;
		static const uint NUMFLSTUSR = 2;

	public:
		ContIac(const uint numFLstUsg = 1, const uint numFLstUsr = 1);

	public:
		uint numFLstUsg;
		uint numFLstUsr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * StatApp (full: StatAppIdecNavMaint)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint LSTUSGALT = 2;
		static const uint LSTUSRALT = 3;
		static const uint LSTUSGNUMFIRSTDISP = 4;
		static const uint LSTUSRNUMFIRSTDISP = 5;

	public:
		StatApp(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool LstUsgAlt = true, const bool LstUsrAlt = true, const uint LstUsgNumFirstdisp = 1, const uint LstUsrNumFirstdisp = 1);

	public:
		uint ixIdecVExpstate;
		bool LstUsgAlt;
		bool LstUsrAlt;
		uint LstUsgNumFirstdisp;
		uint LstUsrNumFirstdisp;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecNavMaint)
	  */
	class StatShr : public Block {

	public:
		static const uint LSTUSGAVAIL = 1;
		static const uint BUTUSGVIEWACTIVE = 2;
		static const uint LSTUSRAVAIL = 3;
		static const uint BUTUSRVIEWACTIVE = 4;

	public:
		StatShr(const bool LstUsgAvail = true, const bool ButUsgViewActive = true, const bool LstUsrAvail = true, const bool ButUsrViewActive = true);

	public:
		bool LstUsgAvail;
		bool ButUsgViewActive;
		bool LstUsrAvail;
		bool ButUsrViewActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecNavMaint)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTUSG = 2;
		static const uint CPTUSR = 3;
		static const uint CPTSCF = 4;
		static const uint CPTUTL = 5;

	public:
		Tag(const string& Cpt = "", const string& CptUsg = "", const string& CptUsr = "", const string& CptScf = "", const string& CptUtl = "");

	public:
		string Cpt;
		string CptUsg;
		string CptUsr;
		string CptScf;
		string CptUtl;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecNavMaintData)
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
		* DpchAppDo (full: DpchAppIdecNavMaintDo)
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
		* DpchEngData (full: DpchEngIdecNavMaintData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFLSTUSG = 3;
		static const uint FEEDFLSTUSR = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		Feed feedFLstUsg;
		Feed feedFLstUsr;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

