import pulsar as psr
def load_ref_system():
    """ Returns d-aspartic_acid as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.1749      0.2716     -0.8816
        C      0.2902     -0.3063     -0.5085
        C     -0.6411     -0.5180     -1.7035
        O     -0.8069      0.2223     -2.6543
        O     -1.3677     -1.6581     -1.7034
        H     -1.9153     -1.6984     -2.4819
        C     -0.4682      0.5172      0.5398
        C      0.4146      0.9504      1.6942
        H     -0.9011      1.4221      0.0654
        N      0.8376     -1.5441      0.0868
        H      1.2665     -2.1008     -0.6201
        H      0.1218     -2.0662      0.5461
        O      1.4697      1.7781      1.5170
        O      0.2747      0.6686      2.8640
        H     -1.3307     -0.0569      0.9378
        H      1.5926      1.9741      0.5965
        """)
