/*
Klasse mit Fahrbefehlen für Cherokey 4WD
Funktionen:
- Fahre gerade aus
- Fahre Strecke gerade aus
- Fahre Kurve
- Fahre Kurve Strecke
- Drehe
- Drehe Winkel
- Stoppe Fahrzueg
- Bremse Fahrzeug ab
- Starte Messung
- Messe Strecke
	
24.09.2014 Anian Bühler
*/

#include "Arduino.h"


#ifndef _LGIDRIVE_
#define _LGIDRIVE_

class Drive
{
private:
	//Pins
	uint8_t m1SpeedPin,		//PWM1
			m2SpeedPin, 	//PWM2
			m1DirPin, 		//DirectionPin 1
			m2DirPin, 		//DirectionPin 2 
			m1IRpin, 		// Encoder Interrupt Pin1
			m2IRpin;		// Encoder Interrupt Pin1
			
	bool	globalDirM1,
			globalDirM2;

	

public:
	//Konstruktoren
	//******************************************************************
	Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin, uint8_t m1IRpin, uint8_t m2IRpin);
	Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin);
	Drive ();

	//Timer
	//******************************************************************
	void wait(int time);

	//setter
	//******************************************************************
	void resetCounterLeft();
	void resetCounterRight();
	
	//getter
	//******************************************************************
	int getIncementLeft();
	int getIncementRight();
	void countCounterLeft();
	void countCounterRight();

	//Fahre-Befehle
	//******************************************************************
	
	//Fahre gerade aus
	void drive(uint8_t driveSpeed, bool driveDirection);
	
	//Fahre Strecke gerade aus
	void driveDistance(int driveDistance, uint8_t driveSpeed, bool driveDirection);
	
	//Fahre Kurve
	void driveCurve(int driveDirectionLR, int driveSpeed);
	
	//Fahre Distanz Kurve
	void driveCurveDistance(int driveDistance, int driveDirectionLR, int driveSpeed);
	
	//Drehe
	void turn(uint8_t turnSpeed, bool turnDirection);
	
	//Drehe Winkel
	void turnAngle(uint8_t turnAngle, uint8_t turnSpeed, bool turnDirection);
	
	//Stoppe Fahrzeug
	void stopp();
	
	//Bremse Fahrzeug
	void brake();
	
	//Starte Messung (Reset)
	void startMeasure();
	
	//Werte Messung aus
	int getDistance();
	
	//Gebe Messwert zurück
	int getDistanceCM();
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	

	//Motor-Ansteuerung
	//*******************************************************************
	void setMotor(uint8_t Speed_left, uint8_t Speed_right, bool Direction_left, bool Direction_right);

};

#endif;