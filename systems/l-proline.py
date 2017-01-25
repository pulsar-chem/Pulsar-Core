import pulsar as psr
def load_ref_system():
    """ Returns l-proline as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H      0.1496     -0.6313      1.7128
        C      0.1233     -0.1937      0.6852
        C     -0.9235     -0.9400     -0.1273
        O     -0.8714     -1.3378     -1.2775
        O     -2.0780     -1.1965      0.5296
        H     -2.6819     -1.6580     -0.0443
        N      1.5084     -0.3315      0.1439
        C      1.9714      0.9925     -0.3578
        H      2.8468      1.2751      0.2579
        H      2.3293      0.9389     -1.4038
        C      0.8210      1.9825     -0.1956
        H      0.3659      2.2269     -1.1743
        H      1.1678      2.9469      0.2175
        C     -0.1925      1.3098      0.7247
        H     -1.2330      1.5283      0.4219
        H     -0.1004      1.6897      1.7599
        H      1.5661     -1.0319     -0.5628
        """)
