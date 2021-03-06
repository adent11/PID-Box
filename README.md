# PID-Box Project <!--Temporary Title-->
The goal of the PID box project is to control the speed of a motor using a photinterrupter and PID.
# Project Timeline

|Week|Date| Planned Milestones|Actual Progress|
|----| -- | ----------------- |--------|
|1|10/28/19|Design mount for the motor, and the wheel|Designed mount for the motor, the wheel, and a simple t-slot wall|
|2|11/6/19|Design one wall assembly of motor, wheel, and <br/>photointerrupter|Made assembly with the motor, photointerrupter, LCD, some indicator LEDs, and the potentiometer|
|3|11/11/19|Finish designing the box, add in LCD, LED indicators,<br/> switches, battery pack, and potentiometer|Added switches, battery pack, and arduino; 3d printed motor mount|
|4|11/18/19|Add arduino, start assembling box|Started assembling, made fritzing diagram|
|5|12/2/19|Wire everything and get test code working|Mounted all but motor, due to its tendancy to attach crooked, started wiring|
|6|12/9/19|RPM code|Soldered wires to all of the components, wired all components, assembled box|
|7|1/6/20|PID code|Tested all components, started rpm code, |
|8|1/13/20|Non-PID code|Finished rpm code, started non-PID control code|
|9|1/22/20 |Wrap up loose ends|Finished non-PID control code, wrote PID code, started tuning PID variables|
|10|1/27/20|Delay compensation|Continued tuning PID constants, worked on problem with rpm accuracy|
|11|2/3/20|Delay compensation|Recut wheel, retuned PID constants|
|12|2/10/20|Delay compensation|Finalized code, finished readme|

# The Process
<details><summary><b>Pre-project Planning</b></summary>
<p>
I didn't do a lot of sketching or drawing out plans, so most of my project planning was done in either Solidworks or Arduino, starting with smaller assemblies or simple test codes to gain the understanding of how the project works. I did however spend a while before actually starting the project trying to understand how PID control works.
</p>
</details>

<details><summary><b>Week 1</b></summary>
<p>
  
* Designed mount for motor
* On the motor mount I had some trouble getting the screws to be in a place where I can screw all of them in, so I extended the part that attaches to the box
* Designed wheel 
<br/>
<IMG SRC="Media/MotorMount1.PNG" width="273" height="200"> <IMG SRC="Media/InterruptWheel1.PNG" width="252" height="200"><IMG SRC="Media/MotorAssem1.PNG" width="231" height="200"><br/>
</p>
</details>
  

<details><summary><b>Week 2</b></summary>
<p>
  
* Made sub-assembly of the motor, wheel, and photointerrupter

<br/>
<IMG SRC="Media/PhotointerrupterMotorSubassem11-6.PNG" width="273" height="200">

* Added a row of LEDs that will show the speed

<IMG SRC="Media/PIDBoxAssem11-8.PNG" width="335" height="200"><br/> 
</p>
</details>
  

<details><summary><b>Week 3</b></summary>
<p>
  
* Added in the rest of the components
* 3d printed the motor mount
* Made drawing of all PID box walls
<IMG SRC="Media/PIDGif.gif" width="400" height="400">
<br/> 
</p>
</details>
  
<details><summary><b>Week 4</b></summary>
<p>
  
* Laser cut all walls
* Drilled to fix some holes that were the wrong size
* Recut a wall to have my name, labels for the switches, and some holes that should have been there
* Started making fritzing diagram
</p>
</details>
  

<details><summary><b>Week 5</b></summary>
<p>
  
* Got potentiometer and motor control working with test code
* Broke the wheel trying to put it on
* Made the hole in the wheel slightly wider and recut
* Having trouble attaching the motor and wheel straight
</p>
</details>
  
<details><summary><b>Week 6</b></summary>
<p>

* Soldered wires to all components
* Finished assembling box
* One problem that I faced this week was that all of my wiring had to fit into a relatively small space, so it was tedious and took a long time to wire <br/>
<IMG SRC="Media/PIDBoxWiring.JPG" width="267" height="200"> <br/>
</p>
</details>

<details><summary><b>Week 7</b></summary>
<p>
  
* Tested all components
* I forgot to add a resistor to ground on the mode switch, so I had to solder that on
* Wrote rpm code

``` c++
int calcRPM()
{
  int rpm;
  rpm = interruptCount * (60000 / rpmCalcDelay) / 12; //Calculates rpm, interrupts times calculations per second divided by 
  return rpm;                                         //the number of interrupts per rotation
}
```
</p>
</details>

<details><summary><b>Week 8</b></summary>
<p>
  
* Finished and tested rpm code
* Started non-PID motor control code
</p>
</details>

<details><summary><b>Week 9</b></summary>
<p>
  
* Finished non-PID motor control code
* Finished PID control code
* Started tuning PID variables
</p>
</details>

<details><summary><b>Week 10</b></summary>
<p>
  
* Continued tuning PID constants
* Came across problem with RPM accuracy due to only having one hole cut in my wheel
</p>
</details>

<details><summary><b>Week 11</b></summary>
<p>
  
* Redesigned the wheel to have six holes instead of one for greater accuracy
* Retuned PID constants </br>
<IMG SRC="Media/InterruptWheel2.PNG" width="215" height="200"> </br>
</p>
</details>

<details><summary><b>Week 12</b></summary>
<p>
  
* Finalized code
* Wrap up loose ends such as git
* Made this lovely readme
* Commented code
* Took videos, pictures, and screenshots
</p>
</details>
 
# The Finished Product

### Materials List
* LCD Screen
* LCD Backpack
* Photinterrupter
* 2 Switches
* 10k Potentiometer
* 6 AA Battery Pack
* DC Motor
* 8 220Ω Resistors
* 6 Red LEDs
* 1 Green LED
* Arduino Uno
* Prototyping Shield <br/>
* Box
* Wheel
* Motor Mount

### Wiring
The wiring for the PID Box was fairly straightforward, however having so many LEDs complicated my wiring slightly. I saved some space by soldering the ground legs of all of the LEDs together, and I used a breadboard in order to avoid having to solder resistors on to each LED. The first time I put it together, I forgot to ground the mode switch, so I had to reopen it and solder on the resistor. The only other complex wiring was that of the motor, but I already had that from the motor assignment, so all I had to do was copy it.
<IMG SRC="Media/PIDFritzing.PNG" width="600" height="450">

### The Box
<IMG SRC="Media/VideoPreview.PNG" width="350" height="350">
<sup><a href="https://www.youtube.com/watch?v=RjP5sMNfZZY&feature=youtu.be" target="_blank">The PID Box in action</a></sup>

