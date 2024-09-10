
#define switch_float_pin 3

bool switch_float_flg_initialized = false;
int switch_float_val = 0;
int switch_float_state = LOW; 

unsigned long switch_float_previous_millis_1 = 0;
const long switch_float_period_1 = 101;

bool switch_float_init() {
  pinMode(switch_float_pin, INPUT_PULLUP);
  switch_float_flg_initialized = true;
  return true;
}

bool switch_float_start(unsigned long current_millis) {
  if (!switch_float_flg_initialized)  // to avoid any runtime error in case user missed to initialize
  {
    Serial.println("ERROR in switch_float_start() - switch_float not initialized, call 'switch_float_init()' missed");
    return false;
  }

  if (current_millis - switch_float_previous_millis_1 < switch_float_period_1) {
    return false;
  }

  switch_float_previous_millis_1 = current_millis;

  switch_float_val = digitalRead(switch_float_pin);

  // Serial.print("switch_float_val: ");
  // Serial.println(String(switch_float_val));

  if (switch_float_val == LOW) {           // check if the sensor is LOW
    if (switch_float_state == HIGH) {
      switch_float_state = LOW;       // update variable switch_float_state to LOW
      return true;
    }
  } else {
      delay(200);             // delay 200 milliseconds 
      if (switch_float_state == LOW){
      Serial.println("switch_float detected!"); 
        // Serial.println("Motion stopped!");
        switch_float_state = HIGH;       // update variable state to HIGH
    }
  }
  return false;
}