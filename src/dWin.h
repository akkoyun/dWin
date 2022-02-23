/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#ifndef __dWin__
#define __dWin__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

#define HMI_Serial Serial1
#define	HMI_Serial_Baud 115200

class dwin {

	public:

		enum Data_Type {
			POINTER						= 0,				// 0
			TEXT						= 1,				// 1
			PRESSURE					= 2					// 2
		};

		bool Set_HMI_Begin(void);

		// Tool Functions
		bool Set_HMI_Page(uint8_t _Page_ID);
		bool Set_HMI_Sleep(bool _Status);

		// Information Functions
		bool Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second);
		bool Set_HMI_Footer_Message(const String _Message);

		// Battery Functions
		bool Set_HMI_Battery(uint8_t _Level, float _IV, float _T, float _AC, float _SOC, uint16_t _FB, uint16_t _IB);
		bool Set_HMI_Battery_Icon(uint8_t _Level);
		bool Set_HMI_Battery_IV(float _Value);
		bool Set_HMI_Battery_T(float _Value);
		bool Set_HMI_Battery_AC(float _Value);
		bool Set_HMI_Battery_SOC(float _Value);
		bool Set_HMI_Battery_FB(uint16_t _Value);
		bool Set_HMI_Battery_IB(uint16_t _Value);

		// GSM Functions
		bool Set_HMI_GSM(uint8_t _Level, uint8_t _Manufacturer, uint8_t _Model, uint16_t _Conn, uint16_t _RSSI, uint16_t _Operator, String _Firmware, String _IMEI, String _Serial, String _ICCID, String _IP);
		bool Set_HMI_GSM_Icon(uint8_t _Level);
		bool Set_HMI_GSM_Manufacturer(uint8_t _Value);
		bool Set_HMI_GSM_Model(uint8_t _Value);
		bool Set_HMI_GSM_Connection_Time(uint16_t _Value);
		bool Set_HMI_GSM_RSSI(uint16_t _Value);
		bool Set_HMI_GSM_Operator(uint16_t _Value);
		bool Set_HMI_GSM_Firmware(const String _Message);
		bool Set_HMI_GSM_IMEI(const String _Message);
		bool Set_HMI_GSM_Serial(const String _Message);
		bool Set_HMI_GSM_ICCID(const String _Message);
		bool Set_HMI_GSM_IP(const String _Message);

		// Energy Functions
		bool Set_HMI_Voltage(char _Phase, float _Value);
		bool Set_HMI_Current(char _Phase, float _Value);
		bool Set_HMI_Frequency(float _Value);
		bool Set_HMI_PowerFactor(float _Value);
		
		// Pressure Functions
		bool Set_HMI_Pressure(float _Value);

	private:

		// Battery Address
		const uint16_t Battery_Value_Address = 0x6002;
		const uint16_t Battery_IV_Value_Address = 0x6016;
		const uint16_t Battery_IV_Color_Address = 0x70B3;
		const uint16_t Battery_T_Value_Address = 0x6018;
		const uint16_t Battery_T_Color_Address = 0x70C3;
		const uint16_t Battery_AC_Value_Address = 0x601A;
		const uint16_t Battery_AC_Color_Address = 0x70D3;
		const uint16_t Battery_SOC_Value_Address = 0x601C;
		const uint16_t Battery_FB_Value_Address = 0x601E;
		const uint16_t Battery_IB_Value_Address = 0x6020;
		const uint16_t Battery_CYC_Value_Address = 0x6022;

		// GSM Icon Image Value Address
		const uint16_t GSM_Value_Address = 0x6001;
		const uint16_t GSM_Manufacturer_Value_Address = 0x6024;
		const uint16_t GSM_Model_Value_Address = 0x6026;
		const uint16_t GSM_Conn_Value_Address = 0x6028;
		const uint16_t GSM_RSSI_Value_Address = 0x602A;
		const uint16_t GSM_Operator_Value_Address = 0x602C;
		const uint16_t GSM_Firmware_Text_Address = 0x6030;
		const uint16_t GSM_IMEI_Text_Address = 0x6040;
		const uint16_t GSM_Serial_Text_Address = 0x6050;
		const uint16_t GSM_ICCID_Text_Address = 0x6060;
		const uint16_t GSM_IP_Text_Address = 0x6070;

		// Time Data Value Address
		const uint16_t Time_Value_Address = 0x0010;

		// Text Data Value Address
		const uint16_t Text_Value_Address = 0x6080;

		// Voltage Data Value Address
		const uint16_t Voltage_R_Value_Address = 0x6004;
		const uint16_t Voltage_S_Value_Address = 0x6006;
		const uint16_t Voltage_T_Value_Address = 0x6008;

		// Voltage Data Color Value Address
		const uint16_t Voltage_R_Color_Address = 0x7013;
		const uint16_t Voltage_S_Color_Address = 0x7023;
		const uint16_t Voltage_T_Color_Address = 0x7033;

		// Current Data Value Address
		const uint16_t Current_R_Value_Address = 0x610A;
		const uint16_t Current_S_Value_Address = 0x610C;
		const uint16_t Current_T_Value_Address = 0x610E;

		// Frequency Data Value Address
		const uint16_t Frequency_Value_Address = 0x6010;
		const uint16_t Frequency_Color_Address = 0x7073;

		// Power Factor Data Value Address
		const uint16_t Power_Factor_Value_Address = 0x6012;

		// Pressure Data Value Address
		const uint16_t Pressure_Value_Address = 0x6014;
		const uint16_t Pressure_Color_Address = 0x7093;

		// Page Value Address
		const uint16_t Page_Value_Address = 0x0084;

		// LCD Sleep Address
		const uint16_t Sleep_Value_Address = 0x0082;

		// Color Constants
		char Color_Black[2] = {0x00, 0x00};
		char Color_White[2] = {0xFF, 0xFF};
		char Color_Red[2] = {0xF8, 0x00};
		char Color_Green[2] = {0x07, 0x40};
		char Color_Gray[2] = {0xAD, 0x55};

		bool Write_VP(const uint16_t _Address, uint8_t _Data_Type, char *_Data, uint8_t _Size);

};

extern dwin LCD;

#endif /* defined(__dWin_Arduino__) */