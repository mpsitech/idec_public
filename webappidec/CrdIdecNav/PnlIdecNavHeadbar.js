/**
  * \file PnlIdecNavHeadbar.js
  * web client functionality for panel PnlIdecNavHeadbar
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// --- view initialization
function init() {
	contdoc = doc.getElementById("Headbar_cont").contentDocument;

	var width = 995;

	var appw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenAppCptwidth"));
	contdoc.getElementById("colMenApp").setAttribute("width", "" + appw);
	width -= appw+1;

	var sesw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenSesCptwidth"));
	contdoc.getElementById("colMenSes").setAttribute("width", "" + sesw);
	width -= sesw+1;

	var crdw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenCrdCptwidth"));
	contdoc.getElementById("colMenCrd").setAttribute("width", "" + crdw);
	width -= crdw+1;

	contdoc.getElementById("colFill").setAttribute("width", "" + width);

	var MenCrdAvail = (retrieveSi(srcdoc, "StatShrIdecNavHeadbar", "MenCrdAvail") == "true");
	if (!MenCrdAvail) contdoc.getElementById("tdMenCrd").setAttribute("class", "hide");

	// captions
	setTextContent(contdoc, contdoc.getElementById("MenApp"), retrieveTi(srcdoc, "TagIdecNavHeadbar", "MenApp") + "\\u00a0");
	setTextContent(contdoc, contdoc.getElementById("MenSes"), "\\u00a0" + retrieveTi(srcdoc, "TagIdecNavHeadbar", "MenSes") + "\\u00a0");
	setTextContent(contdoc, contdoc.getElementById("MenCrd"), "\\u00a0" + retrieveTi(srcdoc, "TagIdecNavHeadbar", "MenCrd") + "\\u00a0");
};

// --- event handlers
function handleLoad() {
	scrJref = location.search.substr(location.search.indexOf("scrJref=")+8);

	doc = document;
	srcdoc = doc.getElementById("Headbar_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

function handleMenAppClick() {
	var width;
	width = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenAppWidth"));

	getCrdwnd().toggleMenu("App", 3, width, 63);
};

function handleMenSesClick() {
	var appw;
	var width;

	appw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenAppCptwidth"));
	width = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenSesWidth"));

	getCrdwnd().toggleMenu("Ses", 3+appw+1, width, 83);
};

function handleMenCrdClick() {
	var appw, sesw;
	var width;

	appw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenAppCptwidth"));
	sesw = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenSesCptwidth"));
	width = parseInt(retrieveSi(srcdoc, "StgInfIdecNavHeadbar", "MenCrdWidth"));

	getCrdwnd().toggleMenu("Crd", 3+appw+1+sesw+1, width, 183);
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecNavHeadbarData", "StatShrIdecNavHeadbar", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecNavHeadbarData", "StgInfIdecNavHeadbar", srcdoc)) mask.push("stginf");
	if (updateSrcblock(dom, "DpchEngIdecNavHeadbarData", "TagIdecNavHeadbar", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecNavHeadbarData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Headbar");
			};
		};
	};
};

