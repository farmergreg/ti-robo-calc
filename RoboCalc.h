/**************************************************
***	Project Title: Robo Calc (robocalc)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
***	Description: An Application designed to		***
*** 			 Simplify the development of	***
***				 programs for the Norland		***
***				 Research Robot					***
***************************************************/

#ifndef _ROBOCALC_H_
#define _ROBOCALC_H_

//Version Control and Internal/External App Name
#define APP_VERSION "1.00"
#define APP_TITLE "RoboCalc"
#define APP_INTERNAL "rbot"

//#define DEBUG			//enable extra debugging code

#ifndef _89
#ifndef _92
	#error Please '#define _89' or '#define _92'
#endif
#endif

#ifdef _89
#ifdef _92
	#error '#define _89' and '#define _92' are mutually exclusive
#endif
#endif

#ifdef _89
	#define C(x,y)(x)
#endif
#ifdef _92
	#define C(x,y)(y)
#endif

//My own debuged replacment for TI's OS_NeedMinimumVersion macro
#define CheckAMS(frame, major, minor)								\
{																	\
   static BOOL _OSVersionOK_ = FALSE;								\
   if (! _OSVersionOK_)												\
   {																\
      if (((long const *)AMS_Global_Variables)[-1] < 1499 ||		\
          ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number	\
            < (((major) << 8) + (minor)))							\
         {															\
            MY_ACB(frame)->flags |= (ACB_JT_VERSION|ACB_DELETE);	\
            return;													\
         }															\
      else															\
         _OSVersionOK_ = TRUE;										\
   }																\
}

//Internal event IDs 
#define ACM_DoCustomMenu		(0x500 + 0)
#define ACM_Help				(0x500 + 1)


//This header requires certain other header files
#include "xr.h"		//technically part of this header file; isolated for ease of editing

char* About(void);

extern pFrame pAppObj;
const short AppIcon[];
const short DSIcon[];

#endif
