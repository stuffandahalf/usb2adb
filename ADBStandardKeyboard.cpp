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

// Specialized ADB device functionality for Apple standard keyboards

#include <Arduino.h>
#include "ADBStandardKeyboard.h"

ADBStandardKeyboard::ADBStandardKeyboard()
: ADBDevice(2, ADB_DEFAULT_ADDRESS_KEYBOARD, false), r0(0), r2(0)
{
	
}

ADBStandardKeyboard::~ADBStandardKeyboard() { }

void ADBStandardKeyboard::setKeyState(char c, bool state)
{
	byte newValue = (state << 7) | (c & 0x7F);
	if (!(this->r0 >> 8)) {
		this->r0 = newValue << 8;
	} else if (!(this->r0 & 0xFF)) {
		this->r0 |= newValue;
	}
}

void ADBStandardKeyboard::reset()
{
	ADBDevice::reset();
	
	this->r0 = 0;
	this->r2 = 0;
}

bool ADBStandardKeyboard::getRegister(unsigned int index,
	ADBDevice::Register& out)
{
	if (ADBDevice::getRegister(index, out)) {
		return true;
	}
	switch (index) {
	case 0:
		out = Register::construct<uint16_t>(this->r0);
		return true;
	case 2:
		out = Register::construct<uint16_t>(this->r2);
		return true;
	}
	
	return false;
}
