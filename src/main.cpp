#include <Arduino.h>

void ISR_ss_button_pressed();
void ISR_reset_button_pressed();

#define reset_button_pin 12
#define ss_button_pin 13

enum states{IDLE, RUNNING, PAUSED};
enum states current_state = IDLE;

bool ss_button_pressed = false;
bool reset_button_pressed = false;

uint32_t counter = 0;

void setup() {
Serial.begin(9600);
pinMode(reset_button_pin,INPUT_PULLUP);
pinMode(ss_button_pin,INPUT_PULLUP);

attachInterrupt(reset_button_pin, ISR_reset_button_pressed, FALLING);
attachInterrupt(ss_button_pin, ISR_ss_button_pressed, FALLING);
}

void loop() {
  switch (current_state)
  {
  case IDLE:
    counter = 0;
    if (ss_button_pressed){
      current_state = RUNNING;
      ss_button_pressed = false;
    }
    if (reset_button_pressed){
      reset_button_pressed = false;
    }
    break;
  
  case RUNNING:
    counter++;
    if(ss_button_pressed){
      current_state = PAUSED;
      ss_button_pressed = false;
    }
    if(reset_button_pressed){
      current_state = IDLE;
      reset_button_pressed = false;
    }
    break;

  case PAUSED:
    if(ss_button_pressed){
      current_state = RUNNING;
      ss_button_pressed = false;
    }
    if(reset_button_pressed){
      current_state = IDLE;
      reset_button_pressed = false;
    }
    break;

  default:
    break;
  }
  Serial.println(counter);
}




void ISR_ss_button_pressed()
{
ss_button_pressed = true;
}


void ISR_reset_button_pressed()
{
reset_button_pressed = true;
}
