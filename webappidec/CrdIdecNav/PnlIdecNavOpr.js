/**
  * \file PnlIdecNavOpr.js
  * web client functionality for panel PnlIdecNavOpr
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize() {
	if (retrieveSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate", "mind");

	// change container heights
	getCrdwnd().changeHeight("Opr", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Opr_side").setAttribute("height", "30");
	doc.getElementById("Opr_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Opr_side").src = "./PnlIdecNavOpr_aside.html";
	doc.getElementById("Opr_cont").src = "./PnlIdecNavOpr_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Opr_side").src = "./PnlIdecNavOpr_bside.html";
	doc.getElementById("Opr_cont").src = "./PnlIdecNavOpr_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Opr_side").contentDocument;
	contdoc = doc.getElementById("Opr_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecNavOpr", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Opr_side").contentDocument;
	contdoc = doc.getElementById("Opr_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Opr_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Opr_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecNavOpr", "Cpt"));
	initCpt(contcontdoc, "CptIaq", retrieveTi(srcdoc, "TagIdecNavOpr", "CptIaq"));
	initCpt(contcontdoc, "CptAd1", retrieveTi(srcdoc, "TagIdecNavOpr", "CptAd1"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate");

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
	var height = 348; // full cont height

	// IP refreshBD.vars --- BEGIN
	var LstMisAlt = (retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstMisAlt") == "true");
	var LstMisAvail = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "LstMisAvail") == "true");
	var ButMisViewAvail = !LstMisAlt;
	var ButMisViewActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButMisViewActive") == "true");

	var LstTouAlt = (retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstTouAlt") == "true");
	var LstTouAvail = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "LstTouAvail") == "true");
	var ButTouViewAvail = !LstTouAlt;
	var ButTouViewActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButTouViewActive") == "true");
	var ButTouNewcrdActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButTouNewcrdActive") == "true");

	var ButIaqNewcrdActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButIaqNewcrdActive") == "true");

	var ButAd1NewcrdActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButAd1NewcrdActive") == "true");

	var LstFilAlt = (retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstFilAlt") == "true");
	var LstFilAvail = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "LstFilAvail") == "true");
	var ButFilViewAvail = !LstFilAlt;
	var ButFilViewActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButFilViewActive") == "true");
	var ButFilNewcrdActive = (retrieveSi(srcdoc, "StatShrIdecNavOpr", "ButFilNewcrdActive") == "true");

	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	height -= setCtlAvail(contcontdoc, "Mis", LstMisAvail, 96);
	height -= setCtlAvail(contcontdoc, "Mis2", LstMisAvail && !LstMisAlt, 71);
	if (LstMisAvail) {
		if ( (LstMisAlt == !contcontdoc.getElementById("ButMisExpand")) || (!LstMisAlt == !contcontdoc.getElementById("ButMisCollapse")) ) {
			mytd = contcontdoc.getElementById("ldynMis");
			clearElem(mytd);

			mytd.appendChild(makeSpanCpt(contcontdoc, "CptMis", retrieveTi(srcdoc, "TagIdecNavOpr", "CptMis")));

			mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			if (LstMisAlt) mytd.appendChild(makeImgBut(contcontdoc, "ButMisExpand", "icon/expand"));
			else mytd.appendChild(makeImgBut(contcontdoc, "ButMisCollapse", "icon/collapse"));
		};

		if (!LstMisAlt == !contcontdoc.getElementById("LstMis")) {
			mytd = contcontdoc.getElementById("rdynMis");
			clearElem(mytd);
			mytd = contcontdoc.getElementById("dynMis");
			clearElem(mytd);

			if (LstMisAlt) {
				mytd.setAttribute("rowspan", "1");
			} else {
				mytd.setAttribute("rowspan", "2");
				mytd.appendChild(makeIframeLst(contcontdoc, "LstMis", "./PnlIdecNavOpr_LstMis.xml", true));
			};

		} else {
			if (!LstMisAlt) refreshLst(contcontdoc.getElementById("LstMis").contentWindow.document, srcdoc, 1, true, false, "FeedFLstMis",
						parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstMisNumFirstdisp")), [parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numFLstMis"))]);
		};

		if ((ButMisViewAvail == !contcontdoc.getElementById("ButMisView")) || !contcontdoc.getElementById("ButMisNewcrd")) {
			if (LstMisAlt) mytd = contcontdoc.getElementById("dynMis");
			else mytd = contcontdoc.getElementById("rdynMis");
			clearElem(mytd);

			first = true;

			if (ButMisViewAvail) {
				if (first) first = false;
				else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
				mytd.appendChild(makeImgBut(contcontdoc, "ButMisView", "icon/view"));
			};

			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButMisNewcrd", "icon/newcrd"));
		};

		if (ButMisViewAvail) refreshButicon(contcontdoc, "ButMisView", "icon/view", ButMisViewActive, false);

	} else setCtlAvail(contcontdoc, "Mis2", false, 0);

	height -= setCtlAvail(contcontdoc, "Tou", LstTouAvail, 96);
	height -= setCtlAvail(contcontdoc, "Tou2", LstTouAvail && !LstTouAlt, 71);
	if (LstTouAvail) {
		if ( (LstTouAlt == !contcontdoc.getElementById("ButTouExpand")) || (!LstTouAlt == !contcontdoc.getElementById("ButTouCollapse")) ) {
			mytd = contcontdoc.getElementById("ldynTou");
			clearElem(mytd);

			mytd.appendChild(makeSpanCpt(contcontdoc, "CptTou", retrieveTi(srcdoc, "TagIdecNavOpr", "CptTou")));

			mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			if (LstTouAlt) mytd.appendChild(makeImgBut(contcontdoc, "ButTouExpand", "icon/expand"));
			else mytd.appendChild(makeImgBut(contcontdoc, "ButTouCollapse", "icon/collapse"));
		};

		if (!LstTouAlt == !contcontdoc.getElementById("LstTou")) {
			mytd = contcontdoc.getElementById("rdynTou");
			clearElem(mytd);
			mytd = contcontdoc.getElementById("dynTou");
			clearElem(mytd);

			if (LstTouAlt) {
				mytd.setAttribute("rowspan", "1");
			} else {
				mytd.setAttribute("rowspan", "2");
				mytd.appendChild(makeIframeLst(contcontdoc, "LstTou", "./PnlIdecNavOpr_LstTou.xml", true));
			};

		} else {
			if (!LstTouAlt) refreshLst(contcontdoc.getElementById("LstTou").contentWindow.document, srcdoc, 1, true, false, "FeedFLstTou",
						parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstTouNumFirstdisp")), [parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numFLstTou"))]);
		};

		if ((ButTouViewAvail == !contcontdoc.getElementById("ButTouView")) || !contcontdoc.getElementById("ButTouNewcrd")) {
			if (LstTouAlt) mytd = contcontdoc.getElementById("dynTou");
			else mytd = contcontdoc.getElementById("rdynTou");
			clearElem(mytd);

			first = true;

			if (ButTouViewAvail) {
				if (first) first = false;
				else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
				mytd.appendChild(makeImgBut(contcontdoc, "ButTouView", "icon/view"));
			};

			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButTouNewcrd", "icon/newcrd"));
		};

		if (ButTouViewAvail) refreshButicon(contcontdoc, "ButTouView", "icon/view", ButTouViewActive, false);
		refreshButicon(contcontdoc, "ButTouNewcrd", "icon/newcrd", ButTouNewcrdActive, false);

	} else setCtlAvail(contcontdoc, "Tou2", false, 0);

	refreshButicon(contcontdoc, "ButIaqNewcrd", "icon/newcrd", ButIaqNewcrdActive, false);

	refreshButicon(contcontdoc, "ButAd1Newcrd", "icon/newcrd", ButAd1NewcrdActive, false);

	height -= setCtlAvail(contcontdoc, "Fil", LstFilAvail, 96);
	height -= setCtlAvail(contcontdoc, "Fil2", LstFilAvail && !LstFilAlt, 71);
	if (LstFilAvail) {
		if ( (LstFilAlt == !contcontdoc.getElementById("ButFilExpand")) || (!LstFilAlt == !contcontdoc.getElementById("ButFilCollapse")) ) {
			mytd = contcontdoc.getElementById("ldynFil");
			clearElem(mytd);

			mytd.appendChild(makeSpanCpt(contcontdoc, "CptFil", retrieveTi(srcdoc, "TagIdecNavOpr", "CptFil")));

			mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			if (LstFilAlt) mytd.appendChild(makeImgBut(contcontdoc, "ButFilExpand", "icon/expand"));
			else mytd.appendChild(makeImgBut(contcontdoc, "ButFilCollapse", "icon/collapse"));
		};

		if (!LstFilAlt == !contcontdoc.getElementById("LstFil")) {
			mytd = contcontdoc.getElementById("rdynFil");
			clearElem(mytd);
			mytd = contcontdoc.getElementById("dynFil");
			clearElem(mytd);

			if (LstFilAlt) {
				mytd.setAttribute("rowspan", "1");
			} else {
				mytd.setAttribute("rowspan", "2");
				mytd.appendChild(makeIframeLst(contcontdoc, "LstFil", "./PnlIdecNavOpr_LstFil.xml", true));
			};

		} else {
			if (!LstFilAlt) refreshLst(contcontdoc.getElementById("LstFil").contentWindow.document, srcdoc, 1, true, false, "FeedFLstFil",
						parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", "LstFilNumFirstdisp")), [parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numFLstFil"))]);
		};

		if ((ButFilViewAvail == !contcontdoc.getElementById("ButFilView")) || !contcontdoc.getElementById("ButFilNewcrd")) {
			if (LstFilAlt) mytd = contcontdoc.getElementById("dynFil");
			else mytd = contcontdoc.getElementById("rdynFil");
			clearElem(mytd);

			first = true;

			if (ButFilViewAvail) {
				if (first) first = false;
				else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
				mytd.appendChild(makeImgBut(contcontdoc, "ButFilView", "icon/view"));
			};

			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButFilNewcrd", "icon/newcrd"));
		};

		if (ButFilViewAvail) refreshButicon(contcontdoc, "ButFilView", "icon/view", ButFilViewActive, false);
		refreshButicon(contcontdoc, "ButFilNewcrd", "icon/newcrd", ButFilNewcrdActive, false);

	} else setCtlAvail(contcontdoc, "Fil2", false, 0);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Opr", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Opr_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Opr_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Opr_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecNavOpr", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Opr_src").contentDocument;

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
	setSi(srcdoc, "StatAppIdecNavOpr", basectlsref + "Alt", "true");
	refresh();
};

function handleButExpandClick(basectlsref) {
	setSi(srcdoc, "StatAppIdecNavOpr", basectlsref + "Alt", "false");
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
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavOprDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButCrdopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavOprDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoCrdopenReply);
};

function handleLstLoad(lstdoc, ctlsref, ncol, multsel) {
	if (multsel) {
		refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", ctlsref + "NumFirstdisp")),
					parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numsF" + ctlsref)));
	} else {
		refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", ctlsref + "NumFirstdisp")),
					[parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numF" + ctlsref))]);
	};
};

function handleLstSelect(ctlsref, multsel, num) {
	var found, oldNumFLst, numsFLst, oldNumsFLst;

	if (multsel) {
		oldNumsFLst = parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numsF" + ctlsref));

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

		setCi(srcdoc, "ContIacIdecNavOpr", "numsF" + ctlsref, toBase64(numsFLst));

	} else {
		oldNumFLst = parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numF" + ctlsref));
		if (num == oldNumFLst) num = 0;

		setCi(srcdoc, "ContIacIdecNavOpr", "numF" + ctlsref, num);
	};

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecNavOprData", scrJref, "ContIacIdecNavOpr");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function changeLstNumFirstdisp(lstdoc, ctlsref, ncol, multsel, numFirstdisp, dNumFirstdisp) {
	var oldNumFirstdisp = parseInt(retrieveSi(srcdoc, "StatAppIdecNavOpr", ctlsref + "NumFirstdisp"));
	if (dNumFirstdisp != 0) numFirstdisp = oldNumFirstdisp + dNumFirstdisp;

	var cnt = getFeedSize(srcdoc, "FeedF" + ctlsref);

	if (numFirstdisp > (cnt-5+1)) numFirstdisp = cnt-5+1;
	if (numFirstdisp < 1) numFirstdisp = 1;

	if (numFirstdisp != oldNumFirstdisp) {
		setSi(srcdoc, "StatAppIdecNavOpr", ctlsref + "NumFirstdisp", "" + numFirstdisp);

		if (multsel) refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, numFirstdisp, parseUintvec(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numsF" + ctlsref)));
		else refreshLst(lstdoc, srcdoc, ncol, true, multsel, "FeedF" + ctlsref, numFirstdisp, [parseInt(retrieveCi(srcdoc, "ContIacIdecNavOpr", "numF" + ctlsref))]);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "ContIacIdecNavOpr", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "FeedFLstFil", srcdoc)) mask.push("feedFLstFil");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "FeedFLstMis", srcdoc)) mask.push("feedFLstMis");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "FeedFLstTou", srcdoc)) mask.push("feedFLstTou");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "StatAppIdecNavOpr", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "StatShrIdecNavOpr", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecNavOprData", "TagIdecNavOpr", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecNavOprData") {
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
			if (blk.nodeName == "DpchEngIdecNavOprData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Opr");
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

			} else if (blk.nodeName == "DpchEngIdecNavOprData") {
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

