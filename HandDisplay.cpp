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
