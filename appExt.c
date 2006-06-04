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
#include "appExt.h"
#include "oo.h"

static void NoESArgs(short value);
static void OneESArg(short value);
static long StrToEStackToLong(char *str);
static unsigned long GetLongArg(EStackIndex index, unsigned long rLow, unsigned long rHigh);

//Member Variables
static unsigned short gDistanceCalibration=200;	//by default assume 2 seconds is one unit of distance

//Calibrate
void ext_CLB(void){ OneESArg(401); }
void ext_CLF(void){ OneESArg(421); }
void ext_CRB(void){ OneESArg(410); }
void ext_CSD(void){ NoESArgs(499); }
void ext_CRF(void){ OneESArg(412); }

//Check Switch
void ext_CS (void) { NoESArgs(51); }
void ext_CSN(void){ NoESArgs(52); }

//Reset The Link Interface
void ext_RSTLNK(void) { OSLinkReset(); }

//Switch Only
void ext_SBB(void){ NoESArgs(200); }
void ext_SBF(void){ NoESArgs(202); }
void ext_SBN(void){ NoESArgs(201); }
void ext_SFB(void){ NoESArgs(220); }
void ext_SFF(void){ NoESArgs(222); }
void ext_SFN(void){ NoESArgs(221); }
void ext_SNB(void){ NoESArgs(210); }
void ext_SNF(void){ NoESArgs(212); }
void ext_SNN(void){ NoESArgs(211); }

//Timed Only
void ext_TBB(void){ OneESArg(100); }
void ext_TBF(void){ OneESArg(102); }
void ext_TBN(void){ OneESArg(101); }
void ext_TFB(void){ OneESArg(120); }
void ext_TFF(void){ OneESArg(122); }
void ext_TFN(void){ OneESArg(121); }
void ext_TNB(void){ OneESArg(110); }
void ext_TNF(void){ OneESArg(112); }
void ext_TNN(void){ OneESArg(111); }

//Timed and Switched
void ext_TSBB(void){ OneESArg(300); }
void ext_TSBF(void){ OneESArg(302); }
void ext_TSBN(void){ OneESArg(301); }
void ext_TSFB(void){ OneESArg(320); }
void ext_TSFF(void){ OneESArg(322); }
void ext_TSFN(void){ OneESArg(321); }
void ext_TSNB(void){ OneESArg(310); }
void ext_TSNF(void){ OneESArg(312); }
void ext_TSNN(void){ OneESArg(311); }

static void NoESArgs(short value)
{
	Access_AMS_Global_Variables;
	CONTROL_BITS old_ng=NG_control;
	
	if(remaining_element_count(top_estack)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	TRY
		SET_SIDE_EFFECTS_PERMITTED;		
		
		check_estack_size(50);
		
		PUSH_QUANTUM_NOCHECK(END_TAG);
		push_ushort_to_integer(value);
		PUSH_QUANTUM_NOCHECK(LIST_TAG);
		PUSH_QUANTUM_NOCHECK(SEND_TAG);
		PUSH_QUANTUM_NOCHECK(COMMAND_TAG);
		push_simplify_statements(top_estack);
		
		PUSH_QUANTUM_NOCHECK(T_VAR_TAG);
		PUSH_QUANTUM_NOCHECK(GET_TAG);
		PUSH_QUANTUM_NOCHECK(COMMAND_TAG);
		push_simplify_statements(top_estack);		//some day i'll figure out how the SEPARATOR_TAG works...
		
		PUSH_QUANTUM_NOCHECK(T_VAR_TAG);
		push_simplify(top_estack);
		
	FINALLY
		NG_control=old_ng;
	ENDFINAL
}

static void OneESArg(short value)
{
	Access_AMS_Global_Variables;
	short time;
	CONTROL_BITS old_ng=NG_control;
	short argcount=remaining_element_count(top_estack);
	char buff[512];
	
	if(argcount<1)		ER_throw(TOO_FEW_ARGS_ERROR);
	else if(argcount>1) ER_throw(TOO_MANY_ARGS_ERROR);
	
	
//the following two tags force the anser to be an exact integer... so it works nice with GetLongArg
	push_quantum(RATIONALIZE_TAG);	//RATIONALIZE_TAG = exactP = exact(
	push_quantum(GREATEST_INT_TAG);	//GREATEST_INT_TAG = intP = int(
	push_simplify(top_estack);
	
	time=GetLongArg(top_estack,0,USHRT_MAX);
	
	if(value>400 && time>0xFF)ER_throw(ER_ARGUMENT);	//error checking for calibrate commands
	
	sprintf(buff,"%s{%u,%u}:%st:t", XR_stringPtr(XR_SendB), value, time, XR_stringPtr(XR_GetB));
		
	TRY
		SET_SIDE_EFFECTS_PERMITTED;
		push_parse_text((BYTE *)buff);
		push_simplify_statements(top_estack);
	FINALLY
		NG_control=old_ng;
	ENDFINAL
}

void ext_ABOUTRC(void)
{
	Access_AMS_Global_Variables;
	const WIN_RECT wRegion={C(10, 30), C(4, 6), C(MAX_X-10, 215), C(85, 113)};
	WINDOW win;
	WIN_POINT ds_pt={4,1}, post_pt;
	#ifndef NO_EASTER_EGGS
		short leet_user=FALSE;
		short key_code='x';//initialize it with something other than a valid key...
	#endif
	
	if(remaining_element_count(top_estack)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	if(!WinOpen(&win, &wRegion, WF_SAVE_SCR|WF_TTY|WF_TITLE|WF_ROUNDEDBORDER, XR_stringPtr(XR_ABOUT)))
		ER_throw(ER_MEMORY);
	
	WinBeginPaint(&win);
	
	#ifdef _89
		WinFont(&win, F_4x6);
	#endif
	
	post_pt.x0=WinWidth(&win)-4-((BITMAP*)AppIcon)->NumCols;
	post_pt.y0=1;
	
	WinClr(&win);
	WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
	WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
	
	WinMoveTo(&win,33,7);
	WinStr(&win, (char*)OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_About_Me));//About());
	DrawStaticButton(&win, PDB_OK, 5);
	
	#ifdef NO_EASTER_EGGS
		while(KeyYesOrNo(GKeyIn(NULL, GKF_MODAL | GKF_SYS))==-1);
	#else
		while(KeyYesOrNo(key_code)==-1)
		{
			key_code=GKeyIn(NULL, GKF_MODAL | GKF_SYS);
			if(key_code==(0x31337-(0x12F0|0x30000)) && !leet_user)	//$r3 j00 1 31337 H4X0R G
			{
				short dx=1, dy=1, steps;
				
				leet_user=TRUE;
				
				for(steps=0;steps<C(105,210);steps++)
				{
					#ifdef _92
					if(steps<155)
					{
					#endif
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
						post_pt.x0--;
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
					#ifdef _92
					}
					else
					{
						short delay;
						for(delay=0;delay<5000;delay++);
					}
					#endif
					
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
					if(ds_pt.x0>WinWidth(&win)-16  || ds_pt.x0<0)dx=-dx;
					if(ds_pt.y0>WinHeight(&win)-16 || ds_pt.y0<0)dy=-dy;
					ds_pt.x0+=dx;	ds_pt.y0+=dy;
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
				}
			}
		}
		#endif
	

	WinEndPaint(&win);
	WinClose(&win);
}

void ext_ROBOCALC(void)
{
	Access_AMS_Global_Variables;
	EStackIndex new_top;
	EStackIndex old_top=top_estack;
	
	if(remaining_element_count(old_top)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	push_quantum(END_TAG);
	push_zstr(APP_VERSION);
	push_quantum(STR_TO_EXPR_TAG);
	push_quantum(SECONDARY_TAG);
	
	new_top=top_estack;
	
	push_internal_simplify(top_estack);
	
	delete_between(old_top, new_top);
}

//Determine if the Robot is ON and Connected Properly
void ext_CHKBOT(void)
{
	Access_AMS_Global_Variables;
	volatile BOOL dlg;
	
	if(remaining_element_count(top_estack)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	dlg=ERD_notice(OO_AbsoluteGet(OO_FIRST_STRING+XR_ShortAppName), (UCHAR*)OO_AbsoluteGet(OO_FIRST_STRING+XR_RobotDetection));
	
	TRY
		ext_RSTLNK();
		ext_CSD();
		push_quantum(TRUE_TAG);
		if(dlg)ERD_dismissNotice();
	ONERR
		push_quantum(FALSE_TAG);
		if(dlg)ERD_dismissNotice();
		DlgNotice(OO_AbsoluteGet(OO_FIRST_STRING+XR_ShortAppName), OO_AbsoluteGet(OO_FIRST_STRING+XR_DetectionFailed));
	ENDTRY
}

void ext_DistCal(void)
{
	Access_AMS_Global_Variables;
	EStackIndex old_top=top_estack;
	
	if(remaining_element_count(old_top)) ER_throw(TOO_MANY_ARGS_ERROR);
	
	TRY	
		ext_SFF();
		estack_to_ushort(top_estack, &gDistanceCalibration);
	FINALLY
		top_estack=old_top;
	ENDFINAL
}

//expects 1 integer estack argument: distance/units
//make sure calibration has happened.
void ext_Drive(void)
{
	Access_AMS_Global_Variables;
	EStackIndex old_top=top_estack;
	ELEMENT_COUNT ecount;
	long arg;
	
	ecount=remaining_element_count(top_estack);
	
	if(!ecount) ER_throw(TOO_FEW_ARGS_ERROR);
	if(ecount>1) ER_throw(TOO_MANY_ARGS_ERROR);
	
	TRY	
		push_ulong_to_integer(gDistanceCalibration);
		push_quantum(MULTIPLY_TAG);
	//the following two tags force the anser to be an exact integer... so it works nice with GetLongArg
		push_quantum(RATIONALIZE_TAG);	//RATIONALIZE_TAG = exactP = exact(
		push_quantum(GREATEST_INT_TAG);	//GREATEST_INT_TAG = intP = int(
		
		push_quantum(END_TAG);
		push_simplify(top_estack-1);
			
		if(is_negative(top_estack))
		{
			push_quantum(END_TAG);
			push_negate(top_estack-1);
		 	ext_TBB();
		}
		else
		{
			ext_TFF();
		}
		
		/*arg=GetLongArg(top_estack,0, ULONG_MAX);

		push_quantum(END_TAG);
		
		if(arg<0)
		{//reverse
			arg=-arg;
			push_ulong_to_integer(arg);
			ext_TBB();
		}
		else
		{//forward
			push_ulong_to_integer(arg);
			ext_TFF();
		}*/
	
	FINALLY
		top_estack=old_top;
	ENDFINAL
}

//expects 1 integer estack argument: degrees
//make sure calibration has happened.
//calibration distance*3=distance around circle...
void ext_Turn(void)
{
	Access_AMS_Global_Variables;
	ELEMENT_COUNT ecount;
	EStackIndex old_top=top_estack;
	long arg;
	char buff[200];

	ecount=remaining_element_count(top_estack);
	
	if(!ecount) ER_throw(TOO_FEW_ARGS_ERROR);
	if(ecount>1) ER_throw(TOO_MANY_ARGS_ERROR);
	
	TRY		
		push_ulong_to_integer(gDistanceCalibration);
		push_quantum(MULTIPLY_TAG);
		push_ushort_to_integer(360);
		push_quantum(DIVIDE_TAG);
	//the following two tags force the anser to be an exact integer... so it works nice with GetLongArg
		push_quantum(RATIONALIZE_TAG);	//RATIONALIZE_TAG = exactP = exact(
		push_quantum(GREATEST_INT_TAG);	//GREATEST_INT_TAG = intP = int(
		push_simplify(top_estack);
		
		arg=GetLongArg(top_estack,0, ULONG_MAX);
		
		push_quantum(END_TAG);
		
		if(arg<0)
		{//counterclockwise
			arg=-arg;
			push_long_to_integer(arg);
			ext_TBF();
		}
		else
		{//clockwise
			push_long_to_integer(arg);
			ext_TFB();
		}

	FINALLY
		top_estack=old_top;
	ENDFINAL
}

void ext_Hitec(void)
{//TODO; set an internal flag to tell the other fuctions how to react rather than reprogram the robot.
	Access_AMS_Global_Variables;
	
	EStackIndex old_top=top_estack;

	TRY
		push_quantum(END_TAG);
		push_ushort_to_integer(255);
		ext_CRF();
		
		push_quantum(END_TAG);
		push_ushort_to_integer(255);
		ext_CLB();
		
		push_quantum(END_TAG);
		push_ushort_to_integer(0);
		ext_CRB();
		
		push_quantum(END_TAG);
		push_ushort_to_integer(0);
		ext_CLF();
	FINALLY
		top_estack=old_top;
	ENDFINAL
}

//replacement for tios GetValue
/*
	Less error checking is done... use push_simplify before calling
	I wrote this routine primarily because the AMS routines do not
	seem to handle bases, or any value larger than a USHORT       
	
	this routine may throw an error
*/
static unsigned long GetLongArg(EStackIndex index, unsigned long rLow, unsigned long rHigh)
{
	Quantum tag=*index;
	register short quantum;	//number of quantums
	register unsigned long result=0;
	
	if(tag==SECONDARY_TAG)
	{//handle bin and hex numbers
		tag=*--index;
		if(tag!=BIN_NUM_TAG && tag!=HEX_NUM_TAG) ER_throw(ER_DATATYPE);
		tag=*--index;
	}
	
	quantum=*(--index);
	
	if(tag!=NONNEGATIVE_INTEGER_TAG && tag!=NEGATIVE_INTEGER_TAG) ER_throw(ER_DATATYPE);
		
	if(quantum>4) ER_throw(ER_DOMAIN);
	
	while(quantum--)
	{
		result=(result<<8) + *(--index);
	}
	
	result=tag==NONNEGATIVE_INTEGER_TAG?result:-result;
	
	if(result>rHigh)ER_throw(ER_DOMAIN);
	if(result<rLow)ER_throw(ER_DOMAIN);
	
	return result;
}
