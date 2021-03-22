#ifndef X_MONITOR_INFO_QUERY
#define X_MONITOR_INFO_QUERY

class XMonitorInfoQueryImpl; 

class XMonitorInfoQuery {
public:
  XMonitorInfoQuery(); 
  ~XMonitorInfoQuery(); 

  void print();

private:
  XMonitorInfoQueryImpl *impl_;
};

#endif
