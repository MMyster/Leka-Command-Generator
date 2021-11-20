# Leka-Command-Generator

## Table of Contents
1. [About](#about)
2. [Dependencies](#dependencies)
3. [Installation](#installation)
4. [Tutorial](#tutorial)
5. [Demo](#demo)

## About
***
This tool allows to generate commands that will be sent to Leka robot. 

## Dependencies
***
A list of librairies and/or frameworks used within the project:
* [CLIPP](https://github.com/muellan/clipp): Version 1.2.3 (April 2019)
* [LKAlphaComSpecs](https://github.com/leka/LKAlphaComSpecs#use): Version 3.0.0 (October 2018)
* [CMake](https://cmake.org/): Version 3.16.3

## Installation
***
A little intro about the installation. (Environment : Linux)
```
$ git clone https://github.com/MMyster/Leka-Command-Generator.git
$ cd ../path/to/the/Leka-Command-Generator/build/
$ cmake ..
$ make
$ ./lkctrl /* Whatever you want */
```

Or

```
$ git clone https://github.com/MMyster/Leka-Command-Generator.git
$ cd ../path/to/the/Leka-Command-Generator/
$ chmod +x install.sh
$ ./install.sh 
/* Password*/
$ lkctrl /* Whatever you want */
```
## Tutorial
***
The manual of the tool

```
SYNOPSIS
        lkctrl -h 
        lkctrl led --list 
        lkctrl led (-e|-b) -A [-H] -V <Red value> <Green value> <Blue value> 
        lkctrl led (-e|-b) -A -r 
        lkctrl led (-e|-b) -A -g 
        lkctrl led (-e|-b) -A -b 
        lkctrl led (-e|-b) [-R <first target> <last target>] [-H] -V <Red value>
               <Green value> <Blue value> 

        lkctrl led (-e|-b) [-R <first target> <last target>] -r 
        lkctrl led (-e|-b) [-R <first target> <last target>] -g 
        lkctrl led (-e|-b) [-R <first target> <last target>] -b 
        lkctrl led (-e|-b) <targets>... [-H] -V <Red value> <Green value> <Blue
               value> 

        lkctrl led (-e|-b) <targets>... -r 
        lkctrl led (-e|-b) <targets>... -g 
        lkctrl led (-e|-b) <targets>... -b 
        lkctrl motor [-H] -A <Direction> <Speed> 
        lkctrl motor [-H] -D <Left Spin> <Left Speed> <Right Spin> <Right Speed>


        lkctrl motor [-H] -l <Left Spin> <Left Speed> 
        lkctrl motor [-H] -r <Right Spin> <Right Speed> 

OPTIONS
        -h, --help, man        Manual

        Led setup
            led                Control led(s)
            --list             List of all led(s) id

            Robot parts which implement leds
                -e, --ears     Control ears part of robot
                -b, --belt     Control belt part of robot

            Targets commands
                -A, --all      Aim all targets
                -R, --range <first target> <last target>
                               Aim a range of targets [hex]

                <targets>...   Aim a set of target [hex]

            RGB data controls
                -H, --values-hex, --hex
                               [hex]

                -V, --values <Red value> <Green value> <Blue value>
                               Provide RGB values

                -r, red        set max Red value
                -g, green      set max Green value
                -b, blue       set max Blue value

        Motor setup
            motor              Control motor features
            -H, --hex          [hex]
            -A, --all <Direction> <Speed>
                               Give same instructions towards both wheels

            -D, --duo <Left Spin> <Left Speed> <Right Spin> <Right Speed>
                               Give instructions for each wheel

            -l, --left <Left Spin> <Left Speed>
                               Give instructions towards left wheel

            -r, --right <Right Spin> <Right Speed>
                               Give instructions towards right wheel

```
## Demo
***
Turn on belt LED[12] in colour : RGB(100, 150, 200)

```
$ lkctrl led --belt 12 -V 100 150 200

 [ 2a 2b 2c 2d 5 16 12 64 96 c8 77 ] 

Packet size : 11 bytes

Packet sent !!!

OK !!!


```
