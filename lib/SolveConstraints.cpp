#include "ConstraintGraph.hpp"

namespace andr {

using namespace std;
using namespace llvm;

// Solve All Constraints.
//  (but not completely because of online-additional edges.)
void
ConstraintGraph::solveConstraints()
{
    // Initially all nodes are pushed.
    for (auto &n : nodes) {
        nodesToBeSolved.push(n.getNodeID());
    }

    while(!nodesToBeSolved.empty()) {
        auto nodeID = nodesToBeSolved.pop();
        solveConstraint(getConstraintNode(nodeID));
    }
    //for (int i = 0; i < 10; i++) {
    //    for (auto &n : nodes) {
    //        solveConstraint(n);
    //    }
    //}
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
        if (addrNode.addPtsToSet(n.getNodeID())) {
            nodesToBeSolved.push(addrNode.getNodeID());
        }
    }
    for (const auto copyEdge : n.copys()) {
        ConstraintNode &dstNode = getConstraintNode(copyEdge.getDstNodeID());
        for (const auto pts : n.pts_sets()) {
            if (dstNode.addPtsToSet(pts)) {
                nodesToBeSolved.push(dstNode.getNodeID());
            }
        }
    }
    for (const auto loadEdge : n.loads()) {
        for (const auto pts : n.pts_sets()) {
            if (addConstraintEdge(ConstraintEdgeType::COPY, pts, loadEdge.getDstNodeID())) {
                nodesToBeSolved.push(n.getNodeID());
            }
        }
    }
    for (const auto storeEdge : n.stores()) {
        ConstraintNode &dstNode = getConstraintNode(storeEdge.getDstNodeID());
        for (const auto pts : dstNode.pts_sets()) {
            if (addConstraintEdge(ConstraintEdgeType::COPY, n.getNodeID(), pts)) {
                nodesToBeSolved.push(n.getNodeID());
            }
        }
    }
    for (const auto variantEdge : n.variant_geps()) {
        /// Same as copy!!
        ConstraintNode &dstNode = getConstraintNode(variantEdge.getDstNodeID());
        for (const auto pts : n.pts_sets()) {
            if (dstNode.addPtsToSet(pts)) {
                nodesToBeSolved.push(dstNode.getNodeID());
            }
        }
    }

    //std::cout << "Solve " << n.getNodeID() << ": ";
    //nodesToBeSolved.print(std::cout);
}

} // namespace andr