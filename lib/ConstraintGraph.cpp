
#include "ConstraintGraph.hpp"

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace llvm;

ConstraintNode::ConstraintNode(NodeType t, NodeIndex i, const Value &v)
    : type{t}, idx{i}, value{v} {}

NodeIndex
ConstraintNode::getNodeIndex() const
{
    return idx;
}

void
ConstraintNode::addPtsToSet(NodeIndex i)
{
    ptsToSet.insert(i);
}

void
ConstraintNode::addAddrEdge(NodeIndex i)
{
    addrEdges.insert(i);
}

void
ConstraintNode::addCopyEdge(NodeIndex i)
{
    copyEdges.insert(i);
}

void
ConstraintNode::addLoadEdge(NodeIndex i)
{
    loadEdges.insert(i);
}

void
ConstraintNode::addStoreEdge(NodeIndex i)
{
    storeEdges.insert(i);
}

void
ConstraintNode::print() const
{
    outs() << "NodeType: " << type << "\tNodeIndex: " << idx << "\t";
    value.print(outs(), true);
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

ConstraintGraph::ConstraintGraph() {}

NodeIndex
ConstraintGraph::createValueNode(const Value &v)
{
    //return createNode(NodeType::VALUE_NODE, nodes.size(), v);
    NodeIndex idx = createNode(NodeType::VALUE_NODE, nodes.size(), v);
    valueToIndex.emplace(make_pair(&v, idx));
    return idx;
}

NodeIndex
ConstraintGraph::createObjNode(const Value &v)
{
    //return createNode(NodeType::OBJ_NODE, nodes.size(), v);
    NodeIndex idx = createNode(NodeType::OBJ_NODE, nodes.size(), v);
    objToIndex.emplace(make_pair(&v, idx));
    return idx;
}

NodeIndex
ConstraintGraph::createNode(NodeType t, NodeIndex i, const Value &v)
{
    nodes.emplace_back(t, i, v);
    return i;
}

NodeIndex
ConstraintGraph::getValueNodeIndex(const Value &v)
{
    return valueToIndex[&v];
}

NodeIndex
ConstraintGraph::getObjNodeIndex(const Value &v)
{
    return objToIndex[&v];
}

ConstraintNode&
ConstraintGraph::getConstraintNode(NodeIndex index)
{
    return nodes[index];
}

void
ConstraintGraph::createConstraint(ConstraintType type, NodeIndex lhs, NodeIndex rhs)
{
    constraints.emplace_back(type, lhs, rhs);
}

void
ConstraintGraph::print() const
{
    outs() << "ConstraintGraph::print()\n";
    printNodes();
    printConstraints();
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
ConstraintGraph::printConstraints() const
{
    outs() << "ConstraintGraph::printConstraints()\n";
    for (const auto c : constraints) {
        c.print();
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