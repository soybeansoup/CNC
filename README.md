# CNC

## [What's a CNC?](https://en.wikipedia.org/wiki/Numerical_control)
A programatically driven machine. Think 3d printer, laser/plasma table, waterjet, etc.


## Why?
Dashiell (my little brother) bought a big chainsaw to make useable lumber. Lumber needs to dry after being milled and warps making it not so usable; CNC would allow for it to be useable. This type of machine would potentially allow for taking 3d models to physical objects and other fun projects.


## How
### Initial Design
Started out with a rough design using 2020 extrusion. Axis marked out with the Red (Y?) having linear rails fixed in the picture below. Rough dimensions were 2mx1m
![63442347760--29EE02EC-C3EB-4004-9B00-DC4908044A85](https://user-images.githubusercontent.com/50643385/227980599-7f0d5ff4-db86-4aa6-80db-e7d8006aa0f1.jpg)


Quickly realized this was not going to be beefy enough and started scouring the junkyard for larger extrusions. Found an amalgamation of 8080ish material that must have come from a similar industrial machine.


Here's one of the first hauls ft my failed attempt at an oyster farm and my unparalleled cable managment.
![63582219213--157F8B75-3539-4957-8B26-BB3E0BA7BD5A](https://user-images.githubusercontent.com/50643385/227981605-d2782199-31d2-4b6f-8803-232596ce91c6.jpg)


Ended up making ~10 trips to the junkyard over the course of ~6 months and ultimately changed designs based on what I found.


### Troubles with Hardware
Had a lot of trouble with drop shipped linear rails from Amazon. The bearing action was hit or miss with the balls being non-standard (for the local bike shop I was attempting to source new, higher quality ones from). I did a repack and clean of some of the OEM bearings but this was an awful experience and added little performance to the carriage action.
![IMG-5286](https://user-images.githubusercontent.com/50643385/227982506-617c45e0-6a58-42f1-ad5b-77978411dc92.jpg)

### Troubles with Hardware cont.
All of the motors and drivers also came from Amazon as well as Ebay. In retrospect ordering a different driver/motor combo for every axis was a dumb idea.
![IMG-5306](https://user-images.githubusercontent.com/50643385/227983918-43170bb4-bc15-4130-9873-749bec97aa78.jpg)
![IMG-5307](https://user-images.githubusercontent.com/50643385/227983943-9bd04012-bc4a-4e5f-ac21-c46d483e9f7f.jpg)
![IMG-5308](https://user-images.githubusercontent.com/50643385/227983515-2cd75ec1-37b7-4f64-b126-18dcf8fc1e3b.jpg)

So much inconsistency in wiring diagrams. I would often recieve wiring schematics where the wire coloring reflected in the drawing wouldn't match the wire color in real life... Managed to get everything working though.
![IMG_6112](https://user-images.githubusercontent.com/50643385/227983701-9345b5e2-fbe4-4486-b13f-387093690854.JPG)


For the "Brain Box" first issue was getting everything in a fireproof enclosure so if any of my shoddy solders failed I wouldn't burn down the house.
Again, I visited the junkyard and found some old 4G fire alarm boxes.
![63496155977--8775EF50-DBE2-44EC-8852-3463AD6980B5](https://user-images.githubusercontent.com/50643385/227984852-3679ab4d-2380-44a7-ad04-942325ac3bb4.jpg)
Pictured was an attempt to fit all the goods in a single box. Ultimately I ended up stacking and joining two together.


See my atrocious attempt at soldering these 4 and 6 pin aviation connectors with plumbing solder. After a couple visits to the local electronics shop I got some solid guidance as well as proper solder
![IMG-5309](https://user-images.githubusercontent.com/50643385/227985389-3a55f04c-8357-4998-aa12-6a4de1b578d7.jpg)


And the screw connect driver pins/plugs.
![IMG-5294](https://user-images.githubusercontent.com/50643385/227985412-4b0bd5f0-84b2-49b4-99bf-39191fe8cf64.jpg)


### Learning Firsthand about Integration Hell
I got a single motor working just in time. My cheap drill press motor blew and with a new one a few weeks out I was able to continue some mechanical odds and ends using one of the steppers to drive the drill.

![IMG-5314](https://user-images.githubusercontent.com/50643385/227986755-2eb49918-585e-436b-9cbe-136c35329edb.jpg)
This was a good trial run because it forced me to lean hard into integration hell.
Had to go past Proof-of-concept with wiring and software; wrote some code for the arduino to take input from a rotary encoder to control the drill press speed and finished the pinout for the arduino driver and power supply. This was before I was using a stepper library so everything was written by manually defining high/low voltage pulses as well as timeout to the motor.


### No Need to Engineer if you Overbuild

Started putting those beefy junkyard extrusions to use. Almost all the aluminum and structural pieces were from the junkyard.
The X axis was really what ended up benefiting from the beefier aluminum. Getting everything squared on the Y is to this day a running pain.

![IMG-5410](https://user-images.githubusercontent.com/50643385/227987536-73f12fe6-6fc0-441a-a6e6-9670bddf65a8.jpg)

I'd estimate about ~$3-500 in scrap aluminum which would run a couple grand if bought new. All of the fasteners were from McMaster. Probably spent almost the same amount of money on aluminum from the junkyard as fasteners from McMaster.


### Sacrificing Speed for ~Precision and Cost

I ended up using ball screws on all axis' for the project.
Rack and pinion as I would find out after running the machine for a few projects would prove much more efficient time-wise (on the Y at least) but the screws were a fraction of the cost.
I ended up sacrificing some bed space by putting the lead screws on the inside of gantry legs but this felt the most secure for driving the Y axis.

![65342775510__4B7E8129-6C1A-49C5-B8FB-1A208EEDDE23](https://user-images.githubusercontent.com/50643385/227992295-a98fbd9b-d3af-4925-8d9b-d682090efeb7.jpg)
I bought the biggest lead screws that I could find on Amazon, both in diameter and length. This was early on and guided many later decisions like bed length.
I estimated a maximum Y travel speed from end to end of roughly ~30 seconds before deflection would become unmanageable. I used the calculations found here: https://www.roton.com/screw-university/screw-actions/application-engineering-speed/

You can also see the Z fixture in this image. I bought this machined off Amazon because I really didn't want to mess with the finer details required here. Was honestly happy with how it came and wouldn't have really been able to do it myself for any cheaper. I believe I have roughly 4 inches of travel.

Here it is in more detail:
![IMG_6147](https://user-images.githubusercontent.com/50643385/227992937-e1ced3d1-6196-4967-8d69-4260b96d1e13.jpg)

And with the spindle attached:
![66264747848__B50D6D52-90E5-40A7-A599-AC50427A9084](https://user-images.githubusercontent.com/50643385/227993166-668ff811-1356-43a8-a8af-9463c45238b5.jpg)


### More on the Brains

I spent quite a lot of time dialing the brain box and electronics down to a place where I could reliably control all three axis (four motors) independently in software. I quickly abandoned manual pulse control of the motors in exchange for an [objective stepper motor library](https://www.airspayce.com/mikem/arduino/AccelStepper/). What really pushed me over the edge here was the thought of doing all of PID control from scratch.

At first I used a GRBL breakout board with a 32 pin serial connector(?) I think these are typically used for older printers maybe?

![65342786611__86053814-8AFA-4D30-8476-E0D3582160E3](https://user-images.githubusercontent.com/50643385/227993807-2d98e3c3-d688-4126-9797-48d51ca65022.jpg)
I had trouble with the pinout with this breakout board until I realized, like an idiot, I had soldered the board upside down...


I ordered a new one and got everything working as expected but ran into more issues.
At first I thought it was inherent with the board and got a new type specifically made with direct pinouts for CNC controllers:

![IMG_6108](https://user-images.githubusercontent.com/50643385/227994519-429d14d9-1b10-4a2d-afa6-d0a83f0c203c.jpg)
I really liked how clean and straightforward this new board was compared to the other one but ultimately I had more problems. This time with the limit switch IO.

It turned out the Arduino I was using, which was a gift from my dad when I was a teenager, was limited in available GPIO pins that I needed to be able to distinguish between operations in the software I was writing.

As soon as I bought a modern Arduino I got all of the limit switches and motors working in conjunction as expected.


![66095516174__3B629D54-9C52-4174-B54B-8B67642163AC](https://user-images.githubusercontent.com/50643385/227995182-cc97d286-32c8-41a1-8626-004e7c2b942c.jpg)

### How do I Turn This Thing on (and off)?

Another piece to this was manual/override control. Up to this point any movement on an axis would require writing a simple program to jog the axis, uploading the code to the arduino, and then running said code.
This was a giant PITA and so I bought a nice machined, 100 stop rotary encoder to allow for manual override of all the axis. This forced me to learn about throw switches so I could use a single encoder to switch between wiring for the three sets of motors.
![IMG_6223](https://user-images.githubusercontent.com/50643385/227995820-ddd34c52-63cd-4fde-aedb-32f7a19b8da2.jpg)

Along with the manual drive, I added some kill switches for an E-stop as well as a hard power switch for the three power supplies.
This is more or less what all that looks like in the box:
![66434338274__CB630EFE-C9C2-4017-B85F-2D006F02F928](https://user-images.githubusercontent.com/50643385/227996089-11f35b90-fe3d-4c9c-ac48-bcc03fc3ae2a.jpg)

### The Spindle

Next thing to hook up was the spindle. I went with the 120v option so I could plug everything in to the standard wall outlet without running an extension cord through the house to my washer/dryer. Less power than I'd like but ultimately more convenient.

![66264746820__9C9297A5-46EB-4209-9AD5-9F4CEB83F568](https://user-images.githubusercontent.com/50643385/228015062-a7ce4850-a6d0-4b2f-901d-a103288fb1c0.jpg)

You can see the VFD on the bed. The water lines run along the cable tracks with the spindle power and circulate with a fish tank pump out of a 5 gallon bucket underneath the bed. For now I have the spindle controlled separate from the main logic board. While the breakout board on the Arduino as well as the spindle VFD have pinouts for software control (speed, start/stop) I still have yet to make this happen. It's easy enough to manually turn the spindle on and off during operation.

One feature I would like to add is speed control based on variable output from the X axis encoder lines. Because the spindle is open loop to allow for a variable speed, based on whether there is current contact with material for example, I would need to use the encoding from the closed loop motors.

### My House is Dirty

It became pretty quickly apparent that dust was going to be an issue. The spindle came with a foot for dust mitigation and we had an old dust collector lying around so we set this up and shot the material out the window.
![66282195139__6DFF9FEF-988B-4574-9D29-25CB07D76DC7](https://user-images.githubusercontent.com/50643385/228016371-3f978044-46ed-48ad-9819-f8309572c335.jpg)

Here is everything hooked up and running on the first ~production piece. The brain box and dust collector operate on the same 20A circuit while the spindle is on another. When I figured out theoretical draw I was coming close to constantly flipping a single 20A breaker so had to make this compromise.
![66710159417__5E34B85A-6E47-4AD9-A999-A5947238E222](https://user-images.githubusercontent.com/50643385/228017112-10cd3641-eae7-44ba-b928-ffb116263cb6.jpg)

### Finally Getting to Operate

This was some black oak we milled about a year prior. It ended up becoming my current sit/stand desk setup
![IMG_6399](https://user-images.githubusercontent.com/50643385/228016540-9959b4d1-a23d-485b-bc86-a4b526335b22.jpg)


Here's the desk completed:
![IMG_6323](https://user-images.githubusercontent.com/50643385/228016939-daa942a6-883d-4a83-8b53-207cfde06d07.jpg)


And another piece of the same wood. This ended up becoming a workbench for the future shop space.
![67373206017__CD9B812A-441C-4A70-B56F-BCDE66F51CA1](https://user-images.githubusercontent.com/50643385/228017038-41d2955d-64a4-4dab-9382-168440048178.jpg)


I added a fan to the front of the brain box because I was worried about the drivers, and potentially the logic board, overheating. More likely is my shoddy code and wiring but...
![IMG_6287](https://user-images.githubusercontent.com/50643385/228017286-3bd0429a-d9c4-4640-83e3-8d55a5073ab7.jpg)


### Wish List

This is a constantly evolving project. Below is a nonexhaustive, running wish list of what I would like to add/adjust for the future.

1) High power spindle/variable control in software
2) Spindle control in software
3) Rack and Pinion Y axis
4) Constant jog vs encoder jogging
5) LinuxCNC
6) Probe/homing
