#define ledGreen 8
#define buttonOne 3 // Används med externa avbrott
#define ledRed 9
#define buttonTwo 2 // Används med externa avbrott
#define ledBlue 6
#define POTENTIOMETER_PIN A0

// Volatile som låter arduino veta att variablerna kan ändras
volatile bool buttonOnePressed = false;
volatile bool buttonTwoPressed = false;
volatile unsigned long lastInterruptTimeOne = 0;
volatile unsigned long lastInterruptTimeTwo = 0;
const unsigned long debounceTime = 200; // Debounce-tid i millisekunder

// Knapparna & potentiometer satt till true i början av programmet
bool buttonOneEnabled = true;
bool buttonTwoEnabled = true;
bool potentiometerEnabled = true;

void setup() {
// Lampor sätts som utgång & knappar sätts som ingång med arduinos inbyggda resistor 
 pinMode(ledGreen, OUTPUT);
 pinMode(ledRed, OUTPUT);
 pinMode(buttonOne, INPUT_PULLUP);
 pinMode(buttonTwo, INPUT_PULLUP);
 pinMode(ledBlue, OUTPUT);
 Serial.begin(9600);

 // Initierar interrupts till knapparna, aktiveras vid all typ av ändring
 attachInterrupt(digitalPinToInterrupt(buttonOne), buttonOneISR, CHANGE);
 attachInterrupt(digitalPinToInterrupt(buttonTwo), buttonTwoISR, CHANGE);
}

void loop() {
 // Variabler för när knapparna trycktes sist
 static unsigned long lastToggleTimeOne = 0;
 static unsigned long lastToggleTimeTwo = 0;

 if (buttonOnePressed && buttonOneEnabled) {
   unsigned long currentTime = millis();
   if (currentTime - lastToggleTimeOne > debounceTime) {
     digitalWrite(ledGreen, !digitalRead(ledGreen));
     lastToggleTimeOne = currentTime;
   }
   buttonOnePressed = false;
 }

 if (buttonTwoPressed && buttonTwoEnabled) {
   unsigned long currentTime = millis();
   if (currentTime - lastToggleTimeTwo > debounceTime) {
     digitalWrite(ledRed, !digitalRead(ledRed));
     lastToggleTimeTwo = currentTime;
   }
   buttonTwoPressed = false;
 }

 if (potentiometerEnabled) {
   readAndAdjustAnalogSensor();
 }
 readSerialCommands();
}

// Interrupt Service Routine funktion för knapp1
void buttonOneISR() {
 unsigned long interruptTime = millis();
 if (interruptTime - lastInterruptTimeOne > debounceTime) {
   buttonOnePressed = true;
   lastInterruptTimeOne = interruptTime;
 }
}

// Interrupt Service Routine funktion för knapp2
void buttonTwoISR() {
 unsigned long interruptTime = millis();
 if (interruptTime - lastInterruptTimeTwo > debounceTime) {
   buttonTwoPressed = true;
   lastInterruptTimeTwo = interruptTime;
 }
}

// Funktion för justera ljusstyrkan på LED med potentiometer
void readAndAdjustAnalogSensor() {
 if (!potentiometerEnabled) return;
  int sensorValue = analogRead(POTENTIOMETER_PIN);
 int brightness = map(sensorValue, 0, 1023, 0, 255);
 analogWrite(ledBlue, brightness);
}

// Funktion för att styra kretsen via kommandon på serial monitorn
void readSerialCommands() {
 if (Serial.available() > 0) {
   String command = Serial.readStringUntil('\n');
   Serial.print("Mottaget kommando: "); Serial.println(command);


   if (command == "enable button 1") {
     buttonOneEnabled = true;
     Serial.println("Knapp 1 aktiverad");
   } else if (command == "disable button 1") {
     buttonOneEnabled = false;
     Serial.println("Knapp 1 inaktiverad");
   } else if (command == "enable button 2") {
     buttonTwoEnabled = true;
     Serial.println("Knapp 2 aktiverad");
   } else if (command == "disable button 2") {
     buttonTwoEnabled = false;
     Serial.println("Knapp 2 inaktiverad");
   } else if (command.startsWith("ledpower ")) {
     int power = command.substring(9).toInt();
     if (power == -1) {
       potentiometerEnabled = true;
       Serial.println("Potentiometer aktiverad");
     } else {
       potentiometerEnabled = false;
       int brightness = map(power, 0, 10, 0, 255);
       analogWrite(ledBlue, brightness);
       Serial.print("PWM intensitet satt till: "); Serial.println(brightness);
     }
   } else if (command == "ledon 1") {
     digitalWrite(ledGreen, HIGH);
     Serial.println("LED 1 tänd");
   } else if (command == "ledoff 1") {
     digitalWrite(ledGreen, LOW);
     Serial.println("LED 1 släckt");
   } else if (command == "ledon 2") {
     digitalWrite(ledRed, HIGH);
     Serial.println("LED 2 tänd");
   } else if (command == "ledoff 2") {
     digitalWrite(ledRed, LOW);
     Serial.println("LED 2 släckt");
   } else {
     Serial.println("Okänt kommando");
   }
 }
}
