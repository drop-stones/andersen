#pragma once

#include "ConstraintGraphNode.hpp"

#include <llvm/Support/raw_ostream.h>

namespace andr {

using namespace llvm;

enum class ConstraintType {
    ADDR_OF,
    COPY,
    LOAD,
    STORE,
};
raw_ostream& operator<<(raw_ostream& out, ConstraintType t);

class Constraint {
public:
    Constraint(ConstraintType t, ConstraintNode &l, ConstraintNode &r);
    ConstraintType getConstraintType() const;
    void print() const;

private:
    const ConstraintType type;
    const ConstraintNode& lhs, rhs;
};

} // namespace andr