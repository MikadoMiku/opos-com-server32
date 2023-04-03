#include "DeviceManager.h"
#include <memory>
#include <thread>

// If you start trying to develop this project you need to look over additional include directories
// Under properties->C/C++->General->Additional includes

// You need CCO_s from monroecs - OPOS_CCOs_1.14.001
// Also need to yarn node_addon_api and include the path to the extra include directories where napi.h is located

// To use CCO_s you need ocx or dll files. First use the #import directive to generate a tlh file
// Then comment out the #import and #include the generated tlh file from the projects x64 directory

// Napi.h requires node_api.h which is usually located where your node version are kept
// Example path of node_api.h: C:\Users\power\AppData\Local\node-gyp\Cache\16.14.2\include\node
// Add the path to the projects extra include directories

// Also need node_addon_api from node_modules

// Node api also needs the library called node.lib which needs to be linked under properties->Linker->Input->Additional Dependencies
// The path for this lib for me was: C:\Users\power\AppData\Local\node-gyp\Cache\16.14.2\x64\node.lib (make sure to add the file with its extension not the directory)

// Example repo of a Scale and Scanner: https://github.com/datalogic/OPOSSamples
// Another example: https://github.com/microsoft/Windows-universal-samples/blob/main/Samples/BarcodeScanner/cpp/Scenario1_BasicFunctionality.xaml.cpp

int main()
{
    std::cout << "HELLO!" << std::endl;
    DeviceManager deviceManager;
    std::thread device_manager_thread(&DeviceManager::Start, &deviceManager);
    DWORD threadId = GetThreadId(device_manager_thread.native_handle());
    device_manager_thread.detach();

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "startScanner") {
            PostThreadMessage(threadId, 1025, 0, 0);
        }
        else if (input == "stopScanner") {
            PostThreadMessage(threadId, 1026, 0, 0);
        }

    }

    return 0;
}
