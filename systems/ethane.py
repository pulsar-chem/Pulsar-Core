import pulsar as psr
def load_ref_system():
    """ Returns ethane as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.1851     -0.0039      0.9875
        C      0.7516     -0.0225     -0.0209
        H      1.1669      0.8330     -0.5693
        H      1.1155     -0.9329     -0.5145
        C     -0.7516      0.0225      0.0209
        H     -1.1669     -0.8334      0.5687
        H     -1.1157      0.9326      0.5151
        H     -1.1850      0.0044     -0.9875
        """)
