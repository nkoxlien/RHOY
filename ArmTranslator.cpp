/*********************************************
* HandDisplay.cpp
* Author: Nick Koxlien
*
* Deals with translating a quadrant to a value
* from 600 - 2400 for the motors
**********************************************/

#include "ArmTranslator.h"


ArmTranslator::ArmTranslator(){};


int GetMotor1Value(int x){
	
	int value;
	value = (((x-1)/(RESOLUTION-1)) * 1800) + 600;
	
	return 	value;
}

int GetMotor2Value(int y, int z){

	return 0;
}

int GetMotor3Value(int y, int z){

	return 0;
}
