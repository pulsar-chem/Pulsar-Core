import pulsar as psr
def load_ref_system():
    """ Returns cyclopentane as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C     -0.8201     -1.0104     -0.1068
        C     -1.2133      0.4696      0.0650
        C      0.0767      1.2934     -0.0981
        H     -1.9775      0.7710     -0.6688
        H     -1.6556      0.6382      1.0619
        C      1.2384      0.3351      0.2162
        H      0.1607      1.6760     -1.1302
        H      0.0840      2.1729      0.5646
        C      0.7195     -1.0852     -0.0760
        H      2.1318      0.5711     -0.3826
        H      1.5369      0.4262      1.2751
        H      1.1066     -1.4485     -1.0430
        H      1.0676     -1.7990      0.6877
        H     -1.2614     -1.6277      0.6925
        H     -1.2089     -1.4114     -1.0576
        """)
