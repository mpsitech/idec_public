/**
  * \file PnlIdecScfTrigger.js
  * web client functionality for panel PnlIdecScfTrigger
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Trigger", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Trigger_side").setAttribute("height", "30");
	doc.getElementById("Trigger_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Trigger_side").src = "./PnlIdecScfTrigger_aside.html";
	doc.getElementById("Trigger_cont").src = "./PnlIdecScfTrigger_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Trigger_side").src = "./PnlIdecScfTrigger_bside.html";
	doc.getElementById("Trigger_cont").src = "./PnlIdecScfTrigger_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Trigger_side").contentDocument;
	contdoc = doc.getElementById("Trigger_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfTrigger", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Trigger_side").contentDocument;
	contdoc = doc.getElementById("Trigger_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Trigger_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Trigger_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecScfTrigger", "Cpt"));
	initCpt(contcontdoc, "CptRdl", retrieveTi(srcdoc, "TagIdecScfTrigger", "CptRdl"));
	initCpt(contcontdoc, "CptIdl", retrieveTi(srcdoc, "TagIdecScfTrigger", "CptIdl"));
	initCpt(contcontdoc, "CptQdl", retrieveTi(srcdoc, "TagIdecScfTrigger", "CptQdl"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate");

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
	var height = 110; // full cont height

	// IP refreshBD.vars --- BEGIN

	var SldRdlActive = (retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldRdlActive") == "true");

	var SldIdlActive = (retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldIdlActive") == "true");

	var SldQdlActive = (retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldQdlActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecScfTrigger", "ButMasterOn") == "true");

	refreshSld(contcontdoc, "SldRdl", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldRdlMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldRdlMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfTrigger", "SldRdl")), SldRdlActive, false);

	refreshSld(contcontdoc, "SldIdl", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldIdlMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldIdlMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfTrigger", "SldIdl")), SldIdlActive, false);

	refreshSld(contcontdoc, "SldQdl", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldQdlMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", "SldQdlMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecScfTrigger", "SldQdl")), SldQdlActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Trigger", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Trigger_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Trigger_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Trigger_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecScfTrigger", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Trigger_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfTriggerDo", scrJref, ctlsref + "Click");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfTrigger", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfTrigger", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfTriggerData", scrJref, "ContIacIdecScfTrigger");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecScfTrigger", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecScfTrigger", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfTriggerData", scrJref, "ContIacIdecScfTrigger");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecScfTrigger", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfTriggerData", scrJref, "ContIacIdecScfTrigger");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecScfTrigger", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfTriggerData", scrJref, "ContIacIdecScfTrigger");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecScfTrigger", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecScfTrigger", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecScfTriggerData", scrJref, "ContIacIdecScfTrigger");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfTriggerData", "ContIacIdecScfTrigger", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecScfTriggerData", "ContInfIdecScfTrigger", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfTriggerData", "StatAppIdecScfTrigger", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfTriggerData", "StatShrIdecScfTrigger", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfTriggerData", "TagIdecScfTrigger", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecScfTriggerData") {
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
			if (blk.nodeName == "DpchEngIdecScfTriggerData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Trigger");
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

			} else if (blk.nodeName == "DpchEngIdecScfTriggerData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

