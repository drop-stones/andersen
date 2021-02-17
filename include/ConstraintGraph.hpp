#pragma once

#include "ConstraintNode.hpp"
#include "ConstraintEdge.hpp"
#include "Worklist.hpp"

#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>
#include <unordered_map>

namespace andr {

using namespace std;
using namespace llvm;

using ValueToIDMap = unordered_map<const Value *, NodeID>;
using NodeVector = vector<ConstraintNode>;

class ConstraintGraph {
public:
    ConstraintGraph();
    NodeID createValueNode(const Value* v);
    NodeID createObjNode(const Value* v);
    NodeID getValueNodeID(const Value* v);
    NodeID getObjNodeID(const Value* v);
    ConstraintNode& getConstraintNode(NodeID id);
    bool addConstraintEdge(ConstraintEdgeType type, NodeID src, NodeID dst);
    void solveConstraints();

    void print(raw_ostream& out) const;
    void printNodes(raw_ostream& out) const;
    void printPtsToSets(raw_ostream& out) const;

private:
    NodeID createNode(NodeType ty, NodeID id, const Value* v);
    void solveConstraint(ConstraintNode &n);

    ValueToIDMap valueToID;
    ValueToIDMap objToID;

    NodeVector nodes;
    EdgeID nextEdgeID;

    Worklist<NodeID> nodesToBeSolved;
};

} // namespace andr