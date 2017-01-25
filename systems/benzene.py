import pulsar as psr
def load_ref_system():
    """ Returns benzene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.2194     -0.1652      2.1600
        C      0.6825     -0.0924      1.2087
        C     -0.7075     -0.0352      1.1973
        H     -1.2644     -0.0630      2.1393
        C     -1.3898      0.0572     -0.0114
        H     -2.4836      0.1021     -0.0204
        C     -0.6824      0.0925     -1.2088
        H     -1.2194      0.1652     -2.1599
        C      0.7075      0.0352     -1.1973
        H      1.2641      0.0628     -2.1395
        C      1.3899     -0.0572      0.0114
        H      2.4836     -0.1022      0.0205
        """)
