void calibrateCompass()                                           // Experimental Use Only to Calibrate Magnetometer/ Compass
{
  int minX = 0;
  int maxX = 0;
  int minY = 0;
  int maxY = 0;
  int offX = 0;
  int offY = 0; 

  for (int i=1000; i >= 1; i--) 
  {
  Vector mag = compass.readRaw();                                 // Read compass data
  
  // Determine Min / Max values
  if (mag.XAxis < minX) minX = mag.XAxis;
  if (mag.XAxis > maxX) maxX = mag.XAxis;
  if (mag.YAxis < minY) minY = mag.YAxis;
  if (mag.YAxis > maxY) maxY = mag.YAxis;
  
  offX = (maxX + minX)/2;                                         // Calculate offsets
  offY = (maxY + minY)/2;
  
  delay(10);
  //Serial.print("Compass X & Y offset: ");
  //Serial.print(offX);
  //Serial.print(" ");
  //Serial.print(offY);
  //Serial.print("\n");
  
  }                                                               // end of for loop
  
  StopCar();

  Serial3.print("Compass X & Y offset: ");
  Serial3.print(offX);
  Serial3.print(" ");
  Serial3.print(offY);
  Serial.print("\n");
  compass.setOffset(offX,offY);                                  // Set calibration offset
}
 
 // ************************************************************************************************************************************************* 

void getGPS()                                                 // Get Latest GPS coordinates
{
    while (Serial2.available() > 0)
    gps.encode(Serial2.read());
} 

// *************************************************************************************************************************************************
 
void setWaypoint()                                            // Set up to 5 GPS waypoints
{

//if ((wpCount >= 0) && (wpCount < 50))
if (wpCount >= 0)
  {
    Serial3.print("GPS Waypoint ");
    Serial3.print(wpCount + 1);
    Serial3.print(" Set ");
    getGPS();                                                 // get the latest GPS coordinates
    getCompass();                                             // update latest compass heading     
                                               
//    Home_LATarray[ac] = gps.location.lat();                   // store waypoint in an array   
//    Home_LONarray[ac] = gps.location.lng();                   // store waypoint in an array   
    Home_LATarray = latt;                   // store waypoint in an array   
    Home_LONarray = lon;                   // store waypoint in an array   
                                                              
    Serial.print("Waypoint #1: ");
    Serial.print(Home_LATarray,6);
    Serial.print(" ");
    Serial.println(Home_LONarray,6);

        
  }         
  else {Serial3.print("Waypoints Full");}
}

// ************************************************************************************************************************************************* 

void clearWaypoints()
{
   Home_LATarray = 0; 
   Home_LONarray = 0;
}

 // *************************************************************************************************************************************************
 
void getCompass()                                               // get latest compass value
 {  

  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
 
  if(heading < 0)
     heading += 2 * M_PI;      
  compass_heading = (int)(heading * 180/M_PI);                   // assign compass calculation to variable (compass_heading) and convert to integer to remove decimal places                                                              

 }

 // *************************************************************************************************************************************************

void setHeading()
                                                                 // This procedure will set the current heading and the Heading(s) of the robot going away and returning using opposing degrees from 0 to 360;
                                                                 // for instance, if the car is leaving on a 0 degree path (North), it will return on a 180 degree path (South)
{
   for (int i=0; i <= 5; i++)                                    // Take several readings from the compass to insure accuracy
      { 
        getCompass();                                            // get the current compass heading
      }                                               
    
    desired_heading = compass_heading;                           // set the desired heading to equal the current compass heading
    Heading_A = compass_heading;                                 // Set Heading A to current compass 
    Heading_B = compass_heading + 180;                           // Set Heading B to current compass heading + 180  

      if (Heading_B >= 360)                                      // if the heading is greater than 360 then subtract 360 from it, heading must be between 0 and 360
         {
          Heading_B = Heading_B - 360;
         }
     
    Serial3.print("Compass Heading Set: "); 
    Serial3.print(compass_heading);   
    Serial3.print(" Degrees");

    Serial.print("desired heading");
    Serial.println(desired_heading);
    Serial.print("compass heading");
    Serial.println(compass_heading);

}

// *************************************************************************************************************************************************
 
void gpsInfo()                                                  // displays Satellite data to user
  {
        Number_of_SATS = (int)(gps.satellites.value());         //Query Tiny GPS for the number of Satellites Acquired 
        Distance_To_Home = TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),Home_LATarray, Home_LONarray);  //Query Tiny GPS for Distance to Destination    
        Serial3.print("Lat:");
        latt = gps.location.lat();
//        Serial3.print(gps.location.lat(),6);
        Serial3.print(latt,6);
        Serial3.print(" Lon:");
//        Serial3.print(gps.location.lng(),6);
        lon = gps.location.lng();
        Serial3.print(lon,6);
        Serial3.print(" ");
        Serial3.print(Number_of_SATS); 
        Serial3.print(" SATs ");
        Serial3.print(Distance_To_Home);
        Serial3.print("m"); 
Serial.print("Distance to Home ");
Serial.println(Distance_To_Home);
  
  }
