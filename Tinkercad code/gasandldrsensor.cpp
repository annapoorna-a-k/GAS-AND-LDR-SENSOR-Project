#include <LiquidCrystal.h>      

const int rs = 12, e = 11, db4 = 5, db5 = 4, db6 = 3, db7 = 2;//pinout for LCD
LiquidCrystal lcd(rs, e, db4, db5, db6, db7); // set the LCD pins
//gas sensor
int redLed = 10;    //pin for red led
int greenLed = 9;   //pin for green led
int gasSensor = A0; //pin for gas sensor
int buzzer = 13;    //pin for buzzer
int sensorThresh = 400; //threshold for gas sensor

//ldr sensor
const int blueLed = 8;
const int ldrPin = A1;


void setup()            
{
  //gas sensor
  pinMode(redLed, OUTPUT);  //set red led pin to output
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gasSensor, INPUT);
  
  //ldrsensor
  pinMode(blueLed, OUTPUT);
  pinMode(ldrPin, INPUT);

  Serial.begin(9600);   //start serial communication
  lcd.begin(16,2);    //set LCD to 16x2
}

void loop()
{
  int analogValue = analogRead(gasSensor);  //read gas sensor value and store in analogValue
  Serial.println(analogValue);  //print gas sensor value to serial monitor  (for debugging) 
  
  int ldrStatus = analogRead(ldrPin);  //read ldr sensor value  and store in ldrStatus
  
  //ldr sensor
  if (ldrStatus <= 300)     //if ldr sensor value is less than 300  
  {
  	digitalWrite(blueLed, HIGH);    //turn on blue led  
  	Serial.print("Its DARK, Turn on the LED : ");   //print message to serial monitor 
    Serial.print(ldrStatus);    //print ldr sensor value to serial monitor    
  } 
  else 
  {
  	digitalWrite(blueLed, LOW);   //turn off blue led   
    Serial.print("Its BRIGHT, Turn off the LED : ");    
    Serial.print(ldrStatus);  //print ldr sensor value to serial monitor
  }
  
  //gas sensor
  if(analogValue > sensorThresh)    //if gas sensor value is greater than threshold 
  {
  	digitalWrite(redLed, HIGH);   //turn on red led
  	digitalWrite(greenLed, LOW);    //turn off green led
    tone(buzzer, 1000, 10000);  //play buzzer sound 
	lcd.clear();    //clear LCD screen
    lcd.setCursor(0,0); //set cursor to first row, first column
    lcd.print("ALERT"); //print message to LCD screen
    delay(1000);    //delay for 1 second
    lcd.clear();    //clear LCD screen
    lcd.setCursor(0,1); //set cursor to first row, first column
    lcd.print("EVACUATE");  //print message to LCD screen
    delay(1000);    //delay for 1 second
  }
  else
  {
  	digitalWrite(redLed, LOW);  //turn off red led
  	digitalWrite(greenLed, HIGH);   //turn on green led
    noTone(buzzer); //stop buzzer sound
    lcd.clear();    //clear LCD screen
    lcd.setCursor(0,0); //set cursor to first row, first column of LCD screen   
    lcd.print("SAFE");  //print message to LCD screen
    delay(1000);    //delay for 1 second
    lcd.clear();    //clear LCD screen
    lcd.setCursor(0,1); //set cursor to first row, first column of LCD screen
    lcd.print("ALL CLEAR"); //print message to LCD screen
    delay(1000);    //delay for 1 second
  }
}
