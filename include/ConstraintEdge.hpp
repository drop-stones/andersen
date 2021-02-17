#pragma once

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace std;
using namespace llvm;

enum class ConstraintEdgeType {
    ADDR_OF,
    COPY,
    LOAD,
    STORE,
    CONSTANT_GEP,
    VARIANT_GEP,
};
raw_ostream& operator<<(raw_ostream& out, ConstraintEdgeType t);

using NodeID = unsigned long;
using EdgeID = unsigned int;

class ConstraintEdge {
public:
    ConstraintEdge(ConstraintEdgeType type, NodeID src, NodeID dst, EdgeID idx);
    ConstraintEdgeType getConstraintEdgeType() const;
    NodeID getSrcNodeID() const;
    NodeID getDstNodeID() const;
    EdgeID getEdgeID() const;
    void print(raw_ostream& out) const;

    /// If same ID, return false.
    /// If edgeID is small, return true.
    bool operator< (const ConstraintEdge& e) const {
        if (type == e.getConstraintEdgeType() && srcID == e.getSrcNodeID() && dstID == e.getDstNodeID()) {
            return false;
        }
        return (this->edgeID < e.getEdgeID() ? true : false);
    }

private:
    const ConstraintEdgeType type;
    const EdgeID edgeID;
    const NodeID srcID, dstID;
};

} // namespace andr