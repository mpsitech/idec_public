/**
  * \file PnlIdecStartFail.js
  * web client functionality for Idec login failure panel
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function refresh(srefIxIdecVLocale) {
	if (srefIxIdecVLocale == "enus") {
		setTextContent(doc, doc.getElementById("Cpt"), "Error");
		setTextContent(doc, doc.getElementById("CptMessage"), "Login failed.");
		setTextContent(doc, doc.getElementById("ButLogin"), "Back");
	} else if (srefIxIdecVLocale == "dech") {
		setTextContent(doc, doc.getElementById("Cpt"), "Fehler");
		setTextContent(doc, doc.getElementById("CptMessage"), "Anmeldung fehlgeschlagen.");
		setTextContent(doc, doc.getElementById("ButLogin"), "Zur\\u00fcck");
	};
};

function handleLoad() {
	doc = document;

	// set captions according to card locale
	refresh(getCrdwnd().getLocale());
};

function handleButLoginClick() {
	getCrdwnd().setCont("Login");
};

