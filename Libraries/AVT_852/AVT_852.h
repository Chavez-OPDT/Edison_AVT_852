/*
  AVT.cpp - Library for communication with an Advanced Vehicle Technologies AVT-852.
  Created by Josh Chavez of Omnipotent Performance Diesel Tuning, January 1, 2017.
  (c) 2017 Omnipotent Perofmance Diesel Tuning, LLC
*/

#ifndef AVT_852_h
#define AVT_852_h

#include "Arduino.h"
#define debug Serial1

class AVT_852 {

  public:
    AVT_852();
    void begin(int baud);
    bool firmware (byte *firm);
    bool model (byte *mod);
    void flushReceive ();
    void flush();
    byte write(byte *data, int size);
    bool can ();
    bool vpw ();
    bool kwp ();
    bool swc ();
    bool echoStatus ();
    bool echoStatus (bool x);
    bool timeStamps ();
    bool timeStamps (bool x);
    bool networkMessages ();
    bool networkMessages (bool x);
    bool transmitAcks ();
    bool transmitAcks (bool x);
    byte destinationFilter ();
    bool destinationFilter (byte x);
    byte sourceFilter ();
    bool sourceFilter (byte x);
    byte ledRate ();
    bool highSpeed();
    bool highSpeed(bool x);
    byte mode ();
    byte read(byte *buf);

  private:
    uint16_t _baud;
    byte _timeoutCheck;
    bool _debug = true;
    
};

#endif

