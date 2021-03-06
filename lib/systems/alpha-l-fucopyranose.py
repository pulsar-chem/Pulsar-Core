import pulsar as psr
def load_ref_system():
    """ Returns alpha-l-fucopyranose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      0.3034      0.5630     -1.4201
        O     -0.9595     -0.0740     -1.3035
        C     -1.6127      0.0727     -0.0046
        C     -2.9359     -0.6463     -0.1770
        C     -0.6986     -0.5615      1.0622
        O     -0.5158     -1.9645      0.8411
        C      0.7060      0.0984      1.0742
        O      1.5365     -0.6323      1.9635
        C      1.3326      0.1278     -0.3436
        O      2.4353      1.0154     -0.4197
        O      0.1267      1.9603     -1.1997
        H     -1.7417      1.1629      0.1826
        H     -1.1539     -0.5280      2.0797
        H      0.6865      1.1216      1.5151
        H      1.7881     -0.8587     -0.5961
        H      0.6092      0.3499     -2.4645
        H     -0.4833      2.3514     -1.8583
        H      2.1442      1.9472     -0.2470
        H      1.4224     -1.6076      1.8151
        H     -0.4414     -2.1449     -0.1285
        H     -2.8426     -1.7297     -0.0087
        H     -3.6968     -0.2694      0.5158
        H     -3.3177     -0.5162     -1.2013
        """)
