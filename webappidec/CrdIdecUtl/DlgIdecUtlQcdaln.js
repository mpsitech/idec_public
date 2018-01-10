/**
  * \file DlgIdecUtlQcdaln.js
  * web client functionality for dialog DlgIdecUtlQcdaln
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

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecUtlQcdaln", "Cpt"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButDne"), retrieveTi(srcdoc, "TagDlgIdecUtlQcdaln", "ButDne"));

	refresh();
};

function refresh() {
	// IP refresh.vars --- BEGIN

	// IP refresh.vars --- END

	// IP refresh --- BEGIN

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

function handleButClick(ditshort, ctlsref) {
	var str = serializeDpchAppDoDlg(srcdoc, "DpchAppDlgIdecUtlQcdalnDo", scrJref, ditshort, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleDseSelect(numFDse) {
	var oldNumFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecUtlQcdaln", "numFDse"));

	if (oldNumFDse != numFDse) {
		setCi(srcdoc, "ContIacDlgIdecUtlQcdaln", "numFDse", "" + numFDse);

		setSi(srcdoc, "StatAppDlgIdecUtlQcdaln", "initdone", "false");

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecUtlQcdalnData", scrJref, "ContIacDlgIdecUtlQcdaln");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "ContIacDlgIdecUtlQcdaln", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "ContInfDlgIdecUtlQcdaln", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "FeedFDse", srcdoc)) mask.push("feedFDse");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "StatAppDlgIdecUtlQcdaln", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdalnData", "TagDlgIdecUtlQcdaln", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngDlgIdecUtlQcdalnData") {
		mergeDpchEngData(dom);
		refresh();
	} else if (dpch == "DpchEngDlgIdecUtlQcdalnData") {
		handleDpchEngDlgIdecUtlQcdalnData(dom);
	};
};

function handleDpchEngDlgIdecUtlQcdalnData(dom) {
	// IP handleDpchEngDlgIdecUtlQcdalnData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecUtlQcdalnData") {
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

			} else if (blk.nodeName == "DpchEngDlgIdecUtlQcdalnData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

