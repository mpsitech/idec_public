/**
  * \file DlgIdecUtlQcdaln.h
  * API code for job DlgIdecUtlQcdaln (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECUTLQCDALN_H
#define DLGIDECUTLQCDALN_H

#include "ApiIdec_blks.h"

#define VecVDlgIdecUtlQcdalnDit DlgIdecUtlQcdaln::VecVDit
#define VecVDlgIdecUtlQcdalnDo DlgIdecUtlQcdaln::VecVDo
#define VecVDlgIdecUtlQcdalnSge DlgIdecUtlQcdaln::VecVSge

#define ContIacDlgIdecUtlQcdaln DlgIdecUtlQcdaln::ContIac
#define ContInfDlgIdecUtlQcdaln DlgIdecUtlQcdaln::ContInf
#define StatAppDlgIdecUtlQcdaln DlgIdecUtlQcdaln::StatApp
#define TagDlgIdecUtlQcdaln DlgIdecUtlQcdaln::Tag

#define DpchAppDlgIdecUtlQcdalnData DlgIdecUtlQcdaln::DpchAppData
#define DpchAppDlgIdecUtlQcdalnDo DlgIdecUtlQcdaln::DpchAppDo
#define DpchEngDlgIdecUtlQcdalnData DlgIdecUtlQcdaln::DpchEngData

/**
  * DlgIdecUtlQcdaln
  */
namespace DlgIdecUtlQcdaln {
	/**
		* VecVDit (full: VecVDlgIdecUtlQcdalnDit)
		*/
	class VecVDit {

	public:

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVDo (full: VecVDlgIdecUtlQcdalnDo)
		*/
	class VecVDo {

	public:
		static const uint BUTDNECLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecUtlQcdalnSge)
		*/
	class VecVSge {

	public:

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacDlgIdecUtlQcdaln)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFDSE = 1;

	public:
		ContIac(const uint numFDse = 1);

	public:
		uint numFDse;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfDlgIdecUtlQcdaln)
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
	  * StatApp (full: StatAppDlgIdecUtlQcdaln)
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
	  * Tag (full: TagDlgIdecUtlQcdaln)
	  */
	class Tag : public Block {

	public:
		static const uint CPT = 1;
		static const uint BUTDNE = 2;

	public:
		Tag(const string& Cpt = "", const string& ButDne = "");

	public:
		string Cpt;
		string ButDne;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecUtlQcdalnData)
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
		* DpchAppDo (full: DpchAppDlgIdecUtlQcdalnDo)
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
		* DpchEngData (full: DpchEngDlgIdecUtlQcdalnData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFDSE = 4;
		static const uint FEEDFSGE = 5;
		static const uint STATAPP = 6;
		static const uint TAG = 7;

	public:
		DpchEngData();

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFDse;
		Feed feedFSge;
		StatApp statapp;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

