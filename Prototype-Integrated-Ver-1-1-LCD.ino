#include <Wire.h>
#include <LCD-I2C.h>
#include <Adafruit_MLX90614.h>

// Initialize the LCD. Adjust the address if necessary (default is 0x27)
LCD_I2C lcd(0x27, 16, 2);

// Define MPU6050 I2C address
const int MPU = 0x68;

// Variables for accelerometer data
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
float accel_x_g, accel_y_g, accel_z_g;
float accel_total_g;
int steps = 0;

// Create an instance of the MLX90614 temperature sensor
Adafruit_MLX90614 mlx;

void setup() {
  // Initialize I2C communication
  Wire.begin();

  // Initialize the LCD
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();

  // Wake up MPU6050 from sleep mode
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Initialize MLX90614 temperature sensor
  if (!mlx.begin()) {
    lcd.clear();
    lcd.print("MLX sensor error");
    while (1);
  }

  // Initialize serial communication
  Serial.begin(9600);

  // Display initialization message
  lcd.clear();
  lcd.print("Fitness Tracker");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
}

void loop() {
  // Read object temperature from MLX90614
  float objectTemp = mlx.readObjectTempC();

  // Read accelerometer data from MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // Starting register for accelerometer readings
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  // Combine high and low bytes for each axis
  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();

  // Convert raw accelerometer data to 'g' values
  accel_x_g = accelerometer_x / 16384.0;
  accel_y_g = accelerometer_y / 16384.0;
  accel_z_g = accelerometer_z / 16384.0;

  // Calculate total acceleration (magnitude of the 3D vector)
  accel_total_g = sqrt(pow(accel_x_g, 2) + pow(accel_y_g, 2) + pow(accel_z_g, 2));

  // Detect steps based on the acceleration magnitude
  if (accel_total_g > 1.1) {
    steps++;
  }

  // Calculate calories (simplified calculation)
  float calories = steps * 0.05;

  // Display information on LCD
  lcd.clear();
  lcd.print("Steps: ");
  lcd.print(steps);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(objectTemp, 1);
  lcd.print("C");
  delay(2000);

  lcd.clear();
  lcd.print("Calories: ");
  lcd.print(calories, 1);
  lcd.print(" kcal");
  delay(2000);

  // Print to Serial for debugging
  Serial.println("=================================");
  Serial.print("Steps: ");
  Serial.println(steps);
  Serial.print("Temperature: ");
  Serial.println(objectTemp);
  Serial.print("Calories: ");
  Serial.println(calories);

  delay(1000);  // Short delay before next reading
}