
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int doorPin = 2;
int led1 = 5; // กำหนดขาใช้งาน
const int buttonPin = 6;
int buttonState = 0;

const int potPin = 1;
//Variables:
int potValue = 0; //save analog value
// สร้าง Object สำหรับโมดูล PCA9685 ให้ชื่อ pwm ค่า Address คือ Default (0x40)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); 

#define servoAngle  90
#define servoMin  150     // Pulse น้อยสุด กำหนด 150 จาก 4096
#define servoMax  600    // Pulse มากสุด กำหนด 1000 จาก 4096

// bool touch_init();
// bool touch_start(unsigned long current_millis);

// #define switch_float_pin_1 3
// #define switch_button_pin_1 4

// bool dht_init();
// bool dht_start(unsigned long current_millis);

// bool tracker_init();
// bool tracker_start(unsigned long current_millis);

bool relay_init();
bool relay_toggle(int channel);
bool relay_high(int channel);
bool relay_low(int channel);

bool switch_button_init();
bool switch_button_start(unsigned long current_millis);

bool switch_float_init();
bool switch_float_start(unsigned long current_millis);

int shower_heater_level = 0; // 0 time
int shower_heater_state = 0; // 0 prepair, 1 ready, 2 water in, 3 boiling, 4 water out

unsigned long shower_heater_boiling_start_millis = 0;
const long shower_heater_boiling_period =120000; // 2 min
unsigned long shower_heater_waterout_start_millis = 0;
const long shower_heater_waterout_period = 45000; // 45 sec

// relay channel 1 >>> button
// relay channel 2 >>> water in
// relay channel 3 >>> water out

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  unsigned long setup_millis = millis();

  // dht_init();
  relay_init();
  // tracker_init();
  switch_button_init();
  switch_float_init();

  // bool is_dht_detected = dht_start(setup_millis);

  // touch_init();

  // pinMode(switch_float_pin_1, INPUT_PULLUP);
  // pinMode(switch_button_pin_1, INPUT_PULLUP);

  shower_heater_state = 1;
  
  relay_high(1);

  pwm.begin();
  pwm.setPWMFreq(60);     // กำหนด Frequency = 60 Hz (เซอร์โวส่วนใหญ่จะทำงานที่ 50-60 Hz)
  delay(100);
  setServoAngle(15, servoAngle); // turn off switch
  Serial.println(F("----------------- OK -------------------"));

    // pwm.setPWM(15, 4096, 0);       // turns pin fully on
    // delay(100);
    // pwm.setPWM(15, 0, 4096);       // turns pin fully off

    pinMode(led1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา 2 เป็น OUTPUT
    pinMode(buttonPin, INPUT);// กำหนดขาทำหน้าที่ให้ขา 3 เป็น INPUT รับค่าจากสวิตช์
    pinMode(doorPin, INPUT_PULLUP);
    pinMode(potPin, INPUT); //Optional 
    // digitalWrite(led1, LOW);
}

void setServoAngle(uint8_t servoNum, int angle) {
  int pulse = map(angle, 0, 180, servoMin, servoMax);  // แปลงมุมเป็นค่า PWM
  pwm.setPWM(servoNum, 0, pulse);
}

void loop() {

  int potval = analogRead(potPin);          //Read and save analog value from potentiometer
  potval = map(potval, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
  // analogWrite(ledPin, value);
  if (potval != potValue) { 
    potValue = potval;
    Serial.print("potValue > ");
    Serial.println(String(potValue));
  }

  buttonState = digitalRead(buttonPin); // อ่านค่าสถานะขา3
  // Serial.print("buttonState > ");
  // Serial.println(String(buttonState));
  int doorState  = digitalRead(doorPin);
  if (doorState == LOW) { 
    digitalWrite(led1, HIGH); 
    // Serial.print("doorState > ");
    // Serial.println(String(doorState));
  } else {
    if (buttonState == HIGH) { //กำหนดเงื่อนไขถ้าตัวแปล buttonState เก็บ ค่า 1(HIGH) ให้ทำในปีกกา
      digitalWrite(led1, HIGH); // ไฟ LED 1ติด
    }
    else { //ถ้าตัวแปล buttonState ไม่ได้เก็บ ค่า 1(HIGH) คือ ตัวแปล buttonState เก็บค่า 0(LOW) อยู่ ให้ทำปีกกาข้างล่าง
      digitalWrite(led1, LOW); // ไฟ LED 1ดับ
    }
  }

  
  // // หมุนเซอร์โวไปยังมุม 180 องศา
  // setServoAngle(15, 180); 
  // delay(3000);

  // int switch_float_val_1 = digitalRead(switch_float_pin_1);
  // if (switch_float_val_1 == HIGH)
  // {
  //   Serial.println("The switch_float is being pressed.");
  // }
  
  // int switch_button_val_1 = digitalRead(switch_button_pin_1);
  // if (switch_button_val_1 == LOW)
  // {
  //   Serial.println("The switch_button is being pressed.");
  //   relay_toggle(1);
  // }

  unsigned long current_millis = millis();
  // bool is_touch_detected = touch_start(current_millis);
  // bool is_dht_detected = dht_start(current_millis);
  // bool is_tracker_detected = tracker_start(current_millis);
  bool is_switch_button_detected = switch_button_start(current_millis);
  bool is_switch_float_detected = switch_float_start(current_millis);

  if (is_switch_button_detected == true && shower_heater_level <= 2 ) {
    shower_heater_level = shower_heater_level + 1;
  }

  if (shower_heater_level > 0) {
    if (shower_heater_state == 1 && is_switch_button_detected == true) {
      Serial.print("Water in! > ");
      Serial.println(String(shower_heater_level));
      shower_heater_state = 2; // water in
      relay_low(1);
      relay_high(2);
    } else if (shower_heater_state == 2 && is_switch_float_detected == true) {
      
      Serial.print("Boiling! > ");
      Serial.println(String(shower_heater_level));
      shower_heater_state = 3; // boiling

      setServoAngle(15, servoAngle + 26); // turn on switch at 26 degree

      relay_low(2);
      shower_heater_boiling_start_millis = current_millis;
    } else if (shower_heater_state == 3 && current_millis - shower_heater_boiling_start_millis > shower_heater_boiling_period) {
      Serial.print("Water out! > ");
      Serial.println(String(shower_heater_level));
      shower_heater_state = 4; // water out

      setServoAngle(15, servoAngle); // turn off switch

      relay_high(3);
      shower_heater_waterout_start_millis = current_millis;
    } else if (shower_heater_state == 4 && current_millis - shower_heater_waterout_start_millis > shower_heater_waterout_period) {
      
      shower_heater_level = shower_heater_level - 1;

      if (shower_heater_level > 0) { // loop
        Serial.print("Water in! > ");
        Serial.println(String(shower_heater_level));
        shower_heater_state = 2; // water in
        relay_low(1);
        relay_high(2);
        relay_low(3);
      } else {
        Serial.print("Success! > ");
        Serial.println(String(shower_heater_level));
        shower_heater_state = 1; // Success
        relay_high(1);
        relay_low(3);
      }
      
    }
  }
  

  // if (Serial.available() > 0) {
  //     char input = Serial.read();

  //     if (input == '1') {
  //       relay_toggle(1);
  //     } else if (input == '2') {
  //       relay_toggle(2);
  //     } else if (input == '3') {
  //       relay_toggle(3);
  //     } else if (input == '4') {
  //       relay_toggle(4);
  //     } else if (input == '5') {
  //       relay_toggle(5);
  //     }
  // }
  // delay(1);

  //  for (int pulse = servoMin; pulse < servoMax; pulse++){
  //   // ควบคุมเซอร์โวที่ CH0 และ CH15
  //   // pwm.setPWM(0, 0, pulse);
  //   pwm.setPWM(15, 0, pulse);
  // delay(5);
  // }

  // // เมื่อแขนหมุนไปสุดให้ค่อยๆ ลดจาก Max ไปจน Min แขนจะหมุนกลับจาก 180 ลงมาจน 0 องศา
  // for (int pulse = servoMax; pulse > servoMin; pulse--){
  //   // ควบคุมเซอร์โวที่ CH0 และ CH15
  //   // pwm.setPWM(0, 0, pulse);
  //   pwm.setPWM(15, 0, pulse);
  delay(100);
  // }
}
