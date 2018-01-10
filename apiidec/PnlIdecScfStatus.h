/**
  * \file PnlIdecScfStatus.h
  * API code for job PnlIdecScfStatus (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFSTATUS_H
#define PNLIDECSCFSTATUS_H

#include "ApiIdec_blks.h"

#define VecVIdecScfStatusDo PnlIdecScfStatus::VecVDo
#define VecVIdecScfStatusSge PnlIdecScfStatus::VecVSge

#define ContInfIdecScfStatus PnlIdecScfStatus::ContInf
#define StatAppIdecScfStatus PnlIdecScfStatus::StatApp
#define StatShrIdecScfStatus PnlIdecScfStatus::StatShr
#define TagIdecScfStatus PnlIdecScfStatus::Tag

#define DpchAppIdecScfStatusDo PnlIdecScfStatus::DpchAppDo
#define DpchEngIdecScfStatusData PnlIdecScfStatus::DpchEngData

/**
  * PnlIdecScfStatus
  */
namespace PnlIdecScfStatus {
	/**
		* VecVDo (full: VecVIdecScfStatusDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;
		static const uint BUTTHECLEARCLICK = 2;
		static const uint BUTPHICLEARCLICK = 3;
		static const uint BUTSTECLEARCLICK = 4;
		static const uint BUTFUSCLEARCLICK = 5;
		static const uint BUTQNUCLEARCLICK = 6;
		static const uint BUTQALCLEARCLICK = 7;
		static const uint BUTACVCLEARCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecScfStatusSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRCTH = 2;
		static const uint ALRCPH = 3;
		static const uint ALRCST = 4;
		static const uint ALRCFU = 5;
		static const uint ALRCQN = 6;
		static const uint ALRCQA = 7;
		static const uint ALRCAC = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecScfStatus)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTTHE = 2;
		static const uint TXTPHI = 3;
		static const uint TXTSTE = 4;
		static const uint TXTFUS = 5;
		static const uint TXTQNU = 6;
		static const uint TXTQAL = 7;
		static const uint TXTACV = 8;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtThe = "", const string& TxtPhi = "", const string& TxtSte = "", const string& TxtFus = "", const string& TxtQnu = "", const string& TxtQal = "", const string& TxtAcv = "");

	public:
		bool ButMasterOn;
		string TxtThe;
		string TxtPhi;
		string TxtSte;
		string TxtFus;
		string TxtQnu;
		string TxtQal;
		string TxtAcv;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecScfStatus)
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
	  * StatShr (full: StatShrIdecScfStatus)
	  */
	class StatShr : public Block {

	public:
		static const uint BUTTHECLEARACTIVE = 1;
		static const uint BUTPHICLEARACTIVE = 2;
		static const uint BUTSTECLEARACTIVE = 3;
		static const uint BUTFUSCLEARACTIVE = 4;
		static const uint BUTQNUCLEARACTIVE = 5;
		static const uint BUTQALCLEARACTIVE = 6;
		static const uint BUTACVCLEARACTIVE = 7;

	public:
		StatShr(const bool ButTheClearActive = true, const bool ButPhiClearActive = true, const bool ButSteClearActive = true, const bool ButFusClearActive = true, const bool ButQnuClearActive = true, const bool ButQalClearActive = true, const bool ButAcvClearActive = true);

	public:
		bool ButTheClearActive;
		bool ButPhiClearActive;
		bool ButSteClearActive;
		bool ButFusClearActive;
		bool ButQnuClearActive;
		bool ButQalClearActive;
		bool ButAcvClearActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfStatus)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint HDGCALIB = 2;
		static const uint CPTTHE = 3;
		static const uint BUTTHECLEAR = 4;
		static const uint CPTPHI = 5;
		static const uint BUTPHICLEAR = 6;
		static const uint CPTSTE = 7;
		static const uint BUTSTECLEAR = 8;
		static const uint CPTFUS = 9;
		static const uint BUTFUSCLEAR = 10;
		static const uint CPTQNU = 11;
		static const uint BUTQNUCLEAR = 12;
		static const uint CPTQAL = 13;
		static const uint BUTQALCLEAR = 14;
		static const uint TXTACV = 15;
		static const uint CPTACV = 16;
		static const uint BUTACVCLEAR = 17;

	public:
		Tag(const string& Cpt = "", const string& HdgCalib = "", const string& CptThe = "", const string& ButTheClear = "", const string& CptPhi = "", const string& ButPhiClear = "", const string& CptSte = "", const string& ButSteClear = "", const string& CptFus = "", const string& ButFusClear = "", const string& CptQnu = "", const string& ButQnuClear = "", const string& CptQal = "", const string& ButQalClear = "", const string& TxtAcv = "", const string& CptAcv = "", const string& ButAcvClear = "");

	public:
		string Cpt;
		string HdgCalib;
		string CptThe;
		string ButTheClear;
		string CptPhi;
		string ButPhiClear;
		string CptSte;
		string ButSteClear;
		string CptFus;
		string ButFusClear;
		string CptQnu;
		string ButQnuClear;
		string CptQal;
		string ButQalClear;
		string TxtAcv;
		string CptAcv;
		string ButAcvClear;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecScfStatusDo)
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
		* DpchEngData (full: DpchEngIdecScfStatusData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint STATAPP = 3;
		static const uint STATSHR = 4;
		static const uint TAG = 5;

	public:
		DpchEngData();

	public:
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

