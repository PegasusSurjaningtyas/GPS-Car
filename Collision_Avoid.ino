//
//void Ping()
//{ 
//  currentMillis = millis();
//  
// if ((currentMillis - previousMillis >= interval) && (pingOn == true)) 
// {
//  previousMillis = currentMillis;
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(5);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  pinMode(echoPin, INPUT);
//  duration = pulseIn(echoPin, HIGH);
//  
//  int inches = (duration / 2) / 74;                       // convert the time into a distance
//  Ping_distance == inches;  
// 
//    if ((inches < 12) && (blueToothVal != 5))
//      {
//        Serial3.print("Crash! ");
//        Serial3.println(inches);
//        Reverse();                                        // Quick reverse to Stop quickly
//        delay(100);
//        StopCar();   
//        blueToothVal = 5;                                 // Set bluetooth value to "Stop"
//      } 
//  
//  }       // end if statement
// 
//}         // end Ping()
//
//void pingToggle()                                         // Turns Collision avoidance on/ off
// {
//  if (pingOn == true) {
//    pingOn = false;
//    Serial3.print("Collision Avoidance OFF");
//  }
//    else if (pingOn == false) {
//    pingOn = true;
//    Serial3.print("Collision Avoidance ON");
//  }
//  
// }
