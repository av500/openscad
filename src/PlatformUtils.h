#ifndef PLATFORMUTILS_H_
#define PLATFORMUTILS_H_

#include <string>
#include <vector>
#include <fstream>

namespace PlatformUtils {
	std::string documentsPath();
	std::string libraryPath();
	bool createLibraryPath();
	std::string backupPath();
	bool createBackupPath();
	void resetArgvToUtf8( int argc, char ** &argv, std::vector<std::string> &argstorage );
	FILE *fopen( const char *utf8path, const char *mode );
	std::string formatDouble( const double &x );
	std::string getenv( const char * varname );
	int stat(const char *utf8path, void *buf);
	int system(const char *utf8path);
	bool runningUnderWine();
	const char * pathsep();
	std::string info();
	int getpid();
}


// Define __PLATFORM_WIN__ for Windows(TM) builds
#if defined (__MINGW32__) || defined (__MINGW64__)
#define __PLATFORM_MINGW__
#endif
#if defined (__PLATFORM_MINGW__) || defined (_MSC_VER)
#define __PLATFORM_WIN__
#endif // MINGW32 || MINGW64


// POSIX stat() (requires altered struct_stat)
#if defined (__PLATFORM_WIN__)
namespace PlatformUtils { typedef struct _stat struct_stat; }
#else
namespace PlatformUtils { typedef struct stat struct_stat; }
#endif // __PLATFORM_WIN__


// integer types
#ifdef __PLATFORM_WIN__
typedef __int64 int64_t;
#else
#include <stdint.h>
#endif


// snprintf
#ifdef _MSC_VER
#define snprintf _snprintf
#endif


// ifstream/ofstream for MingW: see ../doc/windows_issues.txt
#ifdef __PLATFORM_MINGW__
#include "../patches/mingstream"
namespace PlatformUtils {
  typedef omingstream ofstream;
  typedef imingstream ifstream;
};
#else
namespace PlatformUtils {
  typedef std::ofstream ofstream;
  typedef std::ifstream ifstream;
};
#endif // Mingw ifstream/ofstream



#endif // PLATFORMUTILS_H_
