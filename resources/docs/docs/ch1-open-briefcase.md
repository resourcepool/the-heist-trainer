# Chapter 1: Opening the briefcase

## Briefing

You got your hands on the stolen briefcase (Thank you, whoever you are SC 6 employee!).
Problem is, the briefcase is locked up, and it's a keypad briefcase!

Here's how it works:
 * You need to enter a 4-digits code, and validate by pushing **star**.
 * After the right code is entered, you have **30 seconds** to enter the **second code**, and validate by **star**.

Fortunately, the briefcases have two design flaws:
 * Hardware flaw: The keypad connectors are external
 * Software flaw: There is no **wait-before-retry** logic implemented on the briefcase system.

## Main Goal

You need to find a way to open this briefcase, and Edward also gave you a hacking program written for ESP-32 microcontrolers.
You have no idea what a microcontroller is nor how to program this device, but you'll have to find a way.

## Step 1.1 - Briefcase wiring

In order to connect to the briefcase, you need to wire your microcontroller to replace the keypad...

Fortunately, edward also found you some docs. Hopefully those docs can help you.




## Step 1.2 - Flashing your Arduino Device

The program we gave you (in the `/hacker` directory of your repository) is an Arduino project.
Once you have setup Arduino, you should be able to flash the device.

By default, every Arduino Device contains a program. In order to flash it, you need to reset it into Bootloader mode each time you want to flash.

To do this, follow the following steps:
 * Push and hold the EN button (it means "ENABLE").
 * Push and hold the BOOT button (it means "BOOTLOADER").
 * Release the EN button. When you release the EN button, the device will reboot.
 * After 1 second, release the BOOTLOADER button

The program Edward gave you is a hacker-tool designed to provide many different utilities for hardware-hacking.

The good thing about it is that the shell is already working, and that you will just have to fill-in the blanks!

The program can be accessed using a Serial Monitor.

To open your Serial Monitor


## Step 1.3 - Coding

You need to implement the method `BruteForceService::simulateButtonPressed`.  
You can test it by launching the command

## Step 2 - Briefcase bruteforce

Now that you know the wiring works, you will need to perform a bruteforce attack on the pins.

Here are the main things you need to understand about the algorithm you will write:
 * You need to simulate fingers going over a keypad. Fingers go one digit at a time.
 * Between presses, keypads need to get back to the steady state where no key is pressed.
 * After entering 4 digits, you need to push * to validate the password.
 * If the password is wrong, you will carry-on with the next password. If the password is right, you should stop entering digits.

Remember: Once the PIN is found, you should stop entering digits.

If you miss a cycle, PINs will change automatically (generated randomly).

When you will have found the right pin, the briefcase will be open for 30 seconds. Don't miss this timeframe!
