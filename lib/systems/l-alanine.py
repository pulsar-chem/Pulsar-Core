import pulsar as psr
def load_ref_system():
    """ Returns l-alanine as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      2.1243     -0.0920      1.6298
        N      1.7374     -0.1422      0.7112
        H      2.0613      0.6335      0.1718
        C      0.2575     -0.1205      0.8106
        H     -0.0277     -1.0425      1.3783
        C     -0.3039      1.1050      1.5253
        H      0.0733      1.1716      2.5550
        H     -0.0396      2.0418      1.0151
        H     -1.3991      1.0613      1.5830
        C     -0.3219     -0.1861     -0.5965
        O     -0.0965      0.5316     -1.5533
        O     -1.2271     -1.1715     -0.7934
        H     -1.5376     -1.1552     -1.6934
        """)
