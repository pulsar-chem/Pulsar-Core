import pulsar as psr
def load_ref_system():
    """ Returns 1_3-thiazole as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.1132      0.2231     -0.4747
        C      0.8191     -1.1118     -0.5272
        H      2.0347      0.6814     -0.8299
        H      1.4416     -1.9170     -0.9226
        S     -0.1701      1.1369      0.2359
        C     -1.0745     -0.3455      0.4400
        N     -0.4473     -1.4266      0.0043
        H     -2.0693     -0.4013      0.8841
        """)
