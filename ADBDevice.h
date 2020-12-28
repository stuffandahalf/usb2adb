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

#ifndef USB2ADB_ADBDEVICE_H
#define USB2ADB_ADBDEVICE_H	1

#pragma once

static const uint8_t ADB_DEFAULT_ADDRESS_DONGLE = 1;
static const uint8_t ADB_DEFAULT_ADDRESS_KEYBOARD = 2;
static const uint8_t ADB_DEFAULT_ADDRESS_MOUSE = 3;
static const uint8_t ADB_DEFAULT_ADDRESS_TABLETS = 4;
static const uint8_t ADB_DEFAULT_ADDRESS_DATA_DEV = 5;
static const uint8_t ADB_DEFAULT_ADDRESS_RESERVED = 6;
static const uint8_t ADB_DEFAULT_ADDRESS_MISC = 7;

enum adb_device_class {
	ADB_DEVICE_CLASS_DONGLE,
	ADB_DEVICE_CLASS_KEYBOARD,
	ADB_DEVICE_CLASS_MOUSE,
	ADB_DEVICE_CLASS_TABLET,
	ADB_DEVICE_CLASS_DATA_DEV,
	ADB_DEVICE_CLASS_RESERVED,
	ADB_DEVICE_CLASS_OTHER
};

class ADBDevice {
public:
	/*class Register {
	private:
		uint8_t size;
		uint8_t *data;
		
	public:
		Register(uint8_t n);
		Register(uint8_t n, unsigned long long int defaultValue);
		
		Register(Register& other);
		~Register();
		
		template <typename T>
		void setValue(T value)
		{
			int vi;
			if (sizeof(T) >= this->size) {
				//start value index at cutoff
			} else if (sizeof(T) < this->size) {
				// fill empty spaces with zeros
			}
		}
		
		template <typename T>
		T getValue() const
		{
			T value = 0;
			//for (int i = 0; i < this->size && i < sizeof(T); i++) {
			for (int i = 0; i < this->size; i++) {
				if (i) {
					value <<= 8;
				}
				value |= this->data[i];
			}
		}
		
		template <typename T>
		operator T() const
		{
			return this->getValue<T>();
		}
		
		template <typename T>
		operator =(T rhs)
		{
			this->setValue<T>(rhs);
		}
		
		template <typename T>
		operator &(T rhs) const
		{
			return this->getValue<T>() & rhs;
		}
		
		template <typename T>
		operator |(T rhs) const
		{
			return this->getValue<T>() | rhs;
		}
		
		template <typename T>
		operator &=(T rhs)
		{
			*this = *this & rhs;
		}
		
		template <typename T>
		operator |=(T rhs)
		{
			*this = *this | rhs;
		}
		
		template <typename T>
		operator >>(T rhs)
		{
			return this->getValue<T>() >> rhs;
		}
		
		template <typename T>
		operator <<(T rhs)
		{
			return this->getValue<T>() << rhs;
		}
	};*/
	
	class Register {
	private:
		size_t size;
		uint8_t *bytes;
		
		Register(size_t n, uint8_t *bytes);
		virtual ~Register();
		
	public:
		template <typename T>
		static Register&& construct(T value)
		{
			return Register(sizeof(T), (uint8_t *)&value);
		}
		
		size_t getSize();
		uint8_t *getBytes();
	};
	
private:
	adb_device_class deviceClass;
	uint16_t r3;
	uint16_t initR3;

protected:
	ADBDevice(uint8_t handler, uint8_t address, bool srq_enable);

public:
	virtual ~ADBDevice();

	/*virtual void talk() = 0;
	virtual void listen() = 0;
	virtual void flush() = 0;
	virtual void reset() = 0;*/
	
	virtual bool getRegister(unsigned int index, Register& out);
	
	uint8_t getDeviceHandler();
	void setDeviceHandler(uint8_t handler);
	uint8_t getDeviceAddress();
	void setDeviceAddress(uint8_t address);
	bool getSRQEnable();
	void setSRQEnable(bool enable);
	
	virtual void reset();
};

#endif /* USB2ADB_ADBDEVICE_H */
