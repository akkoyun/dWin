
void setup() {

	Serial.begin(115200);

}

void loop() {

Text(0);
delay(500);

}

bool Write_VP(const uint16_t _Address, char *_Data, uint8_t _Size) {

	// Define Address variables
	uint8_t _Address_Low = 0;
	uint8_t _Address_High = 0;

	// Get Address Low
	_Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High
	_Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variables
	uint8_t _Pack_Length = 0;

	// Set Legth
	_Pack_Length = _Size + 3;

	// Send Pack
	Serial.write(0x5A);
	Serial.write(0xA5);
	Serial.write(_Pack_Length);
	Serial.write(0x82);
	Serial.write(_Address_High);
	Serial.write(_Address_Low);
	for (uint8_t i = 0; i < _Size; i++) Serial.write(_Data[i]);
	
	// End Function
	return(true);

}
bool Write_VP_Text(const uint16_t _Address, char *_Data, uint8_t _Size) {

	// Define Address variables
	uint8_t _Address_Low = 0;
	uint8_t _Address_High = 0;

	// Get Address Low
	_Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High
	_Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variables
	uint8_t _Pack_Length = 0;

	// Set Legth
	_Pack_Length = _Size + 9;

	// Send Pack
	Serial.write(0x5A);
	Serial.write(0xA5);
	Serial.write(_Pack_Length);
	Serial.write(0x82);
	Serial.write(_Address_High);
	Serial.write(_Address_Low);
	Serial.write(0xA1);
	Serial.write(0x00);
	Serial.write(0x30);
	Serial.write(0x03);
	Serial.write(0x01);
	Serial.write(0xDF);

	for (uint8_t i = 0; i < _Size; i++) Serial.write(_Data[i]);
	
	// End Function
	return(true);

}

bool Battery_Icon(uint8_t _Level) {

	char Data[] = {0x00, 0x00};

	if (_Level == 0) Data[1] = 0x00;
	if (_Level == 1) Data[1] = 0x01;
	if (_Level == 2) Data[1] = 0x02;
	if (_Level == 3) Data[1] = 0x03;
	if (_Level == 4) Data[1] = 0x04;
	if (_Level == 5) Data[1] = 0x05;
	
	Write_VP(0x2000, Data, sizeof(Data));

	return(true);

}
bool GSM_Icon(uint8_t _Level) {

	char Data[] = {0x00, 0x00};

	if (_Level == 0) Data[1] = 0x00;
	if (_Level == 1) Data[1] = 0x01;
	if (_Level == 2) Data[1] = 0x02;
	if (_Level == 3) Data[1] = 0x03;
	if (_Level == 4) Data[1] = 0x04;
	if (_Level == 5) Data[1] = 0x05;
	
	Write_VP(0x2001, Data, sizeof(Data));

	return(true);

}
bool Time(uint8_t _Level) {


	char Data[] = {22, 1, 25, 0, 15, 30};

	
	Write_VP(0x0010, Data, sizeof(Data));

	return(true);

}
bool Text(uint8_t _Level) {


	char Data[] = "Test 12345                   |";

	
	Write_VP_Text(0x1800, Data, sizeof(Data));

	return(true);

}






