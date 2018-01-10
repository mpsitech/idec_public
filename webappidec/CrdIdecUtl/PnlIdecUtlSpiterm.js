/**
  * \file PnlIdecUtlSpiterm.js
  * web client functionality for panel PnlIdecUtlSpiterm
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive() {
	if (!contcontdoc) return;

	var myelem;

	myelem = contcontdoc.getElementById("TxtOlg");
	refreshTxtt(contcontdoc, "TxtOlg", retrieveCi(srcdoc, "ContInfIdecUtlSpiterm", "TxtOlg"));
	myelem.scrollTop = myelem.scrollHeight;

	myelem = contcontdoc.getElementById("TxtIlg");
	refreshTxtt(contcontdoc, "TxtIlg", retrieveCi(srcdoc, "ContInfIdecUtlSpiterm", "TxtIlg"));
	myelem.scrollTop = myelem.scrollHeight;
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	// change container heights
	getCrdwnd().changeHeight("Spiterm", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Spiterm_side").setAttribute("height", "30");
	doc.getElementById("Spiterm_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Spiterm_side").src = "./PnlIdecUtlSpiterm_aside.html";
	doc.getElementById("Spiterm_cont").src = "./PnlIdecUtlSpiterm_a.html";
};

function regularize() {
	// change content (container heights in refreshBD)
	doc.getElementById("Spiterm_side").src = "./PnlIdecUtlSpiterm_bside.html";
	doc.getElementById("Spiterm_cont").src = "./PnlIdecUtlSpiterm_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Spiterm_side").contentDocument;
	contdoc = doc.getElementById("Spiterm_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Spiterm_side").contentDocument;
	contdoc = doc.getElementById("Spiterm_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Spiterm_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Spiterm_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "Cpt"));
	initCpt(contcontdoc, "HdgCon", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "HdgCon"));
	initCpt(contcontdoc, "CptTrg", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptTrg"));
	initCpt(contcontdoc, "CptSte", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptSte"));
	initBut(contcontdoc, "ButCct", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButCct"));
	initBut(contcontdoc, "ButDct", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButDct"));
	initCpt(contcontdoc, "HdgDou", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "HdgDou"));
	initCpt(contcontdoc, "CptOlf", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOlf"));
	initCpt(contcontdoc, "HdgDin", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "HdgDin"));
	initCpt(contcontdoc, "CptIlf", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptIlf"));
	initCpt(contcontdoc, "CptIsd", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptIsd"));
	initCpt(contcontdoc, "HdgOcx", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "HdgOcx"));
	initCpt(contcontdoc, "CptOet", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOet"));
	refreshRbu(contcontdoc, srcdoc, "RbuOet", "FeedFRbuOet", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFRbuOet"), true);
	initCpt(contcontdoc, "CptOcm", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOcm"));
	initBut(contcontdoc, "ButOca", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButOca"));
	initCpt(contcontdoc, "CptOcs", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOcs"));
	initCpt(contcontdoc, "CptOhs", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOhs"));
	initCpt(contcontdoc, "CptOfn", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptOfn"));
	initBut(contcontdoc, "ButOsm", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButOsm"));
	initCpt(contcontdoc, "HdgPcx", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "HdgPcx"));
	initCpt(contcontdoc, "CptPet", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPet"));
	refreshRbu(contcontdoc, srcdoc, "RbuPet", "FeedFRbuPet", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFRbuPet"), retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "RbuPetActive"));
	initCpt(contcontdoc, "CptPcm", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPcm"));
	initBut(contcontdoc, "ButPca", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButPca"));
	initCpt(contcontdoc, "CptPcs", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPcs"));
	initCpt(contcontdoc, "CptPhs", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPhs"));
	initCpt(contcontdoc, "CptPfn", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPfn"));
	initCpt(contcontdoc, "CptPin", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "CptPin"));
	initBut(contcontdoc, "ButPrn", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButPrn"));
	initBut(contcontdoc, "ButPst", retrieveTi(srcdoc, "TagIdecUtlSpiterm", "ButPst"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

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
	var height = 1238; // full cont height

	// IP refreshBD.vars --- BEGIN

	var PupTrgActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "PupTrgActive") == "true");

	var ButCctActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButCctActive") == "true");
	var ButDctActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButDctActive") == "true");

	var PupOcmAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "PupOcmAvail") == "true");
	var ButOcaActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButOcaActive") == "true");

	var TxfOcsAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfOcsAvail") == "true");

	var TxfOhsAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfOhsAvail") == "true");

	var TxfOfnAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfOfnAvail") == "true");

	var ButOsmActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButOsmActive") == "true");

	var RbuPetActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "RbuPetActive") == "true");

	var PupPcmAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "PupPcmAvail") == "true");
	var PupPcmActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "PupPcmActive") == "true");
	var ButPcaActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButPcaActive") == "true");

	var TxfPcsAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPcsAvail") == "true");
	var TxfPcsActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPcsActive") == "true");

	var TxfPhsAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPhsAvail") == "true");
	var TxfPhsActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPhsActive") == "true");

	var TxfPfnAvail = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPfnAvail") == "true");
	var TxfPfnActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "TxfPfnActive") == "true");

	var SldPinActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "SldPinActive") == "true");

	var ButPrnActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButPrnActive") == "true");
	var ButPstActive = (retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "ButPstActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN

	refreshPup(contcontdoc, srcdoc, "PupTrg", "", "FeedFPupTrg", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFPupTrg"), PupTrgActive, false);

	refreshTxt(contcontdoc, "TxtSte", retrieveCi(srcdoc, "ContInfIdecUtlSpiterm", "TxtSte"));

	refreshBut(contcontdoc, "ButCct", ButCctActive, false);
	refreshBut(contcontdoc, "ButDct", ButDctActive, false);

	refreshTxt(contcontdoc, "TxtOlf", retrieveCi(srcdoc, "ContInfIdecUtlSpiterm", "TxtOlf"));

	refreshTxt(contcontdoc, "TxtIlf", retrieveCi(srcdoc, "ContInfIdecUtlSpiterm", "TxtIlf"));

	refreshChk(contcontdoc, "ChkIsd", (retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "ChkIsd") == "true"), true);

	setRbuValue(contcontdoc, "RbuOet", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFRbuOet"), true);

	height -= setCtlAvail(contcontdoc, "Ocm", PupOcmAvail, 25);
	if (PupOcmAvail) {
		refreshPup(contcontdoc, srcdoc, "PupOcm", "", "FeedFPupOcm", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFPupOcm"), true, false);

		refreshBut(contcontdoc, "ButOca", ButOcaActive, false);

	};

	height -= setCtlAvail(contcontdoc, "Ocs", TxfOcsAvail, 75);
	if (TxfOcsAvail) {
		refreshTxft(contcontdoc, "TxfOcs", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfOcs"), true, false, true);

	};

	height -= setCtlAvail(contcontdoc, "Ohs", TxfOhsAvail, 75);
	if (TxfOhsAvail) {
		refreshTxft(contcontdoc, "TxfOhs", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfOhs"), true, false, true);

	};

	height -= setCtlAvail(contcontdoc, "Ofn", TxfOfnAvail, 25);
	if (TxfOfnAvail) {
		refreshTxf(contcontdoc, "TxfOfn", "", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfOfn"), true, false, true);

	};

	refreshBut(contcontdoc, "ButOsm", ButOsmActive, false);

	setRbuValue(contcontdoc, "RbuPet", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFRbuPet"), RbuPetActive);

	height -= setCtlAvail(contcontdoc, "Pcm", PupPcmAvail, 25);
	if (PupPcmAvail) {
		refreshPup(contcontdoc, srcdoc, "PupPcm", "", "FeedFPupPcm", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "numFPupPcm"), PupPcmActive, false);

		refreshBut(contcontdoc, "ButPca", ButPcaActive, false);

	};

	height -= setCtlAvail(contcontdoc, "Pcs", TxfPcsAvail, 75);
	if (TxfPcsAvail) {
		refreshTxft(contcontdoc, "TxfPcs", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfPcs"), TxfPcsActive, false, true);

	};

	height -= setCtlAvail(contcontdoc, "Phs", TxfPhsAvail, 75);
	if (TxfPhsAvail) {
		refreshTxft(contcontdoc, "TxfPhs", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfPhs"), TxfPhsActive, false, true);

	};

	height -= setCtlAvail(contcontdoc, "Pfn", TxfPfnAvail, 25);
	if (TxfPfnAvail) {
		refreshTxf(contcontdoc, "TxfPfn", "", retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "TxfPfn"), TxfPfnActive, false, true);

	};

	refreshSld(contcontdoc, "SldPin", true, true, parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "SldPinMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "SldPinMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", "SldPin")), SldPinActive, false);

	refreshBut(contcontdoc, "ButPrn", ButPrnActive, false);
	refreshBut(contcontdoc, "ButPst", ButPstActive, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Spiterm", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Spiterm_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Spiterm_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Spiterm_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Spiterm_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUtlSpitermDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleChkChange(_doc, ctlsref) {
	var elem = _doc.getElementById(ctlsref);
	var checked;

	elem.setAttribute("class", "chkmod");

	if (elem.checked == true) checked = "true"; else checked = "false";
	setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, checked);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecUtlSpiterm", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleRbuSelect(_doc, ctlsref, num) {
	setCi(srcdoc, "ContIacIdecUtlSpiterm", "numF" + ctlsref, "" + num);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
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

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Rast"));

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
		setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Rast"));
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
			setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
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

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", ctlsref + "Rast"));
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
		setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
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

	setCi(srcdoc, "ContIacIdecUtlSpiterm", ctlsref, elem.value.replace(/\n/g, ";"));

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUtlSpitermData", scrJref, "ContIacIdecUtlSpiterm");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "ContIacIdecUtlSpiterm", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "ContInfIdecUtlSpiterm", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "FeedFPupOcm", srcdoc)) mask.push("feedFPupOcm");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "FeedFPupPcm", srcdoc)) mask.push("feedFPupPcm");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "FeedFPupTrg", srcdoc)) mask.push("feedFPupTrg");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "FeedFRbuOet", srcdoc)) mask.push("feedFRbuOet");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "FeedFRbuPet", srcdoc)) mask.push("feedFRbuPet");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "StatShrIdecUtlSpiterm", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecUtlSpitermData", "TagIdecUtlSpiterm", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecUtlSpitermData") {
		var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

		var mask = mergeDpchEngData(dom);

		if (mask.indexOf("statshr") != -1) {
			var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

			if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
				if (srefIxIdecVExpstate == "mind") minimize();
				else if (srefIxIdecVExpstate == "regd") regularize();
			} else {
				refresh();
			};

		} else {
			refresh();
		};
	} else if (dpch == "DpchEngIdecUtlSpitermLive") {
		handleDpchEngIdecUtlSpitermLive(dom);
	};
};

function handleDpchEngIdecUtlSpitermLive(dom) {
// IP handleDpchEngIdecUtlSpitermLive --- IBEGIN
	updateSrcblock(dom, "DpchEngIdecUtlSpitermLive", "ContInfIdecUtlSpiterm", srcdoc);

	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");
	if (srefIxIdecVExpstate == "regd") refreshLive();
// IP handleDpchEngIdecUtlSpitermLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecUtlSpitermData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Spiterm");
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

			} else if (blk.nodeName == "DpchEngIdecUtlSpitermData") {
				var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

				var mask = mergeDpchEngData(dom);

				if (mask.indexOf("statshr") != -1) {
					var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecUtlSpiterm", "srefIxIdecVExpstate");

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


