/**************************************************
***	Project Title: Robo Calc (robocalc)			***
***	Author: Greg Dietsche						***
***	Date:	11/21/2002							***
***	Description: An Application designed to		***
*** 			 Simplify the development of	***
***				 programs for the Norland		***
***				 Research Robot					***
***************************************************/

#ifndef _EXTENSIONS_H_
#define _EXTENSIONS_H_
	void ext_ABOUTRC(void);
	void ext_ROBOCALC(void);
	
	void ext_CHKBOT(void);
	
	void ext_Hitec(void);	//calibrate the robot for Hitec servo instead of the standard GWS servos
	
	void ext_CLB(void);	//Calibrate Left Backwards
	void ext_CLF(void);	//Calibrate Left Forewards
	void ext_CRB(void);	//Calibrate Right Backwards
	void ext_CRF(void);	//Calibrate Right Forewards
	void ext_CS (void);	//Check Switch
	void ext_CSD(void);	//Calibrate Set Defaults
	void ext_CSN(void);	//Calibrate Defaults

//Reset The Link Interface
void ext_RSTLNK(void);

//Measured Distance Movement and Calibration
void ext_DistCal(void);
void ext_Drive(void);
void ext_Turn(void);

//Switch Only
	void ext_SBB(void);
	void ext_SBF(void);	
	void ext_SBN(void);
	void ext_SFB(void);
	void ext_SFF(void);
	void ext_SFN(void);
	void ext_SNB(void);
	void ext_SNF(void);
	void ext_SNN(void);

//Timer Only	
	void ext_TBB(void);
	void ext_TBF(void);	
	void ext_TBN(void);
	void ext_TFB(void);
	void ext_TFF(void);
	void ext_TFN(void);
	void ext_TNB(void);
	void ext_TNF(void);
	void ext_TNN(void);

//Timer, or Switch
	void ext_TSBB(void);
	void ext_TSBF(void);	
	void ext_TSBN(void);
	void ext_TSFB(void);
	void ext_TSFF(void);
	void ext_TSFN(void);
	void ext_TSNB(void);
	void ext_TSNF(void);
	void ext_TSNN(void);
	
#endif
