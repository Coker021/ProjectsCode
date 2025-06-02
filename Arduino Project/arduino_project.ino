// C++ code
// Arduino Project

//Implemented a menu system
//Conversion between the 3 main units for measuring temperature by using a potentiometer to get a range of values for conversion
//Used the LCD screen to give visual feedback
//IR remote for navigating the menu
//Project Idea gotten from "https://youtu.be/JmUt9O4c2-c"
//In the video, the person made use of a temperature sensor for the range of values
//But i made use of the Potentiometer, mapped out the range which the user will pick themselves

#include <IRremote.h>
#include <LiquidCrystal.h>
#define IR_RECEIVE_PIN 8

LiquidCrystal lcd(13,12,5,4,3,2);
int value= -1;
int menu = 0;
int data = 0;
int RedLED = 6;
int YellowLED = 7;
int BlueLED = 10;
const int RotationPin = A1;
bool exitLoop = false;



void setup() 
{   
  lcd.begin(16,2);
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(RedLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(RotationPin, INPUT);
  randomSeed(analogRead(0));
  Serial.println("Press the power button to start");
}

void loop(){
  if(IrReceiver.decode()){
    IrReceiver.resume();
    value = IrReceiver.decodedIRData.command; 
    //Serial.println(value);
  }
  
  if(menu==0){
    //check for value
    if(value==0){
      menu=1;
      //show menu 1
      PrintMenu1();
 
    }
  }
  
  else if(menu==1){
    //go to menu 1
     Menu1();
    
    value = -1;
    }
  
    else if(menu==2){
      //go to menu 2
     Menu2();
      
      value = -1;
    }
  
    else if(menu==3){
      //go to menu 3
     Menu3();
      value = -1;
    }
}
      //Creating the menu system
void PrintMenu1(){
  Serial.println("Menu 1:");
  Serial.println("1. Celsius to Farenheit");
  Serial.println("2. Celcius to Kelvin");
  Serial.println("3. Go to Menu 2");
  Serial.println("4. Go to Menu 3");
  Serial.println("5. Display formula to Farenheit");
  Serial.println("6. Display formula to Kelvin");
}
void PrintMenu2(){
  Serial.println("Menu 2:");
  Serial.println("1. Farenheit to Celcius");
  Serial.println("2. Farenheit to Kelvin");
  Serial.println("3. Go to Menu 1");
  Serial.println("4. Go to Menu 3");
  Serial.println("5. Display formula to Celsius");
  Serial.println("6. Display formula to Kelvin");
}
void PrintMenu3(){
  Serial.println("Menu 3:");
  Serial.println("1. Kelvin to Celcius");
  Serial.println("2. Kelvin to Farenheit");
  Serial.println("3. Go to Menu 1");
  Serial.println("4. Go to Menu 2");
  Serial.println("5. Display formula to Celcius");
  Serial.println("6. Display formula to Farenheit");
}

      
void Menu1(){
  
    // function to convert from Celcius to Farenheit
    if(value==16){
      Serial.println("Enter Value for Lowest Celsius point");
      while (!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Celsius point");
      while (!Serial.available());
      int highestPoint = Serial.parseInt();
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      //creating a loop so the value of data keeps updating on the LCD screen
      while(!exitLoop){
        data = analogRead(RotationPin);
        int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
        float answer = ((mappedValue * 1.8) + 32);
        //lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Celcius to Faren");
        clearBottomRow();
        lcd.setCursor(5, 1);
        lcd.print(answer);
        lcd.print(" F");
        delay(100);

      // Update LED status based on the answer
        if(answer < 75){
          digitalWrite(BlueLED, HIGH);
          digitalWrite(YellowLED, LOW);
          digitalWrite(RedLED, LOW);
        }
        else if(answer >= 75 && answer <= 102){
          digitalWrite(BlueLED, LOW);
          digitalWrite(YellowLED, HIGH);
          digitalWrite(RedLED, LOW);
        } 
        else if(answer >= 103){
          digitalWrite(BlueLED, LOW);
          digitalWrite(YellowLED, LOW);
          digitalWrite(RedLED, HIGH);
      }

      // Check for IR command to exit function
        if(IrReceiver.decode()){
          IrReceiver.resume();
          int buttonPressed = IrReceiver.decodedIRData.command;
          if(buttonPressed == 12){
            exitLoop = true;
            menu = 1; // Return to the main menu
            lcd.clear();
        }
      }
    }
    PrintMenu1();
  }
  
  // Handle the conversion from Celsius to Kelvin
    else if(value == 17){
      Serial.println("Enter Value for Lowest Celsius point");
      while (!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Celsius point");
      while (!Serial.available());
      int highestPoint = Serial.parseInt();
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      while(!exitLoop){
        data = analogRead(RotationPin);
        int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
        float answer = (mappedValue + 274);
        //lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Celcius to Kel");
        clearBottomRow();
        lcd.setCursor(5, 1);
        lcd.print(answer);
        lcd.print(" K");
        delay(100);

      // Update LED status based on the answer
        if(answer < 297){
          digitalWrite(BlueLED, HIGH);
          digitalWrite(YellowLED, LOW);
          digitalWrite(RedLED, LOW);
        } 
        else if(answer >= 297 && answer <= 313){
          digitalWrite(BlueLED, LOW);
          digitalWrite(YellowLED, HIGH);
          digitalWrite(RedLED, LOW);
        }
        else if(answer >= 314){
          digitalWrite(BlueLED, LOW);
          digitalWrite(YellowLED, LOW);
          digitalWrite(RedLED, HIGH);
      }

      // Check for IR command to exit function
        if(IrReceiver.decode()){
          IrReceiver.resume();
          int buttonPressed = IrReceiver.decodedIRData.command;
          if(buttonPressed == 12){
            menu = 1; // Return to the main menu
            lcd.clear();
            PrintMenu1();
            break; // Exit the while loop
        }
      }
    }
  } 
  // Go to menu 2
  else if(value == 18){
    menu = 2;
    lcd.clear();
    PrintMenu2();
    delay(50);
  } 
  // Go to menu 3
  else if(value == 20){
    menu = 3;
    lcd.clear();
    PrintMenu3();
    delay(50);
  }
  //displaying formula
  else if(value == 21){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Celcius to Farenheit");
    lcd.setCursor(0,1);
    lcd.print("C * 9/5 + 32");
  }
  //displaying formula
  else if(value == 22){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Celcius to Kelvin");
    lcd.setCursor(0,1);
    lcd.print("C + 273.15");
  }
  // Invalid menu error
  else if(value > 0 && value <= 14 || value >= 24){
    Serial.println("Invalid Menu system");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INVALID");
    lcd.setCursor(0, 1);
    lcd.print("MENU!!");
    delay(1000);
    lcd.clear();
  }

  // Reset the value after processing
  value = -1;
}

void Menu2(){
    // function to convert from Farenheit to Celcius
    if(value==16){
      Serial.println("Enter Value for Lowest Farenheit point");
      while(!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Farenheit point");
      int highestPoint = Serial.parseInt();
      while(!Serial.available());
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      while(!exitLoop){
      data = analogRead(RotationPin);
      int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
      float answer = ((mappedValue - 32) * 0.556);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Faren to Cel");
      clearBottomRow();
      lcd.setCursor(5, 1);
      lcd.print(answer);
      lcd.print(" C");
      delay(100);
      
      // Update LED status based on the answer
      if(answer < 24){
        digitalWrite(BlueLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 24 && answer <= 39){
        digitalWrite(YellowLED, HIGH);
        digitalWrite(BlueLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 40){
        digitalWrite(RedLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(BlueLED, LOW);
      }
      // Check for IR command to exit function
      if (IrReceiver.decode()) {
        IrReceiver.resume();
        int buttonPressed = IrReceiver.decodedIRData.command;
        if (buttonPressed == 12) {
          menu = 2; // Return to the main menu
          lcd.clear();
        }
      }
    }
      PrintMenu2();
   }
    //function to convert from farenheit to kelvin
    else if(value==17){
      Serial.println("Enter Value for Lowest Farenheit point");
      while(!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Farenheit point");
      while(!Serial.available());
      int highestPoint = Serial.parseInt();
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      while(!exitLoop){
      data = analogRead(RotationPin);
      int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
      float answer = ((mappedValue - 32) * 0.556 + 274);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Faren to Kel");
      clearBottomRow();
      lcd.setCursor(5, 1);
      lcd.print(answer);
      lcd.print(" K");
      delay(100);
      if(answer < 297){
        digitalWrite(BlueLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 297 && answer <= 313){
        digitalWrite(YellowLED, HIGH);
        digitalWrite(BlueLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 314){
        digitalWrite(RedLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(BlueLED, LOW);
      }
      if (IrReceiver.decode()) {
        IrReceiver.resume();
        int buttonPressed = IrReceiver.decodedIRData.command;
        if (buttonPressed == 12) {
          menu = 2; // Return to the main menu
          lcd.clear();
          PrintMenu2();
          break; // Exit the while loop
        }
      }
    }
  }
      
  //go to menu 1
  else if(value==18){
    menu=1;
    lcd.clear();
    PrintMenu1();
    delay(50);
  }
  //go to menu 3
  else if(value==20){
    menu=3;
    lcd.clear();
    PrintMenu3();
    delay(50);
  }
  //displaying formula
  else if(value == 21){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Faren to Celcius");
    lcd.setCursor(0,1);
    lcd.print("F-32 * 5/9");
  }
  //displaying formula
  else if(value == 22){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Faren to Kelvin");
    lcd.setCursor(0,1);
    lcd.print("F-32 * 5/9 + 274");
  }
   // Invalid menu error
  else if (value > 0 && value <= 14 || value >= 24) {
    Serial.println("Invalid Menu system");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INVALID");
    lcd.setCursor(0, 1);
    lcd.print("MENU!!");
    delay(1000);
    lcd.clear();
  }

  // Reset the value after processing
  value = -1;
}
void Menu3(){
    // function for converting from Kelvin to Celcius
    if(value==16){
      Serial.println("Enter Value for Lowest Kelvin point");
      while(!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Kelvin point");
      while(!Serial.available());
      int highestPoint = Serial.parseInt();
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      while(!exitLoop){
      data = analogRead(RotationPin);
      int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
      float answer = (mappedValue - 274);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kelvin to Cel");
      clearBottomRow();
      lcd.setCursor(5, 1);
      lcd.print(answer);
      lcd.print(" C");
      delay(100);
      if(answer < 24){
        digitalWrite(BlueLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 24 && answer <= 39){
        digitalWrite(YellowLED, HIGH);
        digitalWrite(BlueLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 40){
        digitalWrite(RedLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(BlueLED, LOW);
      }
      if (IrReceiver.decode()) {
        IrReceiver.resume();
        int buttonPressed = IrReceiver.decodedIRData.command;
        if (buttonPressed == 12){
          exitLoop = true;
          menu = 3; // Return to the main menu
          lcd.clear();
        }
      }
    }
      PrintMenu3();
  }
    //function to convert from kelvin to farenheit
    else if(value==17){
      Serial.println("Enter Value for Lowest Kelvin point");
      while(!Serial.available());
      int lowestPoint = Serial.parseInt();
      Serial.println("Enter Value for Highest Kelvin point");
      while(!Serial.available());
      int highestPoint = Serial.parseInt();
      Serial.println("Press 0 to stop Function");
      bool exitLoop = false;
      while(!exitLoop){
      data = analogRead(RotationPin);
      int mappedValue = map(data, 0, 1023, lowestPoint, highestPoint);
      float answer = ((mappedValue - 274) * 1.8 + 32);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kelvin to Faren");
      clearBottomRow();
      lcd.setCursor(5, 1);
      lcd.print(answer);
      lcd.print(" F");
      delay(100);
      
      if(answer < 67){
        digitalWrite(BlueLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 67 && answer <= 103){
        digitalWrite(YellowLED, HIGH);
        digitalWrite(BlueLED, LOW);
        digitalWrite(RedLED, LOW);
      }
      else if(answer >= 103){
        digitalWrite(RedLED, HIGH);
        digitalWrite(YellowLED, LOW);
        digitalWrite(BlueLED, LOW);
      }
      if(IrReceiver.decode()){
        IrReceiver.resume();
        int buttonPressed = IrReceiver.decodedIRData.command;
        if(buttonPressed == 12){
          menu = 3;
          lcd.clear();
          PrintMenu3();
          break;
        }
      }
    }
  }
  //go to menu 1
  else if(value==18){
    menu=1;
    lcd.clear();
    PrintMenu1();
    delay(50);
  }
  //go to menu 2
  else if(value==20){
    menu=2;
    lcd.clear();
    PrintMenu2();
    delay(50);
  }
  else if(value == 21){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kelvin to Cel.");
    lcd.setCursor(0,1);
    lcd.print("K-273.15");
  }
  //displaying formula
  else if(value == 22){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kelvin to Faren");
    lcd.setCursor(0,1);
    lcd.print("K-274 * 9/5 + 32");
  }
   else if (value > 0 && value <= 14 || value >= 24) {
    Serial.println("Invalid Menu system");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INVALID");
    lcd.setCursor(0, 1);
    lcd.print("MENU!!");
    delay(1000);
    lcd.clear();
  }

  // Reset the value after processing
  value = -1;
}
void clearBottomRow(){
  lcd.setCursor(0, 1);  
  lcd.print("                ");
}