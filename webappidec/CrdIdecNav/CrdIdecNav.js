/**
  * \file CrdIdecNav.js
  * web client functionality for card CrdIdecNav
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function getInitdone(pnlshort) {
	return(retrieveSi(srcdoc, "StatAppIdecNav", "initdone" + pnlshort) == "true");
};

function setInitdone(pnlshort) {
	setSi(srcdoc, "StatAppIdecNav", "initdone" + pnlshort, "true");

	checkInitdone();
};

function checkInitdone() {
	var initdoneHeadbar = (retrieveSi(srcdoc, "StatAppIdecNav", "initdoneHeadbar") == "true");
	var initdonePre = (retrieveSi(srcdoc, "StatAppIdecNav", "initdonePre") == "true");
	var initdoneMaint = (retrieveSi(srcdoc, "StatAppIdecNav", "initdoneMaint") == "true");
	var initdoneOpr = (retrieveSi(srcdoc, "StatAppIdecNav", "initdoneOpr") == "true");

	if (!initdoneHeadbar) {
		doc.getElementById("Headbar").src = "./PnlIdecNavHeadbar.html?scrJref=" + scrJrefHeadbar;
	} else if (!initdonePre) {
		doc.getElementById("Pre").src = "./PnlIdecNavPre.html?scrJref=" + scrJrefPre;
	} else if (!initdoneMaint) {
		doc.getElementById("Maint").src = "./PnlIdecNavMaint.html?scrJref=" + scrJrefMaint;
	} else if (!initdoneOpr) {
		doc.getElementById("Opr").src = "./PnlIdecNavOpr.html?scrJref=" + scrJrefOpr;
	} else {
		doc.initdone = true;
		window.onfocus = resumeNotify;

		refresh();

		restartNotify();
	};
};

function setPnlAvail(short, avail) {
	var oldAvail = (doc.getElementById("tr" + short).getAttribute("class") == "show");

	if (avail != oldAvail) {
		if (avail) {
			doc.getElementById("spc" + short).setAttribute("class", "show");
			doc.getElementById("tr" + short).setAttribute("class", "show");
		} else {
			doc.getElementById(short).contentWindow.minimize();
			doc.getElementById("spc" + short).setAttribute("class", "hide");
			doc.getElementById("tr" + short).setAttribute("class", "hide");
		};
	};
};

function getHeight() {
	var height = 25;

	if (doc.getElementById("trPre").getAttribute("class") == "show") height += 10 + parseInt(doc.getElementById("tdPre").getAttribute("height"));
	if (doc.getElementById("trMaint").getAttribute("class") == "show") height += 10 + parseInt(doc.getElementById("tdMaint").getAttribute("height")) + 8;
	if (doc.getElementById("trOpr").getAttribute("class") == "show") height += 10 + parseInt(doc.getElementById("tdOpr").getAttribute("height")) + 8;

	height += 5;

	return height;
};

// --- menu functionality
function toggleMenu(short, left, width, height) {
	var shortMenu = retrieveSi(srcdoc, "StatAppIdecNav", "shortMenu");

	if (doc.getElementById("divMenu")) {
		if (shortMenu == short)
			hideMenu(shortMenu);
		else {
			hideMenu(shortMenu);
			showMenu(short, left, width, height);
		};

	} else {
		showMenu(short, left, width, height);
	};
};

function showMenu(short, left, width, height) {
	var headbarcontdoc = doc.getElementById("Headbar").contentWindow.document.getElementById("Headbar_cont").contentWindow.document;

	setSi(srcdoc, "StatAppIdecNav", "shortMenu", short);
	setSi(srcdoc, "StatAppIdecNav", "widthMenu", "" + (width-3));

	if (short == "App") {
		headbarcontdoc.getElementById("MenApp").setAttribute("class", "menuappact");
	} else {
		headbarcontdoc.getElementById("Men" + short).setAttribute("class", "menuact");
	};
	headbarcontdoc.getElementById("lineMen" + short).setAttribute("class", "menulineact");

	var body = doc.getElementById("body");
	var mydiv, myif;

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("class", "menu");
	mydiv.setAttribute("id", "divMenu");
	mydiv.setAttribute("style", "left:" + left + "px;");

	myif = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:iframe");
	myif.setAttribute("id", "Menu");
	myif.setAttribute("src", "./Men" + short + ".html");
	myif.setAttribute("width", "" + width);
	myif.setAttribute("height", "" + height);
	myif.setAttribute("frameborder", "0");
	myif.setAttribute("scrolling", "no");

	mydiv.appendChild(myif);
	body.appendChild(mydiv);
};

function hideMenu(short) {
	var headbarcontdoc = doc.getElementById("Headbar").contentWindow.document.getElementById("Headbar_cont").contentWindow.document;

	setSi(srcdoc, "StatAppIdecNav", "shortMenu", "");

	if (short == "App") {
		headbarcontdoc.getElementById("MenApp").setAttribute("class", "menuapp");
	} else {
		headbarcontdoc.getElementById("Men" + short).setAttribute("class", "menu");
	};
	headbarcontdoc.getElementById("lineMen" + short).setAttribute("class", "menuline");

	var body = doc.getElementById("body");

	body.removeChild(doc.getElementById("divMenu"));
};

function initMenApp() {
	var mendoc = doc.getElementById("Menu").contentDocument;

	var height = parseInt(doc.getElementById("Menu").getAttribute("height"));

	var MspApp2Avail = (retrieveSi(srcdoc, "StatShrIdecNav", "MspApp2Avail") == "true");
	var MitAppLoiAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitAppLoiAvail") == "true");

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecNav", "widthMenu"));

	setTextContent(mendoc, mendoc.getElementById("MitAppAbt"), retrieveTi(srcdoc, "TagIdecNav", "MitAppAbt"));
	setTextContent(mendoc, mendoc.getElementById("MrlAppHlp"), retrieveTi(srcdoc, "TagIdecNav", "MrlAppHlp"));
	setTextContent(mendoc, mendoc.getElementById("MitAppLoi"), retrieveTi(srcdoc, "TagIdecNav", "MitAppLoi"));

	height -= setMitMspAvail("MspApp2", MspApp2Avail, 1);
	height -= setMitMspAvail("MitAppLoi", MitAppLoiAvail, 20);

	doc.getElementById("Menu").setAttribute("height", "" + height);
};

function initMenSes() {
	var mendoc = doc.getElementById("Menu").contentDocument;

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecNav", "widthMenu"));

	setTextContent(mendoc, mendoc.getElementById("MtxSesSes1"), retrieveCi(srcdoc, "ContInfIdecNav", "MtxSesSes1"));
	setTextContent(mendoc, mendoc.getElementById("MtxSesSes2"), retrieveCi(srcdoc, "ContInfIdecNav", "MtxSesSes2"));
	setTextContent(mendoc, mendoc.getElementById("MtxSesSes3"), retrieveCi(srcdoc, "ContInfIdecNav", "MtxSesSes3"));
	setTextContent(mendoc, mendoc.getElementById("MitSesTrm"), retrieveTi(srcdoc, "TagIdecNav", "MitSesTrm"));
};

function initMenCrd() {
	var mendoc = doc.getElementById("Menu").contentDocument;

	var height = parseInt(doc.getElementById("Menu").getAttribute("height"));

	MspCrd1Avail = (retrieveSi(srcdoc, "StatShrIdecNav", "MspCrd1Avail") == "true");
	MitCrdUsgAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdUsgAvail") == "true");
	MitCrdUsrAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdUsrAvail") == "true");
	MitCrdScfAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdScfAvail") == "true");
	MitCrdUtlAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdUtlAvail") == "true");
	MspCrd2Avail = (retrieveSi(srcdoc, "StatShrIdecNav", "MspCrd2Avail") == "true");
	MitCrdMisAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdMisAvail") == "true");
	MitCrdTouAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdTouAvail") == "true");
	MitCrdIaqAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdIaqAvail") == "true");
	MitCrdIaqActive = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdIaqActive") == "true");
	MitCrdAd1Avail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdAd1Avail") == "true");
	MitCrdAd1Active = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdAd1Active") == "true");
	MitCrdFilAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "MitCrdFilAvail") == "true");

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecNav", "widthMenu"));

	setTextContent(mendoc, mendoc.getElementById("MitCrdUsg"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdUsg"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdUsr"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdUsr"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdScf"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdScf"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdUtl"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdUtl"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdMis"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdMis"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdTou"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdTou"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdIaq"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdIaq"));
	setMitActive("MitCrdIaq", MitCrdIaqActive);
	setTextContent(mendoc, mendoc.getElementById("MitCrdAd1"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdAd1"));
	setMitActive("MitCrdAd1", MitCrdAd1Active);
	setTextContent(mendoc, mendoc.getElementById("MitCrdFil"), retrieveTi(srcdoc, "TagIdecNav", "MitCrdFil"));

	height -= setMitMspAvail("MspCrd1", MspCrd1Avail, 1);
	height -= setMitMspAvail("MitCrdUsg", MitCrdUsgAvail, 20);
	height -= setMitMspAvail("MitCrdUsr", MitCrdUsrAvail, 20);
	height -= setMitMspAvail("MitCrdScf", MitCrdScfAvail, 20);
	height -= setMitMspAvail("MitCrdUtl", MitCrdUtlAvail, 20);
	height -= setMitMspAvail("MspCrd2", MspCrd2Avail, 1);
	height -= setMitMspAvail("MitCrdMis", MitCrdMisAvail, 20);
	height -= setMitMspAvail("MitCrdTou", MitCrdTouAvail, 20);
	height -= setMitMspAvail("MitCrdIaq", MitCrdIaqAvail, 20);
	height -= setMitMspAvail("MitCrdAd1", MitCrdAd1Avail, 20);
	height -= setMitMspAvail("MitCrdFil", MitCrdFilAvail, 20);

	doc.getElementById("Menu").setAttribute("height", "" + height);
};

function setMitMspAvail(short, avail, dh) {
	var mendoc = doc.getElementById("Menu").contentDocument;

	if (!avail) mendoc.getElementById("tr" + short).setAttribute("class", "hide");

	if (avail) return 0;
	else return dh;
};

function setMitActive(short, active) {
	var mendoc = doc.getElementById("Menu").contentDocument;
	var mit = mendoc.getElementById(short);

	if (active) {
		mit.setAttribute("class", "item");
		mit.setAttribute("onclick", "handle" + short + "Click()");
	} else {
		mit.setAttribute("class", "itemdis");
		mit.setAttribute("onclick", "");
	};
};

// --- detached panel functionality
function detachPnl(sref, _scrJref) {
	if ((scrJrefPnld != "") && (scrJrefPnld != _scrJref)) attachPnl();

	scrJrefPnld = _scrJref;

	var body = doc.getElementById("body");

	var mydiv, myif;

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("id", "divPnldshld");
	mydiv.setAttribute("class", "pnldshld");
	mydiv.setAttribute("style", "height:" + (getHeight()-35) + "px;");
	body.appendChild(mydiv);

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("class", "pnld");
	mydiv.setAttribute("id", "divPnld");

	myif = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:iframe");
	myif.setAttribute("id", "Pnld");
	myif.setAttribute("src", "./" + sref + "_d.html?scrJref=" + _scrJref);
	myif.setAttribute("width", "891"); /// PRELIMINARY
	myif.setAttribute("height", "586");
	myif.setAttribute("frameborder", "0");
	myif.setAttribute("scrolling", "no");

	mydiv.appendChild(myif);
	body.appendChild(mydiv);
};

function maximizePnl() {
	/// TBD
};

function attachPnl() {
	var body = doc.getElementById("body");
	body.removeChild(doc.getElementById("divPnldshld"));
	body.removeChild(doc.getElementById("divPnld"));

	scrJrefPnld = "";
};

// --- dialog functionality
function showDlg(sref, _scrJref)  {
	if ((scrJrefDlg != "") && (scrJrefDlg != _scrJref)) hideDlg();

	scrJrefDlg = _scrJref;

	var body = doc.getElementById("body");

	var mydiv, myif;

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("id", "divDlgshld");
	mydiv.setAttribute("class", "dlgshld");
	mydiv.setAttribute("style", "height:" + getHeight() + "px;");
	body.appendChild(mydiv);

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("class", "dlg");
	mydiv.setAttribute("id", "divDlg");

	myif = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:iframe");
	myif.setAttribute("id", "Dlg");
	myif.setAttribute("src", "./" + sref + ".html?scrJref=" + _scrJref);
	myif.setAttribute("width", "691");
	if ((sref == "DlgIdecNavLoaini")) myif.setAttribute("height", "585");
	else myif.setAttribute("height", "555");
	myif.setAttribute("frameborder", "0");
	myif.setAttribute("scrolling", "no");

	mydiv.appendChild(myif);
	body.appendChild(mydiv);
};

function hideDlg() {
	var body = doc.getElementById("body");
	body.removeChild(doc.getElementById("divDlgshld"));
	body.removeChild(doc.getElementById("divDlg"));

	scrJrefDlg = "";
};

// --- alert functionality
function showAlr(_scrJref, blkcontinf, blkfeedfmcb)  {
	// update information
	scrJrefAlr = _scrJref;

	replaceSrcblock(blkcontinf, "ContInfIdecAlert", srcdoc);
	replaceSrcblock(blkfeedfmcb, "FeedFMcbAlert", srcdoc);

	// show alert
	var body = doc.getElementById("body");

	var mydiv, myif;

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("id", "divAlrshld");
	mydiv.setAttribute("class", "alrshld");
	mydiv.setAttribute("style", "height:" + getHeight() + "px;");
	body.appendChild(mydiv);

	mydiv = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:div");
	mydiv.setAttribute("class", "alr");
	mydiv.setAttribute("id", "divAlr");

	myif = doc.createElementNS("http://www.w3.org/1999/xhtml", "html:iframe");
	myif.setAttribute("id", "Alr");
	myif.setAttribute("src", "../iframe/alr.xml");
	myif.setAttribute("width", "501");
	myif.setAttribute("height", "60");
	myif.setAttribute("frameborder", "0");
	myif.setAttribute("scrolling", "no");

	mydiv.appendChild(myif);
	body.appendChild(mydiv);
};

function hideAlr(numFMcb) {
	var str = serializeDpchAppAlert(scrJrefAlr, numFMcb);
	sendReq(str, doc, handleDpchAppDoReply);

	var body = doc.getElementById("body");
	body.removeChild(doc.getElementById("divAlrshld"));
	body.removeChild(doc.getElementById("divAlr"));

	scrJrefAlr = "";
};

function initAlr() {
	var alrdoc = doc.getElementById("Alr").contentDocument;

	var height = 30+2+3+25;

	setTextContent(alrdoc, alrdoc.getElementById("TxtCpt"), retrieveCi(srcdoc, "ContInfIdecAlert", "TxtCpt"));

	height += fillAlrTxtMsgFromCont(alrdoc, srcdoc, "ContInfIdecAlert");

	doc.getElementById("Alr").setAttribute("height", "" + height);

	fillAlrMcbFromFeed(alrdoc, srcdoc, "FeedFMcbAlert");
};

// --- expand state management
function changeHeight(pnlshort, height) {
	var divPnldshld = doc.getElementById("divPnldshld");
	var divDlgshld = doc.getElementById("divDlgshld");
	var divAlrshld = doc.getElementById("divAlrshld");

	if (pnlshort == "Maint") {
		doc.getElementById("tdMaint").setAttribute("height", "" + height);
		doc.getElementById("Maint").setAttribute("height", "" + height);
	} else if (pnlshort == "Opr") {
		doc.getElementById("tdOpr").setAttribute("height", "" + height);
		doc.getElementById("Opr").setAttribute("height", "" + height);
	};

	if (divPnldshld) divPnldshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divDlgshld) divDlgshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divAlrshld) divAlrshld.setAttribute("style", "height:" + getHeight() + "px;");
};

// --- view initialization and refresh
function refresh() {
	var scrJrefDlgloaini = retrieveSi(srcdoc, "StatShrIdecNav", "scrJrefDlgloaini");
	var pnlpreAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "pnlpreAvail") == "true");
	var pnlmaintAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "pnlmaintAvail") == "true");
	var pnloprAvail = (retrieveSi(srcdoc, "StatShrIdecNav", "pnloprAvail") == "true");

	if (scrJrefDlgloaini != "") {
		if (scrJrefDlg != scrJrefDlgloaini) showDlg("DlgIdecNavLoaini", scrJrefDlgloaini);
	} else if (scrJrefDlg != "") hideDlg();

	setPnlAvail("Pre", pnlpreAvail);
	setPnlAvail("Maint", pnlmaintAvail);
	setPnlAvail("Opr", pnloprAvail);
};

// --- event handlers
function handleLoad() {
	scrJref = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc = document;
	srcdoc = doc.getElementById("_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

function handleUnload() {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavDo", scrJref, "close");
	sendReq(str, doc);
};

function handleMitClick(menshort, consref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavDo", scrJref, consref + "Click");
	sendReq(str, doc, handleDpchAppDoReply);

	hideMenu(menshort);
};

function handleMitCrdopenClick(menshort, consref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavDo", scrJref, consref + "Click");
	sendReq(str, doc, handleDpchAppDoCrdopenReply);

	hideMenu(menshort);
};

function handleMrlClick(menshort, consref) {
	window.open(retrieveCi(srcdoc, "ContInfIdecNav", consref), "_blank");

	hideMenu(menshort);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecNavData", "ContInfIdecNav", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecNavData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngIdecNavData", "StatAppIdecNav", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecNavData", "StatShrIdecNav", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecNavData", "TagIdecNav", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecNavData") {
				mergeDpchEngData(dom);

				// establish sub-panel scrJref's as global variables, and start sub-panel load sequence
				scrJrefHeadbar = retrieveSi(srcdoc, "StatShrIdecNav", "scrJrefHeadbar");
				scrJrefPre = retrieveSi(srcdoc, "StatShrIdecNav", "scrJrefPre");
				scrJrefMaint = retrieveSi(srcdoc, "StatShrIdecNav", "scrJrefMaint");
				scrJrefOpr = retrieveSi(srcdoc, "StatShrIdecNav", "scrJrefOpr");

				scrJrefPnld = "";

				scrJrefDlg = "";

				scrJrefAlr = "";

				// load sub-panels one by one
				checkInitdone();
			};
		};
	};
};

function handleDpchAppDoReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		// check dispatch type
		blk = retrieveBlock(dom, "//idec:*");

		if (blk) {
			if (blk.nodeName == "DpchEngIdecConfirm") {
				// do nothing

			} else if (blk.nodeName == "DpchEngIdecAlert") {
				// show alert with new content
				showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));

			} else if (blk.nodeName == "DpchEngIdecNavData") {
				mergeDpchEngData(dom);
				refresh();
			};

			restartNotify();
		};
	};
};

function handleDpchAppDoCrdopenReply() {
	var dom, blk;

	var accepted, _scrJref, sref;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");

		if (blk) {
			if (blk.nodeName == "DpchEngIdecConfirm") {
				accepted = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted");
				_scrJref = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:scrJref");
				sref = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:sref");

				if (accepted == "true") window.open("/web/" + sref + "/" + sref + ".html?scrJref=" + _scrJref, "_blank");

			} else if (blk.nodeName == "DpchEngIdecAlert") {
				showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));
			};

			restartNotify();
		};
	};
};

function terminate() {
	if (doc.timeout) window.clearTimeout(doc.timeout);

	window.onfocus = null;
	window.onbeforeunload = null;

	window.open("../CrdIdecStart/CrdIdecStart.html?do=Logout", "_self");
};

function restartNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecNav", "srefIxIdecVReqitmode");

	if (srefIxIdecVReqitmode != "notify") {
		if (doc.timeout) window.clearTimeout(doc.timeout);

		srefIxIdecVReqitmode = "notify";
		setSi(srcdoc, "StatAppIdecNav", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

		iterateReqit();
	};
};

function resumeNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecNav", "srefIxIdecVReqitmode");

	if (srefIxIdecVReqitmode != "notify") {
		if (doc.timeout) window.clearTimeout(doc.timeout);

		var str = serializeDpchApp("DpchAppIdecResume", scrJref);
		sendReq(str, doc, handleDpchAppResumeReply);
	};
};

function handleDpchAppResumeReply() {
	var dom, blk;

	if ((doc.req.readyState == 4) && (doc.req.status == 404)) {
		terminate();

	} else if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");

		if (blk) if (blk.nodeName == "DpchEngIdecAck") restartNotify();
	};
};

function iteratePoll() {
	iterateReqit();
};

function iterateReqit(ev) {
	var accepted, _scrJref, mask;

	var news = false;
	var iterate = true;

	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecNav", "srefIxIdecVReqitmode");
	var latency = parseInt(retrieveSi(srcdoc, "StatAppIdecNav", "latency"));

	if (doc.reqit && ev) {
		if (doc.reqit.readyState != 4) {
			iterate = false;

		} else if ((doc.reqit.readyState == 4) && (doc.reqit.status == 404)) {
			iterate = false;

			terminate();

		} else if (doc.reqit.readyState == 4) {
			dom = doc.reqit.responseXML;

			// check dispatch type
			blk = retrieveBlock(dom, "//idec:*");

			if (blk) {
				if (blk.nodeName == "DpchEngIdecAck") {
					// no news
					// alert("no news");

				} else if (blk.nodeName == "DpchEngIdecSuspend") {
					// change to "poll" mode
					news = true;

					srefIxIdecVReqitmode = "poll";
					setSi(srcdoc, "StatAppIdecNav", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

				} else {
					// request with content
					news = true;

					_scrJref = retrieveValue(dom, "//idec:*/idec:scrJref");

					if (blk.nodeName == "DpchEngIdecAlert") {
						// card-based treatment even for scrJref corresponding to panel / dialog
						showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
								retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
								retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));

					} else {
						if (_scrJref == scrJref) {
							if (blk.nodeName == "DpchEngIdecConfirm") {
								accepted = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted");

								if (accepted == "false") {
									// arrives on card close
									iterate = false;
									terminate();
								};

							} else if (blk.nodeName == "DpchEngIdecNavData") {
								mask = mergeDpchEngData(dom);
								refresh();
							};

						} else if (_scrJref == scrJrefPnld) {
							doc.getElementById("Pnld").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefDlg) {
							doc.getElementById("Dlg").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefPre) {
							doc.getElementById("Pre").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefMaint) {
							doc.getElementById("Maint").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefOpr) {
							doc.getElementById("Opr").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else {
							// alert("got a '" + blk.nodeName + "' from job with scrJref " + _scrJref);
						};
					};
				};
			};
		};
	};

	if ((srefIxIdecVReqitmode == "notify") && iterate) {
		// send notify request
		if (!doc.reqit) doc.reqit = new XMLHttpRequest();
		doc.reqit.onreadystatechange = iterateReqit;
		doc.reqit.open("GET", "/notify/" + scrJref, true);
		doc.reqit.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		doc.reqit.send("");

	} else if ((srefIxIdecVReqitmode == "poll") && iterate) {
		if (!ev || (news && ev)) {
			// send poll request
			if (!doc.reqit) doc.reqit = new XMLHttpRequest();
			doc.reqit.onreadystatechange = iterateReqit;
			doc.reqit.open("GET", "/poll/" + scrJref, true);
			doc.reqit.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			doc.reqit.send("");

		} else {
			// wait
			doc.timeout = setTimeout(iteratePoll, latency*1000);
		};
	};
};

