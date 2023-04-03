#include "ScannerSink.h"
#pragma once

#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

class DeviceManager {
public:
    DeviceManager();
    void Start();
    void StartScanner();
    void StopScanner();
    ~DeviceManager();
private:
    struct DeviceInfo {
        IUnknown* device;
        IDispatch* sink;
        IConnectionPoint* connectionPoint;
        DWORD cookie;
    };
    using deviceInfoPair = std::pair<std::string, DeviceInfo>;
    std::vector<deviceInfoPair> devices_;
};

#endif