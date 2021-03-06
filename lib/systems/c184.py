import pulsar as psr
def load_ref_system():
    """ Returns c184 as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C          6.13980        0.91989        0.91989
      C          6.13980       -0.91989       -0.91989
      C          4.51033       -2.70065        2.70065
      C          2.70065       -2.70065        4.51033
      C          2.70065       -4.51033        2.70065
      C          4.50384       -2.68991       -1.00195
      C          3.63665       -3.63665        1.91519
      C          2.75142       -2.75142        0.90692
      C          2.68991       -4.50384       -1.00195
      C          3.58581       -3.58581       -1.73023
      C          2.74937       -2.74937       -2.74937
      C          4.50384        1.00195        2.68991
      C          2.68991        1.00195        4.50384
      C          3.63665       -1.91519        3.63665
      C          2.75142       -0.90692        2.75142
      C          5.20270       -1.82733        1.82733
      C          4.55920       -0.89513        0.89513
      C          5.50065        0.00000       -0.00000
      C          4.55920        0.89513       -0.89513
      C          3.64574        0.00387        1.82340
      C          2.71698        0.89885        0.89885
      C          3.64574       -1.82340       -0.00387
      C          2.71698       -0.89885       -0.89885
      C          5.38912       -1.77912       -1.77912
      C          4.50384       -1.00195       -2.68991
      C          3.64574       -0.00387       -1.82340
      C          2.75142        0.90692       -2.75142
      C          3.58581       -1.73023       -3.58581
      C          2.68991       -1.00195       -4.50384
      C          3.58581        1.73023        3.58581
      C          2.74937        2.74937        2.74937
      C          5.38912        1.77912        1.77912
      C          4.50384        2.68991        1.00195
      C          3.58581        3.58581        1.73023
      C          2.68991        4.50384        1.00195
      C          3.64574        1.82340        0.00387
      C          2.75142        2.75142       -0.90692
      C          5.20270        1.82733       -1.82733
      C          4.51033        2.70065       -2.70065
      C          3.63665        3.63665       -1.91519
      C          2.70065        4.51033       -2.70065
      C          3.63665        1.91519       -3.63665
      C          2.70065        2.70065       -4.51033
      C          0.91989       -6.13980       -0.91989
      C         -0.91989       -6.13980        0.91989
      C          1.91519       -3.63665        3.63665
      C          0.90692       -2.75142        2.75142
      C         -1.00195       -2.68991        4.50384
      C         -1.00195       -4.50384        2.68991
      C          1.82733       -5.20270        1.82733
      C          0.89513       -4.55920        0.89513
      C          1.82340       -3.64574       -0.00387
      C          0.89885       -2.71698       -0.89885
      C         -0.00387       -3.64574        1.82340
      C         -0.89885       -2.71698        0.89885
      C          0.00000       -5.50065       -0.00000
      C         -0.89513       -4.55920       -0.89513
      C          1.77912       -5.38912       -1.77912
      C          1.00195       -4.50384       -2.68991
      C          1.73023       -3.58581       -3.58581
      C          1.00195       -2.68991       -4.50384
      C          0.00387       -3.64574       -1.82340
      C         -0.90692       -2.75142       -2.75142
      C          0.91989        0.91989        6.13980
      C         -0.91989       -0.91989        6.13980
      C          1.82733       -1.82733        5.20270
      C          0.89513       -0.89513        4.55920
      C          1.82340        0.00387        3.64574
      C          0.89885        0.89885        2.71698
      C          0.00000       -0.00000        5.50065
      C         -0.89513        0.89513        4.55920
      C         -0.00387       -1.82340        3.64574
      C         -0.89885       -0.89885        2.71698
      C          1.81867       -1.81867        1.81867
      C          0.90902       -0.90902        0.90902
      C          1.81443        0.00000       -0.00000
      C          0.90902        0.90902       -0.90902
      C          0.00000       -0.00000        1.81443
      C         -0.90902        0.90902        0.90902
      C          0.00000       -1.81443       -0.00000
      C         -0.90902       -0.90902       -0.90902
      C          1.80882       -1.80882       -1.80882
      C          0.89885       -0.89885       -2.71698
      C          1.82340       -0.00387       -3.64574
      C          0.89513        0.89513       -4.55920
      C         -0.00000        0.00000       -1.81443
      C         -0.89885        0.89885       -2.71698
      C          0.00387       -1.82340       -3.64574
      C         -0.89513       -0.89513       -4.55920
      C          1.77912       -1.77912       -5.38912
      C          0.91989       -0.91989       -6.13980
      C         -0.00000        0.00000       -5.50065
      C         -0.91989        0.91989       -6.13980
      C          1.77912        1.77912        5.38912
      C          1.00195        2.68991        4.50384
      C          1.73023        3.58581        3.58581
      C          1.00195        4.50384        2.68991
      C          0.00387        1.82340        3.64574
      C         -0.90692        2.75142        2.75142
      C          1.80882        1.80882        1.80882
      C          0.89885        2.71698        0.89885
      C          1.82340        3.64574        0.00387
      C          0.89513        4.55920       -0.89513
      C          0.00387        3.64574        1.82340
      C         -0.89513        4.55920        0.89513
      C         -0.00000        1.81443        0.00000
      C         -0.89885        2.71698       -0.89885
      C          1.81867        1.81867       -1.81867
      C          0.90692        2.75142       -2.75142
      C          1.91519        3.63665       -3.63665
      C         -0.00387        3.64574       -1.82340
      C         -1.00195        4.50384       -2.68991
      C         -0.00387        1.82340       -3.64574
      C         -1.00195        2.68991       -4.50384
      C          1.82733        1.82733       -5.20270
      C          1.77912        5.38912        1.77912
      C          0.91989        6.13980        0.91989
      C         -0.00000        5.50065        0.00000
      C         -0.91989        6.13980       -0.91989
      C          1.82733        5.20270       -1.82733
      C         -1.73023       -3.58581        3.58581
      C         -2.74937       -2.74937        2.74937
      C         -1.77912       -5.38912        1.77912
      C         -2.68991       -4.50384        1.00195
      C         -1.82340       -3.64574        0.00387
      C         -2.75142       -2.75142       -0.90692
      C         -3.58581       -3.58581        1.73023
      C         -4.50384       -2.68991        1.00195
      C         -1.82733       -5.20270       -1.82733
      C         -2.70065       -4.51033       -2.70065
      C         -1.91519       -3.63665       -3.63665
      C         -2.70065       -2.70065       -4.51033
      C         -3.63665       -3.63665       -1.91519
      C         -4.51033       -2.70065       -2.70065
      C         -1.77912       -1.77912        5.38912
      C         -2.68991       -1.00195        4.50384
      C         -1.82340       -0.00387        3.64574
      C         -2.75142        0.90692        2.75142
      C         -3.58581       -1.73023        3.58581
      C         -4.50384       -1.00195        2.68991
      C         -1.80882       -1.80882        1.80882
      C         -2.71698       -0.89885        0.89885
      C         -1.81443       -0.00000        0.00000
      C         -2.71698        0.89885       -0.89885
      C         -3.64574       -0.00387        1.82340
      C         -4.55920        0.89513        0.89513
      C         -3.64574       -1.82340        0.00387
      C         -4.55920       -0.89513       -0.89513
      C         -1.81867       -1.81867       -1.81867
      C         -2.75142       -0.90692       -2.75142
      C         -1.82340        0.00387       -3.64574
      C         -2.68991        1.00195       -4.50384
      C         -3.64574        0.00387       -1.82340
      C         -4.50384        1.00195       -2.68991
      C         -3.63665       -1.91519       -3.63665
      C         -1.82733       -1.82733       -5.20270
      C         -1.82733        1.82733        5.20270
      C         -2.70065        2.70065        4.51033
      C         -1.91519        3.63665        3.63665
      C         -2.70065        4.51033        2.70065
      C         -3.63665        1.91519        3.63665
      C         -4.51033        2.70065        2.70065
      C         -1.81867        1.81867        1.81867
      C         -2.75142        2.75142        0.90692
      C         -1.82340        3.64574       -0.00387
      C         -2.68991        4.50384       -1.00195
      C         -3.63665        3.63665        1.91519
      C         -3.64574        1.82340       -0.00387
      C         -4.50384        2.68991       -1.00195
      C         -1.80882        1.80882       -1.80882
      C         -2.74937        2.74937       -2.74937
      C         -1.73023        3.58581       -3.58581
      C         -3.58581        3.58581       -1.73023
      C         -3.58581        1.73023       -3.58581
      C         -1.77912        1.77912       -5.38912
      C         -1.82733        5.20270        1.82733
      C         -1.77912        5.38912       -1.77912
      C         -5.38912       -1.77912        1.77912
      C         -6.13980       -0.91989        0.91989
      C         -5.50065       -0.00000        0.00000
      C         -6.13980        0.91989       -0.91989
      C         -5.20270       -1.82733       -1.82733
      C         -5.20270        1.82733        1.82733
      C         -5.38912        1.77912       -1.77912
        """)
