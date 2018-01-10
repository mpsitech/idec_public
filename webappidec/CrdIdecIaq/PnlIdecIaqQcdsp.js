/**
  * \file PnlIdecIaqQcdsp.js
  * web client functionality for panel PnlIdecIaqQcdsp
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

// IP cust --- IBEGIN
function refreshLive(mask) {
	if (!contcontdoc) return;

	var x0, y0;

	var ix, ix2;

	var x0q, x1q, x0i, x1i;
	var y0q, y1q, y0i, y1i;

	var T0, T1, T;
	var pT0, pT1, pT;

	var myrect;
	var z, r, g, b;

	var s;

	// QCD related
	var hpix = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQhp"));
	var dpix = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQdp"));

	// LWIR related
	var scliq = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgSiq"));
	var dxi = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgDxi")); dxi = 23.0; // max. deviation: +/-0.5*scliq*hpix, i.e. +/-28
	var dyi = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgDyi")); dyi = -20.0;

	var npixQCD = (doc.cvsh-2.0*doc.margin)/(1.0*doc.Npix+hpix/dpix-1.0)*hpix/dpix;
	var npixUm = (1.0 * npixQCD) / hpix; // QCD micrometers ; LWIR micrometers are scaled as umLWIR = umQCD/scliq

	var npixLWIR = scliq*npixQCD;

	/// DEMO BEGIN
	// sinx * siny
	for (var i=0;i<doc.NpixLWIR;i++) {
		for (var j=0;j<doc.NpixLWIR;j++) {
			doc.Tlwir[i*doc.NpixLWIR+j] = 293.0 + (343.0-293.0) * Math.sin(1.0*i*Math.PI/(1.0*doc.NpixLWIR-1.0)) * Math.sin(1.0*j*Math.PI/(1.0*doc.NpixLWIR-1.0));
		};
	};

	// linear ramp
	for (var i=0;i<(doc.Npix*doc.Npix);i++) doc.Tqcd[i] = 293.0 + (343.0-293.0) * (1.0*i/(1.0*doc.Npix*doc.Npix-1.0));

	// constant
	for (var i=0;i<(doc.Npix*doc.Npix);i++) doc.DeltaTqcd[i] = 1.4;
	// DEMO END

	var cvsctx = contcontdoc.getElementById("cvs").getContext("2d");

	cvsctx.clearRect(0, 0, doc.cvsh, doc.cvsh);

	var d = doc.imgdat.data;

	// determine LWIR temperature range
	T0 = 1000.0;
	T1 = 0.0;

	for (var i=0;i<(doc.NpixLWIR*doc.NpixLWIR);i++) {
		T = doc.Tlwir[i];
		if (T < T0) T0 = T;
		if (T > T1) T1 = T;
	};

	setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgIsu"), "" + T1.toFixed(1) + "K");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgIsc"), "" + (0.5*(T1+T0)).toFixed(1) + "K");
	setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgIsl"), "" + T0.toFixed(1) + "K");

	// determine ratios ; overlap schema works for any constellation (npixLWIR < npixQCD, npixLWIR = npixQCD, npixLWIR > npixQCD)
	for (var i=0;i<doc.Npix;i++) {
		x0q = (1.0*i + 0.5) * npixUm*dpix - 0.5*npixQCD;
		x1q = x0q + npixQCD;

		for (var j=0;j<doc.NpixLWIR;j++) {
			x0i = (1.0*j + 0.5) * npixLWIR + dxi*npixUm - 0.5*npixLWIR;
			x1i = x0i + npixLWIR;

			doc.Ax[i*doc.NpixLWIR+j] = 0.0;
			if ((x1q > x0i) && (x0q < x1i)) {
				if ((x0q <= x0i) && (x1q >= x1i)) doc.Ax[i*doc.NpixLWIR+j] = npixLWIR/npixQCD; // QCD pixel comprises LWIR pixel
				else if ((x0i <= x0q) && (x1i >= x1q)) doc.Ax[i*doc.NpixLWIR+j] = 1.0; // LWIR pixel comprises QCD pixel
				else if ((x0i <= x0q) && (x1i <= x1q)) doc.Ax[i*doc.NpixLWIR+j] = (x1i-x0q)/(x1q-x0q); // partial overlap 1
				else if ((x0i >= x0q) && (x1i >= x1q)) doc.Ax[i*doc.NpixLWIR+j] = (x1q-x0i)/(x1q-x0q); // partial overlap 2
			};
		};
	};

	for (var i=0;i<doc.Npix;i++) {
		y0q = (1.0*i + 0.5) * npixUm*dpix - 0.5*npixQCD;
		y1q = y0q + npixQCD;

		for (var j=0;j<doc.NpixLWIR;j++) {
			y0i = (1.0*j + 0.5) * npixLWIR + dxi*npixUm - 0.5*npixLWIR;
			y1i = y0i + npixLWIR;

			doc.Ay[i*doc.NpixLWIR+j] = 0.0;
			if ((y1q > y0i) && (y0q < y1i)) {
				if ((y0q <= y0i) && (y1q >= y1i)) doc.Ay[i*doc.NpixLWIR+j] = npixLWIR/npixQCD; // QCD pixel comprises LWIR pixel
				else if ((y0i <= y0q) && (y1i >= y1q)) doc.Ay[i*doc.NpixLWIR+j] = 1.0; // LWIR pixel comprises QCD pixel
				else if ((y0i <= y0q) && (y1i <= y1q)) doc.Ay[i*doc.NpixLWIR+j] = (y1i-y0q)/(y1q-y0q); // partial overlap 1
				else if ((y0i >= y0q) && (y1i >= y1q)) doc.Ay[i*doc.NpixLWIR+j] = (y1q-y0i)/(y1q-y0q); // partial overlap 2
			};
		};
	};

	for (var i=0;i<doc.Npix;i++) {
		for (var j=0;j<doc.Npix;j++) {
			doc.Tqcdlwir[i*doc.Npix+j] = 0.0;

			for (var k=0;k<doc.NpixLWIR;k++) {
				if (doc.Ay[i*doc.NpixLWIR+k] != 0.0) {
					for (var l=0;l<doc.NpixLWIR;l++) {
						doc.Tqcdlwir[i*doc.Npix+j] += doc.Ax[j*doc.NpixLWIR+l] * doc.Ay[i*doc.NpixLWIR+k] * doc.Tlwir[k*doc.NpixLWIR+l];
					};
				};
			};
		};
	};

	// determine ratio range
	pT0 = 1000.0;
	pT1 = 0.0;

	for (var i=0;i<(doc.Npix*doc.Npix);i++) {
		T = doc.Tqcd[i];
		T0 = doc.Tqcdlwir[i];

		if (T0 == 0.0) pT = 1.0;
		else pT = (T-T0)/T0;

		if (pT < pT0) pT0 = pT;
		if (pT > pT1) pT1 = pT;
	};

	if (Math.abs(pT0) > Math.abs(pT1)) {
		pT0 = -Math.abs(pT0);
		pT1 = Math.abs(pT0);
	} else {
		pT0 = -Math.abs(pT1);
		pT1 = Math.abs(pT1);
	};

	if (pT0 < -0.5) {
		pT0 = -0.5;
		pT1 = 0.5;
	};

	if (pT0 == -0.5) {
		setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgQsu"), "\u226550%");
		setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgQsl"), "\u2264-50%");
	} else {
		setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgQsu"), "" + (100.0*pT1).toFixed(1) + "%");
		setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgQsl"), "" + (100.0*pT0).toFixed(1) + "%");
	};

	// set QCD rectangle color
	for (var i=0;i<(doc.Npix*doc.Npix);i++) {
		T = doc.Tqcd[i];
		T0 = doc.Tqcdlwir[i];

		if (T0 == 0.0) pT = 1.0;
		else pT = (T-T0)/T0;

		if (pT < pT0) pT = pT0;
		if (pT > pT1) pT = pT1;

		if (pT0 == pT1) z = 0.5;
		else z = (pT-pT0)/(pT1-pT0);

		if (z < 0.25) {
			r = 0;
			g = Math.round(Math.abs(255.0 * 4.0*z));
			b = 255;
		} else if ((z >= 0.25) && (z < 0.5)) {
			r = 0;
			g = 255;
			b = Math.round(255.0 * 4.0*(0.5-z));
		} else if ((z >= 0.5) && (z < 0.75)) {
			r = Math.round(Math.abs(255.0 * 4.0*(z-0.5)));
			g = 255;
			b = 0;
		} else {
			r = 255;
			g = Math.round(Math.abs(255.0 * 4.0*(1.0-z)));
			b = 0;
		};

		myrect = contcontdoc.getElementById("CusImgPxs" + i);

		s = myrect.getAttribute("style");
		if (!s) s = "";

		ptr = s.search("fill-opacity");
		if (ptr != -1) s = s.substr(ptr);

		s = "fill:rgb(" + r + "," + g + "," + b + ");" + s;

		myrect.setAttribute("style", s);
	};

	// draw LWIR rectangles
	for (var i=0;i<doc.NpixLWIR;i++) {
		y0 = (1.0*i + 0.5) * npixLWIR + dyi*npixUm - 0.5*npixLWIR;
		y0 = Math.floor(y0);

		for (var j=0;j<doc.NpixLWIR;j++) {
			x0 = (1.0*j + 0.5) * npixLWIR + dxi*npixUm - 0.5*npixLWIR;
			x0 = Math.floor(x0);

			ix = i*doc.NpixLWIR+j;

			for (var y=y0;y<=(y0+npixLWIR);y++) {
				if ((y >= 0) && (y < doc.cvsh)) {
					for (var x=x0;x<=(x0+npixLWIR);x++) {
						if ((x >= 0) && (x < doc.cvsh)) {
							ix2 = 4*(y*doc.cvsh+x);

							if (T1 == T0) d[ix2] = 127;
							else d[ix2] = Math.round(255.0 * (doc.Tlwir[ix]-T0)/(T1-T0));
							
							d[ix2+1] = d[ix2];
							d[ix2+2] = d[ix2];
							d[ix2+3] = 255;
						};
					};
				};
			};
		};
	};

	cvsctx.putImageData(doc.imgdat, 0, 0);
};

function initImgPxs() {
	var myg, myrect;

	var x, y;

	var hpix = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQhp"));
	var dpix = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQdp"));

	var npixQCD = Math.floor((doc.cvsh-2.0*doc.margin)/(doc.Npix+hpix/dpix-1.0)*hpix/dpix);
	var npixUm = (1.0 * npixQCD) / hpix;

	myg = contcontdoc.getElementById("CusImgPxs");
	clearElem(myg);

	for (var i=0;i<doc.Npix;i++) {
		y = (-1.0*doc.Npix/2.0 + (1.0*i) + 0.5) * npixUm*dpix - 0.5*npixQCD;
		y = 1.0*Math.round(y) - 0.5;

		for (var j=0;j<doc.Npix;j++) {
			x = (-1.0*doc.Npix/2.0 + (1.0*j) + 0.5) * npixUm*dpix - 0.5*npixQCD;
			x = 1.0*Math.round(x) - 0.5;

			myrect = contcontdoc.createElementNS("http://www.w3.org/2000/svg", "svg:rect");
			myrect.setAttribute("id", "CusImgPxs" + (i*doc.Npix+j));
			myrect.setAttribute("class", "svgbut");
			myrect.setAttribute("x", "" + x);
			myrect.setAttribute("y", "" + y);
			myrect.setAttribute("width", "" + npixQCD);
			myrect.setAttribute("height", "" + npixQCD);
			myrect.setAttribute("onclick", "handleCusImgPxsSet(" + (i*doc.Npix+j) + ")");

			myg.appendChild(myrect);
		};
	};
};

function refreshImgPxs() {
	var myrect, s, ptr;

	var CusImgPxs = parseInt(retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "CusImgPxs"));

	for (var i=0;i<(doc.Npix*doc.Npix);i++) {
		myrect = contcontdoc.getElementById("CusImgPxs" + i);

		if (i == CusImgPxs) myrect.setAttribute("class", "svgbuthlt");
		else myrect.setAttribute("class", "svgbut");

		s = myrect.getAttribute("style");
		if (!s) s = "";

		ptr = s.search("fill-opacity");
		if (ptr != -1) s = s.substr(0, ptr);

		if (doc.ButImgShowOn) s += "fill-opacity:1.0;";
		else s += "fill-opacity:0.0;";

		myrect.setAttribute("style", s);
	};
};

function handleCusImgPxsSet(pixel) {
	setCi(srcdoc, "ContIacIdecIaqQcdsp", "CusImgPxs", "" + pixel);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function refreshImgChart() {
	var lam0lwir = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgIl0"));
	var lam1lwir = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgIl1"));

	var lam0qcd = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQlm"));
	var FWHMqcd = parseFloat(retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "TxtImgQdl"));

	var CusImgPxs = parseInt(retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "CusImgPxs"));

	var dmlwir, dmqcd;
	var dflwir, dfqcd;

	var Tlwir = doc.Tqcdlwir[CusImgPxs];
	var Tqcd = doc.Tqcd[CusImgPxs];
	var DeltaTqcd = doc.DeltaTqcd[CusImgPxs];

	if (Tlwir == 0.0) setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgTlw"), "");
	else setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgTlw"), "=" + Tlwir.toFixed(1) + "K");

	if (Tqcd == 0.0) setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgTqc"), "");
	else setTextContent(contcontdoc, contcontdoc.getElementById("TxtImgTqc"), "=" + Tqcd.toFixed(1) + "\u00b1" + DeltaTqcd.toFixed(1) + "K");

	if (Tlwir == 0.0) {
		dmlwir = "M6 220 L240 220";
		dflwir = "M6 220 L240 220 L6 220";
	
	} else {
		for (var lam=0.5;lam<=20.0;lam+=0.1) {
			// x scaling: 1µm corresponds to 12
			// y scaling: 1kW/(m^2*µm) corresponds to 1800

			if (lam == 0.5) {
				dmlwir = "M";
				dflwir = "M";
			} else {
				dmlwir += " L";
				dflwir += " L";
			};

			dmlwir += (12.0*lam) + " " + (220.0-1.8e-6*Mbbdy(lam, Tlwir));
			dflwir += (12.0*lam) + " " + (220.0-1.8e-6*Fsquare(lam, lam0lwir, lam1lwir)*Mbbdy(lam, Tlwir));
		};

		dflwir += " L6 220";
	};

	contcontdoc.getElementById("CusImgMlwir").setAttribute("d", dmlwir);
	contcontdoc.getElementById("CusImgFlwir").setAttribute("d", dflwir);

	if (Tqcd == 0.0) {
		dmqcd = "M6 220 L240 220";
		dfqcd = "M6 220 L240 220 L6 220";

	} else {
		for (var lam=0.5;lam<=20.0;lam+=0.1) {
			if (lam == 0.5) {
				dmqcd = "M";
				dfqcd = "M";
			} else {
				dmqcd += " L";
				dfqcd += " L";
			};

			dmqcd += (12.0*lam) + " " + (220.0-1.8e-6*Mbbdy(lam, Tqcd));
			dfqcd += (12.0*lam) + " " + (220.0-1.8e-6*Fgauss(lam, lam0qcd, FWHMqcd)*Mbbdy(lam, Tqcd));
		};

		dfqcd += " L6 220";
	};

	contcontdoc.getElementById("CusImgMqcd").setAttribute("d", dmqcd);
	contcontdoc.getElementById("CusImgFqcd").setAttribute("d", dfqcd);
};

function Mbbdy(lam, T) {
	// blackbody spectral function
	var h = 6.626068e-34;
	var c0 = 2.99792458e8;
	var k = 1.3806503e-23;

	var M = 2.0 * Math.PI * h * Math.pow(c0, 2.0) * (1.0/Math.pow(1e-6*lam, 5.0)) * (1.0 / (Math.exp(h*c0/((1e-6*lam)*k*T)) - 1.0));

	return M;
};

function Fgauss(lam, lam0, FWHM) {
	var F = Math.exp(-2.773 * Math.pow(lam-lam0, 2.0) / Math.pow(FWHM, 2.0));

	return F;
};

function Fsquare(lam, lam0, lam1) {
	if ((lam >= lam0) && (lam <= lam1)) return 1.0;
	else return 0.0;
};
// IP cust --- IEND

// --- expand state management
function minimize() {
	// change container heights
	getCrdwnd().changeHeight("Qcdsp", 30);
	doc.getElementById("tdSide").setAttribute("height", "30");
	doc.getElementById("Qcdsp_side").setAttribute("height", "30");
	doc.getElementById("Qcdsp_cont").setAttribute("height", "30");

	// change content
	doc.getElementById("Qcdsp_side").src = "./PnlIdecIaqQcdsp_aside.html";
	doc.getElementById("Qcdsp_cont").src = "./PnlIdecIaqQcdsp_a.html";
};

function regularize() {
	// change content (container heights in refreshBD)
	doc.getElementById("Qcdsp_side").src = "./PnlIdecIaqQcdsp_bside.html";
	doc.getElementById("Qcdsp_cont").src = "./PnlIdecIaqQcdsp_b.html";
};

// --- view initialization and refresh
function initA() {
	if (!doc) return;

	sidedoc = doc.getElementById("Qcdsp_side").contentDocument;
	contdoc = doc.getElementById("Qcdsp_cont").contentDocument;
	hdrdoc = null;
	contcontdoc = null;
	ftrdoc = null;

	initCpt(contdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqQcdsp", "Cpt"));

	refreshA();
};

function initBD(bNotD) {
	if (!doc) return;

	sidedoc = doc.getElementById("Qcdsp_side").contentDocument;
	contdoc = doc.getElementById("Qcdsp_cont").contentDocument;
	hdrdoc = contdoc.getElementById("Qcdsp_hdr").contentDocument;
	contcontdoc = contdoc.getElementById("Qcdsp_cont").contentDocument;

	// IP initBD --- BEGIN
	initCpt(hdrdoc, "Cpt", retrieveTi(srcdoc, "TagIdecIaqQcdsp", "Cpt"));
	initCpt(contcontdoc, "CptMod", retrieveTi(srcdoc, "TagIdecIaqQcdsp", "CptMod"));
	refreshPup(contcontdoc, srcdoc, "PupMod", "", "FeedFPupMod", retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "numFPupMod"), retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "PupModActive"), false);
	initCpt(contcontdoc, "CptTin", retrieveTi(srcdoc, "TagIdecIaqQcdsp", "CptTin"));
	// IP initBD --- END

	refreshBD(bNotD);
};

function init() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

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
	var height = 300; // full cont height

	// IP refreshBD.vars --- BEGIN
	var PupModActive = (retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "PupModActive") == "true");

	// IP refreshBD.vars --- END

	// IP refreshBD --- BEGIN
	refreshButicon(hdrdoc, "ButMaster", "icon/master", true, retrieveCi(srcdoc, "ContInfIdecIaqQcdsp", "ButMasterOn") == "true");
	contcontdoc.getElementById("PupMod").value = retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "numFPupMod");

	refreshSld(contcontdoc, "SldTin", true, true, parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "SldTinMin")), parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "SldTinMax")), parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", "SldTin")), true, false);

	// IP refreshBD --- END

	getCrdwnd().changeHeight("Qcdsp", height+31);
	doc.getElementById("tdSide").setAttribute("height", "" + (height+31));
	doc.getElementById("Qcdsp_side").setAttribute("height", "" + (height+31));
	doc.getElementById("Qcdsp_cont").setAttribute("height", "" + (height+31));
	sidedoc.getElementById("tdFlex").setAttribute("height", "" + (height+31-30));
	contdoc.getElementById("tdCont").setAttribute("height", "" + height);
	contdoc.getElementById("Qcdsp_cont").setAttribute("height", "" + height);
};

function refresh() {
	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

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
	srcdoc = doc.getElementById("Qcdsp_src").contentDocument;

	var str = serializeDpchApp("DpchAppIdecInit", scrJref);
	sendReq(str, doc, handleDpchAppInitReply, true);
};

// --- specific event handlers for app controls

function handleButImgShowClick() {
// IP handleButImgShowClick --- IBEGIN
	doc.ButImgShowOn = !doc.ButImgShowOn;

	if (doc.ButImgShowOn) contcontdoc.getElementById("ButImgShow").setAttribute("class", "svgtxtbuthlt");
	else contcontdoc.getElementById("ButImgShow").setAttribute("class", "svgtxtbut");

	refreshB();
// IP handleButImgShowClick --- IEND
};

// --- generalized event handlers for app controls

// --- generalized event handlers for shared controls

function handleButClick(ctlsref) {
	var str = serializeDpchAppDo(srcdoc, "DpchAppIdecIaqQcdspDo", scrJref, ctlsref + "Click");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handlePupChange(_doc, ctlsref, size) {
	var elem = _doc.getElementById(ctlsref);

	elem.setAttribute("class", "pup" + size + "mod");
	setCi(srcdoc, "ContIacIdecIaqQcdsp", "numF" + ctlsref, elem.value);

	var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
	sendReq(str, doc, handleDpchAppDataDoReply);
};

function handleSldJpleftMov(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Jpleftl").setAttribute("class", "sldlhlt");
	};
};

function handleSldJpleftMou(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Jpleftl").setAttribute("class", "sldl");
};

function handleSldJpleftClick(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, oldVal, val;

	var min, max, rast;

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Rast"));

	if (_rast) {
		if (log) val = oldVal / rast;
		else val = oldVal - rast;

		if (val < min) val = min;
		if (val > max) val = max;

	} else {
		pos = getSldPosFromEvtx(true, evt.clientX);
		val = getSldValFromPos(min, max, rast, pos);
	};

	pos = getSldPosFromVal(min, max, val);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleSldJprightMov(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Jprightl").setAttribute("class", "sldlhlt");
	};
};

function handleSldJprightMou(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Jprightl").setAttribute("class", "sldl");
};

function handleSldJprightClick(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, oldVal, val;

	var min, max, rast;

	if (shr) oldVal = parseFloat(retrieveCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref));
	else oldVal = parseFloat(_doc.getElementById(ctlsref + "Val").value);
	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Rast"));

	if (_rast) {
		if (log) val = oldVal * rast;
		else val = oldVal + rast;

		if (val < min) val = min;
		if (val > max) val = max;

	} else {
		pos = getSldPosFromEvtx(true, evt.clientX);
		val = getSldValFromPos(min, max, rast, pos);
	};

	pos = getSldPosFromVal(min, max, val);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
		window["handle" + ctlsref + "Change"](val);
	};
};

function handleSldMov(_doc, ctlsref) {
	_doc.getElementById(ctlsref + "Bar").setAttribute("class", "sldlhlt");
};

function handleSldMou(_doc, ctlsref) {
	if (_doc.getElementById("td" + ctlsref).onmousemove == null) {
		_doc.getElementById(ctlsref + "Bar").setAttribute("class", "sldl");
	};
};

function handleSldMdn(_doc, ctlsref) {
	_doc.getElementById("td" + ctlsref).setAttribute("onmousemove", "handle" + ctlsref + "Move(event)");
	_doc.getElementById("td" + ctlsref).setAttribute("onmouseup", "handle" + ctlsref + "Mup(event)");
};

function handleSldMove(_doc, ctlsref, shr, log, _rast, evt) {
	var pos, val;

	var min, max, rast;

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Rast"));
	else rast = 0.0;

	pos = getSldPosFromEvtx(true, evt.clientX);

	if (log) val = getSldLogvalFromPos(min, max, rast, pos);
	else val = getSldValFromPos(min, max, rast, pos);

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) setCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref, "" + val);
	else window["handle" + ctlsref + "Change"](val);
};

function handleSldMup(_doc, ctlsref, shr) {
	_doc.getElementById("td" + ctlsref).onmousemove = null;
	_doc.getElementById("td" + ctlsref).onmouseup = null;

	if (shr) {
		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
		sendReq(str, doc, handleDpchAppDataDoReply);
	};
};

function handleSldValKey(_doc, ctlsref, shr, log, _rast, evt) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	if (evt.keyCode == 13) {
		min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Min"));
		max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Max"));

		if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Rast"));
		else rast = 0.0;

		val = parseFloat(elem.value);
		if (isNaN(val)) val = 0.0;

		if (log) {
			val = alignSldLogval(min, max, rast, val);
			pos = getSldPosFromLogval(min, max, val);
		} else {
			val = alignSldVal(min, max, rast, val);
			pos = getSldPosFromVal(min, max, val);
		};

		setSldPos(_doc, ctlsref, true, pos);
		setSldVal(_doc, ctlsref, val, true, true);

		if (shr) {
			setCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref, "" + val);

			var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
			sendReq(str, doc, handleDpchAppDataDoReply);

		} else {
			window["handle" + ctlsref + "Change"](val);
		};

		return false;
	};

	return true;
};

function handleSldValChange(_doc, ctlsref, shr, log, _rast) {
	var elem = _doc.getElementById(ctlsref + "Val");

	var pos, val;

	var min, max, rast;

	elem.setAttribute("class", "txfxsmod");

	min = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Min"));
	max = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Max"));

	if (_rast) rast = parseFloat(retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", ctlsref + "Rast"));
	else rast = 0.0;

	val = parseFloat(elem.value);
	if (isNaN(val)) val = 0.0;

	if (log) {
		val = alignSldLogval(min, max, rast, val);
		pos = getSldPosFromLogval(min, max, val);
	} else {
		val = alignSldVal(min, max, rast, val);
		pos = getSldPosFromVal(min, max, val);
	};

	setSldPos(_doc, ctlsref, true, pos);
	setSldVal(_doc, ctlsref, val, true, true);

	if (shr) {
		setCi(srcdoc, "ContIacIdecIaqQcdsp", ctlsref, "" + val);

		var str = serializeDpchAppData(srcdoc, "DpchAppIdecIaqQcdspData", scrJref, "ContIacIdecIaqQcdsp");
		sendReq(str, doc, handleDpchAppDataDoReply);

	} else {
	window["handle" + ctlsref + "Change"](val);
	};
};

// --- server interaction
function mergeDpchEngData(dom) {
	var mask = [];

	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "ContIacIdecIaqQcdsp", srcdoc)) mask.push("contiac");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "ContInfIdecIaqQcdsp", srcdoc)) mask.push("continf");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "FeedFCsiImgSte", srcdoc)) mask.push("feedFCsiImgSte");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "FeedFPupMod", srcdoc)) mask.push("feedFPupMod");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "StatShrIdecIaqQcdsp", srcdoc)) mask.push("statshr");
	if (updateSrcblock(dom, "DpchEngIdecIaqQcdspData", "TagIdecIaqQcdsp", srcdoc)) mask.push("tag");

	return mask;
};

function handleDpchEng(dom, dpch) {
	if (dpch == "DpchEngIdecIaqQcdspData") {
		var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

		var mask = mergeDpchEngData(dom);

		if (mask.indexOf("statshr") != -1) {
			var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

			if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
				if (srefIxIdecVExpstate == "mind") minimize();
				else if (srefIxIdecVExpstate == "regd") regularize();
			} else {
				refresh();
			};

		} else {
			refresh();
		};
	} else if (dpch == "DpchEngIdecIaqQcdspLive") {
		handleDpchEngIdecIaqQcdspLive(dom);
	};
};

function handleDpchEngIdecIaqQcdspLive(dom) {
// IP handleDpchEngIdecIaqQcdspLive --- IBEGIN
	var mask = [];

	var resnode;

	updateSrcblock(dom, "DpchEngIdecIaqQcdspLive", "ContInfIdecIaqQcdsp", srcdoc);

	resnode = getNode(dom, "//idec:DpchEngIdecIaqQcdspLive/idec:Tlwir");
	if (resnode) {
		doc.Tlwir = parseDoublevec(resnode.textContent);
		mask.push("Tlwir");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqQcdspLive/idec:Tqcd");
	if (resnode) {
		doc.Tqcd = parseDoublevec(resnode.textContent);
		mask.push("Tqcd");
	};

	resnode = getNode(dom, "//idec:DpchEngIdecIaqQcdspLive/idec:DeltaTqcd");
	if (resnode) {
		doc.DeltaTqcd = parseDoublevec(resnode.textContent);
		mask.push("DeltaTqcd");
	};

	var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");
	if (srefIxIdecVExpstate == "regd") refreshLive(mask);
// IP handleDpchEngIdecIaqQcdspLive --- IEND
};

function handleDpchAppInitReply() {
	var dom, blk;

	if (doc.req.readyState == 4) {
		dom = doc.req.responseXML;

		blk = retrieveBlock(dom, "//idec:*");
		if (blk) {
			if (blk.nodeName == "DpchEngIdecIaqQcdspData") {
				mergeDpchEngData(dom);
				init();

				getCrdwnd().setInitdone("Qcdsp");
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

			} else if (blk.nodeName == "DpchEngIdecIaqQcdspData") {
				var oldSrefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

				var mask = mergeDpchEngData(dom);

				if (mask.indexOf("statshr") != -1) {
					var srefIxIdecVExpstate = retrieveSi(srcdoc, "StatShrIdecIaqQcdsp", "srefIxIdecVExpstate");

					if (srefIxIdecVExpstate != oldSrefIxIdecVExpstate) {
						if (srefIxIdecVExpstate == "mind") minimize();
						else if (srefIxIdecVExpstate == "regd") regularize();
					} else {
						refresh();
					};

				} else {
					refresh();
				};
			};
		};
	};
};


