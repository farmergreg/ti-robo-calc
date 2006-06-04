/**************************************************
***	Project Title: Robo Calc (robocalc)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
***	Description: An Application designed to		***
*** 			 Simplify the development of	***
***				 programs for the Norland		***
***				 Research Robot					***
***************************************************/

#include <tiams.h>
#include "RoboCalc.h"
#include "oo.h"
#include "appExt.h"
#include "Resources.h"
#include "rle.h"
 
////////////////////////////////////////////////////
//static function prototypes                    ///
//////////////////////////////////////////////////
static void appExtHelp(AppID self, USHORT strnum);
static void Event_Handler(pFrame self, PEvent e);
static void DoCustomMenu(void);

///////////////////////////////////////
//////////////////////////////////////

#define FRAME_SIZE (11 + NUM_XR_STRINGS)
    
APP_EXTENSION const appExtensions[NUM_EXTENSIONS]={
//		func name #, 						help string # 						func index
	{OO_FIRST_APP_STRING + XR_AboutRC,	OO_FIRST_APP_STRING + XR_st_AboutRC,		EXT_ABOUTRC},
	{OO_FIRST_APP_STRING + XR_CHKBOT,	OO_FIRST_APP_STRING + XR_st_CHKBOT,			EXT_CHKBOT},
	
	{OO_FIRST_APP_STRING + XR_CLB,		OO_FIRST_APP_STRING + XR_st_CLB,			EXT_CLB},
	{OO_FIRST_APP_STRING + XR_CLF,		OO_FIRST_APP_STRING + XR_st_CLF,			EXT_CLF},
	{OO_FIRST_APP_STRING + XR_CRB,		OO_FIRST_APP_STRING + XR_st_CRB,			EXT_CRB},
	{OO_FIRST_APP_STRING + XR_CRF,		OO_FIRST_APP_STRING + XR_st_CRF,			EXT_CRF},
	{OO_FIRST_APP_STRING + XR_CS,		OO_FIRST_APP_STRING + XR_st_CS,				EXT_CS },
	{OO_FIRST_APP_STRING + XR_CSD,		OO_FIRST_APP_STRING + XR_st_CSD,			EXT_CSD},
	{OO_FIRST_APP_STRING + XR_CSN,		OO_FIRST_APP_STRING + XR_st_CSN,			EXT_CSN},

	{OO_FIRST_APP_STRING + XR_DistCal,	OO_FIRST_APP_STRING + XR_st_DistCal,		EXT_DISTCAL},
	{OO_FIRST_APP_STRING + XR_Drive,	OO_FIRST_APP_STRING + XR_st_Drive,			EXT_DRIVE},
	
	{OO_FIRST_APP_STRING + XR_Hitec,	OO_FIRST_APP_STRING + XR_st_Hitec,			EXT_HITEC},
	
	
	{OO_FIRST_APP_STRING + XR_ResetLink,OO_FIRST_APP_STRING + XR_st_ResetLink,		EXT_RSTLNK},
	
	{OO_FIRST_APP_STRING + XR_SBB,		OO_FIRST_APP_STRING + XR_st_SBB,			EXT_SBB},
	{OO_FIRST_APP_STRING + XR_SBF,		OO_FIRST_APP_STRING + XR_st_SBF,			EXT_SBF},
	{OO_FIRST_APP_STRING + XR_SBN,		OO_FIRST_APP_STRING + XR_st_SBN,			EXT_SBN},
	{OO_FIRST_APP_STRING + XR_SFB,		OO_FIRST_APP_STRING + XR_st_SFB,			EXT_SFB},
	{OO_FIRST_APP_STRING + XR_SFF,		OO_FIRST_APP_STRING + XR_st_SFF,			EXT_SFF},
	{OO_FIRST_APP_STRING + XR_SFN,		OO_FIRST_APP_STRING + XR_st_SFN,			EXT_SFN},
	{OO_FIRST_APP_STRING + XR_SNB,		OO_FIRST_APP_STRING + XR_st_SNB,			EXT_SNB},
	{OO_FIRST_APP_STRING + XR_SNF,		OO_FIRST_APP_STRING + XR_st_SNF,			EXT_SNF},
	{OO_FIRST_APP_STRING + XR_SNN,		OO_FIRST_APP_STRING + XR_st_SNN,			EXT_SNN},

	{OO_FIRST_APP_STRING + XR_TBB,		OO_FIRST_APP_STRING + XR_st_TBB,			EXT_TBB},
	{OO_FIRST_APP_STRING + XR_TBF,		OO_FIRST_APP_STRING + XR_st_TBF,			EXT_TBF},
	{OO_FIRST_APP_STRING + XR_TBN,		OO_FIRST_APP_STRING + XR_st_TBN,			EXT_TBN},
	{OO_FIRST_APP_STRING + XR_TFB,		OO_FIRST_APP_STRING + XR_st_TFB,			EXT_TFB},
	{OO_FIRST_APP_STRING + XR_TFF,		OO_FIRST_APP_STRING + XR_st_TFF,			EXT_TFF},
	{OO_FIRST_APP_STRING + XR_TFN,		OO_FIRST_APP_STRING + XR_st_TFN,			EXT_TFN},
	{OO_FIRST_APP_STRING + XR_TNB,		OO_FIRST_APP_STRING + XR_st_TNB,			EXT_TNB},
	{OO_FIRST_APP_STRING + XR_TNF,		OO_FIRST_APP_STRING + XR_st_TNF,			EXT_TNF},
	{OO_FIRST_APP_STRING + XR_TNN,		OO_FIRST_APP_STRING + XR_st_TNN,			EXT_TNN},
	
	{OO_FIRST_APP_STRING + XR_TSBB,		OO_FIRST_APP_STRING + XR_st_TSBB,			EXT_TSBB},
	{OO_FIRST_APP_STRING + XR_TSBF,		OO_FIRST_APP_STRING + XR_st_TSBF,			EXT_TSBF},
	{OO_FIRST_APP_STRING + XR_TSBN,		OO_FIRST_APP_STRING + XR_st_TSBN,			EXT_TSBN},
	{OO_FIRST_APP_STRING + XR_TSFB,		OO_FIRST_APP_STRING + XR_st_TSFB,			EXT_TSFB},
	{OO_FIRST_APP_STRING + XR_TSFF,		OO_FIRST_APP_STRING + XR_st_TSFF,			EXT_TSFF},
	{OO_FIRST_APP_STRING + XR_TSFN,		OO_FIRST_APP_STRING + XR_st_TSFN,			EXT_TSFN},
	{OO_FIRST_APP_STRING + XR_TSNB,		OO_FIRST_APP_STRING + XR_st_TSNB,			EXT_TSNB},
	{OO_FIRST_APP_STRING + XR_TSNF,		OO_FIRST_APP_STRING + XR_st_TSNF,			EXT_TSNF},
	{OO_FIRST_APP_STRING + XR_TSNN,		OO_FIRST_APP_STRING + XR_st_TSNN,			EXT_TSNN},
	
	{OO_FIRST_APP_STRING + XR_Turn,		OO_FIRST_APP_STRING + XR_st_Turn,			EXT_TURN},
	
	{OO_FIRST_APP_STRING + XR_RoboCalc,	OO_FIRST_APP_STRING + XR_st_RoboCalc,		EXT_ROBOCALC}
};

APP_EXT_ENTRY const appExtEntries[NUM_EXTENSIONS]={
//		&Function(),		type

	{ext_ABOUTRC,	APP_EXT_PROGRAM},
	
	{ext_CHKBOT,APP_EXT_FUNCTION},
	
	{ext_CLB, 	APP_EXT_FUNCTION},
	{ext_CLF, 	APP_EXT_FUNCTION},	
	{ext_CRB, 	APP_EXT_FUNCTION},
	{ext_CRF, 	APP_EXT_FUNCTION},
	{ext_CS, 	APP_EXT_FUNCTION},
	{ext_CSD, 	APP_EXT_FUNCTION},
	{ext_CSN, 	APP_EXT_FUNCTION},
	
	{ext_DistCal,	APP_EXT_PROGRAM},
	{ext_Drive,		APP_EXT_PROGRAM},
	
	{ext_Hitec,		APP_EXT_PROGRAM},
	
	{ext_RSTLNK, APP_EXT_PROGRAM},
	
	{ext_SBB, 	APP_EXT_FUNCTION},
	{ext_SBF, 	APP_EXT_FUNCTION},
	{ext_SBN, 	APP_EXT_FUNCTION},
	{ext_SFB, 	APP_EXT_FUNCTION},
	{ext_SFF, 	APP_EXT_FUNCTION},
	{ext_SFN, 	APP_EXT_FUNCTION},
	{ext_SNB, 	APP_EXT_FUNCTION},
	{ext_SNF, 	APP_EXT_FUNCTION},
	{ext_SNN, 	APP_EXT_FUNCTION},

	{ext_TBB, 	APP_EXT_FUNCTION},
	{ext_TBF, 	APP_EXT_FUNCTION},
	{ext_TBN, 	APP_EXT_FUNCTION},
	{ext_TFB, 	APP_EXT_FUNCTION},
	{ext_TFF, 	APP_EXT_FUNCTION},
	{ext_TFN, 	APP_EXT_FUNCTION},
	{ext_TNB, 	APP_EXT_FUNCTION},
	{ext_TNF, 	APP_EXT_FUNCTION},
	{ext_TNN, 	APP_EXT_FUNCTION},
	
	{ext_TSBB, 	APP_EXT_FUNCTION},
	{ext_TSBF, 	APP_EXT_FUNCTION},
	{ext_TSBN, 	APP_EXT_FUNCTION},
	{ext_TSFB, 	APP_EXT_FUNCTION},
	{ext_TSFF, 	APP_EXT_FUNCTION},
	{ext_TSFN, 	APP_EXT_FUNCTION},
	{ext_TSNB, 	APP_EXT_FUNCTION},
	{ext_TSNF, 	APP_EXT_FUNCTION},
	{ext_TSNN, 	APP_EXT_FUNCTION},
	
	{ext_Turn, 	APP_EXT_PROGRAM},
	
	{ext_ROBOCALC,	APP_EXT_FUNCTION}
};

FRAME(appObj, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, FRAME_SIZE)
	ATTR(OO_APP_FLAGS, 					APP_INTERACTIVE) 				//0x0001
	ATTR(OO_APP_NAME, 					APP_TITLE)                      //0x0002
	ATTR(OO_APP_TOK_NAME, 				APP_INTERNAL)					//0x0003
	ATTR(OO_APP_PROCESS_EVENT, 			&Event_Handler)                 //0x0004
	ATTR(OO_APP_DEFAULT_MENU, 			&AppMenu)						//0x0005
	ATTR(OO_APP_EXT_COUNT, 				NUM_EXTENSIONS)					//0x0007
	ATTR(OO_APP_EXTENSIONS, 			appExtensions)					//0x0008
	ATTR(OO_APP_EXT_ENTRIES, 			appExtEntries)					//0x0009
	ATTR(OO_APP_ICON,					&AppIcon)						//0c000F
	ATTR(OO_APP_EXT_HELP,				appExtHelp)						//0x0010
	ATTR(OO_APP_ABOUT,					About)							//0x0012
    
//Application Strings   
	STRING_ATTR(XR_ShortAppName,		APP_TITLE)
	STRING_ATTR(XR_LongAppName,			APP_TITLE " v" APP_VERSION)
	STRING_ATTR(XR_AppVersion,			APP_VERSION)
	STRING_ATTR(XR_About_Me,			APP_TITLE " v"APP_VERSION"\n\nCopyright " RF_COPYRIGHT " 2004\nBy: Gregory L. Dietsche.\ngreg@detachedsolutions.com\n\nDetached Solutions:\nwww.detachedsolutions.com")
	STRING_ATTR(XR_RobotDetection,		"Robot Detection In Progress: Press ON To Cancel"RF_ELLIPSIS)
	STRING_ATTR(XR_DetectionFailed,		"Failed to detect a robot. Please make sure the robot is turned on, and check the link cable for loose connections.")
	STRING_ATTR(XR_HelpMessage,			"Full documentation can be found at:\n\nwww.detachedsolutions.com\n/robocalc/\n\nOr open the CATALOG, and Press F3: Flash Apps. Then use F1: Help for more information about each RoboCalc command.")
	
	STRING_ATTR(XR_ConfirmMenuInstall,	"This will replace your Custom Menu with one designed for RoboCalc.\nDo you wish to continue?")
	STRING_ATTR(XR_InstallingMenu,		"Please Wait While The RoboCalc Custom Menu Is Installed.")
	STRING_ATTR(XR_MenuInstalled,		"The RoboCalc Custom Menu has been installed. To use it press \"2nd CUSTOM\".")

//App ext extension help strings
	STRING_ATTR(XR_AboutRC,				"about")
	STRING_ATTR(XR_st_AboutRC,			"Show the RoboCalc About Dialog")
	STRING_ATTR(XR_msg_AboutRC,			"AboutRC()\nShow the RoboCalc About Screen")

//Check for Connection to Robot
    STRING_ATTR(XR_CHKBOT,				"checkbot")
    STRING_ATTR(XR_st_CHKBOT,			"Check If The Robot Is Connected Properly")
    STRING_ATTR(XR_msg_CHKBOT,			"CheckBot()\nChecks for a connection to the robot, resets the link interface and sets the robot to factory defaults. This function returns true if the robot is ON and connected to the calculator.")
    
//Calibration/Check Switch
    STRING_ATTR(XR_CLB,					"clb")
    STRING_ATTR(XR_st_CLB,				"Calibrate Left Wheel, Backward Dir")
    STRING_ATTR(XR_msg_CLB,				"CLB(INT)\nCalibrate left backward pulse length (valid range is 0 - 255).")
    
    STRING_ATTR(XR_CLF,					"clf")
    STRING_ATTR(XR_st_CLF,				"Calibrate Left Wheel, Forward Dir")
    STRING_ATTR(XR_msg_CLF,				"CLF(INT)\nCalibrate left forward pulse length (valid range is 255 - 0).")
    
    STRING_ATTR(XR_CRB,					"crb")
    STRING_ATTR(XR_st_CRB,				"Calibrate Right Wheel, Backward Dir")
    STRING_ATTR(XR_msg_CRB,				"CRB(INT)\nCalibrate right backward pulse length (valid range is 255 - 0).")
    
    STRING_ATTR(XR_CRF,					"crf")
    STRING_ATTR(XR_st_CRF,				"Calibrate Right Wheel, Forward Dir")
    STRING_ATTR(XR_msg_CRF,				"CRF(INT)\nCalibrate right forward pulse length (valid range is 0 - 255).")
    
    STRING_ATTR(XR_CS,					"cs")
    STRING_ATTR(XR_st_CS,				"Check Bumper Switches")
    STRING_ATTR(XR_msg_CS,				"CS()\nFind which bumper switch caused the robot to stop.\n\n1 = Left Switch\n2 = Right Switch\n3 = Both Switches\n")
    
    STRING_ATTR(XR_CSD,					"csd")
    STRING_ATTR(XR_st_CSD,				"Use Factory Default Calibration Settings")
    STRING_ATTR(XR_msg_CSD,				"CSD()\nResets all robot calibration settings to their defaults.")
    
    STRING_ATTR(XR_CSN,					"csn")
    STRING_ATTR(XR_st_CSN,				"Check Bumper Switches Now")
    STRING_ATTR(XR_msg_CSN,				"CSN()\nCheck to see if a bumper switch is pressed NOW.\n\n1 = Left Switch\n2 = Right Switch\n3 = Both Switches\n")
	
	STRING_ATTR(XR_DistCal,				"distcal")
	STRING_ATTR(XR_st_DistCal,			"Calibration for Drive & Turn Commands")
	STRING_ATTR(XR_msg_DistCal,			"DistCal()\nAllow the robot to move one unit of distance forward before the bumper is triggered. Distance traveled should be equal to the circumference of the wheels.")
	
	STRING_ATTR(XR_Drive,				"drive")
	STRING_ATTR(XR_st_Drive,			"Robot moves forward/backward x units")
	STRING_ATTR(XR_msg_Drive,			"Drive(INT)\nMove the robot forward x units. If the unit value is negative, the robot moves in reverse.\nDistance traveled is 1/3 of distance set with distcal().")
	
	STRING_ATTR(XR_Hitec,				"hitec")
	STRING_ATTR(XR_st_Hitec,			"Switches to Hitec Servo Mode")
	STRING_ATTR(XR_msg_Hitec,			"Hitec()\nIf your robot uses Hitec servos, run this command to calibrate the robot so that it works correctly with RoboCalc.")
	
	STRING_ATTR(XR_ResetLink,			"resetlnk")
	STRING_ATTR(XR_st_ResetLink,		"Reset the robot link interface")
	STRING_ATTR(XR_msg_ResetLink,		"ResetLnk()\nFollow this sequence to reset the robot link interface:\n1. Turn off the robot\n2. Execute this command\n3.Turn Robot Back On")
	
//Switch Only    
    STRING_ATTR(XR_SBB,					"sbb")
    STRING_ATTR(XR_st_SBB,				"Switch;Backward;Backward")
    STRING_ATTR(XR_msg_SBB,				"SBB()\nMove backward until a bumper switch is triggered.")
    
    STRING_ATTR(XR_SBF,					"sbf")
    STRING_ATTR(XR_st_SBF,				"Switch;Backward;Forward")
    STRING_ATTR(XR_msg_SBF,				"SBF()\nTurn in place to the left until a bumper switch is triggered.")

    STRING_ATTR(XR_SBN,					"sbn")
    STRING_ATTR(XR_st_SBN,				"Switch;Backward;Neutral")
    STRING_ATTR(XR_msg_SBN,				"SBN()\nTurn left while pivoting on the right wheel until a bumper switch is triggered.")

    STRING_ATTR(XR_SFB,					"sfb")
    STRING_ATTR(XR_st_SFB,				"Switch;Forward;Backward")
    STRING_ATTR(XR_msg_SFB,				"SFB()\nTurn in place to the right until a bumper switch is triggered.")

    STRING_ATTR(XR_SFF,					"sff")
    STRING_ATTR(XR_st_SFF,				"Switch;Forward;Forward")
    STRING_ATTR(XR_msg_SFF,				"SFF()\nMove forward until a bumper switch is triggered.")

    STRING_ATTR(XR_SFN,					"sfn")
    STRING_ATTR(XR_st_SFN,				"Switch;Forward;Neutral")
    STRING_ATTR(XR_msg_SFN,				"SFN()\nTurn right while pivoting on the right wheel until a bumper switch is triggered.")

    STRING_ATTR(XR_SNB,					"snb")
    STRING_ATTR(XR_st_SNB,				"Switch;Neutral;Backward")
    STRING_ATTR(XR_msg_SNB,				"SNB()\nTurn right while pivoting on the left wheel until a bumper switch is triggered.")
    
    STRING_ATTR(XR_SNF,					"snf")
    STRING_ATTR(XR_st_SNF,				"Switch;Neutral;Forward")
    STRING_ATTR(XR_msg_SNF,				"SNF()\nTurn left while pivoting on the left wheel until a bumper switch is triggered.")
    
    STRING_ATTR(XR_SNN,					"snn")
    STRING_ATTR(XR_st_SNN,				"Switch;Neutral;Neutral")
    STRING_ATTR(XR_msg_SNN,				"SNN()\nDo not move; wait until a bumper switch is triggered.")

//Timed Only
    STRING_ATTR(XR_TBB,					"tbb")
    STRING_ATTR(XR_st_TBB,				"Timed;Backward;Backward")
    STRING_ATTR(XR_msg_TBB,				"TBB(INT)\nMove in reverse until the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TBF,					"tbf")
    STRING_ATTR(XR_st_TBF,				"Timed;Backward;Forward")
    STRING_ATTR(XR_msg_TBF,				"TBF(INT)\nTurn in place to the left until the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TBN,					"tbn")
    STRING_ATTR(XR_st_TBN,				"Timed;Backward;Neutral")
    STRING_ATTR(XR_msg_TBN,				"TBN(INT)\nTurn left while pivoting on the right wheel until the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TFB,					"tfb")
    STRING_ATTR(XR_st_TFB,				"Timed;Forward;Backward")
    STRING_ATTR(XR_msg_TFB,				"TFB(INT)\nTurn in place to the right until the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TFF,					"tff")
    STRING_ATTR(XR_st_TFF,				"Timed;Forward;Forward")
    STRING_ATTR(XR_msg_TFF,				"TFF(INT)\nMove forward until the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TFN,					"tfn")
    STRING_ATTR(XR_st_TFN,				"Timed;Forward;Neutral")
    STRING_ATTR(XR_msg_TFN,				"TFN(INT)\nTurn right while pivoting on the right wheel until the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TNB,					"tnb")
    STRING_ATTR(XR_st_TNB,				"Timed;Neutral;Backward")
    STRING_ATTR(XR_msg_TNB,				"TNB(INT)\nTurn right while pivoting on the left wheel until the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TNF,					"tnf")
    STRING_ATTR(XR_st_TNF,				"Timed;Neutral;Forward")
    STRING_ATTR(XR_msg_TNF,				"TNF(INT)\nTurn left while pivoting on the left wheel until the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TNN,					"tnn")
    STRING_ATTR(XR_st_TNN,				"Timed;Neutral;Neutral")
    STRING_ATTR(XR_msg_TNN,				"TNN(INT)\nDo not move; wait until the specified time in milliseconds elapses.")
    
//Timed and Switched
   STRING_ATTR(XR_TSBB,					"tsbb")
    STRING_ATTR(XR_st_TSBB,				"Timed&Switch;Backward;Backward")
    STRING_ATTR(XR_msg_TSBB,			"TSBB(INT)\nMove in reverse until a bumper switch is triggered, or the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TSBF,				"tsbf")
    STRING_ATTR(XR_st_TSBF,				"Timed&Switch;Backward;Forward")
    STRING_ATTR(XR_msg_TSBF,			"TSBF(INT)\nTurn in place to the left until a bumper switch is triggered, or the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TSBN,				"tsbn")
    STRING_ATTR(XR_st_TSBN,				"Timed&Switch;Backward;Neutral")
    STRING_ATTR(XR_msg_TSBN,			"TSBN(INT)\nTurn left while pivoting on the right wheel until a bumper switch is triggered, or the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TSFB,				"tsfb")
    STRING_ATTR(XR_st_TSFB,				"Timed&Switch;Forward;Backward")
    STRING_ATTR(XR_msg_TSFB,			"TSFB(INT)\nTurn in place to the right until a bumper switch is triggered, or the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TSFF,				"tsff")
    STRING_ATTR(XR_st_TSFF,				"Timed&Switch;Forward;Forward")
    STRING_ATTR(XR_msg_TSFF,			"TSFF(INT)\nMove forward until a bumper switch is triggered, or the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TSFN,				"tsfn")
    STRING_ATTR(XR_st_TSFN,				"Timed&Switch;Forward;Neutral")
    STRING_ATTR(XR_msg_TSFN,			"TSFN(INT)\nTurn right while pivoting on the right wheel until a bumper switch is triggered, or the specified time in milliseconds elapses.")

    STRING_ATTR(XR_TSNB,				"tsnb")
    STRING_ATTR(XR_st_TSNB,				"Timed&Switch;Neutral;Backward")
    STRING_ATTR(XR_msg_TSNB,			"TSNB(INT)\nTurn right while pivoting on the left wheel until a bumper switch is triggered, or the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TSNF,				"tsnf")
    STRING_ATTR(XR_st_TSNF,				"Timed&Switch;Neutral;Forward")
    STRING_ATTR(XR_msg_TSNF,			"TSNF(INT)\nTurn left while pivoting on the left wheel until a bumper switch is triggered, or the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_TSNN,				"tsnn")
    STRING_ATTR(XR_st_TSNN,				"Timed&Switch;Neutral;Neutral")
    STRING_ATTR(XR_msg_TSNN,			"TSNN(INT)\nDo not move; wait until a bumper switch is triggered, or the specified time in milliseconds elapses.")
    
    STRING_ATTR(XR_Turn,				"turn")
	STRING_ATTR(XR_st_Turn,				"Robot Turns x degrees")
	STRING_ATTR(XR_msg_Turn,			"Turn(INT)\nTurns the robot the number of degrees specified. You must first calibrate the robot using distcal().")
    
    //Returns the Robo Calc Version
	STRING_ATTR(XR_RoboCalc,			"version")
	STRING_ATTR(XR_st_RoboCalc,			"Returns the version number of RoboCalc ("APP_VERSION")")
	STRING_ATTR(XR_msg_RoboCalc,		"Version()\nReturns the RoboCalc version number as a decimal value. ("APP_VERSION")")
ENDFRAME

//////////////////////////////////////////////////
//Application Data Section					  ///
////////////////////////////////////////////////

/* Pointer to the Frame object */
	pFrame pAppObj = (pFrame)&appObj;  /* Must be first! */
	static WINDOW appW;
	static BOOL appWopen;

//This is a bitmap structure, NOT an icon as suggested by the FRAME entry
const short AppIcon[]={
	0x0013,	//Num Rows	/\
	0x0010,	//Num Cols	<->
	//icon data            	
	0xffff,0xffff,0x0ff0,0x3d5c,0x7ebe,0x5d5e,0x7ebe,0x7d5a,0x7ffe,0x7d5e,
	0x3ffc,0x0db0,0x0eb0,0x0d70,0x0eb0,0x0d70,0x0ff0,0x07e0,0x03c0
};


//16x16 Detached Solutions BITMAP
const short DSIcon[]={
	0x0010,
	0x0010,
	0x0000,0x0000,0x7e00,0x7f00,0x7780,0x7380,0x779c,0x77fe,
	0x7f77,0x7c7e,0x403f,0x7ff7,0x007f,0x003e,0x0000,0x0000
};

#ifdef _89
	#include "TI89TitleScr.h"
#else
	#include "TI92TitleScr.h"
#endif

//due to limitations in TIFS regarding string lengths, i've divided one string into three parts.
static const char strCustomMenu0[]=
"Custom"
":Title \"Sxx\":Item  \"rbot.SBB()\":Item  \"rbot.SBF()\":Item  \"rbot.SBN()\":Item  \"rbot.SFB()\""
":Item \"rbot.SFF()\":Item  \"rbot.SFN()\":Item  \"rbot.SNB()\":Item  \"rbot.SNF()\":Item  \"rbot.SNN()\""
;
static const char strCustomMenu1[]=
":Title \"Txx\":Item  \"rbot.TBB(\":Item  \"rbot.TBF(\":Item  \"rbot.TBN(\":Item  \"rbot.TFB(\":Item  \"rbot.TFF(\""
":Item  \"rbot.TFN(\":Item  \"rbot.TNB(\":Item  \"rbot.TNF(\":Item  \"rbot.TNN(\""
":Title \"TSxx\":Item  \"rbot.TSBB(\":Item  \"rbot.TSBF(\":Item  \"rbot.TSBN(\":Item  \"rbot.TSFB(\":Item  \"rbot.TSFF(\":Item  \"rbot.TSFN(\":Item  \"rbot.TSNB(\":Item  \"rbot.TSNF(\":Item  \"rbot.TSNN(\""
;

static const char strCustomMenu2[]=
":Title \"Distance\":Item  \"rbot.distance(\":Item  \"rbot.turn(\":Item  \"rbot.distcal()\""
":Title \"Status\":Item  \"rbot.CS()\":Item  \"rbot.CSN()\":Item  \"rbot.checkbot()\""
":Title \"Settings\":Item  \"rbot.CLB(\":Item  \"rbot.CLF(\":Item  \"rbot.CRB(\":Item  \"rbot.CRF(\":Item  \"rbot.CSD()\""
":Title \"Advanced\":Item  \"Send {\":Item  \"Get \":Item  \"rbot.AboutRC()\":Item  \"rbot.resetlnk()\":Item  \"rbot.Version()\":Item \"rbot.Hitec()\""
":EndCustm:CustmOff";

//the main event handler
static void Event_Handler(pFrame self, PEvent e)
{
	Access_AMS_Global_Variables;
	WIN_RECT appWR;
	static WIN_POINT ds_pt, bot_pt;
	static short ds_dx=-1, ds_dy=1;
	static short bot_dx=1, bot_dy=1;
	
	CheckAMS(pAppObj, 2, 4);
	
	switch(e->command)
	{
		
		case CM_START:
			appWR = *(e->info.startInfo.startRect);			
			MO_currentOptions();
         	appWopen=WinOpen(&appW, &appWR, (MO_option[MO_OPT_SPLIT_SCREEN]==D_MODE_SPLIT_FULL?WF_NOBORDER:0));
 
         	/*{
         		char buff[200];
         		sprintf(buff, "%d %d", WinHeight(&appW), WinWidth(&appW));
         		ST_helpMsg(buff);
         		ngetchx();
         	}*/
         	
		break;
		
		case CM_QUIT:
			if(appWopen)
				WinClose(&appW);
		break;
		
		#ifdef DEBUG
			case CM_ACTIVATE:
				EV_defaultHandler(e);
				ST_helpMsg("WARNING: This is a debug build!");
			break;
			
			//case CM_DEACTIVATE:
			//break;
		#endif

		case CM_WPAINT:
		
			if(appWopen)
         	{
         		WinClr(&appW);
         		
         		ds_pt.x0=0;ds_pt.y0=0;
         		bot_pt.x0=WinWidth(&appW)-16;bot_pt.y0=WinHeight(&appW)-16;
         		
         		if(MO_option[MO_OPT_SPLIT_SCREEN]==D_MODE_SPLIT_FULL)
         		{
         		//The TI-89 picture is 1604 bytes decompressed	(160x77)
         		//The TI-92 Plus / Voyage 200 picture is 3094 bytes decompressed (240x103)
         			char buff[4000];
         			
         			rle_decode((unsigned char *)buff, (unsigned char*)gTitleScreen, sizeof(gTitleScreen));
         			WinBitmapPut(&appW, 0,0, (BITMAP *)buff, A_REPLACE);
         			
         			/*sprintf(buff, "%lu", rle_decode(NULL, (unsigned char*)gTitleScreen, sizeof(gTitleScreen)));
         			ST_helpMsg(buff);
         			ngetchx();*/
         		}
         		
         		WinBitmapPut(&appW, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
         		WinBitmapPut(&appW, bot_pt.x0, bot_pt.y0, (BITMAP*)AppIcon, A_XOR);
         	}
		
		break;
		
		case CM_NULL:
		{
			static short delay=0;
			
			delay++;
			
			if((delay%1))
				return;
				
			delay=0;
			
				
			WinBitmapPut(&appW, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
		    WinBitmapPut(&appW, bot_pt.x0, bot_pt.y0, (BITMAP*)AppIcon, A_XOR);
		    
		//DS logo calculations
			if(ds_pt.x0>WinWidth(&appW)-16  || ds_pt.x0<0)ds_dx=-ds_dx;
			if(ds_pt.y0>WinHeight(&appW)-16 || ds_pt.y0<0)ds_dy=-ds_dy;
			ds_pt.x0+=ds_dx;	ds_pt.y0+=ds_dy;
		//RoboCalc logo calculations
			if(bot_pt.x0>WinWidth(&appW)-16  || bot_pt.x0<0)bot_dx=-bot_dx;
			if(bot_pt.y0>WinHeight(&appW)-16 || bot_pt.y0<0)bot_dy=-bot_dy;
			bot_pt.x0+=bot_dx;	bot_pt.y0+=bot_dy;
			
			if( (bot_pt.x0-ds_pt.x0) <8  && (bot_pt.y0-ds_pt.y0) <8)
			{
				bot_dx=-bot_dx;
				ds_dx=-ds_dx;
			}
			
			WinBitmapPut(&appW, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
			WinBitmapPut(&appW, bot_pt.x0, bot_pt.y0, (BITMAP*)AppIcon, A_XOR);
		}
		break;
		
		case CM_KEY_PRESS:
			switch(e->info.keyInfo.keyCode)
			{
				case KB_UP:
					bot_dy=-bot_dy;
				break;
				
				case KB_DOWN:
					bot_dx=-bot_dx;
				break;
				
				case KB_LEFT:
					ds_dy=-ds_dy;
				break;
				
				case KB_RIGHT:
					ds_dx=-ds_dx;
				break;
				
				default:
					EV_defaultHandler(e);
				break;
			}
		break;
		
		case CM_ABOUT:
			About();
		break;
		
		case ACM_DoCustomMenu:
			DoCustomMenu();
		break;
		
		case ACM_Help:
			DlgNotice(XR_stringPtr(XR_LongAppName), XR_stringPtr(XR_HelpMessage));
		break;
		
		default:
  			EV_defaultHandler(e);
  		break;
  	}
}

static void DoCustomMenu(void)
{
	Access_AMS_Global_Variables;
	char buff[4*1204];
	BOOL dlg;
	
	if(DlgMessage(XR_stringPtr(XR_ShortAppName), XR_stringPtr(XR_ConfirmMenuInstall), PDB_YES, PDB_NO)!=KB_ENTER)
		return;
		
	dlg=ERD_notice((UCHAR*)XR_stringPtr(XR_ShortAppName), (UCHAR*)XR_stringPtr(XR_InstallingMenu));
	
	TRY
		strcpy(buff,strCustomMenu0);
		strcat(buff,strCustomMenu1);
		strcat(buff,strCustomMenu2);
		
		#ifdef DEBUG
			if(strlen(buff) >= (4*1024))     	//see declaration on the stack of "buff"
				DlgNotice(XR_stringPtr(XR_LongAppName), "Buffer Overflow in function DoCustomMenu");
		#endif
		
		push_quantum(END_TAG);
		push_parse_text((BYTE *)buff);
		push_simplify_statements(top_estack);
	
	FINALLY	
		if(dlg)ERD_dismissNotice();
	ENDFINAL
	
	DlgNotice(XR_stringPtr(XR_LongAppName), XR_stringPtr(XR_MenuInstalled));
	                      
}


//Implements the About Screen and About Frame Attribute about string
char* About(void)
{//This app may not be active when this function is called, so use
//a lookup method that will not fail
	Access_AMS_Global_Variables;
	EStackIndex top=top_estack;
		
	push_quantum(END_TAG);	//ext_ABOUTRC is fussy if it precieves any arguments
	ext_ABOUTRC();
	top_estack=top;

	return OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_About_Me);
}

static void appExtHelp(AppID self, USHORT strnum)
{
	DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName), 
				OO_AbsoluteGet((OO_FIRST_APP_STRING + OO_FIRST_APP_STRING + 12) + strnum*3));
}

