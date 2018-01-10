/**
  * \file Idec.cpp
  * Idec global functionality (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Idec.h"

/******************************************************************************
 namespace Acv
 ******************************************************************************/

ubigint Acv::addfile(
			DbsIdec* dbsidec
			, const string& acvpath
			, const string& path
			, const uint refIxVTbl
			, const ubigint refUref
			, const string& osrefKContent
			, const string& Filename
			, const string& srefKMimetype
			, const string& Comment
		) {
	ubigint retval = 0;

	IdecMFile* fil = NULL;

	uint Archived;
	uint Size;

	ostringstream str;
	string s;

	int res;

	// set archived time to current time
	Archived = time(NULL);

	// determine file size in kB
	struct stat st;
	stat(path.c_str(), &st);
	Size = st.st_size / 1024;

	fil = new IdecMFile(0, 0, 0, 0, refIxVTbl, refUref, osrefKContent, Archived, Filename, "", srefKMimetype, Size, Comment);
	dbsidec->tblidecmfile->insertRec(fil);
	
	// adjust archive name in record
	str.str(""); str.fill('0'); str.width(8); str << right << fil->ref; str.width(0);
	if (Filename.rfind('.') != string::npos) str << Filename.substr(Filename.rfind('.'));

	fil->Archivename = str.str();
	dbsidec->tblidecmfile->updateRec(fil);

	// create folder if required
	str.str(""); str << acvpath << "/";
	str.fill('0'); str.width(5); str << right << ((fil->ref-(fil->ref%1000)) / 1000); str.width(0);

#ifdef _WIN32
	if (access(str.str().c_str(), R_OK | W_OK) == -1) mkdir(str.str().c_str());
#else
	if (access(str.str().c_str(), R_OK | W_OK) == -1) mkdir(str.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

	// copy file
	s = "cp -p " + path + " " + str.str() + "/" + fil->Archivename;

	res = system(s.c_str());
	if (res != 0) cout << "Acv::addfile() error copying file (" << res << ")" << endl;

	retval = fil->ref;
	delete fil;

	return retval;
};

void Acv::alterfile(
			DbsIdec* dbsidec
			, const string& acvpath
			, const string& path
			, const ubigint ref
		) {
	IdecMFile* fil = NULL;

	uint Archived;
	uint Size;

	ostringstream str;
	string s;

	int res;

	// set archived time to current time
	Archived = time(NULL);

	// determine file size in kB
	struct stat st;
	stat(path.c_str(), &st);
	Size = st.st_size / 1024;

	// load record
	dbsidec->tblidecmfile->loadRecByRef(ref, &fil);

	if (fil) {
		// update record
		fil->Archived = Archived;

		str.str(""); str.fill('0'); str.width(8); str << right << fil->ref; str.width(0);
		if (fil->Filename.rfind('.') != string::npos) str << fil->Filename.substr(fil->Filename.rfind('.'));
		fil->Archivename = str.str();

		fil->Size = Size;

		dbsidec->tblidecmfile->updateRec(fil);

		// create folder if required
		str.str(""); str << acvpath << "/";
		str.fill('0'); str.width(5); str << right << ((fil->ref-(fil->ref%1000)) / 1000); str.width(0);

#ifdef _WIN32
		if (access(str.str().c_str(), R_OK | W_OK) == -1) mkdir(str.str().c_str());
#else
		if (access(str.str().c_str(), R_OK | W_OK) == -1) mkdir(str.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

		// copy file
		s = "cp -p " + path + " " + str.str() + "/" + fil->Archivename;

		res = system(s.c_str());
		if (res != 0) cout << "Acv::alterfile() error copying file (" << res << ")" << endl;

		delete fil;
	};
};

string Acv::getfile(
			DbsIdec* dbsidec
			, const ubigint refIdecMFile
		) {
	IdecMFile* fil = NULL;

	ostringstream str;

	dbsidec->tblidecmfile->loadRecByRef(refIdecMFile, &fil);

	if (fil) {
		str.fill('0');
		str.width(5);
		str << right << ((fil->ref-(fil->ref%1000)) / 1000);
		
		str.width(0);
		str << "/" << fil->Archivename;

		delete fil;
	};

	return(str.str());
};

/******************************************************************************
 namespace Lop
 ******************************************************************************/

void Lop::apply(
			const uint ixIdecVLop
			, vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref
		) {
	if (ixIdecVLop == VecIdecVLop::INS) insert(refsList, refsPool, ref);
	else if (ixIdecVLop == VecIdecVLop::RMV) remove(refsList, refsPool, ref);
};

void Lop::insert(
			vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref
		) {
	for (unsigned int i=0;i<refsPool.size();i++) {
		if (refsPool[i] == ref) {
			refsList[i] = ref;
			refsPool[i] = 0;
			break;
		};
	};
};

void Lop::remove(
			vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref
		) {
	for (unsigned int i=0;i<refsList.size();i++) {
		if (refsList[i] == ref) {
			refsPool[i] = ref;
			refsList[i] = 0;
			break;
		};
	};
};

/******************************************************************************
 namespace Oolop
 ******************************************************************************/

void Oolop::apply(
			const uint ixIdecVOolop
			, vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref1
			, const ubigint ref2
		) {
	if (ixIdecVOolop == VecIdecVOolop::INB) insertBefore(refsList, refsPool, ref1, ref2);
	else if (ixIdecVOolop == VecIdecVOolop::INA) insertAfter(refsList, refsPool, ref1, ref2);
	else if (ixIdecVOolop == VecIdecVOolop::RMV) remove(refsList, refsPool, ref1);
	else if (ixIdecVOolop == VecIdecVOolop::TOB) toBefore(refsList, ref1, ref2);
	else if (ixIdecVOolop == VecIdecVOolop::TOA) toAfter(refsList, ref1, ref2);
	else if (ixIdecVOolop == VecIdecVOolop::SWP) swap(refsList, ref1, ref2);
};

void Oolop::insertBefore(
			vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref1
			, const ubigint ref2
		) {
	for (auto itPool=refsPool.begin();itPool!=refsPool.end();itPool++) {
		if (*itPool == ref1) {
			if (ref2 == 0) {
				refsList.insert(refsList.begin(), ref1);
				refsPool.erase(itPool);
			} else {
				for (auto itList=refsList.begin();itList!=refsList.end();itList++) {
					if (*itList == ref2) {
						refsList.insert(itList, ref1);
						refsPool.erase(itPool);
						break;
					};
				};
			};
			break;
		};
	};
};

void Oolop::insertAfter(
			vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref1
			, const ubigint ref2
		) {
	for (auto itPool=refsPool.begin();itPool!=refsPool.end();itPool++) {
		if (*itPool == ref1) {
			if (ref2 == 0) {
				refsList.push_back(ref1);
				refsPool.erase(itPool);
			} else {
				for (auto itList=refsList.begin();itList!=refsList.end();itList++) {
					if (*itList == ref2) {
						refsList.insert(++itList, ref1);
						refsPool.erase(itPool);
						break;
					};
				};
			};
			break;
		};
	};
};

void Oolop::remove(
			vector<ubigint>& refsList
			, vector<ubigint>& refsPool
			, const ubigint ref
		) {
	for (auto itList=refsList.begin();itList!=refsList.end();itList++) {
		if (*itList == ref) {
			refsList.erase(itList);
			refsPool.push_back(ref);
		};
	};
};

void Oolop::toBefore(
			vector<ubigint>& refsList
			, const ubigint ref1
			, const ubigint ref2
		) {
	// *******2*****1****
	// *******12*********
	for (unsigned int i=0;i<refsList.size();i++) {
		if (refsList[i] == ref2) {
			for (unsigned int j=i+1;j<refsList.size();j++) {
				if (refsList[j] == ref1) {
					for (unsigned int k=i+1;k<j;k++) refsList[k+1] = refsList[k];
					refsList[i] = ref1;
					refsList[i+1] = ref2;
					break;
				};
			};
			break;
		};
	};
};

void Oolop::toAfter(
			vector<ubigint>& refsList
			, const ubigint ref1
			, const ubigint ref2
		) {
	// *******1*****2****
	// ************21****
	for (unsigned int i=0;i<refsList.size();i++) {
		if (refsList[i] == ref1) {
			for (unsigned int j=i+1;j<refsList.size();j++) {
				if (refsList[j] == ref2) {
					for (unsigned int k=i+1;k<j;k++) refsList[k-1] = refsList[k];
					refsList[j] = ref1;
					refsList[j-1] = ref2;
					break;
				};
			};
			break;
		};
	};
};

void Oolop::swap(
			vector<ubigint>& refsList
			, const ubigint ref1
			, const ubigint ref2
		) {
	for (auto itList=refsList.begin();itList!=refsList.end();itList++) {
		if (*itList == ref1) {
			for (auto itList2=refsList.begin();itList2!=refsList.end();itList2++) {
				if (*itList2 == ref2) {
					*itList = ref2;
					*itList2 = ref1;
					break;
				};
			};
			break;
		};
	};
};

/******************************************************************************
 namespace Tmp
 ******************************************************************************/

string Tmp::newfile(
			const string& tmppath
			, const string& ext
		) {
	string filename;
	fstream tmpfile;

	unsigned int pathlen = tmppath.length() + 1;

	bool valid = false;

	while (!valid) {
		filename = tmppath + "/" + random();
		if (ext.length() > 0) filename += "." + ext;

		// check if present, create otherwise
		if (access(filename.c_str(), R_OK | W_OK) == -1) {
			tmpfile.open(filename.c_str(), ios::out);
			tmpfile.close();

			valid = true;
		};
	};

	return(filename.substr(pathlen));
};

string Tmp::newfolder(
			const string& tmppath
		) {
	string foldername;

	unsigned int pathlen = tmppath.length() + 1;

	bool valid = false;

	while (!valid) {
		foldername = tmppath + "/" + random();

		// check if present, create otherwise
		if (access(foldername.c_str(), R_OK | W_OK) == -1) {
#ifdef _WIN32
			mkdir(foldername.c_str());
#else
			mkdir(foldername.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

			valid = true;
		};
	};

	return(foldername.substr(pathlen));
};

string Tmp::random() {
	string retval;

	int digit;

	// random seed is done in engine initialization

	// fetch digits and make sure their ASCII code is in the range 0..9/a..z
	for (unsigned int i=0;i<8;i++) {
		digit = rand() % 36 + 48;
		if (digit > 57) digit += (97-48-10);

		retval = retval + ((char) digit);
	};

	return retval;
};

// IP cust --- IBEGIN
/******************************************************************************
 namespace Colormap
 ******************************************************************************/

unsigned int Colormap::red(
			const unsigned int range
			, double val
		) {
	if (val < 0.5) return(0);
	else if ((val >= 0.5) && (val < 0.75)) return(lround(((double) range)*4.0*(val-0.5)));
	else return(range);
};

unsigned int Colormap::green(
			const unsigned int range
			, double val
		) {
	if (val < 0.0) return(0);
	else if ((val >= 0.0) && (val < 0.25)) return(lround(((double) range)*4.0*val));
	else if ((val >= 0.25) && (val < 0.75)) return(range);
	else if ((val >= 0.75) && (val < 1.0)) return(lround(((double) range)*4.0*(1.0-val)));
	else return(0);
};

unsigned int Colormap::blue(
			const unsigned int range
			, double val
		) {
	if (val < 0.25) return(range);
	else if ((val >= 0.25) && (val < 0.5)) return(lround(((double) range)*4.0*(0.5-val)));
	else return(0);
};

/******************************************************************************
 namespace Dotmatrix
 ******************************************************************************/

bitset<35> Dotmatrix::getBitset(
			const char c
		) {
	if ((c == 'A') || (c == 'a')) return(bitset<35>("00100010101000110001111111000110001"));
	else if ((c == 'B') || (c == 'b')) return(bitset<35>("11110100011000111110100011000111110"));
	else if ((c == 'C') || (c == 'c')) return(bitset<35>("01111100001000010000100001000001111"));
	else if ((c == 'D') || (c == 'd')) return(bitset<35>("11110100011000110001100011000111110"));
	else if ((c == 'E') || (c == 'e')) return(bitset<35>("11111100001000011110100001000011111"));
	else if ((c == 'F') || (c == 'f')) return(bitset<35>("11111100001000011110100001000010000"));
	else if ((c == 'G') || (c == 'g')) return(bitset<35>("01111100001000010111100011000101111"));
	else if ((c == 'H') || (c == 'h')) return(bitset<35>("10001100011000111111100011000110001"));
	else if ((c == 'I') || (c == 'i')) return(bitset<35>("00100001000010000100001000010000100"));
	else if ((c == 'J') || (c == 'j')) return(bitset<35>("11111000010000100001000011000101110"));
	else if ((c == 'K') || (c == 'k')) return(bitset<35>("10001100101010011000101001001010001"));
	else if ((c == 'L') || (c == 'l')) return(bitset<35>("10000100001000010000100001000011111"));
	else if ((c == 'M') || (c == 'm')) return(bitset<35>("10001110111010110001100011000110001"));
	else if ((c == 'N') || (c == 'n')) return(bitset<35>("10001110011010110011100011000110001"));
	else if ((c == 'O') || (c == 'o')) return(bitset<35>("01110100011000110001100011000101110"));
	else if ((c == 'P') || (c == 'p')) return(bitset<35>("11110100011000111110100001000010000"));
	else if ((c == 'Q') || (c == 'q')) return(bitset<35>("01110100011000110001100010111000001"));
	else if ((c == 'R') || (c == 'r')) return(bitset<35>("11110100011000111110100011000110001"));
	else if ((c == 'S') || (c == 's')) return(bitset<35>("01111100001000001110000010000111110"));
	else if ((c == 'T') || (c == 't')) return(bitset<35>("11111001000010000100001000010000100"));
	else if ((c == 'U') || (c == 'u')) return(bitset<35>("10001100011000110001100011000101110"));
	else if ((c == 'V') || (c == 'v')) return(bitset<35>("10001100011000110001100010101000100"));
	else if ((c == 'W') || (c == 'w')) return(bitset<35>("10001100011000110001101011101110001"));
	else if ((c == 'X') || (c == 'x')) return(bitset<35>("10001100010101000100010101000110001"));
	else if ((c == 'Y') || (c == 'y')) return(bitset<35>("10001100010101000100001000010000100"));
	else if ((c == 'Z') || (c == 'z')) return(bitset<35>("11111000010001000100010001000011111"));
	else if (c == '0') return(bitset<35>("01110100011001110101110011000101110"));
	else if (c == '1') return(bitset<35>("00010001100101000010000100001000010"));
	else if (c == '2') return(bitset<35>("01110100010001000100010001000011111"));
	else if (c == '3') return(bitset<35>("01110100010000101110000011000101110"));
	else if (c == '4') return(bitset<35>("00010001100101010010111110001000010"));
	else if (c == '5') return(bitset<35>("11111100001000011110000010000111110"));
	else if (c == '6') return(bitset<35>("01110100011000011110100011000101110"));
	else if (c == '7') return(bitset<35>("11111000010001011111001000100010000"));
	else if (c == '8') return(bitset<35>("01110100011000101110100011000101110"));
	else if (c == '9') return(bitset<35>("01110100011000101111000010000111110"));
	else if (c == '.') return(bitset<35>("00000000000000000000000000110001100"));
	else if (c == '(') return(bitset<35>("00010001000100001000010000010000010"));
	else if (c == ')') return(bitset<35>("01000001000001000010000100010001000"));
	else if (c == '[') return(bitset<35>("01110010000100001000010000100001110"));
	else if (c == ']') return(bitset<35>("01110000100001000010000100001001110"));
	else if (c == '<') return(bitset<35>("00001000100010001000001000001000001"));
	else if (c == '>') return(bitset<35>("10000010000010000010001000100010000"));
	else if (c == '+') return(bitset<35>("00000001000010011111001000010000000"));
	else if (c == '-') return(bitset<35>("00000000000000011111000000000000000"));
	else if (c == '*') return(bitset<35>("00000000000101000100010100000000000"));
	else if (c == '/') return(bitset<35>("00000000010001000100010001000000000"));
	else if (c == '%') return(bitset<35>("11000110010001000100010001001100011"));
	else if (c == ',') return(bitset<35>("00000000000000001100011000010001000"));
	else if (c == '=') return(bitset<35>("00000000001111100000111110000000000"));
	else if (c == '|') return(bitset<35>("00100001000010000100001000010000100"));
	else if (c == '^') return(bitset<35>("00100010101000100000000000000000000"));
	else return(bitset<35>());
};

bool Dotmatrix::getDot(
			const char c
			, const unsigned int ix
		) {
	return getBitset(c)[ix];
};

/******************************************************************************
 class Imgbufitem
 ******************************************************************************/

Imgbufitem::Imgbufitem(
			const unsigned int seqno
			, const timespec timestamp
			, unsigned char* data
			, const size_t datalen
			, const ubigint jref
		) {
	this->seqno = seqno;
	this->timestamp = timestamp;
	this->data = data;
	this->datalen = datalen;

	claim(jref);
};

void Imgbufitem::claim(
			const ubigint jref
		) {
	bool found = false;

	for (list<ubigint>::iterator it=jrefsClaim.begin() ; it!=jrefsClaim.end() ; it++) {
		if (*it > jref) {
			jrefsClaim.insert(it, jref);
			found = true;
			break;
		};
	};

	if (!found) jrefsClaim.push_back(jref);
};

void Imgbufitem::release(
			const ubigint jref
		) {
	for (list<ubigint>::iterator it=jrefsClaim.begin() ; it!=jrefsClaim.end() ; it++) {
		if (*it == jref) {
			jrefsClaim.erase(it);
			break;
		} else if (*it > jref) break;
	};
};

/******************************************************************************
 class Imgbuf
 ******************************************************************************/

Imgbuf::Imgbuf() {
	N = 0;
	itemlen = 0;

	brefseq = 0;

	initdone = false;
};

Imgbuf::~Imgbuf() {
	term();
};

void Imgbuf::init(
			const unsigned int N
			, const unsigned int itemlen
		) {
	int res;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	data = new unsigned char[N*itemlen];
	this->N = N;
	this->itemlen = itemlen;

	res = pthread_mutex_init(&mAccess, &attr);
	if (res != 0) {cout << "Imgbuf::init() error initializing mutex mAccess (" << res << ")" << endl;};

	brefseq = 0;

	brefs.clear();
	brefs.resize(N, 0);

	brefsItems.clear();

	pthread_mutexattr_destroy(&attr);
	
	initdone = true;
};

void Imgbuf::term() {
	int res;

	if (initdone) {
		res = pthread_mutex_lock(&mAccess);
		if (res != 0) {cout << "Imgbuf::term() error locking mutex mAccess (" << res << ")" << endl;};

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "Imgbuf::term() error unlocking mutex mAccess (" << res << ")" << endl;};

		while (true) {
			res = pthread_mutex_destroy(&mAccess);
			if (res == EBUSY) {
				res = pthread_mutex_unlock(&mAccess);
				if (res != 0) {cout << "Imgbuf::term() error unlocking mutex mAccess (" << res << ")" << endl;};
			} else {
				if (res != 0) {cout << "Imgbuf::term() error destroying mutex mAccess (" << res << ")" << endl;};
				break;
			};
		};

		delete[] data;
		for (map<ubigint,Imgbufitem*>::iterator it=brefsItems.begin() ; it!=brefsItems.end() ; it++) delete(it->second);
		
		initdone = false;
	};
};

ubigint Imgbuf::getNewItem(
			const ubigint jref
			, const unsigned int seqno
			, timespec timestamp
		) {
	int res;
	ubigint bref;

	unsigned int ix;
	bool found;

	if (initdone) {
		res = pthread_mutex_lock(&mAccess);
		if (res != 0) {cout << "Imgbuf::getNewItem() error locking mutex mAccess (" << res << ")" << endl;};

		// check for available slot
		bref = 0;

		found = false;

		for (ix=0;ix<N;ix++) {
			if (brefs[ix] == 0) {
				found = true;
				break;
			};
		};

		if (!found) {
			ix = cleanup();
			found = (ix < N);
		};

		if (found) {
			// get new bref
			brefseq++;
			bref = brefseq;

			brefs[ix] = bref;

			// create new item
			if (timestamp.tv_sec == 0) Idec::getTimestamp(&timestamp);
			brefsItems[bref] = new Imgbufitem(seqno, timestamp, &(data[ix*itemlen]), itemlen, jref);
		};

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "Imgbuf::getNewItem() error unlocking mutex mAccess (" << res << ")" << endl;};

		return(bref);
	};

	return 0;
};

Imgbufitem* Imgbuf::getItem(
			const ubigint bref
		) {
	// assuming that claim is already made or mAccess is locked

	map<ubigint,Imgbufitem*>::iterator it;

	if (initdone) {
		it = brefsItems.find(bref);
		if (it != brefsItems.end()) return it->second;
	};

	return NULL;
};

void Imgbuf::claim(
			const ubigint bref
			, const ubigint jref
		) {
	int res;

	Imgbufitem* item = NULL;

	if (initdone) {
		res = pthread_mutex_lock(&mAccess);
		if (res != 0) {cout << "Imgbuf::claim() error locking mutex mAccess (" << res << ")" << endl;};

		item = getItem(bref);
		if (item) item->claim(jref);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "Imgbuf::claim() error unlocking mutex mAccess (" << res << ")" << endl;};
	};
};

void Imgbuf::release(
			const ubigint bref
			, const ubigint jref
		) {
	int res;

	Imgbufitem* item = NULL;

	if (initdone) {
		res = pthread_mutex_lock(&mAccess);
		if (res != 0) {cout << "Imgbuf::release() error locking mutex mAccess (" << res << ")" << endl;};

		item = getItem(bref);
		if (item) item->release(jref);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "Imgbuf::release() error unlocking mutex mAccess (" << res << ")" << endl;};
	};
};

void Imgbuf::releaseByJref(
			const ubigint jref
		) {
	int res;

	Imgbufitem* item = NULL;

	if (initdone) {
		res = pthread_mutex_lock(&mAccess);
		if (res != 0) {cout << "Imgbuf::releaseByJref() error locking mutex mAccess (" << res << ")" << endl;};

		for (map<ubigint,Imgbufitem*>::iterator it=brefsItems.begin() ; it!=brefsItems.end() ; it++) {
			item = it->second;
			item->release(jref);
		};

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "Imgbuf::releaseByJref() error unlocking mutex mAccess (" << res << ")" << endl;};
	};
};

unsigned int Imgbuf::cleanup() {
	unsigned int ix = 0;

	map<ubigint,Imgbufitem*>::iterator it;

	Imgbufitem* item = NULL;

	if (initdone) {
		// all entries in brefs are != 0
		for (;ix<N;ix++) {
			it = brefsItems.find(brefs[ix]);

			if (it != brefsItems.end()) {
				item = it->second;

				if (item->jrefsClaim.empty()) {
					brefsItems.erase(it);
					delete item;

					brefs[ix] = 0;

					break;
				};
			} else break;
		};
	};

	return ix;
};

/******************************************************************************
 class Snippet
 ******************************************************************************/

Snippet::Snippet(
			const uint ixIdecVCamres
			, const uint ixIdecVChannel
			, const unsigned int w
			, const unsigned int h
			, const unsigned int x0
			, const unsigned int y0
		) {
	int res;
	pthread_mutexattr_t attr;

	unsigned int wh;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	this->ixIdecVCamres = ixIdecVCamres;
	this->ixIdecVChannel = ixIdecVChannel;

	this->w = w;
	this->h = h;

	if (w == 0) Idec::getCamresWh(ixIdecVCamres, this->w, this->h);

	wh = this->w * this->h;

	if (wh == 0) data = NULL;
	else {
		if (ixIdecVChannel == VecIdecVChannel::GRAY16) data = new unsigned char[2*wh];
		else if (ixIdecVChannel == VecIdecVChannel::DEPTHSP) data = new unsigned char[4*wh];
		else data = new unsigned char[wh];
	};

	this->x0 = x0;
	this->y0 = y0;

	res = pthread_mutex_init(&mAccess, &attr);
	if (res != 0) {cout << "Snippet::Snippet() error initializing mutex mAccess (" << res << ")" << endl;};

	jrefClaim = 0;

	pthread_mutexattr_destroy(&attr);
};

Snippet::~Snippet() {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "Snippet::~Snippet() error locking mutex mAccess (" << res << ")" << endl;};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "Snippet::~Snippet() error unlocking mutex mAccess (" << res << ")" << endl;};

	while (true) {
		res = pthread_mutex_destroy(&mAccess);
		if (res == EBUSY) {
			res = pthread_mutex_unlock(&mAccess);
			if (res != 0) {cout << "Snippet::~Snippet() error unlocking mutex mAccess (" << res << ")" << endl;};
		} else {
			if (res != 0) {cout << "Snippet::~Snippet() error destroying mutex mAccess (" << res << ")" << endl;};
			break;
		};
	};

	if (data) delete[] data;
};

void Snippet::reposition(
			const unsigned int _x0
			, const unsigned int _y0
		) {
	x0 = _x0;
	y0 = _y0;
};

void Snippet::clear() {
	unsigned int wh = w*h;

	if (data) {
		if (ixIdecVChannel == VecIdecVChannel::GRAY16) memset((void*) data, 0, 2*wh);
		else if (ixIdecVChannel == VecIdecVChannel::DEPTHSP) memset((void*) data, 0, 4*wh);
		else memset((void*) data, 0, wh);
	};
};

bool Snippet::claim(
			const ubigint jref
		) {
	bool retval;

	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) cout << "Snippet::claim() error locking mutex mAccess (" << res << ")" << endl;

	if (jrefClaim == 0) {
		jrefClaim = jref;
		retval = true;
	} else retval = false;

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) cout << "Snippet::claim() error unlocking mutex mAccess (" << res << ")" << endl;

	return retval;
};

void Snippet::release() {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) cout << "Snippet::release() error locking mutex mAccess (" << res << ")" << endl;

	jrefClaim = 0;

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) cout << "Snippet::release() error unlocking mutex mAccess (" << res << ")" << endl;
};

void Snippet::addDottext(
			const string& s
			, const uint ixIdecVCorner
			, const unsigned int margin
			, const bool invert
		) {
	int x0, y0, x;
	unsigned int ix;

	int bg, fg;

	bitset<35> bits;

	if ( (ixIdecVChannel == VecIdecVChannel::DEPTHSP) || !data || (w < (2*margin+7)) || (h < (2*margin+9)) ) return;

	x0 = 0;
	y0 = 0;

	if ((ixIdecVCorner == VecIdecVCorner::SW) || (ixIdecVCorner == VecIdecVCorner::W) || (ixIdecVCorner == VecIdecVCorner::NW)) {
		x0 = margin;
	} else if ((ixIdecVCorner == VecIdecVCorner::N) || (ixIdecVCorner == VecIdecVCorner::S)) {
		x0 = (w-6*s.length()-1)/2;
	} else if ((ixIdecVCorner == VecIdecVCorner::NE) || (ixIdecVCorner == VecIdecVCorner::E) || (ixIdecVCorner == VecIdecVCorner::SE)) {
		x0 = w-margin-6*s.length()-1;
	};

	if ((ixIdecVCorner == VecIdecVCorner::N) || (ixIdecVCorner == VecIdecVCorner::NE) || (ixIdecVCorner == VecIdecVCorner::NW)) {
		y0 = margin;
	} else if ((ixIdecVCorner == VecIdecVCorner::E) || (ixIdecVCorner == VecIdecVCorner::W)) {
		y0 = (h-9)/2;
	} else if ((ixIdecVCorner == VecIdecVCorner::SE) || (ixIdecVCorner == VecIdecVCorner::S) || (ixIdecVCorner == VecIdecVCorner::SW)) {
		y0 = h-margin-9;
	};
	
	// standard: black on white, inverted: white on black
	if (invert) {
		bg = 0;
		fg = 65535;
	} else {
		bg = 65535;
		fg = 0;
	};

	for (unsigned int i=0;i<s.length();i++) {
		x = x0 + i*6;

		if ((i == 0) && (x > 0)) {
			// left border
			if (ixIdecVChannel == VecIdecVChannel::GRAY16) for (unsigned int j=0;j<9;j++) ((unsigned short*) data)[(y0+j)*w+x-1] = bg;
			else for (unsigned int j=0;j<9;j++) data[(y0+j)*w+x-1] = bg;
		};

		if ((x >= margin) && ((x+6) <= (w-margin))) {
			// y0 within limits assured by check at the very beginning
			bits = Dotmatrix::getBitset(s[i]);

			if (ixIdecVChannel == VecIdecVChannel::GRAY16) {
				for (unsigned int j=0;j<54;j++) {
					ix = (y0+8-j/6)*w + x + 5-(j%6);

					if ((j >= 6) && (j < 48) && ((j%6) > 0)) ((unsigned short*) data)[ix] = (bits[((j-6)/6)*5+(j%6)-1]) ? fg : bg;
					else ((unsigned short*) data)[ix] = bg;
				};

			} else {
				for (unsigned int j=0;j<54;j++) {
					ix = (y0+8-j/6)*w + x + 5-(j%6);

					if ((j >= 6) && (j < 48) && ((j%6) > 0)) data[ix] = (bits[((j-6)/6)*5+(j%6)-1]) ? fg : bg;
					else data[ix] = bg;
				};
			};
		};
	};
};

/******************************************************************************
 class Testpat
 ******************************************************************************/

Testpat::Testpat(
			const unsigned int w
			, const unsigned int h
			, const bool grayscale
		) {
	double even, odd;
	unsigned int iEven, iOdd;

	unsigned int r;

	unsigned int ix;

	this->w = w;
	this->h = h;

	this->grayscale = grayscale;

	dh = 16;

	if (h >= (3*dh)) hWhite = dh + ((h-dh)%(2*dh));
	else hWhite = h;

	r0 = h/3;
	dr = 5;

	ofs = 0;
	up = false;

	// bars
	if (grayscale) {
		grayEven = new unsigned short[w*dh];
		grayOdd = new unsigned short[w*dh];

		for (unsigned int i=0;i<w;i++) {
			even = 0.5*((double)i)/((double)w);
			odd = 1.0-even;

			iEven = lround(65535.0*even);
			iOdd = lround(65535.0*odd);

			for (unsigned int j=0;j<dh;j++) {
				grayEven[j*w+i] = iEven;
				grayOdd[j*w+i] = iOdd;
			};
		};

		redEven = NULL;
		redOdd = NULL;
		greenEven = NULL;
		greenOdd = NULL;
		blueEven = NULL;
		blueOdd = NULL;

	} else {
		grayEven = NULL;
		grayOdd = NULL;

		redEven = new unsigned char[w*dh];
		redOdd = new unsigned char[w*dh];
		greenEven = new unsigned char[w*dh];
		greenOdd = new unsigned char[w*dh];
		blueEven = new unsigned char[w*dh];
		blueOdd = new unsigned char[w*dh];

		for (unsigned int i=0;i<w;i++) {
			even = 0.5*((double)i)/((double)w);
			odd = 1.0-even;

			iEven = Colormap::red(255, even);
			iOdd = Colormap::red(255, odd);
			for (unsigned int j=0;j<dh;j++) {
				redEven[j*w+i] = iEven;
				redOdd[j*w+i] = iOdd;
			};

			iEven = Colormap::green(255, even);
			iOdd = Colormap::green(255, odd);
			for (unsigned int j=0;j<dh;j++) {
				greenEven[j*w+i] = iEven;
				greenOdd[j*w+i] = iOdd;
			};

			iEven = Colormap::blue(255, even);
			iOdd = Colormap::blue(255, odd);
			for (unsigned int j=0;j<dh;j++) {
				blueEven[j*w+i] = iEven;
				blueOdd[j*w+i] = iOdd;
			};
		};
	};

	for (unsigned int i=0;i<h;i++) {
		for (unsigned int j=0;j<w;j++) {
			ix = i*w+j;

			// circle
			r = sqrt((i-h/2)*(i-h/2) + (j-w/2)*(j-w/2));
			if ((r >= (r0-dr/2)) && (r <= (r0+dr/2))) icsCircle.push_back(ix);
			
			// h and v lines
			if ((i >= (h/2-dr/2)) && (i <= (h/2+dr/2)) && (j >= (w/2))) icsHline.push_back(ix);
			if ((i <= (h/2)) && (j >= (w/2-dr/2)) && (j <= (w/2+dr/2))) icsVline.push_back(ix);
		};
	};
};

Testpat::~Testpat() {
	if (redEven) delete[] redEven;
	if (redOdd) delete[] redOdd;
	if (greenEven) delete[] greenEven;
	if (greenOdd) delete[] greenOdd;
	if (blueEven) delete[] blueEven;
	if (blueOdd) delete[] blueOdd;

	if (grayEven) delete[] grayEven;
	if (grayOdd) delete[] grayOdd;
};

void Testpat::step(
			unsigned char* buf
		) {
	void* src;

	unsigned int ix;

	if (grayscale) {
		unsigned short* gray = (unsigned short*) buf;

		// white bar
		memset((void*) &(gray[ofs*w]), 255, 2*w*hWhite);

		// even/odd bars
		for (unsigned int i=0;i<((h-hWhite)/dh);i++) {
			ix = ofs + hWhite + i*dh;
			if (ix >= h) ix -= h;

			if ((i%2) == 0) src = (void*) grayEven;
			else src = (void*) grayOdd;

			if ((ix+dh) <= h) memcpy((void*) &(gray[ix*w]), src, 2*w*dh);
			else {
				// spill over
				memcpy((void*) &(gray[ix*w]), src, 2*w*(h-ix));
				memcpy((void*) gray, src, 2*w*(dh-(h-ix)));
			};
		};

		// circle, h and v lines
		for (unsigned int i=0;i<icsCircle.size();i++) gray[icsCircle[i]] = 65535;
		for (unsigned int i=0;i<icsHline.size();i++) gray[icsHline[i]] = 0;
		for (unsigned int i=0;i<icsVline.size();i++) gray[icsVline[i]] = 0;

	} else {
		unsigned char* red = buf;
		unsigned char* green = &(buf[w*h]);
		unsigned char* blue = &(buf[2*w*h]);

		// white bar
		memset(&(red[ofs*w]), 255, w*hWhite);
		memset(&(green[ofs*w]), 255, w*hWhite);
		memset(&(blue[ofs*w]), 255, w*hWhite);

		// even/odd bars
		for (unsigned int i=0;i<((h-hWhite)/dh);i++) {
			ix = ofs + hWhite + i*dh;
			if (ix >= h) ix -= h;

			// red
			if ((i%2) == 0) src = (void*) redEven;
			else src = (void*) redOdd;

			if ((ix+dh) <= h) memcpy((void*) &(red[ix*w]), src, w*dh);
			else {
				memcpy((void*) &(red[ix*w]), src, w*(h-ix));
				memcpy((void*) red, src, w*(dh-(h-ix)));
			};

			// green
			if ((i%2) == 0) src = (void*) greenEven;
			else src = (void*) greenOdd;

			if ((ix+dh) <= h) memcpy((void*) &(green[ix*w]), src, w*dh);
			else {
				memcpy((void*) &(green[ix*w]), src, w*(h-ix));
				memcpy((void*) green, src, w*(dh-(h-ix)));
			};

			// blue
			if ((i%2) == 0) src = (void*) blueEven;
			else src = (void*) blueOdd;

			if ((ix+dh) <= h) memcpy((void*) &(blue[ix*w]), src, w*dh);
			else {
				memcpy((void*) &(blue[ix*w]), src, w*(h-ix));
				memcpy((void*) blue, src, w*(dh-(h-ix)));
			};
		};

		// circle, h and v lines
		for (unsigned int i=0;i<icsCircle.size();i++) {
			red[icsCircle[i]] = 255;
			green[icsCircle[i]] = 255;
			blue[icsCircle[i]] = 255;
		};
		for (unsigned int i=0;i<icsHline.size();i++) {
			red[icsHline[i]] = 0;
			green[icsHline[i]] = 0;
			blue[icsHline[i]] = 0;
		};
		for (unsigned int i=0;i<icsVline.size();i++) {
			red[icsVline[i]] = 0;
			green[icsVline[i]] = 0;
			blue[icsVline[i]] = 0;
		};
	};

	if (up) {
		if (ofs == 0) up = false;
		else ofs--;
	} else {
		if ((ofs+hWhite) == h) up = true;
		else ofs++;
	};
};
// IP cust --- IEND

/******************************************************************************
 namespace Idec
 ******************************************************************************/

// IP gbl --- IBEGIN
void Idec::getTimestamp(
			timespec* timestamp
		) {
#ifdef __MACH__
	timeval tv;
	gettimeofday(&tv, NULL);
	timestamp->tv_sec = tv.tv_sec;
	timestamp->tv_nsec = 1000*tv.tv_usec;
#else
	clock_gettime(CLOCK_REALTIME, timestamp);
#endif
};

double Idec::getDoubletime(
			timespec* timestamp
		) {
	return(((double) timestamp->tv_sec) + 1.0e-9 * ((double) timestamp->tv_nsec));
};

void Idec::setupIpl(
			const double xscl // scaling of x-axis values, ymax / xmax for x0 = y0 = 0
			, vector<double>& y
			, const unsigned int N
			, vector<usmallint>& iplX
			, vector<double>& iplY
		) {
	// requirements for y: highest distances between two consecutive points first, strictly monotonically increasing

	unsigned int ixY, ixI, rixI;
	double total, sum, rsum, d;

	iplX.resize(N);
	iplY.resize(N);

	ixY = 0;
	ixI = 0;
	rixI = N-1;

	// determine path length
	total = 0.0;
	for (unsigned int i=0;i<(y.size()-1);i++) total += sqrt(xscl*xscl + pow(y[i+1]-y[i], 2.0)); // forward, i.e. i -> i+1

	sum = 0.0;
	rsum = total;

	d = rsum / ((double) rixI);

	// select y points which are equidistant in sqrt(dx^2+dy^2) ; placement in iplX/iplY after each sufficient increment
	// avoid doubles and take care of situations where distance between points in original data exceeds equidistance constant
	for ( ; ixI<N ; ixI++, rixI--) {
		while ( (sum + ((double) rixI)*d) < total) {
			ixY++;

			if ((ixY+1) == y.size()) break;
			sum += sqrt(xscl*xscl + pow(y[ixY]-y[ixY-1], 2.0));
		};

		if (ixI != 0) if (iplX[ixI-1] == ixY) {
			// avoid double
			ixY++;
			sum += sqrt(xscl*xscl + pow(y[ixY]-y[ixY-1], 2.0));
		};

		rsum = total - sum;
		d = rsum / ((double) rixI);

		if (ixY == y.size()) {
			iplX[ixI] = y.size()-1;
			iplY[ixI] = y[y.size()-1];
		} else {
			iplX[ixI] = ixY;
			iplY[ixI] = y[ixY];
		};
	};

	// - determine quality of interpolation
	map<unsigned int, unsigned int> icsI; // key: y index, value: lower iplX index

	for (ixY=0, ixI=0 ; ixY<y.size() ; ixY++) {
		if ((ixI+1) < N) while (iplX[ixI+1] < ixY) ixI++;
		icsI[ixY] = ixI;
	};

	double res, resr; // one-norm of exact residual (res) and redidual of rounded values (resr)

	res = 0.0;
	resr = 0.0;

	for (ixY=0 ; ixY<y.size() ; ixY++) {
		ixI = icsI[ixY];

		d = iplY[ixI] + ((double) (ixY-iplX[ixI]))/((double) (iplX[ixI+1]-iplX[ixI])) * (iplY[ixI+1]-iplY[ixI]);

		res += fabs(y[ixY] - d);
		resr += fabs(round(y[ixY]) - round(d));
	};

	res /= ((double) y.size());
	resr /= ((double) y.size());

	cout << "\tIdec::setupIpl(): for N=" << N << ", res=" << res << ", resr=" << resr << endl;
};

void Idec::setupFromIpl(
			vector<usmallint>& iplX
			, vector<double>& iplY
			, const unsigned int N
			, vector<double>& y
		) {
	unsigned int ixY, ixI;

	map<unsigned int, unsigned int> icsI; // key: y index, value: lower iplX index

	y.resize(N);

	for (ixY=0, ixI=0 ; ixY<N ; ixY++) {
		if ((ixI+1) < iplX.size()) while (iplX[ixI+1] < ixY) ixI++;
		icsI[ixY] = ixI;
	};

	for (ixY=0 ; ixY<N ; ixY++) {
		ixI = icsI[ixY];

		y[ixY] = iplY[ixI] + ((double) (ixY-iplX[ixI]))/((double) (iplX[ixI+1]-iplX[ixI])) * (iplY[ixI+1]-iplY[ixI]);
	};
};

void Idec::getCamresWh(
			const uint ixIdecVCamres
			, unsigned int& w
			, unsigned int& h
			, const unsigned int _w
			, const unsigned int _h
		) {
	switch (ixIdecVCamres) {
		case VecIdecVCamres::_160: w = 160; h = 120; break;
		case VecIdecVCamres::_320: w = 320; h = 240; break;
		case VecIdecVCamres::_640: w = 640; h = 480; break;
		case VecIdecVCamres::_800: w = 800; h = 600; break;
		case VecIdecVCamres::_1024: w = 1024; h = 768; break;
		case VecIdecVCamres::MAX: w = _w; h = _h; break;
		default: w = 0; h = 0;
	};
};

void Idec::setupIntavg(
			const unsigned int inN
			, const unsigned int inMax
			, const unsigned int outMax
			, const double outPmin
			, unsigned int& im
			, bool* rshs
			, unsigned int& rshsN
		) {
	double insum, p;

	double doutMax = outMax;

	double scl = inMax * inN;

	double m;

	// integer multiplier
	im = outMax / scl;

	insum = im * scl;
	p = insum / doutMax;

	// sub-integer multipliers
	m = 0.5;

	for (unsigned int i=0;i<rshsN;i++) {
		if ((p < outPmin) && ((insum + m*scl) < doutMax)) {
			rshs[i] = true;
			insum += m*scl;
			p = insum / doutMax;

		} else {
			rshs[i] = false;
		};

		m *= 0.5;
	};

	for (unsigned int i=rshsN;i>0;i--) if (!rshs[i-1]) rshsN--; else break;

	// dump result
/*
	double d = im;

	m = 0.5;
	for (unsigned int i=0 ; i<rshsN ; i++) {
		if (rshs[i]) d += m;
		m *= 0.5;
	};

	cout << "\tfor inN=" << inN << ", inMax=" << inMax << ", outMax=" << outMax << ", calculated im=" << im << " and rshs=";
	for (unsigned int i=0;i<rshsN;i++) if (rshs[i]) cout << "1"; else cout << "0";
	cout << ", corresponding to m=" << d << endl;
*/
};

unsigned int Idec::intavg(
			const unsigned int in
			, const unsigned int im
			, bool* rshs
			, const unsigned int rshsN
		) {
	unsigned int retval = im*in;

	for (unsigned int i=0;i<rshsN;i++) if (rshs[i]) retval += (in >> (i+1));

	return retval;
};

void Idec::copytrfBuf(
			unsigned char* src
			, unsigned char* trg
			, const unsigned int wlen
			, const unsigned int w
			, const unsigned int h
			, const uint ixIdecVSqrgrp
		) {
	unsigned int i, invi;
	unsigned int j, invj;

	unsigned int* k = NULL;
	unsigned int* l = NULL;

	unsigned int ix;

	bool skip = false;

	if ((w == h) && (ixIdecVSqrgrp == VecIdecVSqrgrp::R1)) {
		k = &invj;
		l = &i;
	} else if (ixIdecVSqrgrp == VecIdecVSqrgrp::R2) {
		k = &invi;
		l = &invj;
	} else if ((w == h) && (ixIdecVSqrgrp == VecIdecVSqrgrp::R3)) {
		k = &j;
		l = &invi;
	} else if (ixIdecVSqrgrp == VecIdecVSqrgrp::S0) {
		k = &i;
		l = &invj;
	} else if ((w == h) && (ixIdecVSqrgrp == VecIdecVSqrgrp::S1)) {
		k = &j;
		l = &i;
	} else if (ixIdecVSqrgrp == VecIdecVSqrgrp::S2) {
		k = &invi;
		l = &j;
	} else if ((w == h) && (ixIdecVSqrgrp == VecIdecVSqrgrp::S3)) {
		k = &invj;
		l = &invi;
	} else {
		// R0 and invalid ; perform straight copy
		memcpy(trg, src, wlen*w*h);
		skip = true;
	};

	if (!skip) {
		for (i=0,invi=h-1 ; i<h ; i++,invi--) {
			for (j=0,invj=w-1 ; j<w ; j++,invj--) {
				ix = (*k)*w + (*l);
				for (unsigned int m=0;m<wlen;m++) trg[wlen*ix+m] = src[wlen*(i*w+j)+m];
			};
		};
	};
};

void Idec::addSpot(
			unsigned char* buf
			, const unsigned int w
			, const unsigned int h
			, const double A
			, const double x0
			, const double y0
			, const double dr
		) {
	const double eps = 1.0;

	double r, rr;

	int lim, val;
	unsigned int xmin, xmax, ymin, ymax;

	// radius in pixels so that the increment is at least one eps (typically LSB, i.e. 1)
	if (((eps-0.5)/A) <= 1.0) {
		// require negative ln() or (eps-0.5)/A < 1
		r = dr * sqrt(log((eps-0.5)/A)/-2.773);

		lim = (int) floor(x0-r);
		if (lim < 0) xmin = 0; else xmin = lim;

		lim = (int) ceil(x0+r);
		if (((unsigned int) (lim+1)) > w) xmax = w-1; else xmax = lim;

		lim = (int) floor(y0-r);
		if (lim < 0) ymin = 0; else ymin = lim;

		lim = (int) ceil(y0+r);
		if (((unsigned int) (lim+1)) > h) ymax = h-1; else ymax = lim;

		// add to buffer, consider case of saturation
		for (unsigned int i=ymin;i<=ymax;i++) {
			for (unsigned int j=xmin;j<=xmax;j++) {
				rr = pow(((double) j)-x0, 2.0) + pow(((double) i)-y0, 2.0);

				val = ((int) (buf[i*w+j])) + lround(A * exp(-2.773 * rr / pow(dr, 2.0)));
				if (val > 255) val = 255;
// cout << "rr=" << rr << ", buf[i*w+j]=" << ((int) (buf[i*w+j])) << ", val=" << val << endl;

				buf[i*w+j] = val;
			};
		};
	};
};
// IP gbl --- IEND

/******************************************************************************
 namespace OpengIdec
 ******************************************************************************/

void OpengIdec::getIcsIdecVOppackByIxIdecVOpengtype(
			const uint ixIdecVOpengtype
			, vector<uint>& icsIdecVOppack
		) {
	icsIdecVOppack.clear();

};

void OpengIdec::getIcsIdecVDpchByIxIdecVOppack(
			const uint ixIdecVOppack
			, set<uint>& icsIdecVDpch
		) {
};

/******************************************************************************
 namespace StubIdec
 ******************************************************************************/

string StubIdec::getStub(
			DbsIdec* dbsidec
			, const uint ixIdecVStub
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	if (ixIdecVStub == VecIdecVStub::STUBIDECFILSTD) return getStubFilStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECGRP) return getStubGrp(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECMISSTD) return getStubMisStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECOWN) return getStubOwn(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECPRSSTD) return getStubPrsStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECSESMENU) return getStubSesMenu(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECSESSTD) return getStubSesStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECTOUSTD) return getStubTouStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECUSGSTD) return getStubUsgStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);
	else if (ixIdecVStub == VecIdecVStub::STUBIDECUSRSTD) return getStubUsrStd(dbsidec, ref, ixIdecVLocale, ixVNonetype, stcch, strefSub, refresh);

	return("");
};

string StubIdec::getStubFilStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "VecXxxxVYyyyy.cpp"
	string stub;

	stcchitemref_t stref(VecIdecVStub::STUBIDECFILSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no file)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Datei)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmfile->loadFnmByRef(ref, stub)) {
			if (stcch) {
				if (!stit) stit = stcch->addStit(stref);
				stit->stub = stub;
			};
		};
	};

	return stub;
};

string StubIdec::getStubGrp(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "agroup"
	string stub;

	stcchitemref_t stref(VecIdecVStub::STUBIDECGRP, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no user group)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Benutzergruppe)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmusergroup->loadSrfByRef(ref, stub)) {
			if (stcch) {
				if (!stit) stit = stcch->addStit(stref);
				stit->stub = stub;
			};
		};
	};

	return stub;
};

string StubIdec::getStubMisStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "Bosnia flood relief 2014"
	string stub;

	stcchitemref_t stref(VecIdecVStub::STUBIDECMISSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no mission)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Mission)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmmission->loadTitByRef(ref, stub)) {
			if (stcch) {
				if (!stit) stit = stcch->addStit(stref);
				stit->stub = stub;
			};
		};
	};

	return stub;
};

string StubIdec::getStubOwn(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "auser"
	string stub;

	stcchitemref_t stref(VecIdecVStub::STUBIDECOWN, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keiner)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no user)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(kein Benutzer)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmuser->loadSrfByRef(ref, stub)) {
			if (stcch) {
				if (!stit) stit = stcch->addStit(stref);
				stit->stub = stub;
			};
		};
	};

	return stub;
};

string StubIdec::getStubPrsStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "Franz Kuntz"
	string stub;

	IdecMPerson* rec = NULL;

	stcchitemref_t stref(VecIdecVStub::STUBIDECPRSSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no person)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Person)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmperson->loadRecByRef(ref, &rec)) {
			if (stcch && !stit) stit = stcch->addStit(stref);
			// IP getStubIdecPrsStd --- BEGIN
			stub = rec->Lastname;
			if (rec->Firstname.length() > 0) stub = rec->Firstname + " " + stub;
			// IP getStubIdecPrsStd --- END
			if (stit) stit->stub = stub;
			delete rec;
		};
	};

	return stub;
};

string StubIdec::getStubSesMenu(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "user Franz Kuntz (fkuntz) logged in from 127.0.0.1 since 01-01-2010 10:34"
	string stub;

	IdecMSession* rec = NULL;

	stcchitemref_t stref(VecIdecVStub::STUBIDECSESMENU, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no session)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Sitzung)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmsession->loadRecByRef(ref, &rec)) {
			if (stcch && !stit) stit = stcch->addStit(stref);
			// IP getStubIdecSesMenu --- BEGIN
			if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "user " + getStubUsrStd(dbsidec, rec->refIdecMUser, ixIdecVLocale, ixVNonetype, stcch, &stref) + ";logged in from " + rec->Ip + ";since " + Ftm::stamp(rec->start);
			else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "Benutzer " + getStubUsrStd(dbsidec, rec->refIdecMUser, ixIdecVLocale, ixVNonetype, stcch, &stref) + ";eingeloggt von " + rec->Ip + ";seit " + Ftm::stamp(rec->start);
			// IP getStubIdecSesMenu --- END
			if (stit) stit->stub = stub;
			delete rec;
		};
	};

	return stub;
};

string StubIdec::getStubSesStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "01-01-2010 10:34 from 127.0.0.1"
	string stub;

	IdecMSession* rec = NULL;

	stcchitemref_t stref(VecIdecVStub::STUBIDECSESSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no session)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Sitzung)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmsession->loadRecByRef(ref, &rec)) {
			if (stcch && !stit) stit = stcch->addStit(stref);
			// IP getStubIdecSesStd --- BEGIN
			if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = Ftm::stamp(rec->start) + " from " + rec->Ip;
			else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = Ftm::stamp(rec->start) + " von " + rec->Ip;
			// IP getStubIdecSesStd --- END
			if (stit) stit->stub = stub;
			delete rec;
		};
	};

	return stub;
};

string StubIdec::getStubTouStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "Orasje building scan 16-10-2014 9:30:00"
	string stub;

	IdecMTour* rec = NULL;

	stcchitemref_t stref(VecIdecVStub::STUBIDECTOUSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no tour)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Tour)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmtour->loadRecByRef(ref, &rec)) {
			if (stcch && !stit) stit = stcch->addStit(stref);
			// IP getStubTouStd --- IBEGIN
			stub = rec->Title + " " + Ftm::stamp(rec->start);
			// IP getStubTouStd --- IEND
			if (stit) stit->stub = stub;
			delete rec;
		};
	};

	return stub;
};

string StubIdec::getStubUsgStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "super"
	string stub;

	stcchitemref_t stref(VecIdecVStub::STUBIDECUSGSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no user group)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keine Benutzergruppe)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmusergroup->loadSrfByRef(ref, stub)) {
			if (stcch) {
				if (!stit) stit = stcch->addStit(stref);
				stit->stub = stub;
			};
		};
	};

	return stub;
};

string StubIdec::getStubUsrStd(
			DbsIdec* dbsidec
			, const ubigint ref
			, const uint ixIdecVLocale
			, const uint ixVNonetype
			, Stcch* stcch
			, stcchitemref_t* strefSub
			, const bool refresh
		) {
	// example: "Franz Kuntz (fkuntz)"
	string stub;

	IdecMUser* rec = NULL;

	stcchitemref_t stref(VecIdecVStub::STUBIDECUSRSTD, ref, ixIdecVLocale);
	Stcchitem* stit = NULL;

	if (stcch) {
		stit = stcch->getStitByStref(stref);
		if (stit && !refresh) {
			if (strefSub) stcch->link(stref, *strefSub);
			return stit->stub;
		};
	};

	if (ixVNonetype == Stub::VecVNonetype::DASH) stub = "-";
	else if (ixVNonetype == Stub::VecVNonetype::SHORT) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(none)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(keiner)";
	} else if (ixVNonetype == Stub::VecVNonetype::FULL) {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) stub = "(no user)";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) stub = "(kein Benutzer)";
	};

	if (ref != 0) {
		if (dbsidec->tblidecmuser->loadRecByRef(ref, &rec)) {
			if (stcch && !stit) stit = stcch->addStit(stref);
			// IP getStubIdecUsrStd --- BEGIN
			stub = rec->sref + " / " + getStubPrsStd(dbsidec, rec->refIdecMPerson, ixIdecVLocale, ixVNonetype, stcch, &stref);
			// IP getStubIdecUsrStd --- END
			if (stit) stit->stub = stub;
			delete rec;
		};
	};

	return stub;
};

/******************************************************************************
 class ContInfIdecAlert
 ******************************************************************************/

ContInfIdecAlert::ContInfIdecAlert(
			const string& TxtCpt
			, const string& TxtMsg1
			, const string& TxtMsg2
			, const string& TxtMsg3
			, const string& TxtMsg4
			, const string& TxtMsg5
			, const string& TxtMsg6
			, const string& TxtMsg7
			, const string& TxtMsg8
			, const string& TxtMsg9
			, const string& TxtMsg10
			, const string& TxtMsg11
			, const string& TxtMsg12
		) : Block() {
	this->TxtCpt = TxtCpt;
	this->TxtMsg1 = TxtMsg1;
	this->TxtMsg2 = TxtMsg2;
	this->TxtMsg3 = TxtMsg3;
	this->TxtMsg4 = TxtMsg4;
	this->TxtMsg5 = TxtMsg5;
	this->TxtMsg6 = TxtMsg6;
	this->TxtMsg7 = TxtMsg7;
	this->TxtMsg8 = TxtMsg8;
	this->TxtMsg9 = TxtMsg9;
	this->TxtMsg10 = TxtMsg10;
	this->TxtMsg11 = TxtMsg11;
	this->TxtMsg12 = TxtMsg12;

	mask = {TXTCPT, TXTMSG1, TXTMSG2, TXTMSG3, TXTMSG4, TXTMSG5, TXTMSG6, TXTMSG7, TXTMSG8, TXTMSG9, TXTMSG10, TXTMSG11, TXTMSG12};
};

bool ContInfIdecAlert::all(
			const set<uint>& items
		) {
	if (!find(items, TXTCPT)) return false;
	if (!find(items, TXTMSG1)) return false;
	if (!find(items, TXTMSG2)) return false;
	if (!find(items, TXTMSG3)) return false;
	if (!find(items, TXTMSG4)) return false;
	if (!find(items, TXTMSG5)) return false;
	if (!find(items, TXTMSG6)) return false;
	if (!find(items, TXTMSG7)) return false;
	if (!find(items, TXTMSG8)) return false;
	if (!find(items, TXTMSG9)) return false;
	if (!find(items, TXTMSG10)) return false;
	if (!find(items, TXTMSG11)) return false;
	if (!find(items, TXTMSG12)) return false;

	return true;
};

void ContInfIdecAlert::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecAlert";

	string itemtag;
	if (shorttags)
		itemtag = "Ci";
	else
		itemtag = "ContitemInfIdecAlert";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxtCpt", TxtCpt);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg1", TxtMsg1);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg2", TxtMsg2);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg3", TxtMsg3);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg4", TxtMsg4);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg5", TxtMsg5);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg6", TxtMsg6);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg7", TxtMsg7);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg8", TxtMsg8);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg9", TxtMsg9);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg10", TxtMsg10);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg11", TxtMsg11);
		writeStringAttr(wr, itemtag, "sref", "TxtMsg12", TxtMsg12);
	xmlTextWriterEndElement(wr);
};

set<uint> ContInfIdecAlert::compare(
			const ContInfIdecAlert* comp
		) {
	set<uint> items;

	if (TxtCpt == comp->TxtCpt) insert(items, TXTCPT);
	if (TxtMsg1 == comp->TxtMsg1) insert(items, TXTMSG1);
	if (TxtMsg2 == comp->TxtMsg2) insert(items, TXTMSG2);
	if (TxtMsg3 == comp->TxtMsg3) insert(items, TXTMSG3);
	if (TxtMsg4 == comp->TxtMsg4) insert(items, TXTMSG4);
	if (TxtMsg5 == comp->TxtMsg5) insert(items, TXTMSG5);
	if (TxtMsg6 == comp->TxtMsg6) insert(items, TXTMSG6);
	if (TxtMsg7 == comp->TxtMsg7) insert(items, TXTMSG7);
	if (TxtMsg8 == comp->TxtMsg8) insert(items, TXTMSG8);
	if (TxtMsg9 == comp->TxtMsg9) insert(items, TXTMSG9);
	if (TxtMsg10 == comp->TxtMsg10) insert(items, TXTMSG10);
	if (TxtMsg11 == comp->TxtMsg11) insert(items, TXTMSG11);
	if (TxtMsg12 == comp->TxtMsg12) insert(items, TXTMSG12);

	return(items);
};

/******************************************************************************
 class DpchIdec
 ******************************************************************************/

DpchIdec::DpchIdec(
			const uint ixIdecVDpch
		) {
	this->ixIdecVDpch = ixIdecVDpch;
};

DpchIdec::~DpchIdec() {
};

/******************************************************************************
 class DpchInvIdec
 ******************************************************************************/

DpchInvIdec::DpchInvIdec(
			const uint ixIdecVDpch
			, const ubigint oref
			, const ubigint jref
			, const set<uint>& mask
		) : DpchIdec(ixIdecVDpch) {
	this->oref = oref;
	this->jref = jref;

	if (find(mask, ALL)) this->mask = {OREF, JREF};
	else this->mask = mask;
};

DpchInvIdec::~DpchInvIdec() {
};

bool DpchInvIdec::all(
			const set<uint>& items
		) {
	if (!find(items, OREF)) return false;
	if (!find(items, JREF)) return false;

	return true;
};

void DpchInvIdec::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchInvIdec");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrOref", "", scrOref)) add(SCROREF);
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
	};
};

void DpchInvIdec::writeXML(
			pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchRetIdec");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(OREF)) writeString(wr, "scrOref", Scr::scramble(mScr, scr, descr, oref));
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DpchRetIdec
 ******************************************************************************/

DpchRetIdec::DpchRetIdec(
			const uint ixIdecVDpch
			, const string& scrOref
			, const string& scrJref
			, const bool success
			, const set<uint>& mask
		) : DpchIdec(ixIdecVDpch) {
	this->scrOref = scrOref;
	this->scrJref = scrJref;
	this->success = success;

	if (find(mask, ALL)) this->mask = {SCROREF, SCRJREF, SUCCESS};
	else this->mask = mask;
};

DpchRetIdec::~DpchRetIdec() {
};

bool DpchRetIdec::all(
			const set<uint>& items
		) {
	if (!find(items, OREF)) return false;
	if (!find(items, JREF)) return false;
	if (!find(items, SUCCESS)) return false;

	return true;
};

void DpchRetIdec::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchRetIdec");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrOref", "", scrOref)) {
			oref = Scr::descramble(mScr, descr, scrOref);
			add(OREF);
		};
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
		if (extractBoolUclc(docctx, basexpath, "success", "", success)) add(SUCCESS);
	};
};

void DpchRetIdec::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchRetIdec");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCROREF)) writeString(wr, "scrOref", scrOref);
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(SUCCESS)) writeBool(wr, "success", success);
	xmlTextWriterEndElement(wr);
};


