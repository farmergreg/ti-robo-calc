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


//used when this application is not active to retrieve attributes
AppID GetMyAppID(void)
{
	return EV_getAppID((UCHAR*)APP_INTERNAL);
}

//retrieves an attribute from this applications frame under nearly any circumstance
void *OO_AbsoluteGet(ULONG selector)
{
	return OO_GetAppAttr(GetMyAppID(), selector);
}

/*
BOOL OO_AbsoluteSet(ULONG selector, void *value)
{
	return OO_SetAppAttr(GetMyAppID(), selector, value);
}
*/
