#ifndef _PushbulletPUYAR_H_
#define _PushbulletPUYAR_H_

#include <Arduino.h>
#include <WiFiSSLClient.h>

#define debug true

class PushBullet{
	
	public:
	
		PushBullet(const String api_token, WiFiSSLClient &client, const String host, uint16_t SSLport);
		void sendNotePush(String title, String message);
		void sendLinkPush(String title, String message, String url);
		void sendSMSPush(String message, String phoneNumber, String source, String device);
				
	private:
	
		String buildRequest(String url, String body);

		void sendRequest(String req);
		
		WiFiSSLClient *client;
		
		String api_token;
		String host;
		uint16_t SSLport;

};


#endif
