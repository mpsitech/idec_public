/**
  * \file PnlIdecScfConn.h
  * API code for job PnlIdecScfConn (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFCONN_H
#define PNLIDECSCFCONN_H

#include "ApiIdec_blks.h"

#define VecVIdecScfConnDo PnlIdecScfConn::VecVDo

#define ContIacIdecScfConn PnlIdecScfConn::ContIac
#define ContInfIdecScfConn PnlIdecScfConn::ContInf
#define StatAppIdecScfConn PnlIdecScfConn::StatApp
#define StatShrIdecScfConn PnlIdecScfConn::StatShr
#define TagIdecScfConn PnlIdecScfConn::Tag

#define DpchAppIdecScfConnData PnlIdecScfConn::DpchAppData
#define DpchAppIdecScfConnDo PnlIdecScfConn::DpchAppDo
#define DpchEngIdecScfConnData PnlIdecScfConn::DpchEngData
#define DpchEngIdecScfConnLive PnlIdecScfConn::DpchEngLive

/**
  * PnlIdecScfConn
  */
namespace PnlIdecScfConn {
	/**
		* VecVDo (full: VecVIdecScfConnDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfConn)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPTSP = 1;
		static const uint NUMFPUPPSP = 2;
		static const uint NUMFPUPVTY = 3;
		static const uint NUMFPUPLSN = 4;
		static const uint TXFLSN = 5;
		static const uint NUMFPUPLPA = 6;
		static const uint TXFLPA = 7;
		static const uint NUMFPUPLTR = 8;
		static const uint NUMFPUPRSN = 9;
		static const uint TXFRSN = 10;
		static const uint NUMFPUPRPA = 11;
		static const uint TXFRPA = 12;
		static const uint NUMFPUPRTR = 13;
		static const uint NUMFPUPQSP = 14;
		static const uint NUMFPUPFLD = 15;
		static const uint NUMFPUPSPT = 16;
		static const uint NUMFPUPSLD = 17;

	public:
		ContIac(const uint numFPupTsp = 1, const uint numFPupPsp = 1, const uint numFPupVty = 1, const uint numFPupLsn = 1, const string& TxfLsn = "", const uint numFPupLpa = 1, const string& TxfLpa = "", const uint numFPupLtr = 1, const uint numFPupRsn = 1, const string& TxfRsn = "", const uint numFPupRpa = 1, const string& TxfRpa = "", const uint numFPupRtr = 1, const uint numFPupQsp = 1, const uint numFPupFld = 1, const uint numFPupSpt = 1, const uint numFPupSld = 1);

	public:
		uint numFPupTsp;
		uint numFPupPsp;
		uint numFPupVty;
		uint numFPupLsn;
		string TxfLsn;
		uint numFPupLpa;
		string TxfLpa;
		uint numFPupLtr;
		uint numFPupRsn;
		string TxfRsn;
		uint numFPupRpa;
		string TxfRpa;
		uint numFPupRtr;
		uint numFPupQsp;
		uint numFPupFld;
		uint numFPupSpt;
		uint numFPupSld;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfConn)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTSCHGP1 = 2;
		static const uint TXTSCHGP2 = 3;
		static const uint TXTSCHSP1 = 4;
		static const uint NUMFCSISCHSP1 = 5;
		static const uint TXTSCHSP2 = 6;
		static const uint NUMFCSISCHSP2 = 7;
		static const uint TXTSCHSP3 = 8;
		static const uint NUMFCSISCHSP3 = 9;
		static const uint TXTSCHLD1 = 10;
		static const uint TXTSCHLD2 = 11;
		static const uint TXTSCHOCT = 12;
		static const uint TXTSCHOPS = 13;
		static const uint NUMFCSISCHOST = 14;
		static const uint TXTSCHHCT = 15;
		static const uint TXTSCHHPS = 16;
		static const uint NUMFCSISCHHST = 17;
		static const uint TXTSCHIPS = 18;
		static const uint NUMFCSISCHIST = 19;
		static const uint TXTISN = 20;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtSchGp1 = "", const string& TxtSchGp2 = "", const string& TxtSchSp1 = "", const uint numFCsiSchSp1 = 1, const string& TxtSchSp2 = "", const uint numFCsiSchSp2 = 1, const string& TxtSchSp3 = "", const uint numFCsiSchSp3 = 1, const string& TxtSchLd1 = "", const string& TxtSchLd2 = "", const string& TxtSchOct = "", const string& TxtSchOps = "", const uint numFCsiSchOst = 1, const string& TxtSchHct = "", const string& TxtSchHps = "", const uint numFCsiSchHst = 1, const string& TxtSchIps = "", const uint numFCsiSchIst = 1, const string& TxtIsn = "");

	public:
		bool ButMasterOn;
		string TxtSchGp1;
		string TxtSchGp2;
		string TxtSchSp1;
		uint numFCsiSchSp1;
		string TxtSchSp2;
		uint numFCsiSchSp2;
		string TxtSchSp3;
		uint numFCsiSchSp3;
		string TxtSchLd1;
		string TxtSchLd2;
		string TxtSchOct;
		string TxtSchOps;
		uint numFCsiSchOst;
		string TxtSchHct;
		string TxtSchHps;
		uint numFCsiSchHst;
		string TxtSchIps;
		uint numFCsiSchIst;
		string TxtIsn;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecScfConn)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint PUPLSNALT = 2;
		static const uint PUPLPAALT = 3;
		static const uint PUPRSNALT = 4;
		static const uint PUPRPAALT = 5;

	public:
		StatApp(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupLsnAlt = false, const bool PupLpaAlt = false, const bool PupRsnAlt = false, const bool PupRpaAlt = false);

	public:
		uint ixIdecVExpstate;
		bool PupLsnAlt;
		bool PupLpaAlt;
		bool PupRsnAlt;
		bool PupRpaAlt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecScfConn)
	  */
	class StatShr : public Block {

	public:
		static const uint TXFLSNVALID = 1;
		static const uint TXFLPAVALID = 2;
		static const uint TXFRSNVALID = 3;
		static const uint TXFRPAVALID = 4;
		static const uint PUPTSPACTIVE = 5;
		static const uint PUPPSPACTIVE = 6;
		static const uint PUPVTYACTIVE = 7;
		static const uint PUPLSNAVAIL = 8;
		static const uint PUPLSNACTIVE = 9;
		static const uint PUPLPAAVAIL = 10;
		static const uint PUPLPAACTIVE = 11;
		static const uint PUPLTRACTIVE = 12;
		static const uint PUPRSNAVAIL = 13;
		static const uint PUPRSNACTIVE = 14;
		static const uint PUPRPAAVAIL = 15;
		static const uint PUPRPAACTIVE = 16;
		static const uint PUPRTRACTIVE = 17;
		static const uint TXTISNACTIVE = 18;
		static const uint PUPQSPACTIVE = 19;
		static const uint PUPFLDACTIVE = 20;
		static const uint PUPSPTACTIVE = 21;

	public:
		StatShr(const bool TxfLsnValid = false, const bool TxfLpaValid = false, const bool TxfRsnValid = false, const bool TxfRpaValid = false, const bool PupTspActive = true, const bool PupPspActive = true, const bool PupVtyActive = true, const bool PupLsnAvail = true, const bool PupLsnActive = true, const bool PupLpaAvail = true, const bool PupLpaActive = true, const bool PupLtrActive = true, const bool PupRsnAvail = true, const bool PupRsnActive = true, const bool PupRpaAvail = true, const bool PupRpaActive = true, const bool PupRtrActive = true, const bool TxtIsnActive = true, const bool PupQspActive = true, const bool PupFldActive = true, const bool PupSptActive = true);

	public:
		bool TxfLsnValid;
		bool TxfLpaValid;
		bool TxfRsnValid;
		bool TxfRpaValid;
		bool PupTspActive;
		bool PupPspActive;
		bool PupVtyActive;
		bool PupLsnAvail;
		bool PupLsnActive;
		bool PupLpaAvail;
		bool PupLpaActive;
		bool PupLtrActive;
		bool PupRsnAvail;
		bool PupRsnActive;
		bool PupRpaAvail;
		bool PupRpaActive;
		bool PupRtrActive;
		bool TxtIsnActive;
		bool PupQspActive;
		bool PupFldActive;
		bool PupSptActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScfConn)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint CPTSCHALL = 2;
		static const uint CPTSCHLWI = 3;
		static const uint CPTTSP = 4;
		static const uint CPTPSP = 5;
		static const uint CPTVTY = 6;
		static const uint CPTLSN = 7;
		static const uint CPTLPA = 8;
		static const uint CPTLTR = 9;
		static const uint CPTRSN = 10;
		static const uint CPTRPA = 11;
		static const uint CPTRTR = 12;
		static const uint CPTISN = 13;
		static const uint CPTQSP = 14;
		static const uint CPTFLD = 15;
		static const uint CPTSPT = 16;
		static const uint CPTSLD = 17;

	public:
		Tag(const string& Cpt = "", const string& CptSchAll = "", const string& CptSchLwi = "", const string& CptTsp = "", const string& CptPsp = "", const string& CptVty = "", const string& CptLsn = "", const string& CptLpa = "", const string& CptLtr = "", const string& CptRsn = "", const string& CptRpa = "", const string& CptRtr = "", const string& CptIsn = "", const string& CptQsp = "", const string& CptFld = "", const string& CptSpt = "", const string& CptSld = "");

	public:
		string Cpt;
		string CptSchAll;
		string CptSchLwi;
		string CptTsp;
		string CptPsp;
		string CptVty;
		string CptLsn;
		string CptLpa;
		string CptLtr;
		string CptRsn;
		string CptRpa;
		string CptRtr;
		string CptIsn;
		string CptQsp;
		string CptFld;
		string CptSpt;
		string CptSld;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfConnData)
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
		* DpchAppDo (full: DpchAppIdecScfConnDo)
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
		* DpchEngData (full: DpchEngIdecScfConnData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSISCHHST = 4;
		static const uint FEEDFCSISCHIST = 5;
		static const uint FEEDFCSISCHOST = 6;
		static const uint FEEDFCSISCHSP1 = 7;
		static const uint FEEDFCSISCHSP2 = 8;
		static const uint FEEDFCSISCHSP3 = 9;
		static const uint FEEDFPUPFLD = 10;
		static const uint FEEDFPUPLPA = 11;
		static const uint FEEDFPUPLSN = 12;
		static const uint FEEDFPUPLTR = 13;
		static const uint FEEDFPUPPSP = 14;
		static const uint FEEDFPUPQSP = 15;
		static const uint FEEDFPUPRPA = 16;
		static const uint FEEDFPUPRSN = 17;
		static const uint FEEDFPUPRTR = 18;
		static const uint FEEDFPUPSLD = 19;
		static const uint FEEDFPUPSPT = 20;
		static const uint FEEDFPUPTSP = 21;
		static const uint FEEDFPUPVTY = 22;
		static const uint STATAPP = 23;
		static const uint STATSHR = 24;
		static const uint TAG = 25;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiSchHst;
		Feed feedFCsiSchIst;
		Feed feedFCsiSchOst;
		Feed feedFCsiSchSp1;
		Feed feedFCsiSchSp2;
		Feed feedFCsiSchSp3;
		Feed feedFPupFld;
		Feed feedFPupLpa;
		Feed feedFPupLsn;
		Feed feedFPupLtr;
		Feed feedFPupPsp;
		Feed feedFPupQsp;
		Feed feedFPupRpa;
		Feed feedFPupRsn;
		Feed feedFPupRtr;
		Feed feedFPupSld;
		Feed feedFPupSpt;
		Feed feedFPupTsp;
		Feed feedFPupVty;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngLive (full: DpchEngIdecScfConnLive)
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

