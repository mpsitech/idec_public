/**
  * \file CrdIdecIaq.js
  * web client functionality for card CrdIdecIaq
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function getInitdone(pnlshort) {
	return(retrieveSi(srcdoc, "StatAppIdecIaq", "initdone" + pnlshort) == "true");
};

function setInitdone(pnlshort) {
	setSi(srcdoc, "StatAppIdecIaq", "initdone" + pnlshort, "true");

	checkInitdone();
};

function checkInitdone() {
	var initdoneLive = (retrieveSi(srcdoc, "StatAppIdecIaq", "initdoneLive") == "true");
	var initdoneMech = (retrieveSi(srcdoc, "StatAppIdecIaq", "initdoneMech") == "true");
	var initdoneScill = (retrieveSi(srcdoc, "StatAppIdecIaq", "initdoneScill") == "true");
	var initdoneQcdsp = (retrieveSi(srcdoc, "StatAppIdecIaq", "initdoneQcdsp") == "true");
	var initdoneHeadbar = (retrieveSi(srcdoc, "StatAppIdecIaq", "initdoneHeadbar") == "true");

	if (!initdoneLive) {
		doc.getElementById("Live").src = "./PnlIdecIaqLive.html?scrJref=" + scrJrefLive;
	} else if (!initdoneMech) {
		doc.getElementById("Mech").src = "./PnlIdecIaqMech.html?scrJref=" + scrJrefMech;
	} else if (!initdoneScill) {
		doc.getElementById("Scill").src = "./PnlIdecIaqScill.html?scrJref=" + scrJrefScill;
	} else if (!initdoneQcdsp) {
		doc.getElementById("Qcdsp").src = "./PnlIdecIaqQcdsp.html?scrJref=" + scrJrefQcdsp;
	} else if (!initdoneHeadbar) {
		doc.getElementById("Headbar").src = "./PnlIdecIaqHeadbar.html?scrJref=" + scrJrefHeadbar;
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

	height += 10 + parseInt(doc.getElementById("tdLive").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdMech").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdScill").getAttribute("height")) + 8;
	height += 10 + parseInt(doc.getElementById("tdQcdsp").getAttribute("height")) + 8;

	height += 5;

	return height;
};

// --- menu functionality
function toggleMenu(short, left, width, height) {
	var shortMenu = retrieveSi(srcdoc, "StatAppIdecIaq", "shortMenu");

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

	setSi(srcdoc, "StatAppIdecIaq", "shortMenu", short);
	setSi(srcdoc, "StatAppIdecIaq", "widthMenu", "" + (width-3));

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

	setSi(srcdoc, "StatAppIdecIaq", "shortMenu", "");

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

	mendoc.getElementById("colCont").setAttribute("width", retrieveSi(srcdoc, "StatAppIdecIaq", "widthMenu"));
	setTextContent(mendoc, mendoc.getElementById("MitAppAbt"), retrieveTi(srcdoc, "TagIdecIaq", "MitAppAbt"));
	setTextContent(mendoc, mendoc.getElementById("MrlAppHlp"), retrieveTi(srcdoc, "TagIdecIaq", "MrlAppHlp"));
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

	if (pnlshort == "Live") {
		doc.getElementById("tdLive").setAttribute("height", "" + height);
		doc.getElementById("Live").setAttribute("height", "" + height);
	} else if (pnlshort == "Mech") {
		doc.getElementById("tdMech").setAttribute("height", "" + height);
		doc.getElementById("Mech").setAttribute("height", "" + height);
	} else if (pnlshort == "Scill") {
		doc.getElementById("tdScill").setAttribute("height", "" + height);
		doc.getElementById("Scill").setAttribute("height", "" + height);
	} else if (pnlshort == "Qcdsp") {
		doc.getElementById("tdQcdsp").setAttribute("height", "" + height);
		doc.getElementById("Qcdsp").setAttribute("height", "" + height);
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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqDo", scrJref, "close");
	sendReq(str, doc);
};

function handleMitClick(menshort, consref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqDo", scrJref, consref + "Click");
	sendReq(str, doc, handleDpchAppDoReply);

	hideMenu(menshort);
};

function handleMrlClick(menshort, consref) {
	window.open(retrieveCi(srcdoc, "ContInfIdecIaq", consref), "_blank");

	hideMenu(menshort);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqData", "ContInfIdecIaq", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngIdecIaqData", "StatAppIdecIaq", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecIaqData", "StatShrIdecIaq", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecIaqData", "TagIdecIaq", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecIaqData") {
				mergeDpchEngData(dom);

				// establish sub-panel scrJref's as global variables, and start sub-panel load sequence
				scrJrefLive = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefLive");
				scrJrefMech = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefMech");
				scrJrefScill = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefScill");
				scrJrefQcdsp = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefQcdsp");
				scrJrefHeadbar = retrieveSi(srcdoc, "StatShrIdecIaq", "scrJrefHeadbar");

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

			} else if (blk.nodeName == "DpchEngIdecIaqData") {
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
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecIaq", "srefIxIdecVReqitmode");

	if (srefIxIdecVReqitmode != "notify") {
		if (doc.timeout) window.clearTimeout(doc.timeout);

		srefIxIdecVReqitmode = "notify";
		setSi(srcdoc, "StatAppIdecIaq", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

		iterateReqit();
	};
};

function resumeNotify() {
	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecIaq", "srefIxIdecVReqitmode");

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

	var srefIxIdecVReqitmode = retrieveSi(srcdoc, "StatAppIdecIaq", "srefIxIdecVReqitmode");
	var latency = parseInt(retrieveSi(srcdoc, "StatAppIdecIaq", "latency"));

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
					setSi(srcdoc, "StatAppIdecIaq", "srefIxIdecVReqitmode", srefIxIdecVReqitmode);

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

							} else if (blk.nodeName == "DpchEngIdecIaqData") {
								mask = mergeDpchEngData(dom);
								refresh();
							};

						} else if (_scrJref == scrJrefPnld) {
							doc.getElementById("Pnld").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefDlg) {
							doc.getElementById("Dlg").contentWindow.handleDpchEng(dom, blk.nodeName);

						} else if (_scrJref == scrJrefLive) {
							doc.getElementById("Live").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefMech) {
							doc.getElementById("Mech").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefScill) {
							doc.getElementById("Scill").contentWindow.handleDpchEng(dom, blk.nodeName);
						} else if (_scrJref == scrJrefQcdsp) {
							doc.getElementById("Qcdsp").contentWindow.handleDpchEng(dom, blk.nodeName);

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

