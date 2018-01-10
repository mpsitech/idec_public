/**
  * \file PnlIdecScfRecord.js
  * web client functionality for panel PnlIdecScfRecord
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Record", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Record_side").setAttribute("height", "30");
	doc.getElementById("Record_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Record_side").src = "./PnlIdecScfRecord_aside.html";
	doc.getElementById("Record_cont").src = "./PnlIdecScfRecord_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Record_side").src = "./PnlIdecScfRecord_bside.html";
	doc.getElementById("Record_cont").src = "./PnlIdecScfRecord_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Record_side").contentDocument;
	contdoc = doc.getElementById("Record_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfRecord", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Record_side").contentDocument;
	contdoc = doc.getElementById("Record_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Record_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Record_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfRecord", "Cpt"));
	initCpt(contcontdoc, "HdgFrame", retrieveTi(srcdoc, "TagIdecScfRecord", "HdgFrame"));
	initCpt(contcontdoc, "CptFlr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFlr"));
	refreshPup(contcontdoc, srcdoc, "PupFlr", "", "FeedFPupFlr", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFlr"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFlrActive"), false);
	initCpt(contcontdoc, "CptFlg", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFlg"));
	initCpt(contcontdoc, "CptFrr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFrr"));
	refreshPup(contcontdoc, srcdoc, "PupFrr", "", "FeedFPupFrr", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFrr"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFrrActive"), false);
	initCpt(contcontdoc, "CptFrg", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFrg"));
	initCpt(contcontdoc, "CptFir", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFir"));
	refreshPup(contcontdoc, srcdoc, "PupFir", "", "FeedFPupFir", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFir"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFirActive"), false);
	initCpt(contcontdoc, "CptFqc", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFqc"));
	initCpt(contcontdoc, "CptFst", retrieveTi(srcdoc, "TagIdecScfRecord", "CptFst"));
	initCpt(contcontdoc, "HdgVideo", retrieveTi(srcdoc, "TagIdecScfRecord", "HdgVideo"));
	initCpt(contcontdoc, "CptVfr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVfr"));
	initCpt(contcontdoc, "CptVlr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVlr"));
	refreshPup(contcontdoc, srcdoc, "PupVlr", "", "FeedFPupVlr", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVlr"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVlrActive"), false);
	initCpt(contcontdoc, "CptVlg", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVlg"));
	initCpt(contcontdoc, "CptVrr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVrr"));
	refreshPup(contcontdoc, srcdoc, "PupVrr", "", "FeedFPupVrr", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVrr"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVrrActive"), false);
	initCpt(contcontdoc, "CptVrg", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVrg"));
	initCpt(contcontdoc, "CptVir", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVir"));
	refreshPup(contcontdoc, srcdoc, "PupVir", "", "FeedFPupVir", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVir"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVirActive"), false);
	initCpt(contcontdoc, "CptVqc", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVqc"));
	initCpt(contcontdoc, "CptVst", retrieveTi(srcdoc, "TagIdecScfRecord", "CptVst"));
	initCpt(contcontdoc, "CptOwr", retrieveTi(srcdoc, "TagIdecScfRecord", "CptOwr"));
	refreshPup(contcontdoc, srcdoc, "PupOwr", "", "FeedFPupOwr", retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupOwr"), retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupOwrActive"), false);
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate");

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
	var height = 474; // full cont height

	// IP refreshBD.vars --- BEGIN

	var PupFlrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFlrActive") == "true");

	var ChkFlgActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkFlgActive") == "true");

	var PupFrrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFrrActive") == "true");

	var ChkFrgActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkFrgActive") == "true");

	var PupFirActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupFirActive") == "true");

	var ChkFqcActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkFqcActive") == "true");

	var ChkFstActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkFstActive") == "true");

	var SldVfrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "SldVfrActive") == "true");

	var PupVlrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVlrActive") == "true");

	var ChkVlgActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkVlgActive") == "true");

	var PupVrrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVrrActive") == "true");

	var ChkVrgActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkVrgActive") == "true");

	var PupVirActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupVirActive") == "true");

	var ChkVqcActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkVqcActive") == "true");

	var ChkVstActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "ChkVstActive") == "true");

	var PupOwrActive = (retrieveSi(srcdoc, "StatShrIdecScfRecord", "PupOwrActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfRecord", "ButMasterOn") == "true");

	contcontdoc.getElementById("PupFlr").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFlr");

	refreshChk(contcontdoc, "ChkFlg", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkFlg") == "true"), ChkFlgActive);

	contcontdoc.getElementById("PupFrr").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFrr");

	refreshChk(contcontdoc, "ChkFrg", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkFrg") == "true"), ChkFrgActive);

	contcontdoc.getElementById("PupFir").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupFir");

	refreshChk(contcontdoc, "ChkFqc", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkFqc") == "true"), ChkFqcActive);

	refreshChk(contcontdoc, "ChkFst", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkFst") == "true"), ChkFstActive);

	refreshSld(contcontdoc, "SldVfr", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", "SldVfrMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", "SldVfrMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfRecord", "SldVfr")), SldVfrActive, false);

	contcontdoc.getElementById("PupVlr").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVlr");

	refreshChk(contcontdoc, "ChkVlg", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkVlg") == "true"), ChkVlgActive);

	contcontdoc.getElementById("PupVrr").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVrr");

	refreshChk(contcontdoc, "ChkVrg", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkVrg") == "true"), ChkVrgActive);

	contcontdoc.getElementById("PupVir").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupVir");

	refreshChk(contcontdoc, "ChkVqc", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkVqc") == "true"), ChkVqcActive);

	refreshChk(contcontdoc, "ChkVst", (retrieveCi(srcdoc, "ContIacIdecScfRecord", "ChkVst") == "true"), ChkVstActive);

	contcontdoc.getElementById("PupOwr").value = retrieveCi(srcdoc, "ContIacIdecScfRecord", "numFPupOwr");

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Record", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Record_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Record_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Record_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfRecord", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Record_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfRecordDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleChkChange(_doc, ctlsref) {
	var elem = _doc.getElementById(ctlsref);
	var checked;

	elem.setAttribute("class", "chkmod");

	if (elem.checked == true) checked = "true"; else checked = "false";
	setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, checked);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecScfRecord", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleSldJpleftMov(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Jpleftl").setAttribute("class", "sldlhlt");
	};
};

function handleSldJpleftMou(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Jpleftl").setAttribute("class", "sldl");
};

function handleSldJpleftClick(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, oldVal, val;

	var min, max, rast;

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfRecord", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Rast"));

	if (_rast) {
		if (log) val = oldVal / rast;
		else val = oldVal - rast;

		if (val < min) val = min;
		if (val > max) val = max;

	} else {
		pos = getSldPosFromEvtx(true, evt.clientX);
		val = getSldValFromPos(min, max, rast, pos);
	};

	pos = getSldPosFromVal(min, max, val);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleSldJprightMov(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Jprightl").setAttribute("class", "sldlhlt");
	};
};

function handleSldJprightMou(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Jprightl").setAttribute("class", "sldl");
};

function handleSldJprightClick(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, oldVal, val;

	var min, max, rast;

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfRecord", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Rast"));

	if (_rast) {
		if (log) val = oldVal * rast;
		else val = oldVal + rast;

		if (val < min) val = min;
		if (val > max) val = max;

	} else {
		pos = getSldPosFromEvtx(true, evt.clientX);
		val = getSldValFromPos(min, max, rast, pos);
	};

	pos = getSldPosFromVal(min, max, val);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleSldMov(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Bar").setAttribute("class", "sldlhlt");
};

function handleSldMou(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Bar").setAttribute("class", "sldl");
	};
};

function handleSldMdn(_doc, ctlsref) {
	_doc.getElementById("td" + ctlsref).setAttribute("onmousemove", "handle" + ctlsref + "Move(event)");
	_doc.getElementById("td" + ctlsref).setAttribute("onmouseup", "handle" + ctlsref + "Mup(event)");
};

function handleSldMove(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, val;

	var min, max, rast;

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Rast"));
		else rast = 0.0;

		val = parseFloat(elem.value);
		if (isNaN(val)) val = 0.0;

		if (log) {
			val = alignSldLogval(min, max, rast, val);
			pos = getSldPosFromLogval(min, max, val);
		} else {
			val = alignSldVal(min, max, rast, val);
			pos = getSldPosFromVal(min, max, val);
		};

		setSldPos(_doc, ctlsref, true, pos);
		setSldVal(_doc, ctlsref, val, true, true);

		if (shr) {
			setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
			sendReq(str, doc, handleDpchAppDataDoReply);

		} else {
			window["handle" + ctlsref + "Change"](val);
		};

		return false;
	};

	return true;
};

function handleSldValChange(_doc, ctlsref, shr, log, _rast) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfRecord", ctlsref + "Rast"));
	else rast = 0.0;

	val = parseFloat(elem.value);
	if (isNaN(val)) val = 0.0;

	if (log) {
		val = alignSldLogval(min, max, rast, val);
		pos = getSldPosFromLogval(min, max, val);
	} else {
		val = alignSldVal(min, max, rast, val);
		pos = getSldPosFromVal(min, max, val);
	};

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfRecord", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfRecordData", scrJref, "ContIacIdecScfRecord");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "ContIacIdecScfRecord", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "ContInfIdecScfRecord", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupFir", srcdoc)) mask.push("feedFPupFir");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupFlr", srcdoc)) mask.push("feedFPupFlr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupFrr", srcdoc)) mask.push("feedFPupFrr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupOwr", srcdoc)) mask.push("feedFPupOwr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupVir", srcdoc)) mask.push("feedFPupVir");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupVlr", srcdoc)) mask.push("feedFPupVlr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "FeedFPupVrr", srcdoc)) mask.push("feedFPupVrr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "StatAppIdecScfRecord", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "StatShrIdecScfRecord", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfRecordData", "TagIdecScfRecord", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfRecordData") {
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
			if (blk.nodeName == "DpchEngIdecScfRecordData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Record");
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

			} else if (blk.nodeName == "DpchEngIdecScfRecordData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

