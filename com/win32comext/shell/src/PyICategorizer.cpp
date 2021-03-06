// This file implements the ICategorizer Interface and Gateway for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyICategorizer.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGCategorizer::GetDescription(
    /* [size_is][string][out] */ __RPC__out_ecount_full_string(cch) LPWSTR pszDesc,
    /* [in] */ UINT cch)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetDescription", &result, "i", cch);
    if (FAILED(hr))
        return hr;
    // ack - should be a function to convert directly into a buffer.
    WCHAR *allocd_result;
    if (!PyWinObject_AsWCHAR(result, &allocd_result, FALSE)) {
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetDescription");
    }
    else {
        wcsncpy(pszDesc, allocd_result, cch);
        PyWinObject_FreeWCHAR(allocd_result);
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategorizer::GetCategory(
    /* [in] */ UINT cidl,
    /* [size_is][in] */ __RPC__in_ecount_full(cidl) PCUITEMID_CHILD_ARRAY apidl,
    /* [size_is][out] */ __RPC__out_ecount_full(cidl) DWORD *rgCategoryIds)
{
    static const char *method_name = "GetCategory";
    PY_GATEWAY_METHOD;
    PyObject *obapidl = PyList_New(cidl);
    if (!obapidl)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE(method_name);
    for (UINT i = 0; i < cidl; i++) {
        PyObject *obpidl = PyObject_FromPIDL(apidl[i], FALSE);
        if (obpidl) {
            Py_DECREF(obapidl);
            return MAKE_PYCOM_GATEWAY_FAILURE_CODE(method_name);
        }
        PyList_SET_ITEM(obapidl, i, obpidl);
    }
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetCategory", &result, "O", obapidl);
    Py_DECREF(obapidl);
    if (FAILED(hr))
        return hr;
    PyObject *dwords_tuple;
    DWORD ret_cnt;
    if ((dwords_tuple = PyWinSequence_Tuple(result, &ret_cnt)) == NULL)
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE(method_name);
    else {
        if (ret_cnt != cidl) {
            PyErr_Format(PyExc_ValueError, "expecting sequence of length %d, got %d", cidl, ret_cnt);
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE(method_name);
        }
        else {
            for (DWORD tuple_index = 0; tuple_index < cidl; tuple_index++) {
                PyObject *tuple_item = PyTuple_GET_ITEM(dwords_tuple, tuple_index);
                rgCategoryIds[tuple_index] = PyLong_AsLong(tuple_item);
                if ((rgCategoryIds[tuple_index] == -1) && PyErr_Occurred()) {
                    hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE(method_name);
                    break;
                }
            }
        }
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategorizer::GetCategoryInfo(
    /* [in] */ DWORD dwCategoryId,
    /* [out] */ __RPC__out CATEGORY_INFO *pci)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetCategoryInfo", &result, "l", dwCategoryId);
    if (FAILED(hr))
        return hr;
    PyObject *obName;
    if (!PyArg_ParseTuple(result, "iO", &pci->cif, &obName))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategory");
    else {
        WCHAR *allocd_result;
        if (!PyWinObject_AsWCHAR(obName, &allocd_result, FALSE)) {
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategoryInfo");
        }
        else {
            wcsncpy(pci->wszName, allocd_result, sizeof(pci->wszName) / sizeof(pci->wszName[0]));
            PyWinObject_FreeWCHAR(allocd_result);
        }
    }
    // Process the Python results, and convert back to the real params
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGCategorizer::CompareCategory(
    /* [in] */ CATSORT_FLAGS csfFlags,
    /* [in] */ DWORD dwCategoryId1,
    /* [in] */ DWORD dwCategoryId2)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("CompareCategory", &result, "lll", csfFlags, dwCategoryId1, dwCategoryId2);
    if (FAILED(hr))
        return hr;
    if (!PyLong_Check(result)) {
        PyErr_Format(PyExc_TypeError, "CompareCategory expects an int, got a %s", result->ob_type->tp_name);
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("GetCategory");
    }
    else {
        hr = MAKE_HRESULT(SEVERITY_SUCCESS, 0, (USHORT)PyLong_AsLong(result));
    }
    Py_DECREF(result);
    return hr;
}
