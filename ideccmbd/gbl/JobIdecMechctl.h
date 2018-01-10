/**
  * \file JobIdecMechctl.h
  * job handler for job JobIdecMechctl (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef JOBIDECMECHCTL_H
#define JOBIDECMECHCTL_H

// IP custInclude --- INSERT

#define VecVJobIdecMechctlSge JobIdecMechctl::VecVSge

/**
  * JobIdecMechctl
  */
class JobIdecMechctl : public JobIdec {

public:
	/**
		* VecVSge (full: VecVJobIdecMechctlSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint MOVE = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

public:
	JobIdecMechctl(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const bool prefmast);
	~JobIdecMechctl();

	static void initXchgdata(XchgIdec* xchg);
	static void termXchgdata(XchgIdec* xchg);

public:

	// IP specVar --- INSERT

	// IP custVar --- IBEGIN
	static constexpr double pi = 3.141592653589793238462643383279;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	double getAlpha();
	double getBeta();
	double getAlphabeta(const double A, const double T);

	void getThetaThetarpm(double& theta, int& thetarpm);
	void getPhiPhirpm(double& phi, int& phirpm);
	void getAngAngrpm(const double ang0, const double ang3, const double gr, timespec* tang0, double& ang, int& irpm);

	void setTargetTheta(DbsIdec* dbsidec, const double theta);
	void setTargetPhi(DbsIdec* dbsidec, const double phi);
	void setTargetAng(DbsIdec* dbsidec, const double ang, const double gr, uint& ixIdecVAxisste, double& ang0, double& ang1, timespec& tang0);

	void stopTheta();
	void stopPhi();
	void stopAng(const double llim, const double ulim, const double gr, double& ang0, double& ang1, timespec& tang0);

	void refresh(DbsIdec* dbsidec);
	// IP cust --- IEND

public:
	// IP spec --- INSERT

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeMove(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeMove(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void giveupMaster(DbsIdec* dbsidec);
	void giveupSlave(DbsIdec* dbsidec);
	void becomeMaster(DbsIdec* dbsidec);
	void becomeSlave(DbsIdec* dbsidec);

	bool handleClaimMaster(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


