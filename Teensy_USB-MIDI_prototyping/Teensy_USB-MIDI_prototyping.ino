/* Buttons to USB MIDI Example

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.

  ---

  Modified by Dominic Barrett for the MIDI Prototyping workshop

  ---

  The Teensy LC has the pin numbers printed on the board,
  but you can also check the "pinout" diagram here:
  https://www.pjrc.com/teensy/teensylc_front_pinout.png


  For simplicity's sake, we're going to make only 4 buttons
  on pins 1,4,8, and 11 (just to give us some space)
  Feel free to choose different pin inputs as needed
*/

#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 1;

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button1 = Bounce(1, 5);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(4, 5);  // which is appropriate for good
Bounce button3 = Bounce(8, 5);  // quality mechanical pushbuttons
Bounce button4 = Bounce(11, 5);
// if a button is too "sensitive"
// to rapid touch, you can
// increase this time.

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(1, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
}

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (button1.fallingEdge()) {
    //messages are sent as usbMIDI.sendNoteOn(note number, velocity, channel number);
    //"channel" is a variable that is set as a constant at the top of the program
    usbMIDI.sendNoteOn(60, 99, channel);  // 60 = C4
  }
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(62, 99, channel);  // 62 = D4
  }
  if (button3.fallingEdge()) {
    usbMIDI.sendNoteOn(63, 99, channel);  // 63 = D#4
  }
  if (button4.fallingEdge()) {
    usbMIDI.sendNoteOn(64, 99, channel);  // 64 = E4
  }

  // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (button1.risingEdge()) {
    //sendNoteOff() works similarly to sendNoteOn()
    //Velocity is being set to 0
    usbMIDI.sendNoteOff(60, 0, channel);  // 60 = C4
  }
  if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(62, 0, channel);  // 62 = D4
  }
  if (button3.risingEdge()) {
    usbMIDI.sendNoteOff(63, 0, channel);  // 63 = D#4
  }
  if (button4.risingEdge()) {
    usbMIDI.sendNoteOff(64, 0, channel);  // 64 = E4
  }
  
  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

