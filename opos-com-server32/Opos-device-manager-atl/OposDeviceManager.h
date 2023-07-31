// OposDeviceManager.h : Declaration of the COposDeviceManager

#pragma once
#include "resource.h"       // main symbols
#include <vector>
#include <map>
#include <string>

#include "Oposdevicemanageratl_i.h"
#include "_IOposDeviceManagerEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// COposDeviceManager

class ATL_NO_VTABLE COposDeviceManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COposDeviceManager, &CLSID_OposDeviceManager>,
	public IConnectionPointContainerImpl<COposDeviceManager>,
	public CProxy_IOposDeviceManagerEvents<COposDeviceManager>,
	public IConnectionPointImpl<COposDeviceManager, &__uuidof(IMyDeviceManagerEvents)>,
	public IDispatchImpl<IOposDeviceManager, &IID_IOposDeviceManager, &LIBID_OposdevicemanageratlLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	COposDeviceManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)

DECLARE_NOT_AGGREGATABLE(COposDeviceManager)

BEGIN_COM_MAP(COposDeviceManager)
	COM_INTERFACE_ENTRY(IOposDeviceManager)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(COposDeviceManager)
	CONNECTION_POINT_ENTRY(__uuidof(_IOposDeviceManagerEvents))
	CONNECTION_POINT_ENTRY(__uuidof(IMyDeviceManagerEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		if (FAILED(hr))
		{
			return hr;
		}
		return S_OK;
	}

	void FinalRelease()
	{
		for (auto& device : devices_)
		{
			device.second.device->Release();
			device.second.connectionPoint->Unadvise(device.second.cookie);
		}
		devices_.clear();

		CoUninitialize();
	}

	// Same methods as declared in the idl file
	STDMETHOD(StartScanner)(BSTR commandId);
	STDMETHOD(StopScanner)(BSTR commandId);
	STDMETHOD(EnableDataEvent)(BSTR deviceId, BSTR commandId);
	STDMETHOD(DisableDataEvent)(BSTR deviceId, BSTR commandId);
	HRESULT Fire_OnCommandCompleted(BSTR commandId);
public:

private:
	CComDynamicUnkArray m_vecMyDeviceManagerEvents;
	struct DeviceInfo {
		IUnknown* device;
		IDispatch* sink;
		IConnectionPoint* connectionPoint;
		DWORD cookie;
	};

	using deviceInfoPair = std::pair<std::string, DeviceInfo>;
	std::vector<deviceInfoPair> devices_;

};

OBJECT_ENTRY_AUTO(__uuidof(OposDeviceManager), COposDeviceManager)
