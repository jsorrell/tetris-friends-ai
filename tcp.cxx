#include <iostream>
#include <cstdlib>
#include <string>
#include <crafter.h>
#include <boost/regex.hpp>
#include "tetPieces.hpp"

/* Collapse namespaces */
using namespace std;
using namespace Crafter;
using namespace boost;

/* Function for handling a packet */
void PacketHandler(Packet* sniff_packet, void* user) {
  regex rSeed("(?<=seed' t='n'>)(\\d+)(?=<)");
  regex rAttackReceived("(?<=lineAttack%\\d{4}%)(\\d)(?=%(true|false)%)");
  regex rAttackSent("(?<=lineAttack%\\d{4}%\\d{5}%)(\\d)(?=%(true|false)%)");
  /* sniff_packet -> pointer to the packet captured */
  /* user -> void pointer to the data supplied by the user */
  char *a;
  long seed;
  int attackLines;
  /* Check if there is a payload */
  RawLayer* raw_payload = sniff_packet->GetLayer<RawLayer>();
  IP* raw_ip = GetIP(*sniff_packet);
  if(raw_payload) {

    /* You can get the payload as a string */
    string payload = raw_payload->GetStringPayload();
    string ip = raw_ip->GetSourceIP();
    //cout << payload << endl;
    smatch mSeed;
    smatch mAttackReceived;
    smatch mAttackSent;
    regex_search(payload,mSeed,rSeed);
    regex_search(payload,mAttackReceived,rAttackReceived);
    regex_search(payload,mAttackSent,rAttackSent);
    if (mSeed[0].matched) {
      seed = strtol(mSeed[0].str().c_str(),&a,10);
      tetPieces pieces(seed);
      vector <tetPiece> ps = pieces.getNextPieces(100);
      for (int i = 0; i< 100; i++)
        cout << getName(ps[i]) << endl;
      cout << endl;
    }

    if (mAttackReceived[0].matched) {
      attackLines = strtol(mAttackReceived[0].str().c_str(),&a,10);
      cout << attackLines << " More Shit Line(s)!" << endl << endl;
    }
    
    if (mAttackSent[0].matched) {
      attackLines = strtol(mAttackSent[0].str().c_str(),&a,10);
      cout << "You Sent " << attackLines << " Line(s)!" << endl << endl;
    }
  }
}


int main() {
  //50.56.1.203
  Sniffer sniff("tcp and port 9339","wlan0",PacketHandler);

  sniff.Capture();
  //sniff.Spawn();

  //sniff.Cancel();

  return 0;
}
