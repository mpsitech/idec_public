/**
  * \file RootIdec.h
  * job handler for job RootIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef ROOTIDEC_H
#define ROOTIDEC_H

// IP custInclude --- INSERT

#include "SessIdec.h"

#define DpchAppRootIdecLogin RootIdec::DpchAppLogin

/**
  * RootIdec
  */
class RootIdec : public JobIdec {

public:
	/**
		* DpchAppLogin (full: DpchAppRootIdecLogin)
		*/
	class DpchAppLogin : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint PASSWORD = 2;
		static const uint USERNAME = 3;

	public:
		DpchAppLogin();

	public:
		string password;
		string username;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

public:
	RootIdec(XchgIdec* xchg, DbsIdec* dbsidec, const bool _clearAll);
	~RootIdec();

public:

	list<SessIdec*> sesss;

	// IP specVar --- INSERT

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	void clearAll(DbsIdec* dbsidec);
	void clearQtb(DbsIdec* dbsidec);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleClearAll(DbsIdec* dbsidec);
	bool handleCreateSess(DbsIdec* dbsidec);
	bool handleEraseSess(DbsIdec* dbsidec);

	void handleDpchAppLogin(DbsIdec* dbsidec, DpchAppLogin* dpchapplogin, const string ip, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecLogout(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

