
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

bool
ConstraintGraph::addConstraintEdge(ConstraintEdgeType type, NodeID src, NodeID dst)
{
    bool isNew = getConstraintNode(src).addConstraintEdge(type, dst, nextEdgeID);
    if (isNew) {
        nextEdgeID++;
        return true;
    } else {
        return false;
    }
}

void
ConstraintGraph::print(raw_ostream &out) const
{
    outs() << "ConstraintGraph::print()\n";
    printNodes(out);
    printPtsToSets(out);
}

void
ConstraintGraph::printNodes(raw_ostream &out) const
{
    outs() << "ConstraintGraph::printNodes()\n";
    for (const auto &n : nodes) {
        n.print(out);
        out << '\n';
    }
}

void
ConstraintGraph::printPtsToSets(raw_ostream &out) const
{
    outs() << "ConstraintGraph::printPtsToSets()\n";
    for (const auto &n : nodes) {
        if (n.pts_begin() == n.pts_end()) {
            continue;
        }
        n.print(out);
        out << '\n';
        for (const auto &pts : n.pts_sets()) {
            out << "\tpoints-to -> ";
            nodes[pts].print(out);
            out << '\n';
        }
    }
}

} // namespace andr