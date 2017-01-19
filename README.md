# Edison_AVT_852
Initial Release

This project was started in order to provide portable functionality for the Advanced Vehicle Technologies AVT-852 using an Intel Edison.

The AVT-852:
 - Multiple protocol interface.
 - Low cost. 
 - USB to host computer.
 - Fully capable interface with room to grow in functionality and capability.
 - Supported Protocols:
    - 2-wire high speed CAN,
    - Single Wire CAN
    - J1850 VPW
    - fully supports GM-LAN
    - K-line communications
    - LIN
    - 3 channels of analog to digital input

As you can see, due to the large supported features, the AVT-852 is a very well suited candidate to a well rounded communications device.
One of the very bennificial features to this vs. the ELM327 is the AVT's ability to enter 4x J-1850 VPW Mode and transmit and recieve large packets of data.

This includes a Library to communicate with the AVT-852. This library was designed around the Intel Edison, and in the future may be adapted
to other devices/shields that support USB-Host. 

Here is a breakdown of the functions of the Library and its basic usage.


##begin()
####Description:
  - Sets the data rate in bits per second (baud) for data transmission. Reccommended is 115200.

####Syntax:
  - AVT_852.begin(speed)
  
####Parameters:
  - speed: in bits per second (baud) - long
  
####Returns:
  - Nothing

##flush()
####Description:
  - Waits for the transmission of outgoing serial data to complete.

####Syntax:
  - AVT_852.flush()

####Parameters:
  - None

####Returns:
  - Nothing
  
##flushReceive()
####Description:
  - Removes any buffered incoming data.

####Syntax:
  - AVT_852.flushReceive()

####Parameters:
  - None

####Returns:
  - Nothing
  
##write()
####Description:
  - Writes binary data to the AVT.

####Syntax:
  - AVT_852.write(buffer, length)

####Parameters:
  - buffer: An array sent as a series of bytes
  - length: The length of the buffer.

####Returns:
  - byte
    - write() will return the nuber of bytes written, though reading that number is optional.
    
##read()
####Description:
  - This function is still under development. This is here to serve as a place-holder until it is complete.

####Syntax:
  - None

####Parameters:
  - None

####Returns:
  - Nothing
  
##firmware()
####Description:
  - This function sends the necessiary commands to the AVT to request the current firmware revision and stores the bytes in the supplied buffer.

####Syntax:
  - AVT_852.firmware(buffer)

####Parameters:
  - buffer: The buffer where the firmware bytes are stored

####Returns:
  - boolean:
    - firmware() will return True (1) if it was successful and False (0) if there was an ERROR.
  
##model()
####Description:
  - This function sends the necessary commands to the AVT to request the current firmware revision and store the bytes in the supplied bufer. 

####Syntax:
  - AVT_852.model(buffer)

####Parameters:
  - buffer: The buffer where the firmware bytes are stored

####Returns:
  - boolean:
    - model() will return True (1) if it was successful and False (0) if there was an ERROR.
    
##can()
####Description:
  - Sending this command will cause the AVT to enter CAN communications mode. (This is not fully implemented as of yet.)

####Syntax:
  - AVT_852.can()

####Parameters:
  - None

####Returns:
  - boolean
    - can() will return True (1) if it was successful and False (0) if there was an ERROR.
    
##vpw()
####Description:
  - Sending this command will cause the AVT to enter J-1850 VPW communications mode. 

####Syntax:
  - AVT_852.vpw()

####Parameters:
  - None

####Returns:
  - boolean
    - vpw() will return True (1) if it was successful and False (0) if there wasn an ERROR.
