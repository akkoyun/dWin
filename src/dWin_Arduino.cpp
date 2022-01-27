/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#include <dWin_Arduino.h>

// Global Functions
bool dwin::Set_HMI_Begin(void) {

	// Serial Begin
	HMI_Serial.begin(HMI_Serial_Baud);

}
bool dwin::Set_HMI_Battery_Icon(uint8_t _Level) {

	// Control for Limits
	if (_Level < 0) return(false);
	if (_Level > 5) return(false);

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Set Data Array
	switch (_Level) {
	case 0:
		
		Data[1] = 0x00;
		break;
	
	case 1:
		
		Data[1] = 0x01;
		break;
	
	case 2:
		
		Data[1] = 0x02;
		break;
	
	case 3:
		
		Data[1] = 0x03;
		break;
	
	case 4:
		
		Data[1] = 0x04;
		break;
	
	case 5:
		
		Data[1] = 0x05;
		break;
	
	default:

		// End Function
		return(false);

		break;
	}
	
	// Send Data Pack
	Write_VP(Battery_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Icon(uint8_t _Level) {

	// Control for Limits
	if (_Level < 0) return(false);
	if (_Level > 6) return(false);

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Set Data Array
	switch (_Level) {
	case 0:
		
		Data[1] = 0x00;
		break;
	
	case 1:
		
		Data[1] = 0x01;
		break;
	
	case 2:
		
		Data[1] = 0x02;
		break;
	
	case 3:
		
		Data[1] = 0x03;
		break;
	
	case 4:
		
		Data[1] = 0x04;
		break;
	
	case 5:
		
		Data[1] = 0x05;
		break;
	
	case 6:
		
		Data[1] = 0x06;
		break;

	default:

		// End Function
		return(false);

		break;
	}
	
	// Send Data Pack
	Write_VP(GSM_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second) {

	// Declare Default Data Array
	char Data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	// Set Array Values
	Data[0] = _Year;
	Data[1] = _Month;
	Data[2] = _Day;
	Data[4] = _Hour;
	Data[5] = _Minute;
	Data[6] = _Second;

	// Send Data Pack
	Write_VP(Time_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Footer_Message(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(Text_Value_Address, TEXT, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Voltage(char _Phase, float _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Address
	uint16_t _Address_Data;
	uint16_t _Address_Color;

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Define Address
	switch (_Phase) {
	case 'R':
		
		_Address_Data = Voltage_R_Value_Address;
		_Address_Color = Voltage_R_Color_Address;
		break;

	case 'S':
		
		_Address_Data = Voltage_S_Value_Address;
		_Address_Color = Voltage_S_Color_Address;
		break;

	case 'T':
		
		_Address_Data = Voltage_T_Value_Address;
		_Address_Color = Voltage_T_Color_Address;
		break;
	
	default:

		// End Function
		return(false);

		break;
	}

	// Decide Colour
	if ((uint16_t)_Value_RAW > (uint16_t)25300 || (uint16_t)_Value_RAW < (uint16_t)19200) Write_VP(_Address_Color, POINTER, Color_Red, sizeof(Color_Red));
	
	// Send Data Pack
	Write_VP(_Address_Data, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Current(char _Phase, float _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Address
	uint16_t _Address;

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 10);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Define Address
	switch (_Phase) {
	case 'R':
		
		_Address = Current_R_Value_Address;
		break;

	case 'S':
		
		_Address = Current_S_Value_Address;
		break;

	case 'T':
		
		_Address = Current_T_Value_Address;
		break;
	
	default:
		break;
	}

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Frequency(float _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 10);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Decide Colour
	if ((uint16_t)_Value_RAW > (uint16_t)510 || (uint16_t)_Value_RAW < (uint16_t)490) Write_VP(Frequency_Color_Address, POINTER, Color_Red, sizeof(Color_Red));

	// Send Data Pack
	Write_VP(Frequency_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_PowerFactor(float _Value) {

	// Control for Limits
	if (_Value < -1) return(false);
	if (_Value > 1) return(false);

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(Power_Factor_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Pressure_Plot(uint8_t _Value) {

	// Declare Address
	uint16_t _Address = 0x0310;

	// Declare Default Data Array
	char Data[] = {0x5A, 0xA5, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00};

	// Get Address High Byte
	Data[7] = _Value;
	Data[9] = _Value;

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Page(uint8_t _Page_ID) {

	// Control for Limits
	if (_Page_ID < 0) return(false);

	// Declare Default Data Array
	char Data[4] = {0x5A, 0x01, 0x00, 0x00};

	// Set Data Low/High Byte
	Data[3] = _Page_ID;

	// Send Data Pack
	Write_VP(Page_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Sleep(bool _Status) {

	// Data[0] - ON State Brightnes
	// Data[1] - Sleep State Brightnes
	// Data[2] - Sleep Time
	// Data[3] - Sleep Time
	
	// Declare Default Data Array
	char Data[4] = {0x64, 0x64, 0x0B, 0xB8};

	// Sleep State ON
	if (_Status) Data[1] = 0x00;
		
	// Send Data Pack
	Write_VP(Sleep_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}

// Private Functions
bool dwin::Write_VP(const uint16_t _Address, uint8_t _Data_Type, char *_Data, uint8_t _Size) {

	// Set Address Low Byte
	uint8_t _Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High Byte
	uint8_t _Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variable
	uint8_t _Pack_Length = _Size + 3;

	// Set Pack Header
	HMI_Serial.write(0x5A);
	delay(1);
	HMI_Serial.write(0xA5);
	delay(1);
	HMI_Serial.write(_Pack_Length);
	delay(1);
	HMI_Serial.write(0x82);
	delay(1);
	HMI_Serial.write(_Address_High);
	delay(1);
	HMI_Serial.write(_Address_Low);
	delay(1);

	// Control for Data Type
	if (_Data_Type == TEXT) {

		// Text Defination	
		HMI_Serial.write(0xA1);
		HMI_Serial.write(0x00);
		HMI_Serial.write(0x30);
		HMI_Serial.write(0x03);
		HMI_Serial.write(0x01);
		HMI_Serial.write(0xDF);

	}

	// Send Pack
	for (uint8_t i = 0; i < _Size; i++) {
		
		HMI_Serial.write(_Data[i]);
		delay(1);

	}
	
	// Command Delay
	delay(10);

	// End Function
	return(true);

}

// Define Library Class
dwin LCD;

// 1903