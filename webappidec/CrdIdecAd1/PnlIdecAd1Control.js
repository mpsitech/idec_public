/**
  * \file PnlIdecAd1Control.js
  * web client functionality for panel PnlIdecAd1Control
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Control", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Control_side").setAttribute("height", "30");
	doc.getElementById("Control_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Control_side").src = "./PnlIdecAd1Control_aside.html";
	doc.getElementById("Control_cont").src = "./PnlIdecAd1Control_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Control_side").src = "./PnlIdecAd1Control_bside.html";
	doc.getElementById("Control_cont").src = "./PnlIdecAd1Control_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Control_side").contentDocument;
	contdoc = doc.getElementById("Control_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecAd1Control", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Control_side").contentDocument;
	contdoc = doc.getElementById("Control_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Control_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Control_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecAd1Control", "Cpt"));
	initCpt(contcontdoc, "HdgRoi", retrieveTi(srcdoc, "TagIdecAd1Control", "HdgRoi"));
	initCpt(contcontdoc, "CptTll", retrieveTi(srcdoc, "TagIdecAd1Control", "CptTll"));
	initCpt(contcontdoc, "CptTul", retrieveTi(srcdoc, "TagIdecAd1Control", "CptTul"));
	initCpt(contcontdoc, "CptMct", retrieveTi(srcdoc, "TagIdecAd1Control", "CptMct"));
	initCpt(contcontdoc, "CptPrg", retrieveTi(srcdoc, "TagIdecAd1Control", "CptPrg"));
	initBut(contcontdoc, "ButRun", retrieveTi(srcdoc, "TagIdecAd1Control", "ButRun"));
	initBut(contcontdoc, "ButSto", retrieveTi(srcdoc, "TagIdecAd1Control", "ButSto"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate");

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
	var height = 224; // full cont height

	// IP refreshBD.vars --- BEGIN

	var ButRunActive = (retrieveSi(srcdoc, "StatShrIdecAd1Control", "ButRunActive") == "true");
	var ButStoActive = (retrieveSi(srcdoc, "StatShrIdecAd1Control", "ButStoActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecAd1Control", "ButMasterOn") == "true");

	refreshSld(contcontdoc, "SldTll", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", "SldTllMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", "SldTllMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecAd1Control", "SldTll")), true, false);

	refreshSld(contcontdoc, "SldTul", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", "SldTulMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", "SldTulMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecAd1Control", "SldTul")), true, false);

	refreshUpd(contcontdoc, "UpdMct", parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", "UpdMctMin")), parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", "UpdMctMax")), parseInt(retrieveCi(srcdoc, "ContIacIdecAd1Control", "UpdMct")), true, false);

	refreshTxtt(contcontdoc, "TxtPrg", retrieveCi(srcdoc, "ContInfIdecAd1Control", "TxtPrg"));

	refreshBut(contcontdoc, "ButRun", ButRunActive, false);
	refreshBut(contcontdoc, "ButSto", ButStoActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Control", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Control_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Control_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Control_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecAd1Control", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Control_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecAd1ControlDo", scrJref, ctlsref + "Click");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecAd1Control", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecAd1Control", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdValKey(_doc, ctlsref, shr, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var val;

	var min, max;

	elem.setAttribute("class", "txfsmod");

	if (evt.keyCode == 13) {
		min = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
		max = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

		val = parseInt(elem.value);
		if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

		refreshUpd(_doc, ctlsref, min, max, val, true, true);

		if (shr) {
			setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
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

	min = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	val = parseInt(elem.value);
	if (isNaN(val)) val = 0;
		if (val < min) val = min;
		if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdUpClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecAd1Control", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	val = oldVal + 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleUpdDownClick(_doc, ctlsref, shr) {
	var oldVal, val;

	var min, max;

	if (shr) oldVal = parseInt(retrieveCi(srcdoc, "ContIacIdecAd1Control", ctlsref));
	else oldVal = parseInt(_doc.getElementById(ctlsref + "Val").value);
	min = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Min"));
	max = parseInt(retrieveSi(srcdoc, "StatShrIdecAd1Control", ctlsref + "Max"));

	val = oldVal - 1;
	if (val < min) val = min;
	if (val > max) val = max;

	refreshUpd(_doc, ctlsref, min, max, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecAd1Control", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecAd1ControlData", scrJref, "ContIacIdecAd1Control");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "ContIacIdecAd1Control", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "ContInfIdecAd1Control", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "StatAppIdecAd1Control", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "StatShrIdecAd1Control", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecAd1ControlData", "TagIdecAd1Control", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecAd1ControlData") {
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
			if (blk.nodeName == "DpchEngIdecAd1ControlData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Control");
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

			} else if (blk.nodeName == "DpchEngIdecAd1ControlData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

