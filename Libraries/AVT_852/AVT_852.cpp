/*
  AVT.cpp - Library for communication with an Advanced Vehicle Technologies AVT-852.
  Created by Josh Chavez of Omnipotent Performance Diesel Tuning, January 1, 2017.
  (c) 2017 Omnipotent Perofmance Diesel Tuning, LLC
*/

#include "Arduino.h"
#include "AVT_852.h"

RingBuffer rx_buffer_AVT;
TTYUARTClass SerialAVT(&rx_buffer_AVT, 3, false);


AVT_852::AVT_852 () {

}

void AVT_852::begin (int baud) {
  SerialAVT.init_tty("/dev/ttyUSB0");
  SerialAVT.begin(baud);
}

bool AVT_852::firmware (byte *firm) {
  byte d[4];
  byte cmd[2] = {0xB1, 0x01};  
  SerialAVT.write (cmd, sizeof (cmd));
  SerialAVT.readBytes((char*) d, 4);
  if (d[0] != 0x93 && d[1] != 0x04) {
    return false;
  }
  firm[0] = d[2];
  firm[1] = d[3];
  return true;
}

bool AVT_852::model (byte *mod) {
  byte d[4];
  byte cmd[1] = {0xF0};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*) d, 4);
  if (d[0] != 0x93 && d[1] != 0x28) {
    return false;
  }
  mod[0] = d [2];
  mod[1] = d[3];
  return true;  
}

void AVT_852::flushReceive () {
  while(SerialAVT.available()) {
    SerialAVT.read();
  }
}

void AVT_852::flush () {
  SerialAVT.flush();
}

byte AVT_852::write (byte *data, int size) {
  byte x = SerialAVT.write(data, size);
  return x;
}

bool AVT_852::can () {
  byte cmd[2] = {0xE1, 0x99};
  SerialAVT.write(cmd, sizeof(cmd));
  return true;
}

bool AVT_852::vpw () {
  byte cmd[2] = {0xE1, 0x33};
  SerialAVT.write(cmd, sizeof(cmd));
  return true;
}

bool AVT_852::echoStatus () {
  byte d[3];
  byte cmd[2] = {0x51, 0x06};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  if (d[2] == '0') {
    return false;
  }
  else if (d[2] == '1') {
    return true;
  }
}

bool AVT_852::echoStatus (bool x) {
 bool check;
 byte cmd[3] = {0x52, 0x06, x};
 SerialAVT.write(cmd, sizeof(cmd));
 check = echoStatus();
 if (check != x) {
  return false; 
 }
 return true;
}

bool AVT_852::timeStamps () {
  byte d[3];
  byte cmd[2] = {0x51, 0x08};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  if (d[2] == '0') {
    return false;
  }
  else if (d[2] == '1') {
    return true;
  }
}

bool AVT_852::timeStamps (bool x) {
  bool check;
  byte cmd[3] = {0x52, 0x08, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = timeStamps ();
  if (check != x) {
    return false;
  }
  return true;
}

bool AVT_852::networkMessages () {
  byte d[3];
  byte cmd[2] = {0x51, 0x24};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  if (d[2] == '0') {
    return false;
  }
  else if (d[2] == '1') {
    return true;
  }
}

bool AVT_852::networkMessages (bool x) {
  bool check;
  byte cmd[3] = {0x52, 0x24, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = networkMessages ();
  if (check != x) {
    return false;
  }
  return true;
}

bool AVT_852::transmitAcks () {
  byte d[3];
  byte cmd[2] = {0x51, 0x40};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  if (d[2] == '0') {
    return false;
  }
  else if (d[2] == '1') {
    return true;
  }
}

bool AVT_852::transmitAcks (bool x) {
  bool check;
  byte cmd[3] = {0x52, 0x40, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = networkMessages ();
  if (check != x) {
    return false;
  }
  return true;
}

byte AVT_852::destinationFilter () {
  byte d[3];
  byte cmd[2] = {0x51, 0x5B};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  return d[2];
}

bool AVT_852::destinationFilter (byte x) {
  byte check;
  byte cmd[3] = {0x52, 0x5B, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = destinationFilter ();
  if (check != x) {
    return false;
  }
  return true;
}

byte AVT_852::sourceFilter () {
  byte d[3];
  byte cmd[2] = {0x51, 0x5C};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 3);
  return d[2];
}

bool AVT_852::sourceFilter (byte x) {
  byte check;
  byte cmd[3] = {0x52, 0x5C, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = sourceFilter ();
  if (check != x) {
    return false;
  }
  return true;
}

bool AVT_852::highSpeed () {
  byte d[2];
  byte cmd[1] = {0xC0};
  SerialAVT.write(cmd, sizeof(cmd));
  SerialAVT.readBytes((char*)d, 2);
  return d[2];
}

bool AVT_852::highSpeed (bool x) {
  bool check;
  byte cmd[2] = {0xC1, x};
  SerialAVT.write(cmd, sizeof(cmd));
  check = highSpeed ();
  if (check != x) {
    return false;
  }
  return true;
}

byte AVT_852::read (byte *buf) {
  byte header;
  byte receiveStatus;
  byte headerUpper;
  byte headerLower;
  int16_t bytesToRead;

  memset(buf, 0, sizeof(buf));

  _timeoutCheck = SerialAVT.readBytes((char*)header, 1);
  if (!_timeoutCheck) {
    if (_debug) {
      bluetooth.println("AVT Header Read Timeout ...");
    }
    return false;
  }
  headerUpper = header >> 4;
  headerLower = header & 0xF;
  bytesToRead = (int) headerLower - 1;

  if (_debug) {
    bluetooth.print("Header: ");
    bluetooth.println(header, HEX);
    bluetooth.println();
    bluetooth.print("UpperByte: ");
    bluetooth.println(headerUpper, HEX);
    bluetooth.print("LowerByte: ");
    bluetooth.println(headerLower, HEX);
    bluetooth.println();
  }
  switch (headerUpper)
  {
    case 0:
      _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);
      if (!_timeoutCheck) {
        if (_debug) {
          bluetooth.println("AVT Recieve Status Read Timeout ...");
        }
        return false;
      }
      if (receiveStatus != 0) {
        if (_debug) {
          bluetooth.println("AVT Receive Status ERROR ...");
        }
        return false;
      }
      _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead);
      if (!_timeoutCheck | _timeoutCheck != bytesToRead) {
        if (_debug) {
          bluetooth.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
        }
        return false;
      }
      if (_debug) {
        bluetooth.println("DEBUG:");
        for (int8_t i = 0; i < bytesToRead; i++) {
          bluetooth.print(buf[i], HEX);
          bluetooth.print(" ");
        }
        bluetooth.println();
      }
      break;
    case 1:
      switch (headerLower)
      {
        case 1:
          _timeoutCheck = SerialAVT.readBytes((char*)bytesToRead, 1);
          if (!_timeoutCheck) {
            if (_debug) {
              bluetooth.println("AVT Header Read Timeout ...");
            }
            return false;
          }
          bytesToRead = (int)bytesToRead - 1;
          _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);
          if (!_timeoutCheck) {
            if (_debug) {
              bluetooth.println("AVT Receive Status Read Timeout ...");
            }
            return false;
          }
          if (receiveStatus != 0) {
            if (_debug) {
              bluetooth.println("AVT Receive Status ERROR ...");
            }
            return false;
          }
          _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead);
          if (!_timeoutCheck | _timeoutCheck != bytesToRead) {
            if (_debug) {
              bluetooth.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
            }
            return false;
          }
          if (_debug) {
            bluetooth.println("DEBUG:");
            for (int8_t i = 0; i < bytesToRead; i++) {
              bluetooth.print(buf[i], HEX);
              bluetooth.print(" ");
            }
            bluetooth.println();
          }
          break;
        case 2:
          uint8_t c [2];
          _timeoutCheck = SerialAVT.readBytes((char*)c, 2);
          if (!_timeoutCheck | _timeoutCheck != 2) {
            if (_debug) {
              bluetooth.println("AVT Header Read Timeout ...");
            }
            return false;
          }
          bytesToRead = ((c[0] << 8) + c[1]) - 1;
          _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);
          if (!_timeoutCheck) {
            if (_debug) {
              bluetooth.println("AVT Receive Status Read Timeout ...");
            }
            return false;
          }
          if (receiveStatus != 0) {
            if (_debug) {
              bluetooth.println("AVT Receive Status ERROR ...");
            }
            return false;
          }
          _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead);
          if (!_timeoutCheck | _timeoutCheck != bytesToRead) {
            if (_debug) {
              bluetooth.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
            }
            return false;
          }
          if (_debug) {
            bluetooth.println("DEBUG:");
            for (int8_t i = 0; i < bytesToRead; i++) {
              bluetooth.print(buf[i], HEX);
              bluetooth.print(" ");
            }
            bluetooth.println();
          }
          break;
      }
      break;
  }
  return _timeoutCheck;
}

