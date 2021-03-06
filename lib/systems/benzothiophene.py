import pulsar as psr
def load_ref_system():
    """ Returns benzothiophene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      2.4545     -0.4276      0.0040
        C      1.9226     -1.7241     -0.0027
        C      0.5539     -1.9272     -0.0068
        C     -0.2926     -0.8146     -0.0041
        C      1.6270      0.6826      0.0067
        C      0.2438      0.4921      0.0026
        C     -1.7403     -0.8098     -0.0075
        C     -2.2486      0.4476     -0.0034
        H      3.5415     -0.2939      0.0071
        H      2.6019     -2.5830     -0.0047
        H      0.1292     -2.9362     -0.0120
        H      2.0455      1.6946      0.0119
        H     -2.3239     -1.7311     -0.0127
        H     -3.3064      0.7067     -0.0048
        S     -1.0285      1.6903      0.0047
        """)
