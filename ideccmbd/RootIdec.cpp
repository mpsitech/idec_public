/**
  * \file RootIdec.cpp
  * job handler for job RootIdec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "RootIdec.h"

#include "RootIdec_blks.cpp"

/******************************************************************************
 class RootIdec
 ******************************************************************************/

RootIdec::RootIdec(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const bool _clearAll
		) : JobIdec(xchg, VecIdecVJob::ROOTIDEC, 0, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	// log
	xchg->appendToLogfile("root job created");

	if (_clearAll) clearAll(dbsidec);
	else clearQtb(dbsidec);

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECLOGOUT, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

RootIdec::~RootIdec() {
	// log
	xchg->appendToLogfile("root job deleted");

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void RootIdec::clearAll(
			DbsIdec* dbsidec
		) {
	IdecMUsergroup* usg = NULL;
	IdecRMUserMUsergroup* uru = NULL;
	IdecMUser* usr = NULL;
	ubigint refUjs = 0;
	IdecMPerson* prs = NULL;
	ubigint refPjl = 0;

	time_t timeval;
	uint dateval;

	string s;

	// empty out tables
	dbsidec->executeQuery("DELETE FROM TblIdecAccRMUserUniversal");
	dbsidec->executeQuery("DELETE FROM TblIdecAMPersonDetail");
	dbsidec->executeQuery("DELETE FROM TblIdecAMUserAccess");
	dbsidec->executeQuery("DELETE FROM TblIdecAMUsergroupAccess");
	dbsidec->executeQuery("DELETE FROM TblIdecAVControlPar");
	dbsidec->executeQuery("DELETE FROM TblIdecAVKeylistKey");
	dbsidec->executeQuery("DELETE FROM TblIdecAVValuelistVal");
	if (dbsidec->ixDbsVDbstype == VecDbsVDbstype::MY) dbsidec->executeQuery("DELETE FROM TblIdecCFile");
	else if (dbsidec->ixDbsVDbstype == VecDbsVDbstype::PG) dbsidec->executeQuery("ALTER SEQUENCE TblIdecCFile RESTART WITH 1");
	dbsidec->executeQuery("DELETE FROM TblIdecHistRMUserUniversal");
	dbsidec->executeQuery("DELETE FROM TblIdecJAVKeylistKey");
	dbsidec->executeQuery("DELETE FROM TblIdecJMPersonLastname");
	dbsidec->executeQuery("DELETE FROM TblIdecJMUserState");
	dbsidec->executeQuery("DELETE FROM TblIdecMFile");
	dbsidec->executeQuery("DELETE FROM TblIdecMMission");
	dbsidec->executeQuery("DELETE FROM TblIdecMPerson");
	dbsidec->executeQuery("DELETE FROM TblIdecMSession");
	dbsidec->executeQuery("DELETE FROM TblIdecMTour");
	dbsidec->executeQuery("DELETE FROM TblIdecMUser");
	dbsidec->executeQuery("DELETE FROM TblIdecMUsergroup");
	dbsidec->executeQuery("DELETE FROM TblIdecRMUsergroupUniversal");
	dbsidec->executeQuery("DELETE FROM TblIdecRMUserMUsergroup");

	clearQtb(dbsidec);

	// generate a temporary user such that a session can be generated
	dbsidec->tblidecmusergroup->insertNewRec(&usg, 0, 0, "temp", "temporary user group for system initialization");
	dbsidec->tblidecamusergroupaccess->insertNewRec(NULL, usg->ref, VecIdecVCard::CRDIDECNAV, VecIdecWUiaccess::EDIT + VecIdecWUiaccess::EXEC + VecIdecWUiaccess::VIEW);
	dbsidec->tblidecrmusermusergroup->insertNewRec(&uru, 0, usg->ref, VecIdecVUserlevel::GADM);
	dbsidec->tblidecmuser->insertNewRec(&usr, usg->ref, 0, uru->ref, usg->ref, 0, "temp", 0, VecIdecVMUserState::DUE, VecIdecVLocale::ENUS, VecIdecVUserlevel::GADM, "asdf1234");
	refUjs = dbsidec->tblidecjmuserstate->insertNewRec(NULL, usr->ref, 0, VecIdecVMUserState::DUE);

	time(&timeval);
	dateval = 1 + (timeval - (timeval % (3600*24))) / (3600*24);

	dbsidec->tblidecjmuserstate->insertNewRec(NULL, usr->ref, dateval, VecIdecVMUserState::EXP);
	dbsidec->tblidecmperson->insertNewRec(&prs, usg->ref, usr->ref, VecIdecWMPersonDerivate::USR, VecIdecVMPersonSex::M, "Mr.", "Jack", 0, "Smith", 0, "", 0, "", "Dear Jack");

	refPjl = dbsidec->tblidecjmpersonlastname->insertNewRec(NULL, prs->ref, 0, "Smith");

	usg->grp = usg->ref;
	usg->own = usr->ref;
	dbsidec->tblidecmusergroup->updateRec(usg);

	uru->refIdecMUser = usr->ref;
	dbsidec->tblidecrmusermusergroup->updateRec(uru);

	usr->refIdecMPerson = prs->ref;
	usr->refJState = refUjs;
	dbsidec->tblidecmuser->updateRec(usr);

	prs->refJLastname = refPjl;
	dbsidec->tblidecmperson->updateRec(prs);

	cout << "\ttemporary account created for user 'temp', expires " << Ftm::date(dateval) << "; use password 'asdf1234' to log in" << endl;

	xchg->appendToLogfile("database cleared");

	delete usg;
	delete uru;
	delete usr;
	delete prs;
};

void RootIdec::clearQtb(
			DbsIdec* dbsidec
		) {
	dbsidec->executeQuery("DELETE FROM TblIdecQFilList");
	dbsidec->executeQuery("DELETE FROM TblIdecQMis1NTour");
	dbsidec->executeQuery("DELETE FROM TblIdecQMisList");
	dbsidec->executeQuery("DELETE FROM TblIdecQMisRef1NFile");
	dbsidec->executeQuery("DELETE FROM TblIdecQPreselect");
	dbsidec->executeQuery("DELETE FROM TblIdecQSelect");
	dbsidec->executeQuery("DELETE FROM TblIdecQTouList");
	dbsidec->executeQuery("DELETE FROM TblIdecQTouRef1NFile");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsgAAccess");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsgList");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsgMNUser");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsr1NSession");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsrAAccess");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsrList");
	dbsidec->executeQuery("DELETE FROM TblIdecQUsrMNUsergroup");
};

void RootIdec::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {
			cout << "\tclearAll" << endl;
			cout << "\tcreateSess" << endl;
			cout << "\teraseSess" << endl;
		} else if (req->cmd == "clearAll") {
			req->retain = handleClearAll(dbsidec);

		} else if (req->cmd == "createSess") {
			req->retain = handleCreateSess(dbsidec);

		} else if (req->cmd == "eraseSess") {
			req->retain = handleEraseSess(dbsidec);

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
		if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPROOTIDECLOGIN) {
			handleDpchAppLogin(dbsidec, (DpchAppLogin*) (req->dpchapp), req->ip, &(req->dpcheng));

		};
	};
};

bool RootIdec::handleClearAll(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	clearAll(dbsidec);
	return retval;
};

bool RootIdec::handleCreateSess(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	string input2;

	ubigint refUsr;

	SessIdec* sess = NULL;

	cout << "\tuser name: ";
	cin >> input;
	cout << "\tpassword: ";
	cin >> input2;

	// verify password and create a session
	if (dbsidec->tblidecmuser->loadRefBySrfPwd(input, input2, refUsr)) {
		sess = new SessIdec(xchg, dbsidec, jref, refUsr, "127.0.0.1");
		sesss.push_back(sess);

		cout << "\tjob reference: " << sess->jref << endl;
		xchg->jrefCmd = sess->jref;

		xchg->appendToLogfile("command line session created for user '" + input + "'");

	} else {
		cout << "\tlogin failed." << endl;

		xchg->appendToLogfile("command line login refused for user '" + input + "'");
	};

	return false;
	return retval;
};

bool RootIdec::handleEraseSess(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	SessIdec* sess = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=sesss.begin();it!=sesss.end();) {
		sess = *it;
		if (sess->jref == iinput) {
			it = sesss.erase(it);
			delete sess;
			break;
		} else it++;
	};

	return false;
	return retval;
};

void RootIdec::handleDpchAppLogin(
			DbsIdec* dbsidec
			, DpchAppLogin* dpchapplogin
			, const string ip
			, DpchEngIdec** dpcheng
		) {
	ubigint refUsr;

	SessIdec* sess = NULL;

	// verify password and create a session
	if (dbsidec->tblidecmuser->loadRefBySrfPwd(dpchapplogin->username, dpchapplogin->password, refUsr)) {
		sess = new SessIdec(xchg, dbsidec, jref, refUsr, ip);
		sesss.push_back(sess);

		xchg->appendToLogfile("session created for user '" + dpchapplogin->username + "' from IP " + ip);

		*dpcheng = new DpchEngIdecConfirm(true, sess->jref, "");

	} else {
		xchg->appendToLogfile("login refused for user '" + dpchapplogin->username + "' from IP " + ip);

		*dpcheng = new DpchEngIdecConfirm(false, 0, "");
	};
};

void RootIdec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECLOGOUT) {
		call->abort = handleCallIdecLogout(dbsidec, call->jref);
	};
};

bool RootIdec::handleCallIdecLogout(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	SessIdec* sess = NULL;

	for (auto it=sesss.begin();it!=sesss.end();) {
		sess = *it;
		if (sess->jref == jrefTrig) {
			it = sesss.erase(it);
			delete sess;
			break;
		} else it++;
	};
	return retval;
};

