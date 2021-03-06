import pulsar as psr
def load_ref_system():
    """ Returns l-threonine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C     -0.1930      0.2189     -2.5854
        C     -0.2309     -0.4041     -1.1920
        C      0.0084      0.6805     -0.0993
        N      1.3896      1.2111     -0.1476
        O      0.6367     -1.5033     -1.0669
        C     -0.3633      0.1341      1.2745
        O      0.3662     -0.0911      2.2236
        O     -1.6804     -0.0998      1.4718
        H     -0.3666     -0.5393     -3.3605
        H      0.7719      0.6972     -2.8029
        H     -0.9721      0.9842     -2.6931
        H     -1.2227     -0.8824     -1.0117
        H     -0.6736      1.5394     -0.3253
        H      2.0454      0.5010      0.1050
        H      1.4740      1.9764      0.4871
        H      1.4868     -1.2480     -1.4048
        H     -1.8189     -0.4638      2.3410
        """)
