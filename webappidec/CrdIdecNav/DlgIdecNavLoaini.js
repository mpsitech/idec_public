/**
  * \file DlgIdecNavLoaini.js
  * web client functionality for dialog DlgIdecNavLoaini
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- view initialization and refresh
function initIfi() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initIfi --- BEGIN
	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagDlgIdecNavLoainiIfi", "Cpt"));
	contdoc.getElementById("form").setAttribute("action", "/upload/" + scrJref);
	contdoc.getElementById("But").value = retrieveTi(srcdoc, "TagDlgIdecNavLoainiIfi", "Uld");
	// IP initIfi --- END

	setSi(srcdoc, "StatAppDlgIdecNavLoaini", "initdone", "true");

	refreshIfi();
};

function initImp() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initImp --- BEGIN
	initCpt(contdoc, "CptPrg", retrieveTi(srcdoc, "TagDlgIdecNavLoainiImp", "CptPrg"));
	initBut(contdoc, "ButRun", retrieveTi(srcdoc, "TagDlgIdecNavLoainiImp", "ButRun"));
	initBut(contdoc, "ButSto", retrieveTi(srcdoc, "TagDlgIdecNavLoainiImp", "ButSto"));
	// IP initImp --- END

	setSi(srcdoc, "StatAppDlgIdecNavLoaini", "initdone", "true");

	refreshImp();
};

function initAcv() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initAcv --- BEGIN
	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagDlgIdecNavLoainiAcv", "Cpt"));
	contdoc.getElementById("form").setAttribute("action", "/upload/" + scrJref);
	contdoc.getElementById("But").value = retrieveTi(srcdoc, "TagDlgIdecNavLoainiAcv", "Uld");
	// IP initAcv --- END

	setSi(srcdoc, "StatAppDlgIdecNavLoaini", "initdone", "true");

	refreshAcv();
};

function initLfi() {
	contdoc = doc.getElementById("_cont").contentDocument;

	// IP initLfi --- BEGIN
	setTextContent(contdoc, contdoc.getElementById("Dld"), retrieveTi(srcdoc, "TagDlgIdecNavLoainiLfi", "Dld"));
	// IP initLfi --- END

	setSi(srcdoc, "StatAppDlgIdecNavLoaini", "initdone", "true");

	refreshLfi();
};

function init() {
	hdrdoc = doc.getElementById("_hdr").contentDocument;
	ftrdoc = doc.getElementById("_ftr").contentDocument;
	contdoc = null;

	setTextContent(hdrdoc, hdrdoc.getElementById("Cpt"), retrieveTi(srcdoc, "TagDlgIdecNavLoaini", "Cpt"));

	setTextContent(ftrdoc, ftrdoc.getElementById("ButDne"), retrieveTi(srcdoc, "TagDlgIdecNavLoaini", "ButDne"));

	// includes load of initial dit
	refresh(true, true);
};

function refreshHdr() {
	var numFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecNavLoaini", "numFDse"));

	var num;
	var active, sref, Title;

	var myspan, myrect;

	for (num=1 ; num<=4 ; num++) {
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

function refreshIfi() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshIfi.vars --- BEGIN
	var UldActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoainiIfi", "UldActive") == "true");

	// IP refreshIfi.vars --- END

	// IP refreshIfi --- BEGIN

	if (UldActive) {
		contdoc.getElementById("But").setAttribute("class", "but");
		contdoc.getElementById("But").setAttribute("type", "submit");
	} else {
		contdoc.getElementById("But").setAttribute("class", "butinact");
		contdoc.getElementById("But").setAttribute("type", "reset");
	};

	// IP refreshIfi --- END
};

function refreshImp() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshImp.vars --- BEGIN

	var ButRunActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoainiImp", "ButRunActive") == "true");
	var ButStoActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoainiImp", "ButStoActive") == "true");

	// IP refreshImp.vars --- END

	// IP refreshImp --- BEGIN
	refreshTxtt(contdoc, "TxtPrg", retrieveCi(srcdoc, "ContInfDlgIdecNavLoainiImp", "TxtPrg"));

	refreshBut(contdoc, "ButRun", ButRunActive, false);
	refreshBut(contdoc, "ButSto", ButStoActive, false);

	// IP refreshImp --- END
};

function refreshAcv() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshAcv.vars --- BEGIN
	var UldActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoainiAcv", "UldActive") == "true");

	// IP refreshAcv.vars --- END

	// IP refreshAcv --- BEGIN

	if (UldActive) {
		contdoc.getElementById("But").setAttribute("class", "but");
		contdoc.getElementById("But").setAttribute("type", "submit");
	} else {
		contdoc.getElementById("But").setAttribute("class", "butinact");
		contdoc.getElementById("But").setAttribute("type", "reset");
	};

	// IP refreshAcv --- END
};

function refreshLfi() {
	if (!contdoc.getElementById("tbl")) return;

	// IP refreshLfi.vars --- BEGIN
	var DldActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoainiLfi", "DldActive") == "true");

	// IP refreshLfi.vars --- END

	// IP refreshLfi --- BEGIN

	if (DldActive) {
		contdoc.getElementById("Dld").setAttribute("class", "but");
		contdoc.getElementById("Dld").setAttribute("href", "/download/" + scrJref);
		contdoc.getElementById("Dld").setAttribute("target", "_blank");
	} else {
		contdoc.getElementById("Dld").setAttribute("class", "butinact");
		contdoc.getElementById("Dld").setAttribute("href", "#");
		contdoc.getElementById("Dld").setAttribute("target", "_self");
	};

	// IP refreshLfi --- END
};

function refresh(updDit, updHdr) {
	var numFDse = retrieveCi(srcdoc, "ContIacDlgIdecNavLoaini", "numFDse");
	var shortDit = retrieveFeedSrefByNum(srcdoc, "FeedFDse", numFDse);

	// IP refresh.vars --- BEGIN
	var ButDneActive = (retrieveSi(srcdoc, "StatShrDlgIdecNavLoaini", "ButDneActive") == "true");
	// IP refresh.vars --- END

	if (updDit || updHdr) refreshHdr();

	if (updDit) {
		// load new dialog item
		doc.getElementById("_cont").src = "./DlgIdecNavLoaini" + shortDit + ".xml" 

	} else {
		// update current dialog item
		if (shortDit == "Ifi") {
			refreshIfi();
		} else if (shortDit == "Imp") {
			refreshImp();
		} else if (shortDit == "Acv") {
			refreshAcv();
		} else if (shortDit == "Lfi") {
			refreshLfi();
		};
	};

	// IP refresh --- BEGIN
	refreshBut(ftrdoc, "ButDne", ButDneActive, false);
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

// --- specific event handlers for app controls of dialog item Ifi

// --- specific event handlers for app controls of dialog item Imp

// --- specific event handlers for app controls of dialog item Acv

// --- specific event handlers for app controls of dialog item Lfi

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ditshort, ctlsref) {
	var str = serializeDpchAppDoDlg(srcdoc, "DpchAppDlgIdecNavLoainiDo", scrJref, ditshort, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleDseSelect(numFDse) {
	var oldNumFDse = parseInt(retrieveCi(srcdoc, "ContIacDlgIdecNavLoaini", "numFDse"));

	if (oldNumFDse != numFDse) {
		setCi(srcdoc, "ContIacDlgIdecNavLoaini", "numFDse", "" + numFDse);

		setSi(srcdoc, "StatAppDlgIdecNavLoaini", "initdone", "false");

		var str = serializeDpchAppData(srcdoc, "DpchAppDlgIdecNavLoainiData", scrJref, "ContIacDlgIdecNavLoaini");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "ContIacDlgIdecNavLoaini", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "ContInfDlgIdecNavLoaini", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "ContInfDlgIdecNavLoainiImp", srcdoc)) mask.push("continfimp");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "FeedFDse", srcdoc)) mask.push("feedFDse");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "FeedFSge", srcdoc)) mask.push("feedFSge");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatAppDlgIdecNavLoaini", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatShrDlgIdecNavLoaini", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatShrDlgIdecNavLoainiAcv", srcdoc)) mask.push("statshracv");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatShrDlgIdecNavLoainiIfi", srcdoc)) mask.push("statshrifi");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatShrDlgIdecNavLoainiImp", srcdoc)) mask.push("statshrimp");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "StatShrDlgIdecNavLoainiLfi", srcdoc)) mask.push("statshrlfi");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "TagDlgIdecNavLoaini", srcdoc)) mask.push("tag");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "TagDlgIdecNavLoainiAcv", srcdoc)) mask.push("tagacv");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "TagDlgIdecNavLoainiIfi", srcdoc)) mask.push("tagifi");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "TagDlgIdecNavLoainiImp", srcdoc)) mask.push("tagimp");
	if (updateSrcblock(dom, "DpchEngDlgIdecNavLoainiData", "TagDlgIdecNavLoainiLfi", srcdoc)) mask.push("taglfi");

	return mask;
};

function handleDpchEng(dom, dpch) {
	var mask;

	if (dpch == "DpchEngDlgIdecNavLoainiData") {
		mask = mergeDpchEngData(dom);
		refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
	} else if (dpch == "DpchEngDlgIdecNavLoainiData") {
		handleDpchEngDlgIdecNavLoainiData(dom);
	};
};

function handleDpchEngDlgIdecNavLoainiData(dom) {
	// IP handleDpchEngDlgIdecNavLoainiData --- INSERT
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngDlgIdecNavLoainiData") {
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

			} else if (blk.nodeName == "DpchEngDlgIdecNavLoainiData") {
				mask = mergeDpchEngData(dom);
				refresh(mask.indexOf("contiac") != -1, mask.indexOf("feedFDse") != -1);
			};
		};
	};
};

