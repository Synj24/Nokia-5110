#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8
#include "font.h";

void LcdWriteString(char *characters)
{
  while(*characters) LcdWriteCharacter(*characters++);
}

void LcdWriteCharacter(char character)
{
  for(int i=0; i<5; i++) LcdWriteData(ASCII[character - 0x20][i]);
  LcdWriteData(0x00);
}

void LcdWriteData(byte dat)
{
digitalWrite(DC, HIGH); //DC pin is high for data
digitalWrite(CE, LOW);
shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
digitalWrite(CE, HIGH);
}

void LcdXY(int x, int y)
{
  LcdWriteCmd(0x80 | x); //column.
  LcdWriteCmd(0x40 | y); //row.
}

void LcdWriteCmd(byte cmd)
{
digitalWrite(DC, LOW); //DC pin is low for commands
digitalWrite(CE, LOW);
shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
digitalWrite(CE, HIGH);
}


void setup()
{
Serial.begin(9600);
pinMode(RST, OUTPUT);
pinMode(CE, OUTPUT);
pinMode(DC, OUTPUT);
pinMode(DIN, OUTPUT);
pinMode(CLK, OUTPUT);
digitalWrite(RST, LOW);
digitalWrite(RST, HIGH); LcdWriteCmd(0x21); // LCD extended commands
LcdWriteCmd(0xBF); // set LCD Vop (contrast)
LcdWriteCmd(0x04); // set temp coefficent
LcdWriteCmd(0x11); // LCD bias mode 1:40
LcdWriteCmd(0x20); // LCD basic commands
LcdWriteCmd(0x0C); // LCD normal video

for(int i=0; i<504; i++) LcdWriteData(0x00); // clear Screen

//LcdXY(0,2);
//LcdWriteString("VOLTAGE:");
}
//
//char string[8];

void loop()
{
//  float voltage = analogRead(A5) * 3.3 / 1024;
//  LcdXY (50,2);
//  LcdWriteString(dtostrf(voltage,5,2,string));
//  Serial.println(voltage);
//  LcdWriteData(0xfe);
//  //LcdWriteData(0x03);
//  //LcdWriteData(0x08);
//  //LcdWriteData(0x30);
//  //LcdWriteData(0x80);
//  delay(2);

LcdWriteData(0x83);
LcdWriteData(0x0F);
LcdWriteData(0x3C);
LcdWriteData(0xF0);
LcdWriteData(0xC1);
delay(2);
}
