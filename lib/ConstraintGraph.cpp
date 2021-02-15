
#include "ConstraintGraph.hpp"

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace llvm;

ConstraintNode::ConstraintNode(NodeType t, NodeIndex i, const Value &v)
    : type{t}, idx{i}, value{v} {}

void
ConstraintNode::addPtsToSet(NodeIndex i)
{
    ptsToSet.insert(i);
}

void
ConstraintNode::print() const
{
    llvm::outs() << "NodeType: " << type << "\tNodeIndex: " << idx << "\t";
    value.print(llvm::outs(), true);
    llvm::outs() << '\n';
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
    ConstraintNode n {t, i, v};
    nodes.push_back(n);
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

void
ConstraintGraph::createConstraint(ConstraintType t, NodeIndex lhs, NodeIndex rhs)
{
    if (lhs > nodes.size() || rhs > nodes.size()) {
        errs() << "Out-of-Range!!\n";
        exit(1);
    }
    Constraint c {t, nodes[lhs], nodes[rhs]};
    constraints.push_back(c);
}

void
ConstraintGraph::print() const
{
    outs() << "Andersen::print()\n";
    printNodes();
    printConstraints();
}

void
ConstraintGraph::printNodes() const
{
    outs() << "Andersen::printNodes()\n";
    for (const auto n : nodes) {
        n.print();
    }
}

void
ConstraintGraph::printConstraints() const
{
    outs() << "Andersen::printConstraints()\n";
    for (const auto c : constraints) {
        c.print();
    }
}

} // namespace andr