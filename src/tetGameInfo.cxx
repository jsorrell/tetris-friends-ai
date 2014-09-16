#include <thread>
#include <regex>
#include <tins/tins.h>
#include "tetGameInfo.hpp"
#include "tetConstants.hpp"

using namespace std;
using namespace Tetris;
using namespace Tins;


struct tetGameInfo::impl
{

void(*linesSentCallback)(int lines) = NULL;
void(*linesReceivedCallback)(int lines) = NULL;
void(*gameStartedCallback)() = NULL;
void(*gameEndedCallback)() = NULL;
Sniffer* lineSniffer;

int seed;
string interface;

////////////////////Random Gen////////////////////
///////////////PLEASE DO NOT MODIFY///////////////
int mRand1;
int mRand2;
int mRandBuffer[17];
int mSeed;

int getNextRandom()
{////////////MORE//MAGIC//////////
  int b = mRandBuffer[mRand1];
  int c = mRandBuffer[mRand2];

  int a = ((b << 3 & 0xFFFF) | (b >> 13 & 0xFFFF)) & 0xFFFF;
  a += ((c << 5 & 0xFFFF) | (c >> 11 & 0xFFFF)) & 0xFFFF;
  a &= 0xFFFF;
  mRandBuffer[mRand1] = a;
  mRand1 = mRand1 <= 0 ? 16 : mRand1-1;
  mRand2 = mRand2 <= 0 ? 16 : mRand2-1;
  return a & 0x7FFu;
}

void seedRandomPieceGen(int seed)
{////////////////MAGIC////////////////
  mSeed = seed & 0xFFFF;
  unsigned m = (unsigned)mSeed;
  for (int i = 0; i < 17; i++) {
    mRandBuffer[i] = m;
    m = (((m << 5) | (m >> 11)) & 0xFFFF) + 97;
    m &= 0xFFFF;
  }
  mRand1 = 0;
  mRand2 = 10;
  for (int i = 0; i < 100; i++)
    getNextRandom();
}

//////////////////

bool startGameHandler(PDU &pdu)
{
  const regex rSeed(tetConstants::start_game_regex); //also start
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mSeed;
  if(regex_search(payload,mSeed,rSeed)){
    int seed = strtol(mSeed[1].str().c_str(),NULL,10);
    seedRandomPieceGen(seed);
    this_thread::sleep_for(chrono::milliseconds(tetConstants::wait_to_play_first_piece_ms));
    if (gameStartedCallback){
      thread gameStarted(gameStartedCallback);
      gameStarted.detach();
    }
    return false;
  }
  return true;
}

bool endGameHandler(PDU &pdu)
{
  const regex rGameEnded(tetConstants::end_game_regex);
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mEnded;
  if(regex_search(payload,mEnded,rGameEnded)){
    if (gameEndedCallback){
      thread gameEnded(gameEndedCallback);
      gameEnded.detach();
    }
    return false;
  }
  return true;
}

bool lineHandler(PDU &pdu)
{
  const regex rAttackReceived(tetConstants::line_received_regex);
  const regex rAttackSent(tetConstants::line_sent_regex);

  /* Check if there is a payload */
  const vector<uint8_t> raw_payload = pdu.rfind_pdu<RawPDU>().payload();
  string payload(raw_payload.begin(), raw_payload.end());

  smatch mAttackReceived;
  if (regex_search(payload,mAttackReceived,rAttackReceived)) {
    int attackLines = strtol(mAttackReceived[1].str().c_str(),NULL,10);
    if (linesReceivedCallback){
      thread linesReceived(linesReceivedCallback,attackLines);
      linesReceived.detach();
    }
  }

  smatch mAttackSent;
  if (regex_search(payload,mAttackSent,rAttackSent)) {
    int attackLines = strtol(mAttackSent[1].str().c_str(),NULL,10);
    if (linesSentCallback){
      thread linesSent(linesSentCallback,attackLines);
      linesSent.detach();
    }
  }
  return true;
}

};

///////////////Packet Sniffer//////////////////////
/* Function for handling a packet */

tetGameInfo::tetGameInfo(string intf) : pimpl(new impl)
{
  pimpl->interface = intf;
  SnifferConfiguration config;
  config.set_filter(tetConstants::listen_filter);
  config.set_promisc_mode(false);
  pimpl->lineSniffer = new Sniffer(pimpl->interface,config);
}

//no sniffer data, for testing
tetGameInfo::tetGameInfo(int seed) : pimpl(new impl)
{
  pimpl->seedRandomPieceGen(seed);
}

tetGameInfo::~tetGameInfo()
{
}

void tetGameInfo::captureStart()
{
  SnifferConfiguration config;
  config.set_filter(tetConstants::listen_filter);
  config.set_promisc_mode(false);
  Sniffer startGameSniffer(pimpl->interface,config);
  startGameSniffer.sniff_loop(make_sniffer_handler(&*pimpl, &impl::startGameHandler));
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
  Sniffer endGameSniffer(pimpl->interface,config);
  endGameSniffer.sniff_loop(make_sniffer_handler(&*pimpl, &impl::endGameHandler));
}
void tetGameInfo::captureEndAsync()
{
  thread endCapture(&tetGameInfo::captureEnd,this);
  endCapture.detach();
}

void tetGameInfo::captureLines()
{
  pimpl->lineSniffer->sniff_loop(make_sniffer_handler(&*pimpl, &impl::lineHandler));
}

void tetGameInfo::captureLinesAsync()
{
  thread lineCapture(&tetGameInfo::captureLines,this);
  lineCapture.detach();
}

void tetGameInfo::registerLinesSentCallback(void(*callback)(const int numLines))
{
  pimpl->linesSentCallback = callback;
}
void tetGameInfo::registerLinesReceivedCallback(void(*callback)(const int numLines))
{
  pimpl->linesReceivedCallback = callback;
}
void tetGameInfo::registerGameStartedCallback(void(*callback)())
{
  pimpl->gameStartedCallback = callback;
}
void tetGameInfo::registerGameEndedCallback(void(*callback)())
{
  pimpl->gameEndedCallback = callback;
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
      pieceId = pimpl->getNextRandom() % 7;
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

