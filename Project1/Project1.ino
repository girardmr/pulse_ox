float InputPin = A0; // Analog input pin from output of op amp
float q=1.6E-19;
float N=1;
float k=1.38E-23;
float T=298;
float sensorVoltage = 0;
float sensorCurrent = 0;
float LEDCurrent700 = 0;
float Absorbance700 = 0;
float LEDCurrent800 = 0;
float Absorbance800 = 0;
float AvgOxy;
float Is=1E-12;
float Vd=1;
float oxygenation;
float bloodOx = 0;
int resistor = 1000000;
int LED700=3;
int LED800=2;
int Oxy[]={0,0,0,0,0,0,0,0,0,0};

byte i=0;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
Serial.begin(9600);
pinMode(LED700, OUTPUT);
pinMode(LED800, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
for (int index = 0; index < 10; index++){
digitalWrite(LED800, LOW);
digitalWrite(LED700, HIGH);
delay(3000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = -(sensorVoltage*5/(25000000*1023))*1000000;
LEDCurrent700=0.005;
Absorbance700 = log10(sensorCurrent/LEDCurrent700);
digitalWrite(LED700, LOW);
digitalWrite(LED800, HIGH);
delay(3000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = -(sensorVoltage*5/(25000000*1023))*1000000;
LEDCurrent800=0.005;
Absorbance800 = log10(sensorCurrent/LEDCurrent800);
Oxy[index]=Absorbance800/(Absorbance800 + Absorbance700);
oxygenation=Absorbance700/(Absorbance800 + Absorbance700);
bloodOx = -30.667*oxygenation*oxygenation+10*oxygenation+102.67;
Serial.print("Blood Ox % = " );
Serial.println(bloodOx);
  // Turn on the display:
  lcd.display();
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Blood ox % = ");
  lcd.setCursor(0,1);
  lcd.print(bloodOx);
  

  
}



}




