import pulsar as psr
def load_ref_system():
    """ Returns 1h-pyrrole as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        N     -0.9159      0.5838     -0.3356
        C      0.3290      1.1428     -0.0369
        C      1.1676      0.0969      0.3300
        C      0.4250     -1.1121      0.2536
        C     -0.8651     -0.8010     -0.1596
        H      0.5448      2.2081     -0.0983
        H      2.2098      0.1835      0.6244
        H      0.8041     -2.1048      0.4798
        H     -1.7113     -1.4643     -0.3299
        H     -1.7099      1.0897     -0.6265
        """)
