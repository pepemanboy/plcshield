#include <plcshield.h>
void setup() {
  // put your setup code here, to run once:
  plc_setup();

  
  plc_lcd.noBlink(); // Cursor does not blink  
  plc_lcd.noCursor(); // Hide cursor
  
  plc_lcd.clear(); // Clear the screen   
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  plc_lcd.clear(); // Clear the screen 
  for(i = 1; i <= 6; i ++){
    plc_digitalWrite(i,plc_digitalRead(i));

    plc_lcd.setCursor(((i-1)%3)*4,(i-1)/3); // Set the cursor in Column 0, Row 0 of the LCD  

    String s =  String(plc_analogRead(i), DEC); 
    plc_lcd.print(s); // Print this text where the cursor is
  }
  for(i = 1; i <= 3; i++){
    plc_lcd.setCursor(12+i,0);
    String s =  String(plc_buttonRead(i), DEC); 
    plc_lcd.print(s);
  }
  
  
  delay(1000);  
}


