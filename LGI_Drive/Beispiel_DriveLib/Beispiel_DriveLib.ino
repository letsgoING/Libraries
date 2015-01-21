#include <letsgoING_Drive.h>

Drive Rover;


void setup() 
{
}

void loop() 
{ 
  //Fahre vorwärts
  Rover.drive(80, 1);
  Rover.wait(1000);
  Rover.stopp();
  
  
  //Fahre rückwärts
  Rover.drive(80, 0);
  Rover.wait(1000);
  Rover.stopp();
  
  
  //Fahre vorwärts Distanz
  Rover.driveDistance(20, 80, 1);
  Rover.wait(1000);
  
  //Fahre rückwärts Distanz
  Rover.driveDistance(20, 80, 0);
  Rover.wait(1000);
  
   //Fahre Kurve vorwärts
  Rover.driveCurve(40, 80, 1);
  Rover.wait(1000);
  Rover.stopp();
  Rover.wait(1000);
  
  //Fahre Kurve rückwärts
  Rover.driveCurve(40, 80, 0);
  Rover.wait(1000);
  Rover.stopp();
  Rover.wait(1000);
  
  //Fahre Kurve vorwärts Distanz
  Rover.driveCurveDistance(20, 40, 80, 1);
  Rover.wait(1000);
  
  //Fahre Kurve rückwärts Distanz
  Rover.driveCurveDistance(20, 40, 80, 0);
  Rover.wait(1000);
  
  //Drehe 
  Rover.turn(80, 1);
  Rover.wait(1000);
  Rover.stopp();
  Rover.wait(1000);
  
  //Drehe 
  Rover.turn(80, 0);
  Rover.wait(1000);
  Rover.stopp();
  Rover.wait(1000);
  
   //Drehe 
  Rover.turnAngle(90, 40, 1);
  Rover.wait(1000);
  
  //Drehe 
  Rover.turnAngle(90, 40, 0);
  Rover.wait(1000);
}

