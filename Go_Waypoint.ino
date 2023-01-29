
void goWaypoint()
{   
 Serial3.println("Go to Waypoint");
//Serial.print("Home_Latarray ");
//Serial.print(Home_LATarray[ac],6);
//Serial.print(" ");
//Serial.println(Home_LONarray[ac],6);   

//Serial3.print("Distance to Home");   
//Serial3.print(Distance_To_Home);

//Serial3.print("ac= ");
//Serial3.print(ac);

 while (true)  
  {                                                                // Start of Go_Home procedure 
  bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
  if (blueToothVal == 5){break;}                                   // If a 'Stop' Bluetooth command is received then break from the Loop
  getCompass();                                                    // Update Compass heading                                          
  getGPS();                                                        // Tiny GPS function that retrieves GPS data - update GPS location// delay time changed from 100 to 10
  
  if (millis() > 5000 && gps.charsProcessed() < 10)                // If no Data from GPS within 5 seconds then send error
    Serial3.println(F("No GPS data: check wiring"));     
  cur_lat = gps.location.lat();
  cur_lon = gps.location.lng();
  Distance_To_Home = TinyGPSPlus::distanceBetween(cur_lat,cur_lon,Home_LATarray, Home_LONarray);  //Query Tiny GPS for Distance to Destination
  GPS_Course = TinyGPSPlus::courseTo(cur_lat,cur_lon,Home_LATarray,Home_LONarray);                               //Query Tiny GPS for Course to Destination
  Serial3.print("distnace is: ");
  Serial3.println(Distance_To_Home, 7);
  Serial3.print("home lat is: ");
  Serial3.println(Home_LATarray, 7);
   
   /*
    if (Home_LATarray[ac] == 0) {
      Serial3.print("End of Waypoints");
      StopCar();      
      break;
      }      
   */ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  inches = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    if(inches <= 10){
        motor1.run(RELEASE);                                                         
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        delay(100); 
        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);    
        
        motor1.run(BACKWARD);                                                        // Turn left
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(BACKWARD);
        delay(100); 
        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);    
        
        motor1.run(BACKWARD);                                                        // Turn left
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(BACKWARD);
        delay(100);                            

        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);    
        
        motor1.run(BACKWARD);                                                        // Turn left
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(BACKWARD);
        delay(100); 

        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);    
        
        motor1.run(BACKWARD);                                                        // Turn left
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(BACKWARD);
        delay(100); 

         motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);
        motor1.run(FORWARD);                                                         // go forward all wheels 
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        delay(100); 
        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);
        motor1.run(FORWARD);                                                         // go forward all wheels 
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        delay(100); 


        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);   
      
        motor1.run(FORWARD);                                              
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);
        delay(100); 

        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);   
      
        motor1.run(FORWARD);                                              
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);
        delay(100); 
        

        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);   
      
        motor1.run(FORWARD);                                              
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);
        delay(100); 

        motor1.setSpeed(mtr_Spd);                                                   
        motor2.setSpeed(mtr_Spd);     
        motor3.setSpeed(mtr_Spd);     
        motor4.setSpeed(mtr_Spd);   
      
        motor1.run(FORWARD);                                              
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);
        delay(100); 
  }
    if (Distance_To_Home <= 3)                                   // If the Vehicle has reached it's Destination, then Stop
        {
        StopCar();                                               // Stop the robot after each waypoint is reached
        Serial3.println("You have arrived!");                    // Print to Bluetooth device - "You have arrived"          
        ac++;                                                    // increment counter for next waypoint
        break;                                                   // Break from Go_Home procedure and send control back to the Void Loop 
                                                                 // go to next waypoint
        
        }   
   
   
   if ( abs(GPS_Course - compass_heading) <= 100)                  // If GPS Course and the Compass Heading are within x degrees of each other then go Forward                                                                  
                                                                  // otherwise find the shortest turn radius and turn left or right  
       {
         Forward();                                               // Go Forward
       } else 
         {                                                       
            int x = (GPS_Course - 360);                           // x = the GPS desired heading - 360
            int y = (compass_heading - (x));                      // y = the Compass heading - x
            int z = (y - 360);                                    // z = y - 360
            
            if ((z <= 180) && (z >= 0))                           // if z is less than 180 and not a negative value then turn left otherwise turn right
                  { SlowLeftTurn();  }
             else { SlowRightTurn(); }               
        } 
    cur_lat = 0 ;
    cur_lon =0 ;
  }                                                              // End of While Loop

  
}                                                                // End of Go_Home procedure
