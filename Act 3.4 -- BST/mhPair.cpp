#include "mhPair.h"

mhPair::mhPair() {
  
}

mhPair::mhPair(int acc, std::string ipAd) {
  accesos = acc;
  ip = ipAd;
}

int mhPair::getAccesos() {
  return accesos;
}

std::string mhPair::getIP() {
  return ip;
}

bool mhPair::operator==(const mhPair &other) {
  return this->accesos == other.accesos;
}

bool mhPair::operator!=(const mhPair &other) {
  return this->accesos != other.accesos;
}

bool mhPair::operator>(const mhPair &other) {
  return this->accesos > other.accesos;
}

bool mhPair::operator<(const mhPair &other) {
  return this->accesos < other.accesos;
}

bool mhPair::operator<=(const mhPair &other) {
  return this->accesos <= other.accesos;
}

bool mhPair::operator>=(const mhPair &other) {
  return this->accesos >= other.accesos;
}

