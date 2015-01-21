
	//Konstruktoren
	//******************************************************************
	Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin, uint8_t m1IRpin, uint8_t m2IRpin);
	Drive (uint8_t m1SpeedPin, uint8_t m2SpeedPin, uint8_t m1DirPin, uint8_t m2DirPin);
	Drive ();



	//Fahre-Befehle
	//******************************************************************
	
	//Fahre gerade aus
	void drive(uint8_t driveSpeed, bool driveDirection);
	
	//Fahre Strecke gerade aus
	void driveDistance(uint8_t driveDistance, uint8_t driveSpeed, bool driveDirection);
	
	//Fahre Kurve
	void driveCurve(uint8_t driveDirectionLR, uint8_t driveSpeed, bool driveDirectionFB);
	
	//Fahre Distanz Kurve
	void driveCurveDistance(uint8_t driveDistance, uint8_t driveDirectionLR, uint8_t driveSpeed, bool driveDirectionFB);
	
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
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	

	//Motor-Ansteuerung
	//*******************************************************************
	void setMotor(uint8_t Speed_left, uint8_t Speed_right, bool Direction_left, bool Direction_right);


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