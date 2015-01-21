/*
Klasse für die Nutzung zweier Taster an einem Analogeingang
    
5V--+----------
	|         |
	|         |
      /__|      /__|
     /   |S3   /   |S4
   _|_        _|_   
   | | 10k    | | 20k
   |_|		  |_|
	|          |
	|          |
	-----+-----+----- Ax
         |
        _|_           
        | | 10k    
        |_|		  
	     |
	     GND	 
		 
Werte für gedrückte Buttons: (5V, 10bit ADC)
Button 1 (10k): 	510
Button 2 (20k): 	340
Button 1+2    : 	610
Toleranz	  :		+/-20
		 
Anian Bühler 28.08.2014
*/


#include "LGI_AnalogButton.h"

//Konstruktoren
//******************************************************************
	AnalogButton :: AnalogButton (int Button, int AnalogPin, int debounceTime){
		this -> _button = Button;
		this -> _debounceTime = debounceTime;
		this -> _analogIN = AnalogPin;
		this -> _stateSwitch = 0;
		this -> _lastPressButton = 0;
		this -> _lastPressSwitch = 0;
	}

	AnalogButton :: AnalogButton (int Button, int AnalogPin){
		this -> _button = Button;
		this -> _debounceTime = 250;
		this -> _analogIN = AnalogPin;
		this -> _stateSwitch = 0;
		this -> _lastPressButton = 0;
		this -> _lastPressSwitch = 0;
	}

	AnalogButton :: AnalogButton (int Button){
		this -> _button = Button;
		this -> _debounceTime = 250;
		this -> _analogIN = 17;
		this -> _stateSwitch = 0;
		this -> _lastPressButton = 0;
		this -> _lastPressSwitch = 0;
	}

//setter
//******************************************************************

	//set debounce time
	void AnalogButton :: setDebounceTime(int DebounceTime){
		this -> _debounceTime = DebounceTime;
	}
	
	//set switch state (ON/OFF)
	void AnalogButton :: setSwitchState(bool state){
		this->_stateSwitch = state;
	}

//getter
//******************************************************************
	
	//-> waiting until button is pressed
	void AnalogButton :: startButton(){

	  switch(this -> _button){
	  
	  case 1:  //Button 1 is pressed (S3)
		while( !(analogRead(this -> _analogIN) > 490 && analogRead(this -> _analogIN) < 530));
		break;
		
	  case 2:  //Button 2 is pressed (S4)
		while( !(analogRead(this -> _analogIN) > 320 && analogRead(this -> _analogIN) < 360));
		break;
		
	  case 3:  // both Buttons are pressed
		while( !(analogRead(this -> _analogIN) > 590 && analogRead(this -> _analogIN) < 630));
		break; 
	  }
	}	
	
		
	//check is button is pressed
	bool AnalogButton :: getButton(){

		boolean state = 0;
		
		int analogVal = analogRead(this -> _analogIN);	//read analog value
			
		switch(this -> _button){ 
			
		case 1:  //Button 1 is pressed (S3)
		  if( analogVal > 490 && analogVal < 530 ) state = 1;
		  break;
			  
		case 2:  //Button 2 is pressed (S4)
		  if( analogVal > 320 && analogVal < 360 ) state = 1;
		  break;
			  
		case 3:  // both Buttons are pressed
		  if( analogVal > 590 && analogVal < 630 ) state = 1;
		  break;
			
		}

		return state;
	}

	
	//check is button is pressed (debounced)
	bool AnalogButton :: getButtonDebounced(){

		boolean state = 0;

		if( millis() > this -> _lastPressButton + this -> _debounceTime){ //debounce
			this -> _lastPressButton = millis();

			int analogVal = analogRead(this -> _analogIN);	//read analog value
			
			switch(this -> _button){ 
			
			case 1:  //Button 1 is pressed (S3)
			  if( analogVal > 490 && analogVal < 530 ) state = 1;
			  break;
			  
			case 2:  //Button 2 is pressed (S4)
			  if( analogVal > 320 && analogVal < 360 ) state = 1;
			  break;
			  
			case 3:  // both Buttons are pressed
			  if( analogVal > 590 && analogVal < 630 ) state = 1;
			  break;
			}
		 }

		return state;
	}
	
	
	//check if switch state has changed
	bool AnalogButton :: getSwitch(){

		int analogVal = analogRead(this -> _analogIN);	//read analog value
		  
		switch(_button){
		case 1:  //Button 1 is pressed (S3)
		  if( analogVal > 490 && analogVal < 530 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break;
		  
		case 2:  //Button 2 is pressed (S4)
		  if( analogVal > 320 && analogVal < 360 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break;
		  
		case 0:  // both Buttons are pressed
		  if( analogVal > 590 && analogVal < 630 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break; 
		} 
	  return this -> _stateSwitch;
	}
	
	
	//check if switch state has changed
	bool AnalogButton :: getSwitchDebounced(){

	  if( millis() > this -> _lastPressSwitch + this -> _debounceTime){ //debounce
		this -> _lastPressSwitch = millis();

		int analogVal = analogRead(this -> _analogIN);	//read analog value
		  
		switch(_button){
		case 1:  //Button 1 is pressed (S3)
		  if( analogVal > 490 && analogVal < 530 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break;
		  
		case 2:  //Button 2 is pressed (S4)
		  if( analogVal > 320 && analogVal < 360 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break;
		  
		case 0:  // both Buttons are pressed
		  if( analogVal > 590 && analogVal < 630 ) this -> _stateSwitch = !this -> _stateSwitch;
		  break; 
		} 
	  }  
	  return this -> _stateSwitch;
	}

	