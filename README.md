# FSweather
A variation of my TFT_WeatherClient repository
This is a newer (and different) version of my TFT_WeatherClient that resides on this github account.
It is built on a Raspberry Pi 3 B+ using C++ and QT creator instead of Python and TK.
The FS in "FSweather" stands for Full Screen. The Operating system is Buster vertion of Raspian.</br></br>

To auto start the application in X-Windows after the X11 server has started edit:</br></br>

/etc/xdg/lxsession/LXDE-pi/autostart </br></br>
@lxpanel --profile LXDE-pi</br>
@pcmanfm --desktop --profile LXDE-pi</br>
@xscreensaver -no-splash</br>
@xset s off</br>
@xset -dpms</br>
@xset s noblank</br>
@/home/pi/fsweather  <-------- Add this to the end of the file. </br>
(Assuming that fsweather is the application you want to start)</br>
