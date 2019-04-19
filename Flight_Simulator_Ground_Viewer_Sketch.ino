//USER SETUP
const byte analog_bracket = 3;
const byte analog_pin = A0;  // connect all switches to this of your chosen analog pin
const long groundView_interval = 55; // set this high enough to allow single selections -- low number = faster repeats

//record your switch input values here
const int  eyelevel_fwd     = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code ctrl and bksp -- Upload "D110"
const int  eyelevel_back    = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code ctrl and entr -- Upload "D100"
const int  selection_3D     = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and n   -- Upload "D090"
const int  look_down        = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and b   -- Upload "D080"
const int  look_right       = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and j   -- Upload "D070"
const int  look_up          = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and i   -- Upload "D060"
const int  zoom_in          = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and u   -- Upload "D050"
const int  look_fwd_2D      = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and o   -- Upload "D040"
const int  zoom_out         = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and v   -- Upload "D030"
const int  eyelevel_up      = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and p   -- Upload "D020"
const int  look_left        = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and l   -- Upload "D010"
const int  eyelevel_dn      = 42; // FSX 'keyboard options' and Link2FS 'KEYS' code shift and m   -- Upload "D000"
//end user setup



void setup() {
  /*
  The Arduino analog pins are analog input by default -- all input pins should not be left unconnected (floating). 
  Plug one of the following three pin ranges into the next line of code depending on your Arduino board and the 
  analog pin that you are using. The example below exempts pin A0 which is used as the analog input pin. Arduino NANO
  and PRO MINI analog pins A6 and A7 have no digital functions. Connect pins A6 and A7 to +5V through 39k ohm resistors.
   for Arduino UNO  i=15; i<20; i++
   NANO & PRO MINI  i=15; i<20; i++
   for Arduino MEGA i=55; i<70; i++
  */
  for (byte i=15; i<22; i++) pinMode(i, INPUT_PULLUP); // NANO using analog pin A0 (D14) -- pull pins A1 thru A7 HIGH
  
  Serial.begin(115200);
}// end setup()



void loop() {
  static long slot_analogDisplay, slot_groundView;
  
//DISPLAY CURRENT analogRead() -- place // in front of the following line when single and multiple hits run smoothly
  if (millis() > slot_analogDisplay) {Serial.println(analogRead(analog_pin)); slot_analogDisplay += 600;}

//PROVIDE TIME FOR other programming to run
  if (millis() > slot_groundView) {GROUND_VIEW_GATEKEEPER(); slot_groundView += 10;}
}// end loop()



void GROUND_VIEW_GATEKEEPER() {
  int analog_read1Low, analog_read1High, analog_read2;
  static long slot_viewKeyboard;
  bool check_valid;
    
  analogRead(analog_pin); // stabilize the analog to digital converter --  
  analog_read1Low = analogRead(analog_pin) - analog_bracket;
  
//WAIT FOR SWITCH to be pushed
  if (analog_read1Low < 900) {
    analog_read1High = analog_read1Low + (2 * analog_bracket);
    analog_read2 = analogRead(analog_pin);
    
//PROCEED IF CONTACT is stable and repeat has timed out 
    if ((analog_read1Low < analog_read2) && (analog_read1High > analog_read2) && (millis() > slot_viewKeyboard)) {
      check_valid = GROUND_VIEW_KEYBOARD(analog_read1Low, analog_read1High);
      
//slot_viewKeyboard IS EXTENDED ONLY if input matches preprogrammed value -- string uploaded to Link2FS
      if (check_valid == true) slot_viewKeyboard = millis() + groundView_interval;
      
    }//close input is stable ....
  }// close key pressed
}// close ground_view_gatekeeper()
  


bool GROUND_VIEW_KEYBOARD(int low, int high) {
  bool success = false;
  //Serial.println("Keyboard");
  
//CHECK ANALOG INPUT against user setup values -- upload Link2FS code
  if ((low < eyelevel_dn) && (high > eyelevel_dn)) {
     Serial.println("D000"); success = true; return success; }
  if ((low < look_left) && (high > look_left)) {
     Serial.println("D010"); success = true; return success; }
  if ((low < eyelevel_up) && (high > eyelevel_up)) {
     Serial.println("D020"); success = true; return success; }
  if ((low < zoom_out) && (high > zoom_out)) {
     Serial.println("D030"); success = true; return success; }
  if ((low < look_fwd_2D) && (high > look_fwd_2D)) {
     Serial.println("D040"); success = true; return success; }
  if ((low < zoom_in) && (high > zoom_in)) {
     Serial.println("D050"); success = true; return success; }
  if ((low < look_up) && (high > look_up)) {
     Serial.println("D060"); success = true; return success; }
  if ((low < look_right) && (high > look_right)) {
     Serial.println("D070"); success = true; return success; }
  if ((low < look_down) && (high > look_down)) {
     Serial.println("D080"); success = true; return success; }
  if ((low < selection_3D) && (high > selection_3D)) {
     Serial.println("D090"); success = true; return success; }
  if ((low < eyelevel_fwd) && (high > eyelevel_fwd)) {
     Serial.println("D100"); success = true; return success; }
  if ((low < eyelevel_back) && (high > eyelevel_back)) {
     Serial.println("D110"); success = true; return success; }
    
}// end ground_view_keyboard()

/*
RESISTOR LADDER CIRCUIT CONSTRUCTION

MATERIAL -- apart from the microprocessor, use what you have available. Try to keep the ladder resistors within one or
  two standard resistor sizes of each other. This sketch will not work with 4x3 matrix keypads. 
- one    arduino micrprocessor board -- NANO, UNO, MEGA, or PRO MINI connected to serial adapter module
- one    USB cable
- one    5x7cm double side perforated project board pcb
- three  jumpers 
- two    normally open pushbuttons -- suggest 6x6x7.3mm   tactile switch -- } square actuator without cap gives better 
- ten    normally open pushbuttons -- suggest 12x12x7.3mm tactile switch   -- } feel and contact than long tapered actuators
- one    10k  ohm small wattage resistor through hole or surface mount SM0805
- one    100k ohm small wattage resistor through hole or surface mount SM0805
- two    39k ohm small wattage through hole resistor. Analog pins A6 and A7 external pull up resistors.
- twelve 4.7k ohm small wattage resistor through hole or surface mount SM0805

CONSTRUCTION -- suggest assemble the circuit on solderless breadboard first, using axial (through hole) resistors
    and connect ONE jumper between the Arduino analog pin and touch a resistor ladder node at a time, then connect the switches
> ANALOG RESISTOR LADDER 
    NOTE I used 4.7k ohm resistors. Any standard size low wattage resistor between 1000 ohms and 10,000 ohms works well.
  - connect one end of first 4.7k ohm resistor to Arduino GND bus
  - make a chain by connecting the next 4.7k resistor to the first and then repeat for the remaining 4.7k ohm resistors.
    NOTE: each connection between two resistors and a switch is a NODE.
  - pullup resistor --connect one end of 100k ohm resistor to Arduino analog pin A0 and the other end to Arduino 5V bus.
    increase the size of the pullup resistor when using ladder resistors greater than 4.7k ohms
> PUSHBUTTONS
  - connect one terminal of the switch to a separate NODE of the resistor ladder circuit. 
  - connect the other terminal of all switches to analog pin A0.


> PROGRAMMING -- generally a good idea to close the Arduino Serial Monitor if not used for long periods of time. Flooding
    the input buffer will lock up the Arduino IDE program if not the computer and all programming changes are lost
  - load the sketch onto the Arduino board and enable the Arduino Serial Monitor with baud rate of 115200
  - with no buttons pushed - monitor should display a scrolling value of 1023 - if not check the circuit construction for
    loose connections
> IDENTIFY each switch with one of the switch input variables in 'USER SETUP' above
  - touch each node - ONE AT A TIME - with the jumper and record your observed values in 'USER SETUP'
  - re load the sketch onto the Arduino board
  - push each switch (or move jumper to another node) in turn and the serial monitor should display text output for the switch
    eg. push 'pan_left'switch outputs D010 to the monitor
  - revisit 'USER SETUP' if necessary to fine tune the output
  - place 'comment out' marks as directed by 'DISPLAY CURRENT analogRead()' of void loop() to stop scrolling analog value output.
  - again download the sketch onto the Arduion board
  - save the sketch to your project folder with 'PROGRAMMED' added to sketch name
  - close the Arduino serial monitor
  - run Flight Simulator, run Link2FS 'KEYS' program keys as per video.
// end instructions
*/

