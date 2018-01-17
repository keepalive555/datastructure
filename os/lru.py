# -*- coding: utf-8 -*-

"""
Python LRU Cache实现。
"""

from __future__ import print_function

import collections


class LRUCache(object):
    """
    """
    def __init__(self, size=50):
        self.size = size
        self.cache = collections.OrderedDict()

    def get(self, key):
        if key in self.cache:
            value = self.cache.pop(key)
            self.cache[key] = value
        else:
            value = None
        return value

    def set(self, key, value):
        if key in self.cache:
            self.cache.pop(key)
        elif len(self.cache) == self.size:
            self.cache.popitem(last=False)
        self.cache[key] = value

    def show(self):
        for k, v in self.cache.iteritems():
            print(k, v)


if __name__ == '__main__':
    cache = LRUCache(size=5)
    cache.set('key1', 'key1')
    cache.set('key2', 'key2')
    cache.set('key3', 'key3')
    cache.set('key4', 'key4')
    cache.set('key5', 'key5')
    cache.show()
    print('get key2', cache.get('key2'))
    cache.show()
    print('>>>>>>set key6')
    cache.set('key6', 'key6')
    cache.show()
