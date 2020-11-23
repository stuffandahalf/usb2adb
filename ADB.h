#ifndef ADB_H
#define ADB_H	1

class ADB {
private:
	int adb_pin;
	int power_pin;

	bool powerpin_valid();

public:
	ADB(int adb_pin, int power_pin = -1);
	~ADB();

	void power_on();

};

#endif

