Paul Daly - G00470372

Bachelor of Engineering (Honours) in Software and Electronic Engineering - Year 2 Semester 1 - Internet of Things Project

Device to Monitor Conditions for Panic/Anxiety Attacks

Using an ESP32, LCD, LEDs, DFRobot DHT11 Temperature Sensor, DFRobot HeartRate Sensor, LDR Light Sensor and an INMP411 Sound Sensor.

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

------------------------------------------------------------------------------
Update 5: Multiple git branchs

Working through each sensor, testing and getting data, while working through issues with sensors that did not function as intended.
New sound sensor (INMP 441) working perfectly for its use, Light Sensor working as needed, working on Heart Rate Sensor now.
Also working on website.
------------------------------------------------------------------------------
Update 6: Getting Main code up to date

The main code file has been updated with the new sound sensor code, as well as new code for the light sensor. However, I have encountered an issue uploading it to ESP32 ('Core dump flash config is corrupted'). I will look into this for the next commit. I also need to work on the heart sensor, the website, and integrating Fetch API & ThingSpeak into the project.

------------------------------------------------------------------------------
Update 7: Continuing work with Main Code file

The 'corruption' issue has been narrowed down to the code added for the sound sensor, will test further in the next update. Code snippets were added, these are tests for the individual sensors, and are flexible enough to factor into main code later on if needed. Starting website, Fetch and ThingSpeak soon.
