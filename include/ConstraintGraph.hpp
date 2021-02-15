#pragma once

#include "Constraint.hpp"
#include "ConstraintGraphNode.hpp"

#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>
#include <unordered_map>

namespace andr {

using namespace std;
using namespace llvm;

class ConstraintGraph {
public:
    ConstraintGraph();
    NodeIndex createValueNode(const Value &v);
    NodeIndex createObjNode(const Value &v);
    NodeIndex getValueNodeIndex(const Value &v);
    NodeIndex getObjNodeIndex(const Value &v);
    ConstraintNode& getConstraintNode(NodeIndex index);
    void createConstraint(ConstraintType type, NodeIndex lhs, NodeIndex rhs);
    void addConstraintEdges();
    void solveConstraints();

    void print() const;
    void printNodes() const;
    void printConstraints() const;
    void printPtsToSets() const;

private:
    NodeIndex createNode(NodeType t, NodeIndex i, const Value &v);
    void addConstraintEdge(const Constraint &c);
    void solveConstraint(ConstraintNode &n);

    unordered_map<const Value *, NodeIndex> valueToIndex;
    unordered_map<const Value *, NodeIndex> objToIndex;

    vector<ConstraintNode> nodes;
    vector<Constraint> constraints;
};

} // namespace andr