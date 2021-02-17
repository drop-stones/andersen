#include "ConstraintGraph.hpp"

namespace andr {

using namespace std;
using namespace llvm;

// Solve All Constraints.
//  (but not completely because of online-additional edges.)
void
ConstraintGraph::solveConstraints()
{
    // TODO: WorkList Algorithm
    for (int i = 0; i < 10; i++) {
        for (auto &n : nodes) {
            solveConstraint(n);
        }
    }
}

// Solve constraint following Inferrence rules.
//  - ADDR_OF:
//  - COPY:
//  - STORE:
//  - LOAD:
void
ConstraintGraph::solveConstraint(ConstraintNode &n)
{
    for (const auto addrEdge : n.addrs()) {
        ConstraintNode &addrNode = getConstraintNode(addrEdge.getDstNodeID());
        addrNode.addPtsToSet(n.getNodeID());
    }
    for (const auto copyEdge : n.copys()) {
        ConstraintNode &dstNode = getConstraintNode(copyEdge.getDstNodeID());
        for (const auto pts : n) {
            dstNode.addPtsToSet(pts);
        }
    }
    for (const auto loadEdge : n.loads()) {
        for (const auto pts : n) {
            addConstraintEdge(ConstraintEdgeType::COPY, pts, loadEdge.getDstNodeID());
        }
    }
    for (const auto storeEdge : n.stores()) {
        ConstraintNode &dstNode = getConstraintNode(storeEdge.getDstNodeID());
        for (const auto pts : dstNode) {
            // Add Copy edges
            addConstraintEdge(ConstraintEdgeType::COPY, n.getNodeID(), pts);
        }
    }
}

} // namespace andr