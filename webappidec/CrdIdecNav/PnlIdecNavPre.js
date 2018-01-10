/**
  * \file PnlIdecNavPre.js
  * web client functionality for panel PnlIdecNavPre
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// --- expand state management
function minimize() {
};

function regularize() {
};

// --- view initialization and refresh
function init() {
	if (!doc) return;

	contdoc = doc.getElementById("Pre_cont").contentDocument;

// IP init --- INSERT

	refresh();
};

function refresh() {
	var line;

	var n = 0;

	var TxtMisAvail = (retrieveSi(srcdoc, "StatShrIdecNavPre", "TxtMisAvail") == "true"); if (TxtMisAvail) n++;
	var TxtTouAvail = (retrieveSi(srcdoc, "StatShrIdecNavPre", "TxtTouAvail") == "true"); if (TxtTouAvail) n++;

	line = contdoc.getElementById("line");
	while (line.firstChild) line.removeChild(line.firstChild);

	var i = 0;

	if (TxtMisAvail) {
		i++;

		line.appendChild(makeImgBut("ButMisRemove", "icon/close"));
		if (i == n) line.appendChild(makeSpanCpt("\u00a0" + retrieveTi(srcdoc,  "TagIdecNavPre", "CptMis") + ": " + retrieveCi(srcdoc, "ContInfIdecNavPre", "TxtMis")));
		else line.appendChild(makeSpanCpt("\u00a0" + retrieveTi(srcdoc, "TagIdecNavPre", "CptMis") + ": " + retrieveCi(srcdoc, "ContInfIdecNavPre", "TxtMis") + ",\u00a0\u00a0"));
	};

	if (TxtTouAvail) {
		i++;

		line.appendChild(makeImgBut("ButTouRemove", "icon/close"));
		if (i == n) line.appendChild(makeSpanCpt("\u00a0" + retrieveTi(srcdoc,  "TagIdecNavPre", "CptTou") + ": " + retrieveCi(srcdoc, "ContInfIdecNavPre", "TxtTou")));
		else line.appendChild(makeSpanCpt("\u00a0" + retrieveTi(srcdoc, "TagIdecNavPre", "CptTou") + ": " + retrieveCi(srcdoc, "ContInfIdecNavPre", "TxtTou") + ",\u00a0\u00a0"));
	};

};

// --- event handlers
function handleLoad() {
	scrJref = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc = document;
	srcdoc = doc.getElementById("Pre_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecNavPreDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDoReply);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecNavPreData", "ContInfIdecNavPre", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecNavPreData", "StatShrIdecNavPre", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecNavPreData", "TagIdecNavPre", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecNavPreData") {
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
			if (blk.nodeName == "DpchEngIdecNavPreData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Pre");
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

			} else if (blk.nodeName == "DpchEngIdecNavPreData") {
				mergeDpchEngData(dom);
				refresh();
			};
		};
	};
};

