#ifndef X_MONITOR_MANAGER_INC
#define X_MONITOR_MANAGER_INC

class XMonitorManagerImpl;  

class XMonitorManager {
public:
    XMonitorManager();

private:
    XMonitorManagerImpl *impl;
};

#endif
