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
int setenv(const char* name, const char* value, int overwrite)
{
    int errcode = 0;
    if (!overwrite) {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if (errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
}
#endif

#include <iostream>


int jalousie_select(const char* name) {
    PyObject* pName, * pModule, * pFunc, * pValue, * pParameter, * pArgs;

    Py_Initialize();
    pName = PyUnicode_FromString("client_c");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
        std::cout << "bad >:(";
    //else throw;
    pFunc = PyObject_GetAttrString(pModule, "jalousie_select");
    pParameter = PyUnicode_FromString(name);
    pArgs = PyTuple_New(1);
    PyTuple_SET_ITEM(pArgs, 0, pParameter);
    pValue = PyObject_CallObject(pFunc, pArgs);
    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear();
    }
    double result = PyLong_AsDouble(pValue);
    Py_Finalize();
    
    return result;
}


int lamp_select(const char* name) {
    PyObject* pName, * pModule, * pFunc, * pValue, * pParameter, * pArgs;

    Py_Initialize();
    pName = PyUnicode_FromString("client_c");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
        std::cout << "bad >:(";
    //else throw;
    pFunc = PyObject_GetAttrString(pModule, "lamp_select");
    pParameter = PyUnicode_FromString(name);
    pArgs = PyTuple_New(1);
    PyTuple_SET_ITEM(pArgs, 0, pParameter);
    pValue = PyObject_CallObject(pFunc, pArgs);
    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear();
    }
    double result = PyLong_AsDouble(pValue);
    Py_Finalize();

    return result;
}

int heater_select(const char* name) {
    PyObject* pName, * pModule, * pFunc, * pValue, * pParameter, * pArgs;

    Py_Initialize();
    pName = PyUnicode_FromString("client_c");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
        std::cout << "bad >:(";
    //else throw;
    pFunc = PyObject_GetAttrString(pModule, "heater_select");
    pParameter = PyUnicode_FromString(name);
    pArgs = PyTuple_New(1);
    PyTuple_SET_ITEM(pArgs, 0, pParameter);
    pValue = PyObject_CallObject(pFunc, pArgs);
    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear();
    }
    double result = PyLong_AsDouble(pValue);
    Py_Finalize();

    return result;
}


int humidifier_select(const char* name) {
    PyObject* pName, * pModule, * pFunc, * pValue, * pParameter, * pArgs;

    Py_Initialize();
    pName = PyUnicode_FromString("client_c");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
        std::cout << "bad >:(";
    //else throw;
    pFunc = PyObject_GetAttrString(pModule, "humidifier_select");
    pParameter = PyUnicode_FromString(name);
    pArgs = PyTuple_New(1);
    PyTuple_SET_ITEM(pArgs, 0, pParameter);
    pValue = PyObject_CallObject(pFunc, pArgs);
    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear();
    }
    double result = PyLong_AsDouble(pValue);
    Py_Finalize();

    return result;
}


int main() {
    //Py_Initialize();
    //PyRun_SimpleString("import sys; sys.path.append('.')");
    //PyRun_SimpleString("import client;");
    //PyRun_SimpleString("print(client.jalousie_select('kitchen/jalousie')['rotation'])");
    //Py_Finalize();
    //setenv("PYTHONPATH", "C:\\Users\\matve\\source\\repos\\py_client\\py_client", true);
    //Py_Initialize();
    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("print(sys.path)");
    //Py_Finalize();
    int res;
    res = jalousie_select("kitchen/jalousie");
    std::cout << "rotation is " << res << std::endl;
    res = lamp_select("kitchen/lamp1");
    std::cout << "power is " << res << std::endl;
    res = heater_select("kitchen/heater");
    std::cout << "warmth is " << res << std::endl;
    res = humidifier_select("kitchen/humidifier");
    std::cout << "power is " << res << std::endl;

    return 0;
}
