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
- Setze Motor
	
24.09.2014 Anian Bühler
*/

#include "letsgoING_Drive.h"

#define debounceTime 1
//#define CHEROKEY 		//uncomment if Cherokey is used

#ifdef CHEROKEY
	#define _WheelDia   200  // ~~(PI*6,5cm Raddurchmesser)*10 (int mit Nachkommastelle)
	#define _Wheelbase  45  // 45,6 -> PI*Radstand in cm
	#define _Incements  20  //Incremente je Umdrehung
	#define _BrakeTime  100 //time for braking in ms
#else //ARDUROVER
	#define _WheelDia   100  // ~~(PI*3,2cm Raddurchmesser) *10 (int mit Nachkommastelle)
	#define _Wheelbase  40  // 40 -> PI*Radstand in cm
	#define _Incements  30  //Incremente je Umdrehung
	#define _BrakeTime  50 //time for braking in ms
#endif;

int 	countLeft  = 0,		//Encoder Counter 1
		countRight = 0;		//Encoder Counter 1
float 	timeOutLeft  = 0,	//Encoder TimeOut 1	
		timeOutRight = 0;	//Encoder TimeOut 2

void countCounterLeft();
void countCounterRight();
		
//Interruptserviceroutine fuer Encoder 
	//******************************************************************
	void ISREncoder1()
	{	
		countCounterLeft();
	}

	void ISREncoder2()
	{
		countCounterRight();
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//Konstruktoren
//******************************************************************
	Drive::Drive ()
	{
		this->m1SpeedPin = 10; 	//PWM1
		this->m2SpeedPin = 11;	//PWM2
		this->m1DirPin   = 9; 	//DirectionPin 1
		this->m2DirPin	 = 12; 	//DirectionPin 2 
		this->m1IRpin	 = 2; 	// Encoder Interrupt Pin1
		this->m2IRpin	 = 3;	// Encoder Interrupt Pin1

		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		
		attachInterrupt(0, ISREncoder1, CHANGE );
		attachInterrupt(1, ISREncoder2, CHANGE );
		

	}


	Drive::Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin)
	{
		this->m1SpeedPin = m1SpeedPin; 	//PWM1
		this->m2SpeedPin = m2SpeedPin;	//PWM2
		this->m1DirPin   = m1DirPin; 	//DirectionPin 1
		this->m2DirPin	 = m2DirPin; 	//DirectionPin 2 
		this->m1IRpin	 = 2; 			// Encoder Interrupt Pin1
		this->m2IRpin	 = 3;			// Encoder Interrupt Pin1
		
		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		
		attachInterrupt(0, ISREncoder1, CHANGE );
		attachInterrupt(1, ISREncoder2, CHANGE );
	}


	Drive::Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin, uint8_t m1IRpin, uint8_t m2IRpin)
	{		
		this->m1SpeedPin = m1SpeedPin; 	//PWM1
		this->m2SpeedPin = m2SpeedPin;	//PWM2
		this->m1DirPin   = m1DirPin; 	//DirectionPin 1
		this->m2DirPin	 = m2DirPin; 	//DirectionPin 2 
		this->m1IRpin	 = m1IRpin; 	// Encoder Interrupt Pin1
		this->m2IRpin	 = m2IRpin;		// Encoder Interrupt Pin1

		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1SpeedPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		pinMode(this->m1DirPin, OUTPUT);
		
		switch (m1IRpin)
		{
			case 2:
				attachInterrupt(0, ISREncoder1, CHANGE );
				break;
			case 3:
				attachInterrupt(1, ISREncoder1, CHANGE );
				break;
			case 21:
				attachInterrupt(2, ISREncoder1, CHANGE );
				break;
			case 20:
				attachInterrupt(3, ISREncoder1, CHANGE );
				break;
			case 19:
				attachInterrupt(4, ISREncoder1, CHANGE );
				break;
			case 18:
				attachInterrupt(5, ISREncoder1, CHANGE );
				break;
			default:
			attachInterrupt(0, ISREncoder1, CHANGE );
		}
		
		switch (m2IRpin)
		{
			case 2:
				attachInterrupt(0, ISREncoder2, CHANGE );
				break;
			case 3:
				attachInterrupt(1, ISREncoder2, CHANGE );
				break;
			case 21:
				attachInterrupt(2, ISREncoder2, CHANGE );
				break;
			case 20:
				attachInterrupt(3, ISREncoder2, CHANGE );
				break;
			case 19:
				attachInterrupt(4, ISREncoder2, CHANGE );
				break;
			case 18:
				attachInterrupt(5, ISREncoder2, CHANGE );
				break;
			default:
			attachInterrupt(1, ISREncoder2, CHANGE );
		}
		
	}	
	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//Timer
//******************************************************************
		void Drive::wait(int time)
		{
			uint32_t current = millis();
			while(current + time > millis());
		}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//setter
//******************************************************************
	void Drive::resetCounterLeft()
	{
		countLeft = 0;
	}

	void Drive::resetCounterRight()
	{
		countRight = 0;
	}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	
	
//getter
//******************************************************************
	int Drive::getIncementLeft()
	{
		return countLeft;//Encoder Counter 1
	}

	int Drive::getIncementRight()
	{
		return countRight;//Encoder Counter 2
	}

	void countCounterLeft()
	{
		if( millis() > timeOutLeft)
		{
			timeOutLeft = millis() + debounceTime;
			countLeft++;
		}
	}

	void countCounterRight()
	{
		if( millis() > timeOutRight)
		{
			timeOutRight = millis() + debounceTime;
			countRight++;
		}
	}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//Fahre-Befehle
//******************************************************************
	
	//Fahre gerade aus
	void Drive::drive(uint8_t driveSpeed, bool driveDirection)
	{  		
		setMotor(driveSpeed, driveSpeed, driveDirection, driveDirection);
	}
	
	//Fahre Strecke gerade aus
	void Drive::driveDistance(int driveDistance, uint8_t driveSpeed, bool driveDirection)
	{	
		
		int driven = 0;
		
		drive(driveSpeed, driveDirection);
		startMeasure();
		
		while(driven < driveDistance*10) //int mit einer Nachkommastelle
		{
			driven = getDistance();
			wait(2);
		}
  
		brake();
	}
	
	//Fahre Kurve
	void Drive::driveCurve(int driveDirectionLR, int driveSpeed)
	{
		
		int Dir1,  Dir2;
		int TempSpeed1 = driveSpeed + driveDirectionLR;
		int M1 = abs(TempSpeed1);
		
		int TempSpeed2 = driveSpeed - driveDirectionLR;
		int M2 = abs(TempSpeed2);
		
			Dir1 = 0;
			if(TempSpeed1 >= 0) 
				Dir1 = 1;
				
			Dir2 = 0;
			if(TempSpeed2 >= 0) 
				Dir2 = 1;
  
		setMotor(M1, M2, Dir1, Dir2);
	
	}
	
	//Fahre Distanz Kurve
	void Drive::driveCurveDistance(int driveDistance, int driveDirectionLR, int driveSpeed)
	{
	
		int driven = 0;
		
		driveCurve(driveDirectionLR, driveSpeed);
		startMeasure();
		
		while(driven < driveDistance*10) //int mit einer Nachkommastelle
		{
			driven = getDistance();
			wait(2);
		}
  
		brake();
	}
	
	
	//Drehe
	void Drive::turn(uint8_t turnSpeed, bool turnDirection)
	{
		setMotor(turnSpeed, turnSpeed, turnDirection, !turnDirection);
	}
	
	//Drehe Winkel
	void Drive::turnAngle(uint8_t turnAngle, uint8_t turnSpeed, bool turnDirection)
	{
	
		int driven   = 0;
		int Distance = _Wheelbase *abs(turnAngle)/360; 
	
		turn(turnSpeed, turnDirection);
		
		startMeasure();
		
		while(driven < Distance*10) //int mit einer Nachkommastelle
		{
			driven = getDistance();
			wait(2);
		}

		brake();
	}

	
	//Stoppe Fahrzeug
	void Drive::stopp()
	{
		setMotor(0, 0, 0, 0);
	}
	
	//Bremse Fahrzeug
	void Drive::brake()
	{	
		bool Dir1 = this->globalDirM1;
		bool Dir2 = this->globalDirM2;
		
		Dir1 = !Dir1;
		Dir2 = !Dir2;
		
		digitalWrite(this->m1DirPin, Dir1);
		digitalWrite(this->m2DirPin, Dir2);
		
		wait(_BrakeTime);

		setMotor(0, 0, !Dir1, !Dir2);
	}
	
	//Starte Messung (Reset)
	void Drive::startMeasure()
	{
		resetCounterLeft();
		resetCounterRight();
	}
	
	//Werte Messung aus
	int Drive::getDistance()
	{
		int Inc_Left  = getIncementLeft();
		int Inc_Right = getIncementRight();

		int Increment = (Inc_Left + Inc_Right) / 2;
		
		int Distance = _WheelDia * Increment / _Incements;	
		
		return Distance;
	}
	
	//Gebe Messwert zurück
	int Drive::getDistanceCM()
	{
		return getDistance() / 10;
	}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	

	
//Motor-Ansteuerung
//*******************************************************************
	void Drive::setMotor(uint8_t Speed_left, uint8_t Speed_right, bool Direction_left, bool Direction_right)
	{
		int setSpeed1 = constrain(map(Speed_left,0, 100, 80, 254), 0, 254);
		int setSpeed2 = constrain(map(Speed_right,0, 100, 80, 254), 0, 254);
		
		this->globalDirM1 = Direction_left;
		this->globalDirM2 = Direction_right;

		if(Speed_left == 0)
			setSpeed1 = 0;
		if(Speed_right == 0)
			setSpeed2 = 0;

		analogWrite(m1SpeedPin, setSpeed1);
		analogWrite(m2SpeedPin, setSpeed2);
		digitalWrite(m1DirPin, Direction_left);
		digitalWrite(m2DirPin, Direction_right);
	}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
