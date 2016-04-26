/****************************************
*
* Author: Nick Koxlien
*
*****************************************/


#ifndef HAND_DISPLAY_H__
#define HAND_DISPLAY_H__

#include "NiHandTracker.h"

#define RESOLUTION	3
#define MAXX		750
#define MINX		-750
#define MAXY		450
#define MINY		-450
#define MAXZ		1400
#define MINZ		600
			
class HandDisplay{


	public:
 
		virtual XnStatus Init();
		virtual XnStatus Run();
		HandDisplay(xn::Context& context);
		HandTracker m_HandTracker;
		int GetQuadrant(XnPoint3D point);
		int getXLevel(float x);
		int getYLevel(float y);
		int getZLevel(float z);
};

#endif //HAND_DISPLAY_H__
