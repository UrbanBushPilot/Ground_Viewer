Hi. Welcome to the World’s Ugliest general av. 4 seat trainer table top Flight Simulator (WUFS).

**********
Preamble    ******************
**********
There will be a companion YouTube.com video. Search for the author** UrbanBushPilot. In the commentary I will treat this as a first project. It is a builders project eventually requiring a small amount of fabrication including soldering. Please be safe. Solder in an envirment where fumes are extracted to the outside, and by somebody whose brain is long past adolesence. 

When either practicing circuits, or joining downwind at the destination airport, you want to be able to see the runway at a times. This project will allow you to track a point on the ground in the main or ‘new view’ window. This device is not as techy as Tracker IR. Top hat and even keyboard controlled viewers are smoother than this device, but it can be operated  in predetermined steps, by touch, out of the corner of your eye. The runway will alway be where you expect to see it. Maybe not over your shoulder, but in its own monitor or window on the main monitor.

************
Downloads    ******************
************
Ground Viewer uses the Arduino microprocessor, as well as Jim’s Link2FS Keys program. You will need three free downloads. This zip package available from github.org***, the Keys interface available from jimspage.co.nz, and an Arduino IDE program for Windows from Arduino.cc . 

Ground Viewer.zip: download the file and expand to a folder that you can associate with Flight Simulator. It will definitely not appear as an add-on to Flight Simulator. The folder will contain this readme.txt file, drawing of a 5x7cm 12 pushbutton panel, keyboard setup, credits page, and the Ground_ Viewer Sketch folder.

Arduino IDE: download the latest ‘stable’ version of the IDE for your operating system, and install it on the Windows ‘C:\’ main folder. It is a large download 300 – 400 MB. You may use it once to program the ground viewer Arduino board and wipe the folder to free storage space or spend days building your entire flight simulator control system using other Link2FS programs. Make a shortcut for the .exe**** program and place it on Windows desktop or taskbar. 

link2fs_keys_v4.zip: down load and expand to a folder on the ‘C:\’ folder. Make a shortcut for the .exe**** program and place on Windows desktop or taskbar. Set up the twelve links to the keyboard commands as listed in the attached ‘Ground Viewer Key Assignments.doc’ . Look at Jim’s files included with the ‘Keys’ program for additional sketches.

CH340 Windows USB driver –  required for most common Arduino clones. Download the driver for your operating system and install. 


**************
Not Free Stuff    ******************
**************
You, of course, need a  computer, Windows 7 or 10 operating system, and a copy of Flight Simulator 2000 on. This has been tested on FSX using Windows 7 and Flight Simulator 2002 using Windows 10.1  When the ground viewer is up and running on a temporary or permanent surface, it is ready to go before the main computer displays the loading operating system flash screen drawing less power than a bright LED. 

Flight Simulator – you will need to program 12 keyboard keys for the twelve view commands as listed in the attached ‘Ground Viewer Key Assignments.doc’ .


*********
Material    ******************
*********
> One Arduino microprocessor board. Nano - recommended (cheap!), or  UNO, or MEGA. The UNO and MEGA boards are larger, thus easier to handle and have better voltage control and overload protection than the NANO. You can purchase parts for the entire NANO project off shore for the price of a MEGA clone.
> One USB cable to fit the Arduino microprocessor board.
> One mounting board – suggest 5x7cm double side perforated PCB board – maybe a solderless breadboard to test the circuit before assembly.
> Ten SPST momentary pushbuttons – suggest 12x12x7.4mm tactile switches. These are the ones with small square push-on stem made to hold snap on buttons. Omit the snap on buttons and avoid the tactile switches with long conicle actuators. This switch has better feel and is more likely to work when pushed from any direction. If you have enough pushbuttons now of any description, use them. I assume that you are just beginning to work with Flight Simulator and want to keep costs down until you are committed to the hobby.
> Two additional pushbuttons – suggest 6x6x7.4mm tactile switches. Baby brothers to the main pushbuttons. Use for zoom switches. The change in size helps define a central column with two side columns.
> A strip of twenty 4.7k ohm resistors – any resistor between 1k and 10k ohms can be used. Try to keep  them within one standard resistor size of each other. Only 13 resistors are required but I like to double the size of the last resistor attached to the positive bus. Use 10k or two 4.7k resistors end to end.
> Two 39k ohm small wattage axial (through hole) resistors. Pro Mini & Nano A6 & A7 pin pull up.
> One 100k ohm resistor – a smaller size resistor can be used if the ladder resistors are less than 4.7k ohms and double the size if the ladder resistors are larger than 4.7k.
> Wire to connect the switch panel components.
> Three jumpers to connect the switch panel to the Arduino board. 

*************
Circuit Theory ******************
*************
The analog pin on the Arduino board can translate input voltage to a number between 0 and 1023 in a manner similar to a digital voltmeter. We compare the number output by the sensor to a table of observed outputs and when matched, the Arduino board uploads a command to ‘Keys’ changing the monitors view. The resistor ladder is like a potentiometer with only a few selected areas exposed to the pot’s wiper. Any pushbutton switch closes a circuit between the analog sensor and one node between
two resistors with an identifyable voltage. Only one switch is closed at a time. Then, voltage -> output value -> table -> instruction for Flight Simulator. A 100k pullup resistor is required when all switches are open to draw transient voltages away from the Arduino analog pin. The analog converter is sensitive enough that any induced emf or static force around the circiut wires or within the microprocessor itself will produce an output value. If this floating output matches something on the table, instructions to Flight Simulator are issued causing chaos.

***********
The Sketch    ******************
***********
Short, only uses one input pin, enough processing power left over that this may be added to another sketch running the instrument switch panel or avionics.
> User Setup 
   - analog pin A0 is specified although the user can select any analog pin connected to the circuit. Change the pin specified by ‘analog_pin’ to the pin now connected to the resistor ladder
   - the user can select the interval between instructions to Flight Simulator – lowering ‘groundView_interval’ will make the repeated actions run more frequently. It may produce more movement than intended. When the pushbutton is held down long enough, the repeated instructions may stack up and the view will continue to change after the pushbutton is released.
- the user can set the sensitivity of the analog input. A well built circuit with some ground plane protection may produce a single value when a switch is closed. Temporary circuits usually produce a range of outputs. A default value for analog_bracket is set at 3. Using more than, less than logic ( < > ) a stored analog value may match the sensor output. It will also match one or two units above and below. Increase the value of ‘analog_bracket’ to 4 if you must. When a larger bracket is required, look for one or more worn out pushbuttons.
- switch input values – remove the comment out marks before the first line of code in loop(). Close each switch in turn and observe the value scrolling on the serial monitor,  record this number to the right of the ‘=’ sign for the switch pressed.

> void setup() - normally only runs once - nothing much to do except set internal pullup resistors for the unused Arduino analog pins. This removes some more of the influence of stray emf within the Arduino microprocessor. Finally ‘Serial.begin(115200);’ activates the USB serial bus enabling communication between the running sketch and the main computer. The sketch baud rate is 115200. This must be set on the ‘Arduino Serial Monitor’ window near the bottom right hand corner. 
NOTE: disable the serial monitor when it is not required. Eventually the data collected will overfill the display buffer and lockup the Arduino IDE – and maybe the computer. You lose all unsaved changes and must restart Arduino IDE if not the computer. Nothing is damaged, but it is a real pain.

> void loop() - there are only two lines of code. The first line enables the serial monitor to read and display the analog output to the voltage currently applied to the designated analog pin. Replace the comment out marks when you do not need to adjust the values in ‘user setup’ and reload sketch onto the Arduino board.  - The second line enables the switch panel read and process functions. You may comment out this line if you return to user setup to make adjustments to the values of the designated switch value table. Load the changed sketch onto the Arduino board, make changes to the observed analog outputs, then remove the marks, and once again reload the Arduiono board. The code uploaded to ‘Keys’ displays 10 times faster than the current analog output value. A single fast scrolling number can be difficult to read. You want to see a range of values to determine what value is the most likely to bracket the tabled output value. 

> GROUND_VIEW_GATEKEEPER() - aka gatekeeper()
> GROUND_VIEW_KEYBOARD()    - aka keyboard()
The two functions working together screen out switch bounce and poor switch response. Push a button and release one command is sent up to Link2FS Keys. Hold a button down and that instruction will repeat every 60ms. 

This sketch is released in the spirit of open source programming. Use,  distribute, and improve this as you wish for your personal use. Use at your own risk.

Thank you, Jim
UrbanBushPilot
April 2019
