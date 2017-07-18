
include "enums.thrift"

service DemoService {
    enums.ErrorType query(1: string req),
}
