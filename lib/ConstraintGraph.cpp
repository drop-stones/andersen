
#include "ConstraintGraph.hpp"

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace llvm;

ConstraintGraph::ConstraintGraph() : nextEdgeID{0} {}

NodeID
ConstraintGraph::createValueNode(const Value* v)
{
    NodeID id = createNode(NodeType::VALUE_NODE, nodes.size(), v);
    valueToID.emplace(make_pair(v, id));
    return id;
}

NodeID
ConstraintGraph::createObjNode(const Value* v)
{
    NodeID id = createNode(NodeType::OBJ_NODE, nodes.size(), v);
    objToID.emplace(make_pair(v, id));
    return id;
}

NodeID
ConstraintGraph::createNode(NodeType ty, NodeID id, const Value* v)
{
    nodes.emplace_back(ty, id, v);
    return id;
}

NodeID
ConstraintGraph::getValueNodeID(const Value* v)
{
    return valueToID[v];
}

NodeID
ConstraintGraph::getObjNodeID(const Value* v)
{
    return objToID[v];
}

ConstraintNode&
ConstraintGraph::getConstraintNode(NodeID id)
{
    return nodes[id];
}

EdgeID
ConstraintGraph::addConstraintEdge(ConstraintEdgeType type, NodeID src, NodeID dst)
{
    getConstraintNode(src).addConstraintEdge(type, dst, nextEdgeID);
    nextEdgeID++;
    return nextEdgeID;
}

void
ConstraintGraph::print() const
{
    outs() << "ConstraintGraph::print()\n";
    printNodes();
    //printConstraints();
}

void
ConstraintGraph::printNodes() const
{
    outs() << "ConstraintGraph::printNodes()\n";
    for (const auto n : nodes) {
        n.print();
    }
}

void
ConstraintGraph::printPtsToSets() const
{
    outs() << "ConstraintGraph::printPtsToSets()\n";
    for (const auto n : nodes) {
        n.printPtsToSet();
    }
}

} // namespace andr