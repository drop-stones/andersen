#pragma once

#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <set>

namespace andr {

using namespace std;
using namespace llvm;

enum class NodeType {
    VALUE_NODE,     // Pointer
    OBJ_NODE,       // Allocated Object
};
raw_ostream& operator<<(raw_ostream& out, NodeType t);
typedef unsigned long NodeIndex;
typedef set<NodeIndex> NodeSet;
class Constraint;

class ConstraintNode {
public:
    ConstraintNode(NodeType t, NodeIndex i, const Value &v);
    void addPtsToSet (NodeIndex i);
    void addCopyEdge (NodeIndex i);
    void addLoadEdge (NodeIndex i);
    void addStoreEdge(NodeIndex i);
    void print() const;

private:
    const NodeIndex idx;
    const NodeType type;
    const Value &value;
    NodeSet copyEdges, loadEdges, storeEdges, ptsToSet;
};


} // namespace andr