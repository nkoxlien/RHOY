/*********************************************
* HandDisplay.cpp
* Author: Nick Koxlien
*
* Initializes the Hand Tracker and given the 
* XnPoint3D of the hand returns the quadrant in
* 3D space that the hand is currently in 
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

int HandDisplay::GetQuadrant(XnPoint3D point){
	int xLevel, yLevel, zLevel, quadrant;
	
	if((xLevel = getXLevel(point.X)) == 0){
		printf("XLevel out of range\n");
		return 0;
	}

	if((yLevel = getYLevel(point.Y)) == 0){

		printf("YLevel out of range\n");
		return 0;
	}

	if((zLevel = getZLevel(point.Z)) == 0){

		printf("ZLevel out of range\n");
		return 0;
	}

	quadrant = (xLevel + (RESOLUTION * (yLevel - 1)) + ((RESOLUTION * RESOLUTION) * (zLevel - 1)));
	
	return quadrant;	
}

int HandDisplay::getXLevel(float x){
	
	int resLength, level;
	
	if(x > MAXX || x < MINX){
		
		return 0;	
	}

	resLength = (MAXX - MINX) / RESOLUTION;

	for(int i = 1; i <= RESOLUTION; i++){
	
		if( x > (MAXX - (i * resLength))){
			level = RESOLUTION - (i-1);
			return level; 
		}			
	}

	return 0;
	
}

int HandDisplay::getYLevel(float y){
	
	int resLength, level;
	
	if(y > MAXY || y < MINY){
		
		return 0;	
	}

	resLength = (MAXY - MINY) / RESOLUTION;

	for(int i = 1; i <= RESOLUTION; i++){
	
		if( y > (MAXY - (i * resLength))){
			level = i; 
			return level;
		}			
	}
	
	return 0;
		
}

int HandDisplay::getZLevel(float Z){
	
	int resLength, level;
	
	if(z > MAXZ || z < MINZ){
		
		return 0;	
	}

	resLength = (MAXZ - MINZ) / RESOLUTION;

	for(int i = 1; i <= RESOLUTION; i++){
	
		if( z > (MAXZ - (i * resLength))){
			level = i;
			return level; 
		}			
	}
	
	return 0;
}
