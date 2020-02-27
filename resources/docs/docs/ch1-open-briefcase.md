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
You have no idea what a microcontroler is nor how to program this device, but you'll have to find a way.

## Step 1 - Briefcase wiring

In order to connect to the briefcase, you need to wire your microcontroler to replace the keypad...

TODO

## Step 2 - Briefcase wake signal

The briefcase is programmed to wake whenever the **#** sign is pushed.
You will have to programmatically wake it up that way.

The program Edward gave you is a hacker-tool designed to provide many different utilities for hardware-hacking.

The good thing about it is that the shell is already working, and that you will just have to fill-in the blanks!

## Step 3 - Briefcase bruteforce

Now that you know the wiring works, you will need to perform a bruteforce attack on the pins.

Here are the main things you need to understand about the algorithm you will write:
 * You need to simulate fingers going over a keypad. Fingers go one digit at a time.
 * Between presses, keypads need to get back to the steady state where no key is pressed.
 * After entering 4 digits, you need to push * to validate the password.
 * If the password is wrong, you will carry-on with the next password. If the password is right, you absolutely need to go on to phase 2.

Remember: Once the first PIN is found, you have 30 seconds to enter the right second PIN (through a second round of bruteforce).

If you miss a cycle, PINs will change automatically (generated randomly).

When you will have found the right two pins, the briefcase will be open for 30 seconds. Don't miss this timeframe!
