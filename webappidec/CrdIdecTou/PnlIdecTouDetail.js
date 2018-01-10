/**
  * \file PnlIdecTouDetail.js
  * web client functionality for panel PnlIdecTouDetail
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize(updh) {
	if (retrieveSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate", "mind");

	// change container heights
	getRecwnd().changeHeight("Detail", 30, updh);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Detail_side").setAttribute("height", "30");
	doc.getElementById("Detail_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Detail_side").src = "./PnlIdecTouDetail_aside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecTouDetail_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Detail_side").src = "./PnlIdecTouDetail_bside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecTouDetail_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecTouDetail", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	contcontdoc = contdoc.getElementById("Detail_cont").contentDocument;
	ftrdoc = contdoc.getElementById("Detail_ftr").contentDocument;

	// IP initBD --- BEGIN
	initCpt(contcontdoc, "CptTit", retrieveTi(srcdoc, "TagIdecTouDetail", "CptTit"));
	initCpt(contcontdoc, "CptMis", retrieveTi(srcdoc, "TagIdecTouDetail", "CptMis"));
	initCpt(contcontdoc, "CptSta", retrieveTi(srcdoc, "TagIdecTouDetail", "CptSta"));
	initCpt(contcontdoc, "CptSto", retrieveTi(srcdoc, "TagIdecTouDetail", "CptSto"));
	initCpt(contcontdoc, "CptAre", retrieveTi(srcdoc, "TagIdecTouDetail", "CptAre"));
	initCpt(contcontdoc, "CptThe", retrieveTi(srcdoc, "TagIdecTouDetail", "CptThe"));
	initCpt(contcontdoc, "CptPhi", retrieveTi(srcdoc, "TagIdecTouDetail", "CptPhi"));
	initCpt(contcontdoc, "CptCmt", retrieveTi(srcdoc, "TagIdecTouDetail", "CptCmt"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate");

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
	var height = 267; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxfTitActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfTitActive") == "true");

	var TxtMisActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxtMisActive") == "true");
	var ButMisViewAvail = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "ButMisViewAvail") == "true");
	var ButMisViewActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "ButMisViewActive") == "true");

	var TxfStaActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfStaActive") == "true");

	var TxfStoActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfStoActive") == "true");

	var TxfAreActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfAreActive") == "true");

	var TxfTheActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfTheActive") == "true");

	var TxfPhiActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfPhiActive") == "true");

	var TxfCmtActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "TxfCmtActive") == "true");

	var ButSaveActive = (retrieveSi(srcdoc, "StatShrIdecTouDetail", "ButSaveActive") == "true");
	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshTxf(contcontdoc, "TxfTit", "", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfTit"), TxfTitActive, false, true);

	if ((ButMisViewAvail == !contcontdoc.getElementById("ButMisView"))) {
		mytd = contcontdoc.getElementById("rdynMis");
		clearElem(mytd);

		first = true;

		if (ButMisViewAvail) {
			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButMisView", "icon/view"));
		};
	};

	refreshTxt(contcontdoc, "TxtMis", retrieveCi(srcdoc, "ContInfIdecTouDetail", "TxtMis"));

	if (ButMisViewAvail) refreshButicon(contcontdoc, "ButMisView", "icon/view", ButMisViewActive, false);

	refreshTxf(contcontdoc, "TxfSta", "", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfSta"), TxfStaActive, false, true);

	refreshTxf(contcontdoc, "TxfSto", "", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfSto"), TxfStoActive, false, true);

	refreshTxf(contcontdoc, "TxfAre", "", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfAre"), TxfAreActive, false, true);

	refreshTxf(contcontdoc, "TxfThe", "s", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfThe"), TxfTheActive, false, true);

	refreshTxf(contcontdoc, "TxfPhi", "s", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfPhi"), TxfPhiActive, false, true);

	refreshTxft(contcontdoc, "TxfCmt", retrieveCi(srcdoc, "ContIacIdecTouDetail", "TxfCmt"), TxfCmtActive, false, true);

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
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecTouDetail", "srefIxIdecVExpstate");

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecTouDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButCrdopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecTouDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoCrdopenReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecTouDetail", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecTouDetailData", scrJref, "ContIacIdecTouDetail");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecTouDetail", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecTouDetailData", scrJref, "ContIacIdecTouDetail");
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

	setCi(srcdoc, "ContIacIdecTouDetail", ctlsref, elem.value.replace(/\n/g, ";"));

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecTouDetailData", scrJref, "ContIacIdecTouDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecTouDetailData", "ContIacIdecTouDetail", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecTouDetailData", "ContInfIdecTouDetail", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecTouDetailData", "StatAppIdecTouDetail", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecTouDetailData", "StatShrIdecTouDetail", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecTouDetailData", "TagIdecTouDetail", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecTouDetailData") {
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
			if (blk.nodeName == "DpchEngIdecTouDetailData") {
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

			} else if (blk.nodeName == "DpchEngIdecTouDetailData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

function handleDpchAppDoCrdopenReply() {
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

				if (accepted == "true") window.open("/web/" + sref + "/" + sref + ".html?scrJref=" + _scrJref, "_blank");

			} else if (blk.nodeName == "DpchEngIdecAlert") {
				getCrdwnd().showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));
			};
		};
	};
};

