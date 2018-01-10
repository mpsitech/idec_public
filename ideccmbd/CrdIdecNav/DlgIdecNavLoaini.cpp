/**
  * \file DlgIdecNavLoaini.cpp
  * job handler for job DlgIdecNavLoaini (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "DlgIdecNavLoaini.h"

#include "DlgIdecNavLoaini_blks.cpp"
#include "DlgIdecNavLoaini_evals.cpp"

/******************************************************************************
 class DlgIdecNavLoaini
 ******************************************************************************/

DlgIdecNavLoaini::DlgIdecNavLoaini(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::DLGIDECNAVLOAINI, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFDse.tag = "FeedFDse";
	VecVDit::fillFeed(ixIdecVLocale, feedFDse);
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	iex = NULL;

	// IP constructor.cust1 --- INSERT

	ixVDit = VecVDit::IFI;

	iex = new IexIdecIni(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

DlgIdecNavLoaini::~DlgIdecNavLoaini() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* DlgIdecNavLoaini::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &continfimp, &feedFDse, &feedFSge, &statshr, &statshracv, &statshrifi, &statshrimp, &statshrlfi, items);
	};

	return dpcheng;
};

void DlgIdecNavLoaini::refreshIfi(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShrIfi oldStatshrifi(statshrifi);

	// IP refreshIfi --- BEGIN
	// statshrifi
	statshrifi.UldActive = evalIfiUldActive(dbsidec);

	// IP refreshIfi --- END
	if (statshrifi.diff(&oldStatshrifi).size() != 0) insert(moditems, DpchEngData::STATSHRIFI);
};

void DlgIdecNavLoaini::refreshImp(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInfImp oldContinfimp(continfimp);
	StatShrImp oldStatshrimp(statshrimp);

	// IP refreshImp --- RBEGIN
	// continfimp
	continfimp.TxtPrg = getSquawk(dbsidec);

	// statshrimp
	statshrimp.ButRunActive = evalImpButRunActive(dbsidec);
	statshrimp.ButStoActive = evalImpButStoActive(dbsidec);

	// IP refreshImp --- REND
	if (continfimp.diff(&oldContinfimp).size() != 0) insert(moditems, DpchEngData::CONTINFIMP);
	if (statshrimp.diff(&oldStatshrimp).size() != 0) insert(moditems, DpchEngData::STATSHRIMP);
};

void DlgIdecNavLoaini::refreshAcv(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShrAcv oldStatshracv(statshracv);

	// IP refreshAcv --- BEGIN
	// statshracv
	statshracv.UldActive = evalAcvUldActive(dbsidec);

	// IP refreshAcv --- END
	if (statshracv.diff(&oldStatshracv).size() != 0) insert(moditems, DpchEngData::STATSHRACV);
};

void DlgIdecNavLoaini::refreshLfi(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShrLfi oldStatshrlfi(statshrlfi);

	// IP refreshLfi --- BEGIN
	// statshrlfi
	statshrlfi.DldActive = evalLfiDldActive(dbsidec);

	// IP refreshLfi --- END
	if (statshrlfi.diff(&oldStatshrlfi).size() != 0) insert(moditems, DpchEngData::STATSHRLFI);
};

void DlgIdecNavLoaini::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.numFSge = ixVSge;

	// contiac
	contiac.numFDse = ixVDit;

	// statshr
	statshr.ButDneActive = evalButDneActive(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

	refreshIfi(dbsidec, moditems);
	refreshImp(dbsidec, moditems);
	refreshAcv(dbsidec, moditems);
	refreshLfi(dbsidec, moditems);
};

void DlgIdecNavLoaini::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::PRSIDLE: leaveSgePrsidle(dbsidec); break;
				case VecVSge::PARSE: leaveSgeParse(dbsidec); break;
				case VecVSge::ALRIDECPER: leaveSgeAlridecper(dbsidec); break;
				case VecVSge::PRSDONE: leaveSgePrsdone(dbsidec); break;
				case VecVSge::IMPIDLE: leaveSgeImpidle(dbsidec); break;
				case VecVSge::IMPORT: leaveSgeImport(dbsidec); break;
				case VecVSge::IMPDONE: leaveSgeImpdone(dbsidec); break;
				case VecVSge::UPKIDLE: leaveSgeUpkidle(dbsidec); break;
				case VecVSge::UNPACK: leaveSgeUnpack(dbsidec); break;
				case VecVSge::DONE: leaveSgeDone(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::PRSIDLE: _ixVSge = enterSgePrsidle(dbsidec, reenter); break;
			case VecVSge::PARSE: _ixVSge = enterSgeParse(dbsidec, reenter); break;
			case VecVSge::ALRIDECPER: _ixVSge = enterSgeAlridecper(dbsidec, reenter); break;
			case VecVSge::PRSDONE: _ixVSge = enterSgePrsdone(dbsidec, reenter); break;
			case VecVSge::IMPIDLE: _ixVSge = enterSgeImpidle(dbsidec, reenter); break;
			case VecVSge::IMPORT: _ixVSge = enterSgeImport(dbsidec, reenter); break;
			case VecVSge::IMPDONE: _ixVSge = enterSgeImpdone(dbsidec, reenter); break;
			case VecVSge::UPKIDLE: _ixVSge = enterSgeUpkidle(dbsidec, reenter); break;
			case VecVSge::UNPACK: _ixVSge = enterSgeUnpack(dbsidec, reenter); break;
			case VecVSge::DONE: _ixVSge = enterSgeDone(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint DlgIdecNavLoaini::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint DlgIdecNavLoaini::enterSgePrsidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRSIDLE;
	nextIxVSge = VecVSge::PARSE;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgePrsidle --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgePrsidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrsidle --- INSERT
};

uint DlgIdecNavLoaini::enterSgeParse(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PARSE;
	nextIxVSge = retval;
	// IP enterSgeParse --- IBEGIN
	ifstream ififile;

	char* buf;
	string s;

	bool ifitxt;
	bool ifixml;

	bool success;

	iex->reset();

	// check file type
	ififile.open(infilename.c_str(), ifstream::in);

	buf = new char[16];
	ififile.get(buf, 16);
	s = string(buf);

	ifitxt = (s.find("- ") == 0);
	ifixml = (s.find("<?xml") == 0);		

	delete[] buf;
	ififile.close();

	// parse file accordingly
	success = false;

	if (ifitxt) success = iex->readTxtFile(infilename);
	else if (ifixml) success = iex->readXMLFile(infilename);

	if (success) {
		retval = VecVSge::PRSDONE;
	} else {
		if (reqCmd) {
			cout << "\tparse error at line " << iex->lineno << endl;
			retval = VecVSge::IDLE;
		} else {
			retval = VecVSge::ALRIDECPER;
		};
	};
	// IP enterSgeParse --- IEND
	return retval;
};

void DlgIdecNavLoaini::leaveSgeParse(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeParse --- INSERT
};

uint DlgIdecNavLoaini::enterSgeAlridecper(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECPER;
	nextIxVSge = VecVSge::IDLE;
	// IP enterSgeAlridecper --- RBEGIN
	xchg->submitDpch(AlrIdec::prepareAlrPer(jref, ixIdecVLocale, to_string(iex->lineno), feedFMcbAlert));
	// IP enterSgeAlridecper --- REND
	return retval;
};

void DlgIdecNavLoaini::leaveSgeAlridecper(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecper --- INSERT
};

uint DlgIdecNavLoaini::enterSgePrsdone(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRSDONE;
	nextIxVSge = retval;
	// IP enterSgePrsdone --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgePrsdone(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrsdone --- INSERT
};

uint DlgIdecNavLoaini::enterSgeImpidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IMPIDLE;
	nextIxVSge = VecVSge::IMPORT;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeImpidle --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgeImpidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeImpidle --- INSERT
};

uint DlgIdecNavLoaini::enterSgeImport(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IMPORT;
	nextIxVSge = VecVSge::IMPDONE;

	if (!reenter) wrefLast = xchg->addWakeup(jref, "mon", 250000, true);
	// IP enterSgeImport --- IBEGIN
	iex->import(dbsidec);
	// IP enterSgeImport --- IEND
	retval = nextIxVSge;
	return retval;
};

void DlgIdecNavLoaini::leaveSgeImport(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeImport --- INSERT
};

uint DlgIdecNavLoaini::enterSgeImpdone(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IMPDONE;
	nextIxVSge = retval;
	// IP enterSgeImpdone --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgeImpdone(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeImpdone --- INSERT
};

uint DlgIdecNavLoaini::enterSgeUpkidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::UPKIDLE;
	nextIxVSge = VecVSge::UNPACK;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeUpkidle --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgeUpkidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeUpkidle --- INSERT
};

uint DlgIdecNavLoaini::enterSgeUnpack(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::UNPACK;
	nextIxVSge = VecVSge::DONE;
	// IP enterSgeUnpack --- IBEGIN
	ubigint ref;

	DIR* dir = NULL;
	dirent* diritem = NULL;

	string s;

	// collect refs of newly imported files
	dbsidec->tblidecqselect->removeRstByJref(jref);
	for (unsigned int ix0=0;ix0<iex->imeimfile.nodes.size();ix0++) dbsidec->tblidecqselect->insertNewRec(NULL, jref, 0, 0, iex->imeimfile.nodes[ix0]->ref);

	// handle archive file containing many (or all) files
	s = "mv " + infilename + " " + infilename + ".tgz";
	system(s.c_str());

#ifdef _WIN32
	mkdir(infilename.c_str());
#else
	mkdir(infilename.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

	// unpack
	s = "tar xzvf " + infilename + ".tgz -C " + infilename;
	system(s.c_str());

	// traverse directory and match each single file to import
	dir = opendir(infilename.c_str());

	if (dir) {
		// traverse directory
		diritem = readdir(dir);
		while (diritem) {

			if (diritem->d_type == DT_REG) {
				// file: try to match
				ref = 0;

				dbsidec->loadRefBySQL("SELECT TblIdecMFile.ref FROM TblIdecQSelect, TblIdecMFile WHERE TblIdecQSelect.jref = " + to_string(jref)
							+ " AND TblIdecMFile.ref = TblIdecQSelect.ref AND TblIdecMFile.Filename = '" + diritem->d_name + "'", ref);

				if (ref != 0) {
					Acv::alterfile(dbsidec, xchg->acvpath, infilename + "/" + diritem->d_name, ref);
					if (reqCmd) cout << "updated file '" << diritem->d_name << "'" << endl;
				};

			} else {
				// something else: do nothing
			};

			diritem = readdir(dir);
		};

		closedir(dir);
	};
	// IP enterSgeUnpack --- IEND
	retval = nextIxVSge;
	return retval;
};

void DlgIdecNavLoaini::leaveSgeUnpack(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeUnpack --- INSERT
};

uint DlgIdecNavLoaini::enterSgeDone(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::DONE;
	nextIxVSge = retval;
	// IP enterSgeDone --- INSERT
	return retval;
};

void DlgIdecNavLoaini::leaveSgeDone(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeDone --- INSERT
};

string DlgIdecNavLoaini::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- RBEGIN
	if ( (ixVSge == VecVSge::PARSE) || (ixVSge == VecVSge::ALRIDECPER) || (ixVSge == VecVSge::PRSDONE) || (ixVSge == VecVSge::IMPORT) || (ixVSge == VecVSge::IMPDONE) || (ixVSge == VecVSge::UNPACK) ) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			if (ixVSge == VecVSge::PARSE) retval = "parsing initialization data";
			else if (ixVSge == VecVSge::ALRIDECPER) retval = "parse error";
			else if (ixVSge == VecVSge::PRSDONE) retval = "initialization data parsed";
			else if (ixVSge == VecVSge::IMPORT) retval = "importing initialization data (" + to_string(iex->impcnt) + " records added)";
			else if (ixVSge == VecVSge::IMPDONE) retval = "import done";
			else if (ixVSge == VecVSge::UNPACK) retval = "unpacking inizialization files";
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			if (ixVSge == VecVSge::PARSE) retval = "lese Initialisierungsdaten ein";
			else if (ixVSge == VecVSge::ALRIDECPER) retval = "Fehler beim Einlesen";
			else if (ixVSge == VecVSge::PRSDONE) retval = "Initialisierungsdaten eingelesen";
			else if (ixVSge == VecVSge::IMPORT) retval = "importiere Initialisierungsdaten (" + to_string(iex->impcnt) + " Datens\\u00e4tze hinzugef\\u00fcgt)";
			else if (ixVSge == VecVSge::IMPDONE) retval = "Import abgeschlossen";
			else if (ixVSge == VecVSge::UNPACK) retval = "entpacke Initialisierungsdateien";
		};

	} else {
		retval = VecVSge::getSref(ixVSge);
	};
	// IP getSquawk --- REND
	return retval;
};

void DlgIdecNavLoaini::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTDNECLICK) {
					handleDpchAppDoButDneClick(dbsidec, &(req->dpcheng));
				};

			} else if (dpchappdo->ixVDoImp != 0) {
				if (dpchappdo->ixVDoImp == VecVDoImp::BUTRUNCLICK) {
					handleDpchAppDoImpButRunClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDoImp == VecVDoImp::BUTSTOCLICK) {
					handleDpchAppDoImpButStoClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::UPLOAD) {
		handleUpload(dbsidec, req->filename);

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::DOWNLOAD) {
		req->filename = handleDownload(dbsidec);

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

void DlgIdecNavLoaini::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void DlgIdecNavLoaini::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (has(diffitems, ContIac::NUMFDSE)) {
		if ((_contiac->numFDse >= VecVDit::IFI) && (_contiac->numFDse <= VecVDit::LFI)) ixVDit = _contiac->numFDse;
		refresh(dbsidec, moditems);
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void DlgIdecNavLoaini::handleDpchAppDoButDneClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButDneClick --- IBEGIN
	if (statshr.ButDneActive) {
		*dpcheng = new DpchEngIdecConfirm(true, jref, "");
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECDLGCLOSE, jref);
	};
	// IP handleDpchAppDoButDneClick --- IEND
};

void DlgIdecNavLoaini::handleDpchAppDoImpButRunClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoImpButRunClick --- BEGIN
	if (statshrimp.ButRunActive) {
		if (ixVSge == VecVSge::PRSDONE) {
			changeStage(dbsidec, VecVSge::IMPIDLE, dpcheng);
		};
	};
	// IP handleDpchAppDoImpButRunClick --- END
};

void DlgIdecNavLoaini::handleDpchAppDoImpButStoClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoImpButStoClick --- INSERT
};

void DlgIdecNavLoaini::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppIdecAlert --- IBEGIN
	if (ixVSge == VecVSge::ALRIDECPER) {
		changeStage(dbsidec, nextIxVSge);
	};
	// IP handleDpchAppIdecAlert --- IEND
};

void DlgIdecNavLoaini::handleUpload(
			DbsIdec* dbsidec
			, const string& filename
		) {
	// IP handleUpload --- BEGIN
	if (ixVSge == VecVSge::IDLE) {
		infilename = filename; // IP handleUpload.prsidle --- ILINE
		changeStage(dbsidec, VecVSge::PRSIDLE);
	} else if (ixVSge == VecVSge::IMPDONE) {
		infilename = filename; // IP handleUpload.upkidle --- ILINE
		changeStage(dbsidec, VecVSge::UPKIDLE);
	};
	// IP handleUpload --- END
};

string DlgIdecNavLoaini::handleDownload(
			DbsIdec* dbsidec
		) {
	return(""); // IP handleDownload --- LINE
};

void DlgIdecNavLoaini::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::PRSIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if (ixVSge == VecVSge::IMPIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if ((ixVSge == VecVSge::IMPORT) && (sref == "mon")) {
		wrefLast = xchg->addWakeup(jref, "mon", 250000, true);
		refreshWithDpchEng(dbsidec); // IP handleTimer.import.mon --- ILINE
	} else if (ixVSge == VecVSge::UPKIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};


