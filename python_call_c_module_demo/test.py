#!/usr/bin/env python
# coding=utf-8

'''
test for call c module
'''

# from demo_module import demo_function
import demo_module

val = input("Please input a intger: ")
ret = demo_module.demo_function(val)

print("ret = %d" %(ret))

# raise demo_module.error("error")
