#include "DeviceManager.h"
#include "Essential.h"
#include "ScannerSink.h"

#define WM_STARTSCANNER (WM_USER + 1) // 1024 + 1
#define WM_STOPSCANNER (WM_USER + 2) // 1024 + 2

using namespace std;

DeviceManager::DeviceManager() {
}

DeviceManager::~DeviceManager() {
	for (auto& device : devices_)
	{
		device.second.device->Release();
		device.second.connectionPoint->Unadvise(device.second.cookie);
	}
	devices_.clear();

	CoUninitialize();
}

void DeviceManager::Start() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		throw runtime_error("Failed to initialize COM.");
	}
	std::cout << "Device manager started..." << std::endl;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Process messages
		if (msg.message == WM_STARTSCANNER) {
			// OnMyMessage(msg.wParam, msg.lParam);
			this->StartScanner();
		}
		else if (msg.message == WM_STOPSCANNER) {
			// OnMyMessage(msg.wParam, msg.lParam);
			this->StopScanner();
		}
	}
}

void DeviceManager::StartScanner() {
	HRESULT hr;
	//std::vector<std::string> keys =
	//{
	//    USBCOM_SCANNER_ANY,
	//    USBOEM_SCANNER_HANDHELD,
	//    USBOEM_SCANNER_FIXED_RETAIL,
	//    RS232_SCANNER_ANY,
	//    RS232SC_SCANNER_FIXED_RETAIL
	//};

	OposScanner_CCO::IOPOSScannerPtr scanner = nullptr;
	hr = scanner.CreateInstance("OPOS.Scanner");

	// Attempt to open and claim a scanner (first come, first serve).
	//size_t index, count = keys.size();
	//for (index = 0; index < count; ++index)
	//{
	//    scanner->Open(keys[index].c_str());
	//    scanner->ClaimDevice(1000);
	//    if (scanner->Claimed)
	//        break;

	//    scanner->Close();
	//}

	if (FAILED(hr))
	{
		throw runtime_error("Failed to create scanner instance.");
	}

	hr = scanner->Open(L"USBScanner");
	if (FAILED(hr))
	{
		throw runtime_error("Failed to open scanner.");
	}

	hr = scanner->ClaimDevice(1000);
	if (FAILED(hr))
	{
		scanner->Close();
		throw runtime_error("Failed to claim scanner.");
	}


	if (scanner->Claimed) {
		std::cout << "Connected to: USBScanner" << std::endl;

		// Enable the scanner and decoding events.
		scanner->DeviceEnabled = true;
		scanner->DataEventEnabled = true;
		scanner->DecodeData = true;

		// Determine whether scanner is connectable
		IConnectionPointContainer* cpc;
		bool isConnectable = (scanner->QueryInterface(IID_IConnectionPointContainer, (void**)&cpc) == S_OK);

		if (isConnectable) {
			// Determine whether _IOPOSScannerEvents connection point is supported.
			IConnectionPoint* cp;
			bool haveConnectionPoint = (cpc->FindConnectionPoint(__uuidof(OposScanner_CCO::_IOPOSScannerEvents), &cp) == S_OK);
			cpc->Release();

			if (haveConnectionPoint) {
				ScannerSink* sink = new ScannerSink(*scanner, "USBScanner");

				// Connect cp with sink (subscribe to the sink).
				// cookie is a token representing the connection,
				// used later when deleting the connection.
				DWORD cookie;
				cp->Advise(sink, &cookie);

				sink->GoodBeep();
				std::cout << "Press \'Ctrl + C\' to quit." << std::endl;
				DeviceInfo deviceInfo = {
					scanner, sink, cp, cookie
				};
				devices_.push_back(deviceInfoPair("USBScanner", deviceInfo));
			}
		}
	}


	wcout << "Scanner started." << endl;
}

void DeviceManager::StopScanner() {
	OposScanner_CCO::IOPOSScannerPtr scannerSmartPtr = nullptr;

	std::string scannerName = "USBScanner";
	DeviceInfo scannerInfo;
	bool scannerFound = false;
	for (const auto& devicePair : devices_) {
		if (devicePair.first == scannerName) {
			// Found the scanner, access the DeviceInfo struct
			scannerInfo = devicePair.second;
			scannerFound = true;
			// Access the device, sink, connection point and cookie using scannerInfo.device, scannerInfo.sink, scannerInfo.connectionPoint, and scannerInfo.cookie respectively
			break;
		}
	}

	if (scannerFound)
	{
		// OposScanner_CCO::IOPOSScannerPtr* scanner = dynamic_cast<OposScanner_CCO::IOPOSScannerPtr*>(scannerInfo.device);

		HRESULT hr = scannerInfo.device->QueryInterface(__uuidof(OposScanner_CCO::IOPOSScanner), (void**)&scannerSmartPtr);
		if (FAILED(hr))
		{
			throw runtime_error("Failed to get IOPOSScanner interface pointer.");
		}

		// scannerSmartPtr = scanner->GetInterfacePtr();

		scannerSmartPtr->ReleaseDevice();
		scannerSmartPtr->Close();
		scannerInfo.connectionPoint->Unadvise(scannerInfo.cookie);

		// I think this is somehow release? Might be released when doing cp->Unadvise()
		// The example i looked at did not have a separate release for it so that may be the case
		//  getting access violation...
		//if (scannerInfo.sink != nullptr && scannerInfo.sink != NULL) {
		//	scannerInfo.sink->Release();
		//}


		devices_.erase(std::remove_if(devices_.begin(), devices_.end(), [&](const deviceInfoPair& devicePair) {
			return devicePair.first == scannerName;
			}), devices_.end());


		wcout << "Scanner stopped." << endl;
	}
	else
	{
		wcout << "No scanner to stop." << endl;
	}
}
