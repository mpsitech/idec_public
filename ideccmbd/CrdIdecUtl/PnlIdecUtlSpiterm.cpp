/**
  * \file PnlIdecUtlSpiterm.cpp
  * job handler for job PnlIdecUtlSpiterm (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUtlSpiterm.h"

#include "PnlIdecUtlSpiterm_blks.cpp"
#include "PnlIdecUtlSpiterm_evals.cpp"

/******************************************************************************
 class PnlIdecUtlSpiterm
 ******************************************************************************/

PnlIdecUtlSpiterm::PnlIdecUtlSpiterm(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUTLSPITERM, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFPupOcm.tag = "FeedFPupOcm";
	feedFPupPcm.tag = "FeedFPupPcm";
	feedFPupTrg.tag = "FeedFPupTrg";
	feedFRbuOet.tag = "FeedFRbuOet";
	VecVOcxenttype::fillFeed(ixIdecVLocale, feedFRbuOet);
	feedFRbuPet.tag = "FeedFRbuPet";
	VecVPcxenttype::fillFeed(ixIdecVLocale, feedFRbuPet);

	// IP constructor.cust1 --- IBEGIN
	unt = NULL;

	if (xchg->datajobprc.sysidhw) xchg->datajobprc.sysidhw->fillFeedFTarget(feedFPupTrg);
	// IP constructor.cust1 --- IEND

	// IP constructor.cust2 --- IBEGIN
	set<uint> moditems2;
	changeTarget(moditems2);
	// IP constructor.cust2 --- IEND

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECDEVIDHW, jref, Clstn::VecVJobmask::SELF, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecUtlSpiterm::~PnlIdecUtlSpiterm() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	if (unt) delete unt;
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void PnlIdecUtlSpiterm::changeTarget(
			set<uint>& moditems
		) {
/// unt must be NULL here (stageCtd is forbidden)
	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	Feed feed;
	Feed feed2;

	Feeditem* fi = NULL;

	utinyint tixVController;

	feedFPupOcm.clear();
	contiac.numFPupOcm = 0;

	feedFPupPcm.clear();
	contiac.numFPupPcm = 0;

	if (sysidhw) {
		sysidhw->fillFeedFController(ixVTarget, feed);

		if (feed.size() > 0) {
			for (unsigned int i=0;i<feed.size();i++) {
				tixVController = feed.getIxByNum(i+1);

				sysidhw->fillFeedFCommand(ixVTarget, tixVController, feed2);

				for (unsigned int j=0;j<feed2.size();j++) {
					fi = feed2.getByNum(j+1);

					fi->ix = ((tixVController << 8) + fi->ix);
					fi->sref = getCmdsref(fi->ix);
					fi->Title1 = fi->sref;

					feedFPupOcm.nodes.push_back(new Feeditem(*fi));
					feedFPupPcm.nodes.push_back(new Feeditem(*fi));
				};
			};

		} else {
			sysidhw->fillFeedFCommand(ixVTarget, 0, feedFPupOcm);
			sysidhw->fillFeedFCommand(ixVTarget, 0, feedFPupPcm);
		};
	};

	insert(moditems, {DpchEngData::CONTIAC,DpchEngData::FEEDFPUPOCM,DpchEngData::FEEDFPUPPCM});
};

void PnlIdecUtlSpiterm::refreshLive(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	string srefSystem = VecIdecVSystem::getSref(xchg->stgidechardware.ixIdecVSystem);
	string srefTarget = feedFPupTrg.getSrefByNum(contiac.numFPupTrg);

	// continf
	ContInf oldContinf(continf);

	if (!unt || (ixVSge == VecVSge::IDLE)) {
		continf.TxtOlg = "";
		continf.TxtIlg = "";

	} else {
		continf.TxtOlg = Ftm::stamp(lround(unt->t0)) + " connected to " + srefTarget + " via " + srefSystem + ";";
		if (outlog.size() > 20) {
			continf.TxtOlg += ";(" + to_string(outlog.size()-20) + " previous log entries)";
			for (unsigned int i=(outlog.size()-20);i<outlog.size();i++) continf.TxtOlg += ";" + outlog[i];
		} else for (unsigned int i=0;i<outlog.size();i++) continf.TxtOlg += ";" + outlog[i];

		continf.TxtIlg = Ftm::stamp(lround(unt->t0)) + " connected to " + srefTarget + " via " + srefSystem + ";";
		if (inlog.size() > 20) {
			continf.TxtIlg += ";(" + to_string(inlog.size()-20) + " previous log entries)";
			for (unsigned int i=(inlog.size()-20);i<inlog.size();i++) continf.TxtIlg += ";" + inlog[i];
		} else for (unsigned int i=0;i<inlog.size();i++) continf.TxtIlg += ";" + inlog[i];
	};

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

void PnlIdecUtlSpiterm::appendToLogfile(
			const string& filename
			, vector<string> ss
		) {
	fstream logfile;

	logfile.open(logfolder + "/" + filename, ios::out | ios::app);

	for (unsigned int i=0;i<ss.size();i++) logfile << ss[i] << endl;

	logfile.close();
};

void PnlIdecUtlSpiterm::appendToOutlog(
			Cmd* cmd
		) {
	string cmdsref;

	bool truncated;

	string s;

	if (unt) {
/*
		cmdsref = getCmdsref((cmd->tixVController << 8) + cmd->tixVCommand);

		s = "[" + to_string(unt->getDt()) + "] ";

		if ((cmd->ixVState == Cmd::VecVState::WAITINV) || (cmd->ixVState == Cmd::VecVState::WAITREV)) {
			s += "sending ";
			if (cmd->ixVState == Cmd::VecVState::WAITINV) s += to_string(cmd->getInvBuflen()+10);
			else s += "9";
			s += " bytes of data to ";
			if (cmd->ixVState == Cmd::VecVState::WAITINV) s += "invoke";
			else s += "revoke";
			s += " command " + cmdsref + " (" + to_string(cmd->cref) + ")";
			
		} else if (cmd->ixVState == Cmd::VecVState::DONE) {
			s += "command " + cmdsref + " (" + to_string(cmd->cref) + "): ";
			if (cmd->success) s += "success";
			else s += "failure";
		};

		appendToLogfile("out.log", {s, cmdsref + "(" + cmd->getInvText() + ")", cmd->getInvHex()});

		if ((cmd->ixVState == Cmd::VecVState::WAITINV) || (cmd->ixVState == Cmd::VecVState::WAITREV)) {
			truncated = false;

			s += ";" + cmdsref + "(" + cmd->getInvText(true, &truncated) + ")";
			s += ";" + cmd->getInvHex(true, &truncated);
			if (truncated) s += ";(full transcript in log file)";
		};

		outlog.push_back(s);
*/
	};
};

void PnlIdecUtlSpiterm::appendToInlog(
			Cmd* cmd
		) {
	string cmdsref;

	bool truncated;

	string s;

	if (unt) {
/*
		cmdsref = getCmdsref((cmd->tixVController << 8) + cmd->tixVCommand);

		if (cmd->Nret > 1) {
			s = "[" + to_string(unt->getDt()) + "] discarding " + to_string(cmd->Nret-1) + " sets of return data for command " + cmdsref + " (" + to_string(cmd->cref) + ")";
			appendToLogfile("in.log", {s});
			inlog.push_back(s);
		};

		s = "[" + to_string(unt->getDt()) + "] received " + to_string(cmd->getRetBuflen()+9) + " bytes of data returned from command " + cmdsref + " (" + to_string(cmd->cref) + ")";
		appendToLogfile("in.log", {s, "(" + cmd->getRetText() + ")", cmd->getRetHex()});

		truncated = false;

		s += ";" + cmd->getRetHex(true, &truncated);
		if (truncated) s += ";(full transcript in log file)";

		inlog.push_back(s);
*/
	};
};

void PnlIdecUtlSpiterm::parseCmdseq(
			vector<string>& ss
			, vector<Cmd*>& cmds
		) {
	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	string cmdsref;
	uint cmdix;

	utinyint tixVController;
	utinyint tixVCommand;

	Cmd* cmd = NULL;

	string s;

	size_t ptr;

	for (unsigned int i=0;i<cmds.size();i++) delete cmds[i];
	cmds.clear();

	if (sysidhw) {
		for (unsigned int i=0;i<ss.size();i++) {
			s = ss[i];

			if (s.length() == 0) continue;
			if (s[s.length()-1] != ')') continue;
			s = s.substr(0, s.length()-1);
			ptr = s.find('(');
			if (ptr == string::npos) continue;

			cmdix = getCmdix(s.substr(0, ptr));
			tixVController = (cmdix >> 8);
			tixVCommand = (cmdix & 0xFF);
			s = s.substr(ptr+1);

			cmd = sysidhw->getNewCmd(ixVTarget, tixVController, tixVCommand);
			if (!cmd) continue;

			cmd->parlistToParsInv(s);
			cmds.push_back(cmd);
		};
	};
};

void PnlIdecUtlSpiterm::parseHexseqs(
			vector<string>& ss
			, vector<Cmd*>& cmds
		) {
	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	utinyint tixVController;
	utinyint tixVCommand;

	Cmd* cmd = NULL;

	string s;

	for (unsigned int i=0;i<cmds.size();i++) delete cmds[i];
	cmds.clear();

	if (sysidhw) {
		for (unsigned int i=0;i<ss.size();i++) {
			s = ss[i];

			if (s.find("0x") == 0) s = s.substr(2);
			if (s.length() < 4) continue;

			tixVController = Dbe::hexToBin(s.substr(0, 2));
			tixVCommand = Dbe::hexToBin(s.substr(2, 2));

			s = s.substr(4);

			cmd = sysidhw->getNewCmd(ixVTarget, tixVController, tixVCommand);
			if (!cmd) continue;

			cmd->hexToParsInv(s);
			cmds.push_back(cmd);
		};
	};
};

void PnlIdecUtlSpiterm::parseFile(
			const string& path
			, vector<Cmd*>& cmds
		) {
	fstream infile;
	char* buf = NULL;

	vector<string> ss;
	string s;

	for (unsigned int i=0;i<cmds.size();i++) delete cmds[i];
	cmds.clear();

	buf = new char[1048576];

	infile.open(path.c_str(), ifstream::in);

	while (infile.good() && (!infile.eof())) {
		infile.getline(buf, 1048576, '\n');
		s = string(buf);

		if (s.length() > 2) ss.push_back(s);
	};

	infile.close();

	delete[] buf;

	if (ss.size() > 0) {
		if (ss[0].find("0x") == 0) parseHexseqs(ss, cmds);
		else parseCmdseq(ss, cmds);
	};
};

uint PnlIdecUtlSpiterm::getCmdix(
			const string& cmdsref
		) {
	utinyint tixVController = 0;
	utinyint tixVCommand = 0;

	size_t ptr;

	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	if (sysidhw) {
		ptr = cmdsref.find('.');

		if (ptr != string::npos) {
			tixVController = sysidhw->getTixVControllerBySref(ixVTarget, cmdsref.substr(0, ptr));
			tixVCommand = sysidhw->getTixVCommandBySref(ixVTarget, tixVController, cmdsref.substr(ptr+1));
		} else tixVCommand = sysidhw->getTixVCommandBySref(ixVTarget, 0, cmdsref);
	};

	return((tixVController << 8) + tixVCommand);
};

string PnlIdecUtlSpiterm::getCmdsref(
			const uint cmdix
		) {
	string cmdsref;

	utinyint tixVController = (cmdix >> 8);
	utinyint tixVCommand = (cmdix & 0xFF);

	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	if (sysidhw) {
		cmdsref = sysidhw->getSrefByTixVController(ixVTarget, tixVController);
		if (cmdsref != "") cmdsref += ".";
		cmdsref += sysidhw->getSrefByTixVCommand(ixVTarget, tixVController, tixVCommand);
	};

	return cmdsref;
};

void PnlIdecUtlSpiterm::callbackIdhw(
			const ubigint uref
			, const ubigint cref
			, void* arg
		) {
	ExtcallIdec* extcall = (ExtcallIdec*) arg;

	extcall->xchg->runExtcall(arg);
};

// IP cust --- IEND
DpchEngIdec* PnlIdecUtlSpiterm::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupOcm, &feedFPupPcm, &feedFPupTrg, &feedFRbuOet, &feedFRbuPet, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecUtlSpiterm::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	// continf
	ContInf oldContinf(continf);

	continf.TxtSte = getSquawk(dbsidec);

	if (ixVSge == VecVSge::IDLE) {
		continf.TxtOlf = "";
		continf.TxtIlf = "";
	} else {
		continf.TxtOlf = logfolder + "/out.log";
		continf.TxtIlf = logfolder + "/in.log";
	};

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.PupTrgActive = evalPupTrgActive(dbsidec);
	statshr.ButCctActive = evalButCctActive(dbsidec);
	statshr.ButDctActive = evalButDctActive(dbsidec);

	statshr.PupOcmAvail = (contiac.numFRbuOet == VecVPcxenttype::CSQ);

	statshr.ButOcaActive = (contiac.numFPupOcm != 0);

	statshr.TxfOcsAvail = (contiac.numFRbuOet == VecVOcxenttype::CSQ);
	statshr.TxfOhsAvail = (contiac.numFRbuOet == VecVOcxenttype::HSQ);
	statshr.TxfOfnAvail = (contiac.numFRbuOet == VecVOcxenttype::FILE);

	statshr.ButOsmActive = evalButOsmActive(dbsidec);

	statshr.RbuPetActive = evalRbuPetActive(dbsidec);

	statshr.PupPcmAvail = (contiac.numFRbuPet == VecVPcxenttype::CSQ);
	statshr.PupPcmActive = evalPupPcmActive(dbsidec);

	statshr.ButPcaActive = ((ixVSge != VecVSge::PRDEXEC) && (contiac.numFPupPcm != 0));

	statshr.TxfPcsAvail = (contiac.numFRbuPet == VecVPcxenttype::CSQ);
	statshr.TxfPhsAvail = (contiac.numFRbuPet == VecVPcxenttype::HSQ);
	statshr.TxfPfnAvail = (contiac.numFRbuPet == VecVPcxenttype::FILE);

	statshr.SldPinActive = evalSldPinActive(dbsidec);
	statshr.ButPrnActive = evalButPrnActive(dbsidec);
	statshr.ButPstActive = evalButPstActive(dbsidec);

	refreshLive(dbsidec, moditems);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecUtlSpiterm::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::CTD: leaveSgeCtd(dbsidec); break;
				case VecVSge::PRDEXEC: leaveSgePrdexec(dbsidec); break;
				case VecVSge::ERR: leaveSgeErr(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::CTD: _ixVSge = enterSgeCtd(dbsidec, reenter); break;
			case VecVSge::PRDEXEC: _ixVSge = enterSgePrdexec(dbsidec, reenter); break;
			case VecVSge::ERR: _ixVSge = enterSgeErr(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- IBEGIN
		if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng);
		// IP changeStage.refresh2 --- IEND
	} while (ixVSge != _ixVSge);
};

uint PnlIdecUtlSpiterm::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- IBEGIN

	string s;

	if (unt) {
		s = Ftm::stamp(lround(unt->t0 + unt->getDt())) + " disconnected";

		appendToLogfile("out.log", {"", s});
		appendToLogfile("in.log", {"", s});

		logfolder = "";

		outlog.clear();
		inlog.clear();

		delete unt;
		unt = NULL;
	};

	// IP enterSgeIdle --- IEND
	return retval;
};

void PnlIdecUtlSpiterm::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint PnlIdecUtlSpiterm::enterSgeCtd(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CTD;
	nextIxVSge = retval;
	// IP enterSgeCtd --- IBEGIN
/// requires a selected target and unt NULL

	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);

	string s;

	unt = sysidhw->connectToTarget(ixVTarget);

	if (unt) {
		logfolder = xchg->stgidechardware.logpath;

		time_t stamp = lround(unt->t0);
		tm* tmStamp = gmtime(&stamp);

		logfolder += "/" + to_string(tmStamp->tm_mday) + "-" + to_string(tmStamp->tm_mon+1) + "-" + to_string(tmStamp->tm_year+1900)
					+ "." + to_string(3600*tmStamp->tm_hour + 60*tmStamp->tm_min + tmStamp->tm_sec)
					+ "." + feedFPupTrg.getSrefByNum(contiac.numFPupTrg);

		mkdir(logfolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		s = Ftm::stamp(lround(unt->t0)) + " connected to " + feedFPupTrg.getSrefByNum(contiac.numFPupTrg) + " via "
					+ VecIdecVSystem::getSref(xchg->stgidechardware.ixIdecVSystem);

		appendToLogfile("out.log", {s, ""});
		appendToLogfile("in.log", {s, ""});
	};

	// IP enterSgeCtd --- IEND
	return retval;
};

void PnlIdecUtlSpiterm::leaveSgeCtd(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeCtd --- INSERT
};

uint PnlIdecUtlSpiterm::enterSgePrdexec(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRDEXEC;
	nextIxVSge = retval;
	// IP enterSgePrdexec --- INSERT
	return retval;
};

void PnlIdecUtlSpiterm::leaveSgePrdexec(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgePrdexec --- INSERT
};

uint PnlIdecUtlSpiterm::enterSgeErr(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ERR;
	nextIxVSge = retval;
	// IP enterSgeErr --- INSERT
	return retval;
};

void PnlIdecUtlSpiterm::leaveSgeErr(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeErr --- INSERT
};

string PnlIdecUtlSpiterm::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- RBEGIN
	string srefSystem = VecIdecVSystem::getSref(xchg->stgidechardware.ixIdecVSystem);
	string srefTarget = feedFPupTrg.getSrefByNum(contiac.numFPupTrg);

	if ( (ixVSge == VecVSge::IDLE) || (ixVSge == VecVSge::CTD) || (ixVSge == VecVSge::PRDEXEC) || (ixVSge == VecVSge::ERR) ) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			if (ixVSge == VecVSge::IDLE) retval = "not connected";
			else if (ixVSge == VecVSge::CTD) retval = "connected to " + srefTarget + " via " + srefSystem;
			else if (ixVSge == VecVSge::PRDEXEC) retval = "periodic execution on " + srefTarget + " via " + srefSystem;
			else if (ixVSge == VecVSge::ERR) retval = "error sending data";
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			if (ixVSge == VecVSge::IDLE) retval = "nicht verbunden";
			else if (ixVSge == VecVSge::CTD) retval = "verbunden mit " + srefTarget + " \\u00fcber " + srefSystem;
			else if (ixVSge == VecVSge::PRDEXEC) retval = "periodische Ausf\\u00fchrung auf " + srefTarget + " \\u00fcber " + srefSystem;
			else if (ixVSge == VecVSge::ERR) retval = "Fehler beim Senden von Daten";
		};

	} else {
		retval = VecVSge::getSref(ixVSge);
	};
	// IP getSquawk --- REND
	return retval;
};

void PnlIdecUtlSpiterm::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
		if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECINIT) {
			handleDpchAppIdecInit(dbsidec, (DpchAppIdecInit*) (req->dpchapp), &(req->dpcheng));

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLSPITERMDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUTLSPITERMDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTCCTCLICK) {
					handleDpchAppDoButCctClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTDCTCLICK) {
					handleDpchAppDoButDctClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTOCACLICK) {
					handleDpchAppDoButOcaClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTOSMCLICK) {
					handleDpchAppDoButOsmClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPCACLICK) {
					handleDpchAppDoButPcaClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPRNCLICK) {
					handleDpchAppDoButPrnClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPSTCLICK) {
					handleDpchAppDoButPstClick(dbsidec, &(req->dpcheng));
				};

			};

		};

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

void PnlIdecUtlSpiterm::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUtlSpiterm::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	muteRefresh = true;

	if (has(diffitems, ContIac::NUMFPUPTRG)) {
		contiac.numFPupTrg = _contiac->numFPupTrg;
		changeTarget(moditems);
	};

	if (has(diffitems, ContIac::CHKISD)) contiac.ChkIsd = _contiac->ChkIsd;

	if (has(diffitems, ContIac::NUMFRBUOET)) contiac.numFRbuOet = _contiac->numFRbuOet;
	if (has(diffitems, ContIac::NUMFPUPOCM)) contiac.numFPupOcm = _contiac->numFPupOcm;
	if (has(diffitems, ContIac::TXFOCS)) contiac.TxfOcs = _contiac->TxfOcs;
	if (has(diffitems, ContIac::TXFOHS)) contiac.TxfOhs = _contiac->TxfOhs;
	if (has(diffitems, ContIac::TXFOFN)) contiac.TxfOfn = _contiac->TxfOfn;

	if (has(diffitems, ContIac::NUMFRBUPET)) contiac.numFRbuPet = _contiac->numFRbuPet;
	if (has(diffitems, ContIac::NUMFPUPPCM)) contiac.numFPupPcm = _contiac->numFPupPcm;
	if (has(diffitems, ContIac::TXFPCS)) contiac.TxfPcs = _contiac->TxfPcs;
	if (has(diffitems, ContIac::TXFPHS)) contiac.TxfPhs = _contiac->TxfPhs;
	if (has(diffitems, ContIac::TXFPFN)) contiac.TxfPfn = _contiac->TxfPfn;
	if (has(diffitems, ContIac::SLDPIN)) contiac.SldPin = _contiac->SldPin;

	refresh(dbsidec, moditems);

	muteRefresh = false;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecUtlSpiterm::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButRegularizeClick --- BEGIN
	statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
	*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	// IP handleDpchAppDoButRegularizeClick --- END
};

void PnlIdecUtlSpiterm::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMinimizeClick --- RBEGIN
	set<uint> moditems;

	invalidateWakeups();

	statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
	insert(moditems, DpchEngData::STATSHR);

	*dpcheng = getNewDpchEng(moditems);

	changeStage(dbsidec, VecVSge::IDLE, dpcheng);
	// IP handleDpchAppDoButMinimizeClick --- REND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButCctClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButCctClick --- IBEGIN
	if (statshr.ButCctActive) {
		if (ixVSge == VecVSge::IDLE) {
			changeStage(dbsidec, VecVSge::CTD, dpcheng);
		};
	};
	// IP handleDpchAppDoButCctClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButDctClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDctClick --- IBEGIN
	if (statshr.ButDctActive) {
		if (ixVSge != VecVSge::IDLE) {
			changeStage(dbsidec, VecVSge::IDLE, dpcheng);
		};
	};
	// IP handleDpchAppDoButDctClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButOcaClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButOcaClick --- IBEGIN
	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);
	uint cmdix = feedFPupOcm.getIxByNum(contiac.numFPupOcm);

	string s;

	if (statshr.ButOcaActive) {
		if (sysidhw) {
			s = sysidhw->getCmdInvTemplate(ixVTarget, (cmdix >> 8), (cmdix & 0xFF));

			if (s != "") {
				if (contiac.TxfOcs != "") if (contiac.TxfOcs[contiac.TxfOcs.length()-1] != ';') contiac.TxfOcs += ";";
				contiac.TxfOcs += s + ";";

				*dpcheng = getNewDpchEng({DpchEngData::CONTIAC});
			};
		};
	};
	// IP handleDpchAppDoButOcaClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButOsmClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButOsmClick --- IBEGIN
	vector<string> ss;
	string s;

	vector<Cmd*> cmds;
	Cmd* cmd = NULL;

	ExtcallIdec* extcall = NULL;

	set<uint> moditems;

	if (unt) {
		if (contiac.numFRbuOet == VecVOcxenttype::CSQ) {
			// parse command sequence
			StrMod::stringToVector(contiac.TxfOcs, ss, ';');
			parseCmdseq(ss, cmds);

		} else if (contiac.numFRbuOet == VecVOcxenttype::HSQ) {
			// parse hexcode sequences
			StrMod::stringToVector(contiac.TxfOhs, ss, ';');
			parseHexseqs(ss, cmds);

		} else if (contiac.numFRbuOet == VecVOcxenttype::FILE) {
			// parse file
			parseFile(contiac.TxfOfn, cmds);
		};

		for (unsigned int i=0;i<cmds.size();i++) {
			cmd = cmds[i];

/*
			cmd->cref = unt->getNewCref();

			extcall = new ExtcallIdec(xchg, new Call(VecIdecVCall::CALLIDECDEVIDHW, jref, Arg(0, cmd->cref, {}, "", 0, 0.0, false, "", Arg::REF)));
			cmd->setCallback(callbackIdhw, (void*) extcall);
*/

			ocmds[cmd->cref] = cmd;
			oextcalls[cmd->cref] = extcall;
			
			appendToOutlog(cmd);
		};

		unt->invokeCmds(cmds);

		refreshLive(dbsidec, moditems);
		if (!moditems.empty()) xchg->submitDpch(new DpchEngLive(jref, &continf, {DpchEngLive::JREF, DpchEngLive::CONTINF}));
		moditems.clear();
	};
	// IP handleDpchAppDoButOsmClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButPcaClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPcaClick --- IBEGIN
	SysIdhw*& sysidhw = xchg->datajobprc.sysidhw;

	uint ixVTarget = feedFPupTrg.getIxByNum(contiac.numFPupTrg);
	uint cmdix = feedFPupOcm.getIxByNum(contiac.numFPupOcm);

	string s;

	if (statshr.ButPcaActive) {
		if (sysidhw) {
			s = sysidhw->getCmdInvTemplate(ixVTarget, (cmdix >> 8), (cmdix & 0xFF));

			if (s != "") {
				if (contiac.TxfPcs != "") if (contiac.TxfPcs[contiac.TxfPcs.length()-1] != ';') contiac.TxfPcs += ";";
				contiac.TxfPcs += s + ";";

				*dpcheng = getNewDpchEng({DpchEngData::CONTIAC});
			};
		};
	};
	// IP handleDpchAppDoButPcaClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButPrnClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPrnClick --- IBEGIN
	if (statshr.ButPrnActive) {
		if (ixVSge == VecVSge::CTD) {
			changeStage(dbsidec, VecVSge::PRDEXEC, dpcheng);
		};
	};
	// IP handleDpchAppDoButPrnClick --- IEND
};

void PnlIdecUtlSpiterm::handleDpchAppDoButPstClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPstClick --- IBEGIN
	if (statshr.ButPstActive) {
		if (ixVSge == VecVSge::PRDEXEC) {
			changeStage(dbsidec, VecVSge::CTD, dpcheng);
		};
	};
	// IP handleDpchAppDoButPstClick --- IEND
};

void PnlIdecUtlSpiterm::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::PRDEXEC) && (sref == "prdexec")) {
		// IP handleTimer.prdexec --- IBEGIN
		// ...
		// IP handleTimer.prdexec --- IEND
	};
};

void PnlIdecUtlSpiterm::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDEVIDHW) {
		call->abort = handleCallIdecDevidhw(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecUtlSpiterm::handleCallIdecDevidhw(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecDevidhw --- IBEGIN

	set<uint> moditems;

	Cmd* cmd = NULL;

	auto it = ocmds.find(refInv);
	if (it != ocmds.end()) {
		cmd = it->second;

		cmd->lockAccess("PnlIdecUtlSpiterm", "handleCallIdecDevidhw");

		if (cmd->ixVState == Cmd::VecVState::DONE) appendToOutlog(cmd);
		if (cmd->Nret > 0) appendToInlog(cmd);

		cmd->Nret = 0;

		if (cmd->ixVState == Cmd::VecVState::DONE) {
			auto it2 = oextcalls.find(cmd->cref);
			if (it2 != oextcalls.end()) {
				delete it2->second;
				oextcalls.erase(it2);
			};

			cmd->unlockAccess("PnlIdecUtlSpiterm", "handleCallIdecDevidhw[1]");
			delete cmd;
			ocmds.erase(it);

		} else {
			cmd->unlockAccess("PnlIdecUtlSpiterm", "handleCallIdecDevidhw[2]");
		};

		refreshLive(dbsidec, moditems);
		if (!moditems.empty()) xchg->submitDpch(new DpchEngLive(jref, &continf, {DpchEngLive::JREF, DpchEngLive::CONTINF}));
	};

	// IP handleCallIdecDevidhw --- IEND
	return retval;
};


