/*********************************************
* HandDisplay.cpp
* Author: Nick Koxlien
*
* Deals with translating a quadrant to a value
* from 600 - 2400 for the motors
**********************************************/

#include "ArmTranslator.h"


ArmTranslator::ArmTranslator(){};


int ArmTranslator::GetMotor1Value(int x){
	
	int value, resolution;
	resolution = RESOLUTION;
	value = (x-1) * (2400 -600) / (RESOLUTION - 1) + 600;
	return 	value;
}

int ArmTranslator::GetMotor2Value(int y, int z){

	return 0;
}

int ArmTranslator::GetMotor3Value(int y, int z){

	return 0;
}
