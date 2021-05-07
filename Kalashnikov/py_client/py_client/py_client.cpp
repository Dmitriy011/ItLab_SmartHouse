#include "py_client.h"

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

int sensor_insert(const char* name, long value) {
    PyObject* pName, * pModule, * pFunc, * pValue, * pParameterName, * pParameterValue, * pArgs;

    Py_Initialize();
    pName = PyUnicode_FromString("client_c");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
        std::cout << "bad >:(";
    //else throw;
    pFunc = PyObject_GetAttrString(pModule, "sensor_insert");
    pParameterName = PyUnicode_FromString(name);
    pParameterValue = PyLong_FromLong(value);
    pArgs = PyTuple_New(2);
    PyTuple_SET_ITEM(pArgs, 0, pParameterName);
    PyTuple_SetItem(pArgs, 1, pParameterValue);
    pValue = PyObject_CallObject(pFunc, pArgs);
    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear();
    }
    double result = PyLong_AsDouble(pValue);
    Py_Finalize();

    return result;
}



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