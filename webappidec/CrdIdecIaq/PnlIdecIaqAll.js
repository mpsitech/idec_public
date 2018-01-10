// IP file --- KEEP
/**
  * \file PnlIdecIaqAll.js
  * combined interactive web client functionality for card CrdIdecIaq
  * (comprises features from Mech, Qcdsp and Scill)
  * \author Alexander Wirthmueller
  * \date created: 7 Aug 2015
  * \date modified: 16 Aug 2015
  */

// --- state vector

VecVSte_IDLE = 1;

// initialize panels
VecVSte_INIT_IDLE = 2;
VecVSte_INIT_DPCHINIT_CRDIAQ = 3;
VecVSte_INIT_DPCHINIT_PNLIAQLIVE = 4;
VecVSte_INIT_DPCHINIT_PNLIAQMECH = 5;
VecVSte_INIT_DPCHINIT_PNLIAQSCILL = 6;
VecVSte_INIT_DPCHINIT_PNLIAQQCDSP = 7;
VecVSte_INIT_DPCHIAQLIVEDO_BUTREGULARIZE = 8;
VecVSte_INIT_DPCHIAQMECHDO_BUTREGULARIZE = 9;
VecVSte_INIT_DPCHIAQQCDSPDO_BUTREGULARIZE = 10;
VecVSte_INIT_ERR = 11;
VecVSte_INIT_DONE = 12;

// --- view initialization and refresh
function refresh() {
	refreshIaqLive();
	refreshIaqMech();
	refreshIaqScill();
	refreshIaqQcdsp();
};

function refreshIaqLive() {
};

function refreshIaqMech() {
	var theta = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtTheAng")); if (isNaN(theta)) theta = 0.0;
	var phi = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtPhiAng")); if (isNaN(phi)) phi = 0.0;

	// hsb and vsb
	setTextContent(contdoc, contdoc.getElementById("TxtWh"), "" + theta.toFixed(1) + "\u00b0 / " + phi.toFixed(1) + "\u00b0");
};

function refreshIaqScill() {
	var SldSpt = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", "SldSpt"));
	var SldFld = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", "SldFld"));

	refreshButicon(contdoc, "ButSciSpt", "iconidec/spot", true, SldSpt == 1.0);
	refreshButicon(contdoc, "ButSciFld", "iconidec/flood", true, SldFld == 1.0);
};

function refreshIaqQcdsp() {
	var srefIxVMode = retrieveFeedSrefByNum(srcdoc, "FeedFPupMod", retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "numFPupMod"));

	refreshButicon(contdoc, "ButQcdOff", "iconidec/qcdoff", true, srefIxVMode == "off");
	refreshButicon(contdoc, "ButQcdSingle", "iconidec/qcdsng", true, srefIxVMode == "pix");
	refreshButicon(contdoc, "ButQcdArray", "iconidec/qcdarr", true, srefIxVMode == "frm");
};

// --- event handlers

function js_OnWindowResize(widthPx, heightPx) {
	setTextContent(contdoc, contdoc.getElementById("TxtWh"), "" + widthPx + "," + heightPx);
};

function handleLoad() {
	doc = document;
	contdoc = doc.getElementById("All_cont").contentDocument;
	srcdoc = doc.getElementById("All_src").contentDocument;

	doc.scrJrefCrdIaq = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc.scrJrefPnlIaqLive = "";
	doc.scrJrefPnlIaqMech = "";
	doc.scrJrefPnlIaqScill = "";
	doc.scrJrefPnlIsqQcdsp = "";

//	js_OnWindowResize(150, 150);

	doc.ixVSte = 0;
	changeState(VecVSte_INIT_IDLE);
};

function handleButQcdOffClick() {
};

function handleButQcdSingleClick() {
};

function handleButQcdArrayClick() {
};

function handleButSciSptClick() {
};

function handleButSciFldClick() {
};

function handleHsbJpleftMov() {
};

function handleHsbJpleftMou() {
};

function handleHsbJpleftClick(evt) {
};

function handleHsbJprightMov() {
};

function handleHsbJprightMou() {
};

function handleHsbJprightClick(evt) {
};

function handleVsbJpupMov() {
};

function handleVsbJpupMou() {
};

function handleVsbJpupClick(evt) {
};

function handleVsbJpdownMov() {
};

function handleVsbJpdownMou() {
};

function handleVsbJpdownClick(evt) {
};

function handleButQcdShowClick() {
};

function handleButSnapClick() {
};

function handlePxsSet(pixel) {
};

// --- state machine

function changeState(_ixVSte) {
	while (doc.ixVSte != _ixVSte) {
		switch (doc.ixVSte) {
			case VecVSte_IDLE: leaveSteIdle(); break;

			case VecVSte_INIT_IDLE: leaveSteInit_idle(); break;
			case VecVSte_INIT_DPCHINIT_CRDIAQ: leaveSteInit_dpchinit_crdiaq(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQLIVE: leaveSteInit_dpchinit_pnliaqlive(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQMECH: leaveSteInit_dpchinit_pnliaqmech(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQSCILL: leaveSteInit_dpchinit_pnliaqscill(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQQCDSP: leaveSteInit_dpchinit_pnliaqqcdsp(); break;
			case VecVSte_INIT_DPCHIAQLIVEDO_BUTREGULARIZE: leaveSteInit_dpchiaqlivedo_butregularize(); break;
			case VecVSte_INIT_DPCHIAQMECHDO_BUTREGULARIZE: leaveSteInit_dpchiaqmechdo_butregularize(); break;
			case VecVSte_INIT_DPCHIAQQCDSPDO_BUTREGULARIZE: leaveSteInit_dpchiaqqcdspdo_butregularize(); break;
			case VecVSte_INIT_ERR: leaveSteInit_err(); break;
			case VecVSte_INIT_DONE: leaveSteInit_done(); break;
		};

		doc.ixVSte = _ixVSte;
		console.log("changed to state " + _ixVSte);
		refresh();

		switch (_ixVSte) {
			case VecVSte_IDLE: _ixVSte = enterSteIdle(); break;

			case VecVSte_INIT_IDLE: _ixVSte = enterSteInit_idle(); break;
			case VecVSte_INIT_DPCHINIT_CRDIAQ: _ixVSte = enterSteInit_dpchinit_crdiaq(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQLIVE: _ixVSte = enterSteInit_dpchinit_pnliaqlive(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQMECH: _ixVSte = enterSteInit_dpchinit_pnliaqmech(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQSCILL: _ixVSte = enterSteInit_dpchinit_pnliaqscill(); break;
			case VecVSte_INIT_DPCHINIT_PNLIAQQCDSP: _ixVSte = enterSteInit_dpchinit_pnliaqqcdsp(); break;
			case VecVSte_INIT_DPCHIAQLIVEDO_BUTREGULARIZE: _ixVSte = enterSteInit_dpchiaqlivedo_butregularize(); break;
			case VecVSte_INIT_DPCHIAQMECHDO_BUTREGULARIZE: _ixVSte = enterSteInit_dpchiaqmechdo_butregularize(); break;
			case VecVSte_INIT_DPCHIAQQCDSPDO_BUTREGULARIZE: _ixVSte = enterSteInit_dpchiaqqcdspdo_butregularize(); break;
			case VecVSte_INIT_ERR: _ixVSte = enterSteInit_err(); break;
			case VecVSte_INIT_DONE: _ixVSte = enterSteInit_done(); break;
		};

		if (_ixVSte == 0) break;
	};
};

function enterSteIdle() {
	var retval = 0;
// IP enterSteIdle --- IBEGIN
// IP enterSteIdle --- IEND
	return retval;
};

function leaveSteIdle() {
// IP leaveSteIdle --- IBEGIN
// IP leaveSteIdle --- IEND
};

function enterSteInit_idle() {
	var retval = 0;
// IP enterSteInit_idle --- IBEGIN

	retval = VecVSte_INIT_DPCHINIT_CRDIAQ;

// IP enterSteInit_idle --- IEND
	return retval;
};

function leaveSteInit_idle() {
// IP leaveSteInit_idle --- IBEGIN
// IP leaveSteInit_idle --- IEND
};

function enterSteInit_dpchinit_crdiaq() {
	var retval = 0;
// IP enterSteInit_dpchinit_crdiaq --- IBEGIN

	var str = serializeDpchApp("DpchAppIdecInit", doc.scrJrefCrdIaq);
	sendReq(str, doc, handleDpchAppReply, true);

// IP enterSteInit_dpchinit_crdiaq --- IEND
	return retval;
};

function leaveSteInit_dpchinit_crdiaq() {
// IP leaveSteInit_dpchinit_crdiaq --- IBEGIN
// IP leaveSteInit_dpchinit_crdiaq --- IEND
};

function enterSteInit_dpchinit_pnliaqlive() {
	var retval = 0;
// IP enterSteInit_dpchinit_pnliaqlive --- IBEGIN

	var str = serializeDpchApp("DpchAppIdecInit", doc.scrJrefPnlIaqLive);
	sendReq(str, doc, handleDpchAppReply, true);

// IP enterSteInit_dpchinit_pnliaqlive --- IEND
	return retval;
};

function leaveSteInit_dpchinit_pnliaqlive() {
// IP leaveSteInit_dpchinit_pnliaqlive --- IBEGIN
// IP leaveSteInit_dpchinit_pnliaqlive --- IEND
};

function enterSteInit_dpchinit_pnliaqmech() {
	var retval = 0;
// IP enterSteInit_dpchinit_pnliaqmech --- IBEGIN

	var str = serializeDpchApp("DpchAppIdecInit", doc.scrJrefPnlIaqMech);
	sendReq(str, doc, handleDpchAppReply, true);

// IP enterSteInit_dpchinit_pnliaqmech --- IEND
	return retval;
};

function leaveSteInit_dpchinit_pnliaqmech() {
// IP leaveSteInit_dpchinit_pnliaqmech --- IBEGIN
// IP leaveSteInit_dpchinit_pnliaqmech --- IEND
};

function enterSteInit_dpchinit_pnliaqscill() {
	var retval = 0;
// IP enterSteInit_dpchinit_pnliaqscill --- IBEGIN

	var str = serializeDpchApp("DpchAppIdecInit", doc.scrJrefPnlIaqScill);
	sendReq(str, doc, handleDpchAppReply, true);

// IP enterSteInit_dpchinit_pnliaqscill --- IEND
	return retval;
};

function leaveSteInit_dpchinit_pnliaqscill() {
// IP leaveSteInit_dpchinit_pnliaqscill --- IBEGIN
// IP leaveSteInit_dpchinit_pnliaqscill --- IEND
};

function enterSteInit_dpchinit_pnliaqqcdsp() {
	var retval = 0;
// IP enterSteInit_dpchinit_pnliaqqcdsp --- IBEGIN

	var str = serializeDpchApp("DpchAppIdecInit", doc.scrJrefPnlIaqQcdsp);
	sendReq(str, doc, handleDpchAppReply, true);

// IP enterSteInit_dpchinit_pnliaqqcdsp --- IEND
	return retval;
};

function leaveSteInit_dpchinit_pnliaqqcdsp() {
// IP leaveSteInit_dpchinit_pnliaqqcdsp --- IBEGIN
// IP leaveSteInit_dpchinit_pnliaqqcdsp --- IEND
};

function enterSteInit_dpchiaqlivedo_butregularize() {
	var retval = 0;
// IP enterSteInit_dpchiaqlivedo_butregularize --- IBEGIN

	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqLiveDo", doc.scrJrefPnlIaqLive, "ButRegularizeClick");
	sendReq(str, doc, handleDpchAppReply);

// IP enterSteInit_dpchiaqlivedo_butregularize --- IEND
	return retval;
};

function leaveSteInit_dpchiaqlivedo_butregularize() {
// IP leaveSteInit_dpchiaqlivedo_butregularize --- IBEGIN
// IP leaveSteInit_dpchiaqlivedo_butregularize --- IEND
};

function enterSteInit_dpchiaqmechdo_butregularize() {
	var retval = 0;
// IP enterSteInit_dpchiaqmechdo_butregularize --- IBEGIN

	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqMechDo", doc.scrJrefPnlIaqMech, "ButRegularizeClick");
	sendReq(str, doc, handleDpchAppReply);

// IP enterSteInit_dpchiaqmechdo_butregularize --- IEND
	return retval;
};

function leaveSteInit_dpchiaqmechdo_butregularize() {
// IP leaveSteInit_dpchiaqmechdo_butregularize --- IBEGIN
// IP leaveSteInit_dpchiaqmechdo_butregularize --- IEND
};

function enterSteInit_dpchiaqqcdspdo_butregularize() {
	var retval = 0;
// IP enterSteInit_dpchiaqqcdspdo_butregularize --- IBEGIN

	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqQcdspDo", doc.scrJrefPnlIaqQcdsp, "ButRegularizeClick");
	sendReq(str, doc, handleDpchAppReply);

// IP enterSteInit_dpchiaqqcdspdo_butregularize --- IEND
	return retval;
};

function leaveSteInit_dpchiaqqcdspdo_butregularize() {
// IP leaveSteInit_dpchiaqqcdspdo_butregularize --- IBEGIN
// IP leaveSteInit_dpchiaqqcdspdo_butregularize --- IEND
};

function enterSteInit_err() {
	var retval = 0;
// IP enterSteInit_err --- IBEGIN
// IP enterSteInit_err --- IEND
	return retval;
};

function leaveSteInit_err() {
// IP leaveSteInit_err --- IBEGIN
// IP leaveSteInit_err --- IEND
};

function enterSteInit_done() {
	var retval = 0;
// IP enterSteInit_done --- IBEGIN

	iterateNotify();
	retval = VecVSte_IDLE;

// IP enterSteInit_done --- IEND
	return retval;
};

function leaveSteInit_done() {
// IP leaveSteInit_done --- IBEGIN
// IP leaveSteInit_done --- IEND
};

// --- server interaction
function mergeDpchEngIdecIaqData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqData", "StatShrIdecIaq", srcdoc)) mask.push("statshr");

	if (mask.indexOf("statshr") != -1) return true;
	return false;
};

function mergeDpchEngIdecIaqLiveData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "StatShrIdecIaqLive", srcdoc)) mask.push("statshr");

	if (mask.indexOf("statshr") != -1) return true;
	return false;
};

function mergeDpchEngIdecIaqMechData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "ContIacIdecIaqMech", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "ContInfIdecIaqMech", srcdoc)) mask.push("continf"); // e.g. for ButMasterOn
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "StatShrIdecIaqMech", srcdoc)) mask.push("statshr");

	if ((mask.indexOf("contiac") != -1) || (mask.indexOf("continf") != -1) || (mask.indexOf("statshr") != -1)) return true;
	return false;
};

function mergeDpchEngIdecIaqScillData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "ContIacIdecIaqScill", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "ContInfIdecIaqScill", srcdoc)) mask.push("continf"); // e.g. for ButMasterOn
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "StatShrIdecIaqScill", srcdoc)) mask.push("statshr");

	if ((mask.indexOf("contiac") != -1) || (mask.indexOf("continf") != -1) || (mask.indexOf("statshr") != -1)) return true;
	return false;
};

function mergeDpchEngIdecIaqQcdspData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "ContIacIdecIaqQcdsp", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "ContInfIdecIaqQcdsp", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "FeedFPupMod", srcdoc)) mask.push("feedFPupMod");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "StatShrIdecIaqQcdsp", srcdoc)) mask.push("statshr");

	if ((mask.indexOf("contiac") != -1) || (mask.indexOf("continf") != -1) || (mask.indexOf("feedFPupMod") != -1) || (mask.indexOf("statshr") != -1)) return true;
	return false;
};

// should pass scrJref, mask (?) along
function handleDpchEngInit(dom, dpch) {
	var skipRefresh = false;

	var scrJref = retrieveValue(dom, "//idec:*/idec:scrJref");

	if (doc.ixVSte == VecVSte_INIT_DPCHINIT_CRDIAQ) {
		if ((dpch == "DpchEngIdecIaqData") && (scrJref == doc.scrJrefCrdIaq)) {
//			if (has("statshr")) {
				doc.scrJrefPnlIaqLive = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefLive");
				doc.scrJrefPnlIaqMech = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefMech");
				doc.scrJrefPnlIaqScill = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefScill");
				doc.scrJrefPnlIaqQcdsp = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefQcdsp");

				changeState(VecVSte_INIT_DPCHINIT_PNLIAQLIVE);
				skipRefresh = true;
//			};
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHINIT_PNLIAQLIVE) {
		if ((dpch == "DpchEngIdecIaqLiveData") && (scrJref == doc.scrJrefPnlIaqLive)) {
//			if (has("statshr")) {
				changeState(VecVSte_INIT_DPCHINIT_PNLIAQMECH);
				skipRefresh = true;
//			};
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHINIT_PNLIAQMECH) {
		if ((dpch == "DpchEngIdecIaqMechData") && (scrJref == doc.scrJrefPnlIaqMech)) {
//			if (has("statshr")) {
				changeState(VecVSte_INIT_DPCHINIT_PNLIAQSCILL);
				skipRefresh = true;
//			};
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHINIT_PNLIAQSCILL) {
		if ((dpch == "DpchEngIdecIaqScillData") && (scrJref == doc.scrJrefPnlIaqScill)) {
//			if (has("statshr")) {
				changeState(VecVSte_INIT_DPCHINIT_PNLIAQQCDSP);
				skipRefresh = true;
//			};
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHINIT_PNLIAQQCDSP) {
		if ((dpch == "DpchEngIdecIaqQcdspData") && (scrJref == doc.scrJrefPnlIaqQcdsp)) {
//			if (has("statshr")) {
				changeState(VecVSte_INIT_DPCHIAQLIVEDO_BUTREGULARIZE);
				skipRefresh = true;
//			};
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHIAQLIVEDO_BUTREGULARIZE) {
		if (retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate") == "regd") {
			changeState(VecVSte_INIT_DPCHIAQMECHDO_BUTREGULARIZE);
			skipRefresh = true;
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHIAQMECHDO_BUTREGULARIZE) {
		if (retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate") == "regd") {
			changeState(VecVSte_INIT_DPCHIAQQCDSPDO_BUTREGULARIZE);
			skipRefresh = true;
		};

	} else if (doc.ixVSte == VecVSte_INIT_DPCHIAQQCDSPDO_BUTREGULARIZE) {
		if (retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate") == "regd") {
			changeState(VecVSte_INIT_DONE);
			skipRefresh = true;
		};
	};

	return skipRefresh;
};

function handleDpchEng(dom, dpch) {
	var _refresh = true;

	var scrJref = retrieveValue(dom, "//idec:*/idec:scrJref");

	// --- merge data blocks
	if ((dpch == "DpchEngIdecIaqData") && (scrJref == doc.scrJrefCrdIaq)) {
		_refresh = mergeDpchEngIdecIaqData(dom);
	} if ((dpch == "DpchEngIdecIaqLiveData") && (scrJref == doc.scrJrefPnlIaqLive)) {
		_refresh = mergeDpchEngIdecIaqLiveData(dom);
	} else if ((dpch == "DpchEngIdecIaqMechData") && (scrJref == doc.scrJrefPnlIaqMech)) {
		_refresh = mergeDpchEngIdecIaqMechData(dom);
	} else if ((dpch == "DpchEngIdecIaqScillData") && (scrJref == doc.scrJrefPnlIaqScill)) {
		_refresh = mergeDpchEngIdecIaqScillData(dom);
	} else if ((dpch == "DpchEngIdecIaqQcdspData") && (scrJref == doc.scrJrefPnlIaqQcdsp)) {
		_refresh = mergeDpchEngIdecIaqQcdspData(dom);
	};

	// --- process state-related dispatches
	if ((doc.ixVSte >= VecVSte_INIT_IDLE) && (doc.ixVSte <= VecVSte_INIT_DONE)) {
		if (handleDpchEngInit(dom, dpch)) _refresh = false;
	};

	if (_refresh) refresh();

	// --- process other dispatches
	if ((dpch == "DpchEngIdecIaqMechLive") && (scrJref == doc.scrJrefPnlIaqMech)) {
		if (updateSrcblock(dom, "DpchEngIdecIaqMechLive", "ContInfIdecIaqMech", srcdoc)) {
			refreshIaqMech();
		};
	};
};

function handleDpchAppReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		// check dispatch type
		blk = retrieveBlock(dom, "//idec:*");

		if (blk) handleDpchEng(dom, blk.nodeName);
	};
};

function dpchEngConfirmAccepted(dom, dpch, scrJref) {
	var accepted = false;

	if (dpch == "DpchEngIdecConfirm") {
		accepted = (retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted") == "true");
		if (accepted && (scrJref != "")) accepted = (retrieveValue(dom, "//idec:*/idec:scrJref") == scrJref);
	};

	return accepted;
};

function dpchEngConfirmDenied(dom, dpch, scrJref) {
	var denied = false;

	if (dpch == "DpchEngIdecConfirm") {
		denied = (retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted") == "false");
		if (denied && (scrJref != "")) denied = (retrieveValue(dom, "//idec:*/idec:scrJref") == scrJref);
	};

	return denied;
};

function iterateNotify(ev) {
	var iterate = true;

	if (doc.reqit && ev) {
		if (doc.reqit.readyState != 4) {
			iterate = false;

		} else if ((doc.reqit.readyState == 4) && (doc.reqit.status == 404)) {
			iterate = false;
			// terminate();

		} else if (doc.reqit.readyState == 4) {
			dom = doc.reqit.responseXML;

			// check dispatch type
			blk = retrieveBlock(dom, "//idec:*");

			if (blk) {
				if (blk.nodeName == "DpchEngIdecAck") {
					// no news
				} else {
					// request with content
					if (dpchEngConfirmDenied(dom, blk.nodeName, doc.scrJrefCrdIaq)) {
						iterate = false;
						// terminate();
					} else {
						handleDpchEng(dom, blk.nodeName);
					};
				};
			};
		};
	};

	if (iterate) {
		// send notify request
		if (!doc.reqit) doc.reqit = new XMLHttpRequest();
		doc.reqit.onreadystatechange = iterateNotify;
		doc.reqit.open("GET", "/notify/" + doc.scrJrefCrdIaq, true);
		doc.reqit.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		doc.reqit.send("");
	};
};

/*
->DpchInit{scrJrefCrdiaq}
<-StatShrCrdiaq (live, mech, scill, qcdsp)
... init all others ...

QCD 3 icons: relate to PnlIdecIaqQcdsp.contiac.numFPupMod
LEDs 2 icons: relate to PnlIdecIaqScill.SldFld, .SldSpt
Csi: relates to PnlIdecIaqQcdsp.CsiQcdSte
Colored Windows-Logo-Like button: relates to (local/app) ButShow
Snapshot button: relates to PnlIdecIaqLive.VecVDo.ButSnapClick
Scroll bars: relate to PnlIdecIaqMech
then, cus pix selector (PnlIdecIaqQcdsp)
and, lwir image display (PnlIdecIaqQcdsp)
*/

/*
function handleUnload() {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqDo", scrJref, "close");
	sendReq(str, doc);
};

function terminate() {
	if (doc.timeout) window.clearTimeout(doc.timeout);

	window.onfocus = null;
	window.onbeforeunload = null;

// IP terminate --- BEGIN
	window.open("about:blank", "_self");
// IP terminate --- END
};
*/