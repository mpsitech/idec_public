/**
  * \file CrdIdecUsr.h
  * API code for job CrdIdecUsr (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECUSR_H
#define CRDIDECUSR_H

#include "ApiIdec_blks.h"

#define VecVIdecUsrDo CrdIdecUsr::VecVDo
#define VecVIdecUsrSge CrdIdecUsr::VecVSge

#define ContInfIdecUsr CrdIdecUsr::ContInf
#define StatAppIdecUsr CrdIdecUsr::StatApp
#define StatShrIdecUsr CrdIdecUsr::StatShr
#define TagIdecUsr CrdIdecUsr::Tag

#define DpchAppIdecUsrDo CrdIdecUsr::DpchAppDo
#define DpchEngIdecUsrData CrdIdecUsr::DpchEngData

/**
  * CrdIdecUsr
  */
namespace CrdIdecUsr {
	/**
		* VecVDo (full: VecVIdecUsrDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecUsrSge)
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
	  * ContInf (full: ContInfIdecUsr)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXCRDUSR = 3;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxCrdUsr = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxCrdUsr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecUsr)
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
	  * StatShr (full: StatShrIdecUsr)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFHEADBAR = 1;
		static const uint SCRJREFLIST = 2;
		static const uint SCRJREFREC = 3;

	public:
		StatShr(const string& scrJrefHeadbar = "", const string& scrJrefList = "", const string& scrJrefRec = "");

	public:
		string scrJrefHeadbar;
		string scrJrefList;
		string scrJrefRec;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUsr)
	  */
	class Tag : public Block {

	public:
		static const uint MITAPPABT = 1;
		static const uint MRLAPPHLP = 2;

	public:
		Tag(const string& MitAppAbt = "", const string& MrlAppHlp = "");

	public:
		string MitAppAbt;
		string MrlAppHlp;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUsrDo)
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
		* DpchEngData (full: DpchEngIdecUsrData)
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

