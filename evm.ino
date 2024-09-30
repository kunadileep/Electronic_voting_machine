#include <Keypad.h>
#include <LiquidCrystal.h>
//rs=12,rw=gnd e=11
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[numRows] = {A0, A1, A2, A3};
byte colPins[numCols] = {10, 9, 8, 7};
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
int LCDrow = 0;
int input_size = 0;

String input = "";
String admin_pwd = "997";
int parties = 10;
int* votes = new int[parties];

void displayMessage(String message) {
  lcd.clear();
  lcd.print(message);
}

void Welcome_Message() {
  lcd.clear();
  lcd.print("Welcome Please");
  lcd.setCursor(0, 1);
  lcd.print("cast your vote");
  delay(1500);
  lcd.clear();
  lcd.print("Press A::Admin ");
  lcd.setCursor(1, 1);
  lcd.print("B::Voter");
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Welcome_Message();
}

void loop() {
  char key = myKeypad.getKey();
  static byte first = 0; // Initialize 'first' only once

  if (key != NO_KEY) {
    if (!first) {
      lcd.clear();
      first = 1;
    }

    lcd.print(key);
    lcd.blink();
    if (key == '*') {
      lcd.clear();
      input = "";
    } else if (key == '#') {
      handleInput();
    } else {
      input += key;
    }
  }
}

void handleInput() {
  if (input.length() > 1) {
    lcd.clear();
    lcd.println("Invalid Input!!");
    input = "";
    delay(2000);
   Welcome_Message();
  }
  else {
    if (input == "A") {
      if (check_pwd()) {
        lcd.clear();
        lcd.clear();
        lcd.println("Please enter");
        lcd.setCursor(0, 1);
        lcd.println("the code");
        delay(1500);
        String code = take_input();
        lcd.clear();
        lcd.print(code);
        if (code == "C") {
          // Handle Result
          print_result();
          delay(3000);
          input="";
         Welcome_Message();
        }
        else if (code == "D") {
          // Handle Reset
          for (int i = 0; i < parties; i++) {
            votes[i] = 0;
          }
          lcd.clear();
          lcd.print("Reset");
          lcd.setCursor(0, 1);
          lcd.print("successful!!");
          delay(2000);
          input="";
Welcome_Message();
        }
        else if (code == "CC") {
          // Handle printing parties with votes
          for (int i = 0; i < parties; i++) {
            displayMessage(String(i) + ":" + String(votes[i]));
            delay(1000);
          }
        input="";
        Welcome_Message();
        }
        else if (code == "DD") {
          lcd.clear();
          lcd.print("Enter number of");
          lcd.setCursor(0, 1);
          lcd.print("parties");
          delay(1500);
          int num_party = take_input().toInt();
          delete[] votes;
          parties = num_party;
          votes = new int[num_party];
          input = "";
          lcd.clear();
          displayMessage("Parties set");
          lcd.setCursor(0,1);
          lcd.print("to: "+String(parties));
          delay(1500);input="";
         Welcome_Message();
        }
        else {
          lcd.clear();
          lcd.println("Invalid code");
          delay(2000);input="";
         Welcome_Message();
        }
      }
    }
    else if (input == "B") {
      if (check_pwd()){
      displayMessage("Enter party num:");
      String input_str = take_input();
      if (!containsAlphabet(input_str)) {
        int input_int = input_str.toInt();
        if (input_int >= 0 && input_int < parties) {
          votes[input_int]++;
          lcd.clear();
          lcd.print("Successfully");
          lcd.setCursor(0, 1);
          lcd.print("casted");
          delay(1500);
        Welcome_Message();
          input = "";
        }
        else {
          lcd.clear();
          lcd.println("Invalid input");
          delay(1000);
          lcd.clear();
          lcd.println("Press A::Admin ");
          lcd.setCursor(1, 4);
          lcd.print("B::Voter");
          input = "";
        }
      }
      else {
        lcd.clear();
        lcd.println("Invalid input");
        input = "";
        delay(2000);input="";
       Welcome_Message();
      }
    }
       
        
    }
    else {
      lcd.clear();
      lcd.println("Invalid input");
      input = "";
      delay(2000);
    Welcome_Message();
    }
  }
}

int check_pwd() {
  lcd.clear();
  lcd.print("enter admin");
  lcd.setCursor(0, 1);
  lcd.print("password");
  String inpt_pwd = "";
  int first=0;
 //  lcd.setCursor(0,1);
  while (true) {
    char key = myKeypad.getKey();
    if (key != NO_KEY) {
       
    if(!first)
      { lcd.clear();first=1;}
      lcd.print("*");
      lcd.blink();
      if (inpt_pwd.length() > 3) {
        lcd.clear();
        lcd.print("enter admin");
        lcd.setCursor(0, 1);
        lcd.print("password");
        return 0;
      }
      if (key == '#') {
        if (inpt_pwd == admin_pwd) {
          return 1;
        }
        lcd.clear();
        lcd.print("enter admin");
        lcd.setCursor(0, 1);
        lcd.print("password");
        return 0;
      }
      else if (key != '*') {
        inpt_pwd += key;
      }
      else {
        lcd.clear();
        inpt_pwd = "";
      }
    }
  }
}

String take_input() {
  String input = "";
  int first=0;
  //lcd.setCursor(0,1);
  while (true) {
    char key = myKeypad.getKey();
    if (key != NO_KEY) {
     if(!first)
      { lcd.clear();first=1;}
      lcd.print(key);
      lcd.blink();
      if (key == '*') {
        lcd.clear();
        input = "";
      }
      else if (key != '#') {
        input += key;
      }
      if (key == '#') {
        return input;
      }
    }
  }
}

void print_result() {
  int winner = 0;
  int maxi = -1;

  for (int i = 0; i < parties; i++) {
    if (winner < votes[i]) {
      winner = votes[i];
      maxi = i;
    }
  }

  int cnt = 0;
  for (int i = 0; i < parties; i++) {
    if (winner == votes[i]) {
      cnt++;
    }
  }

  if (cnt > 1) {
    displayMessage("!!Tie!!");
  } else {
    displayMessage("Winner: " + String(maxi));
  }
}

bool containsAlphabet(const String &str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (isAlpha(str.charAt(i))) {
      return true;
    }
  }
  return false;
}
