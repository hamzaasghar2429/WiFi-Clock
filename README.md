# WiFi-Clock
Building a clock with an ESP8266 is a fantastic step up from standard Arduino projects because you can leverage its built-in WiFi to create an NTP (Network Time Protocol) Clock. Instead of relying purely on the internal hardware timer (which can drift over time), the microcontroller can ping an internet server to get the exact atomic time.

Here is how the hardware and logic map out for a system like the one on your breadboard:

The Core Components
The Brain (Microcontroller): Your ESP8266 NodeMCU. It handles the timekeeping math, manages the WiFi connection, and pushes data to the screen.

The Display (Output): The 0.96" I2C OLED screen. It uses two communication pins (SDA and SCL) to receive pixel data from the ESP8266.

The Inputs (User Interface): The three push buttons you have wired up. In a typical clock design, these act as:

Button 1: Mode/Select (Switch between normal operation and setting the time).

Button 2: Increment Hours.

Button 3: Increment Minutes.

The Time Source: * Primary: An external NTP server (like pool.ntp.org) accessed via WiFi.

Secondary: The ESP8266's internal millis() function to keep the time ticking between internet syncs.

How the Logic Works
A smart clock generally operates using a State Machine with two primary modes:

Normal Mode (Running): The ESP8266's main loop checks the internal timer. Once exactly 1000 milliseconds have passed, it increments the "Seconds" variable by 1. If seconds hit 60, it rolls over to 0 and increments the "Minutes" variable, and so on. Every few hours, it quietly connects to WiFi, fetches the current exact time for Pakistan Standard Time (PKT), and overwrites its internal variables to correct any drift.

Setup Mode (Manual Override): If you press the "Mode" button, the automatic ticking pauses. The microcontroller now actively polls the Hour and Minute buttons. If it detects a button press (a digital pin going LOW), it increments the respective variable. When you press "Mode" again, it exits setup and resumes normal ticking from your newly set time.
