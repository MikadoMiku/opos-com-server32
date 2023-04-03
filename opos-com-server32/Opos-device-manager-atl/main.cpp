// Opos-device-manager-atl.cpp : Implementation of WinMain


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "Oposdevicemanageratl_i.h"
#include "xdlldata.h"


using namespace ATL;


class COposdevicemanageratlModule : public ATL::CAtlExeModuleT< COposdevicemanageratlModule >
{
public :
	DECLARE_LIBID(LIBID_OposdevicemanageratlLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OPOSDEVICEMANAGERATL, "{fc266689-1baa-4157-a847-23daab7348ac}")
};

COposdevicemanageratlModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

