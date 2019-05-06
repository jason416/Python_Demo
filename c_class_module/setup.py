#!/usr/bin/env python
# coding=utf-8
from distutils.core import setup, Extension

setup(name="noddy", version="1.0",ext_modules=[Extension("noddy", ["noddy.c"]),
                                               Extension("noddy2", ["noddy2.c"])])
