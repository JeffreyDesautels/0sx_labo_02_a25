//code = 2255309

unsigned long current_time = 0;
const int led_pins[] = { 8, 9, 10, 11 };
int potentiometer_pin = A1;
int potentiometer_value = 0;
int led_index = 0;
const int btn_2 = 2;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(btn_2, INPUT_PULLUP);

  Serial.println("Setup completed");
}

void loop() {
  current_time = millis();

  potentiometer_value = analogRead(potentiometer_pin);
  int converted_value = map(potentiometer_value, 0, 1023, 0, 20);

  btn_task(converted_value);
  led_task(converted_value);
}

void btn_task(int cv) {
  static int previous_state = 1;
  static int current_state = 0;
  static int state = 0;
  const int delay = 50;
  const int width = 20;

  static unsigned long last_change = 0;

  current_state = digitalRead(btn_2);

  if (current_state != previous_state) {
    last_change = millis();
  }

  if ((millis() - last_change) > delay) {
    if (current_state != state) {
      if (!current_state) {
        Serial.print("[");
        for (int i = 0; i < width; i++) {
          if (i < cv) {
            Serial.print("#");
          } else {
            Serial.print(".");
          }
        }
        Serial.print("] ");
        Serial.print(cv * 5);
        Serial.println("%");
      }
      state = current_state;
    }
  }

  previous_state = current_state;
}

void led_task(int cv) {
  if (cv < 5) {
    digitalWrite(led_pins[0], HIGH);
    digitalWrite(led_pins[1], LOW);
    digitalWrite(led_pins[2], LOW);
    digitalWrite(led_pins[3], LOW);
  } else if (cv < 10) {
    digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], HIGH);
    digitalWrite(led_pins[2], LOW);
    digitalWrite(led_pins[3], LOW);
  } else if (cv < 15) {
    digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], LOW);
    digitalWrite(led_pins[2], HIGH);
    digitalWrite(led_pins[3], LOW);
  } else {
    digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], LOW);
    digitalWrite(led_pins[2], LOW);
    digitalWrite(led_pins[3], HIGH);
  }
}
