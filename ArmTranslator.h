/****************************************
*
* Author: Nick Koxlien
*
*****************************************/

#ifndef ARM_TRANSLATOR_H__
#define ARM_TRANSLATOR_H__

class ArmTranslator{


	public: 
		ArmTranslator();
		int GetMotor1Value(int quadrant);
		int GetMotor2Value(int quadrant);
		int GetMotor3Value(int quadrant);
		int GetMotor4Value(int quadrant);
		int GetMotor5Value(int quadrant);	
		
	private:
		int m_rResolution;
}

#endif //ARM_TRANSLATOR_H__
