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
	std::string info();
	void resetArgvToUtf8( int argc, char ** &argv, std::vector<std::string> &argstorage );
	FILE *fopen( const char *utf8path, const char *mode );
	std::string formatDouble( const double &x );
	int stat(const char *utf8path, void *buf);
	int getpid();
}


// Detect various compilers indicating a Windows target and set __PLATFORM_WIN__
#if defined (__MINGW32__) || defined (__MINGW64__)
#define __PLATFORM_MINGW__
#endif
#if defined (__PLATFORM_MINGW__) || defined (_MSC_VER)
#define __PLATFORM_WIN__
#endif // MINGW32 || MINGW64


// portable version of POSIX stat() requires custom struct_stat
#if defined (__PLATFORM_WIN__)
namespace PlatformUtils { typedef struct _stat struct_stat; }
#else
namespace PlatformUtils { typedef struct stat struct_stat; }
#endif // __PLATFORM_WIN__


// portable snprintf
#ifdef _MSC_VER
#define snprintf _snprintf
#endif


// portable version of ifstream/ofstream
// MingW ifstream/ofstream: see ../doc/windows_issues.txt & ../patches/minsgream
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
