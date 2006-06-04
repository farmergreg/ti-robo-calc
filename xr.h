/**************************************************
***	Project Title: Robo Calc (robocalc)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
***	Description: An Application designed to		***
*** 			 Simplify the development of	***
***				 programs for the Norland		***
***				 Research Robot					***
***************************************************/

#ifndef _XR_H_
#define _XR_H_
								
//Application XR strings
enum XR_STRINGS { XR_ShortAppName=OO_FIRST_APP_STRING,
				  XR_LongAppName,
				  XR_AppVersion,
				  XR_About_Me,
				  XR_RobotDetection,
				  XR_DetectionFailed,
				  XR_HelpMessage,
				  
				  XR_ConfirmMenuInstall,
				  XR_InstallingMenu,
				  XR_MenuInstalled,
                  
                  XR_AboutRC,
				  XR_st_AboutRC,
				  XR_msg_AboutRC,
				  
				  XR_CHKBOT,
				  XR_st_CHKBOT,
				  XR_msg_CHKBOT,
				  
				  XR_CLB,
				  XR_st_CLB,
				  XR_msg_CLB,
				  
				  XR_CLF,
				  XR_st_CLF,
				  XR_msg_CLF,
				  
				  XR_CRB,
				  XR_st_CRB,
				  XR_msg_CRB,
				  
				  XR_CRF,
				  XR_st_CRF,
				  XR_msg_CRF,
				  
				  XR_CS,
				  XR_st_CS,
				  XR_msg_CS,
				  
				  XR_CSD,
				  XR_st_CSD,
				  XR_msg_CSD,
				  
				  XR_CSN,
				  XR_st_CSN,
				  XR_msg_CSN,

				  XR_DistCal,
				  XR_st_DistCal,
				  XR_msg_DistCal,
				  
				  XR_Drive,
				  XR_st_Drive,
				  XR_msg_Drive,
				  
				  XR_Hitec,
				  XR_st_Hitec,
				  XR_msg_Hitec,
				  				  
				  XR_ResetLink,
				  XR_st_ResetLink,
				  XR_msg_ResetLink,
				  
				  XR_SBB,			//BB
				  XR_st_SBB,
				  XR_msg_SBB,
				  XR_SBF,			//BF
				  XR_st_SBF,
				  XR_msg_SBF,
				  XR_SBN,			//BN
				  XR_st_SBN,
				  XR_msg_SBN,
				  XR_SFB,			//FB
				  XR_st_SFB,
				  XR_msg_SFB,
				  XR_SFF,			//FF
				  XR_st_SFF,
				  XR_msg_SFF,
				  XR_SFN,			//FN
				  XR_st_SFN,
				  XR_msg_SFN,				  
				  XR_SNB,			//NB
				  XR_st_SNB,
				  XR_msg_SNB,
				  XR_SNF,			//NF
				  XR_st_SNF,
				  XR_msg_SNF,
				  XR_SNN,			//NN
				  XR_st_SNN,
				  XR_msg_SNN,

				  XR_TBB,			//BB
				  XR_st_TBB,
				  XR_msg_TBB,
				  XR_TBF,			//BF
				  XR_st_TBF,
				  XR_msg_TBF,
				  XR_TBN,			//BN
				  XR_st_TBN,
				  XR_msg_TBN,
				  XR_TFB,			//FB
				  XR_st_TFB,
				  XR_msg_TFB,
				  XR_TFF,			//FF
				  XR_st_TFF,
				  XR_msg_TFF,
				  XR_TFN,			//FN
				  XR_st_TFN,
				  XR_msg_TFN,				  
				  XR_TNB,			//NB
				  XR_st_TNB,
				  XR_msg_TNB,
				  XR_TNF,			//NF
				  XR_st_TNF,
				  XR_msg_TNF,
				  XR_TNN,			//NN
				  XR_st_TNN,
				  XR_msg_TNN,
				  				  
				  XR_TSBB,			//BB
				  XR_st_TSBB,
				  XR_msg_TSBB,
				  XR_TSBF,			//BF
				  XR_st_TSBF,
				  XR_msg_TSBF,
				  XR_TSBN,			//BN
				  XR_st_TSBN,
				  XR_msg_TSBN,
				  XR_TSFB,			//FB
				  XR_st_TSFB,
				  XR_msg_TSFB,
				  XR_TSFF,			//FF
				  XR_st_TSFF,
				  XR_msg_TSFF,
				  XR_TSFN,			//FN
				  XR_st_TSFN,
				  XR_msg_TSFN,				  
				  XR_TSNB,			//NB
				  XR_st_TSNB,
				  XR_msg_TSNB,
				  XR_TSNF,			//NF
				  XR_st_TSNF,
				  XR_msg_TSNF,
				  XR_TSNN,			//NN
				  XR_st_TSNN,
				  XR_msg_TSNN,
				  
				  XR_Turn,			//Turn
				  XR_st_Turn,
				  XR_msg_Turn,
				  
				  XR_RoboCalc,		//Version
                  XR_st_RoboCalc,
                  XR_msg_RoboCalc,
				  
				  LAST_XR_STRING
				  };                          	
#define NUM_XR_STRINGS (LAST_XR_STRING-OO_FIRST_APP_STRING)
//Application Defined TI-Basic Extensions
//Keep in ABC order, or there will be big problems!
	
enum
{
    EXT_ABOUTRC,
    EXT_CHKBOT,
    
    EXT_CLB,
    EXT_CLF,    
    EXT_CRB,
    EXT_CRF,
    EXT_CS,
    EXT_CSD,
    EXT_CSN,
    
    EXT_DISTCAL,
    EXT_DRIVE,
    EXT_HITEC,
    EXT_RSTLNK,
    
    EXT_SBB,
    EXT_SBF,
	EXT_SBN,
	EXT_SFB,
	EXT_SFF,
	EXT_SFN,
	EXT_SNB,
	EXT_SNF,
	EXT_SNN,
    
    EXT_TBB,
    EXT_TBF,
	EXT_TBN,
	EXT_TFB,
	EXT_TFF,
	EXT_TFN,
	EXT_TNB,
	EXT_TNF,
	EXT_TNN,
		
    EXT_TSBB,
    EXT_TSBF,
	EXT_TSBN,
	EXT_TSFB,
	EXT_TSFF,
	EXT_TSFN,
	EXT_TSNB,
	EXT_TSNF,
	EXT_TSNN,
	
	EXT_TURN,
	
	EXT_ROBOCALC,

	NUM_EXTENSIONS
};

#endif
