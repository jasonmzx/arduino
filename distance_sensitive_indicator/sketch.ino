//Ultrasonic Sensor pins:

const int trigger_pin = 3;
const int echo_pin = 2;

//Passive buzzer pin:

const int buzzer = 12;

// The Liquid Crystal allows me to use the LCD display using high functionality
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

long duration;
long distance;

//Function to scroll various strings on my LCD display:

void scroll_text(String caption, int scroll_speed) {

  int caption_len = caption.length() - 10;

  for(int i = 0; i < caption_len; ++i){
    lcd.scrollDisplayLeft(); //Built-in which shift's the string by 1 char to the left. (Also clears the row automatically)
     delay(scroll_speed);
  }
  
}

//This function just generates the blinking characters at each edge of the caption:

void blink_border( String caption, int iteration, int scroll_speed, 
                  bool include_distance, int distance ){
  
  lcd.clear();
  lcd.setCursor(0, 0);

  for(int i = 0; i < iteration; ++i){
    lcd.clear();
    
    if((i & 0x01) == 0){
      lcd.print("&" + caption + "&");
    } else {
      lcd.print(">" + caption + "<");
    }

    //Include distance caption on the second row of LCD display

    if(include_distance == true){
    lcd.setCursor(0, 1);
    lcd.print(String(distance) + " cm");
    }
    
    delay(scroll_speed);
  }

}

void setup() {
  //Ultrasonic Setup:

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a setup msg to the LCD.
  lcd.print("Setting up...");
}

void loop() {
  digitalWrite(trigger_pin , LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW );

  duration = pulseIn(echo_pin, HIGH);

  // Delta S = ( Delta T * Velocity ) / 2 <-- Since the ultrasonic wave travels to the target and back 
  distance = duration*0.034/2; //Since the Ultrasonic sensor travels at the speed of sound, and we know time, we convert this into a distance

  // DEBUG for Serial Monitor
  Serial.println("Distance: ");
  Serial.println(distance);
  
  lcd.clear();
  lcd.setCursor(0, 0); //Set to top row of LCD monitor

  //Distance sensitivity logic:

  if(distance > 1000){ //It suddenly spikes to over 1000 cm which indicates some kind of lag with the Ultrasonic, I just display an error message
        lcd.print("ERROR: UNSYNCED");
        delay(50);
  }
  else if(distance > 5 && distance < 15){
    lcd.print("Perfect, stay there.");

    tone(buzzer,400);
    delay(500);
    noTone(buzzer);
    
    scroll_text("Perfect, stay there.", 20);
  }

  else if (distance <= 5){
    blink_border(" MOVE AWAY ",10,200, true, distance);
  }

  else {
    blink_border(" COME CLOSER ",10,200, true, distance);
  }
  
  lcd.setCursor(0, 1);
  lcd.print(String(distance) + " cm");

  delay(100); //main refresh delay for LCD display
}