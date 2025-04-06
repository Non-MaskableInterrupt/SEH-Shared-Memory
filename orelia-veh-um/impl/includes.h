#include <chrono>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <vector>
#include <winternl.h>
#include <cstdint>
#include <DbgHelp.h>
#include <thread>
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "ntdll.lib")

#include <dependencies/skcrypt/skcrypter.h>
#include <impl/log/log.hxx>
#include <impl/ia32/ia32.h>

#include <dependencies/request/request.hxx>
#include <workspace/driver/driver.hxx>
driver::c_driver* g_driver = new driver::c_driver;

#include <workspace/exception/exception.hxx>