//tprebuild.cpp
#define BOOST_DATE_TIME_SOURCE	//thread����Ҫʹ��date_time��
#define BOOST_THREAD_NO_LIB
#define BOOST_HAS_WINTHREADS
#define BOOST_THREAD_BUILD_DLL
#include <boost/thread.hpp>

#ifdef _MSC_VER	//windows ϵͳ���߳�
extern "C" void tss_cleanup_implemented(void) {} //һ������ĺ���
#include <libs/thread/src/win32/thread.cpp>
#include <libs/thread/src/win32/tss_dll.cpp>
#include <libs/thread/src/win32/tss_pe.cpp>
#else	//unix ϵͳ��ص�ʵ���ļ�
#include <libs/thread/src/pthread/thread.cpp>
#include <libs/thread/src/pthread/once.cpp>
#endif // _MSC_VER

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501 //����VC�µı��뾯��
#endif
#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LIB
