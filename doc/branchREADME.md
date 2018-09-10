Cmake is prepared for profiling:
    
    set_target_properties(TestDataModel PROPERTIES COMPILE_FLAGS "-pg")
    set_target_properties(TestDataModel PROPERTIES LINK_FLAGS "-pg")
    
For short executations one can add runtimes together by:
    
    for i in `seq 1 100`; do
    fastprog
    mv gmon.out gmon.out.$i
    done
    gprof -s fastprog gmon.out.*
    gprof fastprog gmon.sum
