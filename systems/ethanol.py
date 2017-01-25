import pulsar as psr
def load_ref_system():
    """ Returns ethanol as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.8853     -0.0401      1.0854
        C      1.2699     -0.0477      0.1772
        H      1.5840      0.8007     -0.4449
        H      1.5089     -0.9636     -0.3791
        C     -0.2033      0.0282      0.5345
        H     -0.4993     -0.8287      1.1714
        H     -0.4235      0.9513      1.1064
        O     -0.9394      0.0157     -0.6674
        H     -1.8540      0.0626     -0.4252
        """)
