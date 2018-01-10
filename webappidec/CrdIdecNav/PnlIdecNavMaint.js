/**
  * \file PnlIdecNavMaint.js
  * web client functionality for panel PnlIdecNavMaint
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Maint", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Maint_side").setAttribute("height", "30");
	doc.getElementById("Maint_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Maint_side").src = "./PnlIdecNavMaint_aside.html";
	doc.getElementById("Maint_cont").src = "./PnlIdecNavMaint_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Maint_side").src = "./PnlIdecNavMaint_bside.html";
	doc.getElementById("Maint_cont").src = "./PnlIdecNavMaint_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Maint_side").contentDocument;
	contdoc = doc.getElementById("Maint_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecNavMaint", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Maint_side").contentDocument;
	contdoc = doc.getElementById("Maint_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Maint_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Maint_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecNavMaint", "Cpt"));
	initCpt(contcontdoc, "CptScf", retrieveTi(srcdoc, "TagIdecNavMaint", "CptScf"));
	initCpt(contcontdoc, "CptUtl", retrieveTi(srcdoc, "TagIdecNavMaint", "CptUtl"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate");

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
	var height = 252; // full cont height

	// IP refreshBD.vars --- BEGIN
	var LstUsgAlt = (retrieveSi(srcdoc, "StatAppIdecNavMaint", "LstUsgAlt") == "true");
	var LstUsgAvail = (retrieveSi(srcdoc, "StatShrIdecNavMaint", "LstUsgAvail") == "true");
	var ButUsgViewAvail = !LstUsgAlt;
	var ButUsgViewActive = (retrieveSi(srcdoc, "StatShrIdecNavMaint", "ButUsgViewActive") == "true");

	var LstUsrAlt = (retrieveSi(srcdoc, "StatAppIdecNavMaint", "LstUsrAlt") == "true");
	var LstUsrAvail = (retrieveSi(srcdoc, "StatShrIdecNavMaint", "LstUsrAvail") == "true");
	var ButUsrViewAvail = !LstUsrAlt;
	var ButUsrViewActive = (retrieveSi(srcdoc, "StatShrIdecNavMaint", "ButUsrViewActive") == "true");

	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	height -= setCtlAvail(contcontdoc, "Usg", LstUsgAvail, 96);
	height -= setCtlAvail(contcontdoc, "Usg2", LstUsgAvail && !LstUsgAlt, 71);
	if (LstUsgAvail) {
		if ( (LstUsgAlt == !contcontdoc.getElementById("ButUsgExpand")) || (!LstUsgAlt == !contcontdoc.getElementById("ButUsgCollapse")) ) {
			mytd = contcontdoc.getElementById("ldynUsg");
			clearElem(mytd);

			mytd.appendChild(makeSpanCpt(contcontdoc, "CptUsg", retrieveTi(srcdoc, "TagIdecNavMaint", "CptUsg")));

			mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			if (LstUsgAlt) mytd.appendChild(makeImgBut(contcontdoc, "ButUsgExpand", "icon/expand"));
			else mytd.appendChild(makeImgBut(contcontdoc, "ButUsgCollapse", "icon/collapse"));
		};

		if (!LstUsgAlt == !contcontdoc.getElementById("LstUsg")) {
			mytd = contcontdoc.getElementById("rdynUsg");
			clearElem(mytd);
			mytd = contcontdoc.getElementById("dynUsg");
			clearElem(mytd);

			if (LstUsgAlt) {
				mytd.setAttribute("rowspan", "1");
			} else {
				mytd.setAttribute("rowspan", "2");
				mytd.appendChild(makeIframeLst(contcontdoc, "LstUsg", "./PnlIdecNavMaint_LstUsg.xml", true));
			};

		} else {
			if (!LstUsgAlt) refreshLst(contcontdoc.getElementById("LstUsg").contentWindow.document, srcdoc, 1, true, false, "FeedFLstUsg",
						parseInt(retrieveSi(srcdoc, "StatAppIdecNavMaint", "LstUsgNumFirstdisp")), [parseInt(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numFLstUsg"))]);
		};

		if ((ButUsgViewAvail == !contcontdoc.getElementById("ButUsgView")) || !contcontdoc.getElementById("ButUsgNewcrd")) {
			if (LstUsgAlt) mytd = contcontdoc.getElementById("dynUsg");
			else mytd = contcontdoc.getElementById("rdynUsg");
			clearElem(mytd);

			first = true;

			if (ButUsgViewAvail) {
				if (first) first = false;
				else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
				mytd.appendChild(makeImgBut(contcontdoc, "ButUsgView", "icon/view"));
			};

			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButUsgNewcrd", "icon/newcrd"));
		};

		if (ButUsgViewAvail) refreshButicon(contcontdoc, "ButUsgView", "icon/view", ButUsgViewActive, false);

	} else setCtlAvail(contcontdoc, "Usg2", false, 0);

	height -= setCtlAvail(contcontdoc, "Usr", LstUsrAvail, 96);
	height -= setCtlAvail(contcontdoc, "Usr2", LstUsrAvail && !LstUsrAlt, 71);
	if (LstUsrAvail) {
		if ( (LstUsrAlt == !contcontdoc.getElementById("ButUsrExpand")) || (!LstUsrAlt == !contcontdoc.getElementById("ButUsrCollapse")) ) {
			mytd = contcontdoc.getElementById("ldynUsr");
			clearElem(mytd);

			mytd.appendChild(makeSpanCpt(contcontdoc, "CptUsr", retrieveTi(srcdoc, "TagIdecNavMaint", "CptUsr")));

			mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			if (LstUsrAlt) mytd.appendChild(makeImgBut(contcontdoc, "ButUsrExpand", "icon/expand"));
			else mytd.appendChild(makeImgBut(contcontdoc, "ButUsrCollapse", "icon/collapse"));
		};

		if (!LstUsrAlt == !contcontdoc.getElementById("LstUsr")) {
			mytd = contcontdoc.getElementById("rdynUsr");
			clearElem(mytd);
			mytd = contcontdoc.getElementById("dynUsr");
			clearElem(mytd);

			if (LstUsrAlt) {
				mytd.setAttribute("rowspan", "1");
			} else {
				mytd.setAttribute("rowspan", "2");
				mytd.appendChild(makeIframeLst(contcontdoc, "LstUsr", "./PnlIdecNavMaint_LstUsr.xml", true));
			};

		} else {
			if (!LstUsrAlt) refreshLst(contcontdoc.getElementById("LstUsr").contentWindow.document, srcdoc, 1, true, false, "FeedFLstUsr",
						parseInt(retrieveSi(srcdoc, "StatAppIdecNavMaint", "LstUsrNumFirstdisp")), [parseInt(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numFLstUsr"))]);
		};

		if ((ButUsrViewAvail == !contcontdoc.getElementById("ButUsrView")) || !contcontdoc.getElementById("ButUsrNewcrd")) {
			if (LstUsrAlt) mytd = contcontdoc.getElementById("dynUsr");
			else mytd = contcontdoc.getElementById("rdynUsr");
			clearElem(mytd);

			first = true;

			if (ButUsrViewAvail) {
				if (first) first = false;
				else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
				mytd.appendChild(makeImgBut(contcontdoc, "ButUsrView", "icon/view"));
			};

			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButUsrNewcrd", "icon/newcrd"));
		};

		if (ButUsrViewAvail) refreshButicon(contcontdoc, "ButUsrView", "icon/view", ButUsrViewActive, false);

	} else setCtlAvail(contcontdoc, "Usr2", false, 0);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Maint", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Maint_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Maint_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Maint_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecNavMaint", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Maint_src").contentDocument;

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

function handleButCollapseClick(basectlsref) {
	setSi(srcdoc, "StatAppIdecNavMaint", basectlsref + "Alt", "true");
	refresh();
};

function handleButExpandClick(basectlsref) {
	setSi(srcdoc, "StatAppIdecNavMaint", basectlsref + "Alt", "false");
	refresh();
};

function setLsbPos(lstdoc, pos) {
	var vpos = (16 + Math.round(pos * (90-2*16)));

	lstdoc.getElementById("LsbJpupr").setAttribute("height", "" + (vpos-10));
	lstdoc.getElementById("LsbJpupl").setAttribute("y2", "" + vpos);

	lstdoc.getElementById("LsbJpdownr").setAttribute("y", "" + vpos);
	lstdoc.getElementById("LsbJpdownr").setAttribute("height", "" + (90-vpos-10));
	lstdoc.getElementById("LsbJpdownl").setAttribute("y1", "" + vpos);

	lstdoc.getElementById("Lsb").setAttribute("transform", "translate(0 " + vpos + ")");
};

function handleLsbUpClick(lstdoc, basectlsref, ncol, multsel) {
	changeLstNumFirstdisp(lstdoc, basectlsref, multsel, ncol, 0, -1);
};

function handleLsbJpupClick(lstdoc, basectlsref, ncol, multsel) {
	changeLstNumFirstdisp(lstdoc, basectlsref, ncol, multsel, 0, -4);
};

function handleLsbJpdownClick(lstdoc, basectlsref, ncol, multsel) {
	changeLstNumFirstdisp(lstdoc, basectlsref, ncol, multsel, 0, 4);
};

function handleLsbDownClick(lstdoc, basectlsref, ncol, multsel) {
	changeLstNumFirstdisp(lstdoc, basectlsref, ncol, multsel, 0, 1);
};

function handleLsbMdn(lstdoc, basectlsref) {
	lstdoc.getElementById("tdLsb").onmousemove = contcontdoc.getElementById(basectlsref).contentWindow.handleLsbMove;
	lstdoc.getElementById("tdLsb").onmouseup = contcontdoc.getElementById(basectlsref).contentWindow.handleLsbMup;
};

function handleLsbMove(lstdoc, evt) {
	if ((evt.clientY >= 16) && (evt.clientY <= (90-16))) {
		var pos = (evt.clientY-16)/(90-2*16);
		setLsbPos(lstdoc, pos);
	};
};

function handleLsbMup(lstdoc, basectlsref, ncol, multsel, evt) {
	lstdoc.getElementById("tdLsb").removeAttribute("onmousemove");
	lstdoc.getElementById("tdLsb").removeAttribute("onmouseup");

	var cnt = getFeedSize(srcdoc, "FeedF" + basectlsref);

	var pos = (evt.clientY-16)/(90-2*16);
	changeLstNumFirstdisp(lstdoc, basectlsref, ncol, multsel, Math.round(pos*(cnt-5))+1, 0);
};

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavMaintDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButCrdopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavMaintDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoCrdopenReply);
};

function handleLstLoad(lstdoc, ctlsref, ncol, multsel) {
	if (multsel) {
		refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, parseInt(retrieveSi(srcdoc, "StatAppIdecNavMaint", ctlsref + "NumFirstdisp")),
					parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numsF" + ctlsref)));
	} else {
		refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, parseInt(retrieveSi(srcdoc, "StatAppIdecNavMaint", ctlsref + "NumFirstdisp")),
					[parseInt(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numF" + ctlsref))]);
	};
};

function handleLstSelect(ctlsref, multsel, num) {
	var found, oldNumFLst, numsFLst, oldNumsFLst;

	if (multsel) {
		oldNumsFLst = parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numsF" + ctlsref));

		found = false;

		for (var i=0;i<oldNumsFLst.length;i++) {
			if (oldNumsFLst[i] == num) {
				numsFLst = new Uint32Array(oldNumsFLst.length-1);

				for (var j=0;j<oldNumsFLst.length;j++)
					if (j < i) numsFLst[j] = oldNumsFLst[j];
					else if (j > i) numsFLst[j-1] = oldNumsFLst[j];

				found = true;
				break;
			};
		};

		if (!found) {
			numsFLst = new Uint32Array(oldNumsFLst.length+1);

			for (var i=0;i<oldNumsFLst.length;i++) numsFLst[i] = oldNumsFLst[i];
			numsFLst[oldNumsFLst.length] = num;
		};

		setCi(srcdoc, "ContIacIdecNavMaint", "numsF" + ctlsref, toBase64(numsFLst));

	} else {
		oldNumFLst = parseInt(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numF" + ctlsref));
		if (num == oldNumFLst) num = 0;

		setCi(srcdoc, "ContIacIdecNavMaint", "numF" + ctlsref, num);
	};

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecNavMaintData", scrJref, "ContIacIdecNavMaint");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function changeLstNumFirstdisp(lstdoc, ctlsref, ncol, multsel, numFirstdisp, dNumFirstdisp) {
	var oldNumFirstdisp = parseInt(retrieveSi(srcdoc, "StatAppIdecNavMaint", ctlsref + "NumFirstdisp"));
	if (dNumFirstdisp != 0) numFirstdisp = oldNumFirstdisp + dNumFirstdisp;

	var cnt = getFeedSize(srcdoc, "FeedF" + ctlsref);

	if (numFirstdisp > (cnt-5+1)) numFirstdisp = cnt-5+1;
	if (numFirstdisp < 1) numFirstdisp = 1;

	if (numFirstdisp != oldNumFirstdisp) {
		setSi(srcdoc, "StatAppIdecNavMaint", ctlsref + "NumFirstdisp", "" + numFirstdisp);

		if (multsel) refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, numFirstdisp, parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numsF" + ctlsref)));
		else refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, numFirstdisp, [parseInt(retrieveCi(srcdoc, "ContIacIdecNavMaint", "numF" + ctlsref))]);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "ContIacIdecNavMaint", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "FeedFLstUsg", srcdoc)) mask.push("feedFLstUsg");
	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "FeedFLstUsr", srcdoc)) mask.push("feedFLstUsr");
	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "StatAppIdecNavMaint", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "StatShrIdecNavMaint", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecNavMaintData", "TagIdecNavMaint", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecNavMaintData") {
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
			if (blk.nodeName == "DpchEngIdecNavMaintData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Maint");
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

			} else if (blk.nodeName == "DpchEngIdecNavMaintData") {
				mergeDpchEngData(dom);
				refresh();
			};
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
				getCrdwnd().showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
						retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));
			};
		};
	};
};

