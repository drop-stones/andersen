#include "ConstraintGraph.hpp"
#include "ConstraintEdge.hpp"

namespace andr {

using namespace llvm;

// enum class NodeType
raw_ostream& operator<<(raw_ostream &out, NodeType t) {
    switch(t) {
    case NodeType::VALUE_NODE:  out << "VALUE_NODE"; break;
    case NodeType::OBJ_NODE:    out << "OBJ_NODE";   break;
    default:                    out << "Invalid Type";    break;
    }
    return out;
}

// enum class ConstraintType
raw_ostream& operator<<(raw_ostream& out, ConstraintEdgeType t) {
    switch(t) {
    case ConstraintEdgeType::ADDR_OF:       out << "ADDR_OF"; break;
    case ConstraintEdgeType::COPY:          out << "COPY";    break;
    case ConstraintEdgeType::LOAD:          out << "LOAD";    break;
    case ConstraintEdgeType::STORE:         out << "STORE";   break;
    case ConstraintEdgeType::CONSTANT_GEP:  out << "CONSTANT_GEP";  break;
    case ConstraintEdgeType::VARIANT_GEP:   out << "VARIANT_GEP";   break;
    default:                                out << "Invalid Type"; break;
    }
    return out;
}

} // namespace andr