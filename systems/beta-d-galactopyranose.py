import pulsar as psr
def load_ref_system():
    """ Returns beta-d-galactopyranose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      0.2723      1.3545     -0.8489
        O     -0.9316      0.9726     -0.1689
        C     -1.2766     -0.4323     -0.1279
        C     -0.1046     -1.3451      0.2892
        C      1.2130     -0.9681     -0.4253
        C      1.4835      0.5427     -0.3223
        O      2.6056      0.7608     -1.1862
        O      2.2057     -1.7025      0.3055
        O      0.0487     -1.2082      1.7057
        C     -2.4239     -0.4627      0.9000
        O     -3.6784     -0.4727      0.2189
        O      0.4159      2.7131     -0.4959
        H     -1.6397     -0.7088     -1.1457
        H     -0.3548     -2.4153      0.0839
        H      1.2370     -1.3064     -1.4861
        H      1.7480      0.8419      0.7170
        H      0.1500      1.3308     -1.9494
        H      0.0247      2.8803      0.4000
        H      2.8510      1.7166     -1.1796
        H      3.1068     -1.4014      0.0331
        H      0.9262     -1.5891      1.9784
        H     -2.3543      0.4019      1.5872
        H     -2.4355     -1.4027      1.4870
        H     -3.8609      0.4078     -0.1741
        """)
