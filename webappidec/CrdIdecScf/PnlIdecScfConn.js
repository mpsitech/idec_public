/**
  * \file PnlIdecScfConn.js
  * web client functionality for panel PnlIdecScfConn
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive() {
	if (retrieveSi(srcdoc, "StatShrIdecScfConn", "srefIxIdecVExpstate") != "regd") return;

	refreshCsi(contcontdoc, "CsiSchSp1", srcdoc, "FeedFCsiSchSp1", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchSp1"));
	refreshCsi(contcontdoc, "CsiSchSp2", srcdoc, "FeedFCsiSchSp2", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchSp2"));
	refreshCsi(contcontdoc, "CsiSchSp3", srcdoc, "FeedFCsiSchSp3", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchSp3"));
	refreshCsi(contcontdoc, "CsiSchOst", srcdoc, "FeedFCsiSchOst", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchOst"));
	refreshCsi(contcontdoc, "CsiSchHst", srcdoc, "FeedFCsiSchHst", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchHst"));
	refreshCsi(contcontdoc, "CsiSchIst", srcdoc, "FeedFCsiSchIst", retrieveCi(srcdoc, "ContInfIdecScfConn", "numFCsiSchIst"));
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Conn", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Conn_side").setAttribute("height", "30");
	doc.getElementById("Conn_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Conn_side").src = "./PnlIdecScfConn_aside.html";
	doc.getElementById("Conn_cont").src = "./PnlIdecScfConn_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Conn_side").src = "./PnlIdecScfConn_bside.html";
	doc.getElementById("Conn_cont").src = "./PnlIdecScfConn_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Conn_side").contentDocument;
	contdoc = doc.getElementById("Conn_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfConn", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Conn_side").contentDocument;
	contdoc = doc.getElementById("Conn_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Conn_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Conn_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfConn", "Cpt"));
	initCpt(contcontdoc, "CptTsp", retrieveTi(srcdoc, "TagIdecScfConn", "CptTsp"));
	refreshPup(contcontdoc, srcdoc, "PupTsp", "", "FeedFPupTsp", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupTsp"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupTspActive"), false);
	initCpt(contcontdoc, "CptPsp", retrieveTi(srcdoc, "TagIdecScfConn", "CptPsp"));
	refreshPup(contcontdoc, srcdoc, "PupPsp", "", "FeedFPupPsp", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupPsp"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupPspActive"), false);
	initCpt(contcontdoc, "CptVty", retrieveTi(srcdoc, "TagIdecScfConn", "CptVty"));
	refreshPup(contcontdoc, srcdoc, "PupVty", "", "FeedFPupVty", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupVty"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupVtyActive"), false);
	initCpt(contcontdoc, "CptLsn", retrieveTi(srcdoc, "TagIdecScfConn", "CptLsn"));
	initCpt(contcontdoc, "CptLpa", retrieveTi(srcdoc, "TagIdecScfConn", "CptLpa"));
	initCpt(contcontdoc, "CptLtr", retrieveTi(srcdoc, "TagIdecScfConn", "CptLtr"));
	refreshPup(contcontdoc, srcdoc, "PupLtr", "", "FeedFPupLtr", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupLtr"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLtrActive"), false);
	initCpt(contcontdoc, "CptRsn", retrieveTi(srcdoc, "TagIdecScfConn", "CptRsn"));
	initCpt(contcontdoc, "CptRpa", retrieveTi(srcdoc, "TagIdecScfConn", "CptRpa"));
	initCpt(contcontdoc, "CptRtr", retrieveTi(srcdoc, "TagIdecScfConn", "CptRtr"));
	refreshPup(contcontdoc, srcdoc, "PupRtr", "", "FeedFPupRtr", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupRtr"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRtrActive"), false);
	initCpt(contcontdoc, "CptIsn", retrieveTi(srcdoc, "TagIdecScfConn", "CptIsn"));
	initCpt(contcontdoc, "CptQsp", retrieveTi(srcdoc, "TagIdecScfConn", "CptQsp"));
	refreshPup(contcontdoc, srcdoc, "PupQsp", "", "FeedFPupQsp", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupQsp"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupQspActive"), false);
	initCpt(contcontdoc, "CptFld", retrieveTi(srcdoc, "TagIdecScfConn", "CptFld"));
	refreshPup(contcontdoc, srcdoc, "PupFld", "", "FeedFPupFld", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupFld"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupFldActive"), false);
	initCpt(contcontdoc, "CptSpt", retrieveTi(srcdoc, "TagIdecScfConn", "CptSpt"));
	refreshPup(contcontdoc, srcdoc, "PupSpt", "", "FeedFPupSpt", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupSpt"), retrieveSi(srcdoc, "StatShrIdecScfConn", "PupSptActive"), false);
	initCpt(contcontdoc, "CptSld", retrieveTi(srcdoc, "TagIdecScfConn", "CptSld"));
	refreshPup(contcontdoc, srcdoc, "PupSld", "", "FeedFPupSld", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupSld"), true, false);
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate");

	if (srefIxIdecVExpstate == "mind") {
		initA();
	} else if (srefIxIdecVExpstate == "regd") {
		initBD(true);
	} else if (srefIxIdecVExpstate == "detd") {
		initBD(false);
	};
};

function refreshA() {
};

function refreshBD(bNotD) {
	var height = 667; // full cont height

	// IP refreshBD.vars --- BEGIN

	var PupTspActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupTspActive") == "true");

	var PupPspActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupPspActive") == "true");

	var PupVtyActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupVtyActive") == "true");

	var PupLsnAlt = (retrieveSi(srcdoc, "StatAppIdecScfConn", "PupLsnAlt") == "true");
	var TxfLsnValid = (retrieveSi(srcdoc, "StatShrIdecScfConn", "TxfLsnValid") == "true");
	var PupLsnAvail = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLsnAvail") == "true");
	var PupLsnActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLsnActive") == "true");

	var PupLpaAlt = (retrieveSi(srcdoc, "StatAppIdecScfConn", "PupLpaAlt") == "true");
	var TxfLpaValid = (retrieveSi(srcdoc, "StatShrIdecScfConn", "TxfLpaValid") == "true");
	var PupLpaAvail = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLpaAvail") == "true");
	var PupLpaActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLpaActive") == "true");

	var PupLtrActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupLtrActive") == "true");

	var PupRsnAlt = (retrieveSi(srcdoc, "StatAppIdecScfConn", "PupRsnAlt") == "true");
	var TxfRsnValid = (retrieveSi(srcdoc, "StatShrIdecScfConn", "TxfRsnValid") == "true");
	var PupRsnAvail = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRsnAvail") == "true");
	var PupRsnActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRsnActive") == "true");

	var PupRpaAlt = (retrieveSi(srcdoc, "StatAppIdecScfConn", "PupRpaAlt") == "true");
	var TxfRpaValid = (retrieveSi(srcdoc, "StatShrIdecScfConn", "TxfRpaValid") == "true");
	var PupRpaAvail = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRpaAvail") == "true");
	var PupRpaActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRpaActive") == "true");

	var PupRtrActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupRtrActive") == "true");

	var TxtIsnActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "TxtIsnActive") == "true");

	var PupQspActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupQspActive") == "true");

	var PupFldActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupFldActive") == "true");

	var PupSptActive = (retrieveSi(srcdoc, "StatShrIdecScfConn", "PupSptActive") == "true");

	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfConn", "ButMasterOn") == "true");

	contcontdoc.getElementById("PupTsp").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupTsp");

	contcontdoc.getElementById("PupPsp").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupPsp");

	contcontdoc.getElementById("PupVty").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupVty");

	height -= setCtlAvail(contcontdoc, "Lsn", PupLsnAvail, 25);
	if (PupLsnAvail) {
		if ( (PupLsnAlt == !contcontdoc.getElementById("TxfLsn")) || (!PupLsnAlt == !contcontdoc.getElementById("PupLsn")) ) {
			mytd = contcontdoc.getElementById("dynLsn");
			clearElem(mytd);

			if (PupLsnAlt) mytd.appendChild(makeInputTxf(contcontdoc, "TxfLsn", ""));
			else mytd.appendChild(makeSelectPup(contcontdoc, "PupLsn", ""));
		};

		if (PupLsnAlt) refreshTxf(contcontdoc, "TxfLsn", "", retrieveCi(srcdoc, "ContIacIdecScfConn", "TxfLsn"), PupLsnActive, false, TxfLsnValid);
		else refreshPup(contcontdoc, srcdoc, "PupLsn", "", "FeedFPupLsn", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupLsn"), true, false);

	};

	height -= setCtlAvail(contcontdoc, "Lpa", PupLpaAvail, 25);
	if (PupLpaAvail) {
		if ( (PupLpaAlt == !contcontdoc.getElementById("TxfLpa")) || (!PupLpaAlt == !contcontdoc.getElementById("PupLpa")) ) {
			mytd = contcontdoc.getElementById("dynLpa");
			clearElem(mytd);

			if (PupLpaAlt) mytd.appendChild(makeInputTxf(contcontdoc, "TxfLpa", ""));
			else mytd.appendChild(makeSelectPup(contcontdoc, "PupLpa", ""));
		};

		if (PupLpaAlt) refreshTxf(contcontdoc, "TxfLpa", "", retrieveCi(srcdoc, "ContIacIdecScfConn", "TxfLpa"), PupLpaActive, false, TxfLpaValid);
		else refreshPup(contcontdoc, srcdoc, "PupLpa", "", "FeedFPupLpa", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupLpa"), true, false);

	};

	contcontdoc.getElementById("PupLtr").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupLtr");

	height -= setCtlAvail(contcontdoc, "Rsn", PupRsnAvail, 25);
	if (PupRsnAvail) {
		if ( (PupRsnAlt == !contcontdoc.getElementById("TxfRsn")) || (!PupRsnAlt == !contcontdoc.getElementById("PupRsn")) ) {
			mytd = contcontdoc.getElementById("dynRsn");
			clearElem(mytd);

			if (PupRsnAlt) mytd.appendChild(makeInputTxf(contcontdoc, "TxfRsn", ""));
			else mytd.appendChild(makeSelectPup(contcontdoc, "PupRsn", ""));
		};

		if (PupRsnAlt) refreshTxf(contcontdoc, "TxfRsn", "", retrieveCi(srcdoc, "ContIacIdecScfConn", "TxfRsn"), PupRsnActive, false, TxfRsnValid);
		else refreshPup(contcontdoc, srcdoc, "PupRsn", "", "FeedFPupRsn", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupRsn"), true, false);

	};

	height -= setCtlAvail(contcontdoc, "Rpa", PupRpaAvail, 25);
	if (PupRpaAvail) {
		if ( (PupRpaAlt == !contcontdoc.getElementById("TxfRpa")) || (!PupRpaAlt == !contcontdoc.getElementById("PupRpa")) ) {
			mytd = contcontdoc.getElementById("dynRpa");
			clearElem(mytd);

			if (PupRpaAlt) mytd.appendChild(makeInputTxf(contcontdoc, "TxfRpa", ""));
			else mytd.appendChild(makeSelectPup(contcontdoc, "PupRpa", ""));
		};

		if (PupRpaAlt) refreshTxf(contcontdoc, "TxfRpa", "", retrieveCi(srcdoc, "ContIacIdecScfConn", "TxfRpa"), PupRpaActive, false, TxfRpaValid);
		else refreshPup(contcontdoc, srcdoc, "PupRpa", "", "FeedFPupRpa", retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupRpa"), true, false);

	};

	contcontdoc.getElementById("PupRtr").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupRtr");

	refreshTxt(contcontdoc, "TxtIsn", retrieveCi(srcdoc, "ContInfIdecScfConn", "TxtIsn"));

	contcontdoc.getElementById("PupQsp").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupQsp");

	contcontdoc.getElementById("PupFld").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupFld");

	contcontdoc.getElementById("PupSpt").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupSpt");

	contcontdoc.getElementById("PupSld").value = retrieveCi(srcdoc, "ContIacIdecScfConn", "numFPupSld");

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Conn", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Conn_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Conn_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Conn_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfConn", "srefIxIdecVExpstate");

	if (srefIxIdecVExpstate == "mind") {
		refreshA();
	} else if (srefIxIdecVExpstate == "regd") {
		refreshBD(true);
	} else if (srefIxIdecVExpstate == "detd") {
		refreshBD(false);
	};
};

// --- event handlers
function handleLoad() {
	scrJref = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc = document;
	srcdoc = doc.getElementById("Conn_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

function handleButRegularizeClick() {
	regularize(true);
};

function handleButMinimizeClick() {
	minimize(true);
};

// --- generalized event handlers for app controls

function handleButToggleClick(basectlsref) {
	var alt;

	if (retrieveSi(srcdoc, "StatAppIdecScfConn", basectlsref + "Alt") == "true") alt = "false"; else alt = "true";
	setSi(srcdoc, "StatAppIdecScfConn", basectlsref + "Alt", alt);

	refresh();
};

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfConnDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecScfConn", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfConnData", scrJref, "ContIacIdecScfConn");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecScfConn", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfConnData", scrJref, "ContIacIdecScfConn");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecScfConn", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfConnData", scrJref, "ContIacIdecScfConn");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "ContIacIdecScfConn", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "ContInfIdecScfConn", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchHst", srcdoc)) mask.push("feedFCsiSchHst");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchIst", srcdoc)) mask.push("feedFCsiSchIst");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchOst", srcdoc)) mask.push("feedFCsiSchOst");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchSp1", srcdoc)) mask.push("feedFCsiSchSp1");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchSp2", srcdoc)) mask.push("feedFCsiSchSp2");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFCsiSchSp3", srcdoc)) mask.push("feedFCsiSchSp3");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupFld", srcdoc)) mask.push("feedFPupFld");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupLpa", srcdoc)) mask.push("feedFPupLpa");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupLsn", srcdoc)) mask.push("feedFPupLsn");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupLtr", srcdoc)) mask.push("feedFPupLtr");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupPsp", srcdoc)) mask.push("feedFPupPsp");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupQsp", srcdoc)) mask.push("feedFPupQsp");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupRpa", srcdoc)) mask.push("feedFPupRpa");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupRsn", srcdoc)) mask.push("feedFPupRsn");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupRtr", srcdoc)) mask.push("feedFPupRtr");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupSld", srcdoc)) mask.push("feedFPupSld");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupSpt", srcdoc)) mask.push("feedFPupSpt");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupTsp", srcdoc)) mask.push("feedFPupTsp");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "FeedFPupVty", srcdoc)) mask.push("feedFPupVty");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "StatAppIdecScfConn", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "StatShrIdecScfConn", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfConnData", "TagIdecScfConn", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfConnData") {
		mergeDpchEngData(dom);
		refresh();
	} else if (dpch == "DpchEngIdecScfConnLive") {
		handleDpchEngIdecScfConnLive(dom);
	};
};

function handleDpchEngIdecScfConnLive(dom) {
// IP handleDpchEngIdecScfConnLive --- IBEGIN
	updateSrcblock(dom, "DpchEngIdecScfConnLive", "ContInfIdecScfConn", srcdoc);
	refreshLive();
// IP handleDpchEngIdecScfConnLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecScfConnData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Conn");
			};
		};
	};
};

function handleDpchAppDataDoReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		// check dispatch type
		blk = retrieveBlock(dom, "//idec:*");

		if (blk) {
			if (blk.nodeName == "DpchEngIdecConfirm") {
				// do nothing

			} else if (blk.nodeName == "DpchEngIdecScfConnData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};


