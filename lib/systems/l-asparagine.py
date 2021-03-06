import pulsar as psr
def load_ref_system():
    """ Returns l-asparagine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        O      2.5679     -0.7855      0.1854
        C      1.6592     -0.5713     -0.5945
        O      2.0157     -0.3356     -1.8778
        C      0.1581     -0.5073     -0.3284
        N     -0.2646     -1.8193      0.2126
        C     -0.1205      0.6967      0.5872
        H      0.2719      0.5100      1.6090
        H      0.4350      1.5823      0.2165
        C     -1.6073      0.9802      0.6719
        O     -2.3970      0.3313      1.3521
        N     -2.1328      2.0400     -0.0627
        H     -1.5483      2.6038     -0.6284
        H     -3.1001      2.2533     -0.0260
        H      2.9589     -0.4206     -1.9780
        H     -0.3890     -0.3730     -1.2961
        H     -1.2571     -1.8306      0.3180
        H      0.1690     -1.9854      1.0968
        """)
