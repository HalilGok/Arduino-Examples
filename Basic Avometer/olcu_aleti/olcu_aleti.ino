
#include <LiquidCrystal.h>  //LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal ekran(8, 9, 4, 5, 6, 7);

// tus değerleri selected=722,left=481,right=0,up=132,down=309
#define selected_buton_min 710
#define selected_buton_max 735
#define left_buton_min 470
#define left_buton_max 490
#define right_buton_max 10
#define up_buton_min 120
#define up_buton_max 140
#define down_buton_min 290
#define down_buton_max 320

// A0-Tuş değerlerinin okunduğu bacak // A1- direnc değerlerinin okunduğu bacak// A2- gerilim değerlerini okuduğu bacak
int okunan;
int okunan2;
int  menuitem = 1;
int direncgiris = A1;
int voltgiris = A2;
int kondansatorgiris = A3;
int kisa_devregiris = A4;
int desarj = 2;
int sarj = 3;
int kisa_devre = 0; //  ***********
int buzzer = 1;
float sarjDirenc = 9990.0;
void setup() {
  pinMode(direncgiris, INPUT);
  pinMode(voltgiris, INPUT);
  pinMode(kondansatorgiris, INPUT);
  pinMode(kisa_devre, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sarj, OUTPUT);
  digitalWrite(sarj, LOW);
  ekran.begin(16, 2);
  ekran.clear();


}

void loop() {
  pinMode(desarj, OUTPUT);
  digitalWrite(desarj, LOW);
  analog_oku();
  delay(250);




}
int analog_oku()
{
  int okunan = analogRead(0);
  secenek_goster();
  if ( okunan < right_buton_max && okunan < 1000)
  {

    menuitem++;
    if (menuitem == 5)
      menuitem = 1;
    delay(500);
  }

  if (left_buton_min < okunan && okunan < left_buton_max && okunan < 1000)
  {

    menuitem--;
    if (menuitem == 0)
      menuitem = 4;
    delay(500);

  }


}
int direnc_oku() {

  ekran.clear();

  int direncokunan = analogRead(direncgiris);

  if (direncokunan == 0)
  { ekran.clear();
    ekran.print("   OHM  METRE   ");
    ekran.setCursor(0, 1);
    ekran.print("Direnc Yerlestir");
    delay (100);
    direncokunan = analogRead(direncgiris);
    delay (100);

  }
  if (direncokunan == !(0)) {
    float R1 = 9830.0;
    float VT = 5.0;
    float V1 = direncokunan * VT / 1023;
    float R2 = (R1 * (VT - V1)) / V1;

    ekran.clear();
    ekran.print("R : ");
    ekran.print(R2);
    ekran.print(" ");
  }
  delay(300);

}
int volt_oku() {  // 0 - 5V arası
  ekran.clear();
  int deger = analogRead(voltgiris);

  float volt = deger * 5.0 / 1023.0;

  ekran.print("Volt degeri:");
  ekran.setCursor(0, 1);
  ekran.print("      ");
  ekran.print(volt);
  ekran.print("V");

  delay(150);

}
int kondansator_oku() {


  digitalWrite(sarj, LOW);
  int deger1 = analogRead(kondansatorgiris);

  ekran.clear();
  ekran.setCursor(0, 0);
  ekran.print("  KONDANSATOR  ");
  ekran.setCursor(0, 1);
  ekran.print("  YERLESTiRiN  ");

  while (deger1 == 0)
  {
    deger1 = analogRead(kondansatorgiris);

  }

  ekran.clear();
  ekran.setCursor(0, 0);
  ekran.print(" KAPASiTE METRE ");
  ekran.setCursor(0, 1);
  ekran.print("Desarj ediliyor");

  while (deger1 > 0) {
    deger1 = analogRead(kondansatorgiris);

  }

  pinMode(desarj, INPUT);
  digitalWrite(sarj, HIGH);
  unsigned long baslamaZamani = micros();

  ekran.clear();
  ekran.setCursor(0, 0);
  ekran.print(" KAPASiTE METRE ");
  ekran.setCursor(0, 1);
  ekran.print("Sarj Ediliyor");
  while (deger1 < 648) {
    deger1 = analogRead(kondansatorgiris);

  }

  unsigned long bitisZamani = micros();

  unsigned long zaman = bitisZamani - baslamaZamani;

  float kapasiteDeger = zaman / sarjDirenc;
  ekran.clear();
  ekran.setCursor(0, 0);
  ekran.print(" KAPASiTE METRE ");
  ekran.setCursor(0, 1);
  ekran.print("C : ");
  ekran.print(kapasiteDeger);
  ekran.print("uF");
  delay(2000);
}
int kisa_devre_oku() {

  digitalWrite(kisa_devre, 1);

  int var = analogRead(kisa_devregiris);
  if (var > 50 ) {

    ekran.clear();
    ekran.print("Kisa devre var");
    digitalWrite(buzzer, HIGH);
    delay(100);
  }
  if (var == 0) {
    ekran.clear();
    ekran.print("Kisa devre yok");
    digitalWrite(buzzer, LOW);
    ekran.setCursor(0, 1);
    ekran.print(var);
    delay(500);
  }
}
int secenek_goster()
{
  switch (menuitem)
  {
    case 1:
      { ekran.clear();
        ekran.print("> Direnc Okuma");
        ekran.setCursor(0, 1);
        ekran.print(" < Olcu Aleti >");
        okunan = analogRead(0);
        if (okunan < 1020)
        {
          okunan2 = okunan;
        }

        if (selected_buton_min < okunan2 && selected_buton_max > okunan2 && okunan2 < 1000) {

          direnc_oku();

        }
        break;
      }
    case 2:
      { ekran.clear();
        ekran.print("> Volt okuma");
        ekran.setCursor(0, 1);
        ekran.print(" < Olcu Aleti >");
        okunan = analogRead(0);
        if (okunan < 1020)
        {
          okunan2 = okunan;
        }

        if (selected_buton_min < okunan2 && selected_buton_max > okunan2 && okunan2 < 1000) {

          volt_oku();
        }
        break;
      }
    case 3:
      {
        ekran.clear();
        ekran.print(">Kondansator oku");
        ekran.setCursor(0, 1);
        ekran.print(" < Olcu Aleti >");
        okunan = analogRead(0);
        if (okunan < 1020)
        {
          okunan2 = okunan;
        }

        if (selected_buton_min < okunan2 && selected_buton_max > okunan2 && okunan2 < 1000) {
          kondansator_oku();
        }
        break;
      }
    case 4:
      {
        ekran.clear();
        ekran.print("> Kisa devre");
        ekran.setCursor(0, 1);
        ekran.print(" < Olcu Aleti >");
        okunan = analogRead(0);
        if (okunan < 1020)
        {
          okunan2 = okunan;
        }

        if (selected_buton_min < okunan2 && selected_buton_max > okunan2 && okunan2 < 1000) {

          kisa_devre_oku();
        }
        break;
      }
  }
}
