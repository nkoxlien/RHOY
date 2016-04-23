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
};

#endif //HAND_DISPLAY_H__
