import pulsar as psr
def load_ref_system():
    """ Returns beta-d-fructopyranose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.5157     -1.4350     -0.0968
        C      1.0362     -0.0041     -0.4099
        O     -0.0001     -0.0908     -1.4209
        C     -1.3206     -0.4276     -0.9611
        C     -1.7712      0.5546      0.1317
        O     -2.9968      0.0291      0.6667
        C     -0.7807      0.5568      1.3181
        O     -0.7170     -0.7388      1.9299
        C      0.6584      0.8356      0.8364
        O      0.6865      2.2377      0.5675
        O      2.0241      0.7619     -1.0702
        O      1.6679     -2.1687     -1.3108
        H     -1.3335     -1.4683     -0.5878
        H     -1.9212     -0.3457     -1.8848
        H      1.3883      0.6507      1.6627
        H     -1.0841      1.3006      2.0905
        H     -1.9031      1.5836     -0.2644
        H      0.8039     -1.9539      0.5785
        H      2.5298     -1.4460      0.3475
        H      2.2237      0.3715     -1.9608
        H      1.1820      2.4227     -0.2754
        H     -1.6371     -1.0579      2.1114
        H     -3.7576      0.5868      0.4130
        H      0.8459     -2.0839     -1.8554
        """)
