/*
  A simple program designed to setup and demonstrate the Keyes Vibration Sensor Module - BDAA100015 
  The program monitors connected analog and digital pin and outputs the value to the
  serial monitor.
  
  modified 26th September 2019
  by Sebastian Karam - Flux Workshop
*/
//For DK
#define HEADER_SIZE 5
#define MAGIC_1 2
#define MAGIC_2 4
#define OPCODE_UART_DATA 1

#define SLAVE_ADDRESS 0x36
int SendData, DATA_SIZE, error;
int ranging_mm = 0;
int tof_1 = 0;
int tof_2 = 0;



int analogpin = 1; // define analog OUT signal pin
int analog; // define variable to store value read from pin
int digitalpin = 3; // define digital OUT signal pin
int digital; // define variable to store value read from pin

unsigned int i = 0;
int signal_list[500] = {};
int threshold = 800;
int count = 0;
int threshold_cut = 100;
int cut = 0;
  
void setup() {
  pinMode(analogpin, INPUT); // set the OUT signal pin as an input
  pinMode(digitalpin, INPUT); // set the OUT signal pin as an input
  // Start the hardware serial port for the serial monitor.
//  Serial.begin(115200, SERIAL_8E1);
  Serial.begin(9600); // launch the serial monitor
//  Serial.println("Flux Workshop Example");
}

void loop() { 
  analog = analogRead(analogpin);  // read the voltage level on the A0
  digital = digitalRead(digitalpin);  // read the voltage level on the D2
  
//  Serial.println((String)"Light level: Analog " + analog + " Digital " + digital ); // send the result to the serial monitor
//  Serial.println(analog); // send the result to the serial monitor
  delay(5); // pause for a moment before repeating
  i += 1;
////  Serial.println((String)i);
  if (i>500){
    i=0; //reset to beginning of array, so you don't try to save readings outside of the bounds of the array
  }
  signal_list[i-1] = analog;
//  
  if (i==500) {
    for (int j=0;j<i;j+=1) {
      if (signal_list[j] > threshold) {
        count += 1;
//        Serial.println((String)count);
      }
    }
     // cutting tree
    if (count > threshold_cut) {
      cut = 1;
      Serial.println((String)cut);
    }
    else {
      cut = 0;
      Serial.println((String)cut);
    }
  }
  count = 0;
}
