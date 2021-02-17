
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

bool
ConstraintNode::addPtsToSet(NodeID i)
{
    const auto isNew = ptsToSet.insert(i);
    return isNew.second;
}

bool
ConstraintNode::addConstraintEdge(ConstraintEdgeType type, NodeID dst, EdgeID id)
{
    switch(type) {
    case ConstraintEdgeType::ADDR_OF:       return addAddrEdge(dst, id); 
    case ConstraintEdgeType::COPY:          return addCopyEdge(dst, id); 
    case ConstraintEdgeType::LOAD:          return addLoadEdge(dst, id); 
    case ConstraintEdgeType::STORE:         return addStoreEdge(dst, id);
    case ConstraintEdgeType::CONSTANT_GEP:  return addConstantGepEdge(dst, id);
    case ConstraintEdgeType::VARIANT_GEP:   return addVariantGepEdge(dst, id); 
    default:    errs() << "Invalid Type";   return false;
    }
}

bool
ConstraintNode::addAddrEdge(NodeID dst, EdgeID id)
{
    const auto isNew = addrEdges.emplace(ConstraintEdgeType::ADDR_OF, nodeID, dst, id);
    return isNew.second;
}

bool
ConstraintNode::addCopyEdge(NodeID dst, EdgeID id)
{
    const auto isNew = copyEdges.emplace(ConstraintEdgeType::COPY, nodeID, dst, id);
    return isNew.second;
}

bool
ConstraintNode::addLoadEdge(NodeID dst, EdgeID id)
{
    const auto isNew = loadEdges.emplace(ConstraintEdgeType::LOAD, nodeID, dst, id);
    return isNew.second;
}

bool
ConstraintNode::addStoreEdge(NodeID dst, EdgeID id)
{
    const auto isNew = storeEdges.emplace(ConstraintEdgeType::STORE, nodeID, dst, id);
    return isNew.second;
}

bool
ConstraintNode::addConstantGepEdge(NodeID dst, EdgeID id)
{
    const auto isNew = constantGepEdges.emplace(ConstraintEdgeType::CONSTANT_GEP, nodeID, dst, id);
    return isNew.second;
}

bool
ConstraintNode::addVariantGepEdge(NodeID dst, EdgeID id)
{
    const auto isNew = variantGepEdges.emplace(ConstraintEdgeType::VARIANT_GEP, nodeID, dst, id);
    return isNew.second;
}


void
ConstraintNode::print(raw_ostream& out) const
{
    value->print(out, true);
    out << "\t|\t" << "NodeType: " << type << "\tID: " << nodeID;
}

} // namespace andr