# radio-pi

This is a personal project to play radio stations designed to be working in a Raspberry pi (event without X11 with framebuffer) but also works on a GNU/Linux (Debian, Ubuntu, etc.).

We've been using it for months almost daily. The UI/UX could be improved but it works as it is now.

## Dependencies
* Qt 5
* mplayer
* Suggested: alsamixer

## Compile and use on a Desktop GNU/Linux
radio-pi needs Qt 5. Make sure that `qmake --version` returns Qt 5, e.g.:
```
QMake version 3.0
Using Qt version 5.7.1 in /usr/lib/x86_64-linux-gnu
```

For example in a Debian stretch it was needed to install qt5-default:
```
apt-get install qt5-default
```

To download and compile:
```
git clone https://github.com/cpina/radio-pi.git
cd radio-pi
qmake
make
```

## Use the application
In the same directory as the radio-pi there should be a directory named `configuration`. The cloned repository has a default configuration directory.

Executing `radio-pi` should appear a screen like:
![Screenshot](docs/screenshot.png)

The repository has a `configuration` directory with three files:
```
commands.json
keys.json
stations.json
```

### stations.json
[See example!](http://raw.githubusercontent.com/cpina/radio-pi/master/configuration/stations.json)

Defines the radio station number, the name to be displayed and the URL that will be used with `mplayer` to play this radio station.

Note that a "radio station" can execute a command (see the radio station 99). The command should exist in `commands.json` and is executed when the user presses this station.

### keys.json
[See example!](http://raw.githubusercontent.com/cpina/radio-pi/master/configuration/keys.json)

Defines the possible keys to react for the default actions:
 * change_station_up
 * change_station_down
 * volume_up
 * volume_down

Accepts an array that can contain strings following the [Qt::Key!](http://doc.qt.io/qt-5/qt.html#Key-enum) enum or integers (needed for when Qt doesn't have an Enum representation, for example for the remote control).

If the name of the keys is unknown execute `radio-pi`, select the window, press the key. In the output it would display:
```
==== key pressed: Qt::Key(Key_F7)
==== key pressed: Qt::Key(Key_Home)
==== key pressed: Qt::Key(Key_End)
```

Or a number - this are the names or numbers that can be used.

### commands.json
[See example!](https://raw.githubusercontent.com/cpina/radio-pi/master/configuration/commands.json)

To try to keep the software as general as possible the user can define which commands are used for a series of actions. This can be tested in the console, for example in:
```
{
	"volume_status": "amixer -M get Master",
	"power_off": "/home/carles/bin/write.sh",
	"set_volume": "amixer -M set Master %d%",
	"mute": "amixer -M set Master mute",
	"unmute": "amixer -M set Master unmute"
}
```

`set_volume` replaces %d by a number between 0 to 100. 


# Default configuration:
Arrow up/down to change stations up/down.
Arrow left/right to change the volume. Also the volume up/down in a remote control.

## Crosscompile in a Desktop GNU/Linux to be used in a RaspberrPi
To setup the Debian "standard x86-64" environment for cross-compilation I followed:
https://wiki.qt.io/RaspberryPi2EGLFS

Note the step that I sometimes need to do again (because ~/raspi-qt in my system is a symbolic link to an external file system):

Go to Tools -> Options -> Build&Run -> Compilers
  Add
    GCC
    Compiler path: ~/raspi-qt/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++


# Hardware for RaspberryPi

For the physical box:
* Cardboard box
* Tissues

# TODO
