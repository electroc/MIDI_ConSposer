#include <MIDI.h>
#include <Keypad.h>


MIDI_CREATE_DEFAULT_INSTANCE();
using namespace midi;

static const unsigned ledPin = 13;                                  // LED pin on Arduino Uno
static const int CHANNEL_MIDI_DEVICE = MIDI_CHANNEL_OMNI; //        omni !!!!

//static const int CHANNEL_MIDI_DEVICE = 4; 
static const byte kp3midiport=16;

unsigned int knob1val=0;
unsigned int knob2val=0;
unsigned int knob3val=0;
unsigned int knob4val=0;
unsigned int knob5val=0;
unsigned int knob6val=0;

unsigned int counter1=0;


static const byte knob1=A0;
static const byte knob2=A1;
static const byte knob3=A2;
static const byte knob4=A3;
static const byte knob5=A4;
static const byte knob6=A5;

static const byte light_senseD=4;

static const byte button_D2=2;
static const byte button_D3=3;
static const byte button_D4=4;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 11, 12, 13}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {

  MIDI.sendNoteOn(pitch, velocity, channel);
 }

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 

  MIDI.sendNoteOff(pitch, velocity, channel);
}

void handlerControlChange(byte channel, byte number, byte value) {
  // ZOOM BOARD -> KP3+
  if(channel==1) {
    if(number==73&&value==127) MIDI.sendNoteOn(36, 127, kp3midiport);
    if(number==73&&value==0)   MIDI.sendNoteOn(36, 127, kp3midiport);
    if(number==75&&value==127) MIDI.sendNoteOn(37, 127, kp3midiport);
    if(number==75&&value==0)   MIDI.sendNoteOn(37, 127, kp3midiport);
    if(number==76&&value==127) MIDI.sendNoteOn(38, 127, kp3midiport);
    if(number==76&&value==0)   MIDI.sendNoteOn(38, 127, kp3midiport);
    if(number==77&&value==127) MIDI.sendNoteOn(39, 127, kp3midiport);
    if(number==77&&value==0)   MIDI.sendNoteOn(39, 127, kp3midiport);
    else   MIDI.sendControlChange(number, value, channel);
    MIDI.sendNoteOff(36, 0, kp3midiport);
    MIDI.sendNoteOff(37, 0, kp3midiport);
    MIDI.sendNoteOff(38, 0, kp3midiport);
    MIDI.sendNoteOff(39, 0, kp3midiport);
  }
  
}

void readPoti(byte knob, unsigned int knob_value){
  
  knob_value=analogRead(knob);
  return knob_value;
  }

void mapPoti(unsigned int knob_value){

  knob_value=map(knob_value, 0, 1023,0, 126);
  return knob_value;
  
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(button_D2, INPUT);
    pinMode(button_D3, INPUT);
    pinMode(button_D4, INPUT);

    MIDI.begin(CHANNEL_MIDI_DEVICE);                      // Launch MIDI and listen to channel 4
    MIDI.setHandleNoteOn(MyHandleNoteOn);
    MIDI.setThruFilterMode(0);
    // declare our MIDI-handlers.
    MIDI.setHandleControlChange(handlerControlChange);
    //  MIDI.setHandleProgramChange(handlerProgramChange);
    MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 

 /*   
    Serial.begin(9600);
    delay(2000);
   Serial.println("MIDI Translator v0.1");
   //delay(2000);
   readPotis();
   //delay(2000);
   Serial.print("pitch_poti : ");
   Serial.println(pitch_poti);
   
   Serial.print("vel_poti : ");
   Serial.println(vel_poti);
   */
   delay(1000);
   
}

void loop()
{
  MIDI.read();

  

}

