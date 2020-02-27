# Chapter 2: Surprise Surprise

## Briefing

Congratulations, you managed to open the briefcase.
Inside will be lots of documents, some interesting, some completely useless.
Ohh wait. There's a badge! Quick, hurry-up and try to login onto the safe...  
What? It didn't work?... Hmmm.

Damn! The intel was wrong. The employee whose briefcase was stolen is only a SC 5...

Remember, you need to be Security Clearance level 6 or above in order to get access to the content of the safe.

You'll need to find another way.


## Step 1 - NFC Reader Wiring

The employee badge is a MiFARE Classic 1K card. Your first job is to wire the NFC-Reader (PN-532) to the Arduino and make it able to detect the card.

Just so you know, the Arduino uses a SPI Connection in order to communicate with the reader.

**Hint:** Everything should be written on the card itself, if you can't read it well, look into the Datasheet in your docs ;)

## Step 2 - Find and decode data stored on the badge

Now, we need to find a way to understand which data is stored on the badge and how it is stored.

For this, you need to quickly understand how memory is organized and how TLV payloads are encoded.

Fortunately, we have provided you with the official documentation of MiFARE!

What could help is to understand which "kind" of data is stored on the card.

For reference :
 * a database ID can be an integer (4, 8, or any number of bytes)
 * a UUID is encoded on 16-bytes
 * a String encoded in ASCII takes only one byte per character
 * a Timestamp can be encoded on 4 or 8 bytes. Timestamp of **January 1st 2020 12:00 AM** is **0x5E0BD2F0** in Hex, **1577833200** in decimal (epoch seconds)

## Step 3 - Tapping into the Auth network

The auth network is available on a wireless connection, with a hidden SSID.

By scanning the available WiFi Networks with **airmon-ng**, we can easily determine which one it is.

TODO


## Step 4 - Becoming SC 6

Now that you have access to the wifi and know the URL of the Auth server, you might want to connect to it and see if you can get more info from there... If you need help, now would probably be a good moment to go through the documents in your Briefcase.

Found what you needed? Then why don't you go ahead and change the content of your Badge's memory?
Yeah, we thought you'd love it as well!

Let's crack this safe!
