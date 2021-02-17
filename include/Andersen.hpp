#pragma once

#include "ConstraintGraph.hpp"

#include <llvm/IR/Module.h>
#include <map>

namespace andr {

class Andersen {
public:
    static char ID;
    Andersen();
    bool runOnModule(const llvm::Module &module);

private:
    void collectConstraints(const llvm::Module &module);
    void collectConstraints(const llvm::Function &func);
    void collectConstraints(const llvm::Instruction &ins);

    ConstraintGraph graph;
};

} // namespace andr
