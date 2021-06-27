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
 * Pin for the green LED.
 */
const int GREEN_LED_PIN = 7;

/**
 * Pin for the red LED.
 */
const int RED_LED_PIN = 8;

/**
 * Pin for the servo motor.
 */
const int SERVO_PIN = 9;

/**
 * Angle when the servo is in opened state.
 */
const int OPEN_ANGLE = 120;

/**
 * Angle when the servo is in closed state.
 */
const int CLOSE_ANGLE = 0;

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
 * Blinks the green LED.
 */
static void blinkGreenLED() {
  for (int i = 0; i < 10; ++i) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(100);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(100);
  }
}

/**
 * Opens the door, turns off the red LED and blinks the green LED.
 */
static void openDoor() {
  digitalWrite(RED_LED_PIN, LOW);
  servo.write(OPEN_ANGLE);
  blinkGreenLED();
}

/**
 * Set up serial, push button, LEDs and attach the servo.
 */
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

/**
 *
 */
void loop() {
  if (isButtonPressed()) {
    Serial.println("Opening door using button!");
    openDoor();
  } else if (isSerialOne()) {
    Serial.println("Opening door using serial!");
    openDoor();
  } else {
    servo.write(CLOSE_ANGLE);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(20);
  }
}
