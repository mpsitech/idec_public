/**
  * \file VecIdecVDpch.h
  * vector VecIdecVDpch (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVDPCH_H
#define VECIDECVDPCH_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVDpch
	*/
namespace VecIdecVDpch {
	const uint DPCHENGDLGIDECFILEXTRMEDDATA = 1;
	const uint DPCHENGDLGIDECMISNEWDATA = 2;
	const uint DPCHENGDLGIDECNAVLOAINIDATA = 3;
	const uint DPCHENGDLGIDECTOUNEWDATA = 4;
	const uint DPCHENGDLGIDECUTLFUSIONDATA = 5;
	const uint DPCHENGDLGIDECUTLPHIDATA = 6;
	const uint DPCHENGDLGIDECUTLQCDALNDATA = 7;
	const uint DPCHENGDLGIDECUTLQCDNUCDATA = 8;
	const uint DPCHENGDLGIDECUTLSTEREODATA = 9;
	const uint DPCHENGDLGIDECUTLTHETADATA = 10;
	const uint DPCHENGIDECACK = 11;
	const uint DPCHENGIDECAD1CONTROLDATA = 12;
	const uint DPCHENGIDECAD1DATA = 13;
	const uint DPCHENGIDECAD1HEADBARDATA = 14;
	const uint DPCHENGIDECALERT = 15;
	const uint DPCHENGIDECCONFIRM = 16;
	const uint DPCHENGIDECFILDATA = 17;
	const uint DPCHENGIDECFILDETAILDATA = 18;
	const uint DPCHENGIDECFILHEADBARDATA = 19;
	const uint DPCHENGIDECFILLISTDATA = 20;
	const uint DPCHENGIDECFILRECDATA = 21;
	const uint DPCHENGIDECIAQDATA = 22;
	const uint DPCHENGIDECIAQHEADBARDATA = 23;
	const uint DPCHENGIDECIAQLIVEDATA = 24;
	const uint DPCHENGIDECIAQLIVELIVE = 25;
	const uint DPCHENGIDECIAQMECHDATA = 26;
	const uint DPCHENGIDECIAQMECHLIVE = 27;
	const uint DPCHENGIDECIAQQCDSPDATA = 28;
	const uint DPCHENGIDECIAQQCDSPLIVE = 29;
	const uint DPCHENGIDECIAQSCILLDATA = 30;
	const uint DPCHENGIDECMIS1NTOURDATA = 31;
	const uint DPCHENGIDECMISDATA = 32;
	const uint DPCHENGIDECMISDETAILDATA = 33;
	const uint DPCHENGIDECMISHEADBARDATA = 34;
	const uint DPCHENGIDECMISLISTDATA = 35;
	const uint DPCHENGIDECMISRECDATA = 36;
	const uint DPCHENGIDECMISREF1NFILEDATA = 37;
	const uint DPCHENGIDECNAVDATA = 38;
	const uint DPCHENGIDECNAVHEADBARDATA = 39;
	const uint DPCHENGIDECNAVMAINTDATA = 40;
	const uint DPCHENGIDECNAVOPRDATA = 41;
	const uint DPCHENGIDECNAVPREDATA = 42;
	const uint DPCHENGIDECSCFCONNDATA = 43;
	const uint DPCHENGIDECSCFCONNLIVE = 44;
	const uint DPCHENGIDECSCFDATA = 45;
	const uint DPCHENGIDECSCFHEADBARDATA = 46;
	const uint DPCHENGIDECSCFLWIRDATA = 47;
	const uint DPCHENGIDECSCFMECHDATA = 48;
	const uint DPCHENGIDECSCFMECHLIVE = 49;
	const uint DPCHENGIDECSCFOPTICSDATA = 50;
	const uint DPCHENGIDECSCFQCDDATA = 51;
	const uint DPCHENGIDECSCFRECORDDATA = 52;
	const uint DPCHENGIDECSCFSTATUSDATA = 53;
	const uint DPCHENGIDECSCFTRIGGERDATA = 54;
	const uint DPCHENGIDECSUSPEND = 55;
	const uint DPCHENGIDECTOUDATA = 56;
	const uint DPCHENGIDECTOUDETAILDATA = 57;
	const uint DPCHENGIDECTOUHEADBARDATA = 58;
	const uint DPCHENGIDECTOULISTDATA = 59;
	const uint DPCHENGIDECTOURECDATA = 60;
	const uint DPCHENGIDECTOUREF1NFILEDATA = 61;
	const uint DPCHENGIDECUSGAACCESSDATA = 62;
	const uint DPCHENGIDECUSGDATA = 63;
	const uint DPCHENGIDECUSGDETAILDATA = 64;
	const uint DPCHENGIDECUSGHEADBARDATA = 65;
	const uint DPCHENGIDECUSGLISTDATA = 66;
	const uint DPCHENGIDECUSGMNUSERDATA = 67;
	const uint DPCHENGIDECUSGRECDATA = 68;
	const uint DPCHENGIDECUSR1NSESSIONDATA = 69;
	const uint DPCHENGIDECUSRAACCESSDATA = 70;
	const uint DPCHENGIDECUSRDATA = 71;
	const uint DPCHENGIDECUSRDETAILDATA = 72;
	const uint DPCHENGIDECUSRHEADBARDATA = 73;
	const uint DPCHENGIDECUSRLISTDATA = 74;
	const uint DPCHENGIDECUSRMNUSERGROUPDATA = 75;
	const uint DPCHENGIDECUSRRECDATA = 76;
	const uint DPCHENGIDECUTLDATA = 77;
	const uint DPCHENGIDECUTLHEADBARDATA = 78;
	const uint DPCHENGIDECUTLSPITERMDATA = 79;
	const uint DPCHENGIDECUTLSPITERMLIVE = 80;
	const uint DPCHENGSESSIDECDATA = 81;
	const uint DPCHAPPDLGIDECFILEXTRMEDDATA = 82;
	const uint DPCHAPPDLGIDECFILEXTRMEDDO = 83;
	const uint DPCHAPPDLGIDECMISNEWDATA = 84;
	const uint DPCHAPPDLGIDECMISNEWDO = 85;
	const uint DPCHAPPDLGIDECNAVLOAINIDATA = 86;
	const uint DPCHAPPDLGIDECNAVLOAINIDO = 87;
	const uint DPCHAPPDLGIDECTOUNEWDATA = 88;
	const uint DPCHAPPDLGIDECTOUNEWDO = 89;
	const uint DPCHAPPDLGIDECUTLFUSIONDATA = 90;
	const uint DPCHAPPDLGIDECUTLFUSIONDO = 91;
	const uint DPCHAPPDLGIDECUTLPHIDATA = 92;
	const uint DPCHAPPDLGIDECUTLPHIDO = 93;
	const uint DPCHAPPDLGIDECUTLQCDALNDATA = 94;
	const uint DPCHAPPDLGIDECUTLQCDALNDO = 95;
	const uint DPCHAPPDLGIDECUTLQCDNUCDATA = 96;
	const uint DPCHAPPDLGIDECUTLQCDNUCDO = 97;
	const uint DPCHAPPDLGIDECUTLSTEREODATA = 98;
	const uint DPCHAPPDLGIDECUTLSTEREODO = 99;
	const uint DPCHAPPDLGIDECUTLTHETADATA = 100;
	const uint DPCHAPPDLGIDECUTLTHETADO = 101;
	const uint DPCHAPPIDECAD1CONTROLDATA = 102;
	const uint DPCHAPPIDECAD1CONTROLDO = 103;
	const uint DPCHAPPIDECAD1DO = 104;
	const uint DPCHAPPIDECALERT = 105;
	const uint DPCHAPPIDECFILDETAILDATA = 106;
	const uint DPCHAPPIDECFILDETAILDO = 107;
	const uint DPCHAPPIDECFILDO = 108;
	const uint DPCHAPPIDECFILLISTDATA = 109;
	const uint DPCHAPPIDECFILLISTDO = 110;
	const uint DPCHAPPIDECFILRECDO = 111;
	const uint DPCHAPPIDECIAQDO = 112;
	const uint DPCHAPPIDECIAQLIVEDATA = 113;
	const uint DPCHAPPIDECIAQLIVEDO = 114;
	const uint DPCHAPPIDECIAQMECHDATA = 115;
	const uint DPCHAPPIDECIAQMECHDO = 116;
	const uint DPCHAPPIDECIAQQCDSPDATA = 117;
	const uint DPCHAPPIDECIAQQCDSPDO = 118;
	const uint DPCHAPPIDECIAQSCILLDATA = 119;
	const uint DPCHAPPIDECIAQSCILLDO = 120;
	const uint DPCHAPPIDECINIT = 121;
	const uint DPCHAPPIDECMIS1NTOURDATA = 122;
	const uint DPCHAPPIDECMIS1NTOURDO = 123;
	const uint DPCHAPPIDECMISDETAILDATA = 124;
	const uint DPCHAPPIDECMISDETAILDO = 125;
	const uint DPCHAPPIDECMISDO = 126;
	const uint DPCHAPPIDECMISLISTDATA = 127;
	const uint DPCHAPPIDECMISLISTDO = 128;
	const uint DPCHAPPIDECMISRECDO = 129;
	const uint DPCHAPPIDECMISREF1NFILEDATA = 130;
	const uint DPCHAPPIDECMISREF1NFILEDO = 131;
	const uint DPCHAPPIDECNAVDO = 132;
	const uint DPCHAPPIDECNAVMAINTDATA = 133;
	const uint DPCHAPPIDECNAVMAINTDO = 134;
	const uint DPCHAPPIDECNAVOPRDATA = 135;
	const uint DPCHAPPIDECNAVOPRDO = 136;
	const uint DPCHAPPIDECNAVPREDO = 137;
	const uint DPCHAPPIDECRESUME = 138;
	const uint DPCHAPPIDECSCFCONNDATA = 139;
	const uint DPCHAPPIDECSCFCONNDO = 140;
	const uint DPCHAPPIDECSCFDO = 141;
	const uint DPCHAPPIDECSCFLWIRDATA = 142;
	const uint DPCHAPPIDECSCFLWIRDO = 143;
	const uint DPCHAPPIDECSCFMECHDATA = 144;
	const uint DPCHAPPIDECSCFMECHDO = 145;
	const uint DPCHAPPIDECSCFOPTICSDATA = 146;
	const uint DPCHAPPIDECSCFOPTICSDO = 147;
	const uint DPCHAPPIDECSCFQCDDATA = 148;
	const uint DPCHAPPIDECSCFQCDDO = 149;
	const uint DPCHAPPIDECSCFRECORDDATA = 150;
	const uint DPCHAPPIDECSCFRECORDDO = 151;
	const uint DPCHAPPIDECSCFSTATUSDO = 152;
	const uint DPCHAPPIDECSCFTRIGGERDATA = 153;
	const uint DPCHAPPIDECSCFTRIGGERDO = 154;
	const uint DPCHAPPIDECTOUDETAILDATA = 155;
	const uint DPCHAPPIDECTOUDETAILDO = 156;
	const uint DPCHAPPIDECTOUDO = 157;
	const uint DPCHAPPIDECTOULISTDATA = 158;
	const uint DPCHAPPIDECTOULISTDO = 159;
	const uint DPCHAPPIDECTOURECDO = 160;
	const uint DPCHAPPIDECTOUREF1NFILEDATA = 161;
	const uint DPCHAPPIDECTOUREF1NFILEDO = 162;
	const uint DPCHAPPIDECUSGAACCESSDATA = 163;
	const uint DPCHAPPIDECUSGAACCESSDO = 164;
	const uint DPCHAPPIDECUSGDETAILDATA = 165;
	const uint DPCHAPPIDECUSGDETAILDO = 166;
	const uint DPCHAPPIDECUSGDO = 167;
	const uint DPCHAPPIDECUSGLISTDATA = 168;
	const uint DPCHAPPIDECUSGLISTDO = 169;
	const uint DPCHAPPIDECUSGMNUSERDATA = 170;
	const uint DPCHAPPIDECUSGMNUSERDO = 171;
	const uint DPCHAPPIDECUSGRECDO = 172;
	const uint DPCHAPPIDECUSR1NSESSIONDATA = 173;
	const uint DPCHAPPIDECUSR1NSESSIONDO = 174;
	const uint DPCHAPPIDECUSRAACCESSDATA = 175;
	const uint DPCHAPPIDECUSRAACCESSDO = 176;
	const uint DPCHAPPIDECUSRDETAILDATA = 177;
	const uint DPCHAPPIDECUSRDETAILDO = 178;
	const uint DPCHAPPIDECUSRDO = 179;
	const uint DPCHAPPIDECUSRLISTDATA = 180;
	const uint DPCHAPPIDECUSRLISTDO = 181;
	const uint DPCHAPPIDECUSRMNUSERGROUPDATA = 182;
	const uint DPCHAPPIDECUSRMNUSERGROUPDO = 183;
	const uint DPCHAPPIDECUSRRECDO = 184;
	const uint DPCHAPPIDECUTLDO = 185;
	const uint DPCHAPPIDECUTLSPITERMDATA = 186;
	const uint DPCHAPPIDECUTLSPITERMDO = 187;
	const uint DPCHAPPROOTIDECLOGIN = 188;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

