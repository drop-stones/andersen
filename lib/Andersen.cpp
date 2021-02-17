#include "Andersen.hpp"

#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace andr {

Andersen::Andersen() {}

bool Andersen::runOnModule(const Module &module)
{
    llvm::outs() << "Andersen::runOnModule\n";

    collectConstraints(module);
    graph.print(outs());

    graph.solveConstraints();
    graph.printPtsToSets(outs());

    return false;
}

} // namespace andr