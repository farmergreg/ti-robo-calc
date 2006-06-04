/**************************************************
***	Project Title: Robo Calc (robocalc)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
***	Description: An Application designed to		***
*** 			 Simplify the development of	***
***				 programs for the Norland		***
***				 Research Robot					***
***************************************************/

#ifndef __OO_H__
#define __OO_H__

//Application Frame Object Attribute Data Slots
//#define OO_PROTECTION_ACTIVE	(OO_FIRST_APP_ATTR + 0)		//pointer to BOOL AntiCrashInstalled (READ ONLY)
//#define OO_LEAK_WATCH_END		(OO_FIRST_APP_ATTR + 1)		//DWORD export_LeakWatchEnd(void);

//#define LAST_USED_OO	OO_LEAK_WATCH_END
//#define FIRST_USED_OO	OO_PROTECTION_ACTIVE
//#define NUM_OO_USED	(LAST_USED_OO - FIRST_USED_OO + 1)


//Public Function Prototypes
AppID GetMyAppID(void);
void *OO_AbsoluteGet(ULONG selector);
BOOL OO_AbsoluteSet(ULONG selector, void *value);

#endif
