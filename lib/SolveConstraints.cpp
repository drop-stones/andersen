#include "ConstraintGraph.hpp"

namespace andr {

using namespace std;
using namespace llvm;

void
ConstraintGraph::addConstraintEdges()
{
    for (const auto &c : constraints){
        addConstraintEdge(c);
    }
}

void
ConstraintGraph::addConstraintEdge(const Constraint &c)
{
    switch(c.getConstraintType()) {
    case ConstraintType::ADDR_OF: {
        ConstraintNode &addrNode = getConstraintNode(c.getRhsIndex());
        addrNode.addAddrEdge(c.getLhsIndex());
        break;
    }
    case ConstraintType::COPY: {
        ConstraintNode &srcNode = getConstraintNode(c.getRhsIndex());
        srcNode.addCopyEdge(c.getLhsIndex());
        break;
    }
    case ConstraintType::LOAD: {
        ConstraintNode &srcNode = getConstraintNode(c.getRhsIndex());
        srcNode.addLoadEdge(c.getLhsIndex());
        break;
    }
    case ConstraintType::STORE: {
        ConstraintNode &srcNode = getConstraintNode(c.getRhsIndex());
        //ConstraintNode &dstNode = getConstraintNode(c.getLhsIndex());
        srcNode.addStoreEdge(c.getLhsIndex());
        break;
    }
    default:    errs() << "Invalid\n";
    }
}

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
    for (const auto addrIndex : n.addrs()) {
        ConstraintNode &addrNode = getConstraintNode(addrIndex);
        addrNode.addPtsToSet(n.getNodeIndex());
    }
    for (const auto copyIndex : n.copys()) {
        // TODO
        ConstraintNode &dstNode = getConstraintNode(copyIndex);
        for (const auto pts : n) {
            dstNode.addPtsToSet(pts);
        }
    }
    for (const auto loadIndex : n.loads()) {
        // TODO
        for (const auto pts : n) {
            ConstraintNode &ptsNode = getConstraintNode(pts);
            ptsNode.addCopyEdge(loadIndex);
        }
    }
    for (const auto storeIndex : n.stores()) {
        // TODO
        ConstraintNode &dstNode = getConstraintNode(storeIndex);
        for (const auto pts : dstNode) {
            // Add Copy edges
            n.addCopyEdge(pts);
        }
    }
}

} // namespace andr