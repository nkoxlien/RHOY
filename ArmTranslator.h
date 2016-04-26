/****************************************
*
* Author: Nick Koxlien
*
*****************************************/

#ifndef ARM_TRANSLATOR_H__
#define ARM_TRANSLATOR_H__


#include "HandDisplay.h"
#define MAXVAL 2400
#define MINVAL 600

class ArmTranslator{


	public: 
		ArmTranslator();
		int GetMotor1Value(int x);
		int GetMotor2Value(int y, int z);
		int GetMotor3Value(int y, int z);
		
};

#endif //ARM_TRANSLATOR_H__
