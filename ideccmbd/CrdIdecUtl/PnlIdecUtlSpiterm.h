/**
  * \file PnlIdecUtlSpiterm.h
  * job handler for job PnlIdecUtlSpiterm (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUTLSPITERM_H
#define PNLIDECUTLSPITERM_H

// IP custInclude --- INSERT

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
class PnlIdecUtlSpiterm : public JobIdec {

public:
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

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
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

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
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

		static void fillFeed(Feed& feed);
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
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
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
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecUtlSpiterm)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecUtlSpitermData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;

	public:
		DpchAppData();

	public:
		ContIac contiac;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUtlSpitermDo)
		*/
	class DpchAppDo : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint IXVDO = 2;

	public:
		DpchAppDo();

	public:
		uint ixVDo;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngData (full: DpchEngIdecUtlSpitermData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPOCM = 4;
		static const uint FEEDFPUPPCM = 5;
		static const uint FEEDFPUPTRG = 6;
		static const uint FEEDFRBUOET = 7;
		static const uint FEEDFRBUPET = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;
		static const uint ALL = 11;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupOcm = NULL, Feed* feedFPupPcm = NULL, Feed* feedFPupTrg = NULL, Feed* feedFRbuOet = NULL, Feed* feedFRbuPet = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupOcm;
		Feed feedFPupPcm;
		Feed feedFPupTrg;
		Feed feedFRbuOet;
		Feed feedFRbuPet;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	/**
		* DpchEngLive (full: DpchEngIdecUtlSpitermLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint ALL = 3;

	public:
		DpchEngLive(const ubigint jref = 0, ContInf* continf = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalPupTrgActive(DbsIdec* dbsidec);
	bool evalButCctActive(DbsIdec* dbsidec);
	bool evalButDctActive(DbsIdec* dbsidec);
	bool evalPupOcmAvail(DbsIdec* dbsidec);
	bool evalButOcaActive(DbsIdec* dbsidec);
	bool evalTxfOcsAvail(DbsIdec* dbsidec);
	bool evalTxfOhsAvail(DbsIdec* dbsidec);
	bool evalTxfOfnAvail(DbsIdec* dbsidec);
	bool evalButOsmActive(DbsIdec* dbsidec);
	bool evalRbuPetActive(DbsIdec* dbsidec);
	bool evalPupPcmAvail(DbsIdec* dbsidec);
	bool evalPupPcmActive(DbsIdec* dbsidec);
	bool evalButPcaActive(DbsIdec* dbsidec);
	bool evalTxfPcsAvail(DbsIdec* dbsidec);
	bool evalTxfPcsActive(DbsIdec* dbsidec);
	bool evalTxfPhsAvail(DbsIdec* dbsidec);
	bool evalTxfPhsActive(DbsIdec* dbsidec);
	bool evalTxfPfnAvail(DbsIdec* dbsidec);
	bool evalTxfPfnActive(DbsIdec* dbsidec);
	bool evalSldPinActive(DbsIdec* dbsidec);
	bool evalButPrnActive(DbsIdec* dbsidec);
	bool evalButPstActive(DbsIdec* dbsidec);

public:
	PnlIdecUtlSpiterm(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecUtlSpiterm();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupOcm;
	Feed feedFPupPcm;
	Feed feedFPupTrg;
	Feed feedFRbuOet;
	Feed feedFRbuPet;

	// IP custVar --- IBEGIN
	string logfolder;

	vector<string> outlog;
	vector<string> inlog;

	UntIdhw* unt;

	vector<Cmd*> newcmds;
	vector<ExtcallIdec*> newextcalls;

	map<uint,Cmd*> ocmds;
	map<uint,ExtcallIdec*> oextcalls;

	map<uint,Cmd*> pcmds;
	map<uint,ExtcallIdec*> pextcalls;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	void changeTarget(set<uint>& moditems);

	void refreshLive(DbsIdec* dbsidec, set<uint>& moditems);

	void appendToLogfile(const string& filename, vector<string> ss);
	void appendToOutlog(Cmd* cmd);
	void appendToInlog(Cmd* cmd);

	void parseCmdseq(vector<string>& ss, vector<Cmd*>& cmds);
	void parseHexseqs(vector<string>& ss, vector<Cmd*>& cmds);
	void parseFile(const string& path, vector<Cmd*>& cmds);

	uint getCmdix(const string& cmdsref);
	string getCmdsref(const uint cmdix);

	static void callbackIdhw(const ubigint uref, const ubigint cref, void* arg);
	// IP cust --- IEND

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeCtd(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeCtd(DbsIdec* dbsidec);
	uint enterSgePrdexec(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrdexec(DbsIdec* dbsidec);
	uint enterSgeErr(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeErr(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCctClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButDctClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButOcaClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButOsmClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPcaClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPrnClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPstClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDevidhw(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif


