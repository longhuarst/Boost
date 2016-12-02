//tprebuild.cpp
#define BOOST_DATE_TIME_SOURCE	//thread库需要使用date_time库
#define BOOST_THREAD_NO_LIB
#define BOOST_HAS_WINTHREADS
#define BOOST_THREAD_BUILD_DLL
#include <boost/thread.hpp>

#ifdef _MSC_VER	//windows 系统的线程
extern "C" void tss_cleanup_implemented(void) {} //一个必须的函数
#include <libs/thread/src/win32/thread.cpp>
#include <libs/thread/src/win32/tss_dll.cpp>
#include <libs/thread/src/win32/tss_pe.cpp>
#else	//unix 系统相关的实现文件
#include <libs/thread/src/pthread/thread.cpp>
#include <libs/thread/src/pthread/once.cpp>
#endif // _MSC_VER

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501 //避免VC下的编译警告
#endif
#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LIB
