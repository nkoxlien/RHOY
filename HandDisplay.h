#ifndef _HAND_DISPLAY_H__
#define _HAND_DISPLAY_H__

#include "NiHandTracker.h"

class HandDisplay{


	public: 
		XnStatus Init();
		XnStaus Run();
		
	protected:
		HandDisplay(xn::Context context);

	private: 
		
		HandTracker m_HandTracker;
	
};

