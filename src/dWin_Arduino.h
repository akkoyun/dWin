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

		/**
		 * @brief Write data to specified VP address.
		 * @version 01.00.00
		 * @param _Address Memmory address of dWin
		 * @param _Data Data to write
		 * @return true - Succsess
		 * @return false - Failed
		 */
		bool Write_VP(const uint16_t _Address, const char *_Data);

	private:

};

extern dwin LCD;

#endif /* defined(__dWin_Arduino__) */