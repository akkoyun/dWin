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

// Define PGMspace Function
#include <avr/pgmspace.h>

/**
 * @brief Main Class
 */
class dwin {

	public:

		enum Data_Type {
			POINTER						= 0,				// 0
			TEXT						= 1,				// 1
			PRESSURE					= 2					// 2
		};

		bool Set_HMI_Battery_Icon(uint8_t _Level);
		bool Set_HMI_GSM_Icon(uint8_t _Level);
		bool Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second);
		bool Set_HMI_Footer_Message(const String _Message);
		bool Set_HMI_Voltage(char _Phase, uint16_t _Value);
		bool Set_HMI_Current(char _Phase, uint16_t _Value);
		bool Set_HMI_Frequency(uint16_t _Value);
		bool Set_HMI_PowerFactor(uint16_t _Value);
		bool Set_HMI_Pressure_Plot(uint8_t _Value);

	private:

		char Color_Black[2] = {0x00, 0x00};
		char Color_White[2] = {0xFF, 0xFF};
		char Color_Red[2] = {0xF8, 0x00};
		char Color_Green[2] = {0x07, 0x40};
		char Color_Gray[2] = {0xAD, 0x55};

		bool Write_VP(const uint16_t _Address, uint8_t _Data_Type, char *_Data, uint8_t _Size);

};

extern dwin LCD;

#endif /* defined(__dWin_Arduino__) */