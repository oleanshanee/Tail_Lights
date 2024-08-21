#include <FastLED.h>
#define LEFT_PIN_1 0  //top left brake strip
#define LEFT_PIN_2 1  //botom left brake strip
#define LEFT_PIN_3 2  //top left signal strip
#define LEFT_PIN_4 3  //bottom left signal strip

#define RIGHT_PIN_1 4  //top right brake strip 
#define RIGHT_PIN_2 5  //bottom right brake strip 
#define RIGHT_PIN_3 6  //top right signal strip 
#define RIGHT_PIN_4 7  //bottom right signal strip

#define brakeRunning 8     //The headlight switch signal
#define brakeSwitch 9      //The brake depression signal
#define turnSignalLeft 10   //Left turn signal
#define turnSignalRight 11  //Right turn signal
#define reverseLight 12     //The reverse light signal
#define functionPin A0      //The pin which selects the function in the loop
#define NUM_LEDS 10        //The number of LEDs per strip
#define NUM_STRIPS 8      //The number of strips

//Create a CRGB object for each strip (left and right)
CRGB leftOne[NUM_LEDS];
CRGB leftTwo[NUM_LEDS];
CRGB leftThree[NUM_LEDS];
CRGB leftFour[NUM_LEDS];
CRGB rightOne[NUM_LEDS];
CRGB rightTwo[NUM_LEDS];
CRGB rightThree[NUM_LEDS];
CRGB rightFour[NUM_LEDS];


//Create a pointer array to hold locations of each strip. This way, we can easily make assignments with for loops.
CRGB* ledArray[8] = {leftOne, leftTwo, leftThree, leftFour, rightOne, rightTwo, rightThree, rightFour};
//On the real version in Camry tail lights, a new CRGB* array will need to be made for each block of strips.
//For example, if there ends up being a block in the turn signal area, a block in the brake light are, and a block in the trunk portion, these will all need to have their own CRGB* arrays which will also need to be synced up in each function.




//We have an array which holds pointers to each of the strips.
//The strips can still be accessed individually if wanted. They can also be accessed and assigned by the array in a for loop
//Use something like (ledArray[0])[10] = CRGB(255,255,255); to access a specific LED on a specific row. This means you are accessing the tenth element of leftOne and assigning a CRGB object.
//Now the strips should basically behave like a 2-D array, so it will be easy to draw pixel art and stuff.

//try something like this (ledArray[i])[j, j-1, j-1, j-3] = CRGB(255,0,0);

//Setup of the function potentiometer using pin A5
int functionMapped = 0;
int functionAnalogValue = 0;
unsigned const long flashInterval = 5000;
unsigned long lastBrake = millis();

void setup() {
  //Enable the pullup resistor in the Arudino for the five digital inputs we will use as buttons
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  
  //Add the strips to the FastLED instance
  FastLED.addLeds<WS2812, LEFT_PIN_1, GRB>(leftOne, NUM_LEDS);
  FastLED.addLeds<WS2812, LEFT_PIN_2, GRB>(leftTwo, NUM_LEDS);
  FastLED.addLeds<WS2812, LEFT_PIN_3, GRB>(leftThree, NUM_LEDS);
  FastLED.addLeds<WS2812, LEFT_PIN_4, GRB>(leftFour, NUM_LEDS);
  FastLED.addLeds<WS2812, RIGHT_PIN_1, GRB>(rightOne, NUM_LEDS);
  FastLED.addLeds<WS2812, RIGHT_PIN_2, GRB>(rightTwo, NUM_LEDS);
  FastLED.addLeds<WS2812, RIGHT_PIN_3, GRB>(rightThree, NUM_LEDS);
  FastLED.addLeds<WS2812, RIGHT_PIN_4, GRB>(rightFour, NUM_LEDS);
  //Serial.begin(9600);
}

void loop(){
  //Check the function potentiometer voltage and map its value from 0 to 100
  functionAnalogValue = analogRead(functionPin);
  functionMapped = map(functionAnalogValue, 0, 1023, 0, 100);
  //Switch statement controls which method will be invoked
  switch(functionMapped){
    case 0 ... 10:{
      normalOperation();
      break;
    }
    case 11 ... 20:{
      glitter();
      break;
    }
    case 21 ... 30:{
      waves();
      break;
    }
    case 31 ... 40:{
      //lines();
      break;
    }
    case 41 ... 50:{
      //rainbowChase();
      break;
    }
    break;
  }
}

//----------------------------------- Normal Operation Functions --------------------------------------------------------------------------|

void brakeNominal(){
  makeItDim();
  FastLED.show();
}
void off(){
  makeItBlack();
  FastLED.show();
}
void brakePressed(){
  makeItRed();
  FastLED.show();
}
void offLeftSignal(){
  //Make the strips black to clear other actions, don't show LEDs yet
  makeItBlack();
  //Make the correct strips orange, then show LEDs
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[2])[j] = CRGB(180,30,0);
      (ledArray[3])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}
void onLeftSignal(){
  makeItDim();
  //Make the correct strips orange, then show LEDs
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[2])[j] = CRGB(180,30,0);
      (ledArray[3])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}
void brakeLeftSignal(){
  makeItRed();
  //Make the correct LEDs orange, show.
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[2])[j] = CRGB(180,30,0);
      (ledArray[3])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}

void offRightSignal(){
  //Make the strips black to clear other actions, don't show LEDs yet
  makeItBlack();
  //Make the correct strips orange, then show LEDs
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[6])[j] = CRGB(180,30,0);
      (ledArray[7])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}
void onRightSignal(){
  makeItDim();
  //Make the correct strips orange, then show LEDs
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[6])[j] = CRGB(180,30,0);
      (ledArray[7])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}
void brakeRightSignal(){
  makeItRed();
  //Make the correct LEDs orange, show.
  for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[6])[j] = CRGB(180,30,0);
      (ledArray[7])[j] = CRGB(180,30,0);
  }
  FastLED.show();
}
void offInReverse(){
  //Make the strips black to clear other actions, don't show LEDs yet
  makeItBlack();
  //Make the correct strips white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  FastLED.show();
}
void onInReverse(){
  makeItDim();
  //Make the correct strips white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  FastLED.show();
}
void brakeInReverse(){
  makeItRed();
  //Make the correct strips white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  FastLED.show();
}
void offHazard(){
  makeItBlack();
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
void onHazard(){
  makeItDim();
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
void brakeHazard(){
  makeItRed();
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
void offHazardReverse(){
  makeItBlack();
  //Make the correct LEDs white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  //Make the correct LEDs orange
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
void onHazardReverse(){
  makeItDim();
  //Make the correct LEDs white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  //Make the correct LEDs orange
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
void brakeHazardReverse(){
  makeItRed();
  //Make the correct LEDs white
  for(int i = (NUM_LEDS/2); i < NUM_LEDS; i++){
      ledArray[0][i] = CRGB(240,240,240);
      ledArray[1][i] = CRGB(240,240,240);
      ledArray[4][i] = CRGB(240,240,240);
      ledArray[5][i] = CRGB(240,240,240);
  }
  //Make the correct LEDs orange
  for(int i = 0; i < NUM_LEDS; i++){
      ledArray[2][i] = CRGB(180,30,0);
      ledArray[3][i] = CRGB(180,30,0);
      ledArray[6][i] = CRGB(180,30,0);
      ledArray[7][i] = CRGB(180,30,0);
  }
  FastLED.show();
}
//------------------------------ Normal Operation Global Functions -----------------------------|
void makeItBlack(){
  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[i])[j] = CRGB(0,0,0);
    }
  }
}
void makeItRed(){
  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[i])[j] = CRGB(235,0,0);
    }
  }
}
void makeItDim(){
  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      (ledArray[i])[j] = CRGB(100,0,0);
    }
  }
}
//----------------------------------------------------------------------------------------------|

void normalOperation(){                        //The Arduino has power since the car is on, but the tail lights are off because the headlight switch on the dash is off. Need to program functions for turn signals and reverse lights while the headlight switch is off.
  boolean brakeIsRunning = digitalRead(brakeRunning);
  boolean brakeIsPressed = digitalRead(brakeSwitch);
  boolean leftSignalOn = digitalRead(turnSignalLeft);
  boolean rightSignalOn = digitalRead(turnSignalRight);
  boolean inReverse = digitalRead(reverseLight);
  
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 1){ //All the lights are off.
    off();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 1){ //The brake pedal is pressed.
    brakePressed();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 1 && inReverse == 1){ //All lights off except left signal.
    offLeftSignal();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 0 && inReverse == 1){ //All lights off except right signal.
    offRightSignal();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 1 && inReverse == 1){ //Brake pressed, left signal.
    brakeLeftSignal();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 0 && inReverse == 1){ //Brake pressed, right signal.
    brakeRightSignal();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 0){ //All lights off, reverse on.
    offInReverse();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 0){ //Brake pressed, reverse on.
    brakeInReverse();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch off, hazard on.
    offHazard();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch off, brake pressed, hazard on.
    brakeHazard();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 0){ //Headlight switch off, hazard on, reverse.
    offHazardReverse();
  }else
  if(brakeIsRunning == 1 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 0){ //Headlight switch off, brake pressed, hazard on, reverse.
    brakeHazardReverse();
  }else
  //------------------------------------------------------------------------
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 1){ //Headlight switch on, brake not pressed.
    brakeNominal();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 1){ //Headlight switch on, brake pressed.
    brakePressed();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 1 && inReverse == 1){ //Headlight switch on, left turn signal on.
    onLeftSignal();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch on, right turn signal on.
    onRightSignal();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 1 && inReverse == 1){ //Headlight switch on, left turn signal + brake.
    brakeLeftSignal();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch on, right turn signal + brake.
    brakeRightSignal();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 0){ //Headlight switch on, reverse lights on.
    onInReverse();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 1 && rightSignalOn == 1 && inReverse == 0){ //Headlight switch on, brake pressed, reverse lights on.
    brakeInReverse();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch on, brake not pressed, hazard lights.
    onHazard();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 1){ //Headlight switch on, brake pressed, hazard lights.
    brakeHazard();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 1 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 0){ //Headlight switch on, hazard on, reverse.
    onHazardReverse();
  }else
  if(brakeIsRunning == 0 && brakeIsPressed == 0 && leftSignalOn == 0 && rightSignalOn == 0 && inReverse == 0){ //Headlight switch on, brake pressed, hazard on, reverse.
    brakeHazardReverse();
  }else{
    brakeNominal();
    //Serial.println("in the else clause");
  }
}

void glitter(){
  
  //---*--*-*------*------*----*------*-*---
  //-*-----*------*----*--*-------*-----**--
  //*------*--*----*---*---*------*-----*---  Random 12x per second
  //-*----*--------*-*--*-----*------*---*--
  //----*------*--*-----*-*---*-----*----*--
  //---*-----*-------*--*-----*--*------*-*-
  //-----*------*----*-*------*--*----*--*--
  //---*-----*-------*-----*---*-*--*---*---
  
  for(int i = 0; i < NUM_STRIPS; i++){ //make it all black
    for(int j = 0; j < NUM_LEDS; j++){ 
      (ledArray[i])[j] = CRGB(0,0,0);
    }
  }
  int randoms[32];
  for(int i = 0; i < 32; i++){ //Generate 32 random locations
    randoms[i] = random(0,NUM_LEDS);
  }
  int indexCount = 0;
  for(int i = 0; i < NUM_STRIPS; i++){ //count through each strip
    for(int j = 0; j < 3; j++){ //count to eight
      (ledArray[i])[randoms[indexCount]] = CRGB(255,255,200); //indexCount keeps its value so that it can count all the way to 64.
      indexCount++;
    }
  }
  FastLED.show();
  delay(70);
}

void waves(){

  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  //```'''"""'''```'''"""'''```'''"""'''```'''
  
  boolean runThis = true;
    int r = 120;
    int g = 0;
    int b = 60;
    double radian = 0;
    double multiplierR = 0;
    double multiplierG = 0;
    double multiplierB = 0;
    float wavelength = 100;
    double t = 4;
    
    do{
      for(int i = 0; i < NUM_STRIPS; i++){
        for(int j = 0; j < NUM_LEDS; j++){ 
          multiplierR = abs(sin((((2*3.14)/wavelength)* j) - ((2*3.14)/4)*t)); 
        //multiplierG = abs(cos((((2*3.14)/wavelength)* j) - ((2*3.14)/4)*(t))); 
          multiplierB = abs(cos((((2*3.14)/wavelength)* j) - ((2*3.14)/4)*t)); 
          (ledArray[i])[j] = CRGB(trunc((r*multiplierR)), trunc((g*multiplierG)), trunc((b*multiplierB)));
            }
        }
    FastLED.show();
        t += 0.01;
        functionAnalogValue = analogRead(functionPin);
        functionMapped = map(functionAnalogValue, 0, 1023, 0, 100);
        if(functionMapped < 21 || functionMapped > 30){
          runThis = false;
        }
        }while(runThis == true);
}




//toDo: Make a button that makes the tail lights sparkle when pressed. 
//makeItDim, then pick random spots to make it sparkle every 100ms
