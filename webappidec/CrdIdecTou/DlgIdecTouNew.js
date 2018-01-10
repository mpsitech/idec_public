/**
  * \file DlgIdecTouNew.js
  * web client functionality for dialog DlgIdecTouNew
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- view initialization and refresh
function init() {
	hdrdoc = doc.getElementById("_hdr").contentDocument;
	contdoc = doc.getElementById("_cont").contentDocument;
	ftrdoc = doc.getElementById("_ftr").contentDocument;

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecTouNew", "Cpt"));

	initCpt(contdoc, "DetCptMis", retrieveTi(srcdoc, "TagDlgIdecTouNew", "DetCptMis"));
	initCpt(contdoc, "DetCptTit", retrieveTi(srcdoc, "TagDlgIdecTouNew", "DetCptTit"));
	initCpt(contdoc, "DetCptAre", retrieveTi(srcdoc, "TagDlgIdecTouNew", "DetCptAre"));
	initCpt(contdoc, "DetCptThe", retrieveTi(srcdoc, "TagDlgIdecTouNew", "DetCptThe"));
	initCpt(contdoc, "DetCptPhi", retrieveTi(srcdoc, "TagDlgIdecTouNew", "DetCptPhi"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButCnc"), retrieveTi(srcdoc, "TagDlgIdecTouNew", "ButCnc"));
	setTextContent(ftrdoc, ftrdoc.getElementById("ButCre"), "\u00a0\u00a0" + retrieveTi(srcdoc, "TagDlgIdecTouNew", "ButCre"));

	refresh();
};

function refresh() {
	// IP refresh.vars --- BEGIN
	var DetPupMisActive = (retrieveSi(srcdoc, "StatShrDlgIdecTouNew", "DetPupMisActive") == "true");

	var ButCncActive = (retrieveSi(srcdoc, "StatShrDlgIdecTouNew", "ButCncActive") == "true");
	var ButCreActive = (retrieveSi(srcdoc, "StatShrDlgIdecTouNew", "ButCreActive") == "true");
	// IP refresh.vars --- END

	// IP refresh --- BEGIN
	refreshPup(contdoc, srcdoc, "DetPupMis", "", "FeedFDetPupMis", retrieveCi(srcdoc, "ContIacDlgIdecTouNew", "numFDetPupMis"), DetPupMisActive, false);

	refreshTxf(contdoc, "DetTxfTit", "", retrieveCi(srcdoc, "ContIacDlgIdecTouNew", "DetTxfTit"), true, false, true);

	refreshTxf(contdoc, "DetTxfAre", "", retrieveCi(srcdoc, "ContIacDlgIdecTouNew", "DetTxfAre"), true, false, true);

	refreshTxf(contdoc, "DetTxfThe", "s", retrieveCi(srcdoc, "ContIacDlgIdecTouNew", "DetTxfThe"), true, false, true);

	refreshTxf(contdoc, "DetTxfPhi", "s", retrieveCi(srcdoc, "ContIacDlgIdecTouNew", "DetTxfPhi"), true, false, true);

	refreshBut(ftrdoc, "ButCnc", ButCncActive, false);
	refreshBut(ftrdoc, "ButCre", ButCreActive, false);
	// IP refresh --- END
};

// --- event handlers
function handleLoad() {
	scrJref = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc = document;
	srcdoc = doc.getElementById("_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppDlgIdecTouNewDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacDlgIdecTouNew", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecTouNewData", scrJref, "ContIacDlgIdecTouNew");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacDlgIdecTouNew", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecTouNewData", scrJref, "ContIacDlgIdecTouNew");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacDlgIdecTouNew", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecTouNewData", scrJref, "ContIacDlgIdecTouNew");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "ContIacDlgIdecTouNew", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "ContInfDlgIdecTouNew", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "FeedFDetPupMis", srcdoc)) mask.push("feedFDetPupMis");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "StatAppDlgIdecTouNew", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "StatShrDlgIdecTouNew", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngDlgIdecTouNewData", "TagDlgIdecTouNew", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngDlgIdecTouNewData") {
		mergeDpchEngData(dom);
		refresh();
	} else if (dpch == "DpchEngDlgIdecTouNewData") {
		handleDpchEngDlgIdecTouNewData(dom);
	};
};

function handleDpchEngDlgIdecTouNewData(dom) {
	// IP handleDpchEngDlgIdecTouNewData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecTouNewData") {
				mergeDpchEngData(dom);
				init();
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

			} else if (blk.nodeName == "DpchEngIdecAlert") {
				getCrdwnd().showAlr(retrieveValue(dom, "//idec:DpchEngIdecAlert/idec:scrJref"),
							retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:ContInfIdecAlert"),
							retrieveBlock(dom, "//idec:DpchEngIdecAlert/idec:FeedFMcbAlert"));;

			} else if (blk.nodeName == "DpchEngDlgIdecTouNewData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

