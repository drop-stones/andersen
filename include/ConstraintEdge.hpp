#pragma once

//#include "ConstraintNode.hpp"

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
    NodeID getSrcNodeID() const;
    NodeID getDstNodeID() const;
    EdgeID getEdgeID() const;
    void print() const;

    bool operator< (const ConstraintEdge& e) const {
        return (this->edgeID < e.getEdgeID() ? true : false);
    }

private:
    const ConstraintEdgeType type;
    const EdgeID edgeID;
    const NodeID srcID, dstID;
};

} // namespace andr