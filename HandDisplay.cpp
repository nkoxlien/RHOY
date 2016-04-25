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

}

int HandDisplay::getYLevel(float y){

}

int HandDisplay::getZLevel(float Z){

}
