/**
  * \file PnlIdecStartLogout.js
  * web client functionality for Idec logout panel
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function refresh(srefIxIdecVLocale) {
	if (srefIxIdecVLocale == "enus") {
		setTextContent(doc, doc.getElementById("Cpt"), "Logout");
		setTextContent(doc, doc.getElementById("CptMessage"), "Your session has been terminated.");
		setTextContent(doc, doc.getElementById("ButLogin"), "Login screen");
	} else if (srefIxIdecVLocale == "dech") {
		setTextContent(doc, doc.getElementById("Cpt"), "Abmeldung");
		setTextContent(doc, doc.getElementById("CptMessage"), "Ihre Sitzung wurde beendet.");
		setTextContent(doc, doc.getElementById("ButLogin"), "Anmeldefenster");
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

