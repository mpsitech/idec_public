/**
  * \file Ideccmbd_exe.cpp
  * Idec combined daemon main (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Ideccmbd.h"

#include "Ideccmbd_exe.h"

/******************************************************************************
 class PrefIdeccmbd
 ******************************************************************************/

PrefIdeccmbd::PrefIdeccmbd(
			StgIdeccmbd* stgideccmbd
			, StgIdecDatabase* stgidecdatabase
			, StgIdecGeneral* stgidecgeneral
			, StgIdecHardware* stgidechardware
			, StgIdecMonitor* stgidecmonitor
			, StgIdecPath* stgidecpath
			, StgJobIdecFusion* stgjobidecfusion
			, StgJobIdecIllum* stgjobidecillum
			, StgJobIdecLwiracq* stgjobideclwiracq
			, StgJobIdecMechctl* stgjobidecmechctl
			, StgJobIdecMechctlPhi* stgjobidecmechctlphi
			, StgJobIdecMechctlTheta* stgjobidecmechctltheta
			, StgJobIdecQcdacq* stgjobidecqcdacq
			, StgJobIdecRecord* stgjobidecrecord
			, StgJobIdecSpotfind* stgjobidecspotfind
			, StgJobIdecStereo* stgjobidecstereo
			, StgJobIdecTrigger* stgjobidectrigger
			, StgJobIdecVislacq* stgjobidecvislacq
			, StgJobIdecVisracq* stgjobidecvisracq
			, const set<uint>& mask
		) : Block() {
	if (stgideccmbd) this->stgideccmbd = *stgideccmbd;
	if (stgidecdatabase) this->stgidecdatabase = *stgidecdatabase;
	if (stgidecgeneral) this->stgidecgeneral = *stgidecgeneral;
	if (stgidechardware) this->stgidechardware = *stgidechardware;
	if (stgidecmonitor) this->stgidecmonitor = *stgidecmonitor;
	if (stgidecpath) this->stgidecpath = *stgidecpath;
	if (stgjobidecfusion) this->stgjobidecfusion = *stgjobidecfusion;
	if (stgjobidecillum) this->stgjobidecillum = *stgjobidecillum;
	if (stgjobideclwiracq) this->stgjobideclwiracq = *stgjobideclwiracq;
	if (stgjobidecmechctl) this->stgjobidecmechctl = *stgjobidecmechctl;
	if (stgjobidecmechctlphi) this->stgjobidecmechctlphi = *stgjobidecmechctlphi;
	if (stgjobidecmechctltheta) this->stgjobidecmechctltheta = *stgjobidecmechctltheta;
	if (stgjobidecqcdacq) this->stgjobidecqcdacq = *stgjobidecqcdacq;
	if (stgjobidecrecord) this->stgjobidecrecord = *stgjobidecrecord;
	if (stgjobidecspotfind) this->stgjobidecspotfind = *stgjobidecspotfind;
	if (stgjobidecstereo) this->stgjobidecstereo = *stgjobidecstereo;
	if (stgjobidectrigger) this->stgjobidectrigger = *stgjobidectrigger;
	if (stgjobidecvislacq) this->stgjobidecvislacq = *stgjobidecvislacq;
	if (stgjobidecvisracq) this->stgjobidecvisracq = *stgjobidecvisracq;

	if (find(mask, ALL)) this->mask = {STGIDECCMBD, STGIDECDATABASE, STGIDECGENERAL, STGIDECHARDWARE, STGIDECMONITOR, STGIDECPATH, STGJOBIDECFUSION, STGJOBIDECILLUM, STGJOBIDECLWIRACQ, STGJOBIDECMECHCTL, STGJOBIDECMECHCTLPHI, STGJOBIDECMECHCTLTHETA, STGJOBIDECQCDACQ, STGJOBIDECRECORD, STGJOBIDECSPOTFIND, STGJOBIDECSTEREO, STGJOBIDECTRIGGER, STGJOBIDECVISLACQ, STGJOBIDECVISRACQ};
	else this->mask = mask;
};

bool PrefIdeccmbd::all(
			const set<uint>& items
		) {
	if (!find(items, STGIDECCMBD)) return false;
	if (!find(items, STGIDECDATABASE)) return false;
	if (!find(items, STGIDECGENERAL)) return false;
	if (!find(items, STGIDECHARDWARE)) return false;
	if (!find(items, STGIDECMONITOR)) return false;
	if (!find(items, STGIDECPATH)) return false;
	if (!find(items, STGJOBIDECFUSION)) return false;
	if (!find(items, STGJOBIDECILLUM)) return false;
	if (!find(items, STGJOBIDECLWIRACQ)) return false;
	if (!find(items, STGJOBIDECMECHCTL)) return false;
	if (!find(items, STGJOBIDECMECHCTLPHI)) return false;
	if (!find(items, STGJOBIDECMECHCTLTHETA)) return false;
	if (!find(items, STGJOBIDECQCDACQ)) return false;
	if (!find(items, STGJOBIDECRECORD)) return false;
	if (!find(items, STGJOBIDECSPOTFIND)) return false;
	if (!find(items, STGJOBIDECSTEREO)) return false;
	if (!find(items, STGJOBIDECTRIGGER)) return false;
	if (!find(items, STGJOBIDECVISLACQ)) return false;
	if (!find(items, STGJOBIDECVISRACQ)) return false;

	return true;
};

void PrefIdeccmbd::readXMLFromFile(
			const string& fullpath
		) {
	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;

	parseFile(fullpath, &doc, &docctx);
	readXML(docctx, "/", true);

	closeParsed(doc, docctx);
};

void PrefIdeccmbd::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "PrefIdeccmbd");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (stgideccmbd.readXML(docctx, basexpath, true)) add(STGIDECCMBD);
		if (stgidecdatabase.readXML(docctx, basexpath, true)) add(STGIDECDATABASE);
		if (stgidecgeneral.readXML(docctx, basexpath, true)) add(STGIDECGENERAL);
		if (stgidechardware.readXML(docctx, basexpath, true)) add(STGIDECHARDWARE);
		if (stgidecmonitor.readXML(docctx, basexpath, true)) add(STGIDECMONITOR);
		if (stgidecpath.readXML(docctx, basexpath, true)) add(STGIDECPATH);
		if (stgjobidecfusion.readXML(docctx, basexpath, true)) add(STGJOBIDECFUSION);
		if (stgjobidecillum.readXML(docctx, basexpath, true)) add(STGJOBIDECILLUM);
		if (stgjobideclwiracq.readXML(docctx, basexpath, true)) add(STGJOBIDECLWIRACQ);
		if (stgjobidecmechctl.readXML(docctx, basexpath, true)) add(STGJOBIDECMECHCTL);
		if (stgjobidecmechctlphi.readXML(docctx, basexpath, true)) add(STGJOBIDECMECHCTLPHI);
		if (stgjobidecmechctltheta.readXML(docctx, basexpath, true)) add(STGJOBIDECMECHCTLTHETA);
		if (stgjobidecqcdacq.readXML(docctx, basexpath, true)) add(STGJOBIDECQCDACQ);
		if (stgjobidecrecord.readXML(docctx, basexpath, true)) add(STGJOBIDECRECORD);
		if (stgjobidecspotfind.readXML(docctx, basexpath, true)) add(STGJOBIDECSPOTFIND);
		if (stgjobidecstereo.readXML(docctx, basexpath, true)) add(STGJOBIDECSTEREO);
		if (stgjobidectrigger.readXML(docctx, basexpath, true)) add(STGJOBIDECTRIGGER);
		if (stgjobidecvislacq.readXML(docctx, basexpath, true)) add(STGJOBIDECVISLACQ);
		if (stgjobidecvisracq.readXML(docctx, basexpath, true)) add(STGJOBIDECVISRACQ);
	} else {
		stgideccmbd = StgIdeccmbd();
		stgidecdatabase = StgIdecDatabase();
		stgidecgeneral = StgIdecGeneral();
		stgidechardware = StgIdecHardware();
		stgidecmonitor = StgIdecMonitor();
		stgidecpath = StgIdecPath();
		stgjobidecfusion = StgJobIdecFusion();
		stgjobidecillum = StgJobIdecIllum();
		stgjobideclwiracq = StgJobIdecLwiracq();
		stgjobidecmechctl = StgJobIdecMechctl();
		stgjobidecmechctlphi = StgJobIdecMechctlPhi();
		stgjobidecmechctltheta = StgJobIdecMechctlTheta();
		stgjobidecqcdacq = StgJobIdecQcdacq();
		stgjobidecrecord = StgJobIdecRecord();
		stgjobidecspotfind = StgJobIdecSpotfind();
		stgjobidecstereo = StgJobIdecStereo();
		stgjobidectrigger = StgJobIdecTrigger();
		stgjobidecvislacq = StgJobIdecVislacq();
		stgjobidecvisracq = StgJobIdecVisracq();
	};
};

void PrefIdeccmbd::writeXMLToFile(
			const string& fullpath
		) {
	xmlTextWriter* wr = NULL;

	startwriteFile(fullpath, &wr);
		writeXML(wr);
	closewriteFile(wr);
};

void PrefIdeccmbd::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "PrefIdeccmbd");
		if (has(STGIDECCMBD)) stgideccmbd.writeXML(wr);
		if (has(STGIDECDATABASE)) stgidecdatabase.writeXML(wr);
		if (has(STGIDECGENERAL)) stgidecgeneral.writeXML(wr);
		if (has(STGIDECHARDWARE)) stgidechardware.writeXML(wr);
		if (has(STGIDECMONITOR)) stgidecmonitor.writeXML(wr);
		if (has(STGIDECPATH)) stgidecpath.writeXML(wr);
		if (has(STGJOBIDECFUSION)) stgjobidecfusion.writeXML(wr);
		if (has(STGJOBIDECILLUM)) stgjobidecillum.writeXML(wr);
		if (has(STGJOBIDECLWIRACQ)) stgjobideclwiracq.writeXML(wr);
		if (has(STGJOBIDECMECHCTL)) stgjobidecmechctl.writeXML(wr);
		if (has(STGJOBIDECMECHCTLPHI)) stgjobidecmechctlphi.writeXML(wr);
		if (has(STGJOBIDECMECHCTLTHETA)) stgjobidecmechctltheta.writeXML(wr);
		if (has(STGJOBIDECQCDACQ)) stgjobidecqcdacq.writeXML(wr);
		if (has(STGJOBIDECRECORD)) stgjobidecrecord.writeXML(wr);
		if (has(STGJOBIDECSPOTFIND)) stgjobidecspotfind.writeXML(wr);
		if (has(STGJOBIDECSTEREO)) stgjobidecstereo.writeXML(wr);
		if (has(STGJOBIDECTRIGGER)) stgjobidectrigger.writeXML(wr);
		if (has(STGJOBIDECVISLACQ)) stgjobidecvislacq.writeXML(wr);
		if (has(STGJOBIDECVISRACQ)) stgjobidecvisracq.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class Ideccmbd
 ******************************************************************************/

Ideccmbd::Ideccmbd(
			const string& exedir
			, const bool clearAll
			, const bool startMon
		) {
	xchg = NULL;
	
	root = NULL;

	appsrv = NULL;

	initdone = false;
	init(exedir, clearAll, startMon);
};

Ideccmbd::~Ideccmbd() {
	term();
};

void Ideccmbd::init(
			const string& exedir
			, const bool clearAll
			, const bool startMon
		) {
	pthread_attr_t attr;

	srand(time(NULL));

	// 1. create exchange object
	xchg = new XchgIdeccmbd();
	xchg->exedir = exedir;

	// 2. load preferences
	loadPref();

	// 3. initialize exchange data objects
	initXchgdataJobprc();
	initXchgdataOpprc();
	JobIdecFusion::initXchgdata(xchg);
	JobIdecIllum::initXchgdata(xchg);
	JobIdecLwiracq::initXchgdata(xchg);
	JobIdecMechctl::initXchgdata(xchg);
	JobIdecQcdacq::initXchgdata(xchg);
	JobIdecSpotfind::initXchgdata(xchg);
	JobIdecStereo::initXchgdata(xchg);
	JobIdecTrigger::initXchgdata(xchg);
	JobIdecVislacq::initXchgdata(xchg);
	JobIdecVisracq::initXchgdata(xchg);

	// 4. connect to database
	dbsidec.init(xchg->stgidecdatabase.ixDbsVDbstype, xchg->stgidecdatabase.dbspath, xchg->stgidecdatabase.dbsname, xchg->stgidecdatabase.ip
			, xchg->stgidecdatabase.port, xchg->stgidecdatabase.username, xchg->stgidecdatabase.password);

	// 5. start monitoring (optional)
	if (startMon) xchg->startMon();

	// 6. establish root job
	root = new RootIdec(xchg, &dbsidec, clearAll);

	// 7. start job processor threads
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (unsigned int i=0;i<xchg->stgideccmbd.jobprcn;i++) {
		// thread
		jobprcs.push_back(0);
		pthread_create(&(jobprcs[i]), &attr, &IdeccmbdJobprc::run, (void*) xchg);
	};

	// 8. start op processor threads
	for (unsigned int i=0;i<xchg->stgideccmbd.opprcn;i++) {
		// thread
		opprcs.push_back(0);
		pthread_create(&(opprcs[i]), &attr, &IdeccmbdOpprc::run, (void*) xchg);
	};

	pthread_attr_destroy(&attr);

	// 9. start web server
	appsrv = IdeccmbdAppsrv::start(xchg);

	initdone = true;
};

void Ideccmbd::term() {
	if (initdone) {
		// 1. stop web server
		IdeccmbdAppsrv::stop(appsrv);

		// 2. end op processor threads
		for (unsigned int i=0;i<opprcs.size();i++) {
			//if (opprcs[i]) {
				pthread_cancel(opprcs[i]);
				pthread_join(opprcs[i], NULL);
			//};
		};

		// 3. end job processor threads
		for (unsigned int i=0;i<jobprcs.size();i++) {
			//if (jobprcs[i]) {
				pthread_cancel(jobprcs[i]);
				pthread_join(jobprcs[i], NULL);
			//};
		};

		// 4. delete root job
		delete root;
		root = NULL;

		// 5. clean-up exchange data objects
		JobIdecVisracq::termXchgdata(xchg);
		JobIdecVislacq::termXchgdata(xchg);
		JobIdecTrigger::termXchgdata(xchg);
		JobIdecStereo::termXchgdata(xchg);
		JobIdecSpotfind::termXchgdata(xchg);
		JobIdecQcdacq::termXchgdata(xchg);
		JobIdecMechctl::termXchgdata(xchg);
		JobIdecLwiracq::termXchgdata(xchg);
		JobIdecIllum::termXchgdata(xchg);
		JobIdecFusion::termXchgdata(xchg);
		termXchgdataOpprc();
		termXchgdataJobprc();

		// 6. store preferences
		storePref();

		// 7. delete exchange object
		delete xchg;
	};
};

void Ideccmbd::loadPref() {
	PrefIdeccmbd pref;

	pref.readXMLFromFile(xchg->exedir + "/PrefIdeccmbd.xml");

	xchg->stgideccmbd = pref.stgideccmbd;
	xchg->stgidecdatabase = pref.stgidecdatabase;
	xchg->stgidecgeneral = pref.stgidecgeneral;
	xchg->stgidechardware = pref.stgidechardware;
	xchg->stgidecmonitor = pref.stgidecmonitor;
	xchg->stgidecpath = pref.stgidecpath;
	xchg->stgjobidecfusion = pref.stgjobidecfusion;
	xchg->stgjobidecillum = pref.stgjobidecillum;
	xchg->stgjobideclwiracq = pref.stgjobideclwiracq;
	xchg->stgjobidecmechctl = pref.stgjobidecmechctl;
	xchg->stgjobidecmechctlphi = pref.stgjobidecmechctlphi;
	xchg->stgjobidecmechctltheta = pref.stgjobidecmechctltheta;
	xchg->stgjobidecqcdacq = pref.stgjobidecqcdacq;
	xchg->stgjobidecrecord = pref.stgjobidecrecord;
	xchg->stgjobidecspotfind = pref.stgjobidecspotfind;
	xchg->stgjobidecstereo = pref.stgjobidecstereo;
	xchg->stgjobidectrigger = pref.stgjobidectrigger;
	xchg->stgjobidecvislacq = pref.stgjobidecvislacq;
	xchg->stgjobidecvisracq = pref.stgjobidecvisracq;

	xchg->acvpath = xchg->stgidecpath.acvpath;
	xchg->tmppath = xchg->stgidecpath.tmppath;
	xchg->helpurl = xchg->stgidecpath.helpurl;
};

void Ideccmbd::storePref() {
	PrefIdeccmbd pref(&(xchg->stgideccmbd), &(xchg->stgidecdatabase), &(xchg->stgidecgeneral), &(xchg->stgidechardware), &(xchg->stgidecmonitor), &(xchg->stgidecpath), &(xchg->stgjobidecfusion), &(xchg->stgjobidecillum), &(xchg->stgjobideclwiracq), &(xchg->stgjobidecmechctl), &(xchg->stgjobidecmechctlphi), &(xchg->stgjobidecmechctltheta), &(xchg->stgjobidecqcdacq), &(xchg->stgjobidecrecord), &(xchg->stgjobidecspotfind), &(xchg->stgjobidecstereo), &(xchg->stgjobidectrigger), &(xchg->stgjobidecvislacq), &(xchg->stgjobidecvisracq));

	pref.writeXMLToFile(xchg->exedir + "/PrefIdeccmbd.xml");
};

void Ideccmbd::initXchgdataJobprc() {
	// IP initXchgdataJobprc --- IBEGIN

	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	XchgIdhw*& _xchgidhw = xchg->datajobprc.xchgidhw;

	if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) {
		SysIdhwBasys3Fwd* sysidhw = new SysIdhwBasys3Fwd(xchg->stgidechardware.Nretry, lround(1000.0*xchg->stgidechardware.dtpoll), &_xchgidhw);
		sysidhw->init(xchg->stgidechardware.path, xchg->stgidechardware.bps);
		_sysidhw = sysidhw;
/*

	} else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) {
		SysIdhwDspcomplex3Spi* sysidhw = new SysIdhwDspcomplex3Spi(xchg->stgidechardware.Nretry, lround(1000.0*xchg->stgidechardware.dtpoll), &_xchgidhw);
		sysidhw->init(xchg->stgidechardware.path, xchg->stgidechardware.bps);
		_sysidhw = sysidhw;
*/
	} else _sysidhw = NULL;

	Mutex::init(&(xchg->datajobprc.mFlycap), false, "xchg->datajobprc.mFlycap", "Ideccmbd", "initXchgdataJobprc");

	// IP initXchgdataJobprc --- IEND
};

void Ideccmbd::termXchgdataJobprc() {
	// IP termXchgdataJobprc --- IBEGIN
	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;

	if (_sysidhw) delete _sysidhw;

	Mutex::destroy(&(xchg->datajobprc.mFlycap), false, "xchg->datajobprc.mFlycap", "Ideccmbd", "termXchgdataJobprc");
	// IP termXchgdataJobprc --- IEND
};

void Ideccmbd::initXchgdataOpprc() {
	// IP initXchgdataOpprc --- INSERT
};

void Ideccmbd::termXchgdataOpprc() {
	// IP termXchgdataOpprc --- INSERT
};

/******************************************************************************
 main program
 ******************************************************************************/

void showSubjobs(
			XchgIdeccmbd* xchg
			, JobIdec* job
			, bool clstns
			, bool ops
			, bool presets
			, bool dcolcont
			, bool stmgrcont
			, unsigned int indent
		) {
	string id;

	// http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	string setgray = "\033[38;2;196;196;196m";
	string reset = "\033[0m";

	DcolIdec* dcol = NULL;
	StmgrIdec* stmgr = NULL;

	vector<uint> icsIdecVCall;
	vector<uint> icsVJobmask;

	vector<uint> icsIdecVPreset;
	vector<Arg> args;

	// indentation
	for (unsigned int i=0;i<indent;i++) id = id + "\t";

	// actual entry
	if (job->jrefsSub.empty()) cout << "\t" << id << "- ";
	else cout << "\t" << id << "+ ";
	cout << VecIdecVJob::getSref(job->ixIdecVJob);

	if (job->jrefMast == job->jref) cout << "/M";
	else if (job->jrefMast != 0) cout << "/S";

	cout << " (" << job->jref;

	dcol = xchg->getDcolByJref(job->jref, false);
	if (dcol) {
		cout << ", dcol";
		dcol->unlockAccess("", "showSubjobs");
	};

	stmgr = xchg->getStmgrByJref(job->jref);
	if (stmgr) {
		cout << ", stmgr";
		stmgr->unlockAccess("", "showSubjobs");
	};

	cout << ")" << endl;

	if (clstns) {
		// call listeners
		cout << setgray;

		xchg->getClstnsByJref(job->jref, false, icsIdecVCall, icsVJobmask);
		for (unsigned int i=0;i<icsIdecVCall.size();i++)
					cout << "\t\t" << id << VecIdecVCall::getSref(icsIdecVCall[i]) << " (" << Clstn::VecVJobmask::getSref(icsVJobmask[i]) << ")" << endl;

		xchg->getClstnsByJref(job->jref, true, icsIdecVCall, icsVJobmask);
		for (unsigned int i=0;i<icsIdecVCall.size();i++)
					cout << "\t\t" << id << "stmgr: " << VecIdecVCall::getSref(icsIdecVCall[i]) << endl;

		cout << reset;
	};

	if (ops) {
		// ops
		cout << setgray;

		Mutex::lock(&(job->mOps), "job(" + to_string(job->jref) + ")->mOps", "", "showSubjobs");

		for (auto it=job->ops.begin();it!=job->ops.end();it++)
					cout << "\t\t" << id << VecIdecVDpch::getSref((*it)->ixVDpch).substr(4+3) << " (" << to_string((*it)->oref) << "): " << (*it)->squawk << endl;

		Mutex::unlock(&(job->mOps), "job(" + to_string(job->jref) + ")->mOps", "", "showSubjobs");

		cout << reset;
	};

	if (presets) {
		// presettings
		cout << setgray;

		xchg->getPresetsByJref(job->jref, icsIdecVPreset, args);

		for (unsigned int i=0;i<icsIdecVPreset.size();i++)
					cout << "\t\t" << id << VecIdecVPreset::getSref(icsIdecVPreset[i]) << ": " << args[i].writeText() << endl;

		cout << reset;
	};

	if (dcolcont) {
		// dispatch collector content
		dcol = xchg->getDcolByJref(job->jref, false);

		if (dcol) {
			cout << setgray;

			for (auto it=dcol->dpchs.begin();it!=dcol->dpchs.end();it++)
						cout << "\t\t" << id << VecIdecVDpch::getSref((*it)->ixIdecVDpch) << " (" << (*it)->jref << ")" << endl;

			dcol->unlockAccess("", "showSubjobs");
			cout << reset;
		};
	};

	if (stmgrcont) {
		// stub manager content
		stmgr = xchg->getStmgrByJref(job->jref);

		if (stmgr) {
			cout << setgray;

			for (auto it=stmgr->stcch->nodes.begin();it!=stmgr->stcch->nodes.end();it++)
						cout << "\t\t" << id << VecIdecVStub::getSref(it->second->stref.ixVStub) << " (" << it->second->stref.ref << "): " << it->second->stub << endl;

			stmgr->unlockAccess("", "showSubjobs");
			cout << reset;
		};
	};

	// sub-entries
	JobIdec* subjob;
	for (auto it=job->jrefsSub.begin();it!=job->jrefsSub.end();it++) {
		subjob = xchg->getJobByJref(*it);
		if (subjob) showSubjobs(xchg, subjob, clstns, ops, presets, dcolcont, stmgrcont, indent+1);
	};
};

void handleSignal(
			int sig
		) {
	// deleting ideccmbd forces PrefIdeccmbd to be written
	if (ideccmbd) delete ideccmbd;

	exit(sig);
};

int main(
			const int argc
			, const char** argv
		) {
	char* buf = NULL;
	string exedir;
	size_t ptr;

	string s;
	bool nocp = false;
	bool clearAll = false;
	bool startMon = false;

	pthread_mutex_t mcDummy;
	pthread_cond_t cDummy;

	string cmd;

	string input;
	int iinput;

	string s_backup;

	XchgIdeccmbd* xchg;

	JobIdec* job;

	ReqIdec* req;

	ideccmbd = NULL;

	// ensure proper termination on signals such as ctrl-c
#ifndef _WIN32
	signal(SIGHUP, handleSignal);
#endif
	signal(SIGINT, handleSignal); // 2
	signal(SIGTERM, handleSignal); // 15

	// determine executable path
	buf = new char[4096];

	if (readlink("/proc/self/exe", buf, 4096) >= 1) {
		exedir = buf;

	} else {
		if (strlen(argv[0]) >= 1) {
			exedir = argv[0];

			if (exedir[0] != '/') {
				if (getcwd(buf, 4096)) {
					exedir = "/" + exedir;
					exedir = buf + exedir;
				};
			};
		};
	};

	delete[] buf;

	ptr = exedir.rfind('/');
	if ((ptr != string::npos) && (ptr > 0)) exedir = exedir.substr(0, ptr);

	// evaluate command line options
	for (int i=1;i<argc;i++) {
		s = argv[i];

		if (s == "-nocp") nocp = true;
		else if (s == "-clearAll") clearAll = true;
		else if (s == "-startMon") startMon = true;
	};

	try {
		// calls ideccmbd.init()
		ideccmbd = new Ideccmbd(exedir, clearAll, startMon);
		xchg = ideccmbd->xchg;

		// welcome message
		cout << "Welcome to ICARUSDetectorControl 0.2.1!" << endl;

		if (nocp) {
			// wait on a dummy condition
			Mutex::init(&mcDummy, false, "mcDummy", "", "main");
			Cond::init(&cDummy, "cDummy", "", "main");
			Mutex::lock(&mcDummy, "mcDummy", "", "main");
			Cond::wait(&cDummy, &mcDummy, "cDummy", "", "main");
			Mutex::unlock(&mcDummy, "mcDummy", "", "main");
			Mutex::destroy(&mcDummy, false, "mcDummy", "", "main");
			Cond::destroy(&cDummy, "cDummy", "", "main");

		} else {
			// main command loop
			while (cmd != "quit") {
				cout << "Ideccmbd >> ";
				cin >> cmd;

				if (cmd == "quit") {

				} else if (cmd == "cmdsetStd") {
					cout << "\tquit" << endl;

					cout << "\tstartMon" << endl;
					cout << "\tstopMon" << endl;

					cout << "\tshowJobs" << endl;
					cout << "\tshowSubjobs" << endl;

					cout << "\tgotoJob" << endl;
					cout << "\tgotoSupjob" << endl;

					cout << "\tshowClstns" << endl;
					cout << "\tshowOps" << endl;
					cout << "\tshowPresets" << endl;

					cout << "\tshowDcolContent" << endl;
					cout << "\tshowStmgrContent" << endl;

				} else if (cmd == "startMon") {
					xchg->startMon();

				} else if (cmd == "stopMon") {
					xchg->stopMon();

				} else if (cmd == "showJobs") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, false, false, false, false, false, 0);

				} else if (cmd == "showSubjobs") {
					job = xchg->getJobByJref(xchg->jrefCmd);
					if (job) showSubjobs(xchg, job, false, false, false, false, false, 0);

				} else if (cmd == "gotoJob") {
					cout << "\tjob reference: ";
					cin >> input;
					iinput = atoi(input.c_str());

					job = xchg->getJobByJref(iinput);

					if (job) xchg->jrefCmd = job->jref;
					else cout << "\tjob reference doesn't exist!" << endl;

				} else if (cmd == "gotoSupjob") {
					job = xchg->getJobByJref(xchg->jrefCmd);

					if (job) {
						job = xchg->getJobByJref(job->jrefSup);

						if (job) xchg->jrefCmd = job->jref;
						else cout << "\talready at topmost job!" << endl;
					};

				} else if (cmd == "showClstns") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, true, false, false, false, false, 0);

				} else if (cmd == "showOps") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, false, true, false, false, false, 0);

				} else if (cmd == "showPresets") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, false, false, true, false, false, 0);

				} else if (cmd == "showDcolContent") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, false, false, false, true, false, 0);

				} else if (cmd == "showStmgrContent") {
					job = xchg->getJobByJref(xchg->jrefRoot);
					if (job) showSubjobs(xchg, job, false, false, false, false, true, 0);

				} else {
					job = xchg->getJobByJref(xchg->jrefCmd);

					if (job) {
						req = new ReqIdec(ReqIdec::VecVBasetype::CMD, ReqIdec::VecVState::RECEIVE);
						req->cmd = cmd;
						req->jref = xchg->jrefCmd;

						xchg->addReq(req);

						s_backup = "";

						while (req->ixVState != ReqIdec::VecVState::REPLY) {
							// wait for job processor to finish or to time out
							Mutex::lock(&(req->mcReady), "req->mcReady", "", "main");
							Cond::timedwait(&(req->cReady), &(req->mcReady), 1000000, "req->cReady", "", "main");
							Mutex::unlock(&(req->mcReady), "req->mcReady", "", "main");

							if (req->ixVState == ReqIdec::VecVState::WAITPRC) {
								cout << "\twaiting for processing" << endl;

							} else if (req->ixVState == ReqIdec::VecVState::PRC) {
								s = job->getSquawk(&(ideccmbd->dbsidec));
								if (s != s_backup) {
									cout << "\t" << s << endl;
									s_backup = s;
								};
							};
						};

						delete req;
					};
				};
			};
		};

		delete ideccmbd;

	} catch (DbsException e) {
		cout << e.err << endl;
	};
	
	return(0);
};


