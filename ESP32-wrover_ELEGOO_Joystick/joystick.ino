
#define VRX_PIN  36 // ESP32 pin GIOP36 (ADC0) connected to VRX pin
#define VRY_PIN  39 // ESP32 pin GIOP39 (ADC0) connected to VRY pin
#define SW_PIN   18 // ESP32 pin GIOP17 connected to SW  pin


#include <ezButton.h>
ezButton button(SW_PIN);


int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
int buttonValue = 0;

void setup() {
  Serial.begin(115200) ;
   button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop();

  // read X and Y analog values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  buttonValue = button.getState();


  if (button.isPressed()) {
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
    // TODO do something here
  }

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(valueX);
  Serial.print(", y = ");
  Serial.println(valueY);
  Serial.print("BV: ");
  Serial.println(buttonValue);
  delay(200);
}