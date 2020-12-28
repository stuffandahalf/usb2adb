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

// Handles all ADB communications and device handling

#include <Arduino.h>
#include "ADB.h"
#include "ADBDevice.h"

namespace {

const uint16_t RESET_LENGTH = 3000;
const uint16_t ATN_LENGTH = 800;
const uint16_t SYNC_LENGTH = 70;
const uint16_t SRQ_LENGTH = 300;

inline bool in_duration(unsigned long time, uint16_t threshold)
{
	return (threshold * 0.97) <= time && time <= (threshold * 1.03);
}

const uint8_t ADB_COMMAND_FLUSH = 0b00;
const uint8_t ADB_COMMAND_LISTEN = 0b10;
const uint8_t ADB_COMMAND_TALK = 0b11;

bool ready = false;
uint8_t ADB_IN_PIN;
uint8_t ADB_OUT_PIN;
volatile static ADBDevice **devices;
volatile uint8_t request = 0;

}

void adb_init(uint8_t adb_in_pin, uint8_t adb_out_pin, volatile ADBDevice **devs)
{
	ADB_IN_PIN = adb_in_pin;
	ADB_OUT_PIN = adb_out_pin;
	
	devices = devs;
	
	pinMode(ADB_IN_PIN, INPUT);
	pinMode(ADB_OUT_PIN, INPUT); // Leave pin state untouched until writing
	if (Serial) {
		Serial.println("Waiting for ADB");
	}
	while (!digitalRead(ADB_IN_PIN));
	if (Serial) {
		Serial.println("Ready");
	}
	ready = true;
	attachInterrupt(digitalPinToInterrupt(ADB_IN_PIN), adb_handler, LOW);
}

ADBDevice *adb_get_device(uint8_t address) {
	for (ADBDevice **dev = devices; *dev != NULL; dev++) {
		if ((*dev)->getDeviceAddress() == address) {
			return *dev;
		}
	}
	return NULL;
}

void adb_handler()
{
	unsigned long t0, t1, dt;
	
	t0 = micros();
	while (!digitalRead(ADB_IN_PIN));
	t1 = micros();
	dt = t1 - t0;
	
	if (in_duration(dt, ATN_LENGTH)) {
		// attention, proceed
	} else if (in_duration(dt, RESET_LENGTH)) {
		//kb.reset();
		// reset devices
		return;
	} else {
		// invalid signal
		return;
	}
	
	//t0 = micros();
	while (digitalRead(ADB_IN_PIN));
	/*t1 = micros();
	dt = t1 - t0;
	
	if (70 <= dt && dt <= 75) {
		// sync, proceed
	} else {
		
	}*/
	
	//byte request = 0;
	for (int i = 0; i < 8; i++) {
		t0 = micros();
		while (!digitalRead(ADB_IN_PIN));
		t1 = micros();
		dt = t1 - t0;
		if (50 <= dt && dt <= 72) {
			// 0 bit
			request |= (0 << i);
		} else if (dt < 50) {
			// 1 bit
			request |= (1 << i);
		} else {
			return;
		}
		while (digitalRead(ADB_IN_PIN));
	}
	
	// 0 stop bit
	while (!digitalRead(ADB_IN_PIN));
	while (digitalRead(ADB_IN_PIN));
	
	if (!(request & 0xF)) {
		// general reset
	} else {
		uint8_t address = request >> 4;
		uint8_t reg = request & 0x03;
		ADBDevice *dev;
		//if (address != kb.getDeviceAddress()) {
		if ((dev = adb_get_device(address)) == NULL) {
			return;
		}
		switch ((request >> 2) & 0x03) {
		case ADB_COMMAND_FLUSH:
			break;
		case ADB_COMMAND_LISTEN:
			break;
		case ADB_COMMAND_TALK:
			break;
		}
	}
}
