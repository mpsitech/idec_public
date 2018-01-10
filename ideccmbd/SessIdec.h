/**
  * \file SessIdec.h
  * job handler for job SessIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef SESSIDEC_H
#define SESSIDEC_H

// IP custInclude --- INSERT

#include "CrdIdecNav.h"
#include "CrdIdecUsg.h"
#include "CrdIdecUsr.h"
#include "CrdIdecScf.h"
#include "CrdIdecUtl.h"
#include "CrdIdecMis.h"
#include "CrdIdecTou.h"
#include "CrdIdecIaq.h"
#include "CrdIdecAd1.h"
#include "CrdIdecFil.h"

#define StatShrSessIdec SessIdec::StatShr

#define DpchEngSessIdecData SessIdec::DpchEngData

/**
  * SessIdec
  */
class SessIdec : public JobIdec {

public:
	/**
		* StatShr (full: StatShrSessIdec)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFCRDNAV = 1;

	public:
		StatShr(const ubigint jrefCrdnav = 0);

	public:
		ubigint jrefCrdnav;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* DpchEngData (full: DpchEngSessIdecData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint STATSHR = 2;
		static const uint ALL = 3;

	public:
		DpchEngData(const ubigint jref = 0, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

public:
	SessIdec(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const ubigint refIdecMUser, const string& ip);
	~SessIdec();

public:
	StatShr statshr;

	CrdIdecNav* crdnav;
	list<CrdIdecUsg*> crdusgs;
	list<CrdIdecUsr*> crdusrs;
	list<CrdIdecScf*> crdscfs;
	list<CrdIdecUtl*> crdutls;
	list<CrdIdecMis*> crdmiss;
	list<CrdIdecTou*> crdtous;
	list<CrdIdecIaq*> crdiaqs;
	list<CrdIdecAd1*> crdad1s;
	list<CrdIdecFil*> crdfils;

	map<ubigint, uint> usgaccs;

	map<ubigint,string> scr;
	map<string,ubigint> descr;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	uint checkCrdActive(const uint ixIdecVCard);
	uint evalCrdtouActive();
	uint evalCrdiaqActive();
	uint evalCrdad1Active();
	uint evalCrdfilActive();

	uint checkUiaccess(const uint ixIdecVCard);
	uint getIxUac(DbsIdec* dbsidec, const uint ixIdecVCard, const bool adm, ListIdecRMUserMUsergroup& urus, const ubigint refIdecMUser);

	uint checkAccess(DbsIdec* dbsidec, const uint ixIdecVCard, const ubigint ref);
	void logAccess(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint preUref, const uint ixIdecVCard, const ubigint unvUref);

	uint crdToMtb(const uint ixIdecVCard);
	uint preToMtb(const uint ixIdecVPreset);
	bool hasActive(const uint ixIdecVCard);
	bool hasGrpown(const uint ixIdecVMaintable);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleCreateCrdad1(DbsIdec* dbsidec);
	bool handleCreateCrdfil(DbsIdec* dbsidec);
	bool handleCreateCrdiaq(DbsIdec* dbsidec);
	bool handleCreateCrdmis(DbsIdec* dbsidec);
	bool handleCreateCrdscf(DbsIdec* dbsidec);
	bool handleCreateCrdtou(DbsIdec* dbsidec);
	bool handleCreateCrdusg(DbsIdec* dbsidec);
	bool handleCreateCrdusr(DbsIdec* dbsidec);
	bool handleCreateCrdutl(DbsIdec* dbsidec);
	bool handleEraseCrdad1(DbsIdec* dbsidec);
	bool handleEraseCrdfil(DbsIdec* dbsidec);
	bool handleEraseCrdiaq(DbsIdec* dbsidec);
	bool handleEraseCrdmis(DbsIdec* dbsidec);
	bool handleEraseCrdscf(DbsIdec* dbsidec);
	bool handleEraseCrdtou(DbsIdec* dbsidec);
	bool handleEraseCrdusg(DbsIdec* dbsidec);
	bool handleEraseCrdusr(DbsIdec* dbsidec);
	bool handleEraseCrdutl(DbsIdec* dbsidec);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecAccess(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv, uint& ixRet);
	bool handleCallIdecCrdActive(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, uint& ixRet);
	bool handleCallIdecCrdClose(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv);
	bool handleCallIdecCrdOpen(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv, const string& srefInv, const int intvalInv, ubigint& refRet);
	bool handleCallIdecDescr(DbsIdec* dbsidec, const ubigint jrefTrig, const string& srefInv, ubigint& refRet);
	bool handleCallIdecLog(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv, const string& srefInv, const int intvalInv);
	bool handleCallIdecScr(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv, string& srefRet);
	bool handleCallIdecRefPreSet(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

