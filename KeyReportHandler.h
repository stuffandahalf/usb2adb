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

#ifndef USB2ADB_KEYREPORTHANDLER_H
#define USB2ADB_KEYREPORTHANDLER_H	1

#pragma once

#include <hidboot.h>
#include "ADBStandardKeyboard.h"

class KeyReportHandler : public KeyboardReportParser {
private:
	volatile ADBStandardKeyboard& kb;
	//void PrintKey(uint8_t mod, uint8_t key);

public:
	KeyReportHandler(volatile ADBStandardKeyboard& kb);
	virtual ~KeyReportHandler() { }

protected:

	virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

	virtual void OnKeyDown(uint8_t mod, uint8_t key);
	virtual void OnKeyUp(uint8_t mod, uint8_t key);
	virtual void OnKeyPressed(uint8_t key);
	
	
};

#endif /* USB2ADB_KEYREPORTHANDLER_H */
