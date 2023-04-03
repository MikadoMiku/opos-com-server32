#pragma once

#include <windows.h>
#include <processthreadsapi.h>

#include <string>
#include <vector>
#include <iostream>

// Only for development and debugging. I imported the ocx file and compiled the code. 
// Compiling the code generated the tlh and tli files in the projects Debug folder.
// #import "C:\\OposCCOs-1_14_001\\CommonCO\\OPOSScanner.ocx"
#include "x64/Debug/oposscanner.tlh"

// This import statement informs the IDE of the COM interface and everything in the
// namespace OposScanner_CCO, but is not required for compilation.
// #import "libid:ccb90180-b81e-11d2-ab74-0040054c3719"
// #import "C:\\OposCCOs-1_14_001\\CommonCO\\Opos_Constants.dll"
#include "x64/Debug/opos_constants.tlh"

#define USBCOM_SCANNER_ANY           "RS232Imager"
#define USBOEM_SCANNER_HANDHELD      "USBHHScanner"
#define USBOEM_SCANNER_FIXED_RETAIL  "USBScanner"
#define RS232_SCANNER_ANY            "RS232Scanner"
#define RS232SC_SCANNER_FIXED_RETAIL "SCRS232Scanner"
