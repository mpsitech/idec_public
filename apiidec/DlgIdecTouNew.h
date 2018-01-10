/**
  * \file DlgIdecTouNew.h
  * API code for job DlgIdecTouNew (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECTOUNEW_H
#define DLGIDECTOUNEW_H

#include "ApiIdec_blks.h"

#define VecVDlgIdecTouNewDo DlgIdecTouNew::VecVDo
#define VecVDlgIdecTouNewSge DlgIdecTouNew::VecVSge

#define ContIacDlgIdecTouNew DlgIdecTouNew::ContIac
#define ContInfDlgIdecTouNew DlgIdecTouNew::ContInf
#define StatAppDlgIdecTouNew DlgIdecTouNew::StatApp
#define StatShrDlgIdecTouNew DlgIdecTouNew::StatShr
#define TagDlgIdecTouNew DlgIdecTouNew::Tag

#define DpchAppDlgIdecTouNewData DlgIdecTouNew::DpchAppData
#define DpchAppDlgIdecTouNewDo DlgIdecTouNew::DpchAppDo
#define DpchEngDlgIdecTouNewData DlgIdecTouNew::DpchEngData

/**
  * DlgIdecTouNew
  */
namespace DlgIdecTouNew {
	/**
		* VecVDo (full: VecVDlgIdecTouNewDo)
		*/
	class VecVDo {

	public:
		static const uint BUTCNCCLICK = 1;
		static const uint BUTCRECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecTouNewSge)
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
	  * ContIac (full: ContIacDlgIdecTouNew)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFDETPUPMIS = 1;
		static const uint DETTXFTIT = 2;
		static const uint DETTXFARE = 3;
		static const uint DETTXFTHE = 4;
		static const uint DETTXFPHI = 5;

	public:
		ContIac(const uint numFDetPupMis = 1, const string& DetTxfTit = "", const string& DetTxfAre = "", const string& DetTxfThe = "", const string& DetTxfPhi = "");

	public:
		uint numFDetPupMis;
		string DetTxfTit;
		string DetTxfAre;
		string DetTxfThe;
		string DetTxfPhi;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfDlgIdecTouNew)
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
	  * StatApp (full: StatAppDlgIdecTouNew)
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
	  * StatShr (full: StatShrDlgIdecTouNew)
	  */
	class StatShr : public Block {

	public:
		static const uint DETPUPMISACTIVE = 1;
		static const uint BUTCNCACTIVE = 2;
		static const uint BUTCREACTIVE = 3;

	public:
		StatShr(const bool DetPupMisActive = true, const bool ButCncActive = true, const bool ButCreActive = true);

	public:
		bool DetPupMisActive;
		bool ButCncActive;
		bool ButCreActive;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagDlgIdecTouNew)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint DETCPTMIS = 2;
		static const uint DETCPTTIT = 3;
		static const uint DETCPTARE = 4;
		static const uint DETCPTTHE = 5;
		static const uint DETCPTPHI = 6;
		static const uint BUTCNC = 7;
		static const uint BUTCRE = 8;

	public:
		Tag(const string& Cpt = "", const string& DetCptMis = "", const string& DetCptTit = "", const string& DetCptAre = "", const string& DetCptThe = "", const string& DetCptPhi = "", const string& ButCnc = "", const string& ButCre = "");

	public:
		string Cpt;
		string DetCptMis;
		string DetCptTit;
		string DetCptAre;
		string DetCptThe;
		string DetCptPhi;
		string ButCnc;
		string ButCre;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecTouNewData)
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
		* DpchAppDo (full: DpchAppDlgIdecTouNewDo)
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
		* DpchEngData (full: DpchEngDlgIdecTouNewData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFDETPUPMIS = 4;
		static const uint FEEDFSGE = 5;
		static const uint STATAPP = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFDetPupMis;
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

