import pulsar as psr
def load_ref_system():
    """ Returns decanoic_acid as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C     -0.0234      0.5102     -0.2759
        C      0.0360     -0.8188      0.4595
        C     -0.5244     -1.9439     -0.3963
        C     -0.4624     -3.2691      0.3451
        C     -1.0052     -4.4129     -0.4693
        O     -1.4689     -4.4299     -1.5950
        O     -0.9681     -5.6150      0.1584
        H     -1.0699      0.7368     -0.5638
        H      0.5379      0.4404     -1.2296
        C      0.5369      1.6384      0.5751
        H     -0.5268     -0.7494      1.4125
        H      1.0824     -1.0454      0.7481
        H      0.0374     -2.0137     -1.3494
        H     -1.5704     -1.7178     -0.6854
        H     -1.0309     -3.2069      1.2958
        H      0.5831     -3.5018      0.6341
        H     -1.3249     -6.2881     -0.4127
        C      0.4780      2.9661     -0.1628
        H      1.5831      1.4117      0.8641
        H     -0.0254      1.7095      1.5281
        C      1.0374      4.0964      0.6857
        H     -0.5683      3.1921     -0.4517
        H      1.0400      2.8945     -1.1160
        C      0.9804      5.4240     -0.0533
        H      2.0833      3.8709      0.9764
        H      0.4744      4.1703      1.6379
        C      1.5357      6.5507      0.7883
        H     -0.0652      5.6486     -0.3438
        H      1.5430      5.3497     -1.0052
        H      2.5838      6.3724      1.0634
        H      0.9708      6.6754      1.7218
        H      1.4958      7.5065      0.2506
        """)