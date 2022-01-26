#include <dWin_Arduino.h>

void setup() {

	Serial.begin(115200);

}

void loop() {

	// Set Battery Icon
	LCD.Set_HMI_Battery_Icon(2);

	// Set GSM Icon
	LCD.Set_HMI_GSM_Icon(3);

	// Set Time
	LCD.Set_HMI_Time_Stamp(25, 1, 22, 16, 58, 0);
	
	// Set Text Message
	LCD.Set_HMI_Footer_Message(String(millis()));
	
	// Set Voltage
	LCD.Set_HMI_Voltage('R', 19055);
	LCD.Set_HMI_Voltage('S', 25500);
	LCD.Set_HMI_Voltage('T', 22005);

	// Set Current
	LCD.Set_HMI_Current('R', 203);
	LCD.Set_HMI_Current('S', 204);
	LCD.Set_HMI_Current('T', 205);

	// Set Frequency
	LCD.Set_HMI_Frequency(523);

	// Set Power Factor
	LCD.Set_HMI_PowerFactor(503);

	// Set Pressure
	LCD.Set_HMI_Pressure_Plot(random(15, 25));

	// Loop Delay
	delay(250);

}
