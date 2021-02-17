set(AndersenSourceCodes
        Andersen.cpp
        ConstraintGraph.cpp
        ConstraintNode.cpp
        ConstraintEdge.cpp
        CollectConstraints.cpp
        SolveConstraints.cpp
        Types.cpp
)

add_library(Andersen STATIC ${AndersenSourceCodes})
target_include_directories(Andersen PUBLIC ${andersen_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})
target_link_libraries(Andersen PUBLIC ${LLVM_LIBS})
# compile options
target_compile_options(Andersen PUBLIC -fsanitize=address)
target_link_options(Andersen PUBLIC -fsanitize=address)