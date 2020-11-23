#include <Arduino.h>
#include "ADB.h"

ADB::ADB(int adb_pin, int power_pin)
{
	this->adb_pin = adb_pin;
	this->power_pin = power_pin;
}

ADB::~ADB()
{

}

void ADB::init()
{
	pinMode(this->adb_pin, INPUT);
	if (this->powerpin_valid()) {
		pinMode(this->powerpin_valid(), INPUT);
	}
}

void ADB::poweron()
{
	if (this->powerpin_valid()) {
		pinMode(this->power_pin, OUTPUT);
		digitalWrite(this->power_pin, LOW);
		delay(500);
		pinMode(this->power_pin, INPUT);
	}
}

bool ADB::powerpin_valid()
{
	return this->power_pin > 0;
}

