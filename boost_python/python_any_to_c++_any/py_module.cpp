#include <iostream>
#include <boost/python.hpp>
#include "py_variant.h"

#if PY_MAJOR_VERSION >= 3
#define PyString_Check PyUnicode_Check
#define PyString_AsString(S) PyBytes_AsString(PyUnicode_AsUTF8String(S))
#endif

using namespace boost::python;
using namespace Variant_test;

Variant test(const Variant &val)
{
    Variant var_l = val;
    return var_l;
}



BOOST_PYTHON_MODULE(py_variant)
{
    variant_from_python_converter();
    to_python_converter<Variant, variant_to_python_converter>();

   def("test", (Variant (*) (const Variant &)) &test); 
}








