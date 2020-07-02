#include <PushBulletPUYAR.h>


PushBullet::PushBullet(const String api_token, WiFiSSLClient &client, const String host, uint16_t SSLport){
	this->client = &client;
	this->api_token = api_token;
	this->host = host;
	this->SSLport = SSLport;
}


String PushBullet::buildRequest(String url, String body){
	String request = String("POST ") + url +" HTTP/1.1\r\n" +
		"Host: " + this->host + "\r\n" +
		"Access-Token: " + this->api_token + "\r\n" +
                "Content-Type: application/json\r\n" +
                "Content-Length: "+ String(body.length()) +"\r\n\r\n" +
                body + "\r\n";
	return request;
}


void PushBullet::sendRequest(String req){
 if (!client->connected()) {
    if (debug) Serial.println("Connecting to server");
    if (!client->connect(this->host.c_str(), this->SSLport)) {
      if (debug) Serial.println("Conection error");
    }
  }
  if (client->connected()) {
	    if (debug){
			Serial.println("\nRequest:");
			Serial.println(req);
			}
	  client->println(req);
	  client->stop();
	}
}
	

void PushBullet::sendNotePush(String title, String message){
	sendRequest(buildRequest("/v2/pushes", "{\"type\": \"note\", \"title\": \"" + title + "\", \"body\": \"" + message + "\"}"));
}


void PushBullet::sendLinkPush(String title, String message, String url){
	sendRequest(buildRequest("/v2/pushes", "{\"body\":\""+message+"\",\"title\":\""+title+"\",\"url\":\""+url+"\",\"type\":\"link\"}"));		   
}


void PushBullet::sendSMSPush(String message, String phoneNumber, String source, String device){
	sendRequest(buildRequest("/v2/ephemerals", "{\"push\": { \"conversation_iden\": \"" + phoneNumber + "\",\"message\": \"" + message + "\",\"package_name\": \"com.pushbullet.android\",\"source_user_iden\": \"" + device + "\",\"target_device_iden\": \"" + source +"\",\"type\": \"messaging_extension_reply\"},\"type\": \"push\"}"));
}


