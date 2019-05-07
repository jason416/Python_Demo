#!/usr/bin/env python
# coding=utf-8
from noddy2 import Noddy

class sub(Noddy):
    def __init__(self, first='default first', last='default last', number=100):
        self.first = first
        self.last = last
        self.number = number
    def get_attr(self):
        return (self.first, self.last, self.number)
    def name(self):
        print("In subclass of Noddy, call rewrited name()")
        print("first = %s, last = %s, number = %d" % (self.first, self.last, self.number))

n = Noddy()
n.first = 'Noddy'
print(n.first, n.last, n.number)
print("In class Noddy, call name(): " + n.name())
print("\n")

s1 = sub()
s2 = sub('jason', 'lee', 123)

print(s1.get_attr())
s1.name()
print("\n")

print(s2.get_attr())
s2.name()


