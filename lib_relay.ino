
#define relay_pin_1 12
#define relay_pin_2 11
#define relay_pin_3 10
#define relay_pin_4 9
#define relay_pin_5 8

bool relay_flg_initialized = false;
// int relay_val_1 = 0;
// int relay_state = HIGH; 

unsigned long relay_previous_millis_1 = 0;
const long relay_period_1 = 201;

bool relay_init() {
  pinMode(relay_pin_1, OUTPUT);
  pinMode(relay_pin_2, OUTPUT);
  pinMode(relay_pin_3, OUTPUT);
  pinMode(relay_pin_4, OUTPUT);
  pinMode(relay_pin_5, OUTPUT);
  relay_flg_initialized = true;
  return true;
}

bool relay_toggle(int channel) {

  Serial.print("relay: ");
  Serial.print(String(channel));

  int pin_channel;
  if (channel == 1) {
    pin_channel = relay_pin_1;
  } else if (channel == 2) {
    pin_channel = relay_pin_2;
  } else if (channel == 3) {
    pin_channel = relay_pin_3;
  } else if (channel == 4) {
    pin_channel = relay_pin_4;
  } else if (channel == 5) {
    pin_channel = relay_pin_5;
  } else {
  Serial.println(", status: err");
    return false;
  }
  int relay_val = digitalRead(pin_channel);

  Serial.print(", status: ");
  Serial.println(String(relay_val));

  if (relay_val == HIGH) {
    digitalWrite(pin_channel, LOW);
  } else if (relay_val == LOW) {
    digitalWrite(pin_channel, HIGH);
  }
  return true;
}
