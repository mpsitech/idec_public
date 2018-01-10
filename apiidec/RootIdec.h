/**
  * \file RootIdec.h
  * API code for job RootIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef ROOTIDEC_H
#define ROOTIDEC_H

#include "ApiIdec_blks.h"

#define DpchAppRootIdecLogin RootIdec::DpchAppLogin

/**
  * RootIdec
  */
namespace RootIdec {
	/**
		* DpchAppLogin (full: DpchAppRootIdecLogin)
		*/
	class DpchAppLogin : public DpchAppIdec {

	public:
		static const uint SCRJREF = 1;
		static const uint PASSWORD = 2;
		static const uint USERNAME = 3;
		static const uint ALL = 4;

	public:
		DpchAppLogin(const string& scrJref = "", const string& password = "", const string& username = "", const set<uint>& mask = {NONE});

	public:
		string password;
		string username;

	public:
		string getSrefsMask();

		void writeXML(xmlTextWriter* wr);
	};

};

#endif

