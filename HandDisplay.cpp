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


	while(!xnOSWasKeyboardHit()){
		typedef TrailHistory			History;
		typedef History::ConstIterator 		HistoryIterator;
		typedef Trail::ConstIterator		TrailIterator;


		const TrailHistory&	history = m_HandTracker.GetHistory();	
		const HistoryIterator hend = history.End();

		for(HistoryIterator hit = history.Begin(); hit != hend; ++hit){
			
	
			int numpoints = 0;
			const Trail&		trail = hit -> Value();
			
			const TrailIterator	tend = trail.End();
			for(TrailIterator	tit = trail.Begin(); tit != tend; ++tit){

				XnPoint3D	point = *tit;

				printf("X = %.2f, Y = %.2f, Z = %.2f\n", point.X, point.Y, point.Z);
			}
		}
	}

	return rc;
}
