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
float bloodOx = 0;
int resistor = 1000000;
int LED700=3;
int LED800=5;
int Oxy[]={0,0,0,0,0,0,0,0,0,0};

byte i=0;

void setup() {
Serial.begin(9600);
pinMode(LED700, OUTPUT);
pinMode(LED800, OUTPUT);
}

void loop() {
for (int index = 0; index < 10; index++){
digitalWrite(LED800, LOW);
digitalWrite(LED700, HIGH);
delay(1000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = sensorVoltage*5/(resistor*1023);
Serial.print("Sensor Voltage = " );
Serial.println(sensorVoltage*5/1023);
Serial.print("Sensor Current Red = " );
Serial.println(sensorCurrent);
//LEDCurrent700=Is*(exp((q*Vd)/(N*k*T))-1);
LEDCurrent700 = 0.005;
Serial.print("LED Current 700 = " );
Serial.println(LEDCurrent700);
Absorbance700 = -log10(sensorCurrent/LEDCurrent700);
digitalWrite(LED700, LOW);
digitalWrite(LED800, HIGH);
delay(1000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = sensorVoltage*5/(resistor*1023);
Serial.print("Sensor Current IR = " );
Serial.println(sensorCurrent);
//LEDCurrent800=Is*(exp((q*Vd)/(N*k*T))-1);
LEDCurrent800 = 0.005;
Serial.print("LED Current 800 = " );
Serial.println(LEDCurrent800);
Absorbance800 = -log10(sensorCurrent/LEDCurrent800);
Serial.print("AbsorbanceIR = " );
Serial.println(Absorbance800);
Serial.print("AbsorbanceRed = ");
Serial.println(Absorbance700);
Oxy[index]=Absorbance800/(Absorbance800 + Absorbance700);
Serial.print("oxygenation = " );
Serial.println(Oxy[index]);
bloodOx = -30.667*(Oxy[index])^2+10*Oxy[index]+102.67;
Serial.print("Blood Ox % = " );
Serial.println(bloodOx);
}

  int total = 0;
  int average = 0;
  for (i=0; i<10; i++) {
    total = total + Oxy[i];
  }
  average = total / 10;


Serial.print("Average oxygenation = ");
Serial.println(average);

}
