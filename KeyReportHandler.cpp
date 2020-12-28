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

// Handles the signals sent from the USB keyboard and updates an
// ADBStandardKeyboard's registers

#include <Arduino.h>
#include "KeyReportHandler.h"

KeyReportHandler::KeyReportHandler(volatile ADBStandardKeyboard& kb)
: KeyboardReportParser(), kb(kb)
{
	
}

void
KeyReportHandler::OnControlKeysChanged(uint8_t before, uint8_t after)
{
	MODIFIERKEYS beforeMod, afterMod;
	beforeMod = *(MODIFIERKEYS *)&before;
	afterMod = *(MODIFIERKEYS *)&after;
	
	
}

void
KeyReportHandler::OnKeyDown(uint8_t mod, uint8_t key)
{
	char c = OemToAscii(mod, key);
	Serial.println(c);
	this->kb.setKeyState(c, ADB_STD_KB_KEY_DOWN);
}

void
KeyReportHandler::OnKeyUp(uint8_t mod, uint8_t key)
{
	
}

void
KeyReportHandler::OnKeyPressed(uint8_t key)
{
	
}
