import pulsar as psr
def load_ref_system():
    """ Returns dimethyl_sulfoxide as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.5407     -0.3295      0.0798
        S     -0.0596      0.4296     -0.3610
        C     -0.9467     -1.1596     -0.4976
        O     -0.4670      0.6286      1.1081
        H      2.2637      0.4718      0.3373
        H      1.9354     -0.8892     -0.7935
        H      1.4455     -1.0221      0.9435
        H     -0.5613     -1.7221     -1.3732
        H     -2.0263     -0.9599     -0.6580
        H     -0.8255     -1.7803      0.4161
        """)
