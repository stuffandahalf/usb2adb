#include <Arduino.h>
#include "ADB.h"

ADB::ADB(byte handler, byte address, bool srq_enable) : r3(0x4000)
{
	this->setDeviceHandler(handler);
	this->setDeviceAddress(address);
	this->setSRQEnable(srq_enable);
	
	this->initR3 = this->r3;
	
	Serial.println(HEX, this->r3);
}

ADB::~ADB() { };
	
byte ADB::getDeviceHandler()
{
	return this->r3 & 0xFF;
}

void ADB::setDeviceHandler(byte handler)
{
	this->r3 &= 0xFF00;
	this->r3 |= handler;
}

byte ADB::getDeviceAddress()
{
	return (this->r3 >> 8) & 0xF;
}
	
void ADB::setDeviceAddress(byte address)
{
	this->r3 &= 0xF0FF;
	this->r3 |= (address & 0xF) << 8;
}

bool ADB::getSRQEnable()
{
	return this->r3 & 0x2000;
}

void ADB::setSRQEnable(bool enable)
{
	this->r3 |= (0x2000 & (enable << 13));
}

void ADB::reset()
{
	this->r3 = this->initR3;
}
