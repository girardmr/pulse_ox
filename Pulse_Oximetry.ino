float InputPin = A0; // Analog input pin conencted to output of op amp
float q=1.6E-19;
float N=1;
float k=1.38E-23;
float T=298;
float Is=1E-12;
float Vd=1;
float sensorVoltage = 0;
float sensorCurrent = 0;
float LEDCurrent700 = 0;
float Absorbance700 = 0;
float LEDCurrent800 = 0;
float Absorbance800 = 0;
float bloodOx = 0;
int resistor = 1000000;
int LED=3;
int Oxy[]={0,0,0,0,0,0,0,0,0,0};
byte i=0;

void setup() {
Serial.begin(9600);
pinMode(LED, OUTPUT);

}

void loop() {
for (int index = 0; index < 10; index++){
digitalWrite(LED, LOW);
delay(1000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = sensorVoltage*5/(resistor*1023);
LEDCurrent700=Is*(exp((q*Vd)/(N*k*T))-1);
Absorbance700 = -log10(sensorCurrent/LEDCurrent700);
digitalWrite(LED, HIGH);
delay(1000);
sensorVoltage = analogRead(InputPin);
sensorCurrent = sensorVoltage*5/(resistor*1023);
LEDCurrent800=Is*(exp((q*Vd)/(N*k*T))-1);
Absorbance800 = -log10(sensorCurrent/LEDCurrent800);
Oxy[index]=Absorbance800/(Absorbance800 + Absorbance700);
bloodOx = -30.667*(Oxy[index])^2+10*Oxy[index]+102.67;
}

  int total = 0;
  int average = 0;
  for (i=0; i<10; i++) {
    total = total + Oxy[i];
  }
  average = total / 10;

Serial.print("\t Blood oxygenation = ");
Serial.println(average);

}
