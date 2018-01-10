/**
  * \file PnlIdecScfLwir.js
  * web client functionality for panel PnlIdecScfLwir
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Lwir", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Lwir_side").setAttribute("height", "30");
	doc.getElementById("Lwir_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Lwir_side").src = "./PnlIdecScfLwir_aside.html";
	doc.getElementById("Lwir_cont").src = "./PnlIdecScfLwir_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Lwir_side").src = "./PnlIdecScfLwir_bside.html";
	doc.getElementById("Lwir_cont").src = "./PnlIdecScfLwir_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Lwir_side").contentDocument;
	contdoc = doc.getElementById("Lwir_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfLwir", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Lwir_side").contentDocument;
	contdoc = doc.getElementById("Lwir_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Lwir_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Lwir_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfLwir", "Cpt"));
	initCpt(contcontdoc, "CptLm0", retrieveTi(srcdoc, "TagIdecScfLwir", "CptLm0"));
	initCpt(contcontdoc, "CptLm1", retrieveTi(srcdoc, "TagIdecScfLwir", "CptLm1"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate");

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
	var height = 60; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxfLm0Active = (retrieveSi(srcdoc, "StatShrIdecScfLwir", "TxfLm0Active") == "true");

	var TxfLm1Active = (retrieveSi(srcdoc, "StatShrIdecScfLwir", "TxfLm1Active") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfLwir", "ButMasterOn") == "true");
	refreshTxf(contcontdoc, "TxfLm0", "s", retrieveCi(srcdoc, "ContIacIdecScfLwir", "TxfLm0"), TxfLm0Active, false, true);

	refreshTxf(contcontdoc, "TxfLm1", "s", retrieveCi(srcdoc, "ContIacIdecScfLwir", "TxfLm1"), TxfLm1Active, false, true);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Lwir", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Lwir_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Lwir_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Lwir_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfLwir", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Lwir_src").contentDocument;

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

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfLwirDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecScfLwir", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfLwirData", scrJref, "ContIacIdecScfLwir");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecScfLwir", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfLwirData", scrJref, "ContIacIdecScfLwir");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfLwirData", "ContIacIdecScfLwir", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfLwirData", "ContInfIdecScfLwir", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfLwirData", "StatAppIdecScfLwir", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfLwirData", "StatShrIdecScfLwir", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfLwirData", "TagIdecScfLwir", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfLwirData") {
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
			if (blk.nodeName == "DpchEngIdecScfLwirData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Lwir");
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

			} else if (blk.nodeName == "DpchEngIdecScfLwirData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

