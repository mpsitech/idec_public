/**
  * \file DlgIdecFilExtrmed.js
  * web client functionality for dialog DlgIdecFilExtrmed
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- view initialization and refresh
function initPvw() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initPvw --- BEGIN
	// IP initPvw --- END

	setSi(srcdoc, "StatAppDlgIdecFilExtrmed", "initdone", "true");

	refreshPvw();
};

function initSel() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initSel --- BEGIN
	// IP initSel --- END

	setSi(srcdoc, "StatAppDlgIdecFilExtrmed", "initdone", "true");

	refreshSel();
};

function initFia() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initFia --- BEGIN
	// IP initFia --- END

	setSi(srcdoc, "StatAppDlgIdecFilExtrmed", "initdone", "true");

	refreshFia();
};

function init() {
	hdrdoc = doc.getElementById("_hdr").contentDocument;
	ftrdoc = doc.getElementById("_ftr").contentDocument;
	contdoc = null;

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecFilExtrmed", "Cpt"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButDne"), retrieveTi(srcdoc, "TagDlgIdecFilExtrmed", "ButDne"));

	// includes load of initial dit
	refresh(true, true);
};

function refreshHdr() {
	var numFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecFilExtrmed", "numFDse"));

	var num;
	var active, sref, Title;

	var myspan, myrect;

	for (num=1 ; num<=3 ; num++) {
		sref = retrieveValue(srcdoc, "//idec:FeedFDse/idec:Fi[@num='" + num + "']/idec:sref");
		Title = retrieveValue(srcdoc, "//idec:FeedFDse/idec:Fi[@num='" + num + "']/idec:tit1");

		myspan = hdrdoc.getElementById("Cpt" + sref);
		myrect = hdrdoc.getElementById("Dit" + sref);

		setTextContent(hdrdoc, myspan, Title);

		if (num == numFDse) {
			myspan.setAttribute("class", "hdr_ditsel");
			myrect.setAttribute("class", "hdr_ditsels");
		} else {
			myspan.setAttribute("class", "hdr_dit");
			myspan.setAttribute("onclick", "handleDseSelect(" + num + ")");
			myrect.setAttribute("class", "hdr_dits");
			myrect.setAttribute("onclick", "handleDseSelect(" + num + ")");
		};
	};
};

function refreshPvw() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshPvw.vars --- BEGIN
	// IP refreshPvw.vars --- END

	// IP refreshPvw --- BEGIN
	// IP refreshPvw --- END
};

function refreshSel() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshSel.vars --- BEGIN
	// IP refreshSel.vars --- END

	// IP refreshSel --- BEGIN
	// IP refreshSel --- END
};

function refreshFia() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshFia.vars --- BEGIN
	// IP refreshFia.vars --- END

	// IP refreshFia --- BEGIN
	// IP refreshFia --- END
};

function refresh(updDit, updHdr) {
	var numFDse = retrieveCi(srcdoc, "ContIacDlgIdecFilExtrmed", "numFDse");
	var shortDit = retrieveFeedSrefByNum(srcdoc, "FeedFDse", numFDse);

	// IP refresh.vars --- BEGIN
	// IP refresh.vars --- END

	if (updDit || updHdr) refreshHdr();

	if (updDit) {
		// load new dialog item
		doc.getElementById("_cont").src = "./DlgIdecFilExtrmed" + shortDit + ".xml" 

	} else {
		// update current dialog item
		if (shortDit == "Pvw") {
			refreshPvw();
		} else if (shortDit == "Sel") {
			refreshSel();
		} else if (shortDit == "Fia") {
			refreshFia();
		};
	};

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

// --- specific event handlers for app controls of dialog item Pvw

// --- specific event handlers for app controls of dialog item Sel

// --- specific event handlers for app controls of dialog item Fia

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ditshort, ctlsref) {
	var str = serializeDpchAppDoDlg(srcdoc, "DpchAppDlgIdecFilExtrmedDo", scrJref, ditshort, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleDseSelect(numFDse) {
	var oldNumFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecFilExtrmed", "numFDse"));

	if (oldNumFDse != numFDse) {
		setCi(srcdoc, "ContIacDlgIdecFilExtrmed", "numFDse", "" + numFDse);

		setSi(srcdoc, "StatAppDlgIdecFilExtrmed", "initdone", "false");

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecFilExtrmedData", scrJref, "ContIacDlgIdecFilExtrmed");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "ContIacDlgIdecFilExtrmed", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "ContInfDlgIdecFilExtrmed", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "FeedFDse", srcdoc)) mask.push("feedFDse");
	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "StatAppDlgIdecFilExtrmed", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecFilExtrmedData", "TagDlgIdecFilExtrmed", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	var mask;

	if (dpch == "DpchEngDlgIdecFilExtrmedData") {
		mask = mergeDpchEngData(dom);
		refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
	} else if (dpch == "DpchEngDlgIdecFilExtrmedData") {
		handleDpchEngDlgIdecFilExtrmedData(dom);
	};
};

function handleDpchEngDlgIdecFilExtrmedData(dom) {
	// IP handleDpchEngDlgIdecFilExtrmedData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecFilExtrmedData") {
				mergeDpchEngData(dom);
				init();
			};
		};
	};
};

function handleDpchAppDataDoReply() {
	var dom, blk, mask;

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

			} else if (blk.nodeName == "DpchEngDlgIdecFilExtrmedData") {
				mask = mergeDpchEngData(dom);
				refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
			};
		};
	};
};

