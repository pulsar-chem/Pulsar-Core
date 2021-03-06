import pulsar as psr
def load_ref_system():
    """ Returns c197 as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      C         -0.00000        0.00000        7.06473
      C          0.66844        1.15777        6.48782
      C          0.76053        1.31727        5.02626
      C         -1.33688        0.00000        6.48782
      C         -1.52106        0.00000        5.02626
      C          0.66844       -1.15777        6.48782
      C          0.76053       -1.31727        5.02626
      C          3.09155       -0.00000        4.89187
      C          3.76890        1.12689        4.30138
      C          3.85152        1.28905        2.85545
      C          1.51464       -0.00000        4.48380
      C          1.50171       -0.00000        2.84995
      C          3.76890       -1.12689        4.30138
      C          3.85152       -1.28905        2.85545
      C          6.30621       -0.00000        2.71725
      C          6.99495        1.12731        2.14729
      C          6.67560        1.44777        0.69748
      C          4.63993       -0.00000        2.31440
      C          4.57683       -0.00000        0.71078
      C          6.99495       -1.12731        2.14729
      C          6.67560       -1.44777        0.69748
      C         -1.54577        2.67736        4.89187
      C         -0.90854        3.82741        4.30138
      C         -0.80941        3.98004        2.85545
      C         -2.86036        2.70052        4.30138
      C         -3.04211        2.69099        2.85545
      C         -0.75732        1.31172        4.48380
      C         -0.75086        1.30052        2.84995
      C          1.39780        2.42106        4.30673
      C          1.49508        2.58956        2.86321
      C          2.13520        3.69828        2.19674
      C          2.24513        3.88869        0.76523
      C         -0.02557        2.60743        2.31661
      C         -0.01555        2.60441        0.72359
      C          2.27088        1.28157        2.31661
      C          2.26326        1.28874        0.72359
      C          4.46808        2.41375        2.18822
      C          4.57513        2.61064        0.74605
      C          5.30856        3.74384        0.15995
      C          5.11666        4.19808       -1.27865
      C          3.02141        2.60250        0.20805
      C          3.03152        2.63427       -1.38631
      C          5.31879        1.33509        0.14874
      C          5.05215        1.33488       -1.28995
      C         -3.15311        5.46134        2.71725
      C         -2.52120        6.62146        2.14729
      C         -2.08400        6.50513        0.69748
      C         -4.47375        5.49415        2.14729
      C         -4.59160        5.05736        0.69748
      C         -2.31997        4.01830        2.31440
      C         -2.28841        3.96365        0.71078
      C         -0.14367        5.07635        2.18822
      C         -0.02668        5.26750        0.74605
      C          0.58798        6.46927        0.15995
      C          1.07732        6.53020       -1.27865
      C         -1.50317        5.27376        0.14874
      C         -1.37004        5.04273       -1.28995
      C          0.74312        3.91787        0.20805
      C          0.76559        3.94250       -1.38631
      C          2.89443        5.01329        0.15122
      C          2.98020        5.16186       -1.28348
      C          1.59067        5.32770       -1.92317
      C          1.70755        5.17565       -3.36333
      C          3.81859        4.04141       -1.92317
      C          3.62847        4.06661       -3.36333
      C         -1.54577       -2.67736        4.89187
      C         -0.75732       -1.31172        4.48380
      C         -0.75086       -1.30052        2.84995
      C         -2.86036       -2.70052        4.30138
      C         -3.04211       -2.69099        2.85545
      C         -0.90854       -3.82741        4.30138
      C         -0.80941       -3.98004        2.85545
      C          1.39780       -2.42106        4.30673
      C          1.49508       -2.58956        2.86321
      C          2.27088       -1.28157        2.31661
      C          2.26326       -1.28874        0.72359
      C         -0.02557       -2.60743        2.31661
      C         -0.01555       -2.60441        0.72359
      C          2.13520       -3.69828        2.19674
      C          2.24513       -3.88869        0.76523
      C          4.46808       -2.41375        2.18822
      C          4.57513       -2.61064        0.74605
      C          5.31879       -1.33509        0.14874
      C          5.05215       -1.33488       -1.28995
      C          3.02141       -2.60250        0.20805
      C          3.03152       -2.63427       -1.38631
      C          5.30856       -3.74384        0.15995
      C          5.11666       -4.19808       -1.27865
      C         -2.79560        0.00000        4.30673
      C         -2.99016        0.00000        2.86321
      C         -2.24531        1.32586        2.31661
      C         -2.24771        1.31567        0.72359
      C         -4.27041        0.00000        2.19674
      C         -4.49027        0.00000        0.76523
      C         -2.24531       -1.32586        2.31661
      C         -2.24771       -1.31567        0.72359
      C         -0.00000        0.00000        2.32182
      C         -0.00000        0.00000        0.72886
      C          0.75097        1.30072        0.19870
      C          0.75303        1.30428       -1.38821
      C         -1.50195        0.00000        0.19870
      C         -1.50606        0.00000       -1.38821
      C          0.75097       -1.30072        0.19870
      C          0.75303       -1.30428       -1.38821
      C          3.01790       -0.00000        0.20411
      C          2.99791       -0.00000       -1.38662
      C          3.75903        1.33276       -1.93167
      C          3.55205        1.33196       -3.36754
      C          1.49184       -0.00000       -1.91548
      C          1.49880       -0.00000       -3.52200
      C          3.75903       -1.33276       -1.93167
      C          3.55205       -1.33196       -3.36754
      C         -4.32441        2.66260        2.18822
      C         -4.54845        2.65685        0.74605
      C         -3.81562        3.93866        0.14874
      C         -3.68211        3.70785       -1.28995
      C         -5.89654        2.72543        0.15995
      C         -6.19398        2.33211       -1.27865
      C         -3.76454        1.31537        0.20805
      C         -3.79710        1.30824       -1.38631
      C         -1.50895        2.61358        0.20411
      C         -1.49895        2.59626       -1.38662
      C         -0.72531        3.92179       -1.93167
      C         -0.62251        3.74214       -3.36754
      C         -3.03371        2.58904       -1.93167
      C         -2.92954        2.41018       -3.36754
      C         -0.74592        1.29197       -1.91548
      C         -0.74940        1.29799       -3.52200
      C          1.51182        2.61855       -1.90919
      C          1.52578        2.64272       -3.52336
      C          2.31852        4.01579       -3.95119
      C          0.02062        2.63660       -4.06169
      C          0.13198        2.49320       -5.51487
      C          2.27305        1.33616       -4.06169
      C          2.09319        1.36090       -5.51487
      C         -3.15311       -5.46134        2.71725
      C         -2.31997       -4.01830        2.31440
      C         -2.28841       -3.96365        0.71078
      C         -4.47375       -5.49415        2.14729
      C         -4.59160       -5.05736        0.69748
      C         -2.52120       -6.62146        2.14729
      C         -2.08400       -6.50513        0.69748
      C         -0.14367       -5.07635        2.18822
      C         -0.02668       -5.26750        0.74605
      C          0.74312       -3.91787        0.20805
      C          0.76559       -3.94250       -1.38631
      C         -1.50317       -5.27376        0.14874
      C         -1.37004       -5.04273       -1.28995
      C          0.58798       -6.46927        0.15995
      C          1.07732       -6.53020       -1.27865
      C          2.89443       -5.01329        0.15122
      C          2.98020       -5.16186       -1.28348
      C          3.81859       -4.04141       -1.92317
      C          3.62847       -4.06661       -3.36333
      C          1.59067       -5.32770       -1.92317
      C          1.70755       -5.17565       -3.36333
      C         -4.32441       -2.66260        2.18822
      C         -4.54845       -2.65685        0.74605
      C         -3.76454       -1.31537        0.20805
      C         -3.79710       -1.30824       -1.38631
      C         -5.89654       -2.72543        0.15995
      C         -6.19398       -2.33211       -1.27865
      C         -3.81562       -3.93866        0.14874
      C         -3.68211       -3.70785       -1.28995
      C         -1.50895       -2.61358        0.20411
      C         -1.49895       -2.59626       -1.38662
      C         -0.74592       -1.29197       -1.91548
      C         -0.74940       -1.29799       -3.52200
      C         -3.03371       -2.58904       -1.93167
      C         -2.92954       -2.41018       -3.36754
      C         -0.72531       -3.92179       -1.93167
      C         -0.62251       -3.74214       -3.36754
      C          1.51182       -2.61855       -1.90919
      C          1.52578       -2.64272       -3.52336
      C          2.27305       -1.33616       -4.06169
      C          2.09319       -1.36090       -5.51487
      C          0.02062       -2.63660       -4.06169
      C          0.13198       -2.49320       -5.51487
      C          2.31852       -4.01579       -3.95119
      C         -5.78885        0.00000        0.15122
      C         -5.96040        0.00000       -1.28348
      C         -5.40926        1.28629       -1.92317
      C         -5.33602        1.10904       -3.36333
      C         -5.40926       -1.28629       -1.92317
      C         -5.33602       -1.10904       -3.36333
      C         -3.02364        0.00000       -1.90919
      C         -3.05156        0.00000       -3.52336
      C         -2.29367        1.30044       -4.06169
      C         -2.22516        1.13231       -5.51487
      C         -4.63703        0.00000       -3.95119
      C         -2.29367       -1.30044       -4.06169
      C         -2.22516       -1.13231       -5.51487
      C          0.00000       -0.00000       -4.06453
      C          0.00000       -0.00000       -5.77233
      C          0.77940        1.34996       -6.13263
      C         -1.55879        0.00000       -6.13263
      C          0.77940       -1.34996       -6.13263
        """)
