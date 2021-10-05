# Chapter 2: Surprise Surprise

## Briefing

Congratulations, you managed to open the briefcase.
Inside will be lots of documents, some interesting, some completely useless.
Ohh wait. There's a badge! Quick, hurry-up and try to login onto the safe...  
What? It didn't work?... Hmmm.

Damn! The intel was wrong. The employee whose briefcase was stolen is only a SC 3...

Remember, you need to be Security Clearance level 4 or above in order to get access to the content of the safe.

You'll need to find another way.


## Step 1 - NFC Reader Wiring

The employee badge is a MiFARE Classic 1K card. Your first job is to wire the NFC-Reader (PN-532) to the Arduino and make it able to detect the card.

Just so you know, the Arduino uses a SPI Connection in order to communicate with the reader.

**Hint:** Everything should be written on the card itself, if you can't read it well, look into the Datasheet in your docs ;)


## Step 2 - Find the right info, write it on the NFC-card, open the safe

### About the MEDUSA network

The auth network is available on a wireless connection, with a hidden SSID.

By scanning the available WiFi Networks with **airmon-ng**, we can easily determine which one it is.

Then, using **aircrack-ng** or **wifite** or any cracking software, we managed to crack it!

Great: here are the credentials:

`SSID: MEDUSA`
`Key: E0E9542D44`

After sniffing around, we found ARP requests going to `192.168.1.2`... Could this be our auth server?

A quick portscan indicates ports `80` and `8080` are both listening on that IP... Seems that we're onto something.

Why don't you go check with your browser what's on `http://192.168.1.2`

Don't forget we're looking for someone with SC 4 and above...

**Hint: Now may be the time to take a look on all those files in your briefcase...**

**Hint 2 : You may need to use a tool to convert some data... visit _"/tools"_ page of the website**


### Understanding all data stored on the badge

We have taught you to understand the data stored on the badge.

You understand how memory is organized and how TLV payloads are encoded.
(if you don't remember, we have provided you with the official documentation of MiFARE!)

What could help is to understand how data is encoded on the card.

**Remember:** Only the Employee UUID and Last Login Timestamp are to be changed.

For reference :
 * a UUID is encoded on 16-bytes, 2 characters per byte (should not require any specific encoding)
 * a String encoded in ASCII takes only one byte per character
 * a Timestamp can be encoded on 4 or 8 bytes. Timestamp of 4 bytes for **January 1st 2020 12:00 AM** is **0x5E0BD2F0** in Hex, **1577833200** in decimal (epoch seconds)

In our case, you can consider that the timestamp is written as **little-endian**.

### Becoming SC 4

If you found the right data by hacking on the website, and understood which blocks you should change on sector 3, you only need to manually write the blocks using your microcontroller interface.

The command should be **nfc-write**, don't forget to initialize the NFC Reader by using the **nfc-en** command

Let's crack this safe!
