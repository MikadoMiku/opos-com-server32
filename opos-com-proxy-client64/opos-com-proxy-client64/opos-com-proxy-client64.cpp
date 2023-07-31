#include "Oposdevicemanageratl_i.h" // Include the header file generated by your ATL project
#include "Oposdevicemanageratl_i.c"
#include <iostream>
#include <Windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <napi.h>

std::queue<std::string> commandQueue;
std::mutex commandQueueMutex;

enum ThreadMessage {
	EnableDataEvent = WM_USER + 1,
	DisableDataEvent = WM_USER +2
};


class CMyDeviceManagerEvents : public IMyDeviceManagerEvents
{
public:
	STDMETHODIMP OnDataEvent(BSTR data)
	{
		std::wcout << std::endl;
		std::wstring wstrData(data);
		std::wcout << L"Data event received: " << wstrData << std::endl;
		return S_OK;
	}

	STDMETHODIMP OnErrorEvent(BSTR errorMessage)
	{
		std::wstring wstrErrorMessage(errorMessage);
		std::wcerr << L"Error event received: " << wstrErrorMessage << std::endl;
		return S_OK;
	}

	STDMETHODIMP_(ULONG) AddRef() override { return 1; }
	STDMETHODIMP_(ULONG) Release() override { return 1; }

	STDMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override
	{
		if (iid == IID_IUnknown || iid == IID_IMyDeviceManagerEvents)
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
	}
};

void comThreadFunction() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr)) {
		std::cerr << "Failed to initialize COM library." << std::endl;
		return;
	}

	CComPtr<IOposDeviceManager> spDeviceManager;
	hr = spDeviceManager.CoCreateInstance(__uuidof(OposDeviceManager));
	// ...

	// Create an instance of your event handler class
	CMyDeviceManagerEvents eventHandler;

	// Query the COM object for the IConnectionPointContainer interface
	CComPtr<IConnectionPointContainer> spCPC;
	hr = spDeviceManager->QueryInterface(IID_IConnectionPointContainer, (void**)&spCPC);

	// Find the connection point for the IMyDeviceManagerEvents interface
	CComPtr<IConnectionPoint> spCP;
	hr = spCPC->FindConnectionPoint(IID_IMyDeviceManagerEvents, &spCP);

	// Advise the connection point with the event handler object
	DWORD dwCookie;
	hr = spCP->Advise(&eventHandler, &dwCookie);


	// Call a method of your COM server, e.g., StartScanner
	hr = spDeviceManager->StartScanner();

	// Run a loop to handle COM events and user commands
	MSG msg;
	while (true) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		std::string command;
		{
			std::lock_guard<std::mutex> lock(commandQueueMutex);
			if (!commandQueue.empty()) {
				command = commandQueue.front();
				commandQueue.pop();
			}
		}

		if (!command.empty()) {
			if (command == "q") {
				hr = spDeviceManager->StopScanner();
				break;
			}
			else if (command == "enableDataEvents") {
				BSTR bstr = SysAllocString(L"device");
				hr = spDeviceManager->EnableDataEvent(bstr);
				SysFreeString(bstr);
			}
			else if (command == "disableDataEvents") {
				BSTR bstr = SysAllocString(L"device");
				hr = spDeviceManager->DisableDataEvent(bstr);
				SysFreeString(bstr);
			}

			// Process the command and call the appropriate methods on the COM server
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	hr = spCP->Unadvise(dwCookie);

	CoUninitialize();
}

void inputThreadFunction() {
	std::string input;
	while (true) {
		std::cout << "Enter command (q to quit): ";
		std::getline(std::cin, input);

		if (input.empty()) {
			continue;
		}

		std::lock_guard<std::mutex> lock(commandQueueMutex);
		commandQueue.push(input);

		if (input == "q") {
			break;
		}
	}
}

int main() {
	std::thread comThread(comThreadFunction);
	std::thread inputThread(inputThreadFunction);

	comThread.join();
	inputThread.join();

	std::cout << "Done." << std::endl;
	return 0;
}

Napi::String Method(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	return Napi::String::New(env, "world");
}

Napi::String StartMain(const Napi::CallbackInfo& info)
{
	main();
	Napi::Env env = info.Env();
	return Napi::String::New(env, "main started?");
}

Napi::Boolean DoCommand(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	// Check if there is at least one argument and if the argument is a string
	if (info.Length() < 1 || !info[0].IsString()) {
		Napi::TypeError::New(env, "Expected a string as the first argument").ThrowAsJavaScriptException();
		return Napi::Boolean::New(env, false);
	}

	// Convert the JavaScript string to a std::string
	std::string command = info[0].As<Napi::String>().Utf8Value();

	std::lock_guard<std::mutex> lock(commandQueueMutex);
	commandQueue.push(command);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "hello"),
		Napi::Function::New(env, Method));
	exports.Set(Napi::String::New(env, "startMain"),
		Napi::Function::New(env, StartMain));
	return exports;
}

NODE_API_MODULE(hello, Init)
