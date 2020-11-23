#include <USB.h>

const int POWER_PIN = 2;
const int ADB_PIN = 3;

ADB interface(ADB_PIN, POWER_PIN);

void setup()
{
	Serial.begin(115200);
	interface.init();
}

void loop()
{
	
}

