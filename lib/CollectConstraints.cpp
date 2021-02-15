#include "Andersen.hpp"
#include "Constraint.hpp"
#include "ConstraintGraph.hpp"

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace llvm;

void
Andersen::collectConstraints(const Module &module)
{
    for (const auto &f : module) {
        collectConstraints(f);
    }
}

void
Andersen::collectConstraints(const Function &func)
{
    outs() << "Andersen::collectConstraints(" << func.getName() << ")\n";
    for (const auto &bb : func) {
        for (const auto &ins : bb) {
            if (ins.getType()->isPointerTy()) {
                graph.createValueNode(ins);
            }
        }
    }

    for (const auto &bb : func) {
        for (const auto &ins : bb) {
            collectConstraints(ins);
        }
    }
}

void
Andersen::collectConstraints(const Instruction &ins)
{
    switch(ins.getOpcode()) {
    case Instruction::Alloca: {
        outs() << "Alloca\n";

        NodeIndex value_index = graph.getValueNodeIndex(ins);
        NodeIndex obj_index = graph.createObjNode(ins);
        graph.createConstraint(ConstraintType::ADDR_OF, value_index, obj_index);
        break;
    }
    case Instruction::Load: {
        outs() << "Load\n";
        if (ins.getType()->isPointerTy()) { // load *
            ins.print(outs());
            outs() << '\n';

            NodeIndex src_index = graph.getValueNodeIndex(*ins.getOperand(0));
            NodeIndex value_index = graph.getValueNodeIndex(ins);
            graph.createConstraint(ConstraintType::LOAD, value_index, src_index);
        }
        break;
    }
    case Instruction::Store: {
        outs() << "Store\n";
        if (ins.getOperand(0)->getType()->isPointerTy()) {  // store *, **
            ins.print(outs());
            outs() << '\n';

            NodeIndex src_index = graph.getValueNodeIndex(*ins.getOperand(0));
            NodeIndex dst_index = graph.getValueNodeIndex(*ins.getOperand(1));
            graph.createConstraint(ConstraintType::STORE, dst_index, src_index);
        }
        break;
    }
    case Instruction::Call:
        outs() << "Call\n";
        break;
    case Instruction::Ret:
        outs() << "Ret\n";
        break;
    case Instruction::GetElementPtr:
        outs() << "GetElementPtr\n";
        break;
    default:
        outs() << "default\n";
        break;
    }
}

} // namespace andr