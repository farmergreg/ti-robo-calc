echo off
call clean
del RoboCalc89\* /Q
del "RoboCalc92+"\* /Q
rd RoboCalc89
rd "RoboCalc92+"
md RoboCalc89
md RoboCalc92+
copy *.c RoboCalc89
copy *.c "RoboCalc92+"
copy *.h RoboCalc89
copy *.h "RoboCalc92+"
copy *.r RoboCalc89
copy *.r "RoboCalc92+"
copy *92p.FSP "RoboCalc92+"
copy *89.FSP RoboCalc89
copy clean.bat RoboCalc89
copy clean.bat "RoboCalc92+"
