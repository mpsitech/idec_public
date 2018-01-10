/**
  * \file JobIdecQcdacq.h
  * job handler for job JobIdecQcdacq (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECQCDACQ_H
#define JOBIDECQCDACQ_H

// IP custInclude --- IBEGIN
#include <chrono>
#include <random>
// IP custInclude --- IEND

#include "JobIdecTrigger.h"

#define VecVJobIdecQcdacqSge JobIdecQcdacq::VecVSge

/**
  * JobIdecQcdacq
  */
class JobIdecQcdacq : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecQcdacqSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint COOL = 2;
		static const uint READY = 3;
		static const uint ACQIDLE = 4;
		static const uint ACQ = 5;
		static const uint PRC = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecQcdacq(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecQcdacq();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	JobIdecTrigger* jobtrigger;

	// IP specVar --- INSERT

	// IP custVar --- IBEGIN
	static constexpr double pi = 3.141592653589793238462643383279;

	static constexpr double h = 6.626068e-34;
	static constexpr double c0 = 2.99792458e8;
	static constexpr double k = 1.3806503e-23;
	static constexpr double sig = 5.67037321e-8;

	ubigint bref;
	unsigned int seqno;
	timespec timestamp;

	vector<double> T;
	vector<double> DeltaT;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	double getTdet();
	void setTargetTdet(DbsIdec* dbsidec, const double Tdet);

	void refresh(DbsIdec* dbsidec);

	void changeSqrgrp(const uint ixIdecVSqrgrp);
	void changePixel(const bool fullframe, const usmallint pixel);
	void changeTint(const double tint);

	static void setupIplTTvsSS(XchgIdec* xchg); // includes iplDTdSvsSS

	static void setupTTvsSS(XchgIdec* xchg);
	static void setupDTdSvsSS(XchgIdec* xchg);

	static double Sqcd(const double T, const double Flam0, const double Fdlam, const unsigned int FsigN, const double lam0, const double lam1, const double dlam);

	void start(DbsIdec* dbsidec, const bool fullframe = true, const usmallint pixel = 0, const double tint = 0.1);
	void stop(DbsIdec* dbsidec);
	bool started(const bool any = false);
	// IP cust --- IEND

public:
	// IP spec --- INSERT

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeCool(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeCool(DbsIdec* dbsidec);
	uint enterSgeReady(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeReady(DbsIdec* dbsidec);
	uint enterSgeAcqidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAcqidle(DbsIdec* dbsidec);
	uint enterSgeAcq(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAcq(DbsIdec* dbsidec);
	uint enterSgePrc(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrc(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecTrigQcd(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecStart(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStop(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecSptfnd(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecIbitrdy(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


