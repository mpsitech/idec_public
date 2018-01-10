/**
  * \file JobIdecSpotfind.h
  * job handler for job JobIdecSpotfind (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECSPOTFIND_H
#define JOBIDECSPOTFIND_H

// IP custInclude --- INSERT

#include "JobIdecVislacq.h"
#include "JobIdecVisracq.h"

#define VecVJobIdecSpotfindSge JobIdecSpotfind::VecVSge

/**
  * JobIdecSpotfind
  */
class JobIdecSpotfind : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecSpotfindSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint READY = 2;
		static const uint ACQIDLE = 3;
		static const uint ACQ = 4;
		static const uint PRC = 5;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecSpotfind(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecSpotfind();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	JobIdecVislacq* jobvislacq;
	JobIdecVisracq* jobvisracq;

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void start(DbsIdec* dbsidec, const bool visr);
	void stop(DbsIdec* dbsidec);
	bool started(const bool any = false);

	double triangulate(const double ds, const double x1, const double f1, const double x2, const double f2, const double dphi);
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

	bool handleCallIdecStart(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStop(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecSptfnd(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


