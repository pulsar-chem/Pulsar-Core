from TestFxns import *
import numpy as np

tester = Tester("Testing Eigen Matrix Vector Python Interface")

Mat1=np.array([[1.0,2.0,3.0,4.0],[5.0,6.0,7.0,8.0]])
Mat2=np.array([[2.0,3.0,4.0,5.0],[6.0,7.0,8.0,9.0]])
M1=psr.math.EigenMatrixImpl(Mat1)
tester.test("Matrix constructor works",True,True,np.array_equal,Mat1,M1.get_matrix())
M2=psr.math.EigenMatrixImpl(Mat2)
tester.test("Matrix sizes works",True,[2,4],M1.sizes)
tester.test("Matrix get_value works",True,3.0,M1.get_value,[0,2])
M1.set_value([0,2],55.0)
tester.test("Matrix set_value works",True,55.0,M1.get_value,[0,2])
tester.test("Matrix != works",True,True,M1.__ne__,M2)
Mat4=M1.get_matrix()
tester.test("Not an alias of numpy array",True,False,np.array_equal,Mat1,Mat4)
m_hash=[146, 88, 75, 12, 250, 147, 195, 231, 81, 168, 57, 184, 212, 71, 236,168]
tester.test("Matrix Hash Value",True,m_hash,M1.my_hash)


Vec1=np.array([1.0,2.0,3.0,4.0])
Vec2=np.array([2.0,3.0,4.0,5.0])
V1=psr.math.EigenVectorImpl(Vec1)
tester.test("Vector constructor works",True,True,np.array_equal,Vec1,V1.get_matrix())
V2=psr.math.EigenVectorImpl(Vec2)
tester.test("Vector sizes works",True,[4],V1.sizes)
tester.test("Vector get_value works",True,3.0,V1.get_value,[2])
V1.set_value([2],55.0)
tester.test("Vector set_value works",True,55.0,V1.get_value,[2])
tester.test("Vector != works",True,True,V1.__ne__,V2)
Vec4=V1.get_matrix()
tester.test("Not an alias of numpy array",True,False,np.array_equal,Vec1,Vec4)
v_hash=[0, 119, 80, 12, 141, 99, 213, 252, 166, 38, 255, 42, 113, 45, 80, 61]
tester.test("Vector Hash Value",True,v_hash,V1.my_hash)

tester.print_results();