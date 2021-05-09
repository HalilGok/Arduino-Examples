//// Youtube Abone Ol ////
//// açıklama videosu ////
/// https://www.youtube.com/watch?v=MoG4x3YYcpY&t=160s ////

//// HALİL GÖK //////////


#include<Wire.h>
#include<LCD.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C  ekran(0x27, 2, 1, 0, 4, 5, 6, 7);
int buzzer = 6;
int port = 2;; //step
int hiz = 5; //step

float sure; // sensor
float mesafe; //sensor

const int trigger_pin = 8;
const int echo_pin = 9;

void ileri(int adim) {
  for (int i = 0; i <= adim; i++)
  { digitalWrite(port, HIGH);
    delay(hiz);
    digitalWrite(port, LOW);
    port_arttir();
    if (i == 0 || i == 250 || i == 500 || i == 750 || i == 1000)
    { ekran.clear();
      digitalWrite(trigger_pin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigger_pin, LOW);
      sure = pulseIn(echo_pin, HIGH);
      mesafe = (sure / 2) / 28.5;
      Serial.print("cisme olan uzaklık: ");
      Serial.print(mesafe);
      Serial.println("cm");
      Serial.println("------------------");
      if (mesafe > 50)
      { ekran.print("Cisim yok");
        digitalWrite(buzzer, LOW);
      }
      if (mesafe < 50)
      { ekran.print("cisim var");
        ekran.setCursor(0, 1);
        ekran.print("mesafe:");
        ekran.print(        mesafe);
        ekran.print("cm");
        digitalWrite(buzzer, HIGH);
      }
    }
  }
}

void geri(int adim) {
  for (int i = 0; i <= adim; i++)
  { digitalWrite(port, HIGH);
    delay(hiz);
    digitalWrite(port, LOW);
    port_azalt();
    if (i == 0 || i == 250 || i == 500 || i == 750 || i == 1000)
    { ekran.clear();
      digitalWrite(trigger_pin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigger_pin, LOW);
      sure = pulseIn(echo_pin, HIGH);
      mesafe = (sure / 2) / 28.5;
      Serial.print("cisme olan uzaklık: ");
      Serial.print(mesafe);
      Serial.println("cm");
      Serial.println("------------------");
      if (mesafe > 50)
      { ekran.print("Cisim yok");
        digitalWrite(buzzer, LOW);
      }
      if (mesafe < 50)
      { ekran.print("cisim var");
        ekran.setCursor(0, 1);
        ekran.print("mesafe:");
        ekran.print(        mesafe);
        ekran.print("       cm");
        digitalWrite(buzzer, HIGH);
      }

    }
  }
}

void port_arttir() {
  port++;
  if (port == 6)
    port = 2;
}

void port_azalt() {
  if (port == 2)
    port = 6;
  port--;
}
void setup() {
  ekran.begin(16, 2);
  Serial.begin(9600);
  ekran.clear();
  ekran.home();

  pinMode(0, OUTPUT);  //IN1
  pinMode(1, OUTPUT);  //IN2
  pinMode(2, OUTPUT);  //IN3
  pinMode(3, OUTPUT);  //IN4
  pinMode(6, OUTPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

}

void loop() {
  ileri(2000);
  delay(1000);
  geri(2000);
}
