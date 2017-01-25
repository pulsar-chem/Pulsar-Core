import pulsar as psr
def load_ref_system():
    """ Returns heptacene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C          0.00000        0.70725        1.21701
      C         -0.00000       -0.70725        1.21701
      C         -0.00000       -1.40545        2.43397
      C         -0.00000       -0.70751        3.65104
      C         -0.00000        0.70751        3.65104
      C          0.00000        1.40545        2.43397
      C          0.00000        1.40536       -0.00000
      C         -0.00000       -1.40536        0.00000
      H         -0.00000       -2.49035        2.43387
      C         -0.00000       -1.40620        4.86805
      C         -0.00000        1.40620        4.86805
      H          0.00000        2.49035        2.43387
      C         -0.00000       -0.70725       -1.21701
      C          0.00000        0.70725       -1.21701
      H          0.00000        2.49025       -0.00000
      H         -0.00000       -2.49025        0.00000
      C         -0.00000       -1.40545       -2.43397
      C          0.00000        1.40545       -2.43397
      C         -0.00000       -0.70776        6.08426
      C         -0.00000        0.70776        6.08426
      H         -0.00000       -2.49107        4.86866
      H          0.00000        2.49107        4.86866
      C         -0.00000       -1.40234        7.30441
      C         -0.00000        1.40234        7.30441
      C         -0.00000        0.69872        8.51225
      C         -0.00000       -0.69872        8.51225
      H         -0.00000       -2.48577        7.32125
      H          0.00000        2.48577        7.32125
      H         -0.00000        1.23799        9.45070
      H         -0.00000       -1.23799        9.45070
      C          0.00000        0.70751       -3.65104
      C          0.00000       -0.70751       -3.65104
      H         -0.00000       -2.49035       -2.43387
      H          0.00000        2.49035       -2.43387
      C          0.00000        1.40620       -4.86805
      C          0.00000       -1.40620       -4.86805
      C          0.00000       -0.70776       -6.08426
      C          0.00000        0.70776       -6.08426
      H          0.00000        2.49107       -4.86866
      H         -0.00000       -2.49107       -4.86866
      C          0.00000       -1.40234       -7.30441
      C          0.00000        1.40234       -7.30441
      C          0.00000        0.69872       -8.51225
      C          0.00000       -0.69872       -8.51225
      H         -0.00000       -2.48577       -7.32125
      H          0.00000        2.48577       -7.32125
      H          0.00000        1.23799       -9.45070
      H          0.00000       -1.23799       -9.45070
        """)
