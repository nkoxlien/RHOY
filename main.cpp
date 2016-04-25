/*********************************************************
* This application tracks a user's hand and prints out the
* x, y, and z coordinates
*
* Author: Nick Koxlien
*********************************************************/

#include "HandDisplay.h"

#define SAMPLE_XML_PATH "../../Config/SamplesConfig.xml"


xn::Context		g_context;
xn::ScriptNode		g_scriptNode;

int main(int argc, char* argv[]){
	
	XnUserID currentID;
	XnStatus rc;
	xn::EnumerationErrors errors;

	rc = g_context.InitFromXmlFile(SAMPLE_XML_PATH, g_scriptNode, &errors);
	
	if (rc == XN_STATUS_NO_NODE_PRESENT){
                XnChar strError[1024];
                errors.ToString(strError, 1024);
                printf("%s\n", strError);
                return (rc);
        }

	else if (rc != XN_STATUS_OK){
                printf("Open failed: %s\n", xnGetStatusString(rc));
                return (rc);
        }


	HandDisplay display(g_context);	

	rc = display.Init();
	
	if(rc != XN_STATUS_OK){
		
		printf("Display init failed: %s\n", xnGetStatusString(rc));
		return(1);
	}

	
	rc = display.Run();

	if(rc != XN_STATUS_OK){

		printf("Display run failed: %s\n", xnGetStatusString(rc));
		return(1);
	}

	while(!xnOSWasKeyboardHit()){

		XnUserID ID;
		rc = g_context.WaitAnyUpdateAll();
		if (rc != XN_STATUS_OK){

			printf("UpdateData failed: %s\n", xnGetStatusString(rc));
			continue;
		}
		
		if((ID = display.m_HandTracker.GetID()) != 0){
			if( currentID == 0 ){
				currentID = ID;
			}	
			
			else if( currentID != ID){

				continue;
			}
			typedef TrailHistory			History;
			typedef History::ConstIterator 		HistoryIterator;
			typedef Trail::ConstIterator		TrailIterator;


			const TrailHistory&	history = display.m_HandTracker.GetHistory();	
			const HistoryIterator hend = history.End();
			HistoryIterator hit = history.Begin();

			const Trail& trail = hit -> Value();
			const TrailIterator tit = trail.Begin();
			
			XnPoint3D	point = *tit;
		

			printf("User ID = %i\n", ID);
			printf("X = %.2f, Y = %.2f, Z = %.2f\n", point.X, point.Y, point.Z);
		}
		
		else{
		 currentID = 0;
		}
	}

	return(0);
}
