
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FCTCLIENT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FCTCLIENT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FCTCLIENT_EXPORTS
#define FCTCLIENT_API __declspec(dllexport)
#else
#define FCTCLIENT_API __declspec(dllimport)
#endif

// This class is exported from the FCTClient.dll
class FCTCLIENT_API CFCTClient {
public:
	CFCTClient(void);
	// TODO: add your methods here.
};

extern FCTCLIENT_API int nFCTClient;

FCTCLIENT_API int fnFCTClient(void);
FCTCLIENT_API int connect2host();
FCTCLIENT_API int start(int num, char * buf);
FCTCLIENT_API int start(int num, char * buf,int camIndex);
FCTCLIENT_API int loadpatternfile(int code);
FCTCLIENT_API int check();
FCTCLIENT_API int getresult(int * result, int *pimg);
FCTCLIENT_API int selectimagesrc(int id);//cam--0 pic--1
FCTCLIENT_API int changeimage(int id);//cam--0 pic--1
FCTCLIENT_API int getimagesize(int *w,int *h);
