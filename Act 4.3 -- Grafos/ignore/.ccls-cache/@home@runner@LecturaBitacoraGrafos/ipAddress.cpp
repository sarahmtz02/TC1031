#include <cmath>
#include "ipAddress.h"

ipAddress::ipAddress(){
  ipString = "0.0.0.0";
  ipPort = "0000";
  ipIndex = 0;
  degree = 0;
  ipValue = 0;
}

ipAddress::ipAddress(std::string _ip, std::string _port, int idx){
  ipString=_ip;
  ipPort=_port;
  ipIndex = idx;
  degree = 0;
  // Convertir IP
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  int partA = std::stoi(results[0]);
  int partB = std::stoi(results[1]);
  int partC = std::stoi(results[2]);
  int partD = std::stoi(results[3]);
  ipValue = partA*(pow(256,3)) + partB*(pow(256,2)) + partC*(pow(256,1)) + partD;
  

}

std::string ipAddress::getIp(){
  return ipString;
}

std::string ipAddress::getIpPort(){
  return ipPort;
}

unsigned int ipAddress::getIpValue(){
  return ipValue;
}

int ipAddress::getIpIndex(){
  return ipIndex;
}

bool ipAddress::operator==(const ipAddress &other) {
  return this->ipValue == other.ipValue;
}

bool ipAddress::operator!=(const ipAddress &other) {
  return this->ipValue != other.ipValue;
}

bool ipAddress::operator>(const ipAddress &other) {
  return this->ipValue > other.ipValue;
}

bool ipAddress::operator>=(const ipAddress &other) {
  return this->ipValue >= other.ipValue;
}

bool ipAddress::operator<(const ipAddress &other) {
  return this->ipValue < other.ipValue;
}

bool ipAddress::operator<=(const ipAddress &other) {
  return this->ipValue <= other.ipValue;
}

//Complejidad O(1)
void ipAddress::setDegree(int g){
  degree = g;
}

//Complejidad O(1)
void ipAddress::addToDegree(){
  degree++;
}

//Complejidad O(1)
int ipAddress::getDegree(){
  return degree;
}