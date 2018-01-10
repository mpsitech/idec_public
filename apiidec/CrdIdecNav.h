/**
  * \file CrdIdecNav.h
  * API code for job CrdIdecNav (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECNAV_H
#define CRDIDECNAV_H

#include "ApiIdec_blks.h"

#define VecVIdecNavDo CrdIdecNav::VecVDo
#define VecVIdecNavSge CrdIdecNav::VecVSge

#define ContInfIdecNav CrdIdecNav::ContInf
#define StatAppIdecNav CrdIdecNav::StatApp
#define StatShrIdecNav CrdIdecNav::StatShr
#define TagIdecNav CrdIdecNav::Tag

#define DpchAppIdecNavDo CrdIdecNav::DpchAppDo
#define DpchEngIdecNavData CrdIdecNav::DpchEngData

/**
  * CrdIdecNav
  */
namespace CrdIdecNav {
	/**
		* VecVDo (full: VecVIdecNavDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITSESTRMCLICK = 3;
		static const uint MITCRDUSGCLICK = 4;
		static const uint MITCRDUSRCLICK = 5;
		static const uint MITCRDSCFCLICK = 6;
		static const uint MITCRDUTLCLICK = 7;
		static const uint MITCRDMISCLICK = 8;
		static const uint MITCRDTOUCLICK = 9;
		static const uint MITCRDIAQCLICK = 10;
		static const uint MITCRDAD1CLICK = 11;
		static const uint MITCRDFILCLICK = 12;
		static const uint MITAPPLOICLICK = 13;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecNavSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRIDECABT = 2;
		static const uint CLOSE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecNav)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXSESSES1 = 3;
		static const uint MTXSESSES2 = 4;
		static const uint MTXSESSES3 = 5;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxSesSes1 = "", const string& MtxSesSes2 = "", const string& MtxSesSes3 = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxSesSes1;
		string MtxSesSes2;
		string MtxSesSes3;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecNav)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVREQITMODE = 1;
		static const uint LATENCY = 2;
		static const uint SHORTMENU = 3;
		static const uint WIDTHMENU = 4;
		static const uint INITDONEHEADBAR = 5;
		static const uint INITDONEPRE = 6;
		static const uint INITDONEMAINT = 7;
		static const uint INITDONEOPR = 8;

	public:
		StatApp(const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneHeadbar = false, const bool initdonePre = false, const bool initdoneMaint = false, const bool initdoneOpr = false);

	public:
		uint ixIdecVReqitmode;
		usmallint latency;
		string shortMenu;
		uint widthMenu;
		bool initdoneHeadbar;
		bool initdonePre;
		bool initdoneMaint;
		bool initdoneOpr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecNav)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFDLGLOAINI = 1;
		static const uint SCRJREFHEADBAR = 2;
		static const uint SCRJREFPRE = 3;
		static const uint PNLPREAVAIL = 4;
		static const uint SCRJREFMAINT = 5;
		static const uint PNLMAINTAVAIL = 6;
		static const uint SCRJREFOPR = 7;
		static const uint PNLOPRAVAIL = 8;
		static const uint MSPCRD1AVAIL = 9;
		static const uint MITCRDUSGAVAIL = 10;
		static const uint MITCRDUSRAVAIL = 11;
		static const uint MITCRDSCFAVAIL = 12;
		static const uint MITCRDUTLAVAIL = 13;
		static const uint MSPCRD2AVAIL = 14;
		static const uint MITCRDMISAVAIL = 15;
		static const uint MITCRDTOUAVAIL = 16;
		static const uint MITCRDIAQAVAIL = 17;
		static const uint MITCRDIAQACTIVE = 18;
		static const uint MITCRDAD1AVAIL = 19;
		static const uint MITCRDAD1ACTIVE = 20;
		static const uint MITCRDFILAVAIL = 21;
		static const uint MSPAPP2AVAIL = 22;
		static const uint MITAPPLOIAVAIL = 23;

	public:
		StatShr(const string& scrJrefDlgloaini = "", const string& scrJrefHeadbar = "", const string& scrJrefPre = "", const bool pnlpreAvail = false, const string& scrJrefMaint = "", const bool pnlmaintAvail = false, const string& scrJrefOpr = "", const bool pnloprAvail = false, const bool MspCrd1Avail = true, const bool MitCrdUsgAvail = true, const bool MitCrdUsrAvail = true, const bool MitCrdScfAvail = true, const bool MitCrdUtlAvail = true, const bool MspCrd2Avail = true, const bool MitCrdMisAvail = true, const bool MitCrdTouAvail = true, const bool MitCrdIaqAvail = true, const bool MitCrdIaqActive = true, const bool MitCrdAd1Avail = true, const bool MitCrdAd1Active = true, const bool MitCrdFilAvail = true, const bool MspApp2Avail = true, const bool MitAppLoiAvail = true);

	public:
		string scrJrefDlgloaini;
		string scrJrefHeadbar;
		string scrJrefPre;
		bool pnlpreAvail;
		string scrJrefMaint;
		bool pnlmaintAvail;
		string scrJrefOpr;
		bool pnloprAvail;
		bool MspCrd1Avail;
		bool MitCrdUsgAvail;
		bool MitCrdUsrAvail;
		bool MitCrdScfAvail;
		bool MitCrdUtlAvail;
		bool MspCrd2Avail;
		bool MitCrdMisAvail;
		bool MitCrdTouAvail;
		bool MitCrdIaqAvail;
		bool MitCrdIaqActive;
		bool MitCrdAd1Avail;
		bool MitCrdAd1Active;
		bool MitCrdFilAvail;
		bool MspApp2Avail;
		bool MitAppLoiAvail;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecNav)
	  */
	class Tag : public Block {

	public:
		static const uint MITAPPABT = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MITSESTRM = 3;
		static const uint MITCRDUSG = 4;
		static const uint MITCRDUSR = 5;
		static const uint MITCRDSCF = 6;
		static const uint MITCRDUTL = 7;
		static const uint MITCRDMIS = 8;
		static const uint MITCRDTOU = 9;
		static const uint MITCRDIAQ = 10;
		static const uint MITCRDAD1 = 11;
		static const uint MITCRDFIL = 12;
		static const uint MITAPPLOI = 13;

	public:
		Tag(const string& MitAppAbt = "", const string& MrlAppHlp = "", const string& MitSesTrm = "", const string& MitCrdUsg = "", const string& MitCrdUsr = "", const string& MitCrdScf = "", const string& MitCrdUtl = "", const string& MitCrdMis = "", const string& MitCrdTou = "", const string& MitCrdIaq = "", const string& MitCrdAd1 = "", const string& MitCrdFil = "", const string& MitAppLoi = "");

	public:
		string MitAppAbt;
		string MrlAppHlp;
		string MitSesTrm;
		string MitCrdUsg;
		string MitCrdUsr;
		string MitCrdScf;
		string MitCrdUtl;
		string MitCrdMis;
		string MitCrdTou;
		string MitCrdIaq;
		string MitCrdAd1;
		string MitCrdFil;
		string MitAppLoi;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecNavDo)
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
		* DpchEngData (full: DpchEngIdecNavData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint FEEDFSGE = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;

	public:
		DpchEngData();

	public:
		ContInf continf;
		Feed feedFSge;
		StatApp statapp;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

