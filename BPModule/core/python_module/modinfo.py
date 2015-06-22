#!/usr/bin/env python3

import os

minfo = { "TESTMOD1" :
  {
    "name"        : "Some test",
    "soname"      : "testmodule1",
    "version"     : "0.1a",
    "description" : "Some test module",
    "authors"     : ["me", "myself", "I"],
    "refs"        : ["some paper", "some other paper"],
    "options"     : [ 
                        ("adouble", "0.0", "Some help string"),
                        ("aint", 1, "Some help string2"),
                        ("double2", 2.1, "Some help string3")
                    ]
  }
}


