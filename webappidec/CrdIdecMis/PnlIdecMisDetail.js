/**
  * \file PnlIdecMisDetail.js
  * web client functionality for panel PnlIdecMisDetail
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize(updh) {
	if (retrieveSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate", "mind");

	// change container heights
	getRecwnd().changeHeight("Detail", 30, updh);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Detail_side").setAttribute("height", "30");
	doc.getElementById("Detail_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Detail_side").src = "./PnlIdecMisDetail_aside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecMisDetail_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Detail_side").src = "./PnlIdecMisDetail_bside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecMisDetail_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecMisDetail", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	contcontdoc = contdoc.getElementById("Detail_cont").contentDocument;
	ftrdoc = contdoc.getElementById("Detail_ftr").contentDocument;

	// IP initBD --- BEGIN
	initCpt(contcontdoc, "CptTit", retrieveTi(srcdoc, "TagIdecMisDetail", "CptTit"));
	initCpt(contcontdoc, "CptSta", retrieveTi(srcdoc, "TagIdecMisDetail", "CptSta"));
	initCpt(contcontdoc, "CptSto", retrieveTi(srcdoc, "TagIdecMisDetail", "CptSto"));
	initCpt(contcontdoc, "CptCry", retrieveTi(srcdoc, "TagIdecMisDetail", "CptCry"));
	initCpt(contcontdoc, "CptReg", retrieveTi(srcdoc, "TagIdecMisDetail", "CptReg"));
	initCpt(contcontdoc, "CptMun", retrieveTi(srcdoc, "TagIdecMisDetail", "CptMun"));
	initCpt(contcontdoc, "CptCmt", retrieveTi(srcdoc, "TagIdecMisDetail", "CptCmt"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate");

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
	var height = 242; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxfTitActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfTitActive") == "true");

	var TxfStaActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfStaActive") == "true");

	var TxfStoActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfStoActive") == "true");

	var PupCryAlt = (retrieveSi(srcdoc, "StatAppIdecMisDetail", "PupCryAlt") == "true");
	var TxfCryValid = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfCryValid") == "true");
	var PupCryActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "PupCryActive") == "true");
	var ButCryEditAvail = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "ButCryEditAvail") == "true");

	var TxfRegActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfRegActive") == "true");

	var TxfMunActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfMunActive") == "true");

	var TxfCmtActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "TxfCmtActive") == "true");

	var ButSaveActive = (retrieveSi(srcdoc, "StatShrIdecMisDetail", "ButSaveActive") == "true");
	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshTxf(contcontdoc, "TxfTit", "", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfTit"), TxfTitActive, false, true);

	refreshTxf(contcontdoc, "TxfSta", "s", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfSta"), TxfStaActive, false, true);

	refreshTxf(contcontdoc, "TxfSto", "s", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfSto"), TxfStoActive, false, true);

	if ( (PupCryAlt == !contcontdoc.getElementById("TxfCry")) || (!PupCryAlt == !contcontdoc.getElementById("PupCry")) ) {
		mytd = contcontdoc.getElementById("dynCry");
		clearElem(mytd);

		if (PupCryAlt) mytd.appendChild(makeInputTxf(contcontdoc, "TxfCry", ""));
		else mytd.appendChild(makeSelectPup(contcontdoc, "PupCry", ""));
	};

	if (PupCryAlt) refreshTxf(contcontdoc, "TxfCry", "", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfCry"), PupCryActive, false, TxfCryValid);
	else refreshPup(contcontdoc, srcdoc, "PupCry", "", "FeedFPupCry", retrieveCi(srcdoc, "ContIacIdecMisDetail", "numFPupCry"), true, false);

	if ((ButCryEditAvail == !contcontdoc.getElementById("ButCryEdit"))) {
		mytd = contcontdoc.getElementById("rdynCry");
		clearElem(mytd);

		first = true;

		if (ButCryEditAvail) {
			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButCryEdit", "icon/edit"));
		};
	};

	refreshTxf(contcontdoc, "TxfReg", "", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfReg"), TxfRegActive, false, true);

	refreshTxf(contcontdoc, "TxfMun", "", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfMun"), TxfMunActive, false, true);

	refreshTxft(contcontdoc, "TxfCmt", retrieveCi(srcdoc, "ContIacIdecMisDetail", "TxfCmt"), TxfCmtActive, false, true);

	refreshButicon(ftrdoc, "ButSave", "icon/save", ButSaveActive, false);
	// IP refreshBD --- END

	getRecwnd().changeHeight("Detail", height+26, true);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+26));
	doc.getElementById("Detail_side").setAttribute("height", "" + (height+26));
	doc.getElementById("Detail_cont").setAttribute("height", "" + (height+26));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+26-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Detail_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecMisDetail", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Detail_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

function handleButMinimizeClick() {
	minimize(true);
};

function handleButRegularizeClick() {
	regularize(true);
};

// --- generalized event handlers for app controls

function handleButToggleClick(basectlsref) {
	var alt;

	if (retrieveSi(srcdoc, "StatAppIdecMisDetail", basectlsref + "Alt") == "true") alt = "false"; else alt = "true";
	setSi(srcdoc, "StatAppIdecMisDetail", basectlsref + "Alt", alt);

	refresh();
};

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecMisDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButDlgopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecMisDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoDlgopenReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecMisDetail", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecMisDetailData", scrJref, "ContIacIdecMisDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecMisDetail", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecMisDetailData", scrJref, "ContIacIdecMisDetail");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecMisDetail", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecMisDetailData", scrJref, "ContIacIdecMisDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxftKey(_doc, ctlsref, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txfmod");

	return true;
};

function handleTxftChange(_doc, ctlsref) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txfmod");

	setCi(srcdoc, "ContIacIdecMisDetail", ctlsref, elem.value.replace(/\n/g, ";"));

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecMisDetailData", scrJref, "ContIacIdecMisDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecMisDetailData", "ContIacIdecMisDetail", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecMisDetailData", "FeedFPupCry", srcdoc)) mask.push("feedFPupCry");
	if (updateSrcblock(dom, "DpchEngIdecMisDetailData", "StatAppIdecMisDetail", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecMisDetailData", "StatShrIdecMisDetail", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecMisDetailData", "TagIdecMisDetail", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecMisDetailData") {
		mergeDpchEngData(dom);
		refresh();
	};
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecMisDetailData") {
				mergeDpchEngData(dom);
				init();

				getRecwnd().setInitdone("Detail");
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

			} else if (blk.nodeName == "DpchEngIdecMisDetailData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

function handleDpchAppDoDlgopenReply() {
	var dom, blk;

	var accepted, _scrJref, sref;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");

		if (blk) {
			if (blk.nodeName == "DpchEngIdecConfirm") {
				accepted = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted");
				_scrJref = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:scrJref");
				sref = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:sref");

				if ((accepted == "true") && (sref != "")) getCrdwnd().showDlg(sref, _scrJref);
			};
		};
	};
};

