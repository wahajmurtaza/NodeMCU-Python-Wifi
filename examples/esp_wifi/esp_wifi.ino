
/* This example is written for Nodemcu Modules */

#include "ESP_Wahaj.h" // importing our library

# define led D4
int pwm = 255;
String path = "nothing";
void setup(){
  Serial.begin(9600);
  start("ssid","password");  // Wifi details connect to
  

}

void loop(){
  //waitUntilNewReq();  //Waits until a new request from python come

  if(CheckNewReq() == 1)
  {
    //Serial.println("new request");
    if (getPath()=="/two"){
    returnThisStr("two replied");
    }
    else if (getPath()=="/one"){
    returnThisStr("one replied");
    }
    else if(getPath()=="/favicon.ico"){   //this happens for browsers only.
      returnThisStr("garbage");
    }

    else        //here we receive data. You can receive pwm255 and the decode it to 255 and also get more variables like this
    {
      path = getPath();
      Serial.println(path);   //String
      //returnThisStr("nothing");
      path.remove(0,1);    //Remove slash /
      Serial.println(path);
      pwm = path.toInt();    //convert to int you can use toFloat()
      Serial.println(pwm);
    }
    
  }
  
//Serial.println("tesiting....");
//if(pwm == 255) Serial.println("highhhhh");
//if(pwm == 0) Serial.println("lowwwwsssh");
//analogWrite(led,pwm);
  
}