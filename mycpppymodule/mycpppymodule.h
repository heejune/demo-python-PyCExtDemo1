// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MYCPPPYMODULE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MYCPPPYMODULE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MYCPPPYMODULE_EXPORTS
#define MYCPPPYMODULE_API __declspec(dllexport)
#else
#define MYCPPPYMODULE_API __declspec(dllimport)
#endif

// This class is exported from the mycpppymodule.dll
class MYCPPPYMODULE_API Cmycpppymodule {
public:
	Cmycpppymodule(void);
	// TODO: add your methods here.
};

extern MYCPPPYMODULE_API int nmycpppymodule;

MYCPPPYMODULE_API int fnmycpppymodule(void);
