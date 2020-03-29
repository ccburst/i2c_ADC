#include <Wire.h>

#define Addr 0x50 //  I2C address

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  REG_write(0x00,0x80); // 1.至能VCM
  REG_write(0x01,0x00); // 2.設定PGAC0   原始設定
  REG_write(0x02,0x00); // 3.設定PGAC1   原始設定
  REG_write(0x09,0x00); // 4.設定ADCS    原始設定
 // REG_write(0x07,0x20); // 5.設定ADCR0   原始設定 設定工作模式
  REG_write(0x08,0x00); // 5.設定ADCR1   原始設定 控制A/D數據狀態
  REG_write(0x03,0x00); // 6.設定PGACS   原始設定  
  REG_write(0x07,0x00); // 7.設定ADCR0   00000000 開啟工作模式
  
}

void REG_write(int a,int b){

  Wire.beginTransmission(Addr);
  Wire.write(a);  // 進入 暫存器
  Wire.write(b);  // 寫入控制內容
//  Serial.println(a);
//  Serial.println(b);
  Wire.endTransmission();  /* Stop I2C Transmission*/

}


void loop()
{
  int data;

  //REG_write(0x07,0x80); // 7.設定ADCR0   00000000 開啟工作模式
  
 // REG_write(0x08,0x04); // 7.設定ADCR0   00000000 開啟工作模式

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Channel Selection
  Wire.write(0x04);  
  
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  
  // Read 1 byte of data
  if (Wire.available())
  {
    //Serial.println(Wire.available());
    data = Wire.read();

    Serial.println(data);
    
    delay(100);
     
  }
  
  Wire.endTransmission();
  REG_write(0x08,0x00); // 7.設定ADCR0   00000000 開啟工作模式
  //REG_write(0x07,0x00); // 7.設定ADCR0   00000000 開啟工作模式
}
