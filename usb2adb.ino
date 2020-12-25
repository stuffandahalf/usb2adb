#include <hidboot.h>
#include "ADBStandardKeyboard.h"
#include "KeyReportHandler.h"

const byte POWER_PIN = 2;
const byte ADB_IN_PIN = 3;
const byte ADB_OUT_PIN = 4;

const unsigned short RESET_LENGTH = 3000;
const unsigned short ATN_LENGTH = 800;
const unsigned short SYNC_LENGTH = 70;

USB usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hidKeyboard(&usb);

volatile ADBStandardKeyboard kb;
KeyReportHandler kb_status(kb);

volatile byte request = 0;

void adb_handler()
{
	unsigned long t0, t1, dt;
	
	t0 = micros();
	while (!digitalRead(ADB_IN_PIN));
	t1 = micros();
	dt = t1 - t0;
	
	if (776 <= dt && dt <= 824) {
		// attention, proceed
	} else if (dt >= 824) {
		kb.reset();
		return;
	} else {
		// invalid signal
		return;
	}
	
	//t0 = micros();
	while (digitalRead(ADB_IN_PIN));
	/*t1 = micros();
	dt = t1 - t0;
	
	if (70 <= dt && dt <= 75) {
		// sync, proceed
	} else {
		
	}*/
	
	//byte request = 0;
	for (int i = 0; i < 8; i++) {
		t0 = micros();
		while (!digitalRead(ADB_IN_PIN));
		t1 = micros();
		dt = t1 - t0;
		if (50 <= dt && dt <= 72) {
			// 0 bit
			request |= (0 << i);
		} else if (dt < 50) {
			// 1 bit
			request |= (1 << i);
		} else {
			return;
		}
	}
}

void setup()
{
	pinMode(POWER_PIN, INPUT_PULLUP);
	pinMode(ADB_IN_PIN, INPUT);
	pinMode(ADB_OUT_PIN, INPUT); // Leave pin state untouched until writing
	
	Serial.begin(115200);
	while (!Serial);
	
	if (usb.Init() == -1) {
		Serial.println("Failed to initialize USB interface");
		while(1);
	}
	
	delay(200);
	
	hidKeyboard.SetReportParser(0, &kb_status);
	
	while (!digitalRead(ADB_IN_PIN));
	attachInterrupt(digitalPinToInterrupt(ADB_IN_PIN), adb_handler, LOW);
}

void loop()
{
	if (request) {
		Serial.println(request, HEX);
		request = 0;
	}
	usb.Task();
}
