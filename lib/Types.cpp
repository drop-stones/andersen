#include "Constraint.hpp"
#include "ConstraintGraph.hpp"

namespace andr {

using namespace llvm;

// enum class ConstraintType
raw_ostream& operator<<(raw_ostream& out, ConstraintType t) {
    switch(t) {
    case ConstraintType::ADDR_OF:   out << "ADDR_OF"; break;
    case ConstraintType::COPY:      out << "COPY";    break;
    case ConstraintType::LOAD:      out << "LOAD";    break;
    case ConstraintType::STORE:     out << "STORE";   break;
    default:                        out << "Invalid"; break;
    }
    return out;
}

// enum class NodeType
raw_ostream& operator<<(raw_ostream &out, NodeType t) {
    switch(t) {
    case NodeType::VALUE_NODE:  out << "VALUE_NODE"; break;
    case NodeType::OBJ_NODE:    out << "OBJ_NODE";   break;
    default:                    out << "Invalid";    break;
    }
    return out;
}

} // namespace andr