/**
  * \file PnlIdecUsgDetail.js
  * web client functionality for panel PnlIdecUsgDetail
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize(updh) {
	if (retrieveSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate", "mind");

	// change container heights
	getRecwnd().changeHeight("Detail", 30, updh);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Detail_side").setAttribute("height", "30");
	doc.getElementById("Detail_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Detail_side").src = "./PnlIdecUsgDetail_aside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecUsgDetail_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Detail_side").src = "./PnlIdecUsgDetail_bside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecUsgDetail_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecUsgDetail", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	contcontdoc = contdoc.getElementById("Detail_cont").contentDocument;
	ftrdoc = contdoc.getElementById("Detail_ftr").contentDocument;

	// IP initBD --- BEGIN
	initCpt(contcontdoc, "CptSrf", retrieveTi(srcdoc, "TagIdecUsgDetail", "CptSrf"));
	initCpt(contcontdoc, "CptCmt", retrieveTi(srcdoc, "TagIdecUsgDetail", "CptCmt"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate");

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
	var height = 117; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxtSrfActive = (retrieveSi(srcdoc, "StatShrIdecUsgDetail", "TxtSrfActive") == "true");

	var TxfCmtActive = (retrieveSi(srcdoc, "StatShrIdecUsgDetail", "TxfCmtActive") == "true");

	var ButSaveActive = (retrieveSi(srcdoc, "StatShrIdecUsgDetail", "ButSaveActive") == "true");
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshTxt(contcontdoc, "TxtSrf", retrieveCi(srcdoc, "ContInfIdecUsgDetail", "TxtSrf"));

	refreshTxft(contcontdoc, "TxfCmt", retrieveCi(srcdoc, "ContIacIdecUsgDetail", "TxfCmt"), TxfCmtActive, false, true);

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
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecUsgDetail", "srefIxIdecVExpstate");

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

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUsgDetailDo", scrJref, ctlsref + "Click");
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

	setCi(srcdoc, "ContIacIdecUsgDetail", ctlsref, elem.value.replace(/\n/g, ";"));

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUsgDetailData", scrJref, "ContIacIdecUsgDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecUsgDetailData", "ContIacIdecUsgDetail", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecUsgDetailData", "ContInfIdecUsgDetail", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecUsgDetailData", "StatAppIdecUsgDetail", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecUsgDetailData", "StatShrIdecUsgDetail", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecUsgDetailData", "TagIdecUsgDetail", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecUsgDetailData") {
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
			if (blk.nodeName == "DpchEngIdecUsgDetailData") {
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

			} else if (blk.nodeName == "DpchEngIdecUsgDetailData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

