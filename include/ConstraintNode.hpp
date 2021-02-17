#pragma once

#include "ConstraintEdge.hpp"

#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <set>

namespace andr {

using namespace std;
using namespace llvm;

enum class NodeType {
    VALUE_NODE,     // Pointer
    OBJ_NODE,       // Allocated Object
};
raw_ostream& operator<<(raw_ostream& out, NodeType t);
using NodeID = unsigned long;
using NodeSet = set<NodeID>;
using EdgeSet = set<ConstraintEdge>;

class ConstraintNode {
public:
    ConstraintNode(NodeType ty, NodeID id, const Value* v);
    NodeID getNodeID() const;
    void addPtsToSet (NodeID id);
    void addConstraintEdge(ConstraintEdgeType type, NodeID dst, EdgeID id);

    void print() const;
    void printPtsToSet() const;

    using edge_iterator = EdgeSet::iterator;
    using const_edge_iterator = EdgeSet::const_iterator;
    using node_iterator = NodeSet::iterator;
    using const_node_iterator = NodeSet::const_iterator;

    //inline iterator begin() { return ptsToSet.begin(); }
    //inline iterator end() { return ptsToSet.end(); }
    inline const_node_iterator begin() const { return ptsToSet.begin(); }
    inline const_node_iterator end() const { return ptsToSet.end(); }
    //inline iterator addr_begin() { return addrEdges.begin(); }
    //inline iterator addr_end() { return addrEdges.end(); }
    inline const_edge_iterator addr_begin() const { return addrEdges.begin(); }
    inline const_edge_iterator addr_end() const { return addrEdges.end(); }
    inline llvm::iterator_range<const_edge_iterator> addrs() const {
        return llvm::iterator_range<const_edge_iterator>(addr_begin(), addr_end());
    }
    //inline iterator copy_begin() { return copyEdges.begin(); }
    //inline iterator copy_end() { return copyEdges.end(); }
    inline const_edge_iterator copy_begin() const { return copyEdges.begin(); }
    inline const_edge_iterator copy_end() const { return copyEdges.end(); }
    inline llvm::iterator_range<const_edge_iterator> copys() const {
        return llvm::iterator_range<const_edge_iterator>(copy_begin(), copy_end());
    }
    inline const_edge_iterator load_begin() const { return loadEdges.begin(); }
    inline const_edge_iterator load_end() const { return loadEdges.end(); }
    inline llvm::iterator_range<const_edge_iterator> loads() const {
        return llvm::iterator_range<const_edge_iterator>(load_begin(), load_end());
    }
    inline const_edge_iterator store_begin() const { return storeEdges.begin(); }
    inline const_edge_iterator store_end() const { return storeEdges.end(); }
    inline llvm::iterator_range<const_edge_iterator> stores() const {
        return llvm::iterator_range<const_edge_iterator>(store_begin(), store_end());
    }

private:
    void addAddrEdge       (NodeID dst, EdgeID id);
    void addCopyEdge       (NodeID dst, EdgeID id);
    void addLoadEdge       (NodeID dst, EdgeID id);
    void addStoreEdge      (NodeID dst, EdgeID id);
    void addConstantGepEdge(NodeID dst, EdgeID id);
    void addVariantGepEdge (NodeID dst, EdgeID id);


    const NodeID nodeID;
    const NodeType type;
    const Value* value;
    NodeSet ptsToSet;
    EdgeSet addrEdges, copyEdges, loadEdges, storeEdges, constantGepEdges, variantGepEdges;
};


} // namespace andr