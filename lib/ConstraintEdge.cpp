
#include "ConstraintEdge.hpp"

namespace andr {

using namespace std;
using namespace llvm;

ConstraintEdge::ConstraintEdge(ConstraintEdgeType ty, NodeID src, NodeID dst, EdgeID id)
    : type{ty}, srcID{src}, dstID{dst}, edgeID{id} {}

NodeID
ConstraintEdge::getSrcNodeID() const
{
    return srcID;
}

NodeID
ConstraintEdge::getDstNodeID() const
{
    return dstID;
}

EdgeID
ConstraintEdge::getEdgeID() const
{
    return edgeID;
}

void
ConstraintEdge::print() const
{
    // TODO
}

} // namespace andr