#ifndef USB2ADB_ADB_H
#define USB2ADB_ADB_H	1

#pragma once

#include <Arduino.h>

static const byte ADB_DEFAULT_ADDRESS_DONGLE = 1;
static const byte ADB_DEFAULT_ADDRESS_KEYBOARD = 2;
static const byte ADB_DEFAULT_ADDRESS_MOUSE = 3;
static const byte ADB_DEFAULT_ADDRESS_TABLETS = 4;
static const byte ADB_DEFAULT_ADDRESS_DATA_DEV = 5;
static const byte ADB_DEFAULT_ADDRESS_RESERVED = 6;
static const byte ADB_DEFAULT_ADDRESS_MISC = 7;

class ADB {
private:
	unsigned short r3;
	unsigned short initR3;

protected:
	ADB(byte handler, byte address, bool srq_enable);

public:
	virtual ~ADB();

	/*virtual void talk() = 0;
	virtual void listen() = 0;
	virtual void flush() = 0;
	virtual void reset() = 0;*/
	
	unsigned short getRegister3() { return this->r3; }
	
	byte getDeviceHandler();
	void setDeviceHandler(byte handler);
	byte getDeviceAddress();
	void setDeviceAddress(byte address);
	bool getSRQEnable();
	void setSRQEnable(bool enable);
	
	virtual void reset();
};

#endif /* USB2ADB_ADB_H */
