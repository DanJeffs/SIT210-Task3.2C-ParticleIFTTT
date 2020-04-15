// This #include statement was automatically added by the Particle IDE.
#include <BH1750Lib.h>

//********************************************************************
// BH1750Lib for Spark
// http://github.com/davidegironi/spark-bh1750lib
// Copyright (c) Davide Gironi, 2014 
//
// References:
//   https://github.com/claws/BH1750/
//
// Released under GPLv3.
// Please refer to LICENSE file for licensing information.
//********************************************************************

//debug to serial port
#define UARTDEBUG 0

//initialize devide
BH1750Lib bh1750;

//int to check for notification already sent.
int lastCheck = 2;

void setup() {

bh1750.begin(BH1750LIB_MODE_CONTINUOUSHIGHRES);
  
#if UARTDEBUG == 1
    Serial.begin(9600);
    Serial.println("Starting...");
#endif
}

void loop() {

    uint16_t luxvalue = bh1750.lightLevel();

    char Lux[64];
    sprintf(Lux,"%d",luxvalue);
    Spark.variable("Lux",Lux);
    Particle.publish("Lux",Lux);
    
    if (luxvalue > 50 && lastCheck == 1){
        Particle.publish("Lux", "high", PUBLIC);
        lastCheck = 2;
    }
    else if (luxvalue < 49 && lastCheck == 2){
        Particle.publish("Lux", "low" , PUBLIC);
        lastCheck = 1;
    }
    
    
#if UARTDEBUG == 1
    //read
    Serial.print("Light: ");
    Serial.print(luxvalue);
    Serial.println(" lux");
#endif
    
    //wait for the next reading
    delay(2000);
}
