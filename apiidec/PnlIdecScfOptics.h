/**
  * \file PnlIdecScfOptics.h
  * API code for job PnlIdecScfOptics (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFOPTICS_H
#define PNLIDECSCFOPTICS_H

#include "ApiIdec_blks.h"

#define VecVIdecScfOpticsDo PnlIdecScfOptics::VecVDo

#define ContIacIdecScfOptics PnlIdecScfOptics::ContIac
#define ContInfIdecScfOptics PnlIdecScfOptics::ContInf
#define StatAppIdecScfOptics PnlIdecScfOptics::StatApp
#define StatShrIdecScfOptics PnlIdecScfOptics::StatShr
#define TagIdecScfOptics PnlIdecScfOptics::Tag

#define DpchAppIdecScfOpticsData PnlIdecScfOptics::DpchAppData
#define DpchAppIdecScfOpticsDo PnlIdecScfOptics::DpchAppDo
#define DpchEngIdecScfOpticsData PnlIdecScfOptics::DpchEngData

/**
  * PnlIdecScfOptics
  */
namespace PnlIdecScfOptics {
	/**
		* VecVDo (full: VecVIdecScfOpticsDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfOptics)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFDST = 1;
		static const uint TXFIDX = 2;
		static const uint TXFIDY = 3;
		static const uint TXFQDX = 4;
		static const uint TXFQDY = 5;
		static const uint TXFADX = 6;
		static const uint TXFADY = 7;
		static const uint NUMFPUPLSG = 8;
		static const uint NUMFPUPRSG = 9;
		static const uint NUMFPUPISG = 10;
		static const uint UPDQWH = 11;
		static const uint TXFQHP = 12;
		static const uint TXFQDP = 13;
		static const uint TXFQFL = 14;
		static const uint TXFQFN = 15;
		static const uint NUMFPUPQSG = 16;

	public:
		ContIac(const string& TxfDst = "", const string& TxfIdx = "", const string& TxfIdy = "", const string& TxfQdx = "", const string& TxfQdy = "", const string& TxfAdx = "", const string& TxfAdy = "", const uint numFPupLsg = 1, const uint numFPupRsg = 1, const uint numFPupIsg = 1, const int UpdQwh = 0, const string& TxfQhp = "", const string& TxfQdp = "", const string& TxfQfl = "", const string& TxfQfn = "", const uint numFPupQsg = 1);

	public:
		string TxfDst;
		string TxfIdx;
		string TxfIdy;
		string TxfQdx;
		string TxfQdy;
		string TxfAdx;
		string TxfAdy;
		uint numFPupLsg;
		uint numFPupRsg;
		uint numFPupIsg;
		int UpdQwh;
		string TxfQhp;
		string TxfQdp;
		string TxfQfl;
		string TxfQfn;
		uint numFPupQsg;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfOptics)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTVWI = 2;
		static const uint TXTVHE = 3;
		static const uint TXTVHP = 4;
		static const uint TXTVFL = 5;
		static const uint TXTVFN = 6;
		static const uint TXTIWI = 7;
		static const uint TXTIHE = 8;
		static const uint TXTIHP = 9;
		static const uint TXTIFL = 10;
		static const uint TXTIFN = 11;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtVwi = "", const string& TxtVhe = "", const string& TxtVhp = "", const string& TxtVfl = "", const string& TxtVfn = "", const string& TxtIwi = "", const string& TxtIhe = "", const string& TxtIhp = "", const string& TxtIfl = "", const string& TxtIfn = "");

	public:
		bool ButMasterOn;
		string TxtVwi;
		string TxtVhe;
		string TxtVhp;
		string TxtVfl;
		string TxtVfn;
		string TxtIwi;
		string TxtIhe;
		string TxtIhp;
		string TxtIfl;
		string TxtIfn;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecScfOptics)
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
	  * StatShr (full: StatShrIdecScfOptics)
	  */
	class StatShr : public Block {

	public:
		static const uint TXFDSTACTIVE = 1;
		static const uint TXFIDXACTIVE = 2;
		static const uint TXFIDYACTIVE = 3;
		static const uint TXFQDXACTIVE = 4;
		static const uint TXFQDYACTIVE = 5;
		static const uint TXFADXACTIVE = 6;
		static const uint TXFADYACTIVE = 7;
		static const uint PUPLSGACTIVE = 8;
		static const uint PUPRSGACTIVE = 9;
		static const uint PUPISGACTIVE = 10;
		static const uint UPDQWHACTIVE = 11;
		static const uint UPDQWHMIN = 12;
		static const uint UPDQWHMAX = 13;
		static const uint TXFQHPACTIVE = 14;
		static const uint TXFQDPACTIVE = 15;
		static const uint TXFQFLACTIVE = 16;
		static const uint TXFQFNACTIVE = 17;
		static const uint PUPQSGACTIVE = 18;

	public:
		StatShr(const bool TxfDstActive = true, const bool TxfIdxActive = true, const bool TxfIdyActive = true, const bool TxfQdxActive = true, const bool TxfQdyActive = true, const bool TxfAdxActive = true, const bool TxfAdyActive = true, const bool PupLsgActive = true, const bool PupRsgActive = true, const bool PupIsgActive = true, const bool UpdQwhActive = true, const int UpdQwhMin = 0, const int UpdQwhMax = 100, const bool TxfQhpActive = true, const bool TxfQdpActive = true, const bool TxfQflActive = true, const bool TxfQfnActive = true, const bool PupQsgActive = true);

	public:
		bool TxfDstActive;
		bool TxfIdxActive;
		bool TxfIdyActive;
		bool TxfQdxActive;
		bool TxfQdyActive;
		bool TxfAdxActive;
		bool TxfAdyActive;
		bool PupLsgActive;
		bool PupRsgActive;
		bool PupIsgActive;
		bool UpdQwhActive;
		int UpdQwhMin;
		int UpdQwhMax;
		bool TxfQhpActive;
		bool TxfQdpActive;
		bool TxfQflActive;
		bool TxfQfnActive;
		bool PupQsgActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfOptics)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint HDGGEOM = 2;
		static const uint CPTDST = 3;
		static const uint CPTIDX = 4;
		static const uint CPTIDY = 5;
		static const uint CPTQDX = 6;
		static const uint CPTQDY = 7;
		static const uint CPTADX = 8;
		static const uint CPTADY = 9;
		static const uint HDGVISLR = 10;
		static const uint CPTVWI = 11;
		static const uint CPTVHE = 12;
		static const uint CPTVHP = 13;
		static const uint CPTVFL = 14;
		static const uint CPTVFN = 15;
		static const uint CPTLSG = 16;
		static const uint CPTRSG = 17;
		static const uint HDGLWIR = 18;
		static const uint CPTIWI = 19;
		static const uint CPTIHE = 20;
		static const uint CPTIHP = 21;
		static const uint CPTIFL = 22;
		static const uint CPTIFN = 23;
		static const uint CPTISG = 24;
		static const uint HDGQCD = 25;
		static const uint CPTQWH = 26;
		static const uint CPTQHP = 27;
		static const uint CPTQDP = 28;
		static const uint CPTQFL = 29;
		static const uint CPTQFN = 30;
		static const uint CPTQSG = 31;

	public:
		Tag(const string& Cpt = "", const string& HdgGeom = "", const string& CptDst = "", const string& CptIdx = "", const string& CptIdy = "", const string& CptQdx = "", const string& CptQdy = "", const string& CptAdx = "", const string& CptAdy = "", const string& HdgVislr = "", const string& CptVwi = "", const string& CptVhe = "", const string& CptVhp = "", const string& CptVfl = "", const string& CptVfn = "", const string& CptLsg = "", const string& CptRsg = "", const string& HdgLwir = "", const string& CptIwi = "", const string& CptIhe = "", const string& CptIhp = "", const string& CptIfl = "", const string& CptIfn = "", const string& CptIsg = "", const string& HdgQcd = "", const string& CptQwh = "", const string& CptQhp = "", const string& CptQdp = "", const string& CptQfl = "", const string& CptQfn = "", const string& CptQsg = "");

	public:
		string Cpt;
		string HdgGeom;
		string CptDst;
		string CptIdx;
		string CptIdy;
		string CptQdx;
		string CptQdy;
		string CptAdx;
		string CptAdy;
		string HdgVislr;
		string CptVwi;
		string CptVhe;
		string CptVhp;
		string CptVfl;
		string CptVfn;
		string CptLsg;
		string CptRsg;
		string HdgLwir;
		string CptIwi;
		string CptIhe;
		string CptIhp;
		string CptIfl;
		string CptIfn;
		string CptIsg;
		string HdgQcd;
		string CptQwh;
		string CptQhp;
		string CptQdp;
		string CptQfl;
		string CptQfn;
		string CptQsg;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfOpticsData)
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
		* DpchAppDo (full: DpchAppIdecScfOpticsDo)
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
		* DpchEngData (full: DpchEngIdecScfOpticsData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPISG = 4;
		static const uint FEEDFPUPLSG = 5;
		static const uint FEEDFPUPQSG = 6;
		static const uint FEEDFPUPRSG = 7;
		static const uint STATAPP = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupIsg;
		Feed feedFPupLsg;
		Feed feedFPupQsg;
		Feed feedFPupRsg;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

