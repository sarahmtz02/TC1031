#ifndef _MH_PAIR_
#define _MH_PAIR_

#include <string>

class mhPair {
  private:
    int accesos;
    std::string ip;

  public:
    mhPair();
    mhPair(int acc, std::string ipAd);
    int getAccesos();
    std::string getIP();
    bool operator ==(const mhPair&);
    bool operator !=(const mhPair&);
    bool operator >(const mhPair&);
    bool operator <(const mhPair&);
    bool operator <=(const mhPair&);
    bool operator >=(const mhPair&);

};

#endif  // _MH_PAIR_
