import pulsar as psr
def load_ref_system():
    """ Returns d-proline as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        H     -0.5259      0.8856     -1.3203
        C     -0.1604      0.3169     -0.4263
        C     -0.7325     -1.0840     -0.5650
        O     -0.3760     -1.9705     -1.3227
        O     -1.8076     -1.3840      0.2014
        H     -2.0718     -2.2847      0.0363
        N      1.3332      0.2242     -0.3979
        C      1.8616      1.2555      0.5362
        H      2.4984      0.7232      1.2683
        H      2.5175      1.9878      0.0264
        C      0.6628      1.9276      1.2028
        H      0.5326      2.9636      0.8360
        H      0.7994      2.0166      2.2957
        C     -0.5485      1.0663      0.8556
        H     -1.4617      1.6716      0.7118
        H     -0.7788      0.3685      1.6834
        H      1.7192      0.3058     -1.3116
        """)
