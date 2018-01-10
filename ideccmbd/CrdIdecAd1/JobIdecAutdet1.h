/**
  * \file JobIdecAutdet1.h
  * job handler for job JobIdecAutdet1 (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECAUTDET1_H
#define JOBIDECAUTDET1_H

// IP custInclude --- INSERT

#include "JobIdecIllum.h"
#include "JobIdecLwiracq.h"
#include "JobIdecMechctl.h"
#include "JobIdecQcdacq.h"
#include "JobIdecRecord.h"
#include "JobIdecTrigger.h"

#define VecVJobIdecAutdet1Sge JobIdecAutdet1::VecVSge

/**
  * JobIdecAutdet1
  */
class JobIdecAutdet1 : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecAutdet1Sge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint SURVEY = 2;
		static const uint POS = 3;
		static const uint PRC = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecAutdet1(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecAutdet1();

public:

	JobIdecIllum* jobillum;
	JobIdecLwiracq* joblwiracq;
	JobIdecMechctl* jobmechctl;
	JobIdecQcdacq* jobqcdacq;
	JobIdecRecord* jobrecord;
	JobIdecTrigger* jobtrigger;

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	// IP spec --- INSERT

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeSurvey(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeSurvey(DbsIdec* dbsidec);
	uint enterSgePos(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePos(DbsIdec* dbsidec);
	uint enterSgePrc(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrc(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

