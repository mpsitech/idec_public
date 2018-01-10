/**
  * \file PnlIdecStartLogin.js
  * web client functionality for Idec login panel
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function refresh(srefIxIdecVLocale) {
	var pup = doc.getElementById("PupLocale");
	var opt;

	clearElem(pup);

	if (srefIxIdecVLocale == "enus") {
		setTextContent(doc, doc.getElementById("Cpt"), "Login");

		opt = doc.createElement("option");
		opt.setAttribute("value", "enus");
		setTextContent(doc, opt, "English (United States)");
		pup.appendChild(opt);
		opt = doc.createElement("option");
		opt.setAttribute("value", "dech");
		setTextContent(doc, opt, "German (Switzerland)");
		pup.appendChild(opt);

		setTextContent(doc, doc.getElementById("CptUsername"), "User name");
		setTextContent(doc, doc.getElementById("CptPassword"), "Password");
		setTextContent(doc, doc.getElementById("ButReset"), "Reset");
		setTextContent(doc, doc.getElementById("ButLogin"), "Login");
	} else if (srefIxIdecVLocale == "dech") {
		setTextContent(doc, doc.getElementById("Cpt"), "Anmeldung");

		opt = doc.createElement("option");
		opt.setAttribute("value", "enus");
		setTextContent(doc, opt, "Englisch (Vereinigte Staaten)");
		pup.appendChild(opt);
		opt = doc.createElement("option");
		opt.setAttribute("value", "dech");
		setTextContent(doc, opt, "Deutsch (Schweiz)");
		pup.appendChild(opt);

		setTextContent(doc, doc.getElementById("CptUsername"), "Benutzername");
		setTextContent(doc, doc.getElementById("CptPassword"), "Passwort");
		setTextContent(doc, doc.getElementById("ButReset"), "Zur\\u00fccksetzen");
		setTextContent(doc, doc.getElementById("ButLogin"), "Anmelden");
	};

	pup.value = srefIxIdecVLocale;
};

function handleLoad() {
	doc = document;

	// set captions according to card locale
	refresh(getCrdwnd().getLocale());
};

function handlePupLocaleChange() {
	srefIxIdecVLocale = doc.getElementById("PupLocale").value;
	refresh(srefIxIdecVLocale);

	// notify card to change cookie
	getCrdwnd().setLocale(srefIxIdecVLocale);
};

function handleTxfPasswordKey(evt) {
	if (evt.keyCode == 13) {
		handleButLoginClick();
		return false;
	};

	return true;
};

function handleButResetClick() {
	doc.getElementById("TxfUsername").value = "";
	doc.getElementById("TxfPassword").value = "";
};

function handleButLoginClick() {
	var str = serializeDpchAppLogin(doc.getElementById("TxfPassword").value, doc.getElementById("TxfUsername").value, getCrdwnd().getLocale());
	sendReq(str, doc, handleDpchAppLoginReply);
};

function handleDpchAppLoginReply() {
	var dom;

	var accepted, scrJref;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		accepted = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:accepted");
		scrJref = retrieveValue(dom, "//idec:DpchEngIdecConfirm/idec:scrJref");

		if (accepted == "true") {
			var str = serializeDpchApp("DpchAppIdecInit", scrJref);
			sendReq(str, doc, handleDpchAppInitReply);

		} else {
			getCrdwnd().setCont("Fail");
		};
	};
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngSessIdecData") {
				var scrJrefCrdnav = retrieveValue(dom, "//idec:DpchEngSessIdecData/idec:StatShrSessIdec/idec:Si[@sref='scrJrefCrdnav']");

				if (scrJrefCrdnav == "") getCrdwnd().setCont("Fail");
				else window.open("/web/CrdIdecNav/CrdIdecNav.html?scrJref=" + scrJrefCrdnav, "_parent");
			};
		};
	};
};

function serializeDpchAppLogin(password, username, srefIxIdecVLocale) {
	var dpch, elem, txt;
	var ser;
	var str;

	dpch = doc.createElement("DpchAppRootIdecLogin");

	elem = doc.createElement("password");
	txt = doc.createTextNode(password);
	elem.appendChild(txt);
	dpch.appendChild(elem);

	elem = doc.createElement("username");
	txt = doc.createTextNode(username);
	elem.appendChild(txt);
	dpch.appendChild(elem);

	elem = doc.createElement("srefIxIdecVLocale");
	txt = doc.createTextNode(srefIxIdecVLocale);
	elem.appendChild(txt);
	dpch.appendChild(elem);	

	ser = new XMLSerializer();

	str = ser.serializeToString(dpch);

	return(str);
};

