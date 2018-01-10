/**
  * \file PnlIdecIaqLive.js
  * web client functionality for panel PnlIdecIaqLive
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive(mask) {
	if (!contcontdoc) return;

	refreshTxt(contcontdoc, "TxtSte", retrieveCi(srcdoc, "ContInfIdecIaqLive", "TxtSte"));

	var cvsctx = contcontdoc.getElementById("cvs").getContext("2d");

	var d = doc.imgdat.data;

	var w = 640;
	var h = 480;

	var mult = 1;
	var ix, ix2;

	var a, b, x;
///
	var min, max;
///

	if ( (mask.indexOf("red") != -1) && (mask.indexOf("green") != -1) && (mask.indexOf("blue") != -1) ) {
		mult = Math.round(Math.sqrt((w*h) / doc.red.length));

		if ( (mult*mult*doc.red.length) == (w*h) ) {
			for (var i=0;i<h/mult;i++) {
				for (var j=0;j<w/mult;j++) {
					ix = (i*w/mult)+j;
					ix2 = 4 * (i*mult*w + j*mult);

					d[ix2] = doc.red[ix];
					d[ix2+1] = doc.green[ix];
					d[ix2+2] = doc.blue[ix];
					d[ix2+3] = 255;
				};
			};

		} else mult = 1;

	} else if (mask.indexOf("gray") != -1) {
		// adjust with contrast/brightness
		a = parseFloat(contcontdoc.getElementById("SldConVal").value);
		if (isNaN(a)) a = 1.0;
		if (a < 1.0) a = 0.0;
		if (a > 100.0) a = 100.0;
		a /= 256.0;

		b = parseFloat(contcontdoc.getElementById("SldBriVal").value);
		if (isNaN(b)) b = 0.0;
		if (b < 0.0) b = 0.0;
		if (b > 1.0) b = 1.0;
		b = 65535.0 * (1.0-b);

		mult = Math.round(Math.sqrt((w*h) / doc.gray.length));

		if ( (mult*mult*doc.gray.length) == (w*h) ) {
			for (var i=0;i<h/mult;i++) {
				for (var j=0;j<w/mult;j++) {
					ix = (i*w/mult)+j;
					ix2 = 4 * (i*mult*w + j*mult);

					x = a*(1.0*doc.gray[ix]-b);
					if (x < 0.0) x = 0.0;
					if (x > 255.0) x = 255.0;

					d[ix2] = x;
					d[ix2+1] = d[ix2];
					d[ix2+2] = d[ix2];
					d[ix2+3] = 255;
				};
			};

		} else mult = 1;

	} else if (mask.indexOf("depth") != -1) {
		var min, max;

		mult = Math.round(Math.sqrt((w*h) / doc.depth.length));

		if ( (mult*mult*doc.depth.length) == (w*h) ) {
			// find min/max
			min = 1e6;
			max = -1e6;

			for (var i=0;i<doc.depth.length;i++) {
				if (doc.depth[i] < min) min = doc.depth[i];
				if (doc.depth[i] > max) max = doc.depth[i];
			};

			if (max > min) {
				a = 255.0/(max-min);
				b = min;

				for (var i=0;i<h/mult;i++) {
					for (var j=0;j<w/mult;j++) {
						ix = (i*w/mult)+j;
						ix2 = 4 * (i*mult*w + j*mult);

						x = a*(1.0*doc.depth[ix]-b);
						if (x < 0.0) x = 0.0;
						if (x > 255.0) x = 255.0;

						d[ix2] = x;
						d[ix2+1] = d[ix2];
						d[ix2+2] = d[ix2];
						d[ix2+3] = 255;
					};
				};
			};
		};
	};

	if (mult > 1) {
		// scale (enlarge) image
		for (var i=0;i<h/mult;i++) {
			for (var j=0;j<w/mult;j++) {
				ix = 4 * (i*mult*w + j*mult);

				for (var k=0;k<mult;k++) {
					for (var l=0;l<mult;l++) {
						if ((k != 0) || (l != 0)) {
							ix2 = 4 * ((i*mult+k)*w + j*mult+l);

							d[ix2] = d[ix];
							d[ix2+1] = d[ix+1];
							d[ix2+2] = d[ix+2];
							d[ix2+3] = d[ix+3];
						};
					};
				};
			};
		};
	};

	cvsctx.putImageData(doc.imgdat, 25, 0);
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	// change container heights
	getCrdwnd().changeHeight("Live", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Live_side").setAttribute("height", "30");
	doc.getElementById("Live_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Live_side").src = "./PnlIdecIaqLive_aside.html";
	doc.getElementById("Live_cont").src = "./PnlIdecIaqLive_a.html";
};

function regularize() {
	// change content (container heights in refreshBD)
	doc.getElementById("Live_side").src = "./PnlIdecIaqLive_bside.html";
	doc.getElementById("Live_cont").src = "./PnlIdecIaqLive_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Live_side").contentDocument;
	contdoc = doc.getElementById("Live_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqLive", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Live_side").contentDocument;
	contdoc = doc.getElementById("Live_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Live_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Live_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqLive", "Cpt"));
	initCpt(contcontdoc, "CptSrc", retrieveTi(srcdoc, "TagIdecIaqLive", "CptSrc"));
	refreshPup(contcontdoc, srcdoc, "PupSrc", "", "FeedFPupSrc", retrieveCi(srcdoc, "ContIacIdecIaqLive", "numFPupSrc"), true, false);
	initCpt(contcontdoc, "CptRes", retrieveTi(srcdoc, "TagIdecIaqLive", "CptRes"));
	initCpt(contcontdoc, "CptGrs", retrieveTi(srcdoc, "TagIdecIaqLive", "CptGrs"));
	initCpt(contcontdoc, "CptCon", retrieveTi(srcdoc, "TagIdecIaqLive", "CptCon"));
	initCpt(contcontdoc, "CptBri", retrieveTi(srcdoc, "TagIdecIaqLive", "CptBri"));
	initCpt(contcontdoc, "CptFrr", retrieveTi(srcdoc, "TagIdecIaqLive", "CptFrr"));
	initCpt(contcontdoc, "CptExt", retrieveTi(srcdoc, "TagIdecIaqLive", "CptExt"));
	initCpt(contcontdoc, "CptSte", retrieveTi(srcdoc, "TagIdecIaqLive", "CptSte"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

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
	var height = 335; // full cont height

	// IP refreshBD.vars --- BEGIN

	var CusImgHeight = parseInt(retrieveSi(srcdoc, "StatShrIdecIaqLive", "CusImgHeight"));

	var ChkGrsAvail = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "ChkGrsAvail") == "true");

	var SldConAvail = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldConAvail") == "true");

	var SldBriAvail = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldBriAvail") == "true");

	var SldFrrActive = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldFrrActive") == "true");

	var SldExtAvail = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldExtAvail") == "true");
	var SldExtActive = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldExtActive") == "true");

	var ButPlayActive = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "ButPlayActive") == "true");
	var ButStopActive = (retrieveSi(srcdoc, "StatShrIdecIaqLive", "ButStopActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecIaqLive", "ButMasterOn") == "true");
	contcontdoc.getElementById("PupSrc").value = retrieveCi(srcdoc, "ContIacIdecIaqLive", "numFPupSrc");

	mytd = contcontdoc.getElementById("tdImg");
	mytd.setAttribute("height", "" + CusImgHeight);
	height += CusImgHeight-100;

	refreshPup(contcontdoc, srcdoc, "PupRes", "", "FeedFPupRes", retrieveCi(srcdoc, "ContIacIdecIaqLive", "numFPupRes"), true, false);

	height -= setCtlAvail(contcontdoc, "Grs", ChkGrsAvail, 25);
	if (ChkGrsAvail) {
		refreshChk(contcontdoc, "ChkGrs", (retrieveCi(srcdoc, "ContIacIdecIaqLive", "ChkGrs") == "true"), true);

	};

	height -= setCtlAvail(contcontdoc, "Con", SldConAvail, 25);
	if (SldConAvail) {

	};

	height -= setCtlAvail(contcontdoc, "Bri", SldBriAvail, 25);
	if (SldBriAvail) {

	};

	refreshSld(contcontdoc, "SldFrr", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldFrrMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldFrrMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqLive", "SldFrr")), SldFrrActive, false);

	height -= setCtlAvail(contcontdoc, "Ext", SldExtAvail, 25);
	if (SldExtAvail) {
		refreshSld(contcontdoc, "SldExt", true, true, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldExtMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldExtMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqLive", "SldExt")), SldExtActive, false);

	};

	refreshTxt(contcontdoc, "TxtSte", retrieveCi(srcdoc, "ContInfIdecIaqLive", "TxtSte"));

	refreshButicon(contcontdoc, "ButPlay", "iconidec/play", ButPlayActive, false);
	refreshButicon(contcontdoc, "ButStop", "iconidec/stop", ButStopActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Live", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Live_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Live_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Live_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Live_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

function handleSldConChange(val) {
// IP handleSldConChange --- IBEGIN
	refreshSld(contcontdoc, "SldCon", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldConMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldConMax")), val, true, false);
	if (doc.gray) refreshLive(["gray"]);
// IP handleSldConChange --- IEND
};

function handleSldBriChange(val) {
// IP handleSldBriChange --- IBEGIN
	refreshSld(contcontdoc, "SldBri", true, false, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldBriMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", "SldBriMax")), val, true, false);
	if (doc.gray) refreshLive(["gray"]);
// IP handleSldBriChange --- IEND
};

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqLiveDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleChkChange(_doc, ctlsref) {
	var elem = _doc.getElementById(ctlsref);
	var checked;

	elem.setAttribute("class", "chkmod");

	if (elem.checked == true) checked = "true"; else checked = "false";
	setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, checked);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecIaqLive", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqLive", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqLive", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqLive", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecIaqLive", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqLiveData", scrJref, "ContIacIdecIaqLive");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "ContIacIdecIaqLive", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "ContInfIdecIaqLive", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "FeedFPupRes", srcdoc)) mask.push("feedFPupRes");
	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "FeedFPupSrc", srcdoc)) mask.push("feedFPupSrc");
	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "StatShrIdecIaqLive", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecIaqLiveData", "TagIdecIaqLive", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecIaqLiveData") {
		var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

		var mask = mergeDpchEngData(dom);

		if (mask.indexOf("statshr") != -1) {
			var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

			if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
				if (srefIxIdecVExpstate == "mind") minimize();
				else if (srefIxIdecVExpstate == "regd") regularize();
			} else {
				refresh();
			};

		} else {
			refresh();
		};
	} else if (dpch == "DpchEngIdecIaqLiveLive") {
		handleDpchEngIdecIaqLiveLive(dom);
	};
};

function handleDpchEngIdecIaqLiveLive(dom) {
// IP handleDpchEngIdecIaqLiveLive --- IBEGIN
	var mask = [];

	var resnode;

	updateSrcblock(dom, "DpchEngIdecIaqLiveLive", "ContInfIdecIaqLive", srcdoc);

	resnode = getNode(dom, "//idec:DpchEngIdecIaqLiveLive/idec:red");
	if (resnode) {
		doc.red = parseUtinyintvec(resnode.textContent);
		mask.push("red");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqLiveLive/idec:green");
	if (resnode) {
		doc.green = parseUtinyintvec(resnode.textContent);
		mask.push("green");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqLiveLive/idec:blue");
	if (resnode) {
		doc.blue = parseUtinyintvec(resnode.textContent);
		mask.push("blue");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqLiveLive/idec:gray");
	if (resnode) {
		doc.gray = parseUsmallintvec(resnode.textContent);
		mask.push("gray");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqLiveLive/idec:depth");
	if (resnode) {
		doc.depth = parseDoublevec(resnode.textContent);
		mask.push("depth");
	};

	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");
	if (srefIxIdecVExpstate == "regd") refreshLive(mask);
// IP handleDpchEngIdecIaqLiveLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecIaqLiveData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Live");
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

			} else if (blk.nodeName == "DpchEngIdecIaqLiveData") {
				var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

				var mask = mergeDpchEngData(dom);

				if (mask.indexOf("statshr") != -1) {
					var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqLive", "srefIxIdecVExpstate");

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


