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
bool dwin::Set_HMI_Battery_Icon(uint8_t _Level) {

	// Declare Address
	uint16_t _Address = 0x2000;

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
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Icon(uint8_t _Level) {

	// Declare Address
	uint16_t _Address = 0x2001;

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
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second) {

	// Declare Address
	uint16_t _Address = 0x0010;

	// Declare Default Data Array
	char Data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	// Set Array Values
	Data[0] = _Year;
	Data[1] = _Month;
	Data[2] = _Day;
	Data[3] = _Second;
	Data[4] = _Hour;
	Data[5] = _Minute;

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Footer_Message(const String _Message) {

	// Declare Address
	uint16_t _Address = 0x1800;

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(_Address, TEXT, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Voltage(char _Phase, uint16_t _Value) {

	// Declare Address
	uint16_t _Address_Data;
	uint16_t _Address_Color;

	// Declare Default Data Array
	char Data[] = {0x00, 0x05};

	// Set Address Low Byte
	Data[1] = (_Value & (uint16_t)0x00FF);

	// Get Address High Byte
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Define Address
	switch (_Phase) {
	case 'R':
		
		_Address_Data = 0x2009;
		_Address_Color = 0xEE03;
		break;

	case 'S':
		
		_Address_Data = 0x200A;
		_Address_Color = 0xED03;
		break;

	case 'T':
		
		_Address_Data = 0x200B;
		_Address_Color = 0xEC03;
		break;
	
	default:
		break;
	}

	// Decide Colour
	if ((int)_Value > 25300 || (int)_Value < 19200) Write_VP(_Address_Color, POINTER, Color_Red, sizeof(Color_Red));
	
	// Send Data Pack
	Write_VP(_Address_Data, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Current(char _Phase, uint16_t _Value) {

	// Declare Address
	uint16_t _Address;

	// Declare Default Data Array
	char Data[] = {0x00, 0x05};

	// Set Address Low Byte
	Data[1] = (_Value & (uint16_t)0x00FF);

	// Get Address High Byte
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Define Address
	switch (_Phase) {
	case 'R':
		
		_Address = 0x200C;
		break;

	case 'S':
		
		_Address = 0x200D;
		break;

	case 'T':
		
		_Address = 0x200E;
		break;
	
	default:
		break;
	}

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Frequency(uint16_t _Value) {

	// Declare Address
	uint16_t _Address = 0x200F;
	uint16_t _Address_Color = 0xE803;

	// Declare Default Data Array
	char Data[] = {0x00, 0x05};

	// Set Address Low Byte
	Data[1] = (_Value & (uint16_t)0x00FF);

	// Get Address High Byte
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Decide Colour
	if ((int)_Value > 510 || (int)_Value < 490) Write_VP(_Address_Color, POINTER, Color_Red, sizeof(Color_Red));

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_PowerFactor(uint16_t _Value) {

	// Declare Address
	uint16_t _Address = 0x2023;

	// Declare Default Data Array
	char Data[] = {0x00, 0x05};

	// Set Address Low Byte
	Data[1] = (_Value & (uint16_t)0x00FF);

	// Get Address High Byte
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(_Address, POINTER, Data, sizeof(Data));

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

// Private Functions
bool dwin::Write_VP(const uint16_t _Address, uint8_t _Data_Type, char *_Data, uint8_t _Size) {

	// Set Address Low Byte
	uint8_t _Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High Byte
	uint8_t _Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variable
	uint8_t _Pack_Length = _Size + 3;

	// Set Pack Header
	Serial.write(0x5A);
	delay(1);
	Serial.write(0xA5);
	delay(1);
	Serial.write(_Pack_Length);
	delay(1);
	Serial.write(0x82);
	delay(1);
	Serial.write(_Address_High);
	delay(1);
	Serial.write(_Address_Low);
	delay(1);

	// Control for Data Type
	if (_Data_Type == TEXT) {

		// Text Defination	
		Serial.write(0xA1);
		Serial.write(0x00);
		Serial.write(0x30);
		Serial.write(0x03);
		Serial.write(0x01);
		Serial.write(0xDF);

	}

	// Send Pack
	for (uint8_t i = 0; i < _Size; i++) {
		
		Serial.write(_Data[i]);
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