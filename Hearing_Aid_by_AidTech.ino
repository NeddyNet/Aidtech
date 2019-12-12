#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); //initializing an LCD screen called lcd, address: default 0x27, size 16 x 2 (32 chars)

//Setup that runs once
void setup() {
  
  int Vibration_Pin = 2;  //Int refereance for output pin      
  int Shock = 400;        // Shock is a vibration(VIB) of 0.4 seconds
  int Short = 2000;       // Short is a vibration(VIB) of 2 second
  int Long = 4000;        // Long is a vibration(VIB) of 4 second 
        
  // opens serial port, sets data rate to 9600 bps
  Serial.begin (9600);

  //set Output pin : Currently set to 2
  pinMode (Vibration_Pin,OUTPUT);

  //Initailzing The LCD screen
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(3,0);           //Printing Welcome to Hearing Aid By AidTech    *Please keep it for CopyRigth
  lcd.print("Welcome to");
  delay(1500); 
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Hearing  Aid");
  lcd.setCursor(3,1);
  lcd.print("By AidTech");
  delay(2000); 
  lcd.clear();
  
  lcd.setCursor(2,0);           //Printing Reminder of Vibrations
  lcd.print("reminder  of");
  lcd.setCursor(3,1);
  lcd.print("Vibrations");
  delay(1500); 
  lcd.clear();
  
  lcd.setCursor(2,0);          //Printing Shock 0.4 Sec and produce the related vibration
  lcd.print("Shock 0.4 Sec");
  delay(1500);
  VIB_Function(Shock,Vibration_Pin);  
  lcd.clear();
  
  lcd.setCursor(3,0);          //Printing Short 2 Sec and produce the related vibration
  lcd.print("Short 2 Sec");
  delay(1500);
  VIB_Function(Short,Vibration_Pin);
  lcd.clear();
  
  lcd.setCursor(3,0);          //Printing Long 4 Sec and produce the related vibration
  lcd.print("Long 4 Sec");
  delay(1500); 
  VIB_Function(Long,Vibration_Pin); 
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("Hearing  Aid");
  lcd.setCursor(3,1);
  lcd.print("By AidTech");
  
}

void loop() {
  // put your main code here, to run repeatedly:
      
  
    //Check if a bluetooth message is recieved
    if(Serial.available()){        

      int Vibration_Pin = 2;  //Int refereance for output pin
      String Text = "";       //String Variable to hold text recieved from bluetooth Client
      int Shock = 400;        // Shock is a vibration(VIB) of 0.4 seconds
      int Short = 2000;       // Short is a vibration(VIB) of 2 second
      int Long = 4000;        // Long is a vibration(VIB) of 4 second 
      
      //Wait until entir message arrives
      delay(100);  
      
      //Clear the LCD         
      lcd.clear();
      
      //Set Text equal to message recieved and char array to hold tect as characters
      Text = Serial.readString();
      Text.toLowerCase();
      
      //print Text On LCD screen regadless of it's existance in the dictionary with maximum display of 32 chars (LCD 16*2)
      for(int i = 0;i<Text.length();i++){
          if(i<16){
            lcd.print(Text[i]);
          }
          else{
            lcd.setCursor(i-16,1);
            lcd.print(Text[i]);
          }
      }

      
      // Vibration of word "Hi" and it's synonyms  (Ref. No. 1)
      if( Text == "hi" || Text == "hello" || Text == "hey" || Text == "greetings" ){
        VIB_Function(Shock,Vibration_Pin);  
      }

      // Vibration of word "Thanks" and it's synonyms  (Ref. No. 2)
      else if(Text == "thanks" || Text == "thank you" || Text == "thank you very much" || Text == "thanks a lot"  ){
        VIB_Function(Shock,Vibration_Pin);
        VIB_Function(Shock,Vibration_Pin);       
      }

      // Vibration of word "Bye" and it's synonyms  (Ref. No. 3)
      else if(Text == "bye" || Text == "goodbye" || Text == "cya" ){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin);     
      }

      // Vibration of word "Good morning" and it's synonyms  (Ref. No. 4)
      else if(Text == "good morning" || Text == "have a good morning"){
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of word "Good afternoon" and it's synonyms  (Ref. No. 5)
      else if(Text == "good afternoon"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of word "Good evening" and it's synonyms  (Ref. No. 6)
      else if(Text == "good evening" || Text == "have a good evening") {
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of word "Good night" and it's synonyms  (Ref. No. 7)
      else if(Text == "night" || Text == "good night" || Text == "nighty" || Text == "have a good night" || Text == "sweet dreams"){
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "How are you" and it's synonyms  (Ref. No. 8)
      else if(Text == "how are you" || Text == "how are you doing" || Text == "how is your day"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "What is your name" and it's synonyms  (Ref. No. 9)
      else if(Text == "what is your name" || Text == "what's your name" || Text == "your name please"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "Are you hungry" and it's synonyms  (Ref. No. 10)
      else if(Text == "are you hungry" || Text == "do you want to eat" || Text == "do you want food"){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of TEXT "How many do you want" and it's synonyms  (Ref. No. 11)
      else if(Text == "how many" || Text == "how many do you want" || Text == "how many do you need"){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "Are you cold" and it's synonyms  (Ref. No. 12)
      else if(Text == "are you cold" || Text == "do you feel cold" || Text == "are you feeling cold" ){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
      }

      // Vibration of TEXT "how is the weather outside" and it's synonyms  (Ref. No. 13)
      else if(Text == "how is the weather" || Text == "how is the weather outside" || Text == "is the weather good" || Text == "is it cold outside" || Text == "is it hot outside"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "How can I go there" and it's synonyms  (Ref. No. 14)
      else if(Text == "how can i go there" || Text == "can you tell me the way" || Text == "where is it" || Text == "can you guide me" || Text == "what are the directions"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Shock,Vibration_Pin); 
      }

      // Vibration of TEXT "Do you have any plans" and it's synonyms  (Ref. No. 15)
      else if(Text == "do you have any plans" || Text == "are you busy" || Text == "you busy" || Text == "any plans today" || Text == "do you have anything after class"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of TEXT "Today" and it's synonyms  (Ref. No. 16)
      else if(Text == "today" || Text == "this day" || Text == "tonight"){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of TEXT "Tomorrow" and it's synonyms  (Ref. No. 17)
      else if(Text == "tomorrow" || Text == "next day" || Text == "tomorrow night" || Text == "tomorrow morning" || Text == "anytime tomorrow"){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "This week" and it's synonyms  (Ref. No. 18)
      else if(Text == "this week" || Text == "within the week" || Text == "within this week" || Text == "later this week"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin);
      }
        

      // Vibration of TEXT "Happy Birthday to you" and it's synonyms (Ref. No. 19)
      else if(Text == "happy birthday" || Text == "happy birthday to you" || Text == "happy birthday my friend" || Text == "wish you a year full of happiness"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "What would you like to drink" and it's synonyms  (Ref. No. 20)
      else if(Text == "what would you like to drink" || Text == "do you want to drink anything" || Text == "do you want a drink" || Text == "would you like a drink" || Text == "do you want a hot drink" || Text == "do you want a cold drink"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
      }

      // Vibration of TEXT "What would you like to eat" and it's synonyms  (Ref. No. 21)
      else if(Text == "what would you like to eat" || Text == "what meal would you like" || Text == "what do you want to eat" || Text == "what food do you prefer" || Text == "any preferable food" || Text == "any preferable meal"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of TEXT "Let’s go" and it's synonyms  (Ref. No. 22)
      else if(Text == "let’s go" || Text == "do you want to leave" || Text == "let’s leave" ||  Text == "do you want to go somewhere else" ){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin);  
      }

      // Vibration of TEXT "Are you single" and it's synonyms  (Ref. No. 23)
      else if(Text == "are you single" ||  Text == "are you not married" ){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "Did you like it" and it's synonyms  (Ref. No. 24)
      else if(Text == "did you like it" || Text == "do you like it" || Text == "how is it" || Text == "is it good"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
      }

      // Vibration of TEXT "Do you want a cigarette" and it's synonyms  (Ref. No. 25)
      else if(Text == "do you want a cigarette" || Text == "do you want to smoke"){
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Long,Vibration_Pin);  
      }

      // Vibration of TEXT "please" and it's synonyms  (Ref. No. 26)
      else if(Text == "please" || Text == "would you please" || Text == "can you please"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Shock,Vibration_Pin); 
      }

      // Vibration of TEXT "How may I help you" and it's synonyms  (Ref. No. 27)
      else if(Text == "how may i help you" || Text == "how can i help you" || Text == "do you need help"){
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Long,Vibration_Pin);  
        VIB_Function(Short,Vibration_Pin); 
      }

      // Vibration of TEXT "Did we pass" and it's synonyms  (Ref. No. 28)
      else if(Text == "did we pass"){
        VIB_Function(Shock,Vibration_Pin); 
        VIB_Function(Short,Vibration_Pin); 
        VIB_Function(Shock,Vibration_Pin); 
      }
      

      //If text doesn't exist perform special vibration 10 fast vibrations refering to "look at LCD screen"
      else{
        int VIB_delay = 200;    // the delay that occurs between different vibrations(VIB) 0.2 seconds
        for(int i = 0;i<10;i++){
        digitalWrite (Vibration_Pin,HIGH); //High voltage(Vibrates)
              delay (VIB_delay);
              lcd.noBacklight();
        digitalWrite (Vibration_Pin,LOW);  //Low voltage(stops-vibration)
              delay (VIB_delay);
              lcd.backlight();
        }
      }
   }
}

void VIB_Function(int VIB,int pin){
  
    int VIB_delay = 200;    // the delay that occurs between different vibrations(VIB) 0.2 seconds
    
    digitalWrite (pin,HIGH); //High voltage(Vibrates)
              delay (VIB);
              lcd.noBacklight();
    digitalWrite (pin,LOW);  //Low voltage(stops-vibration)
              delay (VIB_delay);
              lcd.backlight();  
}
