/**
  * \file IexIdecIni.h
  * import/export handler for database DbsIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IEXIDECINI_H
#define IEXIDECINI_H

#define VecVIexIdecIniIme IexIdecIni::VecVIme

#define ImeitemIIdecIniAVControlPar IexIdecIni::ImeitemIAVControlPar
#define ImeIIdecIniAVControlPar IexIdecIni::ImeIAVControlPar
#define VecWImeIIdecIniAVControlParIel IexIdecIni::ImeIAVControlPar::VecWIel

#define ImeitemIIdecIniJAVKeylistKey IexIdecIni::ImeitemIJAVKeylistKey
#define ImeIIdecIniJAVKeylistKey IexIdecIni::ImeIJAVKeylistKey
#define VecWImeIIdecIniJAVKeylistKeyIel IexIdecIni::ImeIJAVKeylistKey::VecWIel

#define ImeitemIIdecIniAVKeylistKey IexIdecIni::ImeitemIAVKeylistKey
#define ImeIIdecIniAVKeylistKey IexIdecIni::ImeIAVKeylistKey
#define VecWImeIIdecIniAVKeylistKeyIel IexIdecIni::ImeIAVKeylistKey::VecWIel

#define ImeitemIIdecIniAVValuelistVal IexIdecIni::ImeitemIAVValuelistVal
#define ImeIIdecIniAVValuelistVal IexIdecIni::ImeIAVValuelistVal
#define VecWImeIIdecIniAVValuelistValIel IexIdecIni::ImeIAVValuelistVal::VecWIel

#define ImeitemIIdecIniMFile IexIdecIni::ImeitemIMFile
#define ImeIIdecIniMFile IexIdecIni::ImeIMFile
#define VecWImeIIdecIniMFileIel IexIdecIni::ImeIMFile::VecWIel

#define ImeitemIIdecIniAMUsergroupAccess IexIdecIni::ImeitemIAMUsergroupAccess
#define ImeIIdecIniAMUsergroupAccess IexIdecIni::ImeIAMUsergroupAccess
#define VecWImeIIdecIniAMUsergroupAccessIel IexIdecIni::ImeIAMUsergroupAccess::VecWIel

#define ImeitemIIdecIniJMUserState IexIdecIni::ImeitemIJMUserState
#define ImeIIdecIniJMUserState IexIdecIni::ImeIJMUserState
#define VecWImeIIdecIniJMUserStateIel IexIdecIni::ImeIJMUserState::VecWIel

#define ImeitemIIdecIniJMPersonLastname IexIdecIni::ImeitemIJMPersonLastname
#define ImeIIdecIniJMPersonLastname IexIdecIni::ImeIJMPersonLastname
#define VecWImeIIdecIniJMPersonLastnameIel IexIdecIni::ImeIJMPersonLastname::VecWIel

#define ImeitemIIdecIniMPerson IexIdecIni::ImeitemIMPerson
#define ImeIIdecIniMPerson IexIdecIni::ImeIMPerson
#define VecWImeIIdecIniMPersonIel IexIdecIni::ImeIMPerson::VecWIel

#define ImeitemIIdecIniMUser IexIdecIni::ImeitemIMUser
#define ImeIIdecIniMUser IexIdecIni::ImeIMUser
#define VecWImeIIdecIniMUserIel IexIdecIni::ImeIMUser::VecWIel

#define ImeitemIIdecIniMUsergroup IexIdecIni::ImeitemIMUsergroup
#define ImeIIdecIniMUsergroup IexIdecIni::ImeIMUsergroup
#define VecWImeIIdecIniMUsergroupIel IexIdecIni::ImeIMUsergroup::VecWIel

/**
	* IexIdecIni
	*/
class IexIdecIni : public JobIdec {

public:
	/**
		* VecVIme (full: VecVIexIdecIniIme)
		*/
	class VecVIme {

	public:
		static const uint IMEIAVCONTROLPAR = 1;
		static const uint IMEIAVKEYLISTKEY = 2;
		static const uint IMEIAVVALUELISTVAL = 3;
		static const uint IMEIMFILE = 4;
		static const uint IMEIMUSERGROUP = 5;
		static const uint IMEIAMUSERGROUPACCESS = 6;
		static const uint IMEIJAVKEYLISTKEY = 7;
		static const uint IMEIMUSER = 8;
		static const uint IMEIJMUSERSTATE = 9;
		static const uint IMEIMPERSON = 10;
		static const uint IMEIJMPERSONLASTNAME = 11;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

public:
	/**
		* ImeitemIAVControlPar (full: ImeitemIIdecIniAVControlPar)
		*/
	class ImeitemIAVControlPar : public IdecAVControlPar {

	public:
		ImeitemIAVControlPar(const uint ixIdecVControl = 0, const string& Par = "", const string& Val = "");
		ImeitemIAVControlPar(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIAVControlPar (full: ImeIIdecIniAVControlPar)
		*/
	class ImeIAVControlPar {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniAVControlParIel)
			*/
		class VecWIel {

		public:
			static const uint SREFIXIDECVCONTROL = 1;
			static const uint PAR = 2;
			static const uint VAL = 4;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIAVControlPar();
		~ImeIAVControlPar();

	public:
		vector<ImeitemIAVControlPar*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIJAVKeylistKey (full: ImeitemIIdecIniJAVKeylistKey)
		*/
	class ImeitemIJAVKeylistKey : public IdecJAVKeylistKey {

	public:
		ImeitemIJAVKeylistKey(const uint x1IxIdecVLocale = 0, const string& Title = "", const string& Comment = "");
		ImeitemIJAVKeylistKey(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIJAVKeylistKey (full: ImeIIdecIniJAVKeylistKey)
		*/
	class ImeIJAVKeylistKey {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniJAVKeylistKeyIel)
			*/
		class VecWIel {

		public:
			static const uint SREFX1IXIDECVLOCALE = 1;
			static const uint TITLE = 2;
			static const uint COMMENT = 4;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIJAVKeylistKey();
		~ImeIJAVKeylistKey();

	public:
		vector<ImeitemIJAVKeylistKey*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIAVKeylistKey (full: ImeitemIIdecIniAVKeylistKey)
		*/
	class ImeitemIAVKeylistKey : public IdecAVKeylistKey {

	public:
		ImeitemIAVKeylistKey(const uint klsIxIdecVKeylist = 0, const string& sref = "", const string& Avail = "", const string& Implied = "");
		ImeitemIAVKeylistKey(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

		ImeIJAVKeylistKey imeijavkeylistkey;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIAVKeylistKey (full: ImeIIdecIniAVKeylistKey)
		*/
	class ImeIAVKeylistKey {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniAVKeylistKeyIel)
			*/
		class VecWIel {

		public:
			static const uint SREFKLSIXIDECVKEYLIST = 1;
			static const uint SREF = 2;
			static const uint AVAIL = 4;
			static const uint IMPLIED = 8;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIAVKeylistKey();
		~ImeIAVKeylistKey();

	public:
		vector<ImeitemIAVKeylistKey*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIAVValuelistVal (full: ImeitemIIdecIniAVValuelistVal)
		*/
	class ImeitemIAVValuelistVal : public IdecAVValuelistVal {

	public:
		ImeitemIAVValuelistVal(const uint vlsIxIdecVValuelist = 0, const uint x1IxIdecVLocale = 0, const string& Val = "");
		ImeitemIAVValuelistVal(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIAVValuelistVal (full: ImeIIdecIniAVValuelistVal)
		*/
	class ImeIAVValuelistVal {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniAVValuelistValIel)
			*/
		class VecWIel {

		public:
			static const uint SREFVLSIXIDECVVALUELIST = 1;
			static const uint SREFX1IXIDECVLOCALE = 2;
			static const uint VAL = 4;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIAVValuelistVal();
		~ImeIAVValuelistVal();

	public:
		vector<ImeitemIAVValuelistVal*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIMFile (full: ImeitemIIdecIniMFile)
		*/
	class ImeitemIMFile : public IdecMFile {

	public:
		ImeitemIMFile(const string& osrefKContent = "", const string& Filename = "", const string& srefKMimetype = "", const string& Comment = "");
		ImeitemIMFile(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIMFile (full: ImeIIdecIniMFile)
		*/
	class ImeIMFile {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniMFileIel)
			*/
		class VecWIel {

		public:
			static const uint OSREFKCONTENT = 1;
			static const uint FILENAME = 2;
			static const uint SREFKMIMETYPE = 4;
			static const uint COMMENT = 8;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIMFile();
		~ImeIMFile();

	public:
		vector<ImeitemIMFile*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIAMUsergroupAccess (full: ImeitemIIdecIniAMUsergroupAccess)
		*/
	class ImeitemIAMUsergroupAccess : public IdecAMUsergroupAccess {

	public:
		ImeitemIAMUsergroupAccess(const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);
		ImeitemIAMUsergroupAccess(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIAMUsergroupAccess (full: ImeIIdecIniAMUsergroupAccess)
		*/
	class ImeIAMUsergroupAccess {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniAMUsergroupAccessIel)
			*/
		class VecWIel {

		public:
			static const uint SREFX1IXIDECVCARD = 1;
			static const uint SREFSIXIDECWUIACCESS = 2;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIAMUsergroupAccess();
		~ImeIAMUsergroupAccess();

	public:
		vector<ImeitemIAMUsergroupAccess*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIJMUserState (full: ImeitemIIdecIniJMUserState)
		*/
	class ImeitemIJMUserState : public IdecJMUserState {

	public:
		ImeitemIJMUserState(const uint ixVState = 0);
		ImeitemIJMUserState(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIJMUserState (full: ImeIIdecIniJMUserState)
		*/
	class ImeIJMUserState {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniJMUserStateIel)
			*/
		class VecWIel {

		public:
			static const uint SREFIXVSTATE = 1;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIJMUserState();
		~ImeIJMUserState();

	public:
		vector<ImeitemIJMUserState*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIJMPersonLastname (full: ImeitemIIdecIniJMPersonLastname)
		*/
	class ImeitemIJMPersonLastname : public IdecJMPersonLastname {

	public:
		ImeitemIJMPersonLastname(const string& Lastname = "");
		ImeitemIJMPersonLastname(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIJMPersonLastname (full: ImeIIdecIniJMPersonLastname)
		*/
	class ImeIJMPersonLastname {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniJMPersonLastnameIel)
			*/
		class VecWIel {

		public:
			static const uint LASTNAME = 1;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIJMPersonLastname();
		~ImeIJMPersonLastname();

	public:
		vector<ImeitemIJMPersonLastname*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIMPerson (full: ImeitemIIdecIniMPerson)
		*/
	class ImeitemIMPerson : public IdecMPerson {

	public:
		ImeitemIMPerson(const uint ixVSex = 0, const string& Title = "", const string& Firstname = "");
		ImeitemIMPerson(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

		ImeIJMPersonLastname imeijmpersonlastname;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIMPerson (full: ImeIIdecIniMPerson)
		*/
	class ImeIMPerson {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniMPersonIel)
			*/
		class VecWIel {

		public:
			static const uint SREFIXVSEX = 1;
			static const uint TITLE = 2;
			static const uint FIRSTNAME = 4;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIMPerson();
		~ImeIMPerson();

	public:
		vector<ImeitemIMPerson*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIMUser (full: ImeitemIIdecIniMUser)
		*/
	class ImeitemIMUser : public IdecMUser {

	public:
		ImeitemIMUser(const string& sref = "", const uint ixIdecVLocale = 0, const uint ixIdecVUserlevel = 0, const string& Password = "");
		ImeitemIMUser(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

		ImeIJMUserState imeijmuserstate;
		ImeIMPerson imeimperson;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIMUser (full: ImeIIdecIniMUser)
		*/
	class ImeIMUser {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniMUserIel)
			*/
		class VecWIel {

		public:
			static const uint SREF = 1;
			static const uint SREFIXIDECVLOCALE = 2;
			static const uint SREFIXIDECVUSERLEVEL = 4;
			static const uint PASSWORD = 8;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIMUser();
		~ImeIMUser();

	public:
		vector<ImeitemIMUser*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

	/**
		* ImeitemIMUsergroup (full: ImeitemIIdecIniMUsergroup)
		*/
	class ImeitemIMUsergroup : public IdecMUsergroup {

	public:
		ImeitemIMUsergroup(const string& sref = "", const string& Comment = "");
		ImeitemIMUsergroup(DbsIdec* dbsidec, const ubigint ref);

	public:
		uint lineno;
		uint ixWIelValid;

		ImeIAMUsergroupAccess imeiamusergroupaccess;
		ImeIMUser imeimuser;

	public:
		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, const string& basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const uint num, const bool shorttags = true);
	};

	/**
		* ImeIMUsergroup (full: ImeIIdecIniMUsergroup)
		*/
	class ImeIMUsergroup {

	public:
		/**
			* VecWIel (full: VecWImeIIdecIniMUsergroupIel)
			*/
		class VecWIel {

		public:
			static const uint SREF = 1;
			static const uint COMMENT = 2;

			static uint getIx(const string& srefs);
			static void getIcs(const uint ix, set<uint>& ics);
			static string getSrefs(const uint ix);
		};

	public:
		ImeIMUsergroup();
		~ImeIMUsergroup();

	public:
		vector<ImeitemIMUsergroup*> nodes;

	public:
		void clear();

		bool readTxt(Txtrd& txtrd);
		void readXML(xmlXPathContext* docctx, string basexpath);

		void writeTxt(fstream& outfile);
		void writeXML(xmlTextWriter* wr, const bool shorttags = true);
	};

public:
	IexIdecIni(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~IexIdecIni();

public:
	uint lineno;
	uint impcnt;

	ImeIAVControlPar imeiavcontrolpar;
	ImeIAVKeylistKey imeiavkeylistkey;
	ImeIAVValuelistVal imeiavvaluelistval;
	ImeIMFile imeimfile;
	ImeIMUsergroup imeimusergroup;

public:
	// IP cust --- INSERT

public:
	void reset();

	void import(DbsIdec* dbsidec);

	void collect(DbsIdec* dbsidec, const map<uint,uint>& icsIdecVIop = icsIdecVIopInsAll());

public:
	bool readTxt(Txtrd& txtrd);
	void readXML(xmlXPathContext* docctx, string basexpath);

	bool readTxtFile(const string& fullpath);
	bool readXMLFile(const string& fullpath);

	void writeTxt(fstream& outfile);
	void writeXML(xmlTextWriter* wr, const bool shorttags);

	void writeTxtFile(const string& fullpath);
	void writeXMLFile(const string& fullpath, const bool shorttags);

	static map<uint,uint> icsIdecVIopInsAll();
	uint getIxIdecVIop(const map<uint,uint>& icsIdecVIop, const uint ixVIme, uint& ixIdecVIop);

public:
	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleCall(DbsIdec* dbsidec, Call* call);
};

#endif

