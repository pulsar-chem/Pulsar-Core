import pulsar as psr
def load_ref_system():
    """ Returns glycine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      0.1622     -1.0628      1.5533
        C      0.3567     -0.0905      1.0501
        H     -0.0181      0.6975      1.7355
        N      1.7875      0.1811      0.7976
        H      2.2858      0.1158      1.6592
        H      2.1579     -0.4801      0.1480
        C     -0.4086     -0.0874     -0.2553
        O     -0.1765     -0.7075     -1.2773
        O     -1.5162      0.6883     -0.2681
        H     -1.9411      0.6382     -1.1188
        """)
