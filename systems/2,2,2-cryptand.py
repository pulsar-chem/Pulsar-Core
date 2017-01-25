import pulsar as psr
def load_ref_system():
    """ Returns 2,2,2-cryptand as found in the IQMol fragment library.
        All credit to https://github.com/nutjunkie/IQmol
    """
    return psr.make_system("""
      N         -0.00000        0.00000       -2.98155
      N          0.00000       -0.00000        3.16319
      C         -0.97524        1.01436       -3.44434
      C         -2.24705        1.07574       -2.57745
      O         -2.06154        1.99754       -1.49735
      C         -3.19726        2.06024       -0.62698
      C         -3.19923        0.95287        0.43147
      O         -2.34178        1.31957        1.51675
      C         -2.39172        0.35093        2.57125
      C         -1.26497        0.63008        3.58033
      C          1.36608        0.33740       -3.44434
      C          2.05514        1.40813       -2.57745
      O          2.76069        0.78658       -1.49735
      C          3.38285        1.73878       -0.62698
      C          2.42483        2.29418        0.43147
      O          2.31367        1.36826        1.51675
      C          1.49977        1.89583        2.57125
      C          1.17816        0.78046        3.58033
      C         -0.39084       -1.35176       -3.44434
      C          0.19190       -2.48387       -2.57745
      O         -0.69915       -2.78412       -1.49735
      C         -0.18560       -3.79903       -0.62698
      C          0.77440       -3.24705        0.43147
      O          0.02811       -2.68783        1.51675
      C          0.89195       -2.24676        2.57125
      C          0.08682       -1.41054        3.58033
      H         -1.25218        0.80226       -4.48539
      H         -0.52380        2.01367       -3.43782
      H         -3.06898        1.44835       -3.20054
      H         -2.53111        0.08897       -2.19989
      H         -4.11589        2.02057       -1.22378
      H         -3.16079        3.03809       -0.13508
      H         -4.21668        0.83859        0.82217
      H         -2.85928        0.00003        0.01451
      H         -3.35812        0.45709        3.07752
      H         -2.32765       -0.66597        2.16690
      H         -1.55076        0.26937        4.57635
      H         -1.14882        1.71836        3.65871
      H          1.32086        0.68329       -4.48539
      H          2.00579       -0.55321       -3.43782
      H          2.78880        1.93364       -3.20054
      H          1.34261        2.14752       -2.19989
      H          3.80781        2.55418       -1.22378
      H          4.21146        1.21827       -0.13508
      H          2.83458        3.23246        0.82217
      H          1.42967        2.47620        0.01451
      H          2.07492        2.67967        3.07752
      H          0.58708        2.34879        2.16690
      H          1.00866        1.20831        4.57635
      H          2.06255        0.13573        3.65871
      H         -0.06869       -1.48555       -4.48539
      H         -1.48199       -1.46046       -3.43782
      H          0.28018       -3.38200       -3.20054
      H          1.18850       -2.23649       -2.19989
      H          0.30808       -4.57475       -1.22378
      H         -1.05067       -4.25637       -0.13508
      H          1.38210       -4.07105        0.82217
      H          1.42962       -2.47623        0.01451
      H          1.28321       -3.13677        3.07752
      H          1.74057       -1.68282        2.16690
      H          0.54209       -1.47768        4.57635
      H         -0.91373       -1.85409        3.65871
        """)
