#pragma config(Sensor, S2,		 touchSensor1,	 sensorTouch)
#pragma platform(NXT)
/* DON'T TOUCH THE ABOVE CONFIGURATION */


#include "motor.c"
#include "constants.h"

#define UnloadMotor motorB
#define TransportMotor motorC

void conveyor_move(int payload);
void moveToPrinterAndSendJob(int letter);
void unload();

void clearInbox(){
	// Clear the message inbox
	for(int i=0; i<100; i++)
		ClearMessage();
}

task listenToBluetooth(){
	int job;
	int receiver, method, payload;
	while(true)
	{
		receiver = messageParm[0];
		method = messageParm[1];
		payload = messageParm[2];
		if(receiver != 0 || method	!= 0 || payload != 0){
			PlaySound(soundBlip);
			switch(method){
			case CONVEYOR_JOB_START:
				nxtDisplayBigTextLine(2,"Job: %d", payload);
				sendMessageWithParm(WEBSERVER, STT_JOB_STARTED, 0);
				wait1Msec(500);
				sendMessageWithParm(LOADER, LOADER_LOAD_PLATE , 0);
				job = payload;
				break;
			case CONVEYOR_MOVE:
				conveyor_move(payload);
				break;
			case CONVEYOR_PLATE_LOADED:
				nxtDisplayBigTextLine(4,"Sent:%d", job);
				sendMessageWithParm(WEBSERVER, STT_MOVING_TO_PRINTER, 0);
				moveToPrinterAndSendJob(job);
				break;
			case CONVEYOR_JOB_DONE:
				sendMessageWithParm(WEBSERVER, STT_MOVING_TO_DELIVERY, 0);
				unload();
				sendMessageWithParm(WEBSERVER, STT_JOB_DONE, 0);
				break;
			default:
				PlaySound(soundException);
				// method not supported
			}
			ClearMessage();
		}
		wait1Msec(500);
	}
}

// Move conveyor to origin
void moveToStock(){
	while(true)
	{
		if(SensorValue[touchSensor1] == 0){
			motor[TransportMotor] = 40;
		}
		else {
			break;
		}
	}
	motor[TransportMotor] = 0;
}

// Unload the plate
const float Printer2Delivery = 28.5; // nipples
void unload()
{
	driveNipple(Printer2Delivery, -20, TransportMotor);
	sendMessageWithParm(WEBSERVER, STT_UNLOADING, 0);
	int power = 3;
	driveDegree(30, -power, UnloadMotor);
	wait1Msec(200);
	driveDegree(30, power, UnloadMotor);
}

// Procedure called remotely by printer
void conveyor_move(int payload)
{
	int speed = -15;
	if(payload<0)
		speed = abs(speed);
	int gearTeeth = abs(payload);
	driveNipple(gearTeeth, speed, TransportMotor);
}

const float Origin2Printer = 26.1;
void moveToPrinterAndSendJob(int letter){
	// move to printer
	driveNipple(Origin2Printer, -20, TransportMotor);
	// tell printer what should be done
	sendMessageWithParm(PRINTER, PRINTER_PRINT, letter);
}


task main()
{
	clearInbox();
	StartTask(listenToBluetooth);
	moveToStock();


	while(true){wait10Msec(100);}
	//unload();
	return;
}
