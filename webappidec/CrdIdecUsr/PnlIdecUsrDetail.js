/**
  * \file PnlIdecUsrDetail.js
  * web client functionality for panel PnlIdecUsrDetail
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- INSERT

// --- expand state management
function minimize(updh) {
	if (retrieveSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate") == "mind") return;

	setSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate", "mind");

	// change container heights
	getRecwnd().changeHeight("Detail", 30, updh);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Detail_side").setAttribute("height", "30");
	doc.getElementById("Detail_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Detail_side").src = "./PnlIdecUsrDetail_aside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecUsrDetail_a.html";
};

function regularize() {
	if (retrieveSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate") == "regd") return;

	setSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate", "regd");

	// change content (container heights in refreshBD)
	doc.getElementById("Detail_side").src = "./PnlIdecUsrDetail_bside.html";
	doc.getElementById("Detail_cont").src = "./PnlIdecUsrDetail_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecUsrDetail", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Detail_side").contentDocument;
	contdoc = doc.getElementById("Detail_cont").contentDocument;
	contcontdoc = contdoc.getElementById("Detail_cont").contentDocument;
	ftrdoc = contdoc.getElementById("Detail_ftr").contentDocument;

	// IP initBD --- BEGIN
	initCpt(contcontdoc, "CptPrs", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptPrs"));
	initCpt(contcontdoc, "CptSrf", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptSrf"));
	initCpt(contcontdoc, "CptUsg", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptUsg"));
	initCpt(contcontdoc, "CptSte", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptSte"));
	refreshPup(contcontdoc, srcdoc, "PupSte", "", "FeedFPupSte", retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupSte"), retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupSteActive"), false);
	initCpt(contcontdoc, "CptLcl", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptLcl"));
	refreshPup(contcontdoc, srcdoc, "PupLcl", "", "FeedFPupLcl", retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupLcl"), retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupLclActive"), false);
	initCpt(contcontdoc, "CptUlv", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptUlv"));
	refreshPup(contcontdoc, srcdoc, "PupUlv", "", "FeedFPupUlv", retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupUlv"), retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupUlvActive"), false);
	initCpt(contcontdoc, "CptPwd", retrieveTi(srcdoc, "TagIdecUsrDetail", "CptPwd"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate");

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
	var height = 217; // full cont height

	// IP refreshBD.vars --- BEGIN
	var TxtPrsActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "TxtPrsActive") == "true");

	var TxtSrfActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "TxtSrfActive") == "true");

	var TxtUsgActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "TxtUsgActive") == "true");
	var ButUsgViewAvail = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "ButUsgViewAvail") == "true");
	var ButUsgViewActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "ButUsgViewActive") == "true");

	var PupJActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupJActive") == "true");
	var ButJEditAvail = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "ButJEditAvail") == "true");

	var PupSteActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupSteActive") == "true");

	var PupLclActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupLclActive") == "true");

	var PupUlvActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "PupUlvActive") == "true");

	var TxfPwdActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "TxfPwdActive") == "true");

	var ButSaveActive = (retrieveSi(srcdoc, "StatShrIdecUsrDetail", "ButSaveActive") == "true");
	var mytd, first;
	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshTxt(contcontdoc, "TxtPrs", retrieveCi(srcdoc, "ContInfIdecUsrDetail", "TxtPrs"));

	refreshTxt(contcontdoc, "TxtSrf", retrieveCi(srcdoc, "ContInfIdecUsrDetail", "TxtSrf"));

	if ((ButUsgViewAvail == !contcontdoc.getElementById("ButUsgView"))) {
		mytd = contcontdoc.getElementById("rdynUsg");
		clearElem(mytd);

		first = true;

		if (ButUsgViewAvail) {
			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButUsgView", "icon/view"));
		};
	};

	refreshTxt(contcontdoc, "TxtUsg", retrieveCi(srcdoc, "ContInfIdecUsrDetail", "TxtUsg"));

	if (ButUsgViewAvail) refreshButicon(contcontdoc, "ButUsgView", "icon/view", ButUsgViewActive, false);

	if ((ButJEditAvail == !contcontdoc.getElementById("ButJEdit"))) {
		mytd = contcontdoc.getElementById("rdynJ");
		clearElem(mytd);

		first = true;

		if (ButJEditAvail) {
			if (first) first = false;
			else mytd.appendChild(contcontdoc.createTextNode("\u00a0"));
			mytd.appendChild(makeImgBut(contcontdoc, "ButJEdit", "icon/edit"));
		};
	};

	refreshPup(contcontdoc, srcdoc, "PupJ", "s", "FeedFPupJ", retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupJ"), PupJActive, false);

	contcontdoc.getElementById("PupSte").value = retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupSte");

	contcontdoc.getElementById("PupLcl").value = retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupLcl");

	contcontdoc.getElementById("PupUlv").value = retrieveCi(srcdoc, "ContIacIdecUsrDetail", "numFPupUlv");

	refreshTxf(contcontdoc, "TxfPwd", "s", retrieveCi(srcdoc, "ContIacIdecUsrDetail", "TxfPwd"), TxfPwdActive, false, true);

	refreshButicon(ftrdoc, "ButSave", "icon/save", ButSaveActive, false);
	// IP refreshBD --- END

	getRecwnd().changeHeight("Detail", height+26, true);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+26));
	doc.getElementById("Detail_side").setAttribute("height", "" + (height+26));
	doc.getElementById("Detail_cont").setAttribute("height", "" + (height+26));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+26-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Detail_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatAppIdecUsrDetail", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Detail_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

function handleButMinimizeClick() {
	minimize(true);
};

function handleButRegularizeClick() {
	regularize(true);
};

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUsrDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleButCrdopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUsrDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoCrdopenReply);
};

function handleButDlgopenClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecUsrDetailDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoDlgopenReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecUsrDetail", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUsrDetailData", scrJref, "ContIacIdecUsrDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleTxfKey(_doc, ctlsref, size, evt) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	if (evt.keyCode == 13) {
		setCi(srcdoc, "ContIacIdecUsrDetail", ctlsref, elem.value);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecUsrDetailData", scrJref, "ContIacIdecUsrDetail");
		sendReq(str, doc, handleDpchAppDataDoReply);

		return false;
	};

	return true;
};

function handleTxfChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "txf" + size + "mod");

	setCi(srcdoc, "ContIacIdecUsrDetail", ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecUsrDetailData", scrJref, "ContIacIdecUsrDetail");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "ContIacIdecUsrDetail", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "ContInfIdecUsrDetail", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "FeedFPupJ", srcdoc)) mask.push("feedFPupJ");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "FeedFPupLcl", srcdoc)) mask.push("feedFPupLcl");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "FeedFPupSte", srcdoc)) mask.push("feedFPupSte");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "FeedFPupUlv", srcdoc)) mask.push("feedFPupUlv");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "StatAppIdecUsrDetail", srcdoc)) mask.push("statapp");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "StatShrIdecUsrDetail", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecUsrDetailData", "TagIdecUsrDetail", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecUsrDetailData") {
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
			if (blk.nodeName == "DpchEngIdecUsrDetailData") {
				mergeDpchEngData(dom);
				init();

				getRecwnd().setInitdone("Detail");
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

			} else if (blk.nodeName == "DpchEngIdecUsrDetailData") {
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

function handleDpchAppDoDlgopenReply() {
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

				if ((accepted == "true") && (sref != "")) getCrdwnd().showDlg(sref, _scrJref);
			};
		};
	};
};

