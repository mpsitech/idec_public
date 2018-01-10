/**
  * \file JobIdecRecord.h
  * job handler for job JobIdecRecord (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECRECORD_H
#define JOBIDECRECORD_H

// IP custInclude --- INSERT

#include "JobIdecLwiracq.h"
#include "JobIdecQcdacq.h"
#include "JobIdecStereo.h"
#include "JobIdecVislacq.h"
#include "JobIdecVisracq.h"

#define VecVJobIdecRecordSge JobIdecRecord::VecVSge

/**
  * JobIdecRecord
  */
class JobIdecRecord : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecRecordSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint READY = 2;
		static const uint ACQIDLE = 3;
		static const uint ACQ = 4;
		static const uint PAUSE = 5;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecRecord(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecRecord();

public:

	JobIdecLwiracq* joblwiracq;
	JobIdecQcdacq* jobqcdacq;
	JobIdecStereo* jobstereo;
	JobIdecVislacq* jobvislacq;
	JobIdecVisracq* jobvisracq;

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void snapshot(DbsIdec* dbsidec);
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
	uint enterSgePause(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePause(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


