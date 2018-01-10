/**
  * \file PnlIdecScfStatus.js
  * web client functionality for panel PnlIdecScfStatus
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Status", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Status_side").setAttribute("height", "30");
	doc.getElementById("Status_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Status_side").src = "./PnlIdecScfStatus_aside.html";
	doc.getElementById("Status_cont").src = "./PnlIdecScfStatus_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Status_side").src = "./PnlIdecScfStatus_bside.html";
	doc.getElementById("Status_cont").src = "./PnlIdecScfStatus_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Status_side").contentDocument;
	contdoc = doc.getElementById("Status_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfStatus", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Status_side").contentDocument;
	contdoc = doc.getElementById("Status_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Status_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Status_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfStatus", "Cpt"));
	initCpt(contcontdoc, "HdgCalib", retrieveTi(srcdoc, "TagIdecScfStatus", "HdgCalib"));
	initCpt(contcontdoc, "CptThe", retrieveTi(srcdoc, "TagIdecScfStatus", "CptThe"));
	initBut(contcontdoc, "ButTheClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButTheClear"));
	initCpt(contcontdoc, "CptPhi", retrieveTi(srcdoc, "TagIdecScfStatus", "CptPhi"));
	initBut(contcontdoc, "ButPhiClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButPhiClear"));
	initCpt(contcontdoc, "CptSte", retrieveTi(srcdoc, "TagIdecScfStatus", "CptSte"));
	initBut(contcontdoc, "ButSteClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButSteClear"));
	initCpt(contcontdoc, "CptFus", retrieveTi(srcdoc, "TagIdecScfStatus", "CptFus"));
	initBut(contcontdoc, "ButFusClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButFusClear"));
	initCpt(contcontdoc, "CptQnu", retrieveTi(srcdoc, "TagIdecScfStatus", "CptQnu"));
	initBut(contcontdoc, "ButQnuClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButQnuClear"));
	initCpt(contcontdoc, "CptQal", retrieveTi(srcdoc, "TagIdecScfStatus", "CptQal"));
	initBut(contcontdoc, "ButQalClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButQalClear"));
	initCpt(contcontdoc, "CptAcv", retrieveTi(srcdoc, "TagIdecScfStatus", "CptAcv"));
	initBut(contcontdoc, "ButAcvClear", retrieveTi(srcdoc, "TagIdecScfStatus", "ButAcvClear"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate");

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
	var height = 217; // full cont height

	// IP refreshBD.vars --- BEGIN

	var ButTheClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButTheClearActive") == "true");

	var ButPhiClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButPhiClearActive") == "true");

	var ButSteClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButSteClearActive") == "true");

	var ButFusClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButFusClearActive") == "true");

	var ButQnuClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButQnuClearActive") == "true");

	var ButQalClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButQalClearActive") == "true");

	var ButAcvClearActive = (retrieveSi(srcdoc, "StatShrIdecScfStatus", "ButAcvClearActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfStatus", "ButMasterOn") == "true");

	refreshTxt(contcontdoc, "TxtThe", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtThe"));

	refreshBut(contcontdoc, "ButTheClear", ButTheClearActive, false);

	refreshTxt(contcontdoc, "TxtPhi", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtPhi"));

	refreshBut(contcontdoc, "ButPhiClear", ButPhiClearActive, false);

	refreshTxt(contcontdoc, "TxtSte", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtSte"));

	refreshBut(contcontdoc, "ButSteClear", ButSteClearActive, false);

	refreshTxt(contcontdoc, "TxtFus", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtFus"));

	refreshBut(contcontdoc, "ButFusClear", ButFusClearActive, false);

	refreshTxt(contcontdoc, "TxtQnu", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtQnu"));

	refreshBut(contcontdoc, "ButQnuClear", ButQnuClearActive, false);

	refreshTxt(contcontdoc, "TxtQal", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtQal"));

	refreshBut(contcontdoc, "ButQalClear", ButQalClearActive, false);

	refreshTxt(contcontdoc, "TxtAcv", retrieveCi(srcdoc, "ContInfIdecScfStatus", "TxtAcv"));

	refreshBut(contcontdoc, "ButAcvClear", ButAcvClearActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Status", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Status_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Status_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Status_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfStatus", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Status_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfStatusDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfStatusData", "ContInfIdecScfStatus", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfStatusData", "StatAppIdecScfStatus", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfStatusData", "StatShrIdecScfStatus", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfStatusData", "TagIdecScfStatus", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfStatusData") {
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
			if (blk.nodeName == "DpchEngIdecScfStatusData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Status");
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

			} else if (blk.nodeName == "DpchEngIdecScfStatusData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

