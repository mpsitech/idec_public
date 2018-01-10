/**
  * \file JobIdecLwiracq.h
  * job handler for job JobIdecLwiracq (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECLWIRACQ_H
#define JOBIDECLWIRACQ_H

// IP custInclude --- INSERT

#include "JobIdecTrigger.h"

#define VecVJobIdecLwiracqSge JobIdecLwiracq::VecVSge

/**
  * JobIdecLwiracq
  */
class JobIdecLwiracq : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecLwiracqSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint READY = 2;
		static const uint ACQIDLE = 3;
		static const uint ACQ = 4;
		static const uint PRCIDLE = 5;
		static const uint PRC = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecLwiracq(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecLwiracq();

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

	vector<Snippet*> snippets;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	void changeSqrgrp(const uint ixIdecVSqrgrp);

	static void setupIplTTvsSS(XchgIdec* xchg);
	static void setupTTvsSS(XchgIdec* xchg);

	static double Slwir(const double T, const double Flam0, const double Flam1, const double lam0, const double lam1, const double dlam);

	// exact copy from Idec but inline
	static inline unsigned int intavg(const unsigned int in, const unsigned int im, bool* rshs, const unsigned int rshsN);

	void start(DbsIdec* dbsidec, vector<Snippet*> _snippets);
	void stop(DbsIdec* dbsidec);
	bool started(const bool any = false);
	// IP cust --- IEND

public:
	// IP spec --- INSERT

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeReady(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeReady(DbsIdec* dbsidec);
	uint enterSgeAcqidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAcqidle(DbsIdec* dbsidec);
	uint enterSgeAcq(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAcq(DbsIdec* dbsidec);
	uint enterSgePrcidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrcidle(DbsIdec* dbsidec);
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

	bool handleCallIdecTrigLwir(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecStart(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStop(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecIbitrdy(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


