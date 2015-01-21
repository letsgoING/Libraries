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


#include "Arduino.h"

#ifndef _ANALOGBTN_
#define _ANALOGBTN_


class AnalogButton
{
	private:
		bool _stateSwitch;
	
		int	_debounceTime,
			_button,
			_analogIN;

		float _lastPressButton,
			  _lastPressSwitch;


	public:
	//Konstruktoren
	//******************************************************************
		AnalogButton(int Button, int AnalogPin, int debounceTime);
		AnalogButton(int Button, int AnalogPin);
		AnalogButton(int Button);
		
	//setter
	//******************************************************************
		void setDebounceTime(int DebounceTime);
		void setSwitchState(bool state);
		
	//getter
	//******************************************************************
		void startButton();
		bool getButton();
		bool getButtonDebounced();
		bool getSwitch();
		bool getSwitchDebounced();

};

#endif;