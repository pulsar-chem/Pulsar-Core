import pulsar as psr
def load_ref_system():
    """ Returns aniline as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      1.5205     -0.1372      2.5286
        C      0.9575     -0.0905      1.5914
        C     -0.4298     -0.1902      1.6060
        H     -0.9578     -0.3156      2.5570
        C     -1.1520     -0.1316      0.4215
        H     -2.2452     -0.2104      0.4492
        C     -0.4779      0.0324     -0.7969
        N     -1.2191      0.2008     -2.0081
        H     -2.0974     -0.2669     -1.9681
        H     -0.6944     -0.0913     -2.8025
        C      0.9208      0.1292     -0.8109
        H      1.4628      0.2560     -1.7555
        C      1.6275      0.0685      0.3828
        H      2.7196      0.1470      0.3709
        """)