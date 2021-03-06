// This file implements the ICategoryProvider Interface and Gateway for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyICategoryProvider.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyICategoryProvider::PyICategoryProvider(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyICategoryProvider::~PyICategoryProvider() {}

/* static */ ICategoryProvider *PyICategoryProvider::GetI(PyObject *self)
{
    return (ICategoryProvider *)PyIUnknown::GetI(self);
}

// @pymethod |PyICategoryProvider|CanCategorizeOnSCID|Description of CanCategorizeOnSCID.
PyObject *PyICategoryProvider::CanCategorizeOnSCID(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    SHCOLUMNID scid;
    PyObject *obpscid;
    // @pyparm <o SHCOLUMNID>|pscid||Description for pscid
    if (!PyArg_ParseTuple(args, "O:CanCategorizeOnSCID", &obpscid))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyObject_AsSHCOLUMNID(obpscid, &scid))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICP->CanCategorizeOnSCID(&scid);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    PyObject *ret = (hr == S_OK) ? Py_True : Py_False;
    Py_INCREF(ret);
    return ret;
}

// @pymethod |PyICategoryProvider|GetDefaultCategory|Description of GetDefaultCategory.
PyObject *PyICategoryProvider::GetDefaultCategory(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":GetDefaultCategory"))
        return NULL;
    HRESULT hr;
    GUID guid = IID_NULL;
    SHCOLUMNID scid;
    PY_INTERFACE_PRECALL;
    hr = pICP->GetDefaultCategory(&guid, &scid);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    return Py_BuildValue("NN", PyWinObject_FromIID(guid), PyObject_FromSHCOLUMNID(&scid));
}

// @pymethod |PyICategoryProvider|GetCategoryForSCID|Description of GetCategoryForSCID.
PyObject *PyICategoryProvider::GetCategoryForSCID(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    SHCOLUMNID scid;
    PyObject *obpscid;
    // @pyparm <o SHCOLUMNID>|pscid||Description for pscid
    if (!PyArg_ParseTuple(args, "O:GetCategoryForSCID", &obpscid))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyObject_AsSHCOLUMNID(obpscid, &scid))
        return NULL;
    HRESULT hr;
    GUID guid;
    PY_INTERFACE_PRECALL;
    hr = pICP->GetCategoryForSCID(&scid, &guid);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    return PyWinObject_FromIID(guid);
}

// @pymethod |PyICategoryProvider|EnumCategories|Description of EnumCategories.
PyObject *PyICategoryProvider::EnumCategories(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":EnumCategories"))
        return NULL;
    HRESULT hr;
    IEnumGUID *penum;
    PY_INTERFACE_PRECALL;
    hr = pICP->EnumCategories(&penum);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    return PyCom_PyObjectFromIUnknown(penum, IID_IEnumGUID, FALSE);
}

// @pymethod |PyICategoryProvider|GetCategoryName|Description of GetCategoryName.
PyObject *PyICategoryProvider::GetCategoryName(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    GUID guid;
    PyObject *obpguid;
    // @comm The buffer is always 1024 chars long
    WCHAR buffer[1024];
    // @pyparm <o PyIID>|guid||Description for pguid
    if (!PyArg_ParseTuple(args, "O:GetCategoryName", &obpguid))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsIID(obpguid, &guid))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pICP->GetCategoryName(&guid, buffer, sizeof(buffer) / sizeof(buffer[0]));
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    return PyWinObject_FromWCHAR(buffer);
}

// @pymethod |PyICategoryProvider|CreateCategory|Description of CreateCategory.
PyObject *PyICategoryProvider::CreateCategory(PyObject *self, PyObject *args)
{
    ICategoryProvider *pICP = GetI(self);
    if (pICP == NULL)
        return NULL;
    GUID guid;
    PyObject *obpguid;
    // @pyparm <o PyIID>|guid||Description for pguid
    IID riid;
    PyObject *obriid;
    // @pyparm <o PyIID>|riid||Description for riid
    if (!PyArg_ParseTuple(args, "OO:CreateCategory", &obpguid, &obriid))
        return NULL;
    if (!PyWinObject_AsIID(obpguid, &guid) || !PyWinObject_AsIID(obriid, &riid))
        return NULL;
    HRESULT hr;
    void *ret;
    PY_INTERFACE_PRECALL;
    hr = pICP->CreateCategory(&guid, riid, &ret);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pICP, IID_ICategoryProvider);
    return PyCom_PyObjectFromIUnknown((IUnknown *)ret, riid, FALSE);
}

// @object PyICategoryProvider|Description of the interface
static struct PyMethodDef PyICategoryProvider_methods[] = {
    {"CanCategorizeOnSCID", PyICategoryProvider::CanCategorizeOnSCID,
     1},  // @pymeth CanCategorizeOnSCID|Description of CanCategorizeOnSCID
    {"GetDefaultCategory", PyICategoryProvider::GetDefaultCategory,
     1},  // @pymeth GetDefaultCategory|Description of GetDefaultCategory
    {"GetCategoryForSCID", PyICategoryProvider::GetCategoryForSCID,
     1},  // @pymeth GetCategoryForSCID|Description of GetCategoryForSCID
    {"EnumCategories", PyICategoryProvider::EnumCategories, 1},  // @pymeth EnumCategories|Description of EnumCategories
    {"GetCategoryName", PyICategoryProvider::GetCategoryName,
     1},  // @pymeth GetCategoryName|Description of GetCategoryName
    {"CreateCategory", PyICategoryProvider::CreateCategory, 1},  // @pymeth CreateCategory|Description of CreateCategory
    {NULL}};

PyComTypeObject PyICategoryProvider::type("PyICategoryProvider", &PyIUnknown::type, sizeof(PyICategoryProvider),
                                          PyICategoryProvider_methods, GET_PYCOM_CTOR(PyICategoryProvider));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGCategoryProvider::CanCategorizeOnSCID(
    /* [in] */ __RPC__in const SHCOLUMNID *pscid)
{
    PY_GATEWAY_METHOD;
    PyObject *ret;
    HRESULT hr = InvokeViaPolicy("CanCategorizeOnSCID", &ret, "(N)", PyObject_FromSHCOLUMNID(pscid));
    if (FAILED(hr))
        return hr;
    hr = S_FALSE;
    if (PyLong_Check(ret))  // make a bool
        hr = PyLong_AsLong(ret) ? S_OK : S_FALSE;
    Py_DECREF(ret);
    return hr;
}

STDMETHODIMP PyGCategoryProvider::GetDefaultCategory(
    /* [out] */ __RPC__out GUID *pguid,
    /* [out] */ __RPC__out SHCOLUMNID *pscid)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetDefaultCategory", &result);
    if (FAILED(hr))
        return hr;
    // GUID is documented by MSDN as unused - but the FolderView MSDN
    // only sets *pguid (it sets 'pscid' - without the '*' - which has
    // no effect!
    PyObject *obguid, *obscid;
    if (!PyArg_ParseTuple(result, "OO:GetDefaultCategory result", &obguid, &obscid))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetDefaultCategory");
    else {
        if (!PyWinObject_AsIID(obguid, pguid) || !PyObject_AsSHCOLUMNID(obscid, pscid))
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetDefaultCategory");
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategoryProvider::GetCategoryForSCID(
    /* [in] */ __RPC__in const SHCOLUMNID *pscid,
    /* [out] */ __RPC__out GUID *pguid)
{
    PY_GATEWAY_METHOD;
    PyObject *obpscid = PyObject_FromSHCOLUMNID(pscid);
    if (obpscid == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategoryForSCID");
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetCategoryForSCID", &result, "(O)", obpscid);
    Py_DECREF(obpscid);
    if (FAILED(hr))
        return hr;
    if (!PyWinObject_AsIID(result, pguid))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategoryForSCID");
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategoryProvider::EnumCategories(
    /* [out] */ __RPC__deref_out_opt IEnumGUID **penum)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("EnumCategories", &result);
    if (FAILED(hr))
        return hr;
    if (result == Py_None) {
        hr = S_FALSE;
        *penum = NULL;
    }
    else {
        if (!PyCom_InterfaceFromPyInstanceOrObject(result, IID_IEnumGUID, (void **)penum, FALSE))
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("EnumCategories");
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategoryProvider::GetCategoryName(
    /* [in] */ __RPC__in const GUID *pguid,
    /* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszName,
    /* [in] */ UINT cch)
{
    PY_GATEWAY_METHOD;
    PyObject *obpguid = PyWinObject_FromIID(*pguid);
    if (obpguid == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategoryName");
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetCategoryName", &result, "Oi", obpguid, cch);
    Py_DECREF(obpguid);
    if (FAILED(hr))
        return hr;
    // ack - should be a function to convert directly into a buffer.
    WCHAR *allocd_result;
    if (!PyWinObject_AsWCHAR(result, &allocd_result, FALSE)) {
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategoryName");
    }
    else {
        wcsncpy(pszName, allocd_result, cch);
        PyWinObject_FreeWCHAR(allocd_result);
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategoryProvider::CreateCategory(
    /* [in] */ __RPC__in const GUID *pguid,
    /* [in] */ __RPC__in REFIID riid,
    /* [iid_is][out] */ __RPC__deref_out_opt void **ppv)
{
    PY_GATEWAY_METHOD;
    PyObject *obpguid = PyWinObject_FromIID(*pguid);
    if (obpguid == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("CreateCategory");
    PyObject *obriid = PyWinObject_FromIID(riid);
    if (obriid == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("CreateCategory");
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("CreateCategory", &result, "OO", obpguid, obriid);
    Py_DECREF(obpguid);
    Py_DECREF(obriid);
    if (FAILED(hr))
        return hr;
    if (!PyCom_InterfaceFromPyInstanceOrObject(result, riid, ppv, FALSE /* bNoneOK */))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("CreateCategory");
    Py_DECREF(result);
    return hr;
}
