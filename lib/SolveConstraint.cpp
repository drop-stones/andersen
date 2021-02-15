#include "ConstraintGraph.hpp"

namespace andr {

using namespace std;
using namespace llvm;

void
ConstraintGraph::solveConstraints()
{
    for (const auto &c : constraints) {
        solveConstraint(c);
    }
}

void
ConstraintGraph::solveConstraint(const Constraint &c)
{
    switch(c.getConstraintType()) {
    case ConstraintType::ADDR_OF:
    case ConstraintType::COPY:
    case ConstraintType::LOAD:
    case ConstraintType::STORE:
    default:    outs() << "TODO\n";
    }
}

} // namespace andr