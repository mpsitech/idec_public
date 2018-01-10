/**
  * \file PnlIdecScfConn.cpp
  * job handler for job PnlIdecScfConn (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecScfConn.h"

#include "PnlIdecScfConn_blks.cpp"
#include "PnlIdecScfConn_evals.cpp"

/******************************************************************************
 class PnlIdecScfConn
 ******************************************************************************/

PnlIdecScfConn::PnlIdecScfConn(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECSCFCONN, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiSchHst.tag = "FeedFCsiSchHst";
	feedFCsiSchHst.appendIxSrefTitles(VecIdecVCamste::NC, "gry", VecIdecVCamste::getTitle(VecIdecVCamste::NC, ixIdecVLocale));
	feedFCsiSchHst.appendIxSrefTitles(VecIdecVCamste::READY, "grn", VecIdecVCamste::getTitle(VecIdecVCamste::READY, ixIdecVLocale));
	feedFCsiSchHst.appendIxSrefTitles(VecIdecVCamste::ACTIVE, "grn.fl", VecIdecVCamste::getTitle(VecIdecVCamste::ACTIVE, ixIdecVLocale));
	feedFCsiSchIst.tag = "FeedFCsiSchIst";
	feedFCsiSchIst.appendIxSrefTitles(VecIdecVCamste::NC, "gry", VecIdecVCamste::getTitle(VecIdecVCamste::NC, ixIdecVLocale));
	feedFCsiSchIst.appendIxSrefTitles(VecIdecVCamste::READY, "grn", VecIdecVCamste::getTitle(VecIdecVCamste::READY, ixIdecVLocale));
	feedFCsiSchIst.appendIxSrefTitles(VecIdecVCamste::ACTIVE, "grn.fl", VecIdecVCamste::getTitle(VecIdecVCamste::ACTIVE, ixIdecVLocale));
	feedFCsiSchOst.tag = "FeedFCsiSchOst";
	feedFCsiSchOst.appendIxSrefTitles(VecIdecVCamste::NC, "gry", VecIdecVCamste::getTitle(VecIdecVCamste::NC, ixIdecVLocale));
	feedFCsiSchOst.appendIxSrefTitles(VecIdecVCamste::READY, "grn", VecIdecVCamste::getTitle(VecIdecVCamste::READY, ixIdecVLocale));
	feedFCsiSchOst.appendIxSrefTitles(VecIdecVCamste::ACTIVE, "grn.fl", VecIdecVCamste::getTitle(VecIdecVCamste::ACTIVE, ixIdecVLocale));
	feedFCsiSchSp1.tag = "FeedFCsiSchSp1";
	feedFCsiSchSp2.tag = "FeedFCsiSchSp2";
	feedFCsiSchSp3.tag = "FeedFCsiSchSp3";
	feedFPupFld.tag = "FeedFPupFld";
	VecIdecVPort::appendToFeed(VecIdecVPort::LED1, feedFPupFld);
	VecIdecVPort::appendToFeed(VecIdecVPort::LED2, feedFPupFld);
	feedFPupLpa.tag = "FeedFPupLpa";
	feedFPupLsn.tag = "FeedFPupLsn";
	feedFPupLtr.tag = "FeedFPupLtr";
	VecIdecVPort::appendToFeed(VecIdecVPort::GPIO1, feedFPupLtr);
	VecIdecVPort::appendToFeed(VecIdecVPort::GPIO2, feedFPupLtr);
	feedFPupPsp.tag = "FeedFPupPsp";
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI1, feedFPupPsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI2, feedFPupPsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI3, feedFPupPsp);
	feedFPupQsp.tag = "FeedFPupQsp";
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI1, feedFPupQsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI2, feedFPupQsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI3, feedFPupQsp);
	feedFPupRpa.tag = "FeedFPupRpa";
	feedFPupRsn.tag = "FeedFPupRsn";
	feedFPupRtr.tag = "FeedFPupRtr";
	VecIdecVPort::appendToFeed(VecIdecVPort::GPIO1, feedFPupRtr);
	VecIdecVPort::appendToFeed(VecIdecVPort::GPIO2, feedFPupRtr);
	feedFPupSld.tag = "FeedFPupSld";
	VecIdecVStled::fillFeed(ixIdecVLocale, feedFPupSld);
	feedFPupSpt.tag = "FeedFPupSpt";
	VecIdecVPort::appendToFeed(VecIdecVPort::LED1, feedFPupSpt);
	VecIdecVPort::appendToFeed(VecIdecVPort::LED2, feedFPupSpt);
	feedFPupTsp.tag = "FeedFPupTsp";
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI1, feedFPupTsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI2, feedFPupTsp);
	VecIdecVPort::appendToFeed(VecIdecVPort::SPI3, feedFPupTsp);
	feedFPupVty.tag = "FeedFPupVty";
	VecIdecVCamtype::appendToFeed(VecIdecVCamtype::PGCMLN, feedFPupVty);
	VecIdecVCamtype::appendToFeed(VecIdecVCamtype::MSLIFE, feedFPupVty);

	jobillum = NULL;
	joblwiracq = NULL;
	jobmechctl = NULL;
	jobqcdacq = NULL;
	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- INSERT

	jobillum = new JobIdecIllum(xchg, dbsidec, jref, ixIdecVLocale, true);
	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, false);
	jobmechctl = new JobIdecMechctl(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobvisracq = new JobIdecVisracq(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- IBEGIN
	refreshLpaLsnRpaRsn(dbsidec, moditems);
	// IP constructor.cust3 --- IEND

};

PnlIdecScfConn::~PnlIdecScfConn() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void PnlIdecScfConn::refreshLive(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	
	Feed* feed = NULL;
	uint* num = NULL;

	// continf.numFCsiSchSp1/2/3
	continf.numFCsiSchSp1 = 0;
	continf.numFCsiSchSp2 = 0;
	continf.numFCsiSchSp3 = 0;

	// theta axis
	num = NULL;

	if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		num = &continf.numFCsiSchSp1;
	} else if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		num = &continf.numFCsiSchSp2;
	} else if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		num = &continf.numFCsiSchSp3;
	};

	if (num) *num = feed->getNumByIx(xchg->datajobidecmechctl.theIxIdecVAxisste);

	// phi axis
	num = NULL;

	if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		num = &continf.numFCsiSchSp1;
	} else if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		num = &continf.numFCsiSchSp2;
	} else if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		num = &continf.numFCsiSchSp3;
	};

	if (num) *num = feed->getNumByIx(xchg->datajobidecmechctl.phiIxIdecVAxisste);

	// QCD detector
	num = NULL;

	if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		num = &continf.numFCsiSchSp1;
	} else if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		num = &continf.numFCsiSchSp2;
	} else if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		num = &continf.numFCsiSchSp3;
	};

	if (num) *num = feed->getNumByIx(xchg->datajobidecqcdacq.ixIdecVQcdste);

	// preliminary: usbotg <-> VIS-L, usbhost <-> VIS-R
	continf.numFCsiSchOst = feedFCsiSchOst.getNumByIx(xchg->datajobidecvislacq.ixIdecVCamste);
	continf.numFCsiSchHst = feedFCsiSchHst.getNumByIx(xchg->datajobidecvisracq.ixIdecVCamste);
	continf.numFCsiSchIst = feedFCsiSchIst.getNumByIx(xchg->datajobideclwiracq.ixIdecVCamste);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

// invoke on txf enter
void PnlIdecScfConn::refreshPupLpa(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupLpa = 0;

	for (unsigned int i=0;i<feedFPupLpa.size();i++) {
		if (feedFPupLpa.getSrefByNum(i+1) == contiac.TxfLpa) {
			contiac.numFPupLpa = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfLpaValid = (contiac.numFPupLpa != 0);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshPupLsn(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupLsn = 0;

	for (unsigned int i=0;i<feedFPupLsn.size();i++) {
		if (feedFPupLsn.getSrefByNum(i+1) == contiac.TxfLsn) {
			contiac.numFPupLsn = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfLsnValid = (contiac.numFPupLsn != 0);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshPupRpa(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupRpa = 0;

	for (unsigned int i=0;i<feedFPupRpa.size();i++) {
		if (feedFPupRpa.getSrefByNum(i+1) == contiac.TxfRpa) {
			contiac.numFPupRpa = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfRpaValid = (contiac.numFPupRpa != 0);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshPupRsn(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.numFPupRsn = 0;

	for (unsigned int i=0;i<feedFPupRsn.size();i++) {
		if (feedFPupRsn.getSrefByNum(i+1) == contiac.TxfRsn) {
			contiac.numFPupRsn = i+1;
			break;
		};
	};

	// statshr
	statshr.TxfRsnValid = (contiac.numFPupRsn != 0);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

// invoke on selection in pup
void PnlIdecScfConn::refreshTxfLpa(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfLpa = feedFPupLpa.getSrefByNum(contiac.numFPupLpa);

	// statshr
	statshr.TxfLpaValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshTxfLsn(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfLsn = feedFPupLsn.getSrefByNum(contiac.numFPupLsn);

	// statshr
	statshr.TxfLsnValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshTxfRpa(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfRpa = feedFPupRpa.getSrefByNum(contiac.numFPupRpa);

	// statshr
	statshr.TxfRpaValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::refreshTxfRsn(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	StatShr oldStatshr(statshr);

	// contiac
	contiac.TxfRsn = feedFPupRsn.getSrefByNum(contiac.numFPupRsn);

	// statshr
	statshr.TxfRsnValid = true;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

// invoke in constructor
void PnlIdecScfConn::refreshLpaLsnRpaRsn(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	vector<string> paths;
	vector<string> sns;

	// feedFPupLpa, feedFPupLsn, feedFPupRpa, feedFPupRsn
	feedFPupLpa.clear();
	feedFPupLsn.clear();
	feedFPupRpa.clear();
	feedFPupRsn.clear();

	if (jobvislacq) {
		sns = jobvislacq->surveyFlycap();
		for (unsigned int i=0;i<sns.size();i++) {
			feedFPupLsn.appendIxSrefTitles(i, sns[i], sns[i]);
			feedFPupRsn.appendIxSrefTitles(i, sns[i], sns[i]);
		};

		paths = jobvislacq->surveyLifecam();
		for (unsigned int i=0;i<paths.size();i++) {
			feedFPupLpa.appendIxSrefTitles(i, paths[i], paths[i]);
			feedFPupRpa.appendIxSrefTitles(i, paths[i], paths[i]);
		};
	};

	insert(moditems, DpchEngData::FEEDFPUPLPA);
	insert(moditems, DpchEngData::FEEDFPUPLSN);
	insert(moditems, DpchEngData::FEEDFPUPRPA);
	insert(moditems, DpchEngData::FEEDFPUPRSN);

	refreshPupLpa(dbsidec, moditems);
	refreshPupLsn(dbsidec, moditems);
	refreshPupRpa(dbsidec, moditems);
	refreshPupRsn(dbsidec, moditems);
};
// IP cust --- IEND
DpchEngIdec* PnlIdecScfConn::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFCsiSchHst, &feedFCsiSchIst, &feedFCsiSchOst, &feedFCsiSchSp1, &feedFCsiSchSp2, &feedFCsiSchSp3, &feedFPupFld, &feedFPupLpa, &feedFPupLsn, &feedFPupLtr, &feedFPupPsp, &feedFPupQsp, &feedFPupRpa, &feedFPupRsn, &feedFPupRtr, &feedFPupSld, &feedFPupSpt, &feedFPupTsp, &feedFPupVty, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecScfConn::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	Feed* feed = NULL;
	string* s = NULL;

	// contiac
	ContIac oldContiac(contiac);

	contiac.numFPupTsp = feedFPupTsp.getNumByIx(xchg->stgjobidecmechctltheta.ixIdecVPort);
	contiac.numFPupPsp = feedFPupPsp.getNumByIx(xchg->stgjobidecmechctlphi.ixIdecVPort);
	contiac.numFPupVty = feedFPupVty.getNumByIx(xchg->stgjobidecvislacq.ixIdecVCamtype);
	contiac.TxfLsn = xchg->stgjobidecvislacq.serno;
	contiac.TxfLpa = xchg->stgjobidecvislacq.path;
	contiac.numFPupLtr = feedFPupLtr.getNumByIx(xchg->stgjobidecvislacq.trigIxIdecVPort);
	contiac.TxfRsn = xchg->stgjobidecvisracq.serno;
	contiac.TxfRpa = xchg->stgjobidecvisracq.path;
	contiac.numFPupRtr = feedFPupRtr.getNumByIx(xchg->stgjobidecvisracq.trigIxIdecVPort);
	contiac.numFPupQsp = feedFPupQsp.getNumByIx(xchg->stgjobidecqcdacq.ixIdecVPort);
	contiac.numFPupFld = feedFPupFld.getNumByIx(xchg->stgjobidecillum.fldIxIdecVPort);
	contiac.numFPupSpt = feedFPupSpt.getNumByIx(xchg->stgjobidecillum.sptIxIdecVPort);
	contiac.numFPupSld = feedFPupSld.getNumByIx(xchg->stgidecgeneral.ixIdecVStled);

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (jobillum) continf.ButMasterOn = (jobillum->jref == jobillum->jrefMast);
	if (continf.ButMasterOn) continf.ButMasterOn = (joblwiracq->jref == joblwiracq->jrefMast);
	if (continf.ButMasterOn) continf.ButMasterOn = (jobmechctl->jref == jobmechctl->jrefMast);
	if (continf.ButMasterOn) continf.ButMasterOn = (jobqcdacq->jref == jobqcdacq->jrefMast);
	if (continf.ButMasterOn) continf.ButMasterOn = (jobvislacq->jref == jobvislacq->jrefMast);
	if (continf.ButMasterOn) continf.ButMasterOn = (jobvisracq->jref == jobvisracq->jrefMast);

	continf.TxtIsn = xchg->stgjobideclwiracq.serno;

	// - continf.TxtSchGp1/2
	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtSchGp1 = "n.c.";
		continf.TxtSchGp2 = "n.c.";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtSchGp1 = "n.v.";
		continf.TxtSchGp2 = "n.v.";
	};

	// VIS-L camera
	s = NULL;

	if (feedFPupLtr.getIxByNum(contiac.numFPupLtr) == VecIdecVPort::GPIO1) s = &continf.TxtSchGp1;
	else if (feedFPupLtr.getIxByNum(contiac.numFPupLtr) == VecIdecVPort::GPIO2) s = &continf.TxtSchGp2;

	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "VIS-L camera";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "VIS-L-Kamera";
	};

	// VIS-R camera
	s = NULL;

	if (feedFPupRtr.getIxByNum(contiac.numFPupRtr) == VecIdecVPort::GPIO1) s = &continf.TxtSchGp1;
	else if (feedFPupRtr.getIxByNum(contiac.numFPupRtr) == VecIdecVPort::GPIO2) s = &continf.TxtSchGp2;

	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "VIS-R camera";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "VIS-R-Kamera";
	};

	// - feedFCsiSchSp1/2/3, continf.TxtSchSp1/2/3
	Feed oldFeedFCsiSchSp1(feedFCsiSchSp1);
	Feed oldFeedFCsiSchSp2(feedFCsiSchSp2);
	Feed oldFeedFCsiSchSp3(feedFCsiSchSp3);

	feedFCsiSchSp1.clear();
	feedFCsiSchSp2.clear();
	feedFCsiSchSp3.clear();

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtSchSp1 = "n.c.";
		continf.TxtSchSp2 = "n.c.";
		continf.TxtSchSp3 = "n.c.";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtSchSp1 = "n.v.";
		continf.TxtSchSp2 = "n.v.";
		continf.TxtSchSp3 = "n.v.";
	};

	// theta axis
	feed = NULL;
	s = NULL;

	if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		s = &continf.TxtSchSp1;
	} else if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		s = &continf.TxtSchSp2;
	} else if (feedFPupTsp.getIxByNum(contiac.numFPupTsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		s = &continf.TxtSchSp3;
	};

	if (feed) {
		feed->appendIxSrefTitles(VecIdecVAxisste::NC, "gry", VecIdecVAxisste::getTitle(VecIdecVAxisste::NC, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::UNCAL, "ong", VecIdecVAxisste::getTitle(VecIdecVAxisste::UNCAL, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::ACTUC, "ong.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTUC, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::READY, "grn", VecIdecVAxisste::getTitle(VecIdecVAxisste::READY, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::ACTIVE, "grn.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTIVE, ixIdecVLocale));
	};
	
	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "\\u03d1 axis";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "\\u03d1-Achse";
	};

	// phi axis
	feed = NULL;
	s = NULL;

	if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		s = &continf.TxtSchSp1;
	} else if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		s = &continf.TxtSchSp2;
	} else if (feedFPupPsp.getIxByNum(contiac.numFPupPsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		s = &continf.TxtSchSp3;
	};

	if (feed) {
		feed->appendIxSrefTitles(VecIdecVAxisste::NC, "gry", VecIdecVAxisste::getTitle(VecIdecVAxisste::NC, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::UNCAL, "ong", VecIdecVAxisste::getTitle(VecIdecVAxisste::UNCAL, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::ACTUC, "ong.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTUC, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::READY, "grn", VecIdecVAxisste::getTitle(VecIdecVAxisste::READY, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVAxisste::ACTIVE, "grn.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTIVE, ixIdecVLocale));
	};
	
	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "\\u03c6 axis";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "\\u03c6-Achse";
	};

	// QCD detector
	feed = NULL;
	s = NULL;

	if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI1) {
		feed = &feedFCsiSchSp1;
		s = &continf.TxtSchSp1;
	} else if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI2) {
		feed = &feedFCsiSchSp2;
		s = &continf.TxtSchSp2;
	} else if (feedFPupQsp.getIxByNum(contiac.numFPupQsp) == VecIdecVPort::SPI3) {
		feed = &feedFCsiSchSp3;
		s = &continf.TxtSchSp3;
	};

	if (feed) {
		feed->appendIxSrefTitles(VecIdecVQcdste::NC, "gry", VecIdecVQcdste::getTitle(VecIdecVQcdste::NC, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVQcdste::COOL, "ong", VecIdecVQcdste::getTitle(VecIdecVQcdste::COOL, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVQcdste::READY, "grn", VecIdecVQcdste::getTitle(VecIdecVQcdste::READY, ixIdecVLocale));
		feed->appendIxSrefTitles(VecIdecVQcdste::ACTIVE, "grn.fl", VecIdecVQcdste::getTitle(VecIdecVQcdste::ACTIVE, ixIdecVLocale));
	};
	
	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "QCD detector";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "QCD-Detektor";
	};

	if (feedFCsiSchSp1 != oldFeedFCsiSchSp1) insert(moditems, DpchEngData::FEEDFCSISCHSP1);
	if (feedFCsiSchSp2 != oldFeedFCsiSchSp2) insert(moditems, DpchEngData::FEEDFCSISCHSP2);
	if (feedFCsiSchSp3 != oldFeedFCsiSchSp3) insert(moditems, DpchEngData::FEEDFCSISCHSP3);

	// - continf.TxtSchLd1/2
	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtSchLd1 = "n.c.";
		continf.TxtSchLd2 = "n.c.";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtSchLd1 = "n.v.";
		continf.TxtSchLd2 = "n.v.";
	};

	// floodlight
	s = NULL;

	if (feedFPupFld.getIxByNum(contiac.numFPupFld) == VecIdecVPort::LED1) s = &continf.TxtSchLd1;
	else if (feedFPupFld.getIxByNum(contiac.numFPupFld) == VecIdecVPort::LED2) s = &continf.TxtSchLd2;

	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "floodlight";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "Scheinwerfer";
	};

	// spotlight
	s = NULL;

	if (feedFPupSpt.getIxByNum(contiac.numFPupSpt) == VecIdecVPort::LED1) s = &continf.TxtSchLd1;
	else if (feedFPupSpt.getIxByNum(contiac.numFPupSpt) == VecIdecVPort::LED2) s = &continf.TxtSchLd2;

	if (s) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) *s = "spotlight";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) *s = "Spot";
	};

	// preliminary: usbotg <-> VIS-L, usbhost <-> VIS-R
	continf.TxtSchOct = VecIdecVCamtype::getTitle(feedFPupVty.getIxByNum(contiac.numFPupVty));
	continf.TxtSchHct = VecIdecVCamtype::getTitle(feedFPupVty.getIxByNum(contiac.numFPupVty));

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtSchOps = "(VIS-L camera)";
		continf.TxtSchHps = "(VIS-R camera)";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtSchOps = "(VIS-L-Kamera)";
		continf.TxtSchHps = "(VIS-R-Kamera)";
	};

	if (feedFPupVty.getIxByNum(contiac.numFPupVty) == VecIdecVCamtype::PGCMLN) {
		if (contiac.TxfLsn.length() > 0) continf.TxtSchOps = "#" + contiac.TxfLsn + " " + continf.TxtSchOps;
		if (contiac.TxfRsn.length() > 0) continf.TxtSchHps = "#" + contiac.TxfRsn + " " + continf.TxtSchHps;
	} else if (feedFPupVty.getIxByNum(contiac.numFPupVty) == VecIdecVCamtype::MSLIFE) {
		if (contiac.TxfLpa.length() > 0) continf.TxtSchOps = contiac.TxfLpa + " " + continf.TxtSchOps;
		if (contiac.TxfRpa.length() > 0) continf.TxtSchHps = contiac.TxfRpa + " " + continf.TxtSchHps;
	};

	if (continf.TxtIsn.length() == 0) continf.TxtSchIps = ""; else continf.TxtSchIps = "#" + continf.TxtIsn;

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	refreshLive(dbsidec, moditems);

	// may refresh statshr
	refreshPupLpa(dbsidec, moditems);
	refreshPupLsn(dbsidec, moditems);
	refreshPupRpa(dbsidec, moditems);
	refreshPupRsn(dbsidec, moditems);

	// statshr
	statshr.PupTspActive = evalPupTspActive(dbsidec);
	statshr.PupPspActive = evalPupPspActive(dbsidec);
	statshr.PupVtyActive = evalPupVtyActive(dbsidec);
	statshr.PupLsnAvail = evalPupLsnAvail(dbsidec);
	statshr.PupLsnActive = evalPupLsnActive(dbsidec);
	statshr.PupLpaAvail = evalPupLpaAvail(dbsidec);
	statshr.PupLpaActive = evalPupLpaActive(dbsidec);
	statshr.PupLtrActive = evalPupLtrActive(dbsidec);
	statshr.PupRsnAvail = evalPupRsnAvail(dbsidec);
	statshr.PupRsnActive = evalPupRsnActive(dbsidec);
	statshr.PupRpaAvail = evalPupRpaAvail(dbsidec);
	statshr.PupRpaActive = evalPupRpaActive(dbsidec);
	statshr.PupRtrActive = evalPupRtrActive(dbsidec);
	statshr.TxtIsnActive = evalTxtIsnActive(dbsidec);
	statshr.PupQspActive = evalPupQspActive(dbsidec);
	statshr.PupFldActive = evalPupFldActive(dbsidec);
	statshr.PupSptActive = evalPupSptActive(dbsidec);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfConn::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFCONNDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFCONNDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecScfConn::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecScfConn::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	// jobmechctl
	if (has(diffitems, ContIac::NUMFPUPTSP)) contiac.numFPupTsp = _contiac->numFPupTsp;
	if (has(diffitems, ContIac::NUMFPUPPSP)) contiac.numFPupPsp = _contiac->numFPupPsp;

	// jobvislacq, jobvisracq
	if (has(diffitems, ContIac::NUMFPUPVTY)) {
		contiac.numFPupVty = _contiac->numFPupVty;
		jobvislacq->changeCamtype(feedFPupVty.getIxByNum(contiac.numFPupVty));
		jobvisracq->changeCamtype(feedFPupVty.getIxByNum(contiac.numFPupVty));
	};

	// jobvislacq
	if (has(diffitems, ContIac::NUMFPUPLSN)) contiac.numFPupLsn = _contiac->numFPupLsn;
	if (has(diffitems, ContIac::TXFLSN)) contiac.TxfLsn = _contiac->TxfLsn;
	if (has(diffitems, ContIac::NUMFPUPLPA)) contiac.numFPupLpa = _contiac->numFPupLpa;
	if (has(diffitems, ContIac::TXFLPA)) contiac.TxfLpa = _contiac->TxfLpa;
	if (has(diffitems, ContIac::NUMFPUPLTR)) contiac.numFPupLtr = _contiac->numFPupLtr;

	// jobvisracq
	if (has(diffitems, ContIac::NUMFPUPRSN)) contiac.numFPupRsn = _contiac->numFPupRsn;
	if (has(diffitems, ContIac::TXFRSN)) contiac.TxfRsn = _contiac->TxfRsn;
	if (has(diffitems, ContIac::NUMFPUPRPA)) contiac.numFPupRpa = _contiac->numFPupRpa;
	if (has(diffitems, ContIac::TXFRPA)) contiac.TxfRpa = _contiac->TxfRpa;
	if (has(diffitems, ContIac::NUMFPUPRTR)) contiac.numFPupRtr = _contiac->numFPupRtr;

	// jobqcdacq
	if (has(diffitems, ContIac::NUMFPUPQSP)) contiac.numFPupQsp = _contiac->numFPupQsp;

	// jobillum
	if (has(diffitems, ContIac::NUMFPUPFLD)) contiac.numFPupFld = _contiac->numFPupFld;
	if (has(diffitems, ContIac::NUMFPUPSPT)) contiac.numFPupSpt = _contiac->numFPupSpt;

	// universal
	if (has(diffitems, ContIac::NUMFPUPSLD)) contiac.numFPupSld = _contiac->numFPupSld;

	refresh(dbsidec, moditems);

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecScfConn::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobillum) if (jobillum->jref != jobillum->jrefMast) xchg->claimMaster(dbsidec, jobillum->jref);
	if (joblwiracq) if (joblwiracq->jref != joblwiracq->jrefMast) xchg->claimMaster(dbsidec, joblwiracq->jref);
	if (jobmechctl) if (jobmechctl->jref != jobmechctl->jrefMast) xchg->claimMaster(dbsidec, jobmechctl->jref);
	if (jobqcdacq) if (jobqcdacq->jref != jobqcdacq->jrefMast) xchg->claimMaster(dbsidec, jobqcdacq->jref);
	if (jobvislacq) if (jobvislacq->jref != jobvislacq->jrefMast) xchg->claimMaster(dbsidec, jobvislacq->jref);
	if (jobvisracq) if (jobvisracq->jref != jobvisracq->jrefMast) xchg->claimMaster(dbsidec, jobvisracq->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecScfConn::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecScfConn::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool PnlIdecScfConn::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool PnlIdecScfConn::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


