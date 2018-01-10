/**
  * \file JobIdecTrigger.h
  * job handler for job JobIdecTrigger (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECTRIGGER_H
#define JOBIDECTRIGGER_H

// IP custInclude --- INSERT

#define VecVJobIdecTriggerSge JobIdecTrigger::VecVSge

/**
  * JobIdecTrigger
  */
class JobIdecTrigger : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecTriggerSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint RUN = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecTrigger(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecTrigger();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void setupUsecWaits();

	void start(DbsIdec* dbsidec, const double fps);
	void stop(DbsIdec* dbsidec);
	
	void handleUsec(DbsIdec* dbsidec, const string& sref);
	// IP cust --- IEND

public:
	// IP spec --- INSERT

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeRun(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeRun(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecTrigVisl(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecTrigVisr(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecTrigLwir(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecTrigQcd(DbsIdec* dbsidec, const ubigint jrefTrig, const int intvalInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


