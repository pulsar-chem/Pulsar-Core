import pulsar as psr
def load_ref_system():
    """ Returns furan as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        O      1.1014      0.0267      0.3041
        C      0.6009      0.1157     -0.9767
        H      1.3427      0.2213     -1.7620
        C     -0.7699      0.0473     -0.9565
        H     -1.4514      0.0888     -1.8007
        C     -1.1485     -0.0937      0.4268
        H     -2.1639     -0.1763      0.8025
        C      0.0194     -0.1007      1.1480
        H      0.2580     -0.1826      2.2037
        """)