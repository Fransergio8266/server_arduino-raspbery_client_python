/*
 * UIPEthernet EchoServer example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *      -----------------
 *
 * This Hello World example sets up a server at 192.168.1.6 on port 1000.
 * Telnet here to access the service.  The uIP stack will also respond to
 * pings to test if you have successfully established a TCP connection to
 * the Arduino.
 *
 * This example was based upon uIP hello-world by Adam Dunkels <adam@sics.se>
 * Ported to the Arduino IDE by Adam Nielsen <malvineous@shikadi.net>
 * Adaption to Enc28J60 by Norbert Truchsess <norbert.truchsess@t-online.de>
 */

#include <UIPEthernet.h>

EthernetServer server = EthernetServer(1000);

void setup()
{
  Serial.begin(9600);
  //MAC for the shield:
  uint8_t mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
  //the IP address for the shield:
  byte ip[] = { 169, 254, 102, 173 };
  //the gateway for the shield:
  byte gateway[] = { 169, 254, 1, 1 };
  //the sbnet for the shield:
  byte subnet[] = {255,255,0,0};
  byte myDns[] = { 169, 254, 1, 1 };

  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  delay(500);
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());
  server.begin();
  delay(500);
}

void loop()
{
  size_t size;

  if (EthernetClient client = server.available())
    {
     
      while((size = client.available()) > 0)
        {
          uint8_t* msg = (uint8_t*)malloc(size);
          size = client.read(msg,size);
          Serial.write(msg,size);
          client.write(msg,size);
          free(msg);
          delay(500);
        }
  
    }
}
