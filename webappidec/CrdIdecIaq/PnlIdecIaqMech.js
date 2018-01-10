/**
  * \file PnlIdecIaqMech.js
  * web client functionality for panel PnlIdecIaqMech
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive() {
	if (!contcontdoc) return;

	// theta control
	var theta = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtTheAng")); if (isNaN(theta)) theta = 0.0;

	contcontdoc.getElementById("CusTheCam").setAttribute("transform", "rotate(" + (-theta) + ")");

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtTheAng"), "" + theta.toFixed(1) + "\u00b0");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtTheRpm"), retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtTheRpm"));
	refreshCsi(contcontdoc, "CsiTheSte", srcdoc, "FeedFCsiTheSte", retrieveCi(srcdoc, "ContInfIdecIaqMech", "numFCsiTheSte"));

	refreshThephiBut("ButTheCcw", retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCcwActive") == "true", retrieveCi(srcdoc, "ContInfIdecIaqMech", "ButTheCcwOn") == "true");
	refreshThephiBut("ButTheCw", retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCwActive") == "true", retrieveCi(srcdoc, "ContInfIdecIaqMech", "ButTheCwOn") == "true");

	// phi control
	var phi = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtPhiAng")); if (isNaN(phi)) phi = 0.0;

	contcontdoc.getElementById("CusPhiCam").setAttribute("transform", "rotate(" + (-phi) + ")");

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtPhiAng"), "" + phi.toFixed(1) + "\u00b0");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtPhiRpm"), retrieveCi(srcdoc, "ContInfIdecIaqMech", "TxtPhiRpm"));
	refreshCsi(contcontdoc, "CsiPhiSte", srcdoc, "FeedFCsiPhiSte", retrieveCi(srcdoc, "ContInfIdecIaqMech", "numFCsiPhiSte"));

	refreshThephiBut("ButPhiCcw", retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCcwActive") == "true", retrieveCi(srcdoc, "ContInfIdecIaqMech", "ButPhiCcwOn") == "true");
	refreshThephiBut("ButPhiCw", retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCwActive") == "true", retrieveCi(srcdoc, "ContInfIdecIaqMech", "ButPhiCwOn") == "true");
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
	setCi(srcdoc, "ContIacIdecIaqMech", "CusTheAns", "" + angle);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleCusPhiAnsSet(angle) {
	setCi(srcdoc, "ContIacIdecIaqMech", "CusPhiAns", "" + angle);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
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
	doc.getElementById("Mech_side").src = "./PnlIdecIaqMech_aside.html";
	doc.getElementById("Mech_cont").src = "./PnlIdecIaqMech_a.html";
};

function regularize() {
	// change content (container heights in refreshBD)
	doc.getElementById("Mech_side").src = "./PnlIdecIaqMech_bside.html";
	doc.getElementById("Mech_cont").src = "./PnlIdecIaqMech_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Mech_side").contentDocument;
	contdoc = doc.getElementById("Mech_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqMech", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Mech_side").contentDocument;
	contdoc = doc.getElementById("Mech_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Mech_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Mech_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqMech", "Cpt"));
	initCpt(contcontdoc, "CptMod", retrieveTi(srcdoc, "TagIdecIaqMech", "CptMod"));
	refreshPup(contcontdoc, srcdoc, "PupMod", "", "FeedFPupMod", retrieveCi(srcdoc, "ContIacIdecIaqMech", "numFPupMod"), true, false);
	initCpt(contcontdoc, "CptTvv", retrieveTi(srcdoc, "TagIdecIaqMech", "CptTvv"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

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
	var height = 210; // full cont height

	// IP refreshBD.vars --- BEGIN

	var SldTvvAvail = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "SldTvvAvail") == "true");

	var CusTheAnsActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "CusTheAnsActive") == "true");
	var ButTheCcwActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCcwActive") == "true");
	var ButTheCcwstActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCcwstActive") == "true");
	var ButTheCwstActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCwstActive") == "true");
	var ButTheCwActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButTheCwActive") == "true");
	var CusPhiAnsActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "CusPhiAnsActive") == "true");
	var ButPhiCcwActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCcwActive") == "true");
	var ButPhiCcwstActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCcwstActive") == "true");
	var ButPhiCwstActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCwstActive") == "true");
	var ButPhiCwActive = (retrieveSi(srcdoc, "StatShrIdecIaqMech", "ButPhiCwActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecIaqMech", "ButMasterOn") == "true");
	contcontdoc.getElementById("PupMod").value = retrieveCi(srcdoc, "ContIacIdecIaqMech", "numFPupMod");

	height -= setCtlAvail(contcontdoc, "Tvv", SldTvvAvail, 25);
	if (SldTvvAvail) {
		refreshSld(contcontdoc, "SldTvv", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", "SldTvvMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", "SldTvvMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqMech", "SldTvv")), true, false);

	};

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
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqMechDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButMdn(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqMechDo", scrJref, ctlsref + "Mdn");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButMup(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqMechDo", scrJref, ctlsref + "Mup");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecIaqMech", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqMech", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqMech", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecIaqMech", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecIaqMech", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqMech", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecIaqMech", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqMechData", scrJref, "ContIacIdecIaqMech");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "ContIacIdecIaqMech", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "ContInfIdecIaqMech", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "FeedFCsiPhiSte", srcdoc)) mask.push("feedFCsiPhiSte");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "FeedFCsiTheSte", srcdoc)) mask.push("feedFCsiTheSte");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "FeedFPupMod", srcdoc)) mask.push("feedFPupMod");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "StatShrIdecIaqMech", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecIaqMechData", "TagIdecIaqMech", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecIaqMechData") {
		var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

		var mask = mergeDpchEngData(dom);

		if (mask.indexOf("statshr") != -1) {
			var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

			if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
				if (srefIxIdecVExpstate == "mind") minimize();
				else if (srefIxIdecVExpstate == "regd") regularize();
			} else {
				refresh();
			};

		} else {
			refresh();
		};
	} else if (dpch == "DpchEngIdecIaqMechLive") {
		handleDpchEngIdecIaqMechLive(dom);
	};
};

function handleDpchEngIdecIaqMechLive(dom) {
// IP handleDpchEngIdecIaqMechLive --- IBEGIN
	updateSrcblock(dom, "DpchEngIdecIaqMechLive", "ContInfIdecIaqMech", srcdoc);
	refreshLive();
// IP handleDpchEngIdecIaqMechLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecIaqMechData") {
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

			} else if (blk.nodeName == "DpchEngIdecIaqMechData") {
				var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

				var mask = mergeDpchEngData(dom);

				if (mask.indexOf("statshr") != -1) {
					var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqMech", "srefIxIdecVExpstate");

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


