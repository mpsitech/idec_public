/**
  * \file DlgIdecMisNew.h
  * API code for job DlgIdecMisNew (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECMISNEW_H
#define DLGIDECMISNEW_H

#include "ApiIdec_blks.h"

#define VecVDlgIdecMisNewDo DlgIdecMisNew::VecVDo
#define VecVDlgIdecMisNewSge DlgIdecMisNew::VecVSge

#define ContIacDlgIdecMisNew DlgIdecMisNew::ContIac
#define ContInfDlgIdecMisNew DlgIdecMisNew::ContInf
#define StatAppDlgIdecMisNew DlgIdecMisNew::StatApp
#define StatShrDlgIdecMisNew DlgIdecMisNew::StatShr
#define TagDlgIdecMisNew DlgIdecMisNew::Tag

#define DpchAppDlgIdecMisNewData DlgIdecMisNew::DpchAppData
#define DpchAppDlgIdecMisNewDo DlgIdecMisNew::DpchAppDo
#define DpchEngDlgIdecMisNewData DlgIdecMisNew::DpchEngData

/**
  * DlgIdecMisNew
  */
namespace DlgIdecMisNew {
	/**
		* VecVDo (full: VecVDlgIdecMisNewDo)
		*/
	class VecVDo {

	public:
		static const uint BUTCNCCLICK = 1;
		static const uint BUTCRECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecMisNewSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint CREATE = 2;
		static const uint DONE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacDlgIdecMisNew)
	  */
	class ContIac : public Block {

	public:
		static const uint DETTXFTIT = 1;
		static const uint NUMFDETPUPCRY = 2;
		static const uint DETTXFREG = 3;
		static const uint DETTXFMUN = 4;

	public:
		ContIac(const string& DetTxfTit = "", const uint numFDetPupCry = 1, const string& DetTxfReg = "", const string& DetTxfMun = "");

	public:
		string DetTxfTit;
		uint numFDetPupCry;
		string DetTxfReg;
		string DetTxfMun;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfDlgIdecMisNew)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;

	public:
		ContInf(const uint numFSge = 1);

	public:
		uint numFSge;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatApp (full: StatAppDlgIdecMisNew)
	  */
	class StatApp : public Block {

	public:
		static const uint SHORTMENU = 1;

	public:
		StatApp(const string& shortMenu = "");

	public:
		string shortMenu;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatApp* comp);
		set<uint> diff(const StatApp* comp);
	};

	/**
	  * StatShr (full: StatShrDlgIdecMisNew)
	  */
	class StatShr : public Block {

	public:
		static const uint BUTCNCACTIVE = 1;
		static const uint BUTCREACTIVE = 2;

	public:
		StatShr(const bool ButCncActive = true, const bool ButCreActive = true);

	public:
		bool ButCncActive;
		bool ButCreActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagDlgIdecMisNew)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint DETCPTTIT = 2;
		static const uint DETCPTCRY = 3;
		static const uint DETCPTREG = 4;
		static const uint DETCPTMUN = 5;
		static const uint BUTCNC = 6;
		static const uint BUTCRE = 7;

	public:
		Tag(const string& Cpt = "", const string& DetCptTit = "", const string& DetCptCry = "", const string& DetCptReg = "", const string& DetCptMun = "", const string& ButCnc = "", const string& ButCre = "");

	public:
		string Cpt;
		string DetCptTit;
		string DetCptCry;
		string DetCptReg;
		string DetCptMun;
		string ButCnc;
		string ButCre;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecMisNewData)
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
		* DpchAppDo (full: DpchAppDlgIdecMisNewDo)
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
		* DpchEngData (full: DpchEngDlgIdecMisNewData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFDETPUPCRY = 4;
		static const uint FEEDFSGE = 5;
		static const uint STATAPP = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFDetPupCry;
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

