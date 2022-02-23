#include <dWin.h>

void setup() {

	HMI_Serial.begin(HMI_Serial_Baud);

}

void loop() {


	// Set Page Main
	LCD.Set_HMI_Page(0x00);

	// Set Battery Icon
	LCD.Set_HMI_Battery_Icon(2);

	// Set GSM Icon
	LCD.Set_HMI_GSM_Icon(3);

	// Set Time
	LCD.Set_HMI_Time_Stamp(25, 1, 22, 16, 58, 0);
	
	// Set Text Message
	LCD.Set_HMI_Footer_Message(String(millis()));
	
	// Loop Delay
	delay(1000);

	// Set Page Voltage
	LCD.Set_HMI_Page(0x01);

	// Set Voltage
	LCD.Set_HMI_Voltage('R', 190.32);
	LCD.Set_HMI_Voltage('S', 218.35);
	LCD.Set_HMI_Voltage('T', 240.33);

	// Set Current
	LCD.Set_HMI_Current('R', 20.3);
	LCD.Set_HMI_Current('S', 20.4);
	LCD.Set_HMI_Current('T', 2.5);

	// Set Frequency
	LCD.Set_HMI_Frequency(random(50.30));

	// Set Power Factor
	LCD.Set_HMI_PowerFactor(0.8);

	// Loop Delay
	delay(1000);

	// Set Page Pressure
	LCD.Set_HMI_Page(0x02);

	// Loop Delay
	delay(1000);

}
