// This file implements the IApplicationDebugger Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PyIApplicationDebugger.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIApplicationDebugger::PyIApplicationDebugger(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIApplicationDebugger::~PyIApplicationDebugger() {}

/* static */ IApplicationDebugger *PyIApplicationDebugger::GetI(PyObject *self)
{
    return (IApplicationDebugger *)PyIUnknown::GetI(self);
}

// @pymethod |PyIApplicationDebugger|QueryAlive|Returns true if alive, else false.
PyObject *PyIApplicationDebugger::QueryAlive(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":QueryAlive"))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->QueryAlive();
    PY_INTERFACE_POSTCALL;
    return PyLong_FromLong(hr == S_OK);
}

// @pymethod |PyIApplicationDebugger|CreateInstanceAtDebugger|Create objects in the application process address space.
PyObject *PyIApplicationDebugger::CreateInstanceAtDebugger(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    // @comm Provides a mechanism for the debugger IDE, running out-of-process to the
    // application, to create objects in the application process.
    // This method simply delegates to CoCreateInstance.
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    // @pyparm <o PyIID>|rclsid||Description for rclsid
    // @pyparm <o PyIUnknown>|pUnkOuter||Description for pUnkOuter
    // @pyparm int|dwClsContext||Description for dwClsContext
    // @pyparm <o PyIID>|riid||Description for riid
    PyObject *obrclsid;
    PyObject *obpUnkOuter;
    PyObject *obriid;
    IID rclsid;
    IUnknown *pUnkOuter = NULL;
    DWORD dwClsContext;
    IID riid;
    IUnknown *ppvObject;
    if (!PyArg_ParseTuple(args, "OOiO:CreateInstanceAtDebugger", &obrclsid, &obpUnkOuter, &dwClsContext, &obriid))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsIID(obrclsid, &rclsid))
        bPythonIsHappy = FALSE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpUnkOuter, IID_IUnknown, (void **)&pUnkOuter, FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!PyWinObject_AsIID(obriid, &riid))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy) {
        if (pUnkOuter)
            pUnkOuter->Release();
        return NULL;
    }
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->CreateInstanceAtDebugger(rclsid, pUnkOuter, dwClsContext, riid, &ppvObject);
    if (pUnkOuter)
        pUnkOuter->Release();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    return PyCom_PyObjectFromIUnknown(ppvObject, IID_IUnknown, FALSE);
}

// @pymethod |PyIApplicationDebugger|onDebugOutput|Called when <om PyIDebugApplication.DebugOutput> is called.
PyObject *PyIApplicationDebugger::onDebugOutput(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    // @comm The debugger can use this to display the string in an output window.
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    // @pyparm <o unicode>|pstr||Description for pstr
    PyObject *obpstr;
    BSTR pstr;
    if (!PyArg_ParseTuple(args, "O:onDebugOutput", &obpstr))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_BstrFromPyObject(obpstr, &pstr))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->onDebugOutput(pstr);
    if (pstr)
        SysFreeString(pstr);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIApplicationDebugger|onHandleBreakPoint|Called when a breakpoint is hit.
PyObject *PyIApplicationDebugger::onHandleBreakPoint(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    // @comm The application will remain
    // suspended until the debugger IDE calls <om PyIDebugApplication.ResumeFromBreakPoint>.
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    // @pyparm <o PyIRemoteDebugApplicationThread>|prpt||Description for prpt
    // @pyparm int|br||Description for br
    // @pyparm <o IActiveScriptErrorDebug>|pError||Description for pError
    PyObject *obprpt;
    PyObject *obError;
    IRemoteDebugApplicationThread *prpt;
    IActiveScriptErrorDebug *pError;
    BREAKREASON br;
    if (!PyArg_ParseTuple(args, "OiO:onHandleBreakPoint", &obprpt, &br, &obError))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obprpt, IID_IRemoteDebugApplicationThread, (void **)&prpt,
                                               FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obError, IID_IActiveScriptErrorDebug, (void **)&pError,
                                               TRUE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->onHandleBreakPoint(prpt, br, pError);
    prpt->Release();
    if (pError)
        pError->Release();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIApplicationDebugger|onClose|Called when <om PyIDebugApplication.Close> is called.
PyObject *PyIApplicationDebugger::onClose(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":onClose"))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->onClose();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIApplicationDebugger|onDebuggerEvent|Description of onDebuggerEvent.
PyObject *PyIApplicationDebugger::onDebuggerEvent(PyObject *self, PyObject *args)
{
    PY_INTERFACE_METHOD;
    IApplicationDebugger *pIAD = GetI(self);
    if (pIAD == NULL)
        return NULL;
    // @pyparm <o PyIID>|guid||
    // @pyparm <o PyIUnknown>|uUnknown||
    PyObject *obIID;
    PyObject *obUnk;
    if (!PyArg_ParseTuple(args, "OO:onDebuggerEvent", &obIID, &obUnk))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    IID iid;
    IUnknown *punk;
    if (!PyWinObject_AsIID(obIID, &iid))
        bPythonIsHappy = FALSE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obUnk, IID_IUnknown, (void **)&punk, FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIAD->onDebuggerEvent(iid, punk);
    punk->Release();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    Py_INCREF(Py_None);
    return Py_None;
    // @comm The semantics of guid and unknown are entirely application/debugger defined
    // <nl>This method may return E_NOTIMPL.
}

// @object PyIApplicationDebugger|Description of the interface
static struct PyMethodDef PyIApplicationDebugger_methods[] = {
    {"QueryAlive", PyIApplicationDebugger::QueryAlive, 1},  // @pymeth QueryAlive|Returns true if alive, else false.
    {"CreateInstanceAtDebugger", PyIApplicationDebugger::CreateInstanceAtDebugger,
     1},  // @pymeth CreateInstanceAtDebugger|Create objects in the application process address space.
    {"onDebugOutput", PyIApplicationDebugger::onDebugOutput,
     1},  // @pymeth onDebugOutput|Called when <om PyIDebugApplication.DebugOutput> is called.
    {"onHandleBreakPoint", PyIApplicationDebugger::onHandleBreakPoint,
     1},  // @pymeth onHandleBreakPoint|Called when a breakpoint is hit.
    {"onClose", PyIApplicationDebugger::onClose,
     1},  // @pymeth onClose|Called when <om PyIDebugApplication.Close> is called.
    {"onDebuggerEvent", PyIApplicationDebugger::onDebuggerEvent, 1},  // @pymeth onDebuggerEvent|Handle a custom event.
    {NULL}};

PyComTypeObject PyIApplicationDebugger::type("PyIApplicationDebugger", &PyIUnknown::type,
                                             sizeof(PyIApplicationDebugger), PyIApplicationDebugger_methods,
                                             GET_PYCOM_CTOR(PyIApplicationDebugger));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGApplicationDebugger::QueryAlive(void)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("QueryAlive", NULL);
    return hr;
}

STDMETHODIMP PyGApplicationDebugger::CreateInstanceAtDebugger(
    /* [in] */ REFCLSID rclsid,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ DWORD dwClsContext,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppvObject)
{
    PY_GATEWAY_METHOD;
    if (ppvObject == NULL)
        return E_POINTER;
    PyObject *obrclsid;
    PyObject *obpUnkOuter;
    PyObject *obriid;
    obrclsid = PyWinObject_FromIID(rclsid);
    obpUnkOuter = PyCom_PyObjectFromIUnknown(pUnkOuter, IID_IUnknown, TRUE);
    obriid = PyWinObject_FromIID(riid);
    PyObject *result;
    HRESULT hr =
        InvokeViaPolicy("CreateInstanceAtDebugger", &result, "OOiO", obrclsid, obpUnkOuter, dwClsContext, obriid);
    Py_XDECREF(obrclsid);
    Py_XDECREF(obpUnkOuter);
    Py_XDECREF(obriid);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obppvObject;
    if (!PyArg_Parse(result, "O", &obppvObject))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obppvObject, IID_IUnknown, (void **)ppvObject, FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}

/*
STDMETHODIMP PyGApplicationDebugger::onAddDocumentProvider(
        IDebugDocumentProvider __RPC_FAR * pssdp,
        DWORD dwDocumentProviderCookie)
{
    PY_GATEWAY_METHOD;
    PyObject *obpssdp;
    obpssdp = PyCom_PyObjectFromIUnknown(pssdp, IID_IDebugDocumentProvider, TRUE);
    HRESULT hr=InvokeViaPolicy("onAddDocumentProvider", NULL, "Oi", obpssdp, dwDocumentProviderCookie);
    Py_XDECREF(obpssdp);
    return hr;
}

STDMETHODIMP PyGApplicationDebugger::onRemoveDocumentProvider(
        IDebugDocumentProvider __RPC_FAR * pssd,
        DWORD dwDocumentProviderCookie)
{
    PY_GATEWAY_METHOD;
    PyObject *obpssd;
    obpssd = PyCom_PyObjectFromIUnknown(pssd, IID_IDebugDocumentProvider, TRUE);
    HRESULT hr=InvokeViaPolicy("onRemoveDocumentProvider", NULL, "Oi", obpssd, dwDocumentProviderCookie);
    Py_XDECREF(obpssd);
    return hr;
}
*/
STDMETHODIMP PyGApplicationDebugger::onDebugOutput(
    /* [in] */ LPCOLESTR pstr)
{
    PY_GATEWAY_METHOD;
    PyObject *obpstr;
    obpstr = PyWinObject_FromOLECHAR(pstr);
    HRESULT hr = InvokeViaPolicy("onDebugOutput", NULL, "O", obpstr);
    Py_XDECREF(obpstr);
    return hr;
}

STDMETHODIMP PyGApplicationDebugger::onHandleBreakPoint(
    /* [in] */ IRemoteDebugApplicationThread __RPC_FAR *prpt,
    /* [in] */ BREAKREASON br,
    /* [in] */ IActiveScriptErrorDebug __RPC_FAR *pError)
{
    PY_GATEWAY_METHOD;
    PyObject *obprpt, *obErr;
    obprpt = PyCom_PyObjectFromIUnknown(prpt, IID_IRemoteDebugApplicationThread, TRUE);
    obErr = PyCom_PyObjectFromIUnknown(pError, IID_IActiveScriptErrorDebug, TRUE);
    HRESULT hr = InvokeViaPolicy("onHandleBreakPoint", NULL, "OiO", obprpt, br, obErr);
    Py_XDECREF(obprpt);
    Py_XDECREF(obErr);
    return hr;
}

STDMETHODIMP PyGApplicationDebugger::onClose(void)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("onClose", NULL);
}

STDMETHODIMP PyGApplicationDebugger::onDebuggerEvent(REFIID riid, IUnknown *punk)
{
    PY_GATEWAY_METHOD;
    PyObject *obrclsid = PyWinObject_FromIID(riid);
    PyObject *obUnk = PyCom_PyObjectFromIUnknown(punk, IID_IUnknown, TRUE);
    HRESULT hr = InvokeViaPolicy("onDebuggerEvent", NULL, "OO", obrclsid, obUnk);
    Py_XDECREF(obrclsid);
    Py_XDECREF(obUnk);
    return hr;
}
