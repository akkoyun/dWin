/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#include <dWin.h>

// Global Functions
bool dwin::Set_HMI_Begin(void) {

	// Serial Begin
	HMI_Serial.begin(HMI_Serial_Baud);

}

// Battery Functions
bool dwin::Set_HMI_Battery(uint8_t _Level, float _IV, float _T, float _AC, float _SOC, uint16_t _FB, uint16_t _IB) {

	// Set Battery Icon
	Set_HMI_Battery_Icon(_Level);

	// Set IV Value
	Set_HMI_Battery_IV(_IV);

	// Set T Value
	Set_HMI_Battery_T(_T);

	// Set AC Value
	Set_HMI_Battery_AC(_AC);

	// Set SOC Value
	Set_HMI_Battery_SOC(_SOC);

	// Set FB Value
	Set_HMI_Battery_FB(_FB);

	// Set IB Value
	Set_HMI_Battery_IV(_IB);

	// End Function
	return(true);

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
bool dwin::Set_HMI_Battery_IV(float _Value) {

	// Control for Limits
	if (_Value > 0) {
		
		// Decide Colour
		Write_VP(Battery_IV_Color_Address, POINTER, Color_White, sizeof(Color_White));

	} else {

		// Decide Colour
		Write_VP(Battery_IV_Color_Address, POINTER, Color_Red, sizeof(Color_Red));

		// Set Absolute
		_Value *= -1;

	}
	
	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(Battery_IV_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Battery_T(float _Value) {

	// Control for Limits
	if (_Value > 0) {
		
		// Decide Colour
		Write_VP(Battery_T_Color_Address, POINTER, Color_White, sizeof(Color_White));

	} else {

		// Decide Colour
		Write_VP(Battery_T_Color_Address, POINTER, Color_Red, sizeof(Color_Red));

		// Set Absolute
		_Value *= -1;

	}

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(Battery_T_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Battery_AC(float _Value) {

	// Control for Limits
	if (_Value > 0) {
		
		// Decide Colour
		Write_VP(Battery_AC_Color_Address, POINTER, Color_White, sizeof(Color_White));

	} else {

		// Decide Colour
		Write_VP(Battery_AC_Color_Address, POINTER, Color_Red, sizeof(Color_Red));

		// Set Absolute
		_Value *= -1;

	}

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(Battery_AC_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Battery_SOC(float _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);
	
	// Send Data Pack
	Write_VP(Battery_SOC_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Battery_FB(uint16_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);
	
	// Send Data Pack
	Write_VP(Battery_FB_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_Battery_IB(uint16_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);
	
	// Send Data Pack
	Write_VP(Battery_IB_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}

// GSM Functions
bool dwin::Set_HMI_GSM(uint8_t _Level, uint8_t _Manufacturer, uint8_t _Model, uint16_t _Conn, uint16_t _RSSI, uint16_t _Operator, String _Firmware, String _IMEI, String _Serial, String _ICCID, String _IP) {

	// Set Data Set
	Set_HMI_GSM_Icon(_Level);
	Set_HMI_GSM_Manufacturer(_Manufacturer);
	Set_HMI_GSM_Model(_Model);
	Set_HMI_GSM_Connection_Time(_Conn);
	Set_HMI_GSM_RSSI(_RSSI);
	Set_HMI_GSM_Operator(_Operator);
	Set_HMI_GSM_Firmware(_Firmware);
	Set_HMI_GSM_IMEI(_IMEI);
	Set_HMI_GSM_Serial(_Serial);
	Set_HMI_GSM_ICCID(_ICCID);
	Set_HMI_GSM_IP(_IP);

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
bool dwin::Set_HMI_GSM_Manufacturer(uint8_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(GSM_Manufacturer_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Model(uint8_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(GSM_Model_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Connection_Time(uint16_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(GSM_Conn_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_RSSI(uint16_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(GSM_RSSI_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Operator(uint16_t _Value) {

	// Control for Limits
	if (_Value < 0) return(false);

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0]  = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(GSM_Operator_Value_Address, POINTER, Data, sizeof(Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Firmware(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(GSM_Firmware_Text_Address, POINTER, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_IMEI(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(GSM_IMEI_Text_Address, POINTER, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_Serial(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(GSM_Serial_Text_Address, POINTER, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_ICCID(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(GSM_ICCID_Text_Address, POINTER, _Data, sizeof(_Data));

	// End Function
	return(true);

}
bool dwin::Set_HMI_GSM_IP(const String _Message) {

	// Declare Data Variable
	char _Data[20];

	// Convert Data to Array
	_Message.toCharArray(_Data, 20);

	// Send Data Pack
	Write_VP(GSM_IP_Text_Address, POINTER, _Data, sizeof(_Data));

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
	if ((uint16_t)_Value_RAW > (uint16_t)25300 || (uint16_t)_Value_RAW < (uint16_t)19200) {
		Write_VP(_Address_Color, POINTER, Color_Red, sizeof(Color_Red));
	} else {
		Write_VP(_Address_Color, POINTER, Color_White, sizeof(Color_White));
	}
	
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
bool dwin::Set_HMI_Pressure(float _Value) {

	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 10);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Decide Colour
	if ((uint16_t)_Value_RAW > (uint16_t)14 || (uint16_t)_Value_RAW < (uint16_t)12) {

		// Change Color to RED
		Write_VP(Pressure_Color_Address, POINTER, Color_Red, sizeof(Color_Red));

	} else {

		// Change Color to White
		Write_VP(Pressure_Color_Address, POINTER, Color_White, sizeof(Color_White));

	}

	// Send Data Pack
	Write_VP(Pressure_Value_Address, POINTER, Data, sizeof(Data));

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