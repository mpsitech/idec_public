/**
  * \file JobIdecIllum.h
  * job handler for job JobIdecIllum (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECILLUM_H
#define JOBIDECILLUM_H

// IP custInclude --- INSERT

/**
  * JobIdecIllum
  */
class JobIdecIllum : public JobIdec {

public:

public:
	JobIdecIllum(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecIllum();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void setPFlood(DbsIdec* dbsidec, const double pFlood);
	void setPSpot(DbsIdec* dbsidec, const double pSpot);
	// IP cust --- IEND

public:
	// IP spec --- INSERT

public:

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


