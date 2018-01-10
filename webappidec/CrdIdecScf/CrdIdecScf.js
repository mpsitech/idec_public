/**
  * \file CrdIdecScf.js
  * web client functionality for card CrdIdecScf
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function getInitdone(pnlshort) {
	return(retrieveSi(srcdoc, "StatAppIdecScf", "initdone" + pnlshort) == "true");
};

function setInitdone(pnlshort) {
	setSi(srcdoc, "StatAppIdecScf", "initdone" + pnlshort, "true");

	checkInitdone();
};

function checkInitdone() {
	var initdoneConn = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneConn") == "true");
	var initdoneStatus = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneStatus") == "true");
	var initdoneMech = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneMech") == "true");
	var initdoneOptics = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneOptics") == "true");
	var initdoneTrigger = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneTrigger") == "true");
	var initdoneLwir = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneLwir") == "true");
	var initdoneQcd = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneQcd") == "true");
	var initdoneRecord = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneRecord") == "true");
	var initdoneHeadbar = (retrieveSi(srcdoc, "StatAppIdecScf", "initdoneHeadbar") == "true");

	if (!initdoneConn) {
		doc.getElementById("Conn").src = "./PnlIdecScfConn.html?scrJref=" + scrJrefConn;
	} else if (!initdoneStatus) {
		doc.getElementById("Status").src = "./PnlIdecScfStatus.html?scrJref=" + scrJrefStatus;
	} else if (!initdoneMech) {
		doc.getElementById("Mech").src = "./PnlIdecScfMech.html?scrJref=" + scrJrefMech;
	} else if (!initdoneOptics) {
		doc.getElementById("Optics").src = "./PnlIdecScfOptics.html?scrJref=" + scrJrefOptics;
	} else if (!initdoneTrigger) {
		doc.getElementById("Trigger").src = "./PnlIdecScfTrigger.html?scrJref=" + scrJrefTrigger;
	} else if (!initdoneLwir) {
		doc.getElementById("Lwir").src = "./PnlIdecScfLwir.html?scrJref=" + scrJrefLwir;
	} else if (!initdoneQcd) {
		doc.getElementById("Qcd").src = "./PnlIdecScfQcd.html?scrJref=" + scrJrefQcd;
	} else if (!initdoneRecord) {
		doc.getElementById("Record").src = "./PnlIdecScfRecord.html?scrJref=" + scrJrefRecord;
	} else if (!initdoneHeadbar) {
		doc.getElementById("Headbar").src = "./PnlIdecScfHeadbar.html?scrJref=" + scrJrefHeadbar;
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

	height += 10 + parseInt(doc.getElementById("tdConn").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdStatus").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdMech").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdOptics").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdTrigger").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdLwir").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdQcd").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdRecord").getAttribute("height")) + 8;

	height += 5;

	return height;
};

// --- menu functionality
function toggleMenu(short, left, width, height) {
	var shortMenu = retrieveSi(srcdoc, "StatAppIdecScf", "shortMenu");

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

	setSi(srcdoc, "StatAppIdecScf", "shortMenu", short);
	setSi(srcdoc, "StatAppIdecScf", "widthMenu", "" + (width-3));

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

	setSi(srcdoc, "StatAppIdecScf", "shortMenu", "");

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

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecScf", "widthMenu"));
	setTextContent(mendoc, mendoc.getElementById("MitAppAbt"), retrieveTi(srcdoc, "TagIdecScf", "MitAppAbt"));
	setTextContent(mendoc, mendoc.getElementById("MrlAppHlp"), retrieveTi(srcdoc, "TagIdecScf", "MrlAppHlp"));
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
	if (false) myif.setAttribute("height", "585");
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

	if (pnlshort == "Conn") {
		doc.getElementById("tdConn").setAttribute("height", "" + height);
		doc.getElementById("Conn").setAttribute("height", "" + height);
	} else if (pnlshort == "Status") {
		doc.getElementById("tdStatus").setAttribute("height", "" + height);
		doc.getElementById("Status").setAttribute("height", "" + height);
	} else if (pnlshort == "Mech") {
		doc.getElementById("tdMech").setAttribute("height", "" + height);
		doc.getElementById("Mech").setAttribute("height", "" + height);
	} else if (pnlshort == "Optics") {
		doc.getElementById("tdOptics").setAttribute("height", "" + height);
		doc.getElementById("Optics").setAttribute("height", "" + height);
	} else if (pnlshort == "Trigger") {
		doc.getElementById("tdTrigger").setAttribute("height", "" + height);
		doc.getElementById("Trigger").setAttribute("height", "" + height);
	} else if (pnlshort == "Lwir") {
		doc.getElementById("tdLwir").setAttribute("height", "" + height);
		doc.getElementById("Lwir").setAttribute("height", "" + height);
	} else if (pnlshort == "Qcd") {
		doc.getElementById("tdQcd").setAttribute("height", "" + height);
		doc.getElementById("Qcd").setAttribute("height", "" + height);
	} else if (pnlshort == "Record") {
		doc.getElementById("tdRecord").setAttribute("height", "" + height);
		doc.getElementById("Record").setAttribute("height", "" + height);
	};

	if (divPnldshld) divPnldshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divDlgshld) divDlgshld.setAttribute("style", "height:" + getHeight() + "px;");
	if (divAlrshld) divAlrshld.setAttribute("style", "height:" + getHeight() + "px;");
};

// --- view initialization and refresh
function refresh() {
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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfDo", scrJref, "close");
	sendReq(str, doc);
};

function handleMitClick(menshort, consref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecScfDo", scrJref, consref + "Click");
	sendReq(str, doc, handleDpchAppDoReply);

	hideMenu(menshort);
};

function handleMrlClick(menshort, consref) {
	window.open(retrieveCi(srcdoc, "ContInfIdecScf", consref), "_blank");

	hideMenu(menshort);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecScfData", "ContInfIdecScf", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecScfData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngIdecScfData", "StatAppIdecScf", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecScfData", "StatShrIdecScf", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecScfData", "TagIdecScf", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecScfData") {
				mergeDpchEngData(dom);

				// establish sub-panel scrJref's as global variables, and start sub-panel load sequence
				scrJrefConn = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefConn");
				scrJrefStatus = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefStatus");
				scrJrefMech = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefMech");
				scrJrefOptics = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefOptics");
				scrJrefTrigger = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefTrigger");
				scrJrefLwir = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefLwir");
				scrJrefQcd = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefQcd");
				scrJrefRecord = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefRecord");
				scrJrefHeadbar = retrieveSi(srcdoc, "StatShrIdecScf", "scrJrefHeadbar");

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

			} else if (blk.nodeName == "DpchEngIdecScfData") {
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
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecScf", "srefIxIdecVReqitmode");

	if (srefIxIdecVReqitmode != "notify") {
		if (doc.timeout) window.clearTimeout(doc.timeout);

		srefIxIdecVReqitmode = "notify";
		setSi(srcdoc, "StatAppIdecScf", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

		iterateReqit();
	};
};

function resumeNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecScf", "srefIxIdecVReqitmode");

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

	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecScf", "srefIxIdecVReqitmode");
	var latency = parseInt(retrieveSi(srcdoc, "StatAppIdecScf", "latency"));

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
					setSi(srcdoc, "StatAppIdecScf", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

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

							} else if (blk.nodeName == "DpchEngIdecScfData") {
								mask = mergeDpchEngData(dom);
								refresh();
							};

						} else if (_scrJref == scrJrefPnld) {
							doc.getElementById("Pnld").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefDlg) {
							doc.getElementById("Dlg").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefConn) {
							doc.getElementById("Conn").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefStatus) {
							doc.getElementById("Status").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefMech) {
							doc.getElementById("Mech").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefOptics) {
							doc.getElementById("Optics").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefTrigger) {
							doc.getElementById("Trigger").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefLwir) {
							doc.getElementById("Lwir").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefQcd) {
							doc.getElementById("Qcd").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefRecord) {
							doc.getElementById("Record").contentWindow.handleDpchEng(dom, blk.nodeName);

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

