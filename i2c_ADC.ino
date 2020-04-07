#include <Wire.h>

#define Addr 0x50 //  I2C address
int data;

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  REG_write(0x00,0x80); // 1.置能VCM
  REG_write(0x01,0x00); // 2.設定PGAC0   原始設定
  REG_write(0x02,0x00); // 3.設定PGAC1   原始設定
  REG_write(0x09,0x00); // 4.設定ADCS    原始設定
 // REG_write(0x07,0x20); // 5.設定ADCR0   原始設定 設定工作模式
  REG_write(0x08,0x00); // 5.設定ADCR1   原始設定 控制A/D數據狀態
  REG_write(0x03,0x00); // 6.設定PGACS   原始設定  
  REG_write(0x07,0x02); // 7.設定ADCR0   00000000 開啟工作模式
  
}

void loop()
{/*檢測唯讀暫存器*/
  REG_read(0x04);
  REG_write(0x04,0x02);
  Serial.println("after write");
  REG_read(0x04);
  REG_read(0x05);
  REG_write(0x05,0x02);
  Serial.println("after write");
  REG_read(0x05);
  REG_read(0x06);
  REG_write(0x06,0x02);  
  Serial.println("after write");
  REG_read(0x06);
  Serial.println(" ");
}

void REG_write(int a,int b){

  Wire.beginTransmission(Addr);
  Wire.write(a);  // 進入 暫存器
  Wire.write(b);  // 寫入控制內容
  //Serial.println("write sucess");

  Wire.endTransmission();  // Stop I2C Transmission

}

void REG_read(int a){
  
  Wire.beginTransmission(Addr);
  Wire.write(a);  // 進入 暫存器

  Wire.endTransmission();  // Stop I2C Transmission
  
  Wire.requestFrom(Addr, 1);

  if (Wire.available())
  {
    Serial.print("0x0");
    Serial.print(a);
    Serial.print(" = ");
    data = Wire.read();
    Serial.println(data);   //顯示暫存器的內部狀態
  }
 
  
}
