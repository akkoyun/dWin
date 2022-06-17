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

// Define Data Types
#define	__dWin_POINTER__ 	0
#define	__dWin_TEXT__ 		1
#define	__dWin_PRESSURE__ 	2

class dwin {

	private:

		// Stream Object Definition
		Stream * HMI_Serial;

		// Device Register Structure
		struct Register {
			const uint8_t High_Address;
			const uint8_t Low_Address;
		};

		// Color Constants
		uint8_t Color_Black[2] 	= {0x00, 0x00};
		uint8_t Color_White[2] 	= {0xFF, 0xFF};
		uint8_t Color_Red[2] 	= {0xF8, 0x00};
		uint8_t Color_Green[2] 	= {0x07, 0x40};
		uint8_t Color_Gray[2] 	= {0xAD, 0x55};

		/**
		 * @brief dWin data pack send function.
		 * @param _Register Register address
		 * @param _Data_Type Data type
		 * @param _Data Data array
		 * @param _Size Data array size
		 * @return true 
		 * @return false 
		 */
		void Write_VP(Register _Register, uint8_t _Data_Type, uint8_t *_Data, uint8_t _Size) {

			// Declare Length
			uint8_t _Pack_Size = 3;

			// Control for Data Type
			if (_Data_Type == __dWin_TEXT__) _Pack_Size += 6;

			// Set Pack Header
			HMI_Serial->write(0x5A);
			HMI_Serial->write(0xA5);
			HMI_Serial->write(_Size + _Pack_Size);
			HMI_Serial->write(0x82);
			HMI_Serial->write(_Register.High_Address);
			HMI_Serial->write(_Register.Low_Address);

			// Send Pack
			for (size_t i = 0; i < _Size; i++) {
				
				// Send Data Pack
				HMI_Serial->write(_Data[i]);

			}

			// Command Delay
			delay(100);
			
		}

	public:

		/**
		 * @brief HMI Start function.
		 * @param _Serial Serial connection variable
		 */
		void Begin(Stream &_Serial) {

			//Set serial port
			HMI_Serial = &_Serial;

		}

		/**
		 * @brief HMI voltage display function.
		 * @param _Phase Phase id (1:R - 2:S - 3:T)
		 * @param _Value Phase value
		 */
		void Set_HMI_Voltage(uint8_t _Phase, float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Phase
			if (_Phase == 1) {

				// Decide Colour
				if ((uint16_t)_Value_RAW > (uint16_t)25300 || (uint16_t)_Value_RAW < (uint16_t)19200) {

					// Declare Color Register
					Register Color_Register {0x80, 0x13};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

				} else {

					// Declare Color Register
					Register Color_Register {0x80, 0x13};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

				}

				// Declare Data Register
				Register Data_Register {0x60, 0x32};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} else if (_Phase == 2) {

				// Decide Colour
				if ((uint16_t)_Value_RAW > (uint16_t)25300 || (uint16_t)_Value_RAW < (uint16_t)19200) {

					// Declare Color Register
					Register Color_Register {0x80, 0x23};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

				} else {

					// Declare Color Register
					Register Color_Register {0x80, 0x23};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

				}

				// Declare Data Register
				Register Data_Register {0x60, 0x34};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} else if (_Phase == 3) {

				// Decide Colour
				if ((uint16_t)_Value_RAW > (uint16_t)25300 || (uint16_t)_Value_RAW < (uint16_t)19200) {

					// Declare Color Register
					Register Color_Register {0x80, 0x33};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

				} else {

					// Declare Color Register
					Register Color_Register {0x80, 0x33};

					// Write Data
					this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

				}

				// Declare Data Register
				Register Data_Register {0x60, 0x36};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} 
			
		}

		/**
		 * @brief HMI current display function.
		 * @param _Phase Phase id (1:R - 2:S - 3:T)
		 * @param _Value Phase value
		 */
		void Set_HMI_Current(uint8_t _Phase, float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = (uint16_t)abs(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Phase
			if (_Phase == 1) {

				// Declare Data Register
				Register Data_Register {0x61, 0x38};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} else if (_Phase == 2) {

				// Declare Data Register
				Register Data_Register {0x61, 0x40};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} else if (_Phase == 3) {

				// Declare Data Register
				Register Data_Register {0x61, 0x42};

				// Write Data
				this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

			} 
			
		}

		/**
		 * @brief HMI Get current ratio function.
		 */
		uint8_t Get_HMI_Current_Ratio(void) {

			// ->S: 5a a5 04 83 50 04 01 
			// ->R: 5a a5 06 83 50 04 01 00 00 
			// ->S: 5a a5 04 83 50 04 01 
			// ->R: 5a a5 06 83 50 04 01 00 03

			// Declare Default Data Array
			uint8_t Data[7] = {0x5A, 0xA5, 0x04, 0x83, 0x50, 0x04, 0x01};

			// Send Pack
			for (size_t i = 0; i < 7; i++) {
				
				// Send Data Pack
				HMI_Serial->write(Data[i]);

				// Stream Delay
				delay(1);

			}

			// Command Delay
			delay(50);

			// Declare Variable
			uint8_t _Response[9];
			uint8_t _Response_Order = 0;

			// Read UART Response
			while(HMI_Serial->available() > 0) {

				// Read Serial Char
				_Response[_Response_Order] = HMI_Serial->read();
				
				// Increase Read Order
				_Response_Order++;
				
				// Stream Delay
				delay(1);
				
			}

			// End Function
			return(_Response[0]);
			
		}

		/**
		 * @brief HMI frequency display function.
		 * @param _Value Phase value
		 */
		void Set_HMI_Frequency(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 10);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Colour
			if ((uint16_t)_Value_RAW > (uint16_t)510 || (uint16_t)_Value_RAW < (uint16_t)490) {

				// Declare Color Register
				Register Color_Register {0x70, 0x73};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

			} else {

				// Declare Color Register
				Register Color_Register {0x70, 0x73};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x10};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI power factor display function.
		 * @param _Value Phase value
		 */
		void Set_HMI_PowerFactor(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Valueh
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Handle Negative
			if (_Value > 0) {

				// Set Data Low/High Byte
				Data[1] = (_Value_RAW & (uint16_t)0x00FF);
				Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);


			} else {

				// Handle Value
				_Value_RAW = 0xFFFF & (~_Value_RAW + 1);

				// Set Data Low/High Byte
				Data[1] = (_Value_RAW & (uint16_t)0x00FF);
				Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x12};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI power consumption display function.
		 * @param _Value Phase value
		 */
		void Set_HMI_PowerConsumption(uint16_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x46};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI pressure display function.
		 * @param _Value Pressure value
		 */
		void Set_HMI_Pressure(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 10);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Colour
			if ((uint16_t)_Value_RAW > (uint16_t)100) {

				// Declare Color Register
				Register Color_Register {0x80, 0x83};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

			} else {

				// Declare Color Register
				Register Color_Register {0x80, 0x83};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x30};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief Battery detail function.
		 * @param _Level Battery level
		 * @param _IV Instant voltage
		 * @param _T Temperature
		 * @param _AC Average current
		 * @param _SOC State of charge
		 * @param _FB Full battery capacity
		 * @param _IB Instant battery capacity
		 */
		void Set_HMI_Battery(uint8_t _Level, float _IV, float _T, float _AC, float _SOC, uint16_t _FB, uint16_t _IB) {

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
			Set_HMI_Battery_IB(_IB);

		}

		/**
		 * @brief HMI battery icon display function.
		 * @param _Level Battery value
		 */
		void Set_HMI_Battery_Icon(uint8_t _Level) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

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

				break;
			}
			
			// Declare Data Register
			Register Data_Register {0x60, 0x02};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery voltage display function.
		 * @param _Value voltage value
		 */
		void Set_HMI_Battery_IV(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Colour
			if ((uint16_t)_Value_RAW > (uint16_t)0) {

				// Declare Color Register
				Register Color_Register {0x70, 0xB3};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

			} else {

				// Declare Color Register
				Register Color_Register {0x70, 0xB3};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x50};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery temperature display function.
		 * @param _Value Temperature value
		 */
		void Set_HMI_Battery_T(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Colour
			if ((uint16_t)_Value_RAW < (uint16_t)400) {

				// Declare Color Register
				Register Color_Register {0x80, 0xF3};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

			} else {

				// Declare Color Register
				Register Color_Register {0x80, 0xF3};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x52};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery current display function.
		 * @param _Value Current value
		 */
		void Set_HMI_Battery_AC(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Decide Colour
			if ((uint16_t)_Value_RAW > (uint16_t)50) {

				// Declare Color Register
				Register Color_Register {0x81, 0x03};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_Red, 2);

			} else {

				// Declare Color Register
				Register Color_Register {0x81, 0x03};

				// Write Data
				this->Write_VP(Color_Register, __dWin_POINTER__, Color_White, 2);

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x54};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery SOC display function.
		 * @param _Value SOC value
		 */
		void Set_HMI_Battery_SOC(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value * 100);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x56};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery FB display function.
		 * @param _Value FB value
		 */
		void Set_HMI_Battery_FB(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x58};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI battery IB display function.
		 * @param _Value IB value
		 */
		void Set_HMI_Battery_IB(float _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x60};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief GSM details page function
		 * @param _Level Signal level
		 * @param _Manufacturer Manufacturer
		 * @param _Model Model
		 * @param _Conn Connection time
		 * @param _RSSI RSSI
		 * @param _Operator Operator
		 * @param _Firmware Firmware
		 * @param _IMEI IMEI
		 * @param _Serial Serial
		 * @param _ICCID ICCID
		 * @param _IP IP
		 */
		void Set_HMI_GSM(uint8_t _Level, uint8_t _Manufacturer, uint8_t _Model, uint16_t _Conn, uint16_t _RSSI, uint16_t _Operator, char * _Firmware, char * _IMEI, char * _Serial, char * _ICCID, char * _IP) {

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

		/**
		 * @brief HMI GSM icon display function.
		 * @param _Level GSM signal value
		 */
		void Set_HMI_GSM_Icon(uint8_t _Level) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

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

				break;
			}
			
			// Declare Data Register
			Register Data_Register {0x60, 0x01};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM data send display function.
		 * @param _Level Send progress value
		 */
		void Set_HMI_GSM_Send(uint8_t _Level) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Set Data Array
			if (_Level == 1) {

				Data[1] = 0x01;

			} else if (_Level == 0) {

				Data[1] = 0x00;

			} else if (_Level == 2) {

				Data[1] = 0x02;

			}

			// Declare Data Register
			Register Data_Register {0x60, 0x80};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM manufacturer display function.
		 * @param _Level GSM manufacturer value
		 */
		void Set_HMI_GSM_Manufacturer(uint8_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x64};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM model display function.
		 * @param _Level GSM model value
		 */
		void Set_HMI_GSM_Model(uint8_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x66};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM connection time display function.
		 * @param _Level GSM connection time value
		 */
		void Set_HMI_GSM_Connection_Time(uint16_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x68};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM RSSI display function.
		 * @param _Level GSM RSSI value
		 */
		void Set_HMI_GSM_RSSI(uint16_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x70};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief HMI GSM operator display function.
		 * @param _Level GSM operator value
		 */
		void Set_HMI_GSM_Operator(uint16_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Convert Value
			uint16_t _Value_RAW = uint16_t(_Value);

			// Set Data Low/High Byte
			Data[1] = (_Value_RAW & (uint16_t)0x00FF);
			Data[0]  = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x72};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief GSM firmware function.
		 * @param _Message GSM firmware value
		 */
		void Set_HMI_GSM_Firmware(char * _Message) {

			// Declare Data Register
			Register Data_Register {0x70, 0x00};

			// Declare Data
			uint8_t _Data[8];

			// Convert char to uint array
			for (size_t i = 0; i < 8; i++) {
				_Data[i] = uint8_t(_Message[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 8);

		}

		/**
		 * @brief GSM IMEI function.
		 * @param _IMEI GSM IMEI value
		 */
		void Set_HMI_GSM_IMEI(char * _IMEI) {

			// Declare Data Register
			Register Data_Register {0x70, 0x10};

			// Declare Data
			uint8_t _Data[20];

			// Convert char to uint array
			for (size_t i = 0; i < 20; i++) {
				_Data[i] = uint8_t(_IMEI[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 20);

		}

		/**
		 * @brief GSM Serial ID function.
		 * @param _Serial GSM Serial ID value
		 */
		void Set_HMI_GSM_Serial(char * _Serial) {

			// Declare Data Register
			Register Data_Register {0x70, 0x20};

			// Declare Data
			uint8_t _Data[10];

			// Convert char to uint array
			for (size_t i = 0; i < 10; i++) {
				_Data[i] = uint8_t(_Serial[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 10);

		}

		/**
		 * @brief GSM ICCID function.
		 * @param _Serial GSM ICCID value
		 */
		void Set_HMI_GSM_ICCID(char * _ICCID) {

			// Declare Data Register
			Register Data_Register {0x70, 0x30};

			// Declare Data
			uint8_t _Data[20];

			// Convert char to uint array
			for (size_t i = 0; i < 20; i++) {
				_Data[i] = uint8_t(_ICCID[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 20);

		}

		/**
		 * @brief GSM IP function.
		 * @param _Serial GSM IP value
		 */
		void Set_HMI_GSM_IP(char * _IP) {

			// Declare Data Register
			Register Data_Register {0x70, 0x40};

			// Declare Data
			uint8_t _Data[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

			// Convert char to uint array
			for (size_t i = 0; i < 16; i++) {
				_Data[i] = uint8_t(_IP[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 16);

		}

		/**
		 * @brief Time stamp function.
		 */
		void Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second) {

			// Declare Default Data Array
			uint8_t _Data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

			// Set Array Values
			_Data[0] = _Year;
			_Data[1] = _Month;
			_Data[2] = _Day;
			_Data[4] = _Hour;
			_Data[5] = _Minute;
			_Data[6] = _Second;

			// Declare Data Register
			Register Data_Register {0x00, 0x10};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 8);

		}

		/**
		 * @brief Status function.
		 * @param _Serial Status value
		 */
		void Set_HMI_Status(uint16_t _State) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Set Data Low/High Byte
			Data[1] = (_State & (uint16_t)0x00FF);
			Data[0]  = ((_State & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x48};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief Device firmeare function.
		 * @param _Firmware Firmware value
		 */
		void Set_HMI_Firmware(char * _Firmware) {

			// Declare Data Register
			Register Data_Register {0x70, 0x60};

			// Declare Data
			uint8_t _Data[8];

			// Convert char to uint array
			for (size_t i = 0; i < 8; i++) {
				_Data[i] = uint8_t(_Firmware[i]);
			}

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, _Data, 16);

		}

		void Set_HMI_Test(uint16_t _Value) {

			// Declare Default Data Array
			uint8_t Data[2] = {0x00, 0x00};

			// Set Data Low/High Byte
			Data[1] = (_Value & (uint16_t)0x00FF);
			Data[0] = ((_Value & (uint16_t)0xFF00) >> 8);

			// Declare Data Register
			Register Data_Register {0x60, 0x74};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 2);

		}

		/**
		 * @brief LCD Sleep enable function.
		 * @param _Status Sleep status.
		 */
		void Set_HMI_Sleep(bool _Status) {

			// Data[0] - ON State Brightnes
			// Data[1] - Sleep State Brightnes
			// Data[2] - Sleep Time
			// Data[3] - Sleep Time
			
			// Declare Default Data Array
			uint8_t Data[4] = {0x64, 0x64, 0x0B, 0xB8};

			// Sleep State
			if (_Status) Data[1] = 0x64;
			if (!_Status) Data[1] = 0x00;

			// Declare Data Register
			Register Data_Register {0x00, 0x82};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 4);

		}

		/**
		 * @brief LCD reset function.
		 * @param _Status Reset status.
		 */
		void Set_HMI_Reset(void) {

			// Declare Default Data Array
			uint8_t Data[4] = {0x55, 0xAA, 0x5A, 0xA5};

			// Declare Data Register
			Register Data_Register {0x00, 0x04};

			// Write Data
			this->Write_VP(Data_Register, __dWin_POINTER__, Data, 4);

		}

};

#endif /* defined(__dWin_Arduino__) */