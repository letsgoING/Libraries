#include <LGI_QTouch.h>


QTouchSlider Slider(0, 2, 4);

void setup() {

  Serial.begin(9600);

  Slider.init();

  Serial.print("  Offset 3: ");
  Serial.print(Slider.getOffset(1));
  Serial.print("  Offset 4: ");
  Serial.print(Slider.getOffset(2));
  Serial.print("  Offset 5: ");
  Serial.println(Slider.getOffset(3));
  Serial.print("\n\n");

}

void loop() {

  Serial.print("SliderPos: ");
  Serial.println(Slider.getTouchPosition());

  delay(50);
}



