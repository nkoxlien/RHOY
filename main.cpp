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

	return(0);
}
