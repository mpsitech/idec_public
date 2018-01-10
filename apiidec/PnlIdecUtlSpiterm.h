/**
  * \file PnlIdecUtlSpiterm.h
  * API code for job PnlIdecUtlSpiterm (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUTLSPITERM_H
#define PNLIDECUTLSPITERM_H

#include "ApiIdec_blks.h"

#define VecVIdecUtlSpitermDo PnlIdecUtlSpiterm::VecVDo
#define VecVIdecUtlSpitermOcxenttype PnlIdecUtlSpiterm::VecVOcxenttype
#define VecVIdecUtlSpitermPcxenttype PnlIdecUtlSpiterm::VecVPcxenttype
#define VecVIdecUtlSpitermSge PnlIdecUtlSpiterm::VecVSge

#define ContIacIdecUtlSpiterm PnlIdecUtlSpiterm::ContIac
#define ContInfIdecUtlSpiterm PnlIdecUtlSpiterm::ContInf
#define StatShrIdecUtlSpiterm PnlIdecUtlSpiterm::StatShr
#define TagIdecUtlSpiterm PnlIdecUtlSpiterm::Tag

#define DpchAppIdecUtlSpitermData PnlIdecUtlSpiterm::DpchAppData
#define DpchAppIdecUtlSpitermDo PnlIdecUtlSpiterm::DpchAppDo
#define DpchEngIdecUtlSpitermData PnlIdecUtlSpiterm::DpchEngData
#define DpchEngIdecUtlSpitermLive PnlIdecUtlSpiterm::DpchEngLive

/**
  * PnlIdecUtlSpiterm
  */
namespace PnlIdecUtlSpiterm {
	/**
		* VecVDo (full: VecVIdecUtlSpitermDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTCCTCLICK = 3;
		static const uint BUTDCTCLICK = 4;
		static const uint BUTOCACLICK = 5;
		static const uint BUTOSMCLICK = 6;
		static const uint BUTPCACLICK = 7;
		static const uint BUTPRNCLICK = 8;
		static const uint BUTPSTCLICK = 9;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVOcxenttype (full: VecVIdecUtlSpitermOcxenttype)
		*/
	class VecVOcxenttype {

	public:
		static const uint CSQ = 1;
		static const uint HSQ = 2;
		static const uint FILE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVPcxenttype (full: VecVIdecUtlSpitermPcxenttype)
		*/
	class VecVPcxenttype {

	public:
		static const uint CSQ = 1;
		static const uint HSQ = 2;
		static const uint FILE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecUtlSpitermSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint CTD = 2;
		static const uint PRDEXEC = 3;
		static const uint ERR = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUtlSpiterm)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPTRG = 1;
		static const uint CHKISD = 2;
		static const uint NUMFRBUOET = 3;
		static const uint NUMFPUPOCM = 4;
		static const uint TXFOCS = 5;
		static const uint TXFOHS = 6;
		static const uint TXFOFN = 7;
		static const uint NUMFRBUPET = 8;
		static const uint NUMFPUPPCM = 9;
		static const uint TXFPCS = 10;
		static const uint TXFPHS = 11;
		static const uint TXFPFN = 12;
		static const uint SLDPIN = 13;

	public:
		ContIac(const uint numFPupTrg = 1, const bool ChkIsd = false, const uint numFRbuOet = 1, const uint numFPupOcm = 1, const string& TxfOcs = "", const string& TxfOhs = "", const string& TxfOfn = "", const uint numFRbuPet = 1, const uint numFPupPcm = 1, const string& TxfPcs = "", const string& TxfPhs = "", const string& TxfPfn = "", const double SldPin = 0.0);

	public:
		uint numFPupTrg;
		bool ChkIsd;
		uint numFRbuOet;
		uint numFPupOcm;
		string TxfOcs;
		string TxfOhs;
		string TxfOfn;
		uint numFRbuPet;
		uint numFPupPcm;
		string TxfPcs;
		string TxfPhs;
		string TxfPfn;
		double SldPin;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUtlSpiterm)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTSTE = 1;
		static const uint TXTOLG = 2;
		static const uint TXTOLF = 3;
		static const uint TXTILG = 4;
		static const uint TXTILF = 5;

	public:
		ContInf(const string& TxtSte = "", const string& TxtOlg = "", const string& TxtOlf = "", const string& TxtIlg = "", const string& TxtIlf = "");

	public:
		string TxtSte;
		string TxtOlg;
		string TxtOlf;
		string TxtIlg;
		string TxtIlf;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecUtlSpiterm)
	  */
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint PUPTRGACTIVE = 2;
		static const uint BUTCCTACTIVE = 3;
		static const uint BUTDCTACTIVE = 4;
		static const uint PUPOCMAVAIL = 5;
		static const uint BUTOCAACTIVE = 6;
		static const uint TXFOCSAVAIL = 7;
		static const uint TXFOHSAVAIL = 8;
		static const uint TXFOFNAVAIL = 9;
		static const uint BUTOSMACTIVE = 10;
		static const uint RBUPETACTIVE = 11;
		static const uint PUPPCMAVAIL = 12;
		static const uint PUPPCMACTIVE = 13;
		static const uint BUTPCAACTIVE = 14;
		static const uint TXFPCSAVAIL = 15;
		static const uint TXFPCSACTIVE = 16;
		static const uint TXFPHSAVAIL = 17;
		static const uint TXFPHSACTIVE = 18;
		static const uint TXFPFNAVAIL = 19;
		static const uint TXFPFNACTIVE = 20;
		static const uint SLDPINACTIVE = 21;
		static const uint SLDPINMIN = 22;
		static const uint SLDPINMAX = 23;
		static const uint SLDPINRAST = 24;
		static const uint BUTPRNACTIVE = 25;
		static const uint BUTPSTACTIVE = 26;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupTrgActive = true, const bool ButCctActive = true, const bool ButDctActive = true, const bool PupOcmAvail = true, const bool ButOcaActive = true, const bool TxfOcsAvail = true, const bool TxfOhsAvail = true, const bool TxfOfnAvail = true, const bool ButOsmActive = true, const bool RbuPetActive = true, const bool PupPcmAvail = true, const bool PupPcmActive = true, const bool ButPcaActive = true, const bool TxfPcsAvail = true, const bool TxfPcsActive = true, const bool TxfPhsAvail = true, const bool TxfPhsActive = true, const bool TxfPfnAvail = true, const bool TxfPfnActive = true, const bool SldPinActive = true, const double SldPinMin = 0.1, const double SldPinMax = 10000, const double SldPinRast = 10, const bool ButPrnActive = true, const bool ButPstActive = true);

	public:
		uint ixIdecVExpstate;
		bool PupTrgActive;
		bool ButCctActive;
		bool ButDctActive;
		bool PupOcmAvail;
		bool ButOcaActive;
		bool TxfOcsAvail;
		bool TxfOhsAvail;
		bool TxfOfnAvail;
		bool ButOsmActive;
		bool RbuPetActive;
		bool PupPcmAvail;
		bool PupPcmActive;
		bool ButPcaActive;
		bool TxfPcsAvail;
		bool TxfPcsActive;
		bool TxfPhsAvail;
		bool TxfPhsActive;
		bool TxfPfnAvail;
		bool TxfPfnActive;
		bool SldPinActive;
		double SldPinMin;
		double SldPinMax;
		double SldPinRast;
		bool ButPrnActive;
		bool ButPstActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUtlSpiterm)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint HDGCON = 2;
		static const uint CPTTRG = 3;
		static const uint CPTSTE = 4;
		static const uint BUTCCT = 5;
		static const uint BUTDCT = 6;
		static const uint HDGDOU = 7;
		static const uint CPTOLF = 8;
		static const uint HDGDIN = 9;
		static const uint CPTILF = 10;
		static const uint CPTISD = 11;
		static const uint HDGOCX = 12;
		static const uint CPTOET = 13;
		static const uint CPTOCM = 14;
		static const uint BUTOCA = 15;
		static const uint CPTOCS = 16;
		static const uint CPTOHS = 17;
		static const uint CPTOFN = 18;
		static const uint BUTOSM = 19;
		static const uint HDGPCX = 20;
		static const uint CPTPET = 21;
		static const uint CPTPCM = 22;
		static const uint BUTPCA = 23;
		static const uint CPTPCS = 24;
		static const uint CPTPHS = 25;
		static const uint CPTPFN = 26;
		static const uint CPTPIN = 27;
		static const uint BUTPRN = 28;
		static const uint BUTPST = 29;

	public:
		Tag(const string& Cpt = "", const string& HdgCon = "", const string& CptTrg = "", const string& CptSte = "", const string& ButCct = "", const string& ButDct = "", const string& HdgDou = "", const string& CptOlf = "", const string& HdgDin = "", const string& CptIlf = "", const string& CptIsd = "", const string& HdgOcx = "", const string& CptOet = "", const string& CptOcm = "", const string& ButOca = "", const string& CptOcs = "", const string& CptOhs = "", const string& CptOfn = "", const string& ButOsm = "", const string& HdgPcx = "", const string& CptPet = "", const string& CptPcm = "", const string& ButPca = "", const string& CptPcs = "", const string& CptPhs = "", const string& CptPfn = "", const string& CptPin = "", const string& ButPrn = "", const string& ButPst = "");

	public:
		string Cpt;
		string HdgCon;
		string CptTrg;
		string CptSte;
		string ButCct;
		string ButDct;
		string HdgDou;
		string CptOlf;
		string HdgDin;
		string CptIlf;
		string CptIsd;
		string HdgOcx;
		string CptOet;
		string CptOcm;
		string ButOca;
		string CptOcs;
		string CptOhs;
		string CptOfn;
		string ButOsm;
		string HdgPcx;
		string CptPet;
		string CptPcm;
		string ButPca;
		string CptPcs;
		string CptPhs;
		string CptPfn;
		string CptPin;
		string ButPrn;
		string ButPst;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppIdecUtlSpitermData)
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
		* DpchAppDo (full: DpchAppIdecUtlSpitermDo)
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
		* DpchEngData (full: DpchEngIdecUtlSpitermData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPOCM = 4;
		static const uint FEEDFPUPPCM = 5;
		static const uint FEEDFPUPTRG = 6;
		static const uint FEEDFRBUOET = 7;
		static const uint FEEDFRBUPET = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupOcm;
		Feed feedFPupPcm;
		Feed feedFPupTrg;
		Feed feedFRbuOet;
		Feed feedFRbuPet;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngLive (full: DpchEngIdecUtlSpitermLive)
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

