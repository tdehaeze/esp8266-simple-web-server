#ifndef HTMLFUNCTIONS_H_INCLUDED
#define HTMLFUNCTIONS_H_INCLUDED

#include <WString.h>

String getMacAddress(void);
String getDeviceName(void);
String getConnectionState(void);
void urlPostConnectionForm(void);
void urlGetImage(void);
void urlGetDeviceName(void);
void urlGetConnectionInfo(void);
void urlGetConnectionForm(void);
void urlGetConnectionState(void);
void urlGetNetworks(void);
void urlGetPinValue(void);

#endif /* HTMLFUNCTIONS_H_INCLUDED */
