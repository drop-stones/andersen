
#include "ConstraintNode.hpp"

namespace andr {

using namespace std;
using namespace llvm;

ConstraintNode::ConstraintNode(NodeType ty, NodeID id, const Value* v)
    : type{ty}, nodeID{id}, value{v} {}

NodeID
ConstraintNode::getNodeID() const
{
    return nodeID;
}

void
ConstraintNode::addPtsToSet(NodeID i)
{
    ptsToSet.insert(i);
}

void
ConstraintNode::addConstraintEdge(ConstraintEdgeType type, NodeID dst, EdgeID id)
{
    switch(type) {
    case ConstraintEdgeType::ADDR_OF:       addAddrEdge(dst, id);           break;
    case ConstraintEdgeType::COPY:          addCopyEdge(dst, id);           break;
    case ConstraintEdgeType::LOAD:          addLoadEdge(dst, id);           break;
    case ConstraintEdgeType::STORE:         addStoreEdge(dst, id);          break;
    case ConstraintEdgeType::CONSTANT_GEP:  addConstantGepEdge(dst, id);    break;
    case ConstraintEdgeType::VARIANT_GEP:   addVariantGepEdge(dst, id);     break;
    default:                                outs() << "Invalid Type";       break;
    }
}

void
ConstraintNode::addAddrEdge(NodeID dst, EdgeID id)
{
    addrEdges.emplace(ConstraintEdgeType::ADDR_OF, nodeID, dst, id);
}

void
ConstraintNode::addCopyEdge(NodeID dst, EdgeID id)
{
    copyEdges.emplace(ConstraintEdgeType::COPY, nodeID, dst, id);
}

void
ConstraintNode::addLoadEdge(NodeID dst, EdgeID id)
{
    loadEdges.emplace(ConstraintEdgeType::LOAD, nodeID, dst, id);
}

void
ConstraintNode::addStoreEdge(NodeID dst, EdgeID id)
{
    storeEdges.emplace(ConstraintEdgeType::STORE, nodeID, dst, id);
}

void
ConstraintNode::addConstantGepEdge(NodeID dst, EdgeID id)
{
    constantGepEdges.emplace(ConstraintEdgeType::CONSTANT_GEP, nodeID, dst, id);
}

void
ConstraintNode::addVariantGepEdge(NodeID dst, EdgeID id)
{
    variantGepEdges.emplace(ConstraintEdgeType::VARIANT_GEP, nodeID, dst, id);
}


void
ConstraintNode::print() const
{
    outs() << "NodeType: " << type << "\tNodeID: " << nodeID << "\t";
    value->print(outs(), true);
    outs() << '\n';
}

void
ConstraintNode::printPtsToSet() const
{
    print();
    outs() << " points-to:\n";
    for (const auto &pts : ptsToSet) {
        outs() << "\t- " << pts << "\n";
    }
}


} // namespace andr