/**
  * \file DlgIdecUtlQcdnuc.js
  * web client functionality for dialog DlgIdecUtlQcdnuc
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- view initialization and refresh
function initPrp() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initPrp --- BEGIN
	// IP initPrp --- END

	setSi(srcdoc, "StatAppDlgIdecUtlQcdnuc", "initdone", "true");

	refreshPrp();
};

function initCal() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initCal --- BEGIN
	// IP initCal --- END

	setSi(srcdoc, "StatAppDlgIdecUtlQcdnuc", "initdone", "true");

	refreshCal();
};

function init() {
	hdrdoc = doc.getElementById("_hdr").contentDocument;
	ftrdoc = doc.getElementById("_ftr").contentDocument;
	contdoc = null;

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecUtlQcdnuc", "Cpt"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButDne"), retrieveTi(srcdoc, "TagDlgIdecUtlQcdnuc", "ButDne"));

	// includes load of initial dit
	refresh(true, true);
};

function refreshHdr() {
	var numFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecUtlQcdnuc", "numFDse"));

	var num;
	var active, sref, Title;

	var myspan, myrect;

	for (num=1 ; num<=2 ; num++) {
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

function refreshPrp() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshPrp.vars --- BEGIN
	// IP refreshPrp.vars --- END

	// IP refreshPrp --- BEGIN
	// IP refreshPrp --- END
};

function refreshCal() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshCal.vars --- BEGIN
	// IP refreshCal.vars --- END

	// IP refreshCal --- BEGIN
	// IP refreshCal --- END
};

function refresh(updDit, updHdr) {
	var numFDse = retrieveCi(srcdoc, "ContIacDlgIdecUtlQcdnuc", "numFDse");
	var shortDit = retrieveFeedSrefByNum(srcdoc, "FeedFDse", numFDse);

	// IP refresh.vars --- BEGIN
	// IP refresh.vars --- END

	if (updDit || updHdr) refreshHdr();

	if (updDit) {
		// load new dialog item
		doc.getElementById("_cont").src = "./DlgIdecUtlQcdnuc" + shortDit + ".xml" 

	} else {
		// update current dialog item
		if (shortDit == "Prp") {
			refreshPrp();
		} else if (shortDit == "Cal") {
			refreshCal();
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

// --- specific event handlers for app controls of dialog item Prp

// --- specific event handlers for app controls of dialog item Cal

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ditshort, ctlsref) {
	var str = serializeDpchAppDoDlg(srcdoc, "DpchAppDlgIdecUtlQcdnucDo", scrJref, ditshort, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleDseSelect(numFDse) {
	var oldNumFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecUtlQcdnuc", "numFDse"));

	if (oldNumFDse != numFDse) {
		setCi(srcdoc, "ContIacDlgIdecUtlQcdnuc", "numFDse", "" + numFDse);

		setSi(srcdoc, "StatAppDlgIdecUtlQcdnuc", "initdone", "false");

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecUtlQcdnucData", scrJref, "ContIacDlgIdecUtlQcdnuc");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "ContIacDlgIdecUtlQcdnuc", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "ContInfDlgIdecUtlQcdnuc", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "FeedFDse", srcdoc)) mask.push("feedFDse");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "StatAppDlgIdecUtlQcdnuc", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecUtlQcdnucData", "TagDlgIdecUtlQcdnuc", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	var mask;

	if (dpch == "DpchEngDlgIdecUtlQcdnucData") {
		mask = mergeDpchEngData(dom);
		refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
	} else if (dpch == "DpchEngDlgIdecUtlQcdnucData") {
		handleDpchEngDlgIdecUtlQcdnucData(dom);
	};
};

function handleDpchEngDlgIdecUtlQcdnucData(dom) {
	// IP handleDpchEngDlgIdecUtlQcdnucData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecUtlQcdnucData") {
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

			} else if (blk.nodeName == "DpchEngDlgIdecUtlQcdnucData") {
				mask = mergeDpchEngData(dom);
				refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
			};
		};
	};
};

