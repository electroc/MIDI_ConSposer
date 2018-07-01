#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();
using namespace midi;
static const unsigned ledPin = 13;      // LED pin on Arduino Uno
//static const int CHANNEL_MIDI_DEVICE = MIDI_CHANNEL_OMNI; //        omni !!!!
static const int CHANNEL_MIDI_DEVICE = 4; 

unsigned int pitch_poti=0;
unsigned int vel_poti=0;

unsigned int counter1=0;
static const byte global_velo=126;

static const byte pitch_poti_pin=A0;
static const byte vel_poti_pin=A1;

bool minusoktave;
bool minusnote;

static const byte oktave=6;

static const byte noterange=11;

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {

  readPotis();
  velocity=global_velo;

  if(minusnote)pitch=pitch-vel_poti;
  else pitch=pitch+vel_poti;
  
  if(minusoktave)pitch=pitch-(pitch_poti*oktave);
  else pitch=pitch+(pitch_poti*oktave);


  MIDI.sendNoteOn(pitch, velocity, channel);
 }

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 

  if(minusnote)pitch=pitch-vel_poti;
  else pitch=pitch+vel_poti;
  
  if(minusoktave)pitch=pitch-(pitch_poti*oktave);
  else pitch=pitch+(pitch_poti*oktave);
  MIDI.sendNoteOff(pitch, velocity, channel);
}

void readPotis(){
  vel_poti=analogRead(vel_poti_pin);
  
  pitch_poti=analogRead(pitch_poti_pin);

  if(pitch_poti<512)
  {
    minusoktave=true;
    pitch_poti=map(pitch_poti,0,512,3,0);

  }
  else {
    minusoktave=false;
    pitch_poti=map(pitch_poti,512,1023,0,3);
  }

  if(vel_poti<512)
  {
    minusnote=true;
    vel_poti=map(vel_poti,0,512,noterange,0);

  }
  else {
    minusnote=false;
    vel_poti=map(vel_poti,512,1023,0,noterange);
  }
  
}


void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(pitch_poti_pin, INPUT);
    pinMode(vel_poti_pin, INPUT);
    MIDI.begin(CHANNEL_MIDI_DEVICE);                      // Launch MIDI and listen to channel 4
    MIDI.setHandleNoteOn(MyHandleNoteOn);
    MIDI.setThruFilterMode(0);
    // declare our MIDI-handlers.
    // MIDI.setHandleControlChange(handlerControlChange);
    //  MIDI.setHandleProgramChange(handlerProgramChange);
    MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
    readPotis();
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

    
  /*
  
    if (MIDI.read())                    // If we have received a message
    {
        digitalWrite(ledPin, HIGH);
        MIDI.sendNoteOn(42, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
        Serial.println("got midi");
        
        delay(1000);		            // Wait for a second
        MIDI.sendNoteOff(42, 0, 1);     // Stop the note
        digitalWrite(ledPin, LOW);
        
    }
    */
}

