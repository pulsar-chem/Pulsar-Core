import pulsar as psr
def load_ref_system():
    """ Returns toluene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.2264      0.0427      0.0670
        C      1.0031     -1.3293      0.0600
        C     -0.2945     -1.8256     -0.0060
        C     -1.3704     -0.9461     -0.0646
        C     -1.1511      0.4266     -0.0578
        C      0.1497      0.9292      0.0066
        C      0.3871      2.3956     -0.0022
        H      2.2495      0.4310      0.1211
        H      1.8510     -2.0202      0.1071
        H     -0.4688     -2.9062     -0.0109
        H     -2.3926     -1.3347     -0.1157
        H     -2.0006      1.1172     -0.1021
        H      0.5024      2.7582     -1.0330
        H      1.2994      2.6647      0.5466
        H     -0.4475      2.9470      0.4506
        """)
