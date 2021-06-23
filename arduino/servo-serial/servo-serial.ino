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
const int OPEN_ANGLE = 120;

/**
 * Angle when the servo is in closed state.
 */
const int CLOSE_ANGLE = 0;

/**
 * Set up serial, push button and attach the servo.
 */
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  servo.attach(SERVO_PIN);
}

/**
 * Returns true if the button is pressed, otherwise false.
 */
static bool isButtonPressed() {
  return digitalRead(BUTTON_PIN) == HIGH;
}

/**
 * Returns true if there's a 1 read on serial.
 */
static bool isSerialOne() {
  while (Serial.available() > 0) {
    if (Serial.parseInt() == 1) {
      return true;
    }
  }
  return false;
}

/**
 * Checks whether the door should be opened or not.
 */
static bool shouldOpenDoor() {
  return isButtonPressed() || isSerialOne();
}

/**
 *
 */
void loop() {
  if (shouldOpenDoor()) {
    Serial.println("Opening door!");
    servo.write(OPEN_ANGLE);
    delay(OPEN_DELAY);
  } else {
    servo.write(CLOSE_ANGLE);
    delay(20);
  }
}
