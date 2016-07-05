#ifndef HTMLFUNCTIONS_H_INCLUDED
#define HTMLFUNCTIONS_H_INCLUDED

#include <WString.h>

String getMacAddress(void);
String getDeviceName(void);
String getConnectionState(void);
void urlPostConnectionForm(void);
void urlGetDeviceName(void);
void urlGetConnectionInfo(void);
void urlGetConnectionForm(void);
void urlGetConnectionState(void);
void urlGetNetworks(void);

#endif /* HTMLFUNCTIONS_H_INCLUDED */
