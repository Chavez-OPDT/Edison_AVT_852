/*
 * Edison AVT 852
 * 
 * This is the base code of the OPDT Edison. It is designed to be used as a Scan Tool, Tuning Tool, and Diagnostic Tool.
 * It is written to be used with the Intel Edison Board and its USB host, WiFi, and BlueTooth Capibilities.
 * 
 * This program was writtin by and for Omnipotent Performance Diesel, LLC.
 * 
 * Author: Joshua Chavez
 * Start Date: 1/19/2017
 * E-Mail: josh@opdieseltuning.com
 */

#include <AVT_852.h>


AVT_852 avt;

void setup() {
  avt.begin(115200);

}

void loop() {


}
