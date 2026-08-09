
// to acces to /dev/ttyUSB0 from user 'sudo usermod -a -G dialout $USER'
// IR sensor HW-201 at #2
// DoIt ESP32 DevKit V1
// 0.96 inch OLED DIsplay gm009605v4  - 128x64
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The parameter -1 indicates that the display doesn't share a reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SENSOR_PIN 2 // HW-201 IR sensor

unsigned long lastflash;
int RPM;
void ICACHE_RAM_ATTR sensor_update() {
  RPM++;
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
    // Initialize with the I2C addr 0x3C (most common for GM009605)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED display/SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  } else {
    Serial.println(F("OLED display/SSD1306 is OK"));
  }
  
  delay(1000);
  display.clearDisplay(); // Always clear the buffer first!
  // Display static text
  display.setTextSize(1);             // Normal 1:1 pixel scale  
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 10);             // Start at top-left corner
  display.println(F("GM009605v4 OLED"));
  
  display.setTextSize(2);             // Draw 2X scale text
  display.setCursor(0, 30);
  display.print("RPM: ");  
  display.println(" rps");

  display.display(); // Crucial step: push everything drawn to the hardware screen

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_update, RISING);
}

void loop() {
  noInterrupts();  
  int wings= 2;  // no of wings of rotating object, for disc object use 1 with white tape on one side
  int RPMnew = RPM/wings;  //here we used fan which has 3 wings
  Serial.print(RPM);
  Serial.print(", ");
  Serial.print(RPMnew);
  Serial.print(" Rot/sec :");  //Revolutions per second  
  Serial.print((RPMnew*60));
  Serial.println("Rot/min. ");   //Revolutions per minute  
  RPM=0;  
 
  interrupts(); 
  display.clearDisplay(); // Always clear the buffer first!
  // Display static text
  display.setTextSize(2);             // Draw 2X scale text
  display.setTextColor(SSD1306_WHITE);        // Draw white text  
  display.setCursor(0, 16);
  display.print(F("RpS: "));    
  display.println(RPMnew); 
  display.setCursor(0, 36);
  display.print(F("RpM: "));    
  display.println(RPMnew*60); 
  display.display(); // Crucial step: push everything drawn to the hardware screen  
  //ToDo need to make at least 10 sec for real. 
  delay(1000); //1 sec for real test 
}