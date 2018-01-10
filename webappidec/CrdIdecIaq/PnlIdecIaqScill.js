/**
  * \file PnlIdecIaqScill.js
  * web client functionality for panel PnlIdecIaqScill
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Scill", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Scill_side").setAttribute("height", "30");
	doc.getElementById("Scill_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Scill_side").src = "./PnlIdecIaqScill_aside.html";
	doc.getElementById("Scill_cont").src = "./PnlIdecIaqScill_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Scill_side").src = "./PnlIdecIaqScill_bside.html";
	doc.getElementById("Scill_cont").src = "./PnlIdecIaqScill_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Scill_side").contentDocument;
	contdoc = doc.getElementById("Scill_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqScill", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Scill_side").contentDocument;
	contdoc = doc.getElementById("Scill_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Scill_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Scill_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqScill", "Cpt"));
	initCpt(contcontdoc, "CptMod", retrieveTi(srcdoc, "TagIdecIaqScill", "CptMod"));
	refreshPup(contcontdoc, srcdoc, "PupMod", "", "FeedFPupMod", retrieveCi(srcdoc, "ContIacIdecIaqScill", "numFPupMod"), retrieveSi(srcdoc, "StatShrIdecIaqScill", "PupModActive"), false);
	initCpt(contcontdoc, "CptThr", retrieveTi(srcdoc, "TagIdecIaqScill", "CptThr"));
	initCpt(contcontdoc, "CptFld", retrieveTi(srcdoc, "TagIdecIaqScill", "CptFld"));
	initCpt(contcontdoc, "CptSpt", retrieveTi(srcdoc, "TagIdecIaqScill", "CptSpt"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate");

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
	var PupModActive = (retrieveSi(srcdoc, "StatShrIdecIaqScill", "PupModActive") == "true");

	var SldThrAvail = (retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldThrAvail") == "true");
	var SldThrActive = (retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldThrActive") == "true");

	var SldFldActive = (retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldFldActive") == "true");

	var SldSptActive = (retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldSptActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecIaqScill", "ButMasterOn") == "true");
	contcontdoc.getElementById("PupMod").value = retrieveCi(srcdoc, "ContIacIdecIaqScill", "numFPupMod");

	height -= setCtlAvail(contcontdoc, "Thr", SldThrAvail, 25);
	if (SldThrAvail) {
		refreshSld(contcontdoc, "SldThr", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldThrMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldThrMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", "SldThr")), SldThrActive, false);

	};

	refreshSld(contcontdoc, "SldFld", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldFldMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldFldMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", "SldFld")), SldFldActive, false);

	refreshSld(contcontdoc, "SldSpt", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldSptMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", "SldSptMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", "SldSpt")), SldSptActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Scill", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Scill_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Scill_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Scill_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecIaqScill", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Scill_src").contentDocument;

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqScillDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecIaqScill", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqScill", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqScill", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqScill", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecIaqScill", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecIaqScill", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqScill", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecIaqScill", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqScillData", scrJref, "ContIacIdecIaqScill");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "ContIacIdecIaqScill", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "ContInfIdecIaqScill", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "FeedFPupMod", srcdoc)) mask.push("feedFPupMod");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "StatAppIdecIaqScill", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "StatShrIdecIaqScill", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecIaqScillData", "TagIdecIaqScill", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecIaqScillData") {
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
			if (blk.nodeName == "DpchEngIdecIaqScillData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Scill");
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

			} else if (blk.nodeName == "DpchEngIdecIaqScillData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

