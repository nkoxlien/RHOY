/****************************************
*
* Author: Nick Koxlien
*
*****************************************/


#ifndef HAND_DISPLAY_H__
#define HAND_DISPLAY_H__

#include "NiHandTracker.h"

class HandDisplay{


	public:
 
		virtual XnStatus Init();
		virtual XnStatus Run();
		HandDisplay(xn::Context& context);
		HandTracker m_HandTracker;
		int getQuadrant(XnPoint3D point);
		int getXLevel(float x);
		int getYLevel(float y);
		int getZLevel(float z);
};

#endif //HAND_DISPLAY_H__
