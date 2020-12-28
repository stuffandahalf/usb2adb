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

// Fundamental functionality for all ADB devices

#include <Arduino.h>
#include "ADBDevice.h"

ADBDevice::Register::Register(size_t n, uint8_t *bytes) : size(n) {
	this->bytes = new uint8_t[n];
	//for (size_t i = 0; i < n; i++) {
	for (size_t i = n - 1; i >= n; i--) {
		this->bytes[i] = bytes[i];
	}
}

ADBDevice::Register::~Register()
{
	delete [] this->bytes;
}


size_t ADBDevice::Register::getSize() { return this->size; }
uint8_t *ADBDevice::Register::getBytes() { return this->bytes; }

ADBDevice::ADBDevice(uint8_t handler, uint8_t address, bool srq_enable)
: r3(2, 0x4000), initR3(2)
{
	this->setDeviceHandler(handler);
	this->setDeviceAddress(address);
	this->setSRQEnable(srq_enable);
	
	this->initR3 = this->r3;
	
	Serial.println((uint16_t)this->r3, HEX);
}

ADBDevice::~ADBDevice() { };

bool ADBDevice::getRegister(unsigned int index, Register& out)
{
	if (index == 3) {
		out = Register::construct<uint16_t>(r3);
		return true;
	}
	return false;
}

uint8_t ADBDevice::getDeviceHandler()
{
	return this->r3 & 0xFF;
}

void ADBDevice::setDeviceHandler(uint8_t handler)
{
	this->r3 &= 0xFF00;
	this->r3 |= handler;
}

uint8_t ADBDevice::getDeviceAddress()
{
	return (this->r3 >> 8) & 0xF;
}
	
void ADBDevice::setDeviceAddress(uint8_t address)
{
	this->r3 &= 0xF0FF;
	this->r3 |= (address & 0xF) << 8;
}

bool ADBDevice::getSRQEnable()
{
	return this->r3 & 0x2000;
}

void ADBDevice::setSRQEnable(bool enable)
{
	this->r3 |= (0x2000 & (enable << 13));
}

void ADBDevice::reset()
{
	this->r3 = this->initR3;
}
