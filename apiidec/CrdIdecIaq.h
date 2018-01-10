/**
  * \file CrdIdecIaq.h
  * API code for job CrdIdecIaq (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECIAQ_H
#define CRDIDECIAQ_H

#include "ApiIdec_blks.h"

#define VecVIdecIaqDo CrdIdecIaq::VecVDo
#define VecVIdecIaqSge CrdIdecIaq::VecVSge

#define ContInfIdecIaq CrdIdecIaq::ContInf
#define StatAppIdecIaq CrdIdecIaq::StatApp
#define StatShrIdecIaq CrdIdecIaq::StatShr
#define TagIdecIaq CrdIdecIaq::Tag

#define DpchAppIdecIaqDo CrdIdecIaq::DpchAppDo
#define DpchEngIdecIaqData CrdIdecIaq::DpchEngData

/**
  * CrdIdecIaq
  */
namespace CrdIdecIaq {
	/**
		* VecVDo (full: VecVIdecIaqDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecIaqSge)
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
	  * ContInf (full: ContInfIdecIaq)
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
	  * StatApp (full: StatAppIdecIaq)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVREQITMODE = 1;
		static const uint LATENCY = 2;
		static const uint SHORTMENU = 3;
		static const uint WIDTHMENU = 4;
		static const uint INITDONELIVE = 5;
		static const uint INITDONEMECH = 6;
		static const uint INITDONESCILL = 7;
		static const uint INITDONEQCDSP = 8;
		static const uint INITDONEHEADBAR = 9;

	public:
		StatApp(const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneLive = false, const bool initdoneMech = false, const bool initdoneScill = false, const bool initdoneQcdsp = false, const bool initdoneHeadbar = false);

	public:
		uint ixIdecVReqitmode;
		usmallint latency;
		string shortMenu;
		uint widthMenu;
		bool initdoneLive;
		bool initdoneMech;
		bool initdoneScill;
		bool initdoneQcdsp;
		bool initdoneHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecIaq)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFLIVE = 1;
		static const uint SCRJREFMECH = 2;
		static const uint SCRJREFSCILL = 3;
		static const uint SCRJREFQCDSP = 4;
		static const uint SCRJREFHEADBAR = 5;

	public:
		StatShr(const string& scrJrefLive = "", const string& scrJrefMech = "", const string& scrJrefScill = "", const string& scrJrefQcdsp = "", const string& scrJrefHeadbar = "");

	public:
		string scrJrefLive;
		string scrJrefMech;
		string scrJrefScill;
		string scrJrefQcdsp;
		string scrJrefHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecIaq)
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
		* DpchAppDo (full: DpchAppIdecIaqDo)
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
		* DpchEngData (full: DpchEngIdecIaqData)
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

