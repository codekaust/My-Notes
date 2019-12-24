const int analogInPin = A0;   // Number of the pin connected to the photoresistor
const int analogOutPin = 9;   // Number of the pin connected to the LED

int sensorValue = 0;          // Value read by the photoresistor
int outputValue = 0;          // Value sent to the LED

void setup() {
  // Initialise communication with the computer
  Serial.begin(9600);
  
  // Indicate that the pin analogOutPin is an output:
  pinMode(analogOutPin, OUTPUT);      
  // Indicate that analogInPin is an input:
  pinMode(analogInPin, INPUT);     
}

void loop() {
  // Read the value of the photoresistor and
  // store that value in sensorValue:
  sensorValue = analogRead(analogInPin);            
  // scale sensorValue to a value between 0 and 255
  // and store the value in outputValue:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // send this new outputValue to the LED
  analogWrite(analogOutPin, outputValue);           

  // sending the information to the computer
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);
}