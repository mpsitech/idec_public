/**
  * \file CrdIdecUtl.h
  * API code for job CrdIdecUtl (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECUTL_H
#define CRDIDECUTL_H

#include "ApiIdec_blks.h"

#define VecVIdecUtlDo CrdIdecUtl::VecVDo
#define VecVIdecUtlSge CrdIdecUtl::VecVSge

#define ContInfIdecUtl CrdIdecUtl::ContInf
#define StatAppIdecUtl CrdIdecUtl::StatApp
#define StatShrIdecUtl CrdIdecUtl::StatShr
#define TagIdecUtl CrdIdecUtl::Tag

#define DpchAppIdecUtlDo CrdIdecUtl::DpchAppDo
#define DpchEngIdecUtlData CrdIdecUtl::DpchEngData

/**
  * CrdIdecUtl
  */
namespace CrdIdecUtl {
	/**
		* VecVDo (full: VecVIdecUtlDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITCRDTHECLICK = 3;
		static const uint MITCRDPHICLICK = 4;
		static const uint MITCRDSTECLICK = 5;
		static const uint MITCRDFSNCLICK = 6;
		static const uint MITCRDQNUCLICK = 7;
		static const uint MITCRDQALCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecUtlSge)
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
	  * ContInf (full: ContInfIdecUtl)
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
	  * StatApp (full: StatAppIdecUtl)
	  */
	class StatApp : public Block {

	public:
		static const uint IXIDECVREQITMODE = 1;
		static const uint LATENCY = 2;
		static const uint SHORTMENU = 3;
		static const uint WIDTHMENU = 4;
		static const uint INITDONESPITERM = 5;
		static const uint INITDONEHEADBAR = 6;

	public:
		StatApp(const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneSpiterm = false, const bool initdoneHeadbar = false);

	public:
		uint ixIdecVReqitmode;
		usmallint latency;
		string shortMenu;
		uint widthMenu;
		bool initdoneSpiterm;
		bool initdoneHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrIdecUtl)
	  */
	class StatShr : public Block {

	public:
		static const uint SCRJREFDLGFUSION = 1;
		static const uint SCRJREFDLGPHI = 2;
		static const uint SCRJREFDLGQCDALN = 3;
		static const uint SCRJREFDLGQCDNUC = 4;
		static const uint SCRJREFDLGSTEREO = 5;
		static const uint SCRJREFDLGTHETA = 6;
		static const uint SCRJREFSPITERM = 7;
		static const uint SCRJREFHEADBAR = 8;

	public:
		StatShr(const string& scrJrefDlgfusion = "", const string& scrJrefDlgphi = "", const string& scrJrefDlgqcdaln = "", const string& scrJrefDlgqcdnuc = "", const string& scrJrefDlgstereo = "", const string& scrJrefDlgtheta = "", const string& scrJrefSpiterm = "", const string& scrJrefHeadbar = "");

	public:
		string scrJrefDlgfusion;
		string scrJrefDlgphi;
		string scrJrefDlgqcdaln;
		string scrJrefDlgqcdnuc;
		string scrJrefDlgstereo;
		string scrJrefDlgtheta;
		string scrJrefSpiterm;
		string scrJrefHeadbar;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecUtl)
	  */
	class Tag : public Block {

	public:
		static const uint MITAPPABT = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MITCRDTHE = 3;
		static const uint MITCRDPHI = 4;
		static const uint MITCRDSTE = 5;
		static const uint MITCRDFSN = 6;
		static const uint MITCRDQNU = 7;
		static const uint MITCRDQAL = 8;

	public:
		Tag(const string& MitAppAbt = "", const string& MrlAppHlp = "", const string& MitCrdThe = "", const string& MitCrdPhi = "", const string& MitCrdSte = "", const string& MitCrdFsn = "", const string& MitCrdQnu = "", const string& MitCrdQal = "");

	public:
		string MitAppAbt;
		string MrlAppHlp;
		string MitCrdThe;
		string MitCrdPhi;
		string MitCrdSte;
		string MitCrdFsn;
		string MitCrdQnu;
		string MitCrdQal;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUtlDo)
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
		* DpchEngData (full: DpchEngIdecUtlData)
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

