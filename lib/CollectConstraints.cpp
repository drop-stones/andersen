#include "Andersen.hpp"
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
                graph.createValueNode(&ins);
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

        NodeID value_id = graph.getValueNodeID(&ins);
        NodeID obj_id = graph.createObjNode(&ins);
        //graph.createConstraint(ConstraintType::ADDR_OF, value_id, obj_id);
        graph.addConstraintEdge(ConstraintEdgeType::ADDR_OF, obj_id, value_id);
        break;
    }
    case Instruction::Load: {
        outs() << "Load\n";
        if (ins.getType()->isPointerTy()) { // load *
            ins.print(outs());
            outs() << '\n';

            NodeID src_id = graph.getValueNodeID(ins.getOperand(0));
            NodeID value_id = graph.getValueNodeID(&ins);
            //graph.createConstraint(ConstraintType::LOAD, value_id, src_id);
            graph.addConstraintEdge(ConstraintEdgeType::LOAD, src_id, value_id);
        }
        break;
    }
    case Instruction::Store: {
        outs() << "Store\n";
        if (ins.getOperand(0)->getType()->isPointerTy()) {  // store *, **
            ins.print(outs());
            outs() << '\n';

            NodeID src_id = graph.getValueNodeID(ins.getOperand(0));
            NodeID dst_id = graph.getValueNodeID(ins.getOperand(1));
            //graph.createConstraint(ConstraintType::STORE, dst_id, src_id);
            graph.addConstraintEdge(ConstraintEdgeType::STORE, src_id, dst_id);
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