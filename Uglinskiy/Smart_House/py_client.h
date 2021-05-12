#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include "Python.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#ifdef WIN32
int setenv(const char* name, const char* value, int overwrite);
#endif

#include <iostream>

int sensor_insert(const char* name, long value);

int jalousie_select(const char* name);

int lamp_select(const char* name);

int heater_select(const char* name);

int humidifier_select(const char* name);


