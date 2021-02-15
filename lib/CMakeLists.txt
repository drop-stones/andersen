set(AndersenSourceCodes
        Andersen.cpp
        ConstraintGraph.cpp
        Constraint.cpp
        CollectConstraints.cpp
        Types.cpp
)

add_library(Andersen STATIC ${AndersenSourceCodes})
target_include_directories(Andersen PUBLIC ${andersen_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})
target_link_libraries(Andersen PUBLIC ${LLVM_LIBS})