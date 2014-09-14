#include "tetGameInfo.hpp"
using namespace std;
using namespace Tetris;
using namespace Tins;

///////////////Packet Sniffer//////////////////////
/* Function for handling a packet */

tetGameInfo::tetGameInfo(string intf)
{
  this->interface = intf;
  SnifferConfiguration config;
  config.set_filter(tetConstants::listen_filter);
  config.set_promisc_mode(false);
  lineSniffer = new Sniffer(this->interface,config);
}

//no sniffer data, for testing
tetGameInfo::tetGameInfo(int seed)
{
  this->rand = new tetRandomPieceGen(seed);
}

tetGameInfo::~tetGameInfo()
{
  delete lineSniffer;
}

bool tetGameInfo::startGameHandler(PDU &pdu)
{
  const regex rSeed(tetConstants::start_game_regex); //also start
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mSeed;
  if(regex_search(payload,mSeed,rSeed)){
    int seed = strtol(mSeed[1].str().c_str(),NULL,10);
    this->rand = new tetRandomPieceGen(seed);
    this_thread::sleep_for(chrono::milliseconds(tetConstants::wait_to_play_first_piece_ms));
    if (this->gameStartedCallback){
      thread gameStarted(this->gameStartedCallback);
      gameStarted.detach();
    }
    return false;
  }
  return true;
}

bool tetGameInfo::endGameHandler(PDU &pdu)
{
  const regex rGameEnded(tetConstants::end_game_regex);
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mEnded;
  if(regex_search(payload,mEnded,rGameEnded)){
    delete this->rand;
    if (this->gameEndedCallback){
      thread gameEnded(this->gameEndedCallback);
      gameEnded.detach();
    }
    return false;
  }
  return true;
}

bool tetGameInfo::lineHandler(PDU &pdu)
{
  const regex rAttackReceived(tetConstants::line_received_regex);
  const regex rAttackSent(tetConstants::line_sent_regex);

  /* Check if there is a payload */
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mAttackReceived;
  if (regex_search(payload,mAttackReceived,rAttackReceived)) {
    int attackLines = strtol(mAttackReceived[1].str().c_str(),NULL,10);
    if (this->linesReceivedCallback){
      thread linesReceived(this->linesReceivedCallback,attackLines);
      linesReceived.detach();
    }
  }

  smatch mAttackSent;
  if (regex_search(payload,mAttackSent,rAttackSent)) {
    int attackLines = strtol(mAttackSent[1].str().c_str(),NULL,10);
    if (this->linesSentCallback){
      thread linesSent(this->linesSentCallback,attackLines);
      linesSent.detach();
    }
  }
  return true;
}


void tetGameInfo::captureStart()
{
  SnifferConfiguration config;
  config.set_filter(tetConstants::listen_filter);
  config.set_promisc_mode(false);
  Sniffer startGameSniffer(interface,config);
  startGameSniffer.sniff_loop(make_sniffer_handler(this, &tetGameInfo::startGameHandler));
}
void tetGameInfo::captureStartAsync()
{
  thread startCapture(&tetGameInfo::captureStart,this);
  startCapture.detach();
}

void tetGameInfo::captureEnd()
{
  SnifferConfiguration config;
  config.set_filter(tetConstants::listen_filter);
  config.set_promisc_mode(false);
  Sniffer endGameSniffer(interface,config);
  endGameSniffer.sniff_loop(make_sniffer_handler(this, &tetGameInfo::endGameHandler));
}
void tetGameInfo::captureEndAsync()
{
  thread endCapture(&tetGameInfo::captureEnd,this);
  endCapture.detach();
}

void tetGameInfo::captureLines()
{
  lineSniffer->sniff_loop(make_sniffer_handler(this, &tetGameInfo::lineHandler));
}

void tetGameInfo::captureLinesAsync()
{
  thread lineCapture(&tetGameInfo::captureLines,this);
  lineCapture.detach();
}

void tetGameInfo::registerLinesSentCallback(void(*callback)(const int numLines))
{
  linesSentCallback = callback;
}
void tetGameInfo::registerLinesReceivedCallback(void(*callback)(const int numLines))
{
  linesReceivedCallback = callback;
}
void tetGameInfo::registerGameStartedCallback(void(*callback)())
{
  gameStartedCallback = callback;
}
void tetGameInfo::registerGameEndedCallback(void(*callback)())
{
  gameEndedCallback = callback;
}

/////////////////////Pieces/////////////////////////////////

vector <tetPiece> tetGameInfo::getNextBag()
{
  vector<tetPiece> bag;
  vector<bool> refillSlots(7,false);
  //create bag of 7 pieces
  for (int i = 0; i < 7; i++) {
    //keep picking until get one that has not been picked yet.
    int pieceId;
    do {
      pieceId = rand->getNextRandom() % 7;
    } while (refillSlots[pieceId]);
    //found one not made yet
    refillSlots[pieceId] = true;
    string type = tetConstants::piecegen_map[pieceId];
    tetPiece piece(type);
    //put in bag
    bag.push_back(piece);
  }
  return bag;
}

////////////////////Random Gen////////////////////
///////////////PLEASE DO NOT MODIFY///////////////
tetRandomPieceGen :: tetRandomPieceGen(int seed)
{////////////////MAGIC////////////////
  this->mSeed = seed & 0xFFFF;
  unsigned m = (unsigned)mSeed;
  for (int i = 0; i < 17; i++) {
    this->mRandBuffer[i] = m;
    m = (((m << 5) | (m >> 11)) & 0xFFFF) + 97;
    m &= 0xFFFF;
  }
  mRand1 = 0;
  mRand2 = 10;
  for (int i = 0; i < 100; i++)
    this->getNextRandom();
}

int tetRandomPieceGen :: getNextRandom()
{////////////MORE//MAGIC//////////
  int b = this->mRandBuffer[this->mRand1];
  int c = this->mRandBuffer[this->mRand2];

  int a = ((b << 3 & 0xFFFF) | (b >> 13 & 0xFFFF)) & 0xFFFF;
  a += ((c << 5 & 0xFFFF) | (c >> 11 & 0xFFFF)) & 0xFFFF;
  a &= 0xFFFF;
  this->mRandBuffer[this->mRand1] = a;
  this->mRand1 = this->mRand1 <= 0 ? 16 : this->mRand1-1;
  this->mRand2 = this->mRand2 <= 0 ? 16 : this->mRand2-1;
  return a & 0x7FFu;
}