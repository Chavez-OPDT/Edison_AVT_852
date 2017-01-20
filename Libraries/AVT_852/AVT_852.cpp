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

/*
  This function starts the connection to the AVT. Here we need to connect to the AVT which is connected to
  the large USB port on the Edison Arduino breakout board. This can also be achieved with a USB-OTG cable on the 
  mini-breakout board. We are going to have to connect to it through the Linux backend. Make sure that the switch on the
  Arduino Breakout board is switched to the right (towards the large USB port)
*/
void AVT_852::begin (int baud) {
  SerialAVT.init_tty("/dev/ttyUSB0");
  SerialAVT.begin(baud);
}

/*
  This function is used to request the firmware from the AVT.
*/
bool AVT_852::firmware (byte *firm) {
  byte d[4];                              // Here is where we store the response we get from the AVT.
  byte cmd[2] = {0xB1, 0x01};             // This is the command that we send to the AVT to request the FW.
  SerialAVT.write (cmd, sizeof (cmd));    // Send the command
  SerialAVT.readBytes((char*) d, 4);      // Now we read the response.
  if (d[0] != 0x93 && d[1] != 0x04) {     // Lets double check to make sure that we received a correct response.
    return false;                         // If the response was incorrect, return false.
  }
  firm[0] = d[2];                         // Now that we have verified, place the correct data in the buffer that was supplied.
  firm[1] = d[3];
  return true;                            // Return that everything completed successfully/
}

/*
  This function is used to request the Model # from the AVT.
*/

bool AVT_852::model (byte *mod) {
  byte d[4];                              // Here is where we store the response we get from the AVT.
  byte cmd[1] = {0xF0};                   // This is the model # request.
  SerialAVT.write(cmd, sizeof(cmd));      // Send the command
  SerialAVT.readBytes((char*) d, 4);      // Read the response
  if (d[0] != 0x93 && d[1] != 0x28) {     // Double check to make sure that we received a correct response.
    return false;                         // If the response was incorrect, return false.
  }
  mod[0] = d [2];                         // Data is verified, Store it in the supplied buffer.
  mod[1] = d[3];
  return true;                            // Return that everything completed successfully
}

/*
  This function we use to clear any data that may be waiting in the buffer that we dont want.
  We use this because of the change with the flush() function.
*/
void AVT_852::flushReceive () {
  while(SerialAVT.available()) {          // If there is data available keep reading it and throw it away.
    SerialAVT.read();
  }
}

/*
  Here we can use the traditional flush command. This will wait for all data to be sent before continuing.
*/
void AVT_852::flush () {
  SerialAVT.flush();
}

/*
  Here we allow use of the write command. We use the form that has a buffer input with the number of bytes to send.
*/

byte AVT_852::write (byte *data, int size) {
  byte x = SerialAVT.write(data, size);
  return x;
}

/*
  This function is used to enter CAN mode.

  A verification that the mode has been entered needs to be added.
*/

bool AVT_852::can () {
  byte cmd[2] = {0xE1, 0x99};
  SerialAVT.write(cmd, sizeof(cmd));
  return true;
}

/*
  This function is used to enter VPW mode.

  A verification that the mode has been entered needs to be added.
*/

bool AVT_852::vpw () {
  byte cmd[2] = {0xE1, 0x33};
  SerialAVT.write(cmd, sizeof(cmd));
  return true;
}

/*

*/

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

/*
  This is the read function.

  This will probably change many times. It's essentially for reading data received from the AVT that it receives.

  I'm not sure if the final function name will be "read" or something else.

  This is a note that it might change, but functionality should remain close to the same.
*/

byte AVT_852::read (byte *buf) {
  byte header;                     // This is where we will store the header byte of the data that we receive.
  byte receiveStatus;              // We store the receive status byte here
  byte headerUpper;                // We will split the header into an upper and lower byte and store them here.
  byte headerLower;
  int16_t bytesToRead;             // This is where we will store the value of the bytes to read.

  memset(buf, 0, sizeof(buf));     // We clear the buffer to be sure it is empty. To prepare it or to clear any data that may be in it.

  _timeoutCheck = SerialAVT.readBytes((char*)header, 1); //Here we use the ReadBytes function to read the header. We also added a check for a time out to make sure that we atleast receive some data
  if (!_timeoutCheck) {            // If we timed out and received no data. We will print to the debug if its enabled and return a false (0) to show the read failed.
    if (_debug) {
      debug.println("AVT Header Read Timeout ...");
    }
    return false;
  }
  headerUpper = header >> 4;      // If we received the header, now we split it up into two parts. This is the High Byte of the header. We get this by bit shifting.
  headerLower = header & 0xF;     // Here we get the lower byte of the header.
  bytesToRead = (int) headerLower - 1;    // If the upper header contains a 0, the lower will contain the number of bytes to read. Just to prepare we will load it now. We subtract one because we will be loading the receive status byte seperately and it is only used for integrity.

  if (_debug) {                   // Here, if debug is activated, we will print what is contained in the header.
    debug.print("Header: ");
    debug.println(header, HEX);
    debug.println();
    debug.print("UpperByte: ");
    debug.println(headerUpper, HEX);
    debug.print("LowerByte: ");
    debug.println(headerLower, HEX);
    debug.println();
  }
  switch (headerUpper)            // Here we will analyze the upper header to see what kind of message that we received.
  {
    case 0:                       // If we received a 0 it means that we got a standard message that can be up to 13 Bytes. 
      _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);   // Being that we received a message, the next byte we are expecting a 0x00 to confirm that there were no ERRORs
      if (!_timeoutCheck) {                                           // Here we check for and handle a possible timeout. 
        if (_debug) {
          debug.println("AVT Recieve Status Read Timeout ...");
        }
        return false;
      }
      if (receiveStatus != 0) {                                       // Here we handle if the receiveStatus is not 0x00 and we have an ERROR.
        if (_debug) {
          debug.println("AVT Receive Status ERROR ...");
        }
        return false;
      }
      _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead);   // If all was well, we read the rest of the packet that contains all the received data.
      if (!_timeoutCheck | _timeoutCheck != bytesToRead) {            // Check for a timeout and handle it. Here we will also check to see if the # of bytes that we received is equal to the number that we were expecting.
        if (_debug) {
          debug.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
        }
        return false;
      }
      if (_debug) {                                   // Here, if debug is enabled, we will print out the message that we received to the debug.
        debug.println("DEBUG:");
        for (int8_t i = 0; i < bytesToRead; i++) {
          debug.print(buf[i], HEX);
          debug.print(" ");
        }
        debug.println();
      }
      break;
    case 1:                       // If we received a '1' that means that we received a packet of the second or third header type. An '11' contains one byte for length. Max of 0xFF. A '12' contains two bytes for length. With a max of 0xFFFF
      switch (headerLower)
      {
        case 1:                     // So if the lower also contains a 1, we have received an 11 header packet. 
          _timeoutCheck = SerialAVT.readBytes((char*)bytesToRead, 1); // Timeout Check handle and read the byte that contains the # of bytes to read.
          if (!_timeoutCheck) {
            if (_debug) {
              debug.println("AVT Header Read Timeout ...");
            }
            return false;
          }
          bytesToRead = (int)bytesToRead - 1;                             // Now we adjust the bytes to read by subtracting the receive status byte
          _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);   // Now we get the receive status byte and check for and handle a timeout.
          if (!_timeoutCheck) {
            if (_debug) {
              debug.println("AVT Receive Status Read Timeout ...");
            }
            return false;
          }
          if (receiveStatus != 0) {             // Check the value of the receive status byte.
            if (_debug) {
              debug.println("AVT Receive Status ERROR ...");
            }
            return false;
          }
          _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead);     // We now receive the data that we have been waiting for.
          if (!_timeoutCheck | _timeoutCheck != bytesToRead) {              // Check timeout and bytes read.
            if (_debug) {
              debug.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
            }
            return false;
          }
          if (_debug) {                       // If debug is enabled, print the message to the debug port.
            debug.println("DEBUG:");
            for (int8_t i = 0; i < bytesToRead; i++) {
              debug.print(buf[i], HEX);
              debug.print(" ");
            }
            debug.println();
          }
          break;
        case 2:                         // If a 2 was received then that means a '12' was received, we will have 2 bytes containing the number of bytes to read.
          uint8_t c [2];
          _timeoutCheck = SerialAVT.readBytes((char*)c, 2);   // Now we read the two bytes. Store both in a buffer so we can combine them into a single int. Is this the correct method? IDK, but we will have to test.
          if (!_timeoutCheck | _timeoutCheck != 2) {
            if (_debug) {
              debug.println("AVT Header Read Timeout ...");
            }
            return false;
          }
          bytesToRead = ((c[0] << 8) + c[1]) - 1;             // now we combine byte one and 2 and subtract the receiveStatus byte.
          _timeoutCheck = SerialAVT.readBytes((char*)receiveStatus, 1);   // Now get the receiveStatus byte
          if (!_timeoutCheck) {                                           // Timeout Check.
            if (_debug) {
              debug.println("AVT Receive Status Read Timeout ...");
            }
            return false;
          }
          if (receiveStatus != 0) {                           // Check the receiveStatus byte.
            if (_debug) {
              debug.println("AVT Receive Status ERROR ...");
            }
            return false;
          }
          _timeoutCheck = SerialAVT.readBytes((char*)buf, bytesToRead); // If the receive status byte check out! Lets read this data and store it in the supplied buffer.
          if (!_timeoutCheck | _timeoutCheck != bytesToRead) {
            if (_debug) {
              debug.println("AVT Did Not Receive # of Bytes Expected, Timeout ...");
            }
            return false;
          }
          if (_debug) {
            debug.println("DEBUG:");                          // If the debug is turned on, then print the entire message to the debug port.
            for (int8_t i = 0; i < bytesToRead; i++) {
              debug.print(buf[i], HEX);
              debug.print(" ");
            }
            debug.println();
          }
          break;
      }
      break;
  }
  return _timeoutCheck;                             // If everything went well, then return the number of bytes that were received.
}

