
#include "ConstraintEdge.hpp"

namespace andr {

using namespace std;
using namespace llvm;

ConstraintEdge::ConstraintEdge(ConstraintEdgeType ty, NodeID src, NodeID dst, EdgeID id)
    : type{ty}, srcID{src}, dstID{dst}, edgeID{id} {}

ConstraintEdgeType
ConstraintEdge::getConstraintEdgeType() const
{
    return type;
}

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
ConstraintEdge::print(raw_ostream& out) const
{
    // TODO
}

} // namespace andr