#include "TestCXX.hpp"
#include <pulsar/math/CombItr.hpp>

using Comb_t=std::vector<int>;
using CombItr_t=pulsar::math::CombItr<Comb_t>;

TEST_CLASS(TestCombItr){
    Tester tester("Testing CombItr Class C++ Interface");
    
    Comb_t Com1={1,2,3},Com2;
    std::vector<Comb_t> Corr1={{1},{2},{3}},Corr2={{1,2},{1,3},{2,3}},
            Corr3={{1,2,3}};
    try{
        CombItr_t CItr(Com1,4);
        exit(1);//Constructor should throw
    }
    catch(...){}
    
    CombItr_t CItr(Com1,0);
    std::vector<Comb_t> Combinations,Combinations1,
            Combinations2,Combinations3;
    while(CItr)Combinations.push_back(*CItr++);
    tester.test("Handles N choose 0",0,Combinations.size());
    
    CombItr_t CItr0(Com2,0);
    while(CItr0)Combinations.push_back(*CItr0++);
    tester.test("Handles 0 choose 0",0,Combinations.size());
    
    CombItr_t CItr2(Com1,1);
    CombItr_t CItr3=CItr2;
    while(CItr2)Combinations.push_back(*CItr2++);
    tester.test("Handles N choose 1",Corr1,Combinations);
    
    while(CItr3)Combinations1.push_back(*CItr3++);
    tester.test("Copy handles N choose 1",Corr1,Combinations1);
    
    CombItr_t CItr4(Com1,2);
    while(CItr4)Combinations2.push_back(*CItr4++);
    tester.test("Handles N choose 2",Corr2,Combinations2);
    
    CombItr_t CItr5(Com1,3);
    while(CItr5){
        Combinations3.push_back(*CItr5);
        tester.test("Done works",false,CItr5.done());
        tester.test("Can call members of combination",3,CItr5->size());
        ++CItr5;
    }
    tester.test("Handles N choose N",Corr3,Combinations3);
    
    tester.print_results();
}