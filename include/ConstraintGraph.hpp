#pragma once

#include "ConstraintNode.hpp"
#include "ConstraintEdge.hpp"

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
    NodeID createValueNode(const Value* v);
    NodeID createObjNode(const Value* v);
    NodeID getValueNodeID(const Value* v);
    NodeID getObjNodeID(const Value* v);
    ConstraintNode& getConstraintNode(NodeID id);
    EdgeID addConstraintEdge(ConstraintEdgeType type, NodeID src, NodeID dst);
    void solveConstraints();

    void print() const;
    void printNodes() const;
    void printPtsToSets() const;

private:
    NodeID createNode(NodeType ty, NodeID id, const Value* v);
    void solveConstraint(ConstraintNode &n);

    unordered_map<const Value *, NodeID> valueToID;
    unordered_map<const Value *, NodeID> objToID;

    vector<ConstraintNode> nodes;
    EdgeID nextEdgeID;
};

} // namespace andr