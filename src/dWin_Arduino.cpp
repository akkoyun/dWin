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

bool dwin::Write_VP(const uint16_t _Address, const char *_Data) {

	// Define Address variables
	uint8_t _Address_Low = 0;
	uint8_t _Address_High = 0;

	// Get Address Low
	_Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High
	_Address_High = ((_Address & (uint16_t)0xFF00) >> 8);






}

// Define Library Class
dwin LCD;

// 1903