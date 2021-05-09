
int leddizisi[]={2,3,4,5,6,7,8,9};
void setup() {
 for(int i=0 ; i<8; i++)
 {
 pinMode(leddizisi[i], OUTPUT);
 }
}

void loop() {

for(int a=0; a<8; a++)
{/* LEDleri ileri yonde 50 milisaniye yakip sonduruyoruz */

digitalWrite(leddizisi[a], HIGH);
delay(50);
digitalWrite(leddizisi[a], LOW);
}

for(int j=7;j>-1; j--)
  { /* LEDleri geri yonde 50 milisaniye yakip sonduruyoruz */
    digitalWrite(leddizisi[j],HIGH);     
    delay(50);
    digitalWrite(leddizisi[j], LOW);
  }}
