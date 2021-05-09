                /* Hourly temperature data analysis project with Matlab and arudino
                 *  Project tutorial url:https://embeddedsystemshalilgk.wordpress.com
                 *  Project tutorial YOUTUBE :https://www.youtube.com/watch?v=s3WkSCQnHnA&t=4s
                 *  
                 *  by Halil Gök :
                 *  
                  */

////** Includes **////
#include <SPI.h>
#include <SD.h>

File file;  


////**  Private define **////

#define DAYS 0
#define HOURS 1
#define MINUTES 2
#define SECONDS 3

////**  Private variables    **////
unsigned  int hours = 00;
unsigned int minutes = 00;
unsigned int seconds = 0;
unsigned int new_hour = 0, new_minute = 0;
byte dhtData[6];
int dht11pin=A0;
int buzzer=6;
////**  Private variables    **////
void incTime();
void ReadDHT11(int pin, byte* output);
void ReadDHT11(int pin, byte* output);
byte ReadDHT11Pin(int pin);

ISR(TIMER1_COMPA_vect);

void setup() {
 pinMode(buzzer,OUTPUT);
 Serial.begin(115200);
 Serial.println("SD Cart preparing..."); 
  if(!SD.begin(4)) // SD card CS leg connected to digital PIN number 4, if SD card not inserted
  {
    Serial.println("The SD card is not connected!!!");
    Serial.println("Please connect your SD card!!!");
    while(!SD.begin(4)); // waiting until the card is connected
    Serial.println("SD card is ready!!");
    delay(1000); 
  }
  else
  {
    Serial.println("SD card is ready!!"); 
    delay(1000);  
  }
  //Setting Timer1 interrupt  
  //this will increase accuracy for clock timing.
   cli(); 
  TCNT1  = 0;
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15624;  // Time interrupt frequency required for 1 second operation
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
  for(int i=0;i<6;i++)
  {digitalWrite(buzzer,1); delay(100);digitalWrite(buzzer,0); delay(100); 
   }
  // SD.remove("data.txt");
}
ISR(TIMER1_COMPA_vect){     //Her kesmeye girildiğinde otomatik çalıştırılacak fonksiyon.
  incTime();
}

void loop() {
  
  ReadDHT11(dht11pin, dhtData);   //data is read from the DHT11 sensor.

  if (minutes % 20 == 0  && (new_hour != hours || new_minute != minutes))
  { new_hour = hours; new_minute = minutes;
    Serial.print("Time : ");       //the computer prints the necessary information.
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print("  ");
    Serial.print("Temperature: ");
    Serial.print(dhtData[3], DEC);
    Serial.print(".");
    Serial.print(dhtData[4], DEC); 
    Serial.println("°C");   
    /// Information to print to Sd card
    file = SD.open("data.txt",FILE_WRITE); //new data.txt file is created.
    file.print("Time : ");file.print(hours);file.print(":");file.print(minutes); //writing time 
    file.print(" Temperature : ");
    file.print(dhtData[3]);file.print(".");file.print(dhtData[4]);file.println("°C");  //writing data temperature
    file.close(); 
    digitalWrite(buzzer,1);  // on buzzer 
  }
 
  delay(750);// time to wait for new data
  digitalWrite(buzzer,0);  // off buzzer
} 

void incTime() {
  // Increase seconds
  seconds++;

  if (seconds == 60) {
    // Reset seconds
    seconds = 0;

    // Increase minutes
    minutes++;

    if (minutes == 60) {
      // Reset minutes
      minutes = 0;

      // Increase hours
      hours++;

      if (hours == 24) {
        // Reset hours
        hours = 0;
      }
    }
  }
}
void ReadDHT11(int pin, byte* output)
{
  // Init DHT
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(20);
  // Trigger data output
  digitalWrite(pin, LOW);
  delay(20);
  digitalWrite(pin, HIGH);
  delayMicroseconds(40);

  // DHT in var
  byte dht_in;

  // Start reading
  pinMode(pin, INPUT);
  dht_in = digitalRead(pin);

  // Nothing should be returned to begin with
  if (dht_in) {
    // Error mode 1
    output[0] = 1;
    return;
  }

  // Wait 80 microseconds and recheck
  delayMicroseconds(80);
  dht_in = digitalRead(pin);

  // This time something should be there
  if (!dht_in) {
    // Error mode 2
    output[0] = 2;
    return;
  }

  // Wait 80 microseconds then we should get data
  delayMicroseconds(80);

  byte i = 1;
  for (i = 1; i < 6; i++) {
    output[i] = ReadDHT11Pin(pin);
  }

  byte dht_check_sum = output[1] + output[2] + output[3] + output[4];
  if (output[5] != dht_check_sum) {
    // Checksum doesn't match, something went wrong
    output[0] = 3;
  } else {
    // Response passes checksum
    output[0] = 0;
  }
  // Reset the output to high
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

byte ReadDHT11Pin(int pin) {
  byte i = 0;
  byte result = 0;
 // We need to read one byte of data off the data pin, read this bit by bit, literally, by looping 8 times
  for (i = 0; i < 8; i++) {
    // Stall the loop while the pin is low, wait for it to go high indicating incoming bit
    while (digitalRead(pin) == LOW);
    // Pin goes high briefly to notify of incoming bit. Wait 30 microseconds to allow the pin to drop back to low if necessary
    delayMicroseconds(30);
    // If the pin goes high then we have data at this position in the byte
    if (digitalRead(pin) == HIGH) {
      // Set the bit
      result |= (1 << (7 - i));
    }
    // Stall the loop until the pin drops back to low indicating either no data at this bit or the end of the high bit
    while (digitalRead(pin) == HIGH);
  }
  return result;
}
