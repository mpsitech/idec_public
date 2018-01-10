/**
  * \file PnlIdecScfMech.js
  * web client functionality for panel PnlIdecScfMech
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive() {
	if (!contcontdoc) return;

	// orientation sensor
	var alpha = 0.0 + parseFloat(retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtOrsAlpha")); if (isNaN(alpha)) alpha = 0.0;
	var beta = 0.0 + parseFloat(retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtOrsBeta")); if (isNaN(beta)) beta = 0.0;

	contcontdoc.getElementById("CusOrsAphveh").setAttribute("transform", "rotate(" + (-alpha) + ")");
	if (alpha >= 0.0) contcontdoc.getElementById("CusOrsApharc").setAttribute("d", "M " + (-40.0*Math.sin(Math.PI*alpha/180.0)) + " " + (-40.0*Math.cos(Math.PI*alpha/180.0) + " A40 40 0 0 1 0 -40"));
	else contcontdoc.getElementById("CusOrsApharc").setAttribute("d", "M0 -40 A40 40 0 0 1 " + (-40.0*Math.sin(Math.PI*alpha/180.0)) + " " + (-40.0*Math.cos(Math.PI*alpha/180.0)));

	contcontdoc.getElementById("CusOrsBetveh").setAttribute("transform", "rotate(" + (-beta) + ")");
	if (beta >= 0.0) contcontdoc.getElementById("CusOrsBetarc").setAttribute("d", "M " + (-40.0*Math.sin(Math.PI*beta/180.0)) + " " + (-40.0*Math.cos(Math.PI*beta/180.0) + " A40 40 0 0 1 0 -40"));
	else contcontdoc.getElementById("CusOrsBetarc").setAttribute("d", "M0 -40 A40 40 0 0 1 " + (-40.0*Math.sin(Math.PI*beta/180.0)) + " " + (-40.0*Math.cos(Math.PI*beta/180.0)));

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtOrsAlpha"), "" + alpha.toFixed(1) + "\u00b0");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtOrsBeta"), "" + beta.toFixed(1) + "\u00b0");

	// theta control
	var theta = parseFloat(retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtTheAng")); if (isNaN(theta)) theta = 0.0;

	contcontdoc.getElementById("CusTheCam").setAttribute("transform", "rotate(" + (-theta) + ")");

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtTheAng"), "" + theta.toFixed(1) + "\u00b0");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtTheRpm"), retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtTheRpm"));
	refreshCsi(contcontdoc, "CsiTheSte", srcdoc, "FeedFCsiTheSte", retrieveCi(srcdoc, "ContInfIdecScfMech", "numFCsiTheSte"));

	refreshThephiBut("ButTheCcw", retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCcwActive") == "true", retrieveCi(srcdoc, "ContInfIdecScfMech", "ButTheCcwOn") == "true");
	refreshThephiBut("ButTheCw", retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCwActive") == "true", retrieveCi(srcdoc, "ContInfIdecScfMech", "ButTheCwOn") == "true");

	// phi control
	var phi = parseFloat(retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtPhiAng")); if (isNaN(phi)) phi = 0.0;

	contcontdoc.getElementById("CusPhiCam").setAttribute("transform", "rotate(" + (-phi) + ")");

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtPhiAng"), "" + phi.toFixed(1) + "\u00b0");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtPhiRpm"), retrieveCi(srcdoc, "ContInfIdecScfMech", "TxtPhiRpm"));
	refreshCsi(contcontdoc, "CsiPhiSte", srcdoc, "FeedFCsiPhiSte", retrieveCi(srcdoc, "ContInfIdecScfMech", "numFCsiPhiSte"));

	refreshThephiBut("ButPhiCcw", retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCcwActive") == "true", retrieveCi(srcdoc, "ContInfIdecScfMech", "ButPhiCcwOn") == "true");
	refreshThephiBut("ButPhiCw", retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCwActive") == "true", retrieveCi(srcdoc, "ContInfIdecScfMech", "ButPhiCwOn") == "true");
};

function refreshThephiBut(id, act, on) {
	var myg;

	myg = contcontdoc.getElementById(id);

	if (on) myg.setAttribute("class", "updhlt");
	else if (act) myg.setAttribute("class", "upd");
	else myg.setAttribute("class", "updinact");

	if (act) myg.setAttribute("onclick", "handle" + id + "Click()");
	else myg.onclick = null;
};

function handleCusTheAnsSet(angle) {
	setCi(srcdoc, "ContIacIdecScfMech", "CusTheAns", "" + angle);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleCusPhiAnsSet(angle) {
	setCi(srcdoc, "ContIacIdecScfMech", "CusPhiAns", "" + angle);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
	sendReq(str, doc, handleDpchAppDataDoReply);
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	// change container heights
	getCrdwnd().changeHeight("Mech", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Mech_side").setAttribute("height", "30");
	doc.getElementById("Mech_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Mech_side").src = "./PnlIdecScfMech_aside.html";
	doc.getElementById("Mech_cont").src = "./PnlIdecScfMech_a.html";
};

function regularize() {
	// change content (container heights in refreshBD)
	doc.getElementById("Mech_side").src = "./PnlIdecScfMech_bside.html";
	doc.getElementById("Mech_cont").src = "./PnlIdecScfMech_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Mech_side").contentDocument;
	contdoc = doc.getElementById("Mech_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfMech", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Mech_side").contentDocument;
	contdoc = doc.getElementById("Mech_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Mech_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Mech_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfMech", "Cpt"));
	initCpt(contcontdoc, "HdgOrsns", retrieveTi(srcdoc, "TagIdecScfMech", "HdgOrsns"));
	initCpt(contcontdoc, "HdgTheax", retrieveTi(srcdoc, "TagIdecScfMech", "HdgTheax"));
	initCpt(contcontdoc, "CptTgr", retrieveTi(srcdoc, "TagIdecScfMech", "CptTgr"));
	initCpt(contcontdoc, "CptTll", retrieveTi(srcdoc, "TagIdecScfMech", "CptTll"));
	initCpt(contcontdoc, "CptTul", retrieveTi(srcdoc, "TagIdecScfMech", "CptTul"));
	initCpt(contcontdoc, "HdgPhiax", retrieveTi(srcdoc, "TagIdecScfMech", "HdgPhiax"));
	initCpt(contcontdoc, "CptPgr", retrieveTi(srcdoc, "TagIdecScfMech", "CptPgr"));
	initCpt(contcontdoc, "CptPll", retrieveTi(srcdoc, "TagIdecScfMech", "CptPll"));
	initCpt(contcontdoc, "CptPul", retrieveTi(srcdoc, "TagIdecScfMech", "CptPul"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

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
	var height = 699; // full cont height

	// IP refreshBD.vars --- BEGIN

	var CusTheAnsActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "CusTheAnsActive") == "true");
	var ButTheCcwActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCcwActive") == "true");
	var ButTheCcwstActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCcwstActive") == "true");
	var ButTheCwstActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCwstActive") == "true");
	var ButTheCwActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButTheCwActive") == "true");

	var TxfTgrActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "TxfTgrActive") == "true");

	var SldTllActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTllActive") == "true");

	var SldTulActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTulActive") == "true");

	var CusPhiAnsActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "CusPhiAnsActive") == "true");
	var ButPhiCcwActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCcwActive") == "true");
	var ButPhiCcwstActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCcwstActive") == "true");
	var ButPhiCwstActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCwstActive") == "true");
	var ButPhiCwActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "ButPhiCwActive") == "true");

	var TxfPgrActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "TxfPgrActive") == "true");

	var SldPllActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPllActive") == "true");

	var SldPulActive = (retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPulActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfMech", "ButMasterOn") == "true");

	refreshTxf(contcontdoc, "TxfTgr", "s", retrieveCi(srcdoc, "ContIacIdecScfMech", "TxfTgr"), TxfTgrActive, false, true);

	refreshSld(contcontdoc, "SldTll", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTllMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTllMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", "SldTll")), SldTllActive, false);

	refreshSld(contcontdoc, "SldTul", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTulMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldTulMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", "SldTul")), SldTulActive, false);

	refreshTxf(contcontdoc, "TxfPgr", "s", retrieveCi(srcdoc, "ContIacIdecScfMech", "TxfPgr"), TxfPgrActive, false, true);

	refreshSld(contcontdoc, "SldPll", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPllMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPllMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", "SldPll")), SldPllActive, false);

	refreshSld(contcontdoc, "SldPul", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPulMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", "SldPulMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", "SldPul")), SldPulActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Mech", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Mech_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Mech_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Mech_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Mech_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfMechDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButMdn(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfMechDo", scrJref, ctlsref + "Mdn");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButMup(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfMechDo", scrJref, ctlsref + "Mup");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfMech", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecScfMech", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecScfMech", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfMech", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecScfMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecScfMech", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecScfMech", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfMechData", scrJref, "ContIacIdecScfMech");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "ContIacIdecScfMech", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "ContInfIdecScfMech", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "FeedFCsiPhiSte", srcdoc)) mask.push("feedFCsiPhiSte");
	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "FeedFCsiTheSte", srcdoc)) mask.push("feedFCsiTheSte");
	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "StatShrIdecScfMech", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfMechData", "TagIdecScfMech", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfMechData") {
		var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

		var mask = mergeDpchEngData(dom);

		if (mask.indexOf("statshr") != -1) {
			var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

			if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
				if (srefIxIdecVExpstate == "mind") minimize();
				else if (srefIxIdecVExpstate == "regd") regularize();
			} else {
				refresh();
			};

		} else {
			refresh();
		};
	} else if (dpch == "DpchEngIdecScfMechLive") {
		handleDpchEngIdecScfMechLive(dom);
	};
};

function handleDpchEngIdecScfMechLive(dom) {
// IP handleDpchEngIdecScfMechLive --- IBEGIN
	updateSrcblock(dom, "DpchEngIdecScfMechLive", "ContInfIdecScfMech", srcdoc);
	refreshLive();
// IP handleDpchEngIdecScfMechLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecScfMechData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Mech");
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

			} else if (blk.nodeName == "DpchEngIdecScfMechData") {
				var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

				var mask = mergeDpchEngData(dom);

				if (mask.indexOf("statshr") != -1) {
					var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecScfMech", "srefIxIdecVExpstate");

					if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
						if (srefIxIdecVExpstate == "mind") minimize();
						else if (srefIxIdecVExpstate == "regd") regularize();
					} else {
						refresh();
					};

				} else {
					refresh();
				};
			};
		};
	};
};


