#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11); // RX, TX

void setup()
{
	gsm.begin(9600);
	Serial.begin(9600);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	gsmInit();
}

void loop()
{
	if (gsm.available()>0)
	{
		Serial.println(gsm.readString());
	}
	gsm.println("AT+CMGF=1");
	delay(400);
	gsm.println("AT+CMGS=\"+94779847283\"");   // use your 10 digit cell no. here
	delay(400);
	Serial.println("TEST");
	delay(200);
	Serial.write(26);
	delay(10000);
}


void gsmInit()
{
	boolean at_flag = 1;
	while (at_flag)
	{
		gsm.println("AT");
		while (gsm.available()>0)
		{
			if (gsm.find("OK"))
				at_flag = 0;
		}

		delay(500);
	}
	Serial.println("Module Connected..");
	delay(500);
	Serial.println("Disabling ECHO");
	boolean echo_flag = 1;
	while (echo_flag)
	{
		gsm.println("ATE0");
		while (gsm.available()>0)
		{
			if (gsm.find("OK"))
				echo_flag = 0;
		}
		delay(500);
	}
	Serial.println("Echo OFF");
	delay(500);
	Serial.println("Finding Network..");
	boolean net_flag = 1;
	while (net_flag)
	{
		gsm.println("AT+CPIN?");
		while (gsm.available()>0)
		{
			if (gsm.find("+CPIN: READY"))
				net_flag = 0;
		}
		delay(500);
	}
	Serial.println("Network Found..");
	delay(500);
	gsm.println("AT+CMGF=1");
	delay(500);
	gsm.println("AT+CNMI=2,2,0,0,0");
	delay(500);

	digitalWrite(13, HIGH);
}