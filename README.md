# Curtain
Our team is building a system that automatically drives a curtain using an outside LDR (based on light intensity, it sends a command to either open or close the curtains) and Bluetooth connection (sends USER command to set LDR precedence (TRUE "ON" or FALSE "OFF") either to open or close curtains directly to serial port. ) 

There are 2 inputs to the motor. There will be 4 separate c files.  

One c file will be used to OPEN and CLOSE. The file should be such that it doesn't depend on type of input, just that it does the job of driving the curtain. This file will be named "motor.c" 

The other c file will be connected to the LDR transducer. Based on light intensity for a certain period of time, it'll call the motor.c file to either OPEN or CLOSE the curtain. Only on the condition that the USER sets LDR precedence to TRUE. It's assumed to be TRUE always, until prompted by the third c file. This c file will be titled "ldr.c" 

The third c file will be used to process the bluetooth commands from the bluetooth module. Here, a USER can set ldr precedence to ON or OFF for a certain period of time. {2 hrs, 4hrs, 8hrs, indefinitely}. Once LDR precedence is OFF, the user can send commands to the terminal to either OPEN or CLOSE the curtains. 

 

The fourth c file will be the app.c file. This should action the main.c file such that all we need to do is add App_Init(); and App_MainLoop() into our main.c file. 
