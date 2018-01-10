/**
  * \file VecIdecVMimetype.cpp
  * vector VecIdecVMimetype (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVMimetype.h"

/******************************************************************************
 namespace VecIdecVMimetype
 ******************************************************************************/

uint VecIdecVMimetype::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "bmp") return BMP;
	else if (s == "cpp") return CPP;
	else if (s == "css") return CSS;
	else if (s == "csv") return CSV;
	else if (s == "doc") return DOC;
	else if (s == "docx") return DOCX;
	else if (s == "eps") return EPS;
	else if (s == "gif") return GIF;
	else if (s == "h") return H;
	else if (s == "hdf") return HDF;
	else if (s == "html") return HTML;
	else if (s == "jpg") return JPG;
	else if (s == "js") return JS;
	else if (s == "make") return MAKE;
	else if (s == "nc") return NC;
	else if (s == "pdf") return PDF;
	else if (s == "png") return PNG;
	else if (s == "ppt") return PPT;
	else if (s == "pptx") return PPTX;
	else if (s == "sh") return SH;
	else if (s == "sql") return SQL;
	else if (s == "svg") return SVG;
	else if (s == "tex") return TEX;
	else if (s == "tgz") return TGZ;
	else if (s == "tif") return TIF;
	else if (s == "txt") return TXT;
	else if (s == "xls") return XLS;
	else if (s == "xlsx") return XLSX;
	else if (s == "xml") return XML;
	else if (s == "zip") return ZIP;

	return(0);
};

string VecIdecVMimetype::getSref(
			const uint ix
		) {
	if (ix == BMP) return("bmp");
	else if (ix == CPP) return("cpp");
	else if (ix == CSS) return("css");
	else if (ix == CSV) return("csv");
	else if (ix == DOC) return("doc");
	else if (ix == DOCX) return("docx");
	else if (ix == EPS) return("eps");
	else if (ix == GIF) return("gif");
	else if (ix == H) return("h");
	else if (ix == HDF) return("hdf");
	else if (ix == HTML) return("html");
	else if (ix == JPG) return("jpg");
	else if (ix == JS) return("js");
	else if (ix == MAKE) return("make");
	else if (ix == NC) return("nc");
	else if (ix == PDF) return("pdf");
	else if (ix == PNG) return("png");
	else if (ix == PPT) return("ppt");
	else if (ix == PPTX) return("pptx");
	else if (ix == SH) return("sh");
	else if (ix == SQL) return("sql");
	else if (ix == SVG) return("svg");
	else if (ix == TEX) return("tex");
	else if (ix == TGZ) return("tgz");
	else if (ix == TIF) return("tif");
	else if (ix == TXT) return("txt");
	else if (ix == XLS) return("xls");
	else if (ix == XLSX) return("xlsx");
	else if (ix == XML) return("xml");
	else if (ix == ZIP) return("zip");

	return("");
};

string VecIdecVMimetype::getTitle(
			const uint ix
		) {
	if (ix == BMP) return("image/bmp");
	else if (ix == CPP) return("text/x-c");
	else if (ix == CSS) return("text/css");
	else if (ix == CSV) return("text/comma-separated-values");
	else if (ix == DOC) return("application/msword");
	else if (ix == DOCX) return("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
	else if (ix == EPS) return("application/postscript");
	else if (ix == GIF) return("image/gif");
	else if (ix == H) return("text/x-h");
	else if (ix == HDF) return("application/x-hdf");
	else if (ix == HTML) return("text/html");
	else if (ix == JPG) return("image/jpeg");
	else if (ix == JS) return("text/javascript");
	else if (ix == MAKE) return("text/x-makefile");
	else if (ix == NC) return("application/x-netcdf");
	else if (ix == PDF) return("application/pdf");
	else if (ix == PNG) return("image/png");
	else if (ix == PPT) return("application/mspowerpoint");
	else if (ix == PPTX) return("application/vnd.openxmlformats-officedocument.presentationml.presentation");
	else if (ix == SH) return("application/x-sh");
	else if (ix == SQL) return("text/x-sql");
	else if (ix == SVG) return("image/svg+xml");
	else if (ix == TEX) return("application/x-tex");
	else if (ix == TGZ) return("application/x-gzip");
	else if (ix == TIF) return("image/tiff");
	else if (ix == TXT) return("text/plain");
	else if (ix == XLS) return("application/msexcel");
	else if (ix == XLSX) return("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	else if (ix == XML) return("text/xml");
	else if (ix == ZIP) return("application/zip");

	return("");
};

