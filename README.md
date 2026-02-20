Paul Daly - G00470372

Bachelor of Engineering (Honours) in Software and Electronic Engineering - Year 2 Semester 1 - Internet of Things Project

Device to Monitor Conditions for Panic/Anxiety Attacks

Using an ESP32, LCD, LEDs, DFRobot DHT11 Temperature Sensor, DFRobot HeartRate Sensor, LDR Light Sensor and a Sound Sensor (TBD)

------------------------------------------------------------------------------

Update 1: Inital files, working code for testing the peripherals, will be adapted into main device code

Code for LCD added, displaying info from the peripherals

Code for DHT11 added, checking temperature in room and displaying on LCD

Code for Light Sensor added, checking light in room and displaying on LCD

------------------------------------------------------------------------------

Update 2: 'MainCode-LightHeatHeart' Got the main peripherals working with LCD screen, and the LEDs

Heartrate sensor is inconsistent, but I have a video of it working, uploaded to one drive, linked here: https://atlantictu-my.sharepoint.com/personal/g00470372_atu_ie/_layouts/15/stream.aspx?id=%2Fpersonal%2Fg00470372%5Fatu%5Fie%2FDocuments%2FDocuments%2FYear%202%2FIoT%2FVID%5F20251128%5F101951%2Emp4%7E2%2Emp4&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2E3e4412e2%2D0a19%2D4613%2D8806%2D4b8c4ad1644d

------------------------------------------------------------------------------

Update 3: 'MainCode-WebsiteStart' get website functioning and gathering data from sensors

Website code added, working as intended, updates for light, heart and heat values

Light reading currently not working, gives 0 for website and lcd, solve before showcase

Heart reading not working for website, website update loop doesn't work with current heart reading code, doesn't need solving before demonstration

------------------------------------------------------------------------------

Update 4: 'MainCode-Cleanup'

Current Issues: 
Light sensor not working (~suspected bad input pin~, not pin, heat works fine with it) - Not working, but working with other code, wil demo with that

Heartbeat sensor inconsistent (not an issue for demoing) - Ignore for now

Bluetooth connection inconsistent (think it's when the phone is connected to uni wifi) - Working fine
