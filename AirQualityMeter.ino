/*
 Name:		Fijnstofmeter.ino
 Created:	2/18/2018 11:26:28 AM
 Author:	Sebastiaan
*/

#include "libraries\SDS011_sensor\SDS011.h"
#include "libraries\arduino-tm1637-master\src\SevenSegmentTM1637.h"
#include "libraries\MQ135-master\MQ135.h"

#define PIN_RX D6
#define PIN_TX D7
SDS011 mySDS;

#define CLK_1 D3
#define DIO_1 D4
SevenSegmentTM1637 tm1637_p25(CLK_1, DIO_1);

#define CLK_2 D0
#define DIO_2 D5
SevenSegmentTM1637 tm1637_p10(CLK_2, DIO_2);

#define CLK_3 D1
#define DIO_3 D2
SevenSegmentTM1637 tm1637_mq135(CLK_3, DIO_3);

#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);


void setup()
{
	Serial.begin(115200);
	mySDS.begin(PIN_RX, PIN_TX);
	tm1637_p25.begin();
	tm1637_p25.setBacklight(20);
	tm1637_p10.begin();
	tm1637_p10.setBacklight(20);
	tm1637_mq135.begin();
	tm1637_mq135.setBacklight(20);

	tm1637_p25.printRaw(tm1637_p25.encode((char)('0')), 0);
	tm1637_p25.printRaw(tm1637_p25.encode((char)('1')), 1);
	tm1637_p25.printRaw(tm1637_p25.encode((char)('2')), 2);
	tm1637_p25.printRaw(tm1637_p25.encode((char)('3')), 3);

	tm1637_p10.printRaw(tm1637_p10.encode((char)('4')), 0);
	tm1637_p10.printRaw(tm1637_p10.encode((char)('5')), 1);
	tm1637_p10.printRaw(tm1637_p10.encode((char)('6')), 2);
	tm1637_p10.printRaw(tm1637_p10.encode((char)('7')), 3);

	tm1637_mq135.printRaw(tm1637_mq135.encode((char)('8')), 0);
	tm1637_mq135.printRaw(tm1637_mq135.encode((char)('9')), 1);
	tm1637_mq135.printRaw(tm1637_mq135.encode((char)('0')), 2);
	tm1637_mq135.printRaw(tm1637_mq135.encode((char)('1')), 3);

	delay(1000);
}


void readMq135()
{
	int nr_samples = 10;
	int delay_per_sample = 100;

	float rzero_total = 0.0;
	float ppm_total = 0.0;
	for (int i = 0; i < nr_samples; i++)
	{
		float rzero = mq135_sensor.getRZero();
		float ppm = mq135_sensor.getPPM();
		rzero_total += rzero;
		ppm_total += ppm;
		delay(delay_per_sample);
	}

	float rzero = rzero_total / nr_samples;
	float ppm = ppm_total / nr_samples;
	Serial.print("MQ135 RZero: ");
	Serial.print(rzero);
	Serial.print("\t PPM: ");
	Serial.println(ppm);

	int ppm_for_display = (int)ppm;
	if (ppm_for_display < 0)
		ppm_for_display = 0;
	if (ppm_for_display > 9999)
		ppm_for_display = 9999;

	char digits[5] = { '\0' };
	digits[0] = ppm_for_display / 1000;
	if (digits[0] == 0)
		digits[0] = ' ';
	else
		digits[0] += '0';

	digits[1] = (ppm_for_display % 1000) / 100;
	if (digits[0] == 0 && digits[1] == 0)
		digits[1] = ' ';
	else
		digits[1] += '0';

	digits[2] = (ppm_for_display % 100) / 10;
	if (digits[0] == 0 && digits[1] == 0 && digits[2] == 0)
		digits[2] = ' ';
	else
		digits[2] += '0';

	digits[3] = ppm_for_display % 10 + '0';

	tm1637_mq135.print(digits);
}


void updateDisplay(SevenSegmentTM1637& display, float value)
{
	int intValue = (int)(value * 10);
	char ch;
	if (intValue >= 1000)
	{
		ch = '0' + intValue / 1000;
	}
	else
	{
		ch = ' ';
	}
	display.printRaw(display.encode(ch), 0);

	intValue = intValue % 1000;
	if (intValue >= 100)
	{
		ch = '0' + intValue / 100;
	}
	else
	{
		ch = ' ';
	}
	display.printRaw(display.encode(ch), 1);

	intValue = intValue % 100;
	ch = '0' + intValue / 10;
	// Enable decimal dot on third digit to function as decimal separator. Highest bit turns this decimal dot on.
	display.printRaw(display.encode(ch) | B10000000, 2);

	intValue = intValue % 10;
	ch = '0' + intValue;
	display.printRaw(display.encode(ch), 3);
}


void readSds011()
{
	float p25;
	float p10;
	int error = mySDS.read(&p25, &p10);
	if (!error)
	{
		Serial.println("P2.5: " + String(p25));
		Serial.println("P10:  " + String(p10));
		updateDisplay(tm1637_p25, p25);
		updateDisplay(tm1637_p10, p10);

	}
	else
	{
		Serial.println("error");
		tm1637_p25.write("Err");
		tm1637_p10.write("Err");
	}
}


void loop() 
{
	readMq135();
	readSds011();

	// No delay because reading the Mq135 already has a delay
	//delay(1000);
}
