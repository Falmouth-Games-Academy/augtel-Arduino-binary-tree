#include <Arduino.h>

bool debug = false;

const int keyPin = 4;      
bool keyPressed = false;
unsigned long keyPressStart = 0;  // the last time the output pin was toggled
unsigned long keyPressEnd = 0;
unsigned long keyPressDelay = 0;
bool keyActive = false;

int morseIndex = 0;

char characters[] = {
  '*','E', 'T', 
  'I', 'A', 'N', 'M', 
  'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O', 
  'H', 'V', 'F', '-', 'L', '-', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '-', '-',
  '5', '4', '-', '3', '-', '-', '-', '2', '&', '-', '+', '-', '-', '-', '-', '-',
  '6', '-', '/', '-', '-', '-', '-', '-', '7', '-', '-', '-', '8', '-', '9', '0'
};
int charactersLength = strlen(characters);

char path[] = {'-', '-', '-', '-', '-'};


struct node
{
  char key_value;
  int index;
  struct node *left;
  struct node *right;
};


bool charActive = false;
unsigned long charBegin;
unsigned long lastActive; 


struct node *root = 0;



void setup() {
  Serial.begin(115200);

  loadCharacters();

  pinMode(keyPin, INPUT_PULLUP);

}

void loop() {

  
  // monitor key state 
  if (digitalRead(keyPin) == LOW && keyPressed == false)
  {
    // init the timing 
    keyPressStart = millis();
    keyPressed = true;
    keyActive = true;
    Serial.println("KEY PRESSED");
  } else if (digitalRead(keyPin) == HIGH && keyPressed == true)
  {
    // init the timing 
    keyPressEnd = millis();
    keyPressed = false;
    Serial.println("KEY RELEASED");
    keyPressDelay = keyPressEnd - keyPressStart;

    // traverse the tree
    if (keyPressDelay < 500) stepPath('l');
    if (keyPressDelay >= 500 && keyPressDelay <= 2000) stepPath('r');

  }

  // Do we need send the char? 
  if (keyActive && !keyPressed){

    int timeInactive = millis() - keyPressEnd;

    // send char after 2 seconds of inactivity
    if (timeInactive > 2000) sendChar();
    
  }

  delay(20);
}

void sendChar(){
  node n = traverse(path, root);
  Serial.println(n.key_value);

  keyActive = false;
  morseIndex = 0;
  clearPath();
}

void stepPath(char dir){
   
  path[morseIndex] = dir;
  Serial.println(dir);
  
  morseIndex++;
  
  if (morseIndex >= 6) {
    morseIndex = 0;
    clearPath();
  }
}

void clearPath(){
  for (int i = 0; i < strlen(path); i++){
    path[i] = '-';
  }
}

