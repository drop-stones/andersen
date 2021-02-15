#include "Constraint.hpp"

namespace andr {

using namespace llvm;

Constraint::Constraint(ConstraintType t, ConstraintNode &l, ConstraintNode &r)
    : type{t}, lhs{l}, rhs{r} {}

ConstraintType
Constraint::getConstraintType() const
{
    return type;
}

void
Constraint::print() const
{
    outs() << "ConstraintType: " << type << '\n';
    outs() << "  - lhs: ";
    lhs.print();
    outs() << "  - rhs: ";
    rhs.print();
}

} // namespace andr