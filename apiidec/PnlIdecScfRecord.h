/**
  * \file PnlIdecScfRecord.h
  * API code for job PnlIdecScfRecord (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFRECORD_H
#define PNLIDECSCFRECORD_H

#include "ApiIdec_blks.h"

#define VecVIdecScfRecordDo PnlIdecScfRecord::VecVDo

#define ContIacIdecScfRecord PnlIdecScfRecord::ContIac
#define ContInfIdecScfRecord PnlIdecScfRecord::ContInf
#define StatAppIdecScfRecord PnlIdecScfRecord::StatApp
#define StatShrIdecScfRecord PnlIdecScfRecord::StatShr
#define TagIdecScfRecord PnlIdecScfRecord::Tag

#define DpchAppIdecScfRecordData PnlIdecScfRecord::DpchAppData
#define DpchAppIdecScfRecordDo PnlIdecScfRecord::DpchAppDo
#define DpchEngIdecScfRecordData PnlIdecScfRecord::DpchEngData

/**
  * PnlIdecScfRecord
  */
namespace PnlIdecScfRecord {
	/**
		* VecVDo (full: VecVIdecScfRecordDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfRecord)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPFLR = 1;
		static const uint CHKFLG = 2;
		static const uint NUMFPUPFRR = 3;
		static const uint CHKFRG = 4;
		static const uint NUMFPUPFIR = 5;
		static const uint CHKFQC = 6;
		static const uint CHKFST = 7;
		static const uint SLDVFR = 8;
		static const uint NUMFPUPVLR = 9;
		static const uint CHKVLG = 10;
		static const uint NUMFPUPVRR = 11;
		static const uint CHKVRG = 12;
		static const uint NUMFPUPVIR = 13;
		static const uint CHKVQC = 14;
		static const uint CHKVST = 15;
		static const uint NUMFPUPOWR = 16;

	public:
		ContIac(const uint numFPupFlr = 1, const bool ChkFlg = false, const uint numFPupFrr = 1, const bool ChkFrg = false, const uint numFPupFir = 1, const bool ChkFqc = false, const bool ChkFst = false, const double SldVfr = 0.0, const uint numFPupVlr = 1, const bool ChkVlg = false, const uint numFPupVrr = 1, const bool ChkVrg = false, const uint numFPupVir = 1, const bool ChkVqc = false, const bool ChkVst = false, const uint numFPupOwr = 1);

	public:
		uint numFPupFlr;
		bool ChkFlg;
		uint numFPupFrr;
		bool ChkFrg;
		uint numFPupFir;
		bool ChkFqc;
		bool ChkFst;
		double SldVfr;
		uint numFPupVlr;
		bool ChkVlg;
		uint numFPupVrr;
		bool ChkVrg;
		uint numFPupVir;
		bool ChkVqc;
		bool ChkVst;
		uint numFPupOwr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfRecord)
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
	  * StatApp (full: StatAppIdecScfRecord)
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
	  * StatShr (full: StatShrIdecScfRecord)
	  */
	class StatShr : public Block {

	public:
		static const uint PUPFLRACTIVE = 1;
		static const uint CHKFLGACTIVE = 2;
		static const uint PUPFRRACTIVE = 3;
		static const uint CHKFRGACTIVE = 4;
		static const uint PUPFIRACTIVE = 5;
		static const uint CHKFQCACTIVE = 6;
		static const uint CHKFSTACTIVE = 7;
		static const uint SLDVFRACTIVE = 8;
		static const uint SLDVFRMIN = 9;
		static const uint SLDVFRMAX = 10;
		static const uint PUPVLRACTIVE = 11;
		static const uint CHKVLGACTIVE = 12;
		static const uint PUPVRRACTIVE = 13;
		static const uint CHKVRGACTIVE = 14;
		static const uint PUPVIRACTIVE = 15;
		static const uint CHKVQCACTIVE = 16;
		static const uint CHKVSTACTIVE = 17;
		static const uint PUPOWRACTIVE = 18;

	public:
		StatShr(const bool PupFlrActive = true, const bool ChkFlgActive = true, const bool PupFrrActive = true, const bool ChkFrgActive = true, const bool PupFirActive = true, const bool ChkFqcActive = true, const bool ChkFstActive = true, const bool SldVfrActive = true, const double SldVfrMin = 1.0, const double SldVfrMax = 10.0, const bool PupVlrActive = true, const bool ChkVlgActive = true, const bool PupVrrActive = true, const bool ChkVrgActive = true, const bool PupVirActive = true, const bool ChkVqcActive = true, const bool ChkVstActive = true, const bool PupOwrActive = true);

	public:
		bool PupFlrActive;
		bool ChkFlgActive;
		bool PupFrrActive;
		bool ChkFrgActive;
		bool PupFirActive;
		bool ChkFqcActive;
		bool ChkFstActive;
		bool SldVfrActive;
		double SldVfrMin;
		double SldVfrMax;
		bool PupVlrActive;
		bool ChkVlgActive;
		bool PupVrrActive;
		bool ChkVrgActive;
		bool PupVirActive;
		bool ChkVqcActive;
		bool ChkVstActive;
		bool PupOwrActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfRecord)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint HDGFRAME = 2;
		static const uint CPTFLR = 3;
		static const uint CPTFLG = 4;
		static const uint CPTFRR = 5;
		static const uint CPTFRG = 6;
		static const uint CPTFIR = 7;
		static const uint CPTFQC = 8;
		static const uint CPTFST = 9;
		static const uint HDGVIDEO = 10;
		static const uint CPTVFR = 11;
		static const uint CPTVLR = 12;
		static const uint CPTVLG = 13;
		static const uint CPTVRR = 14;
		static const uint CPTVRG = 15;
		static const uint CPTVIR = 16;
		static const uint CPTVQC = 17;
		static const uint CPTVST = 18;
		static const uint CPTOWR = 19;

	public:
		Tag(const string& Cpt = "", const string& HdgFrame = "", const string& CptFlr = "", const string& CptFlg = "", const string& CptFrr = "", const string& CptFrg = "", const string& CptFir = "", const string& CptFqc = "", const string& CptFst = "", const string& HdgVideo = "", const string& CptVfr = "", const string& CptVlr = "", const string& CptVlg = "", const string& CptVrr = "", const string& CptVrg = "", const string& CptVir = "", const string& CptVqc = "", const string& CptVst = "", const string& CptOwr = "");

	public:
		string Cpt;
		string HdgFrame;
		string CptFlr;
		string CptFlg;
		string CptFrr;
		string CptFrg;
		string CptFir;
		string CptFqc;
		string CptFst;
		string HdgVideo;
		string CptVfr;
		string CptVlr;
		string CptVlg;
		string CptVrr;
		string CptVrg;
		string CptVir;
		string CptVqc;
		string CptVst;
		string CptOwr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfRecordData)
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
		* DpchAppDo (full: DpchAppIdecScfRecordDo)
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
		* DpchEngData (full: DpchEngIdecScfRecordData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPFIR = 4;
		static const uint FEEDFPUPFLR = 5;
		static const uint FEEDFPUPFRR = 6;
		static const uint FEEDFPUPOWR = 7;
		static const uint FEEDFPUPVIR = 8;
		static const uint FEEDFPUPVLR = 9;
		static const uint FEEDFPUPVRR = 10;
		static const uint STATAPP = 11;
		static const uint STATSHR = 12;
		static const uint TAG = 13;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupFir;
		Feed feedFPupFlr;
		Feed feedFPupFrr;
		Feed feedFPupOwr;
		Feed feedFPupVir;
		Feed feedFPupVlr;
		Feed feedFPupVrr;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

