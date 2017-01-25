import pulsar as psr
def load_ref_system():
    """ Returns d-idose as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      3.0484     -0.9518     -0.0330
        C      1.9240      0.0982      0.1433
        O      4.2443     -0.5689      0.5859
        H      3.2195     -1.1793     -1.1041
        H      2.7945     -1.8965      0.4784
        H      1.9138      0.4820      1.1913
        C      0.5404     -0.5279     -0.1932
        O      2.1934      1.2705     -0.5882
        H      4.5006      0.2687      0.2192
        C     -0.6258      0.3699      0.3233
        H      0.4759     -1.5199      0.3206
        O      0.5044     -0.7373     -1.5875
        H      2.2274      1.0358     -1.5087
        C     -1.9102     -0.4665      0.5943
        O     -0.9856      1.3928     -0.5773
        H     -0.3101      0.8372      1.2905
        H     -0.3847     -0.9862     -1.8073
        C     -2.9030      0.3767      1.3984
        H     -1.6474     -1.3679      1.1976
        O     -2.4484     -1.0357     -0.5695
        H     -0.1813      1.8117     -0.8571
        O     -4.0159      0.6390      1.0136
        H     -2.5432      0.7403      2.3747
        H     -2.8840     -0.3443     -1.0549
        """)