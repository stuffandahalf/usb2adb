#ifndef ADB2USB_ADB_H
#define ADB2USB_ADB_H	1

#pragma once

#include <Arduino.h>

static const byte ADB_DEVICE_ADDRESS_DONGLE = 1
static const byte ADB_DEVICE_ADDRESS_KEYBOARD = 2;
static const byte ADB_DEVICE_ADDRESS_MOUSE = 3;
static const byte ADB_DEVICE_ADDRESS_TABLETS = 4;
static const byte ADB_DEVICE_ADDRESS_DATA_DEV = 5;
static const byte ADB_DEVICE_ADDRESS_RESERVED = 6;
static const byte ADB_DEVICE_ADDRESS_MISC = 7;

class ADB {
private:
	

public:
	virtual void talk();
	virtual void listen();
	virtual void flush();
	virtual void reset();
	
};

#endif /* ADB2USB_ADB_H */
