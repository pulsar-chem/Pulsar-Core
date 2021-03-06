import pulsar as psr
def load_ref_system():
    """ Returns nitrobenzene as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
        C      1.1584      2.3244      0.0000
        C      1.9309      1.1623      0.0000
        C      1.3210     -0.0901      0.0000
        C     -0.0817     -0.1642      0.0000
        C     -0.8671      1.0003      0.0000
        C     -0.2344      2.2416      0.0000
        N     -0.7449     -1.4946      0.0000
        O     -0.0637     -2.4850      0.0000
        O     -1.9459     -1.5466      0.0000
        H      1.6495      3.3098      0.0000
        H      3.0297      1.2298      0.0000
        H      1.9275     -1.0118      0.0000
        H     -1.9682      0.9300      0.0000
        H     -0.8425      3.1591      0.0000
        """)
