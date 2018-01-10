/**
  * \file CrdIdecScf.h
  * API code for job CrdIdecScf (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECSCF_H
#define CRDIDECSCF_H

#include "ApiIdec_blks.h"

#define VecVIdecScfDo CrdIdecScf::VecVDo
#define VecVIdecScfSge CrdIdecScf::VecVSge

#define ContInfIdecScf CrdIdecScf::ContInf
#define StatAppIdecScf CrdIdecScf::StatApp
#define StatShrIdecScf CrdIdecScf::StatShr
#define TagIdecScf CrdIdecScf::Tag

#define DpchAppIdecScfDo CrdIdecScf::DpchAppDo
#define DpchEngIdecScfData CrdIdecScf::DpchEngData

/**
  * CrdIdecScf
  */
namespace CrdIdecScf {
	/**
		* VecVDo (full: VecVIdecScfDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecScfSge)
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
	  * ContInf (full: ContInfIdecScf)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "");

	public:
		uint numFSge;
		string MrlAppHlp;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppIdecScf)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVREQITMODE = 1;
		static const uint LATENCY = 2;
		static const uint SHORTMENU = 3;
		static const uint WIDTHMENU = 4;
		static const uint INITDONECONN = 5;
		static const uint INITDONESTATUS = 6;
		static const uint INITDONEMECH = 7;
		static const uint INITDONEOPTICS = 8;
		static const uint INITDONETRIGGER = 9;
		static const uint INITDONELWIR = 10;
		static const uint INITDONEQCD = 11;
		static const uint INITDONERECORD = 12;
		static const uint INITDONEHEADBAR = 13;

	public:
		StatApp(const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneConn = false, const bool initdoneStatus = false, const bool initdoneMech = false, const bool initdoneOptics = false, const bool initdoneTrigger = false, const bool initdoneLwir = false, const bool initdoneQcd = false, const bool initdoneRecord = false, const bool initdoneHeadbar = false);

	public:
		uint ixIdecVReqitmode;
		usmallint latency;
		string shortMenu;
		uint widthMenu;
		bool initdoneConn;
		bool initdoneStatus;
		bool initdoneMech;
		bool initdoneOptics;
		bool initdoneTrigger;
		bool initdoneLwir;
		bool initdoneQcd;
		bool initdoneRecord;
		bool initdoneHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecScf)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFCONN = 1;
		static const uint SCRJREFSTATUS = 2;
		static const uint SCRJREFMECH = 3;
		static const uint SCRJREFOPTICS = 4;
		static const uint SCRJREFTRIGGER = 5;
		static const uint SCRJREFLWIR = 6;
		static const uint SCRJREFQCD = 7;
		static const uint SCRJREFRECORD = 8;
		static const uint SCRJREFHEADBAR = 9;

	public:
		StatShr(const string& scrJrefConn = "", const string& scrJrefStatus = "", const string& scrJrefMech = "", const string& scrJrefOptics = "", const string& scrJrefTrigger = "", const string& scrJrefLwir = "", const string& scrJrefQcd = "", const string& scrJrefRecord = "", const string& scrJrefHeadbar = "");

	public:
		string scrJrefConn;
		string scrJrefStatus;
		string scrJrefMech;
		string scrJrefOptics;
		string scrJrefTrigger;
		string scrJrefLwir;
		string scrJrefQcd;
		string scrJrefRecord;
		string scrJrefHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecScf)
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
		* DpchAppDo (full: DpchAppIdecScfDo)
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
		* DpchEngData (full: DpchEngIdecScfData)
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

