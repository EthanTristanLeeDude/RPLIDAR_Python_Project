//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "strings.h"


#define RXD2 16
#define TXD2 17

#define DTR  5

char start_scan[3] = {'\xA5','\x20','\0'};                                        //I hope this is the right way to declare hex strings, remember to end with a null character
char stop_scan[3] = {'\xA5','\x25','\0'};                                         //##hex A520
char express_scan[8] = {'\xA5','\x5A','\x05','\x00','\x00','\x40','\x81','\0'};   //##hex A55A0500004081
char get_info[3] = {'\xA5','\x50','\0'};                                          //##hex A550
char force_scan[3] = {'\xA5','\x21','\0'};                                        //##hex A521
char response[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
char input = 0;  
uint8_t quality =0;
uint8_t qualityByte =0;
bool Snot = 0;
bool S = 0;
uint8_t angle_LSB = 0;
uint8_t angle_MSB = 0;
uint8_t distance_LSB = 0;
uint8_t distance_MSB = 0;
uint16_t angle = 0;
uint16_t distance = 0;
int n =0;
uint16_t perimeter[72] = {0};
int16_t perimeter_X[72] = {0};
int16_t perimeter_Y[72] = {0};

//#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
//#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  SerialBT.begin("RPLIDAR-A1M8"); //Bluetooth device name
  //Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(DTR, OUTPUT);
  digitalWrite(DTR, HIGH);   //not sure is this should be high or low yet
}

void loop() {

  if (Serial.available()){
    input = Serial.read();
  }

  if (input=='t'){ 
    Serial2.write(start_scan);
    while (!Serial2.available()){}  //wait for the response
    for(int i=0; i<7; i++){
        response[i] = Serial2.read();
    }
    for(int i=0; i<7; i++){
      Serial.print(response[i],HEX);
    }
    Serial.print("\n\r");
    n=0;
    while (n <=70){
      qualityByte = (int)Serial2.read();
      
      angle_LSB = (int)Serial2.read();
      angle_MSB = (int)Serial2.read();
      distance_LSB = (int)Serial2.read();
      distance_MSB = (int)Serial2.read();
      
      bool Snot = qualityByte & 0b00000010;
      bool S = qualityByte & 0b00000001;
      if (Snot != S){
        quality = qualityByte/4;
      }
      else{
        quality =0;
      }
      angle = (angle_MSB *256 + angle_LSB) /128;        //in degrees
      bool C = angle_LSB & 0b00000001;
      distance = (distance_MSB*256 + distance_LSB)/40;  //in cm
      if((quality ==15 ) && (C==1) && (Snot ==1) ){
        Serial.print(quality,HEX);
        Serial.print(angle_LSB,HEX);
        Serial.print(angle_MSB,HEX);
        Serial.print(distance_LSB,HEX);
        Serial.print(distance_MSB,HEX);
        Serial.print("\n\r");   
        Serial.print("Snot = ");
        Serial.print(Snot);
        Serial.print("\n\r");   
        Serial.print("S = ");
        Serial.print(S);
        Serial.print("\n\r");  
        Serial.print("C = ");
        Serial.print(C);
        Serial.print("\n\r"); 
        Serial.print("quality = ");
        Serial.print(quality);                
        Serial.print("\t");
        Serial.print("angle = ");
        Serial.print(angle);
        Serial.print("\t");
        Serial.print("distance = ");
        Serial.print(distance);
        Serial.print("\n\r");
        if (angle ==1){
          angle  =0;
        }
        else if (angle == 359){
          angle =0;
        }
        else if ((angle -1)%5 ==0){
          angle = angle -1;
        }
        else if ((angle +1) %5 ==0){
          angle  = angle +1;
        }
        if((angle%5 ==0)) {
          if ((uint16_t)(perimeter[(angle)/5]) == 0){
            if (distance !=0){
              n = n+1;
              perimeter[(uint16_t) ((angle)/5)] = distance;
            }
          }
        }
      }
    }
  Serial.print("\n\r");
  Serial.print("done");
  Serial.print("\n\r");  
  Serial2.write(stop_scan);  
  }
  if (input=='p'){ 
    Serial2.write(stop_scan);
  }
  if (input=='e'){ 
    Serial2.write(express_scan);
  }
  if (input=='g'){ 
    Serial2.write(get_info);
    while (!Serial2.available()){}  //wait for the response
    for(int i=0; i<7; i++){
        response[i] = Serial2.read();
    }
    //response[i] = Serial2.readBytes(7,7);
    for(int i=0; i<7; i++){
      Serial.print(response[i],HEX);
    }
    Serial.print("       - done   \n\r");
    Serial.print("\n\r");
  }
  if (input=='f'){ 
    Serial2.write(force_scan);
  }
  if (input=='n'){ 
    Serial.print("\r\n");
  }
  if (input=='o'){ 
    Serial.print("\r\n");
    for(int i = 0 ; i<72; i++){
    Serial.print("angle = ");
    Serial.print(i*5);
    Serial.print("\t");
    Serial.print("distance = ");
    Serial.print(perimeter[i]);
    Serial.print("\r\n");
    }
    Serial.print("angle = 360");
    Serial.print("\t");
    Serial.print("distance = ");
    Serial.print(perimeter[0]);
    Serial.print("\r\n");
    for(int i = 0 ; i<72; i++){
       perimeter[i] =0;
    }
  }
  if (input == 'x'){ //calculate XY coordinates
    Serial.print("\r\n");

    for (int i = 0 ; i<=71 ; i++){
      perimeter_X[i] = perimeter[i]*sin(i*5*3.14/180);
    }
  
    for (int i = 0 ; i<=71 ; i++){
      perimeter_Y[i] = perimeter[i]*cos(i*5*3.14/180);
    } 
  
    for (int i = 0; i <=71; i++){
      //Serial.print("X = ");
      Serial.print(i*5);
      Serial.print(" degrees: ");
      Serial.print("\t");
      Serial.print(perimeter_X[i]);
      Serial.print("\t");
      //Serial.print("Y = ");
      Serial.print(perimeter_Y[i]);
      Serial.print("\r\n");       
    }
  }
  
  if (Serial2.available()) {
    //SerialBT.write(Serial2.read());
    //Serial.write(Serial2.read());
    Serial.print(Serial2.read(),HEX);
    
  }
  if (SerialBT.available()) {
    Serial2.write(SerialBT.read());
  }
  //delay(2);
  //delay(1);
}
