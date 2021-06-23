/**
 * Turns a servo to open a door knob by taking input from serial
 * or by pushing a button.
 */
 #include <Servo.h>

/**
 * Servo object.
 */
Servo servo;

/**
 * Pin for reading push button state.
 */
const int BUTTON_PIN = A0;

/**
 * Pin for the servo motor.
 */
const int SERVO_PIN = 6;

/**
 * Time in ms to keep the servo in the opened state.
 */
const int OPEN_DELAY = 2000;

/**
 * Angle when the servo is in opened state.
 */
const int OPENED_ANGLE = 120;

/**
 * Angle when the servo is in closed state.
 */
const int CLOSED_ANGLE = 0;

/**
 * Set up serial, push button and attach the servo.
 */
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  servo.attach(SERVO_PIN);
}

/**
 * Check button state, read from serial and open/close the servo.
 */
void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Button DOWN");
    servo.write(OPENED_ANGLE);
    delay(OPEN_DELAY);
  } else {
    servo.write(CLOSED_ANGLE);
    delay(20);
  }
}
