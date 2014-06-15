/*
 * Implementation of Zeller's congruence to determine the day of the
 * week given the date
 *
 * Copyright (C) 2014, Kevin Selwyn <kevinselwyn at gmail dot com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#define VERSION "1.0.1"

void error(char *msg, ...) {
	va_list args;
	va_start(args, msg);
	char *data = va_arg(args, char*);

	if (data) {
		printf(msg, data);
	} else {
		printf(msg);
	}

	exit(1);
}

void usage() {
	error("zeller (v%s)\n\nUsage: zeller [-j] \"Month Day, Year\"\n", VERSION);
}

int month2int(char *month) {
	int i;
	char *months[12] = {
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December",
		"January",
		"February"
	};

	month[0] = toupper(month[0]);

	for (i = 0; i < 12; i++) {
		if (strcmp(months[i], month) == 0) {
			return i + 3;
		}
	}

	error("%s is not a valid month\n", month);
}

char *int2week(int day) {
	char *days[7] = {
		"Saturday",
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday"
	};

	return days[day];
}

int zeller(int day, int month, int year, int julian) {
	int century, output;

	century = (int)floor(year / 100);
	year %= 100;

	output = (day + (int)floor((13 * (month + 1)) / 5) +
			  year + (int)floor(year / 4) +
			  (!julian ? (int)floor(century / 4) : 5 ) -
			  (!julian ? (2 * century) : century)) % 7;

	return output;
}

int main(int argc, char *argv[]) {
	char *date, *pattern, month[10];
	int day, year, julian = 0;

	if (argc < 2) {
		usage();
	}

	if (strcmp(argv[1], "-j") == 0) {
		if (argc == 3) {
			date = argv[2];
			julian = 1;
		} else {
			usage();
		}
	} else {
		date = argv[1];
	}

	pattern = strstr(date, ",") ? "%s %d, %d" : "%s %d %d";

	sscanf(date, pattern, month, &day, &year);

	printf("%s\n", int2week(zeller(day, month2int(month), year, julian)));

	return 0;
}
