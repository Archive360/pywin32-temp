// This file declares the ICopyHook Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyICopyHook : public PyIUnknown
{
public:
	MAKE_PYCOM_CTOR(PyICopyHook);
	static ICopyHook *GetI(PyObject *self);
	static PyComTypeObject type;

	// The Python methods
	static PyObject *CopyCallback(PyObject *self, PyObject *args);

protected:
	PyICopyHook(IUnknown *pdisp);
	~PyICopyHook();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGCopyHook : public PyGatewayBase, public ICopyHook
{
protected:
	PyGCopyHook(PyObject *instance) : PyGatewayBase(instance) { ; }
	PYGATEWAY_MAKE_SUPPORT2(PyGCopyHook, ICopyHook, IID_IShellCopyHook, PyGatewayBase)

	// ICopyHook
	STDMETHOD_(UINT, CopyCallback)(
		HWND hwnd,
		UINT wFunc,
		UINT wFlags,
		LPCTSTR srcFile,
		DWORD srcAttribs,
		LPCTSTR destFile,
		DWORD destAttribs);

};