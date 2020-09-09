# MikrotikTrafficMonitoring
Repo ini di buat dengan bantuan Firebase
Requiretment
1. Mikrotik with Internet Access
2. Firebase Account With Realtime Database
3. NodeMCU and any Display or Arduino With Ehernet Shield

# STEP IN MIKROTIK (WinBox)
System > Scheduler > Add (+) > 
Name : Any
Interval 00:00:01 (1 Seconds)
On Event : Open MikrotikScript.txt

# STEP IN ARDUINO / ESP8266
Arduino Library 
1. Arduino Json >> https://github.com/bblanchon/ArduinoJson
2. SSD1306 (if you use Display Oled) >> https://github.com/adafruit/Adafruit_SSD1306
3. Adafruit GFX (if you use Display Oled) >> https://github.com/adafruit/Adafruit-GFX-Library
4. Wire (if you use Display Oled) >> https://github.com/esp8266/Arduino/tree/master/libraries/Wire

Open Code in Arduino IDE and Upload

# PREVIEW
<image src="https://raw.githubusercontent.com/zailbreck/MikrotikTrafficMonitoring/master/firebase_structure.png">
<image src="https://raw.githubusercontent.com/zailbreck/MikrotikTrafficMonitoring/master/Preview1.jpeg">
<image src="https://raw.githubusercontent.com/zailbreck/MikrotikTrafficMonitoring/master/Preview1.jpeg">
