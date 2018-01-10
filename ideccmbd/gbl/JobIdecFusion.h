/**
  * \file JobIdecFusion.h
  * job handler for job JobIdecFusion (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECFUSION_H
#define JOBIDECFUSION_H

// IP custInclude --- INSERT

#include "JobIdecLwiracq.h"
#include "JobIdecVislacq.h"

#define VecVJobIdecFusionSge JobIdecFusion::VecVSge

/**
  * JobIdecFusion
  */
class JobIdecFusion : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecFusionSge)
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
	JobIdecFusion(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecFusion();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	JobIdecLwiracq* joblwiracq;
	JobIdecVislacq* jobvislacq;

	// IP specVar --- INSERT

	// IP custVar --- IBEGIN
	ubigint bref;
	unsigned int seqno;
	timespec timestamp;

	vector<Snippet*> snippets;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	// exact copy from Idec but inline
	inline unsigned int intavg(const unsigned int in, const unsigned int im, bool* rshs, const unsigned int rshsN);

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

	bool handleCallIdecStart(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStop(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecIbitrdy(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


