# Airport Management System

This project was created as part of an academic project during the first year of preparatory degree. The system manages an airport and its planes, including their departure and arrival times. The project uses C language and the GTK3+ Library to create a graphical user interface.

## Features
- Add new planes to the airport
- Record the departure and arrival times of planes
- Display the flight schedule for a specific day
- Search for a specific flight based on the flight number
- Store and retrieve data from text files
- User-friendly GUI created using GTK3+ Library

## Requirements
- C compiler
- GTK3+ Library

## Usage
Clone the repository and navigate to the project directory in your terminal. Compile the code using the following command:

gcc-9 `pkg-config --cflags gtk+-3.0` -o PROJECT PROJECT_INTERFACE.c PROJECT.c `pkg-config --libs gtk+-3.0`

./PROJECT
