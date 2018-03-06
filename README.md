# radio-pi

This is in development (just started!) Raspberry pi Internet radio streaming. Using Qt 5 framebuffer shows the radio and with a remote the user can change the radio stations.

Lots to do...

To setup the Debian "standard x86-64" environment for cross-compilation I followed:
https://wiki.qt.io/RaspberryPi2EGLFS

Note the step that I sometimes need to do again (because ~/raspi-qt in my system is a symbolic link to an external file system):

Go to Tools -> Options -> Build&Run -> Compilers
  Add
    GCC
    Compiler path: ~/raspi-qt/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++
