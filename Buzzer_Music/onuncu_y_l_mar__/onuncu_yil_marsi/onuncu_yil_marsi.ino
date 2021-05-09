#include <Tone.h>


 // buzzer 9
Tone tone1;

#define OCTAVE_OFFSET 0

int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};
char *song = "Onuncu yil:d=4,o=5,b=250:2c,8p.,g,2c,2a,2f,2d,2c,2p,2f,8p.,f,2d,8p.,a,2d,2c,2e,8p. ,2d,8p.,d,1f,e,8p.,f,c,2d,8p.,1e,2f,a,d,2c";

void setup(void)
{
  Serial.begin(9600);
  tone1.begin(9);
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(char *p)
{
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  while(*p != ':') p++;    
  p++;                     

  if(*p == 'd')
  {
    p++; p++;              
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  if(*p == 'o')
  {
    p++; p++;              
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  if(*p == 'b')
  {
    p++; p++;              
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  wholenote = (60 * 1000L / bpm) * 4;  

  Serial.print("wn: "); Serial.println(wholenote, 10);


  while(*p)
  {
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  

    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    if(*p == '#')
    {
      note++;
      p++;
    }

    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;      

    if(note)
    {
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
  }
}

void loop(void)
{
  play_rtttl(song);
  Serial.println("Done.");
  while(1);
} 
