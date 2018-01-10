/**
  * \file CrdIdecTou.h
  * API code for job CrdIdecTou (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECTOU_H
#define CRDIDECTOU_H

#include "ApiIdec_blks.h"

#define VecVIdecTouDo CrdIdecTou::VecVDo
#define VecVIdecTouSge CrdIdecTou::VecVSge

#define ContInfIdecTou CrdIdecTou::ContInf
#define StatAppIdecTou CrdIdecTou::StatApp
#define StatShrIdecTou CrdIdecTou::StatShr
#define TagIdecTou CrdIdecTou::Tag

#define DpchAppIdecTouDo CrdIdecTou::DpchAppDo
#define DpchEngIdecTouData CrdIdecTou::DpchEngData

/**
  * CrdIdecTou
  */
namespace CrdIdecTou {
	/**
		* VecVDo (full: VecVIdecTouDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITCRDNEWCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecTouSge)
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
	  * ContInf (full: ContInfIdecTou)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXCRDTOU = 3;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxCrdTou = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxCrdTou;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecTou)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVREQITMODE = 1;
		static const uint LATENCY = 2;
		static const uint SHORTMENU = 3;
		static const uint WIDTHMENU = 4;
		static const uint INITDONEHEADBAR = 5;
		static const uint INITDONELIST = 6;
		static const uint INITDONEREC = 7;

	public:
		StatApp(const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneHeadbar = false, const bool initdoneList = false, const bool initdoneRec = false);

	public:
		uint ixIdecVReqitmode;
		usmallint latency;
		string shortMenu;
		uint widthMenu;
		bool initdoneHeadbar;
		bool initdoneList;
		bool initdoneRec;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecTou)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFDLGNEW = 1;
		static const uint SCRJREFHEADBAR = 2;
		static const uint SCRJREFLIST = 3;
		static const uint SCRJREFREC = 4;
		static const uint MSPCRD1AVAIL = 5;
		static const uint MITCRDNEWAVAIL = 6;

	public:
		StatShr(const string& scrJrefDlgnew = "", const string& scrJrefHeadbar = "", const string& scrJrefList = "", const string& scrJrefRec = "", const bool MspCrd1Avail = true, const bool MitCrdNewAvail = true);

	public:
		string scrJrefDlgnew;
		string scrJrefHeadbar;
		string scrJrefList;
		string scrJrefRec;
		bool MspCrd1Avail;
		bool MitCrdNewAvail;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecTou)
	  */
	class Tag : public Block {

	public:
		static const uint MITAPPABT = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MITCRDNEW = 3;

	public:
		Tag(const string& MitAppAbt = "", const string& MrlAppHlp = "", const string& MitCrdNew = "");

	public:
		string MitAppAbt;
		string MrlAppHlp;
		string MitCrdNew;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecTouDo)
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
		* DpchEngData (full: DpchEngIdecTouData)
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

