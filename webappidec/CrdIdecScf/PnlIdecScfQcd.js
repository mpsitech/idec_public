/**
  * \file PnlIdecScfQcd.js
  * web client functionality for panel PnlIdecScfQcd
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Qcd", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Qcd_side").setAttribute("height", "30");
	doc.getElementById("Qcd_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Qcd_side").src = "./PnlIdecScfQcd_aside.html";
	doc.getElementById("Qcd_cont").src = "./PnlIdecScfQcd_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Qcd_side").src = "./PnlIdecScfQcd_bside.html";
	doc.getElementById("Qcd_cont").src = "./PnlIdecScfQcd_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Qcd_side").contentDocument;
	contdoc = doc.getElementById("Qcd_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfQcd", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Qcd_side").contentDocument;
	contdoc = doc.getElementById("Qcd_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Qcd_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Qcd_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfQcd", "Cpt"));
	initCpt(contcontdoc, "CptLam", retrieveTi(srcdoc, "TagIdecScfQcd", "CptLam"));
	initCpt(contcontdoc, "CptDlm", retrieveTi(srcdoc, "TagIdecScfQcd", "CptDlm"));
	initCpt(contcontdoc, "CptAon", retrieveTi(srcdoc, "TagIdecScfQcd", "CptAon"));
	initCpt(contcontdoc, "CptTof", retrieveTi(srcdoc, "TagIdecScfQcd", "CptTof"));
	initCpt(contcontdoc, "CptTmp", retrieveTi(srcdoc, "TagIdecScfQcd", "CptTmp"));
	initCpt(contcontdoc, "CptFan", retrieveTi(srcdoc, "TagIdecScfQcd", "CptFan"));
	refreshPup(contcontdoc, srcdoc, "PupFan", "", "FeedFPupFan", retrieveCi(srcdoc, "ContIacIdecScfQcd", "numFPupFan"), retrieveSi(srcdoc, "StatShrIdecScfQcd", "PupFanActive"), false);
	initCpt(contcontdoc, "CptFmd", retrieveTi(srcdoc, "TagIdecScfQcd", "CptFmd"));
	initCpt(contcontdoc, "CptVdd", retrieveTi(srcdoc, "TagIdecScfQcd", "CptVdd"));
	initCpt(contcontdoc, "CptVd2", retrieveTi(srcdoc, "TagIdecScfQcd", "CptVd2"));
	initCpt(contcontdoc, "CptVrf", retrieveTi(srcdoc, "TagIdecScfQcd", "CptVrf"));
	initCpt(contcontdoc, "CptAsl", retrieveTi(srcdoc, "TagIdecScfQcd", "CptAsl"));
	initCpt(contcontdoc, "CptAmo", retrieveTi(srcdoc, "TagIdecScfQcd", "CptAmo"));
	initCpt(contcontdoc, "CptAad", retrieveTi(srcdoc, "TagIdecScfQcd", "CptAad"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate");

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
	var height = 367; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxfLamActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "TxfLamActive") == "true");

	var TxfDlmActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "TxfDlmActive") == "true");

	var ChkAonActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "ChkAonActive") == "true");

	var SldTofActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTofActive") == "true");

	var SldTmpActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTmpActive") == "true");

	var PupFanActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "PupFanActive") == "true");

	var SldFmdActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldFmdActive") == "true");

	var SldVddActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVddActive") == "true");

	var ChkVd2Active = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "ChkVd2Active") == "true");

	var SldVrfActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVrfActive") == "true");

	var UpdAslActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "UpdAslActive") == "true");

	var SldAmoActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldAmoActive") == "true");

	var ChkAadActive = (retrieveSi(srcdoc, "StatShrIdecScfQcd", "ChkAadActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfQcd", "ButMasterOn") == "true");
	refreshTxf(contcontdoc, "TxfLam", "s", retrieveCi(srcdoc, "ContIacIdecScfQcd", "TxfLam"), TxfLamActive, false, true);

	refreshTxf(contcontdoc, "TxfDlm", "s", retrieveCi(srcdoc, "ContIacIdecScfQcd", "TxfDlm"), TxfDlmActive, false, true);

	refreshChk(contcontdoc, "ChkAon", (retrieveCi(srcdoc, "ContIacIdecScfQcd", "ChkAon") == "true"), ChkAonActive);

	refreshSld(contcontdoc, "SldTof", true, true, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTofMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTofMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldTof")), SldTofActive, false);

	refreshSld(contcontdoc, "SldTmp", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTmpMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldTmpMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldTmp")), SldTmpActive, false);

	contcontdoc.getElementById("PupFan").value = retrieveCi(srcdoc, "ContIacIdecScfQcd", "numFPupFan");

	refreshSld(contcontdoc, "SldFmd", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldFmdMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldFmdMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldFmd")), SldFmdActive, false);

	refreshSld(contcontdoc, "SldVdd", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVddMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVddMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldVdd")), SldVddActive, false);

	refreshChk(contcontdoc, "ChkVd2", (retrieveCi(srcdoc, "ContIacIdecScfQcd", "ChkVd2") == "true"), ChkVd2Active);

	refreshSld(contcontdoc, "SldVrf", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVrfMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldVrfMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldVrf")), SldVrfActive, false);

	refreshUpd(contcontdoc, "UpdAsl", parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", "UpdAslMin")), parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", "UpdAslMax")), parseInt(retrieveCi(srcdoc, "ContIacIdecScfQcd", "UpdAsl")), UpdAslActive, false);

	refreshSld(contcontdoc, "SldAmo", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldAmoMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", "SldAmoMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", "SldAmo")), SldAmoActive, false);

	refreshChk(contcontdoc, "ChkAad", (retrieveCi(srcdoc, "ContIacIdecScfQcd", "ChkAad") == "true"), ChkAadActive);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Qcd", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Qcd_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Qcd_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Qcd_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfQcd", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Qcd_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfQcdDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleChkChange(_doc, ctlsref) {
	var elem = _doc.getElementById(ctlsref);
	var checked;

	elem.setAttribute("class", "chkmod");

	if (elem.checked == true) checked = "true"; else checked = "false";
	setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, checked);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecScfQcd", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfQcd", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleUpdValKey(_doc, ctlsref, shr, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var val;

	var min, max;

	elem.setAttribute("class", "txfsmod");

	if (evt.keyCode == 13) {
		min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
		max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

		val = parseInt(elem.value);
		if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

		refreshUpd(_doc, ctlsref, min, max, val, true, true);

		if (shr) {
			setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
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

	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	val = parseInt(elem.value);
	if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdUpClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecScfQcd", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	val = oldVal + 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdDownClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecScfQcd", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecScfQcd", ctlsref + "Max"));

	val = oldVal - 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecScfQcd", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfQcdData", scrJref, "ContIacIdecScfQcd");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "ContIacIdecScfQcd", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "ContInfIdecScfQcd", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "FeedFPupFan", srcdoc)) mask.push("feedFPupFan");
	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "StatAppIdecScfQcd", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "StatShrIdecScfQcd", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfQcdData", "TagIdecScfQcd", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfQcdData") {
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
			if (blk.nodeName == "DpchEngIdecScfQcdData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Qcd");
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

			} else if (blk.nodeName == "DpchEngIdecScfQcdData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

