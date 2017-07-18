#include <iostream>
#include <type_traits>
#include <exception>
#include <SQLiteCpp/Exception.h> 

template <typename Ret, 
    typename = typename std::enable_if<!std::is_void<Ret>::value>::type, typename ...Args>
Ret try_catch_decorator(Ret (*func)(Args ...args), Args ...args)
{
    try {
        Ret ret = func(args...);
        std::cout << "exec ok" << std::endl;
        return ret;
    } catch (const SQLite::Exception &e) {
        std::cout << "SQLite::Exception: " << e.what() << std::endl;
        std::cout << "ErrorCode: " << e.getErrorCode() << std::endl;
        std::cout << "ExtendedErrorCode: " << e.getExtendedErrorCode() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "std::exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exception" << std::endl;
    }
    return Ret();
}

template <typename ...Args>
void try_catch_decorator(void (*func)(Args ...args), Args ...args)
{
    try {
        func(args...);
        std::cout << "exec ok" << std::endl;
    } catch (const SQLite::Exception &e) {
        std::cout << "SQLite::Exception: " << e.what() << std::endl;
        std::cout << "ErrorCode: " << e.getErrorCode() << std::endl;
        std::cout << "ExtendedErrorCode: " << e.getExtendedErrorCode() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "std::exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exception" << std::endl;
    }
}

