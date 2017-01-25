import pulsar as psr
def load_ref_system():
    """ Returns l-lysine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        N      1.1027     -2.1223      0.2103
        C      0.8799     -0.9837     -0.7101
        C      2.1653     -0.5233     -1.3940
        O      2.0015      0.1019     -2.5808
        C      0.2612      0.2130      0.0260
        C     -1.1667     -0.0696      0.4666
        C     -1.7674      1.1389      1.1684
        C     -3.1924      0.8435      1.6233
        N     -3.7558      1.9940      2.3635
        O      3.3165     -0.6536     -1.0164
        H      1.6562     -1.8371      0.9909
        H      1.5630     -2.8629     -0.2743
        H      0.1669     -1.3483     -1.4928
        H      2.8473      0.3657     -2.9306
        H      0.2731      1.0970     -0.6439
        H      0.8809      0.4945      0.9025
        H     -1.1933     -0.9499      1.1397
        H     -1.7864     -0.3461     -0.4106
        H     -1.7516      2.0153      0.4883
        H     -1.1378      1.4238      2.0355
        H     -3.2011     -0.0264      2.3108
        H     -3.8121      0.5488      0.7478
        H     -4.6963      1.7877      2.6259
        H     -3.7507      2.8057      1.7814
        """)
