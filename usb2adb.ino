// SPDX-License-Identifier: GPL-3.0-only
//
// Copyright (C) 2020 Gregory Norton <gregory.norton@me.com>
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
// 
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.

// Uses a USB Host shield to convert a USB input device to work with Apple
// Desktop Bus computers

#include <hidboot.h>
#include "ADB.h"
#include "ADBStandardKeyboard.h"
#include "KeyReportHandler.h"

const uint8_t ADB_IN_PIN = 3;
const uint8_t ADB_OUT_PIN = 4;

USB usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hidKeyboard(&usb);

volatile ADBStandardKeyboard kb;
KeyReportHandler kb_status(kb);
volatile ADBDevice *devices[] = { &kb, NULL };

void setup()
{	
	Serial.begin(115200);
	while (!Serial);
	
	if (usb.Init() == -1) {
		Serial.println("Failed to initialize USB interface");
		while(1);
	}
	
	delay(200);
	
	hidKeyboard.SetReportParser(0, &kb_status);
	
	adb_init(ADB_IN_PIN, ADB_OUT_PIN, devices);
}

void loop()
{
	/*if (request) {
		Serial.println(request, HEX);
		request = 0;
	}*/
	/*if (!digitalRead(ADB_IN_PIN)) {
		adb_handler();
	}*/
	usb.Task();
}
