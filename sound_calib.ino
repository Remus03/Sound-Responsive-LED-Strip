#include <FastLED.h>
const int SOUND_PIN = 8;
const int SAMPLE_TIME = 40;
unsigned long current;
unsigned long last = 0;
unsigned long elapsed = 0;
const int OUT_PIN = 9;

class Sound_lvl
{
  float old_lvl;
  float new_lvl;

  public:
    Sound_lvl():old_lvl(0), new_lvl(0){};
    Sound_lvl& operator+=(float a)
    {
      new_lvl = new_lvl + a;
      return *this;
    };
    void reset()
    {
      old_lvl = new_lvl;
      new_lvl = 0;
    };
    float getold()
    {
      return old_lvl;
    }
    float getnew()
    {
      return new_lvl;
    }
    
};

CRGB leds[30];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, OUT_PIN>(leds, 30);
}



Sound_lvl level = Sound_lvl();

void loop() {
  current = millis();
  elapsed = current - last;

  if (digitalRead(SOUND_PIN) == HIGH){
    level+=0.025;
  }

  
  if (elapsed > SAMPLE_TIME) {
    Serial.println( level.getnew() );
    if( level.getnew() > level.getold() )
    {
        for(int i = level.getold(); i < level.getnew() ; i++)
      {
        leds[i] = CRGB::Green;
        FastLED.show();
      }
    }
    else
    {
      for( int i = level.getold(); i >= level.getnew(); i--)
      {
        leds[i] = CRGB::Black;
        FastLED.show();
      }
    }
    level.reset();
    last = current;
  }
}
