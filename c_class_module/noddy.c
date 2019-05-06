/*
 * Use C to create a Python Object
 *
 *
 */

#include <Python.h>
#include <stdlib.h>

#define HAS_UNIQUE_ERR

/*
 * every Python object contains, namely a refcount and a pointer to a type object. 
 * These are the fields the PyObject_HEAD macro brings in
 */
typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
} noddy_NoddyObject;

static PyTypeObject noddy_NoddyType = {
    PyVarObject_HEAD_INIT(NULL, 0)  /* this member will be filled in for us by PyType_Ready() */
    .tp_name = "noddy.Noddy",
    .tp_doc = "Noddy objects",
    .tp_basicsize = sizeof(noddy_NoddyObject), /* size for Python */
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyMethodDef noddy_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC initnoddy(void)
{
    PyObject* m;

    if(PyType_Ready(&noddy_NoddyType) < 0)
        return;

    m = Py_InitModule3("noddy", noddy_methods,
                       "Example module that creates an extension type.");

    Py_INCREF(&noddy_NoddyType);
    PyModule_AddObject(m, "Noddy", (PyObject *)&noddy_NoddyType);
}


