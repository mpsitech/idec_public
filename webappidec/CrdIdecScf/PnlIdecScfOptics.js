/**
  * \file PnlIdecScfOptics.js
  * web client functionality for panel PnlIdecScfOptics
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function getGeoHpath(y, x1, x2) {
	var d = "M" + x1 + " " + y + " L" + x2 + " " + y
				+ " M" + x1 + " " + (y-5) + " L" + x1 + " " + (y+5)
				+ " M" + x2 + " " + (y-5) + " L" + x2 + " " + (y+5);

	return d;
};

function getGeoVpath(x, y1, y2) {
	var d = "M" + x + " " + y1 + " L" + x + " " + y2
				+ " M" + (x-5) + " " + y1 + " L" + (x+5) + " " + y1
				+ " M" + (x-5) + " " + y2 + " L" + (x+5) + " " + y2;

	return d;
};

function setGeoOrient(id, o) {
 var nw, ne, se, sw;

	// r0
	nw = "1"; ne = "2"; se = "3"; sw = "4";

	if (o == "r1") {
		nw = "4"; ne = "1"; se = "2"; sw = "3";
	} else if (o == "r2") {
		nw = "3"; ne = "4"; se = "1"; sw = "2";
	} else if (o == "r3") {
		nw = "2"; ne = "3"; se = "4"; sw = "1";
	} else if (o == "s0") {
		nw = "2"; ne = "1"; se = "4"; sw = "3";
	} else if (o == "s1") {
		nw = "4"; ne = "3"; se = "2"; sw = "1";
	} else if (o == "s2") {
		nw = "1"; ne = "4"; se = "3"; sw = "2";
	} else if (o == "s3") {
		nw = "3"; ne = "2"; se = "1"; sw = "4";
	};

	setTextContent(contcontdoc, contcontdoc.getElementById(id + "nw"), nw);
	setTextContent(contcontdoc, contcontdoc.getElementById(id + "ne"), ne);
	setTextContent(contcontdoc, contcontdoc.getElementById(id + "se"), se);
	setTextContent(contcontdoc, contcontdoc.getElementById(id + "sw"), sw);
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Optics", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Optics_side").setAttribute("height", "30");
	doc.getElementById("Optics_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Optics_side").src = "./PnlIdecScfOptics_aside.html";
	doc.getElementById("Optics_cont").src = "./PnlIdecScfOptics_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Optics_side").src = "./PnlIdecScfOptics_bside.html";
	doc.getElementById("Optics_cont").src = "./PnlIdecScfOptics_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Optics_side").contentDocument;
	contdoc = doc.getElementById("Optics_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfOptics", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Optics_side").contentDocument;
	contdoc = doc.getElementById("Optics_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Optics_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Optics_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfOptics", "Cpt"));
	initCpt(contcontdoc, "HdgGeom", retrieveTi(srcdoc, "TagIdecScfOptics", "HdgGeom"));
	initCpt(contcontdoc, "CptDst", retrieveTi(srcdoc, "TagIdecScfOptics", "CptDst"));
	initCpt(contcontdoc, "CptIdx", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIdx"));
	initCpt(contcontdoc, "CptIdy", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIdy"));
	initCpt(contcontdoc, "CptQdx", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQdx"));
	initCpt(contcontdoc, "CptQdy", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQdy"));
	initCpt(contcontdoc, "CptAdx", retrieveTi(srcdoc, "TagIdecScfOptics", "CptAdx"));
	initCpt(contcontdoc, "CptAdy", retrieveTi(srcdoc, "TagIdecScfOptics", "CptAdy"));
	initCpt(contcontdoc, "HdgVislr", retrieveTi(srcdoc, "TagIdecScfOptics", "HdgVislr"));
	initCpt(contcontdoc, "CptVwi", retrieveTi(srcdoc, "TagIdecScfOptics", "CptVwi"));
	initCpt(contcontdoc, "CptVhe", retrieveTi(srcdoc, "TagIdecScfOptics", "CptVhe"));
	initCpt(contcontdoc, "CptVhp", retrieveTi(srcdoc, "TagIdecScfOptics", "CptVhp"));
	initCpt(contcontdoc, "CptVfl", retrieveTi(srcdoc, "TagIdecScfOptics", "CptVfl"));
	initCpt(contcontdoc, "CptVfn", retrieveTi(srcdoc, "TagIdecScfOptics", "CptVfn"));
	initCpt(contcontdoc, "CptLsg", retrieveTi(srcdoc, "TagIdecScfOptics", "CptLsg"));
	refreshPup(contcontdoc, srcdoc, "PupLsg", "s", "FeedFPupLsg", retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupLsg"), retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupLsgActive"), false);
	initCpt(contcontdoc, "CptRsg", retrieveTi(srcdoc, "TagIdecScfOptics", "CptRsg"));
	refreshPup(contcontdoc, srcdoc, "PupRsg", "s", "FeedFPupRsg", retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupRsg"), retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupRsgActive"), false);
	initCpt(contcontdoc, "HdgLwir", retrieveTi(srcdoc, "TagIdecScfOptics", "HdgLwir"));
	initCpt(contcontdoc, "CptIwi", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIwi"));
	initCpt(contcontdoc, "CptIhe", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIhe"));
	initCpt(contcontdoc, "CptIhp", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIhp"));
	initCpt(contcontdoc, "CptIfl", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIfl"));
	initCpt(contcontdoc, "CptIfn", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIfn"));
	initCpt(contcontdoc, "CptIsg", retrieveTi(srcdoc, "TagIdecScfOptics", "CptIsg"));
	refreshPup(contcontdoc, srcdoc, "PupIsg", "s", "FeedFPupIsg", retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupIsg"), retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupIsgActive"), false);
	initCpt(contcontdoc, "HdgQcd", retrieveTi(srcdoc, "TagIdecScfOptics", "HdgQcd"));
	initCpt(contcontdoc, "CptQwh", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQwh"));
	initCpt(contcontdoc, "CptQhp", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQhp"));
	initCpt(contcontdoc, "CptQdp", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQdp"));
	initCpt(contcontdoc, "CptQfl", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQfl"));
	initCpt(contcontdoc, "CptQfn", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQfn"));
	initCpt(contcontdoc, "CptQsg", retrieveTi(srcdoc, "TagIdecScfOptics", "CptQsg"));
	refreshPup(contcontdoc, srcdoc, "PupQsg", "s", "FeedFPupQsg", retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupQsg"), retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupQsgActive"), false);
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate");

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
	var height = 1021; // full cont height

	// IP refreshBD.vars --- BEGIN

	var TxfDstActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfDstActive") == "true");

	var TxfIdxActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfIdxActive") == "true");

	var TxfIdyActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfIdyActive") == "true");

	var TxfQdxActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQdxActive") == "true");

	var TxfQdyActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQdyActive") == "true");

	var TxfAdxActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfAdxActive") == "true");

	var TxfAdyActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfAdyActive") == "true");

	var PupLsgActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupLsgActive") == "true");

	var PupRsgActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupRsgActive") == "true");

	var PupIsgActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupIsgActive") == "true");

	var UpdQwhActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "UpdQwhActive") == "true");

	var TxfQhpActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQhpActive") == "true");

	var TxfQdpActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQdpActive") == "true");

	var TxfQflActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQflActive") == "true");

	var TxfQfnActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "TxfQfnActive") == "true");

	var PupQsgActive = (retrieveSi(srcdoc, "StatShrIdecScfOptics", "PupQsgActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfOptics", "ButMasterOn") == "true");

	refreshTxf(contcontdoc, "TxfDst", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfDst"), TxfDstActive, false, true);

	refreshTxf(contcontdoc, "TxfIdx", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfIdx"), TxfIdxActive, false, true);

	refreshTxf(contcontdoc, "TxfIdy", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfIdy"), TxfIdyActive, false, true);

	refreshTxf(contcontdoc, "TxfQdx", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQdx"), TxfQdxActive, false, true);

	refreshTxf(contcontdoc, "TxfQdy", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQdy"), TxfQdyActive, false, true);

	refreshTxf(contcontdoc, "TxfAdx", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfAdx"), TxfAdxActive, false, true);

	refreshTxf(contcontdoc, "TxfAdy", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfAdy"), TxfAdyActive, false, true);

	refreshTxt(contcontdoc, "TxtVwi", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtVwi"));

	refreshTxt(contcontdoc, "TxtVhe", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtVhe"));

	refreshTxt(contcontdoc, "TxtVhp", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtVhp"));

	refreshTxt(contcontdoc, "TxtVfl", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtVfl"));

	refreshTxt(contcontdoc, "TxtVfn", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtVfn"));

	contcontdoc.getElementById("PupLsg").value = retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupLsg");

	contcontdoc.getElementById("PupRsg").value = retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupRsg");

	refreshTxt(contcontdoc, "TxtIwi", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtIwi"));

	refreshTxt(contcontdoc, "TxtIhe", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtIhe"));

	refreshTxt(contcontdoc, "TxtIhp", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtIhp"));

	refreshTxt(contcontdoc, "TxtIfl", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtIfl"));

	refreshTxt(contcontdoc, "TxtIfn", retrieveCi(srcdoc, "ContInfIdecScfOptics", "TxtIfn"));

	contcontdoc.getElementById("PupIsg").value = retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupIsg");

	refreshUpd(contcontdoc, "UpdQwh", parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", "UpdQwhMin")), parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", "UpdQwhMax")), parseInt(retrieveCi(srcdoc, "ContIacIdecScfOptics", "UpdQwh")), UpdQwhActive, false);

	refreshTxf(contcontdoc, "TxfQhp", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQhp"), TxfQhpActive, false, true);

	refreshTxf(contcontdoc, "TxfQdp", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQdp"), TxfQdpActive, false, true);

	refreshTxf(contcontdoc, "TxfQfl", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQfl"), TxfQflActive, false, true);

	refreshTxf(contcontdoc, "TxfQfn", "s", retrieveCi(srcdoc, "ContIacIdecScfOptics", "TxfQfn"), TxfQfnActive, false, true);

	contcontdoc.getElementById("PupQsg").value = retrieveCi(srcdoc, "ContIacIdecScfOptics", "numFPupQsg");

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Optics", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Optics_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Optics_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Optics_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfOptics", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Optics_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfOpticsDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecScfOptics", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleUpdValKey(_doc, ctlsref, shr, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var val;

	var min, max;

	elem.setAttribute("class", "txfsmod");

	if (evt.keyCode == 13) {
		min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Min"));
		max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Max"));

		val = parseInt(elem.value);
		if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

		refreshUpd(_doc, ctlsref, min, max, val, true, true);

		if (shr) {
			setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
			sendReq(str, doc, handleDpchAppDataDoReply);

		} else {
			window["handle" + ctlsref + "Change"](val);
		};

		return false;
	};

	return true;
};

function handleUpdValChange(_doc, ctlsref, shr) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var val;

	var min, max;

	elem.setAttribute("class", "txfsmod");

	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Max"));

	val = parseInt(elem.value);
	if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, "" + val);

		setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, "" + val);
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdUpClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecScfOptics", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Max"));

	val = oldVal + 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdDownClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecScfOptics", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfOptics", ctlsref + "Max"));

	val = oldVal - 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfOptics", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfOpticsData", scrJref, "ContIacIdecScfOptics");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "ContIacIdecScfOptics", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "ContInfIdecScfOptics", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "FeedFPupIsg", srcdoc)) mask.push("feedFPupIsg");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "FeedFPupLsg", srcdoc)) mask.push("feedFPupLsg");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "FeedFPupQsg", srcdoc)) mask.push("feedFPupQsg");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "FeedFPupRsg", srcdoc)) mask.push("feedFPupRsg");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "StatAppIdecScfOptics", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "StatShrIdecScfOptics", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfOpticsData", "TagIdecScfOptics", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfOpticsData") {
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
			if (blk.nodeName == "DpchEngIdecScfOpticsData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Optics");
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

			} else if (blk.nodeName == "DpchEngIdecScfOpticsData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};


