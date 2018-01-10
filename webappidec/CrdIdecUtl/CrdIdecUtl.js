/**
  * \file CrdIdecUtl.js
  * web client functionality for card CrdIdecUtl
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function getInitdone(pnlshort) {
	return(retrieveSi(srcdoc, "StatAppIdecUtl", "initdone" + pnlshort) == "true");
};

function setInitdone(pnlshort) {
	setSi(srcdoc, "StatAppIdecUtl", "initdone" + pnlshort, "true");

	checkInitdone();
};

function checkInitdone() {
	var initdoneSpiterm = (retrieveSi(srcdoc, "StatAppIdecUtl", "initdoneSpiterm") == "true");
	var initdoneHeadbar = (retrieveSi(srcdoc, "StatAppIdecUtl", "initdoneHeadbar") == "true");

	if (!initdoneSpiterm) {
		doc.getElementById("Spiterm").src = "./PnlIdecUtlSpiterm.html?scrJref=" + scrJrefSpiterm;
	} else if (!initdoneHeadbar) {
		doc.getElementById("Headbar").src = "./PnlIdecUtlHeadbar.html?scrJref=" + scrJrefHeadbar;
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

	height += 10 + parseInt(doc.getElementById("tdSpiterm").getAttribute("height")) + 8;

	height += 5;

	return height;
};

// --- menu functionality
function toggleMenu(short, left, width, height) {
	var shortMenu = retrieveSi(srcdoc, "StatAppIdecUtl", "shortMenu");

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

	setSi(srcdoc, "StatAppIdecUtl", "shortMenu", short);
	setSi(srcdoc, "StatAppIdecUtl", "widthMenu", "" + (width-3));

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

	setSi(srcdoc, "StatAppIdecUtl", "shortMenu", "");

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

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecUtl", "widthMenu"));
	setTextContent(mendoc, mendoc.getElementById("MitAppAbt"), retrieveTi(srcdoc, "TagIdecUtl", "MitAppAbt"));
	setTextContent(mendoc, mendoc.getElementById("MrlAppHlp"), retrieveTi(srcdoc, "TagIdecUtl", "MrlAppHlp"));
};

function initMenCrd() {
	var mendoc = doc.getElementById("Menu").contentDocument;

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecUtl", "widthMenu"));

	setTextContent(mendoc, mendoc.getElementById("MitCrdThe"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdThe"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdPhi"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdPhi"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdSte"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdSte"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdFsn"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdFsn"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdQnu"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdQnu"));
	setTextContent(mendoc, mendoc.getElementById("MitCrdQal"), retrieveTi(srcdoc, "TagIdecUtl", "MitCrdQal"));
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
	if ((sref == "DlgIdecUtlTheta") || (sref == "DlgIdecUtlPhi") || (sref == "DlgIdecUtlStereo") || (sref == "DlgIdecUtlFusion") || (sref == "DlgIdecUtlQcdnuc") || (sref == "DlgIdecUtlQcdaln")) myif.setAttribute("height", "585");
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

	if (pnlshort == "Spiterm") {
		doc.getElementById("tdSpiterm").setAttribute("height", "" + height);
		doc.getElementById("Spiterm").setAttribute("height", "" + height);
	};

	if (divPnldshld) divPnldshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divDlgshld) divDlgshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divAlrshld) divAlrshld.setAttribute("style", "height:" + getHeight() + "px;");
};

// --- view initialization and refresh
function refresh() {
	var scrJrefDlgfusion = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgfusion");
	var scrJrefDlgphi = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgphi");
	var scrJrefDlgqcdaln = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgqcdaln");
	var scrJrefDlgqcdnuc = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgqcdnuc");
	var scrJrefDlgstereo = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgstereo");
	var scrJrefDlgtheta = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefDlgtheta");

	if (scrJrefDlgfusion != "") {
		if (scrJrefDlg != scrJrefDlgfusion) showDlg("DlgIdecUtlFusion", scrJrefDlgfusion);
	} else if (scrJrefDlgphi != "") {
		if (scrJrefDlg != scrJrefDlgphi) showDlg("DlgIdecUtlPhi", scrJrefDlgphi);
	} else if (scrJrefDlgqcdaln != "") {
		if (scrJrefDlg != scrJrefDlgqcdaln) showDlg("DlgIdecUtlQcdaln", scrJrefDlgqcdaln);
	} else if (scrJrefDlgqcdnuc != "") {
		if (scrJrefDlg != scrJrefDlgqcdnuc) showDlg("DlgIdecUtlQcdnuc", scrJrefDlgqcdnuc);
	} else if (scrJrefDlgstereo != "") {
		if (scrJrefDlg != scrJrefDlgstereo) showDlg("DlgIdecUtlStereo", scrJrefDlgstereo);
	} else if (scrJrefDlgtheta != "") {
		if (scrJrefDlg != scrJrefDlgtheta) showDlg("DlgIdecUtlTheta", scrJrefDlgtheta);
	} else if (scrJrefDlg != "") hideDlg();
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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUtlDo", scrJref, "close");
	sendReq(str, doc);
};

function handleMitClick(menshort, consref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUtlDo", scrJref, consref + "Click");
	sendReq(str, doc, handleDpchAppDoReply);

	hideMenu(menshort);
};

function handleMrlClick(menshort, consref) {
	window.open(retrieveCi(srcdoc, "ContInfIdecUtl", consref), "_blank");

	hideMenu(menshort);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecUtlData", "ContInfIdecUtl", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecUtlData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngIdecUtlData", "StatAppIdecUtl", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecUtlData", "StatShrIdecUtl", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecUtlData", "TagIdecUtl", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecUtlData") {
				mergeDpchEngData(dom);

				// establish sub-panel scrJref's as global variables, and start sub-panel load sequence
				scrJrefSpiterm = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefSpiterm");
				scrJrefHeadbar = retrieveSi(srcdoc, "StatShrIdecUtl", "scrJrefHeadbar");

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

			} else if (blk.nodeName == "DpchEngIdecUtlData") {
				mergeDpchEngData(dom);
				refresh();
			};

			restartNotify();
		};
	};
};

function terminate() {
	if (doc.timeout) window.clearTimeout(doc.timeout);

	window.onfocus = null;
	window.onbeforeunload = null;

	window.open("about:blank", "_self");
};

function restartNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecUtl", "srefIxIdecVReqitmode");

	if (srefIxIdecVReqitmode != "notify") {
		if (doc.timeout) window.clearTimeout(doc.timeout);

		srefIxIdecVReqitmode = "notify";
		setSi(srcdoc, "StatAppIdecUtl", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

		iterateReqit();
	};
};

function resumeNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecUtl", "srefIxIdecVReqitmode");

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

	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecUtl", "srefIxIdecVReqitmode");
	var latency = parseInt(retrieveSi(srcdoc, "StatAppIdecUtl", "latency"));

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
					setSi(srcdoc, "StatAppIdecUtl", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

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

							} else if (blk.nodeName == "DpchEngIdecUtlData") {
								mask = mergeDpchEngData(dom);
								refresh();
							};

						} else if (_scrJref == scrJrefPnld) {
							doc.getElementById("Pnld").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefDlg) {
							doc.getElementById("Dlg").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefSpiterm) {
							doc.getElementById("Spiterm").contentWindow.handleDpchEng(dom, blk.nodeName);

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

