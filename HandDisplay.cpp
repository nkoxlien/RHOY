/*********************************************
* HandDisplay.cpp
* Author: Nick Koxlien
*
* Detects a hand and prints the x,y, and z
* coordinates to the console
**********************************************/


#include "HandDisplay.h"




HandDisplay::HandDisplay(xn::Context& context ):
m_HandTracker(context)
{}

XnStatus HandDisplay::Init(){

	return m_HandTracker.Init();
}

XnStatus HandDisplay::Run(){

	XnStatus rc = m_HandTracker.Run();

	if(rc != XN_STATUS_OK){

		return rc;
	}	

	return rc;

}

int HandDisplay::getQuadrant(XnPoint3D point){
	int xLevel, yLevel, zLevel;
	
	if((xLevel = getXLevel(point.X)) == 0){
		printf("XLevel out of range\n");
	}

	if((yLevel = getYLevel(point.Y)) == 0){

		printf("YLevel out of range\n");
	}

	if((zLevel = getZLevel(point.Z)) == 0){

		printf("ZLevel out of range\n");
	}
}

int HandDisplay::getXLevel(float x){
	
	if(x > 750 || x < -750){
		
		return 0;	
	}

	if(x > 233){
		return 3;
	}	
	
	if(x > -233){
		return 2;
	}
	
	return 1;
}

int HandDisplay::getYLevel(float y){
	
	if(y > 450 || y < -450){

		return 0;
	}

	if(y > 150){
		return 1;
	}
	
	if(y > -150){
		return 2;
	}

	return 3;
}

//Base is 1000, closest is 600, farthest 1400
int HandDisplay::getZLevel(float Z){

}
