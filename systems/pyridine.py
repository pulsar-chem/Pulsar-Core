import pulsar as psr
def load_ref_system():
    """ Returns pyridine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.3603      0.0256      0.0000
        C      0.6971     -1.2020      0.0000
        C     -0.6944     -1.2184      0.0000
        C     -1.3895     -0.0129      0.0000
        C     -0.6712      1.1834      0.0000
        N      0.6816      1.1960      0.0000
        H      2.4530      0.1083      0.0000
        H      1.2665     -2.1365      0.0000
        H     -1.2365     -2.1696      0.0000
        H     -2.4837      0.0011      0.0000
        H     -1.1569      2.1657      0.0000
        """)
