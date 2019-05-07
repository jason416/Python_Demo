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

n1 = Noddy()
n2 = Noddy(first='noddy', last='last', number=1)

n1.first = 'Noddy'
print(n1.first, n1.last, n1.number)
print("In class Noddy, call name(): " + n1.name())
print("\n")

print(n2.first, n2.last, n2.number)
print("In class Noddy, call name(): " + n2.name())
print("\n")


s1 = sub()
s2 = sub('jason', 'lee', 123)

print(s1.get_attr())
s1.name()
print("\n")

print(s2.get_attr())
s2.name()


