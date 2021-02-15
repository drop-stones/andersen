#include "Constraint.hpp"

namespace andr {

using namespace llvm;

Constraint::Constraint(ConstraintType t, NodeIndex l, NodeIndex r)
    : type{t}, lhs_index{l}, rhs_index{r}
{}

ConstraintType
Constraint::getConstraintType() const
{
    return type;
}

NodeIndex
Constraint::getLhsIndex() const
{
    return lhs_index;
}

NodeIndex
Constraint::getRhsIndex() const
{
    return rhs_index;
}

void
Constraint::print() const
{
    outs() << "ConstraintType: " << type << '\n';
    outs() << "  - lhs: " << lhs_index << '\n';
    outs() << "  - rhs: " << rhs_index << '\n';
}

} // namespace andr