/**
  * \file PnlIdecNavPre.h
  * API code for job PnlIdecNavPre (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVPRE_H
#define PNLIDECNAVPRE_H

#include "ApiIdec_blks.h"

#define VecVIdecNavPreDo PnlIdecNavPre::VecVDo

#define ContInfIdecNavPre PnlIdecNavPre::ContInf
#define StatShrIdecNavPre PnlIdecNavPre::StatShr
#define TagIdecNavPre PnlIdecNavPre::Tag

#define DpchAppIdecNavPreDo PnlIdecNavPre::DpchAppDo
#define DpchEngIdecNavPreData PnlIdecNavPre::DpchEngData

/**
  * PnlIdecNavPre
  */
namespace PnlIdecNavPre {
	/**
		* VecVDo (full: VecVIdecNavPreDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMISREMOVECLICK = 1;
		static const uint BUTTOUREMOVECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecNavPre)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTMIS = 1;
		static const uint TXTTOU = 2;

	public:
		ContInf(const string& TxtMis = "", const string& TxtTou = "");

	public:
		string TxtMis;
		string TxtTou;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
	  * StatShr (full: StatShrIdecNavPre)
	  */
	class StatShr : public Block {

	public:
		static const uint TXTMISAVAIL = 1;
		static const uint TXTTOUAVAIL = 2;

	public:
		StatShr(const bool TxtMisAvail = true, const bool TxtTouAvail = true);

	public:
		bool TxtMisAvail;
		bool TxtTouAvail;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
	  * Tag (full: TagIdecNavPre)
	  */
	class Tag : public Block {

	public:
		static const uint CPTMIS = 1;
		static const uint CPTTOU = 2;

	public:
		Tag(const string& CptMis = "", const string& CptTou = "");

	public:
		string CptMis;
		string CptTou;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecNavPreDo)
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
		* DpchEngData (full: DpchEngIdecNavPreData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint CONTINF = 2;
		static const uint STATSHR = 3;
		static const uint TAG = 4;

	public:
		DpchEngData();

	public:
		ContInf continf;
		StatShr statshr;
		Tag tag;

	public:
		string getSrefsMask();

		void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

};

#endif

