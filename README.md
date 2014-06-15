#zeller

Implementation of Zeller's congruence to determine the day of the week given the date

##Description

This program uses the formula for [Zeller's congruence](http://en.wikipedia.org/wiki/Zeller's_congruence) to determine the day of the week (Sunday, Monday, ...) based on a date (ex: "July 4, 1776") in either the Gregorian and Julian calendars.

##Installation

```bash
make && sudo make install
```

##Usage

```bash
zeller [-j] "Month Day, Year"
```

Use the `-j` flag to return the day of the week in the Julian calendar. Results are Gregorian by default.
