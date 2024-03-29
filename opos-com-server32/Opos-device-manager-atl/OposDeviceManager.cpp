// OposDeviceManager.cpp : Implementation of COposDeviceManager

#include "pch.h"
#include "FileLoggerr.h"

STDMETHODIMP COposDeviceManager::EnableDataEvent(BSTR deviceId, BSTR commandId) {
	for (auto& device : devices_)
	{
		if (device.first == "USBScanner") {
			ScannerSink* sink = static_cast<ScannerSink*>(device.second.sink);
			sink->EnableDataEvents();
			break;
		}
	}
	std::wstring ws(commandId);
	std::string strCommandId(ws.begin(), ws.end());
	Logger("OnCommandCompleted: " + strCommandId);
	Fire_OnCommandCompleted(commandId);
	return S_OK;
}

STDMETHODIMP COposDeviceManager::DisableDataEvent(BSTR deviceId, BSTR commandId) {
	for (auto& device : devices_)
	{
		if (device.first == "USBScanner") {
			ScannerSink* sink = static_cast<ScannerSink*>(device.second.sink);
			sink->DisableDataEvents();
			break;
		}
	}
	std::wstring ws(commandId);
	std::string strCommandId(ws.begin(), ws.end());
	Logger("OnCommandCompleted: " + strCommandId);
	Fire_OnCommandCompleted(commandId);
	return S_OK;
}

HRESULT COposDeviceManager::Fire_OnCommandCompleted(BSTR commandId)
{
	HRESULT hr = S_OK;
	CComPtr<IConnectionPointContainer> spCPC;
	hr = this->QueryInterface(IID_IConnectionPointContainer, (void**)&spCPC);
	if (SUCCEEDED(hr))
	{
		CComPtr<IConnectionPoint> spCP;
		hr = spCPC->FindConnectionPoint(__uuidof(IMyDeviceManagerEvents), &spCP);
		if (SUCCEEDED(hr))
		{
			CComPtr<IEnumConnections> spEnum;
			hr = spCP->EnumConnections(&spEnum);
			if (SUCCEEDED(hr))
			{
				CONNECTDATA cd = { 0 };
				while (spEnum->Next(1, &cd, NULL) == S_OK)
				{
					IMyDeviceManagerEvents* pEvent = reinterpret_cast<IMyDeviceManagerEvents*>(cd.pUnk);
					if (pEvent)
					{
						pEvent->OnCommandCompleted(commandId);
						cd.pUnk->Release();
					}
				}
			}
		}
	}
	return hr;
}


STDMETHODIMP COposDeviceManager::StartScanner(BSTR commandId) {
	Logger("Scanner started...");
    // The existing code from DeviceManager::StartScanner goes here
    // Replace `this->StartScanner()` with `StartScanner()`
    // Replace any references to the DeviceManager class with COposDeviceManager
	HRESULT hr;

	OposScanner_CCO::IOPOSScannerPtr scanner = nullptr;
	hr = scanner.CreateInstance("OPOS.Scanner");

	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to create scanner instance.");
	}

	hr = scanner->Open(L"USBScanner");
	if (FAILED(hr))
	{
		throw std::runtime_error("Failed to open scanner.");
	}

	hr = scanner->ClaimDevice(1000);
	if (FAILED(hr))
	{
		scanner->Close();
		throw std::runtime_error("Failed to claim scanner.");
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
				ScannerSink* sink = new ScannerSink(this, *scanner, "USBScanner");

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


	std::cout << "Scanner started." << std::endl;
	std::wstring ws(commandId);
	std::string strCommandId(ws.begin(), ws.end());
	Logger("OnCommandCompleted: " + strCommandId);
	Fire_OnCommandCompleted(commandId);
    return S_OK;
}

STDMETHODIMP COposDeviceManager::StopScanner(BSTR commandId) {
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
		HRESULT hr = scannerInfo.device->QueryInterface(__uuidof(OposScanner_CCO::IOPOSScanner), (void**)&scannerSmartPtr);
		if (FAILED(hr))
		{
			throw std::runtime_error("Failed to get IOPOSScanner interface pointer.");
		}

		scannerSmartPtr->ReleaseDevice();
		scannerSmartPtr->Close();
		scannerInfo.connectionPoint->Unadvise(scannerInfo.cookie);

		devices_.erase(std::remove_if(devices_.begin(), devices_.end(), [&](const deviceInfoPair& devicePair) {
			return devicePair.first == scannerName;
			}), devices_.end());


		std::cout << "Scanner stopped." << std::endl;
	}
	else
	{
		std::cout << "No scanner to stop." << std::endl;
	}
	std::wstring ws(commandId);
	std::string strCommandId(ws.begin(), ws.end());
	Logger("OnCommandCompleted: " + strCommandId);
	Fire_OnCommandCompleted(commandId);
    return S_OK;
}
