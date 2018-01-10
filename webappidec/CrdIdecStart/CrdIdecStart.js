/**
  * \file CrdIdecStart.js
  * web client functionality for Idec start page
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

function setCont(pnlshort) {
	if (pnlshort == "Login") {
		doc.getElementById("tdCont").setAttribute("height", "128");
		doc.getElementById("Cont").setAttribute("height", "120");
	} else if (pnlshort == "Fail") {
		doc.getElementById("tdCont").setAttribute("height", "103");
		doc.getElementById("Cont").setAttribute("height", "95");
	} else if (pnlshort == "Logout") {
		doc.getElementById("tdCont").setAttribute("height", "103");
		doc.getElementById("Cont").setAttribute("height", "95");
	};

	doc.getElementById("Cont").src = "./PnlIdecStart" + pnlshort + ".html";
};

function getLocale() {
	return(doc.srefIxIdecVLocale);
};

function setLocale(srefIxIdecVLocale) {
	doc.srefIxIdecVLocale = srefIxIdecVLocale;

	// store locale to cookie
	var expdate = new Date();
	var exptime = expdate.getTime() + (30*24*3600*1000);
	expdate.setTime(exptime);

	doc.cookie = "srefIxIdecVLocale=" + srefIxIdecVLocale + ";expires=" + expdate.toGMTString();
};

function handleLoad() {
	var cookiestr;
	var strptr;
	var pnlshort;

	doc = document;

	// set locale according to cookie (default: enus)
	doc.srefIxIdecVLocale = "enus";

	if (doc.cookie) {
		cookiestr = doc.cookie;

		strptr = cookiestr.search("srefIxIdecVLocale");
		if (strptr != -1) {
			cookiestr = cookiestr.substring(strptr);
			if (cookiestr.search(";") == -1)
				doc.srefIxIdecVLocale = cookiestr.substring(cookiestr.search("=")+1);
			else
				doc.srefIxIdecVLocale = cookiestr.substring(cookiestr.search("=")+1, cookiestr.search(";"));

			// set cookie again, to postpone expiry date
			setLocale(doc.srefIxIdecVLocale);
		};
	};

	// determine panel to display from URL
	if (window.location.search.indexOf("do=") == -1) {
		pnlshort = "Login";

	} else {
		pnlshort = window.location.search.substr(window.location.search.indexOf("do=")+3);
		if ( (pnlshort != "Fail") && (pnlshort != "Logout") ) pnlshort = "Login";
	};

	setCont(pnlshort);
};

