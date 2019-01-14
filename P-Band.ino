#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B11000011, B00000000,
  B11000011, B00000000,
  B11000011, B00000000,
  B11111111, B00000000,
  B11111111, B00000000,
  B11000011, B00000000,
  B11000011, B00000000,
  B11000011, B00000000,
  B00000000, B11111111,
  B00000000, B11111111,
  B00000000, B00011000,
  B00000000, B00011000,
  B00000000, B00011000,
  B00000000, B00011000,
  B00000000, B00011000,
  B00000000, B00011000};


char ch;
char temp[7];
int h,m,s,flag;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Connect a device first");
  
  do{
        if(Serial.available()>0)
        {
          ch=Serial.read();
        }
  
  }while(ch!='*');
  for(int m=0;m<6;m++)
  {
    while(!Serial.available());
   if(Serial.available()>0)
   {
    temp[m]=Serial.read();
   }
  }
  h=10*(temp[0]-48)+(temp[1]-48);
  m=10*(temp[2]-48)+(temp[3]-48);
  s=10*(temp[4]-48)+(temp[5]-48);
  flag=h;
  if(h>12)
  {
    h=h-12;
  }
}


void loop() {
  // put your main code here, to run repeatedly: 
s=s+1; 
display.setCursor(35,5);
display.print(h);
display.print(":");
display.print(m);
display.print(":");
display.print(s);


if(flag<12)display.println(" AM"); 
if(flag==12)display.println(" PM");
if(flag>12)display.println(" PM");
if(flag==24)flag=0; 
 display.display();
delay(950);

display.clearDisplay();
if(s==60){ 
 s=0; 
 m=m+1; 
} 
if(m==60) 
{ 
 m=0; 
 h=h+1; 
 flag=flag+1; 
} 
if(h==13) 
{ 
 h=1; 
} 
 int sensorValue= analogRead(A0);

  Serial.println(sensorValue);

  display.setCursor(0,15);
  display.print("Air Quality index: ");
  display.print(sensorValue);
  display.display();



}
