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

        NodeID valueID = graph.getValueNodeID(&ins);
        NodeID objID = graph.createObjNode(&ins);
        graph.addConstraintEdge(ConstraintEdgeType::ADDR_OF, objID, valueID);
        break;
    }
    case Instruction::Load: {
        outs() << "Load\n";
        if (ins.getType()->isPointerTy()) { // load *
            ins.print(outs());
            outs() << '\n';

            NodeID srcID = graph.getValueNodeID(ins.getOperand(0));
            NodeID valueID = graph.getValueNodeID(&ins);
            graph.addConstraintEdge(ConstraintEdgeType::LOAD, srcID, valueID);
        }
        break;
    }
    case Instruction::Store: {
        outs() << "Store\n";
        if (ins.getOperand(0)->getType()->isPointerTy()) {  // store *, **
            ins.print(outs());
            outs() << '\n';

            NodeID srcID = graph.getValueNodeID(ins.getOperand(0));
            NodeID dstID = graph.getValueNodeID(ins.getOperand(1));
            graph.addConstraintEdge(ConstraintEdgeType::STORE, srcID, dstID);
        }
        break;
    }
    case Instruction::Call:
    case Instruction::Invoke: {
        outs() << "Call\n";
        if (const auto *cs = dyn_cast<const CallInst>(&ins)) {
            collectConstraintsForCall(cs);
        }
        break;
    }
    case Instruction::Ret:
        outs() << "Ret\n";
        break;
    case Instruction::GetElementPtr: {
        outs() << "GetElementPtr\n";

        NodeID compositeDataID = graph.getValueNodeID(ins.getOperand(0));
        NodeID fieldID = graph.getValueNodeID(&ins);
        graph.addConstraintEdge(ConstraintEdgeType::VARIANT_GEP, compositeDataID, fieldID);
        break;
    }
    default:
        outs() << "default\n";
        break;
    }
}

void
Andersen::collectConstraintsForCall(const CallInst* call)
{
    if (const Function* f = call->getCalledFunction()) {
        /// Direct call
        // TODO: handle external library functions

        if (f->getReturnType()->isPointerTy()) {
            NodeID retValID = graph.getValueNodeID(call);

            for (const auto &bb : *f) {
                for (const auto &ins : bb) {
                    if (const auto *ret = dyn_cast<const ReturnInst>(&ins)) {
                        NodeID funcRetID = graph.getValueNodeID(ret->getReturnValue());
                        graph.addConstraintEdge(ConstraintEdgeType::COPY, funcRetID, retValID);
                    }
                }
            }
        }
    } else {
        /// Indirect call
    }
}

} // namespace andr