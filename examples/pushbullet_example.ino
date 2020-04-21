#include <PushBulletPUYAR.h>
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "<your_ssid>";
char pass[] = "<your_pass>";

int status = WL_IDLE_STATUS;

WiFiSSLClient client;
PushBullet pb = PushBullet("<your_access_token>", client, "api.pushbullet.com", 443);

void setup() {
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.println("\nAttempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("Connected to wifi");
}

void loop() {
    pb.sendNotePush("<title>", "<message>");
	delay(3000);
	pb.sendLinkPush("<title>", "<message>", "<link-url>");
	delay(3000);
	/* get source_user_iden & target_device_iden: 
		curl --header 'Access-Token: <your_access_token_here>' \
			https://api.pushbullet.com/v2/devices */
	pd.sendSMSPush("<message>", "<receive_phoneNumber>", "<source_user_iden>", "<target_device_iden>" ) 

	while();
}