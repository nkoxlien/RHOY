/*********************************************************
* This application tracks a user's hand and prints out the
* x, y, and z coordinates
*
* Author: Nick Koxlien
*********************************************************/

#include "HandDisplay.h"
#include "ArmTranslator.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define SAMPLE_XML_PATH "../../Config/SamplesConfig.xml"


xn::Context		g_context;
xn::ScriptNode		g_scriptNode;


int socketStuff(float x, float y, float z);
//int connect();

void error(char *msg){

	perror(msg);
	exit(0);
}

int main(int argc, char* argv[]){
	
	XnUserID currentID;
	XnStatus rc;
	xn::EnumerationErrors errors;
	
	//int sockfd = connect();

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
	ArmTranslator translator;	

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
			int quadrant, xLevel, yLevel, zLevel;
			int motor1Val, motor2Val, motor3Val;
	
			if((xLevel = display.getXLevel(point.X)) < 1){
				printf("X-Level out of range\n");
				continue;
			}
	
			if((yLevel = display.getYLevel(point.Y)) < 1){
				printf("Y-Level out of range\n");
				continue;
			}
			/*if((zLevel = display.getXLevel(point.Z)) < 1){
				printf("Z-Level out of range\n");
				continue;
			}*/
			
			if((motor1Val = translator.GetMotor1Value(xLevel)) < 600){
				printf("Error Translating value for motor 1\n");
				continue;
			}

			if(motor1Val > 2400){
				
				printf("Error Translating value for motor 1\n");
				continue;
			}
			
			
			//printf("User ID = %i\n", ID);
			//printf("X = %.2f, Y = %.2f, Z = %.2f\n", point.X, point.Y, point.Z);
			socketStuff(point.X, point.Y, point.Z);
			//printf("X-Level = %i\n", xLevel);
			//printf("MOTOR 1 VALUE: %i\n", motor1Val);
		}
		
		else{
			currentID = 0;
		}
	}

	return(0);
}

int socketStuff(float x, float y, float z){

    
    int sockfd;
    struct addrinfo hints, *result, *rp;
    int rv, s;
    ssize_t nread;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    
    s = getaddrinfo("192.168.1.3", "22", &hints, &result);
    
    if(s != 0){
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
  
    for(rp = result; rp != NULL; rp = rp->ai_next){
	sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if(sockfd == -1)
	    continue;
	if(connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1){
	    
	    printf("Connected!!\n");
	    //success
	    break;
	}
	close(sockfd);
    } 
    
    if(rp == NULL){

	fprintf(stderr, "Couldn not connect\n");
	exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    
    char xSend[4]; 
    
    char ySend[4];

    char zSend[4];
 
    xSend[3]  = (char)(0x00);
    xSend[2]  =	(char)(0x00); 
    xSend[1]  =	(char)(((((short)x) & 0xff00) >> 8));
    xSend[0]  =	(char)(((short)x) & 0x00ff);
    
    ySend[3]  = (char)(0x00);
    ySend[2]  =	(char)(0x01); 
    ySend[1]  =	(char)((((short)y) & 0xff00) >> 8);
    ySend[0]  =	(char)(((short)y) & 0x00ff);
    
    zSend[3]  = (char)(0x00);
    zSend[2]  =	(char)(0x02); 
    zSend[1]  =	(char)((((short)z) & 0xff00) >> 8);
    zSend[0]  =	(char)(((short)z) & 0x00ff);
     
 
    if(send(sockfd, xSend, 4, 0) < 0){

	fprintf(stderr, "partial/failed write\n");
	exit(EXIT_FAILURE);
    } 
    printf("Wrote X!!\n");
    
    if(send(sockfd, ySend, 4 , 0) < 0){

	fprintf(stderr, "partial/failed write\n");
	exit(EXIT_FAILURE);
    } 
    printf("Wrote Y!!\n");


    if(send(sockfd, zSend, 4, 0) < 0){

	fprintf(stderr, "partial/failed write\n");
	exit(EXIT_FAILURE);
    } 
    printf("Wrote Z!!\n");
    close(sockfd);
    return(0);

}

/*int connect(){


    int sockfd;
    struct addrinfo hints, *result, *rp;
    int rv, s;
    ssize_t nread;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    
    s = getaddrinfo("192.168.1.105", "20000", &hints, &result);
    
    if(s != 0){
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
  
    for(rp = result; rp != NULL; rp = rp->ai_next){
	sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if(sockfd == -1)
	    continue;
	if(connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1){
	    
	    printf("Connected!!\n");
	    //success
	    break;
	}
	close(sockfd);
    } 
    
    if(rp == NULL){

	fprintf(stderr, "Couldn not connect\n");
	exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);
}*/
