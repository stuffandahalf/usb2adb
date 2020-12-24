#include <hidboot.h>
#include "KeyReportHandler.h"

const byte POWER_PIN = 2;
const byte ADB_IN_PIN = 3;
const byte ADB_OUT_PIN = 4;

USB usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hidKeyboard(&usb);

KeyReportHandler keyHandler;

void setup()
{
	pinMode(POWER_PIN, OUTPUT);
	pinMode(ADB_IN_PIN, INPUT);
	pinMode(ADB_OUT_PIN, INPUT); // Leave pin state untouched until writing
	
	digitalWrite(POWER_PIN, HIGH);
	
	Serial.begin(115200);
	while (!Serial);
	
	if (usb.Init() == -1) {
		Serial.println("Failed to initialize USB interface");
		while(1);
	}
	
	delay(200);
	
	hidKeyboard.SetReportParser(0, &keyHandler);
}

void loop()
{
	usb.Task();
}
