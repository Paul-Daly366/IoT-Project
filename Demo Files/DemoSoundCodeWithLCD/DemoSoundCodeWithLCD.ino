#include <Wire.h>
#include "rgb_lcd.h"
#include <driver/i2s.h>
rgb_lcd lcd;

/* LCD wires: Yellow - 22, White - 21 */
#define I2S_SCK 17
#define I2S_WS 18
#define I2S_SD 16
#define I2S_PORT I2S_NUM_0

const int soundThreshold = 500;
const int bufferLen = 1024;

int16_t sBuffer[bufferLen];
int16_t audioData;  // Variable to store 16-bit audio data from microphone
size_t bytesRead, bytesIn = 0;   // Variable to store number of bytes read
uint8_t t = 0;

//Returns whether ambient sound is loud or low
String getSound(){
  //
  String soundValue = "";
  bytesRead = i2s_read(I2S_PORT, &audioData, sizeof(audioData), &bytesIn, portMAX_DELAY);
  int soundIntensity = abs(audioData);
  /*
  //If statement for returning a simple status
  if(soundIntensity > soundThreshold){
    soundValue += "Too loud!";
  }
  else{
    soundValue += "Normal";
  }
  return soundValue;*/
  return (String)soundIntensity;
}

void setup() {
  // put your setup code here, to run once:
  i2s_install();   // Configure and install the I2S driver
  i2s_setpin();    // Set the I2S pins
  i2s_start(I2S_PORT); // Start the I2S receiver
  delay(500);

  lcd.begin(16,2);
  lcd.print("LCD + Sound");
  lcd.setCursor(0,1);
  lcd.print("Snippet");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Sound: ");
  lcd.print(getSound());
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;
}

// ~~ FUNCTIONS TO SETUP I2S WITH INMP441 ~~
// Function to install and configure the I2S driver
void i2s_install() {
    const i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // Set as master receiver
        .sample_rate = 16000,              // Audio sample rate (16kHz)
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // 16-bit per sample
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Use left channel only (mono)
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S), // Standard I2S format
        .intr_alloc_flags = 0,             // No interrupt flags
        .dma_buf_count = 8,                // Number of DMA buffers
        .dma_buf_len = bufferLen,          // Size of each DMA buffer
        .use_apll = false                  // Do not use APLL clock
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL); // Install the driver
}

// Function to set the I2S pinout
void i2s_setpin() {
    const i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,   // Bit clock pin
        .ws_io_num = I2S_WS,     // Word select pin
        .data_out_num = I2S_PIN_NO_CHANGE, // No data output needed (RX only)
        .data_in_num = I2S_SD    // Data input pin (from microphone)
    };

    i2s_set_pin(I2S_PORT, &pin_config); // Apply the pin configuration
}