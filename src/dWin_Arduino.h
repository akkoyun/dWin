/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#ifndef __dWin_Arduino__
#define __dWin_Arduino__

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

		bool Set_HMI_Battery_Icon(uint8_t _Level);
		bool Set_HMI_GSM_Icon(uint8_t _Level);
		bool Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second);
		bool Set_HMI_Footer_Message(const String _Message);
		bool Set_HMI_Voltage(char _Phase, float _Value);
		bool Set_HMI_Current(char _Phase, float _Value);
		bool Set_HMI_Frequency(float _Value);
		bool Set_HMI_PowerFactor(float _Value);
		bool Set_HMI_Pressure_Plot(uint8_t _Value);
		bool Set_HMI_Page(uint8_t _Page_ID);
		bool Set_HMI_Sleep(bool _Status);

	private:

		// Battery Icon Image Value Address
		const uint16_t Battery_Value_Address = 0x2000;

		// GSM Icon Image Value Address
		const uint16_t GSM_Value_Address = 0x2001;

		// Time Data Value Address
		const uint16_t Time_Value_Address = 0x0010;

		// Time Data Value Address
		const uint16_t Text_Value_Address = 0x1800;

		// Voltage Data Value Address
		const uint16_t Voltage_R_Value_Address = 0x2009;
		const uint16_t Voltage_S_Value_Address = 0x200A;
		const uint16_t Voltage_T_Value_Address = 0x200B;

		// Voltage Data Color Value Address
		const uint16_t Voltage_R_Color_Address = 0xEE03;
		const uint16_t Voltage_S_Color_Address = 0xED03;
		const uint16_t Voltage_T_Color_Address = 0xEC03;

		// Current Data Value Address
		const uint16_t Current_R_Value_Address = 0x200C;
		const uint16_t Current_S_Value_Address = 0x200D;
		const uint16_t Current_T_Value_Address = 0x200E;

		// Frequency Data Value Address
		const uint16_t Frequency_Value_Address = 0x200F;
		const uint16_t Frequency_Color_Address = 0xE803;

		// Power Factor Data Value Address
		const uint16_t Power_Factor_Value_Address = 0x2023;

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