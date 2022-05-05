#include <dWin.h>

// Set HMI Object
dwin LCD;

void setup() {

	// Start Serial
	Serial.begin(115200);

	// Start HMI Serial
	Serial1.begin(115200);

	// Start LCD
	LCD.Begin(Serial1);

	// LCD Reset
	LCD.Set_HMI_Reset();

	// LCD boot Delay
	delay(100);

	Serial.println("Boot");

}

void loop() {

	// Dont Sleep
//	LCD.Set_HMI_Sleep(true);

	// Set Battery
	LCD.Set_HMI_Battery(5, 3, 12, 13, 14, 15, 16);

	// Set GSM
	LCD.Set_HMI_GSM(2,1,1,12,22,1,"01.01.01", "12345678901234567890", "222222", "33333", "123.123.123.123");

	// Set Voltage
	LCD.Set_HMI_Voltage(1, random(220));
	LCD.Set_HMI_Voltage(2, random(220));
	LCD.Set_HMI_Voltage(3, random(220));

	// Set Current
	LCD.Set_HMI_Current(1, random(5));
	LCD.Set_HMI_Current(2, random(5));
	LCD.Set_HMI_Current(3, random(5));

	// Set Frequency
	LCD.Set_HMI_Frequency(random(50));

	// Set Power Factor
	LCD.Set_HMI_PowerFactor(random(1));

	// Set Pressure
	LCD.Set_HMI_Pressure(random(10));

	// Set Time
	LCD.Set_HMI_Time_Stamp(25, 1, 22, 16, (millis() % 60), 0);

	// Status
//	LCD.Set_HMI_Status(516);

	// Loop Delay
	delay(1000);

}
