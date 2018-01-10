/**
  * \file VecIdecVDpch.h
  * vector VecIdecVDpch (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "VecIdecVDpch.h"

/******************************************************************************
 namespace VecIdecVDpch
 ******************************************************************************/

uint VecIdecVDpch::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s.compare("dpchengdlgidecfilextrmeddata") == 0) return DPCHENGDLGIDECFILEXTRMEDDATA;
	else if (s.compare("dpchengdlgidecmisnewdata") == 0) return DPCHENGDLGIDECMISNEWDATA;
	else if (s.compare("dpchengdlgidecnavloainidata") == 0) return DPCHENGDLGIDECNAVLOAINIDATA;
	else if (s.compare("dpchengdlgidectounewdata") == 0) return DPCHENGDLGIDECTOUNEWDATA;
	else if (s.compare("dpchengdlgidecutlfusiondata") == 0) return DPCHENGDLGIDECUTLFUSIONDATA;
	else if (s.compare("dpchengdlgidecutlphidata") == 0) return DPCHENGDLGIDECUTLPHIDATA;
	else if (s.compare("dpchengdlgidecutlqcdalndata") == 0) return DPCHENGDLGIDECUTLQCDALNDATA;
	else if (s.compare("dpchengdlgidecutlqcdnucdata") == 0) return DPCHENGDLGIDECUTLQCDNUCDATA;
	else if (s.compare("dpchengdlgidecutlstereodata") == 0) return DPCHENGDLGIDECUTLSTEREODATA;
	else if (s.compare("dpchengdlgidecutlthetadata") == 0) return DPCHENGDLGIDECUTLTHETADATA;
	else if (s.compare("dpchengidecack") == 0) return DPCHENGIDECACK;
	else if (s.compare("dpchengidecad1controldata") == 0) return DPCHENGIDECAD1CONTROLDATA;
	else if (s.compare("dpchengidecad1data") == 0) return DPCHENGIDECAD1DATA;
	else if (s.compare("dpchengidecad1headbardata") == 0) return DPCHENGIDECAD1HEADBARDATA;
	else if (s.compare("dpchengidecalert") == 0) return DPCHENGIDECALERT;
	else if (s.compare("dpchengidecconfirm") == 0) return DPCHENGIDECCONFIRM;
	else if (s.compare("dpchengidecfildata") == 0) return DPCHENGIDECFILDATA;
	else if (s.compare("dpchengidecfildetaildata") == 0) return DPCHENGIDECFILDETAILDATA;
	else if (s.compare("dpchengidecfilheadbardata") == 0) return DPCHENGIDECFILHEADBARDATA;
	else if (s.compare("dpchengidecfillistdata") == 0) return DPCHENGIDECFILLISTDATA;
	else if (s.compare("dpchengidecfilrecdata") == 0) return DPCHENGIDECFILRECDATA;
	else if (s.compare("dpchengideciaqdata") == 0) return DPCHENGIDECIAQDATA;
	else if (s.compare("dpchengideciaqheadbardata") == 0) return DPCHENGIDECIAQHEADBARDATA;
	else if (s.compare("dpchengideciaqlivedata") == 0) return DPCHENGIDECIAQLIVEDATA;
	else if (s.compare("dpchengideciaqlivelive") == 0) return DPCHENGIDECIAQLIVELIVE;
	else if (s.compare("dpchengideciaqmechdata") == 0) return DPCHENGIDECIAQMECHDATA;
	else if (s.compare("dpchengideciaqmechlive") == 0) return DPCHENGIDECIAQMECHLIVE;
	else if (s.compare("dpchengideciaqqcdspdata") == 0) return DPCHENGIDECIAQQCDSPDATA;
	else if (s.compare("dpchengideciaqqcdsplive") == 0) return DPCHENGIDECIAQQCDSPLIVE;
	else if (s.compare("dpchengideciaqscilldata") == 0) return DPCHENGIDECIAQSCILLDATA;
	else if (s.compare("dpchengidecmis1ntourdata") == 0) return DPCHENGIDECMIS1NTOURDATA;
	else if (s.compare("dpchengidecmisdata") == 0) return DPCHENGIDECMISDATA;
	else if (s.compare("dpchengidecmisdetaildata") == 0) return DPCHENGIDECMISDETAILDATA;
	else if (s.compare("dpchengidecmisheadbardata") == 0) return DPCHENGIDECMISHEADBARDATA;
	else if (s.compare("dpchengidecmislistdata") == 0) return DPCHENGIDECMISLISTDATA;
	else if (s.compare("dpchengidecmisrecdata") == 0) return DPCHENGIDECMISRECDATA;
	else if (s.compare("dpchengidecmisref1nfiledata") == 0) return DPCHENGIDECMISREF1NFILEDATA;
	else if (s.compare("dpchengidecnavdata") == 0) return DPCHENGIDECNAVDATA;
	else if (s.compare("dpchengidecnavheadbardata") == 0) return DPCHENGIDECNAVHEADBARDATA;
	else if (s.compare("dpchengidecnavmaintdata") == 0) return DPCHENGIDECNAVMAINTDATA;
	else if (s.compare("dpchengidecnavoprdata") == 0) return DPCHENGIDECNAVOPRDATA;
	else if (s.compare("dpchengidecnavpredata") == 0) return DPCHENGIDECNAVPREDATA;
	else if (s.compare("dpchengidecscfconndata") == 0) return DPCHENGIDECSCFCONNDATA;
	else if (s.compare("dpchengidecscfconnlive") == 0) return DPCHENGIDECSCFCONNLIVE;
	else if (s.compare("dpchengidecscfdata") == 0) return DPCHENGIDECSCFDATA;
	else if (s.compare("dpchengidecscfheadbardata") == 0) return DPCHENGIDECSCFHEADBARDATA;
	else if (s.compare("dpchengidecscflwirdata") == 0) return DPCHENGIDECSCFLWIRDATA;
	else if (s.compare("dpchengidecscfmechdata") == 0) return DPCHENGIDECSCFMECHDATA;
	else if (s.compare("dpchengidecscfmechlive") == 0) return DPCHENGIDECSCFMECHLIVE;
	else if (s.compare("dpchengidecscfopticsdata") == 0) return DPCHENGIDECSCFOPTICSDATA;
	else if (s.compare("dpchengidecscfqcddata") == 0) return DPCHENGIDECSCFQCDDATA;
	else if (s.compare("dpchengidecscfrecorddata") == 0) return DPCHENGIDECSCFRECORDDATA;
	else if (s.compare("dpchengidecscfstatusdata") == 0) return DPCHENGIDECSCFSTATUSDATA;
	else if (s.compare("dpchengidecscftriggerdata") == 0) return DPCHENGIDECSCFTRIGGERDATA;
	else if (s.compare("dpchengidecsuspend") == 0) return DPCHENGIDECSUSPEND;
	else if (s.compare("dpchengidectoudata") == 0) return DPCHENGIDECTOUDATA;
	else if (s.compare("dpchengidectoudetaildata") == 0) return DPCHENGIDECTOUDETAILDATA;
	else if (s.compare("dpchengidectouheadbardata") == 0) return DPCHENGIDECTOUHEADBARDATA;
	else if (s.compare("dpchengidectoulistdata") == 0) return DPCHENGIDECTOULISTDATA;
	else if (s.compare("dpchengidectourecdata") == 0) return DPCHENGIDECTOURECDATA;
	else if (s.compare("dpchengidectouref1nfiledata") == 0) return DPCHENGIDECTOUREF1NFILEDATA;
	else if (s.compare("dpchengidecusgaaccessdata") == 0) return DPCHENGIDECUSGAACCESSDATA;
	else if (s.compare("dpchengidecusgdata") == 0) return DPCHENGIDECUSGDATA;
	else if (s.compare("dpchengidecusgdetaildata") == 0) return DPCHENGIDECUSGDETAILDATA;
	else if (s.compare("dpchengidecusgheadbardata") == 0) return DPCHENGIDECUSGHEADBARDATA;
	else if (s.compare("dpchengidecusglistdata") == 0) return DPCHENGIDECUSGLISTDATA;
	else if (s.compare("dpchengidecusgmnuserdata") == 0) return DPCHENGIDECUSGMNUSERDATA;
	else if (s.compare("dpchengidecusgrecdata") == 0) return DPCHENGIDECUSGRECDATA;
	else if (s.compare("dpchengidecusr1nsessiondata") == 0) return DPCHENGIDECUSR1NSESSIONDATA;
	else if (s.compare("dpchengidecusraaccessdata") == 0) return DPCHENGIDECUSRAACCESSDATA;
	else if (s.compare("dpchengidecusrdata") == 0) return DPCHENGIDECUSRDATA;
	else if (s.compare("dpchengidecusrdetaildata") == 0) return DPCHENGIDECUSRDETAILDATA;
	else if (s.compare("dpchengidecusrheadbardata") == 0) return DPCHENGIDECUSRHEADBARDATA;
	else if (s.compare("dpchengidecusrlistdata") == 0) return DPCHENGIDECUSRLISTDATA;
	else if (s.compare("dpchengidecusrmnusergroupdata") == 0) return DPCHENGIDECUSRMNUSERGROUPDATA;
	else if (s.compare("dpchengidecusrrecdata") == 0) return DPCHENGIDECUSRRECDATA;
	else if (s.compare("dpchengidecutldata") == 0) return DPCHENGIDECUTLDATA;
	else if (s.compare("dpchengidecutlheadbardata") == 0) return DPCHENGIDECUTLHEADBARDATA;
	else if (s.compare("dpchengidecutlspitermdata") == 0) return DPCHENGIDECUTLSPITERMDATA;
	else if (s.compare("dpchengidecutlspitermlive") == 0) return DPCHENGIDECUTLSPITERMLIVE;
	else if (s.compare("dpchengsessidecdata") == 0) return DPCHENGSESSIDECDATA;
	else if (s.compare("dpchappdlgidecfilextrmeddata") == 0) return DPCHAPPDLGIDECFILEXTRMEDDATA;
	else if (s.compare("dpchappdlgidecfilextrmeddo") == 0) return DPCHAPPDLGIDECFILEXTRMEDDO;
	else if (s.compare("dpchappdlgidecmisnewdata") == 0) return DPCHAPPDLGIDECMISNEWDATA;
	else if (s.compare("dpchappdlgidecmisnewdo") == 0) return DPCHAPPDLGIDECMISNEWDO;
	else if (s.compare("dpchappdlgidecnavloainidata") == 0) return DPCHAPPDLGIDECNAVLOAINIDATA;
	else if (s.compare("dpchappdlgidecnavloainido") == 0) return DPCHAPPDLGIDECNAVLOAINIDO;
	else if (s.compare("dpchappdlgidectounewdata") == 0) return DPCHAPPDLGIDECTOUNEWDATA;
	else if (s.compare("dpchappdlgidectounewdo") == 0) return DPCHAPPDLGIDECTOUNEWDO;
	else if (s.compare("dpchappdlgidecutlfusiondata") == 0) return DPCHAPPDLGIDECUTLFUSIONDATA;
	else if (s.compare("dpchappdlgidecutlfusiondo") == 0) return DPCHAPPDLGIDECUTLFUSIONDO;
	else if (s.compare("dpchappdlgidecutlphidata") == 0) return DPCHAPPDLGIDECUTLPHIDATA;
	else if (s.compare("dpchappdlgidecutlphido") == 0) return DPCHAPPDLGIDECUTLPHIDO;
	else if (s.compare("dpchappdlgidecutlqcdalndata") == 0) return DPCHAPPDLGIDECUTLQCDALNDATA;
	else if (s.compare("dpchappdlgidecutlqcdalndo") == 0) return DPCHAPPDLGIDECUTLQCDALNDO;
	else if (s.compare("dpchappdlgidecutlqcdnucdata") == 0) return DPCHAPPDLGIDECUTLQCDNUCDATA;
	else if (s.compare("dpchappdlgidecutlqcdnucdo") == 0) return DPCHAPPDLGIDECUTLQCDNUCDO;
	else if (s.compare("dpchappdlgidecutlstereodata") == 0) return DPCHAPPDLGIDECUTLSTEREODATA;
	else if (s.compare("dpchappdlgidecutlstereodo") == 0) return DPCHAPPDLGIDECUTLSTEREODO;
	else if (s.compare("dpchappdlgidecutlthetadata") == 0) return DPCHAPPDLGIDECUTLTHETADATA;
	else if (s.compare("dpchappdlgidecutlthetado") == 0) return DPCHAPPDLGIDECUTLTHETADO;
	else if (s.compare("dpchappidecad1controldata") == 0) return DPCHAPPIDECAD1CONTROLDATA;
	else if (s.compare("dpchappidecad1controldo") == 0) return DPCHAPPIDECAD1CONTROLDO;
	else if (s.compare("dpchappidecad1do") == 0) return DPCHAPPIDECAD1DO;
	else if (s.compare("dpchappidecalert") == 0) return DPCHAPPIDECALERT;
	else if (s.compare("dpchappidecfildetaildata") == 0) return DPCHAPPIDECFILDETAILDATA;
	else if (s.compare("dpchappidecfildetaildo") == 0) return DPCHAPPIDECFILDETAILDO;
	else if (s.compare("dpchappidecfildo") == 0) return DPCHAPPIDECFILDO;
	else if (s.compare("dpchappidecfillistdata") == 0) return DPCHAPPIDECFILLISTDATA;
	else if (s.compare("dpchappidecfillistdo") == 0) return DPCHAPPIDECFILLISTDO;
	else if (s.compare("dpchappidecfilrecdo") == 0) return DPCHAPPIDECFILRECDO;
	else if (s.compare("dpchappideciaqdo") == 0) return DPCHAPPIDECIAQDO;
	else if (s.compare("dpchappideciaqlivedata") == 0) return DPCHAPPIDECIAQLIVEDATA;
	else if (s.compare("dpchappideciaqlivedo") == 0) return DPCHAPPIDECIAQLIVEDO;
	else if (s.compare("dpchappideciaqmechdata") == 0) return DPCHAPPIDECIAQMECHDATA;
	else if (s.compare("dpchappideciaqmechdo") == 0) return DPCHAPPIDECIAQMECHDO;
	else if (s.compare("dpchappideciaqqcdspdata") == 0) return DPCHAPPIDECIAQQCDSPDATA;
	else if (s.compare("dpchappideciaqqcdspdo") == 0) return DPCHAPPIDECIAQQCDSPDO;
	else if (s.compare("dpchappideciaqscilldata") == 0) return DPCHAPPIDECIAQSCILLDATA;
	else if (s.compare("dpchappideciaqscilldo") == 0) return DPCHAPPIDECIAQSCILLDO;
	else if (s.compare("dpchappidecinit") == 0) return DPCHAPPIDECINIT;
	else if (s.compare("dpchappidecmis1ntourdata") == 0) return DPCHAPPIDECMIS1NTOURDATA;
	else if (s.compare("dpchappidecmis1ntourdo") == 0) return DPCHAPPIDECMIS1NTOURDO;
	else if (s.compare("dpchappidecmisdetaildata") == 0) return DPCHAPPIDECMISDETAILDATA;
	else if (s.compare("dpchappidecmisdetaildo") == 0) return DPCHAPPIDECMISDETAILDO;
	else if (s.compare("dpchappidecmisdo") == 0) return DPCHAPPIDECMISDO;
	else if (s.compare("dpchappidecmislistdata") == 0) return DPCHAPPIDECMISLISTDATA;
	else if (s.compare("dpchappidecmislistdo") == 0) return DPCHAPPIDECMISLISTDO;
	else if (s.compare("dpchappidecmisrecdo") == 0) return DPCHAPPIDECMISRECDO;
	else if (s.compare("dpchappidecmisref1nfiledata") == 0) return DPCHAPPIDECMISREF1NFILEDATA;
	else if (s.compare("dpchappidecmisref1nfiledo") == 0) return DPCHAPPIDECMISREF1NFILEDO;
	else if (s.compare("dpchappidecnavdo") == 0) return DPCHAPPIDECNAVDO;
	else if (s.compare("dpchappidecnavmaintdata") == 0) return DPCHAPPIDECNAVMAINTDATA;
	else if (s.compare("dpchappidecnavmaintdo") == 0) return DPCHAPPIDECNAVMAINTDO;
	else if (s.compare("dpchappidecnavoprdata") == 0) return DPCHAPPIDECNAVOPRDATA;
	else if (s.compare("dpchappidecnavoprdo") == 0) return DPCHAPPIDECNAVOPRDO;
	else if (s.compare("dpchappidecnavpredo") == 0) return DPCHAPPIDECNAVPREDO;
	else if (s.compare("dpchappidecresume") == 0) return DPCHAPPIDECRESUME;
	else if (s.compare("dpchappidecscfconndata") == 0) return DPCHAPPIDECSCFCONNDATA;
	else if (s.compare("dpchappidecscfconndo") == 0) return DPCHAPPIDECSCFCONNDO;
	else if (s.compare("dpchappidecscfdo") == 0) return DPCHAPPIDECSCFDO;
	else if (s.compare("dpchappidecscflwirdata") == 0) return DPCHAPPIDECSCFLWIRDATA;
	else if (s.compare("dpchappidecscflwirdo") == 0) return DPCHAPPIDECSCFLWIRDO;
	else if (s.compare("dpchappidecscfmechdata") == 0) return DPCHAPPIDECSCFMECHDATA;
	else if (s.compare("dpchappidecscfmechdo") == 0) return DPCHAPPIDECSCFMECHDO;
	else if (s.compare("dpchappidecscfopticsdata") == 0) return DPCHAPPIDECSCFOPTICSDATA;
	else if (s.compare("dpchappidecscfopticsdo") == 0) return DPCHAPPIDECSCFOPTICSDO;
	else if (s.compare("dpchappidecscfqcddata") == 0) return DPCHAPPIDECSCFQCDDATA;
	else if (s.compare("dpchappidecscfqcddo") == 0) return DPCHAPPIDECSCFQCDDO;
	else if (s.compare("dpchappidecscfrecorddata") == 0) return DPCHAPPIDECSCFRECORDDATA;
	else if (s.compare("dpchappidecscfrecorddo") == 0) return DPCHAPPIDECSCFRECORDDO;
	else if (s.compare("dpchappidecscfstatusdo") == 0) return DPCHAPPIDECSCFSTATUSDO;
	else if (s.compare("dpchappidecscftriggerdata") == 0) return DPCHAPPIDECSCFTRIGGERDATA;
	else if (s.compare("dpchappidecscftriggerdo") == 0) return DPCHAPPIDECSCFTRIGGERDO;
	else if (s.compare("dpchappidectoudetaildata") == 0) return DPCHAPPIDECTOUDETAILDATA;
	else if (s.compare("dpchappidectoudetaildo") == 0) return DPCHAPPIDECTOUDETAILDO;
	else if (s.compare("dpchappidectoudo") == 0) return DPCHAPPIDECTOUDO;
	else if (s.compare("dpchappidectoulistdata") == 0) return DPCHAPPIDECTOULISTDATA;
	else if (s.compare("dpchappidectoulistdo") == 0) return DPCHAPPIDECTOULISTDO;
	else if (s.compare("dpchappidectourecdo") == 0) return DPCHAPPIDECTOURECDO;
	else if (s.compare("dpchappidectouref1nfiledata") == 0) return DPCHAPPIDECTOUREF1NFILEDATA;
	else if (s.compare("dpchappidectouref1nfiledo") == 0) return DPCHAPPIDECTOUREF1NFILEDO;
	else if (s.compare("dpchappidecusgaaccessdata") == 0) return DPCHAPPIDECUSGAACCESSDATA;
	else if (s.compare("dpchappidecusgaaccessdo") == 0) return DPCHAPPIDECUSGAACCESSDO;
	else if (s.compare("dpchappidecusgdetaildata") == 0) return DPCHAPPIDECUSGDETAILDATA;
	else if (s.compare("dpchappidecusgdetaildo") == 0) return DPCHAPPIDECUSGDETAILDO;
	else if (s.compare("dpchappidecusgdo") == 0) return DPCHAPPIDECUSGDO;
	else if (s.compare("dpchappidecusglistdata") == 0) return DPCHAPPIDECUSGLISTDATA;
	else if (s.compare("dpchappidecusglistdo") == 0) return DPCHAPPIDECUSGLISTDO;
	else if (s.compare("dpchappidecusgmnuserdata") == 0) return DPCHAPPIDECUSGMNUSERDATA;
	else if (s.compare("dpchappidecusgmnuserdo") == 0) return DPCHAPPIDECUSGMNUSERDO;
	else if (s.compare("dpchappidecusgrecdo") == 0) return DPCHAPPIDECUSGRECDO;
	else if (s.compare("dpchappidecusr1nsessiondata") == 0) return DPCHAPPIDECUSR1NSESSIONDATA;
	else if (s.compare("dpchappidecusr1nsessiondo") == 0) return DPCHAPPIDECUSR1NSESSIONDO;
	else if (s.compare("dpchappidecusraaccessdata") == 0) return DPCHAPPIDECUSRAACCESSDATA;
	else if (s.compare("dpchappidecusraaccessdo") == 0) return DPCHAPPIDECUSRAACCESSDO;
	else if (s.compare("dpchappidecusrdetaildata") == 0) return DPCHAPPIDECUSRDETAILDATA;
	else if (s.compare("dpchappidecusrdetaildo") == 0) return DPCHAPPIDECUSRDETAILDO;
	else if (s.compare("dpchappidecusrdo") == 0) return DPCHAPPIDECUSRDO;
	else if (s.compare("dpchappidecusrlistdata") == 0) return DPCHAPPIDECUSRLISTDATA;
	else if (s.compare("dpchappidecusrlistdo") == 0) return DPCHAPPIDECUSRLISTDO;
	else if (s.compare("dpchappidecusrmnusergroupdata") == 0) return DPCHAPPIDECUSRMNUSERGROUPDATA;
	else if (s.compare("dpchappidecusrmnusergroupdo") == 0) return DPCHAPPIDECUSRMNUSERGROUPDO;
	else if (s.compare("dpchappidecusrrecdo") == 0) return DPCHAPPIDECUSRRECDO;
	else if (s.compare("dpchappidecutldo") == 0) return DPCHAPPIDECUTLDO;
	else if (s.compare("dpchappidecutlspitermdata") == 0) return DPCHAPPIDECUTLSPITERMDATA;
	else if (s.compare("dpchappidecutlspitermdo") == 0) return DPCHAPPIDECUTLSPITERMDO;
	else if (s.compare("dpchapprootideclogin") == 0) return DPCHAPPROOTIDECLOGIN;

	return(0);
};

string VecIdecVDpch::getSref(
			const uint ix
		) {
	if (ix == DPCHENGDLGIDECFILEXTRMEDDATA) return("DpchEngDlgIdecFilExtrmedData");
	else if (ix == DPCHENGDLGIDECMISNEWDATA) return("DpchEngDlgIdecMisNewData");
	else if (ix == DPCHENGDLGIDECNAVLOAINIDATA) return("DpchEngDlgIdecNavLoainiData");
	else if (ix == DPCHENGDLGIDECTOUNEWDATA) return("DpchEngDlgIdecTouNewData");
	else if (ix == DPCHENGDLGIDECUTLFUSIONDATA) return("DpchEngDlgIdecUtlFusionData");
	else if (ix == DPCHENGDLGIDECUTLPHIDATA) return("DpchEngDlgIdecUtlPhiData");
	else if (ix == DPCHENGDLGIDECUTLQCDALNDATA) return("DpchEngDlgIdecUtlQcdalnData");
	else if (ix == DPCHENGDLGIDECUTLQCDNUCDATA) return("DpchEngDlgIdecUtlQcdnucData");
	else if (ix == DPCHENGDLGIDECUTLSTEREODATA) return("DpchEngDlgIdecUtlStereoData");
	else if (ix == DPCHENGDLGIDECUTLTHETADATA) return("DpchEngDlgIdecUtlThetaData");
	else if (ix == DPCHENGIDECACK) return("DpchEngIdecAck");
	else if (ix == DPCHENGIDECAD1CONTROLDATA) return("DpchEngIdecAd1ControlData");
	else if (ix == DPCHENGIDECAD1DATA) return("DpchEngIdecAd1Data");
	else if (ix == DPCHENGIDECAD1HEADBARDATA) return("DpchEngIdecAd1HeadbarData");
	else if (ix == DPCHENGIDECALERT) return("DpchEngIdecAlert");
	else if (ix == DPCHENGIDECCONFIRM) return("DpchEngIdecConfirm");
	else if (ix == DPCHENGIDECFILDATA) return("DpchEngIdecFilData");
	else if (ix == DPCHENGIDECFILDETAILDATA) return("DpchEngIdecFilDetailData");
	else if (ix == DPCHENGIDECFILHEADBARDATA) return("DpchEngIdecFilHeadbarData");
	else if (ix == DPCHENGIDECFILLISTDATA) return("DpchEngIdecFilListData");
	else if (ix == DPCHENGIDECFILRECDATA) return("DpchEngIdecFilRecData");
	else if (ix == DPCHENGIDECIAQDATA) return("DpchEngIdecIaqData");
	else if (ix == DPCHENGIDECIAQHEADBARDATA) return("DpchEngIdecIaqHeadbarData");
	else if (ix == DPCHENGIDECIAQLIVEDATA) return("DpchEngIdecIaqLiveData");
	else if (ix == DPCHENGIDECIAQLIVELIVE) return("DpchEngIdecIaqLiveLive");
	else if (ix == DPCHENGIDECIAQMECHDATA) return("DpchEngIdecIaqMechData");
	else if (ix == DPCHENGIDECIAQMECHLIVE) return("DpchEngIdecIaqMechLive");
	else if (ix == DPCHENGIDECIAQQCDSPDATA) return("DpchEngIdecIaqQcdspData");
	else if (ix == DPCHENGIDECIAQQCDSPLIVE) return("DpchEngIdecIaqQcdspLive");
	else if (ix == DPCHENGIDECIAQSCILLDATA) return("DpchEngIdecIaqScillData");
	else if (ix == DPCHENGIDECMIS1NTOURDATA) return("DpchEngIdecMis1NTourData");
	else if (ix == DPCHENGIDECMISDATA) return("DpchEngIdecMisData");
	else if (ix == DPCHENGIDECMISDETAILDATA) return("DpchEngIdecMisDetailData");
	else if (ix == DPCHENGIDECMISHEADBARDATA) return("DpchEngIdecMisHeadbarData");
	else if (ix == DPCHENGIDECMISLISTDATA) return("DpchEngIdecMisListData");
	else if (ix == DPCHENGIDECMISRECDATA) return("DpchEngIdecMisRecData");
	else if (ix == DPCHENGIDECMISREF1NFILEDATA) return("DpchEngIdecMisRef1NFileData");
	else if (ix == DPCHENGIDECNAVDATA) return("DpchEngIdecNavData");
	else if (ix == DPCHENGIDECNAVHEADBARDATA) return("DpchEngIdecNavHeadbarData");
	else if (ix == DPCHENGIDECNAVMAINTDATA) return("DpchEngIdecNavMaintData");
	else if (ix == DPCHENGIDECNAVOPRDATA) return("DpchEngIdecNavOprData");
	else if (ix == DPCHENGIDECNAVPREDATA) return("DpchEngIdecNavPreData");
	else if (ix == DPCHENGIDECSCFCONNDATA) return("DpchEngIdecScfConnData");
	else if (ix == DPCHENGIDECSCFCONNLIVE) return("DpchEngIdecScfConnLive");
	else if (ix == DPCHENGIDECSCFDATA) return("DpchEngIdecScfData");
	else if (ix == DPCHENGIDECSCFHEADBARDATA) return("DpchEngIdecScfHeadbarData");
	else if (ix == DPCHENGIDECSCFLWIRDATA) return("DpchEngIdecScfLwirData");
	else if (ix == DPCHENGIDECSCFMECHDATA) return("DpchEngIdecScfMechData");
	else if (ix == DPCHENGIDECSCFMECHLIVE) return("DpchEngIdecScfMechLive");
	else if (ix == DPCHENGIDECSCFOPTICSDATA) return("DpchEngIdecScfOpticsData");
	else if (ix == DPCHENGIDECSCFQCDDATA) return("DpchEngIdecScfQcdData");
	else if (ix == DPCHENGIDECSCFRECORDDATA) return("DpchEngIdecScfRecordData");
	else if (ix == DPCHENGIDECSCFSTATUSDATA) return("DpchEngIdecScfStatusData");
	else if (ix == DPCHENGIDECSCFTRIGGERDATA) return("DpchEngIdecScfTriggerData");
	else if (ix == DPCHENGIDECSUSPEND) return("DpchEngIdecSuspend");
	else if (ix == DPCHENGIDECTOUDATA) return("DpchEngIdecTouData");
	else if (ix == DPCHENGIDECTOUDETAILDATA) return("DpchEngIdecTouDetailData");
	else if (ix == DPCHENGIDECTOUHEADBARDATA) return("DpchEngIdecTouHeadbarData");
	else if (ix == DPCHENGIDECTOULISTDATA) return("DpchEngIdecTouListData");
	else if (ix == DPCHENGIDECTOURECDATA) return("DpchEngIdecTouRecData");
	else if (ix == DPCHENGIDECTOUREF1NFILEDATA) return("DpchEngIdecTouRef1NFileData");
	else if (ix == DPCHENGIDECUSGAACCESSDATA) return("DpchEngIdecUsgAAccessData");
	else if (ix == DPCHENGIDECUSGDATA) return("DpchEngIdecUsgData");
	else if (ix == DPCHENGIDECUSGDETAILDATA) return("DpchEngIdecUsgDetailData");
	else if (ix == DPCHENGIDECUSGHEADBARDATA) return("DpchEngIdecUsgHeadbarData");
	else if (ix == DPCHENGIDECUSGLISTDATA) return("DpchEngIdecUsgListData");
	else if (ix == DPCHENGIDECUSGMNUSERDATA) return("DpchEngIdecUsgMNUserData");
	else if (ix == DPCHENGIDECUSGRECDATA) return("DpchEngIdecUsgRecData");
	else if (ix == DPCHENGIDECUSR1NSESSIONDATA) return("DpchEngIdecUsr1NSessionData");
	else if (ix == DPCHENGIDECUSRAACCESSDATA) return("DpchEngIdecUsrAAccessData");
	else if (ix == DPCHENGIDECUSRDATA) return("DpchEngIdecUsrData");
	else if (ix == DPCHENGIDECUSRDETAILDATA) return("DpchEngIdecUsrDetailData");
	else if (ix == DPCHENGIDECUSRHEADBARDATA) return("DpchEngIdecUsrHeadbarData");
	else if (ix == DPCHENGIDECUSRLISTDATA) return("DpchEngIdecUsrListData");
	else if (ix == DPCHENGIDECUSRMNUSERGROUPDATA) return("DpchEngIdecUsrMNUsergroupData");
	else if (ix == DPCHENGIDECUSRRECDATA) return("DpchEngIdecUsrRecData");
	else if (ix == DPCHENGIDECUTLDATA) return("DpchEngIdecUtlData");
	else if (ix == DPCHENGIDECUTLHEADBARDATA) return("DpchEngIdecUtlHeadbarData");
	else if (ix == DPCHENGIDECUTLSPITERMDATA) return("DpchEngIdecUtlSpitermData");
	else if (ix == DPCHENGIDECUTLSPITERMLIVE) return("DpchEngIdecUtlSpitermLive");
	else if (ix == DPCHENGSESSIDECDATA) return("DpchEngSessIdecData");
	else if (ix == DPCHAPPDLGIDECFILEXTRMEDDATA) return("DpchAppDlgIdecFilExtrmedData");
	else if (ix == DPCHAPPDLGIDECFILEXTRMEDDO) return("DpchAppDlgIdecFilExtrmedDo");
	else if (ix == DPCHAPPDLGIDECMISNEWDATA) return("DpchAppDlgIdecMisNewData");
	else if (ix == DPCHAPPDLGIDECMISNEWDO) return("DpchAppDlgIdecMisNewDo");
	else if (ix == DPCHAPPDLGIDECNAVLOAINIDATA) return("DpchAppDlgIdecNavLoainiData");
	else if (ix == DPCHAPPDLGIDECNAVLOAINIDO) return("DpchAppDlgIdecNavLoainiDo");
	else if (ix == DPCHAPPDLGIDECTOUNEWDATA) return("DpchAppDlgIdecTouNewData");
	else if (ix == DPCHAPPDLGIDECTOUNEWDO) return("DpchAppDlgIdecTouNewDo");
	else if (ix == DPCHAPPDLGIDECUTLFUSIONDATA) return("DpchAppDlgIdecUtlFusionData");
	else if (ix == DPCHAPPDLGIDECUTLFUSIONDO) return("DpchAppDlgIdecUtlFusionDo");
	else if (ix == DPCHAPPDLGIDECUTLPHIDATA) return("DpchAppDlgIdecUtlPhiData");
	else if (ix == DPCHAPPDLGIDECUTLPHIDO) return("DpchAppDlgIdecUtlPhiDo");
	else if (ix == DPCHAPPDLGIDECUTLQCDALNDATA) return("DpchAppDlgIdecUtlQcdalnData");
	else if (ix == DPCHAPPDLGIDECUTLQCDALNDO) return("DpchAppDlgIdecUtlQcdalnDo");
	else if (ix == DPCHAPPDLGIDECUTLQCDNUCDATA) return("DpchAppDlgIdecUtlQcdnucData");
	else if (ix == DPCHAPPDLGIDECUTLQCDNUCDO) return("DpchAppDlgIdecUtlQcdnucDo");
	else if (ix == DPCHAPPDLGIDECUTLSTEREODATA) return("DpchAppDlgIdecUtlStereoData");
	else if (ix == DPCHAPPDLGIDECUTLSTEREODO) return("DpchAppDlgIdecUtlStereoDo");
	else if (ix == DPCHAPPDLGIDECUTLTHETADATA) return("DpchAppDlgIdecUtlThetaData");
	else if (ix == DPCHAPPDLGIDECUTLTHETADO) return("DpchAppDlgIdecUtlThetaDo");
	else if (ix == DPCHAPPIDECAD1CONTROLDATA) return("DpchAppIdecAd1ControlData");
	else if (ix == DPCHAPPIDECAD1CONTROLDO) return("DpchAppIdecAd1ControlDo");
	else if (ix == DPCHAPPIDECAD1DO) return("DpchAppIdecAd1Do");
	else if (ix == DPCHAPPIDECALERT) return("DpchAppIdecAlert");
	else if (ix == DPCHAPPIDECFILDETAILDATA) return("DpchAppIdecFilDetailData");
	else if (ix == DPCHAPPIDECFILDETAILDO) return("DpchAppIdecFilDetailDo");
	else if (ix == DPCHAPPIDECFILDO) return("DpchAppIdecFilDo");
	else if (ix == DPCHAPPIDECFILLISTDATA) return("DpchAppIdecFilListData");
	else if (ix == DPCHAPPIDECFILLISTDO) return("DpchAppIdecFilListDo");
	else if (ix == DPCHAPPIDECFILRECDO) return("DpchAppIdecFilRecDo");
	else if (ix == DPCHAPPIDECIAQDO) return("DpchAppIdecIaqDo");
	else if (ix == DPCHAPPIDECIAQLIVEDATA) return("DpchAppIdecIaqLiveData");
	else if (ix == DPCHAPPIDECIAQLIVEDO) return("DpchAppIdecIaqLiveDo");
	else if (ix == DPCHAPPIDECIAQMECHDATA) return("DpchAppIdecIaqMechData");
	else if (ix == DPCHAPPIDECIAQMECHDO) return("DpchAppIdecIaqMechDo");
	else if (ix == DPCHAPPIDECIAQQCDSPDATA) return("DpchAppIdecIaqQcdspData");
	else if (ix == DPCHAPPIDECIAQQCDSPDO) return("DpchAppIdecIaqQcdspDo");
	else if (ix == DPCHAPPIDECIAQSCILLDATA) return("DpchAppIdecIaqScillData");
	else if (ix == DPCHAPPIDECIAQSCILLDO) return("DpchAppIdecIaqScillDo");
	else if (ix == DPCHAPPIDECINIT) return("DpchAppIdecInit");
	else if (ix == DPCHAPPIDECMIS1NTOURDATA) return("DpchAppIdecMis1NTourData");
	else if (ix == DPCHAPPIDECMIS1NTOURDO) return("DpchAppIdecMis1NTourDo");
	else if (ix == DPCHAPPIDECMISDETAILDATA) return("DpchAppIdecMisDetailData");
	else if (ix == DPCHAPPIDECMISDETAILDO) return("DpchAppIdecMisDetailDo");
	else if (ix == DPCHAPPIDECMISDO) return("DpchAppIdecMisDo");
	else if (ix == DPCHAPPIDECMISLISTDATA) return("DpchAppIdecMisListData");
	else if (ix == DPCHAPPIDECMISLISTDO) return("DpchAppIdecMisListDo");
	else if (ix == DPCHAPPIDECMISRECDO) return("DpchAppIdecMisRecDo");
	else if (ix == DPCHAPPIDECMISREF1NFILEDATA) return("DpchAppIdecMisRef1NFileData");
	else if (ix == DPCHAPPIDECMISREF1NFILEDO) return("DpchAppIdecMisRef1NFileDo");
	else if (ix == DPCHAPPIDECNAVDO) return("DpchAppIdecNavDo");
	else if (ix == DPCHAPPIDECNAVMAINTDATA) return("DpchAppIdecNavMaintData");
	else if (ix == DPCHAPPIDECNAVMAINTDO) return("DpchAppIdecNavMaintDo");
	else if (ix == DPCHAPPIDECNAVOPRDATA) return("DpchAppIdecNavOprData");
	else if (ix == DPCHAPPIDECNAVOPRDO) return("DpchAppIdecNavOprDo");
	else if (ix == DPCHAPPIDECNAVPREDO) return("DpchAppIdecNavPreDo");
	else if (ix == DPCHAPPIDECRESUME) return("DpchAppIdecResume");
	else if (ix == DPCHAPPIDECSCFCONNDATA) return("DpchAppIdecScfConnData");
	else if (ix == DPCHAPPIDECSCFCONNDO) return("DpchAppIdecScfConnDo");
	else if (ix == DPCHAPPIDECSCFDO) return("DpchAppIdecScfDo");
	else if (ix == DPCHAPPIDECSCFLWIRDATA) return("DpchAppIdecScfLwirData");
	else if (ix == DPCHAPPIDECSCFLWIRDO) return("DpchAppIdecScfLwirDo");
	else if (ix == DPCHAPPIDECSCFMECHDATA) return("DpchAppIdecScfMechData");
	else if (ix == DPCHAPPIDECSCFMECHDO) return("DpchAppIdecScfMechDo");
	else if (ix == DPCHAPPIDECSCFOPTICSDATA) return("DpchAppIdecScfOpticsData");
	else if (ix == DPCHAPPIDECSCFOPTICSDO) return("DpchAppIdecScfOpticsDo");
	else if (ix == DPCHAPPIDECSCFQCDDATA) return("DpchAppIdecScfQcdData");
	else if (ix == DPCHAPPIDECSCFQCDDO) return("DpchAppIdecScfQcdDo");
	else if (ix == DPCHAPPIDECSCFRECORDDATA) return("DpchAppIdecScfRecordData");
	else if (ix == DPCHAPPIDECSCFRECORDDO) return("DpchAppIdecScfRecordDo");
	else if (ix == DPCHAPPIDECSCFSTATUSDO) return("DpchAppIdecScfStatusDo");
	else if (ix == DPCHAPPIDECSCFTRIGGERDATA) return("DpchAppIdecScfTriggerData");
	else if (ix == DPCHAPPIDECSCFTRIGGERDO) return("DpchAppIdecScfTriggerDo");
	else if (ix == DPCHAPPIDECTOUDETAILDATA) return("DpchAppIdecTouDetailData");
	else if (ix == DPCHAPPIDECTOUDETAILDO) return("DpchAppIdecTouDetailDo");
	else if (ix == DPCHAPPIDECTOUDO) return("DpchAppIdecTouDo");
	else if (ix == DPCHAPPIDECTOULISTDATA) return("DpchAppIdecTouListData");
	else if (ix == DPCHAPPIDECTOULISTDO) return("DpchAppIdecTouListDo");
	else if (ix == DPCHAPPIDECTOURECDO) return("DpchAppIdecTouRecDo");
	else if (ix == DPCHAPPIDECTOUREF1NFILEDATA) return("DpchAppIdecTouRef1NFileData");
	else if (ix == DPCHAPPIDECTOUREF1NFILEDO) return("DpchAppIdecTouRef1NFileDo");
	else if (ix == DPCHAPPIDECUSGAACCESSDATA) return("DpchAppIdecUsgAAccessData");
	else if (ix == DPCHAPPIDECUSGAACCESSDO) return("DpchAppIdecUsgAAccessDo");
	else if (ix == DPCHAPPIDECUSGDETAILDATA) return("DpchAppIdecUsgDetailData");
	else if (ix == DPCHAPPIDECUSGDETAILDO) return("DpchAppIdecUsgDetailDo");
	else if (ix == DPCHAPPIDECUSGDO) return("DpchAppIdecUsgDo");
	else if (ix == DPCHAPPIDECUSGLISTDATA) return("DpchAppIdecUsgListData");
	else if (ix == DPCHAPPIDECUSGLISTDO) return("DpchAppIdecUsgListDo");
	else if (ix == DPCHAPPIDECUSGMNUSERDATA) return("DpchAppIdecUsgMNUserData");
	else if (ix == DPCHAPPIDECUSGMNUSERDO) return("DpchAppIdecUsgMNUserDo");
	else if (ix == DPCHAPPIDECUSGRECDO) return("DpchAppIdecUsgRecDo");
	else if (ix == DPCHAPPIDECUSR1NSESSIONDATA) return("DpchAppIdecUsr1NSessionData");
	else if (ix == DPCHAPPIDECUSR1NSESSIONDO) return("DpchAppIdecUsr1NSessionDo");
	else if (ix == DPCHAPPIDECUSRAACCESSDATA) return("DpchAppIdecUsrAAccessData");
	else if (ix == DPCHAPPIDECUSRAACCESSDO) return("DpchAppIdecUsrAAccessDo");
	else if (ix == DPCHAPPIDECUSRDETAILDATA) return("DpchAppIdecUsrDetailData");
	else if (ix == DPCHAPPIDECUSRDETAILDO) return("DpchAppIdecUsrDetailDo");
	else if (ix == DPCHAPPIDECUSRDO) return("DpchAppIdecUsrDo");
	else if (ix == DPCHAPPIDECUSRLISTDATA) return("DpchAppIdecUsrListData");
	else if (ix == DPCHAPPIDECUSRLISTDO) return("DpchAppIdecUsrListDo");
	else if (ix == DPCHAPPIDECUSRMNUSERGROUPDATA) return("DpchAppIdecUsrMNUsergroupData");
	else if (ix == DPCHAPPIDECUSRMNUSERGROUPDO) return("DpchAppIdecUsrMNUsergroupDo");
	else if (ix == DPCHAPPIDECUSRRECDO) return("DpchAppIdecUsrRecDo");
	else if (ix == DPCHAPPIDECUTLDO) return("DpchAppIdecUtlDo");
	else if (ix == DPCHAPPIDECUTLSPITERMDATA) return("DpchAppIdecUtlSpitermData");
	else if (ix == DPCHAPPIDECUTLSPITERMDO) return("DpchAppIdecUtlSpitermDo");
	else if (ix == DPCHAPPROOTIDECLOGIN) return("DpchAppRootIdecLogin");

	return("");
};
