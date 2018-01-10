/**
  * \file DlgIdecMisNew.js
  * web client functionality for dialog DlgIdecMisNew
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

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecMisNew", "Cpt"));

	initCpt(contdoc, "DetCptTit", retrieveTi(srcdoc, "TagDlgIdecMisNew", "DetCptTit"));
	initCpt(contdoc, "DetCptCry", retrieveTi(srcdoc, "TagDlgIdecMisNew", "DetCptCry"));
	initCpt(contdoc, "DetCptReg", retrieveTi(srcdoc, "TagDlgIdecMisNew", "DetCptReg"));
	initCpt(contdoc, "DetCptMun", retrieveTi(srcdoc, "TagDlgIdecMisNew", "DetCptMun"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButCnc"), retrieveTi(srcdoc, "TagDlgIdecMisNew", "ButCnc"));
	setTextContent(ftrdoc, ftrdoc.getElementById("ButCre"), "\u00a0\u00a0" + retrieveTi(srcdoc, "TagDlgIdecMisNew", "ButCre"));

	refresh();
};

function refresh() {
	// IP refresh.vars --- BEGIN

	var ButCncActive = (retrieveSi(srcdoc, "StatShrDlgIdecMisNew", "ButCncActive") == "true");
	var ButCreActive = (retrieveSi(srcdoc, "StatShrDlgIdecMisNew", "ButCreActive") == "true");
	// IP refresh.vars --- END

	// IP refresh --- BEGIN
	refreshTxf(contdoc, "DetTxfTit", "", retrieveCi(srcdoc, "ContIacDlgIdecMisNew", "DetTxfTit"), true, false, true);

	refreshPup(contdoc, srcdoc, "DetPupCry", "", "FeedFDetPupCry", retrieveCi(srcdoc, "ContIacDlgIdecMisNew", "numFDetPupCry"), true, false);

	refreshTxf(contdoc, "DetTxfReg", "", retrieveCi(srcdoc, "ContIacDlgIdecMisNew", "DetTxfReg"), true, false, true);

	refreshTxf(contdoc, "DetTxfMun", "", retrieveCi(srcdoc, "ContIacDlgIdecMisNew", "DetTxfMun"), true, false, true);

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
	var str = serializeDpchAppDo(srcdoc, "DpchAppDlgIdecMisNewDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacDlgIdecMisNew", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecMisNewData", scrJref, "ContIacDlgIdecMisNew");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacDlgIdecMisNew", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecMisNewData", scrJref, "ContIacDlgIdecMisNew");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacDlgIdecMisNew", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecMisNewData", scrJref, "ContIacDlgIdecMisNew");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "ContIacDlgIdecMisNew", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "ContInfDlgIdecMisNew", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "FeedFDetPupCry", srcdoc)) mask.push("feedFDetPupCry");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "StatAppDlgIdecMisNew", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "StatShrDlgIdecMisNew", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngDlgIdecMisNewData", "TagDlgIdecMisNew", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngDlgIdecMisNewData") {
		mergeDpchEngData(dom);
		refresh();
	} else if (dpch == "DpchEngDlgIdecMisNewData") {
		handleDpchEngDlgIdecMisNewData(dom);
	};
};

function handleDpchEngDlgIdecMisNewData(dom) {
	// IP handleDpchEngDlgIdecMisNewData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecMisNewData") {
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

			} else if (blk.nodeName == "DpchEngDlgIdecMisNewData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

