import pulsar as psr
def load_ref_system():
    """ Returns adenine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        N     -2.2027     -0.0935     -0.0068
        C     -0.9319      0.4989     -0.0046
        C      0.0032     -0.5640     -0.0064
        N     -0.7036     -1.7813     -0.0164
        C     -2.0115     -1.4937     -0.0151
        C      1.3811     -0.2282     -0.0017
        N      1.7207      1.0926     -0.0252
        C      0.7470      2.0612     -0.0194
        N     -0.5782      1.8297     -0.0072
        H      1.0891      3.1044     -0.0278
        N      2.4103     -1.1617      0.1252
        H     -3.0709      0.3774     -0.0035
        H     -2.8131     -2.2379     -0.0191
        H      2.1765     -2.0715     -0.1952
        H      3.3110     -0.8521     -0.1580
        """)