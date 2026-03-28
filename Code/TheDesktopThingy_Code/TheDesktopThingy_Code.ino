#include <HID-Project.h>
#include <HID-Settings.h>

#define REVERSED false                  

int val = 0;
int previousval = 0;
int val2 = 0;
int light = 0;

int copy = 0;
int paste = 0;
int reverse = 0;

void setup() {
  Consumer.begin(); 
  Keyboard.begin(); 
  pinMode(A0, INPUT);   
  pinMode(A1, INPUT);   
  pinMode(2, INPUT);   
  pinMode(3, INPUT);   
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);              
  delay(1000);                             
  for(int a = 0; a < 52; a++) {
    Consumer.write(MEDIA_VOLUME_DOWN);    
    delay(2);
  }
}

void loop() {
  val = analogRead(A0);                    
  val = map(val, 0, 1023, 0, 101);  
  light = analogRead(A1);
  light = map(light, 0, 1023, 0, 255);
  analogWrite(5, light);
  
  copy = digitalRead(2);
  paste = digitalRead(3);
  reverse = digitalRead(4);

  if (copy == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    delay(100);
    Keyboard.releaseAll(); 
  }
  if (digitalRead(paste) == LOW) {
    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press('v');
    delay(100);
    Keyboard.releaseAll(); 
  }
  if (digitalRead(reverse) == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('z');
    delay(100);
    Keyboard.releaseAll(); 
  }

  if(REVERSED) {
    val = 101 - val;
  }
  if(abs(val - previousval) > 1) {   
    previousval = val;
    val /= 2;                     
    while(val2 < val) {
      Consumer.write(MEDIA_VOLUME_UP);    
      val2++;
      delay(2);
    }
    while(val2 > val) {
      Consumer.write(MEDIA_VOLUME_DOWN);  
      val2--;
      delay(2);
    }
  }
  delay(301);                             
}                                    
