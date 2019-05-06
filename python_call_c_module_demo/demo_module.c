/*
 * A Simple demo_module, can be called by Python interpreter
 *
 * 1: 所有Python元素，module、function、tuple、string等等，实际上都是PyObject。
 *    C语言里操纵它们，一律使用PyObject *。
 * 2: Python的类型与C语言类型可以相互转换。Python类型XXX转换为C语言类型YYY要使
 *    用PyXXX_AsYYY函数；C类型YYY转换为Python类型XXX要使用PyXXX_FromYYY函数。
 * 3: 也可以创建Python类型的变量，使用PyXXX_New可以创建类型为XXX的变量。
 */

#include <Python.h>
#include <stdlib.h>

#define HAS_UNIQUE_ERR

/* 
 * Module unique exception: <DemoModuleError>
 */
static PyObject *DemoModuleError;


/****************************************************************************/

/*
 * function called last: <demo_function>
 *     最终Python环境调用的用C编写的function
 */
static int demo_function(int a)
{
    return ++a;
}


/*
 * Wrapper function: <_demo_function>
 *     1: 它负责将Python的参数转化为C的参数（PyArg_ParseTuple），
 *     2: 调用实际的demo_function，并处理demo_function的返回值，最终返回给Python环境。
 */
static PyObject * _demo_function(PyObject *self, PyObject *args)
{
    int _a, ret;

    /* "i" is a fromat string, more information referance Python/C API */
    if(!PyArg_ParseTuple(args, "i", &_a))
        return NULL;

    ret = demo_function(_a);
    if(ret < 0) {
        PyErr_SetString(DemoModuleError, "value error");
        return NULL;
    }
    return PyLong_FromLong(ret);
}


/*
 * Method table: <DemoModuleMethods>
 *     1: 它负责告诉Python这个模块里有哪些函数可以被Python调用。
 *     2: 方法表的名字可以随便起，每一项有4个参数，下面是各个参数含:
 *        ml_name   char *      name of the method
 *        ml_meth   PyCFunction pointer to the C implementation
 *        ml_flags  int         flag bits indicating how the call should be constructed
 *        ml_doc    char *      points to the contents of the docstring
 *     3: 方法表总是以{NULL, NULL, 0, NULL}结束。
 *
 */
static PyMethodDef DemoModuleMethods[] = {
    {
        "demo_function", /* name */
        _demo_function,  /* C function */
        METH_VARARGS,     /* METH_VARARGS, METH_KETWORDS */
        ""
    },
    {NULL, NULL, 0, NULL}
};


/*
 * Initialization function: <initdemo_module>
 *     1: 这个的名字不是任取的，是你的module名称添加前缀init。
 *     2: 初始化函数中将模块名称与导出表进行连接。
 *
 */
PyMODINIT_FUNC initdemo_module(void)
{
#ifdef HAS_UNIQUE_ERR
    PyObject *m = NULL; 
    m = Py_InitModule("demo_module", DemoModuleMethods);
    if(m == NULL)
        return ;

    DemoModuleError = PyErr_NewException("demo_module.error", NULL, NULL);
    Py_INCREF(DemoModuleError);
    PyModule_AddObject(m, "error", DemoModuleError);
#else
    (void) Py_InitModule("demo_module", DemoModuleMethods);
#endif
}

