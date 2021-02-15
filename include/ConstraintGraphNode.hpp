#pragma once

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
typedef unsigned long NodeIndex;
typedef set<NodeIndex> NodeSet;
class Constraint;

class ConstraintNode {
public:
    ConstraintNode(NodeType t, NodeIndex i, const Value &v);
    NodeIndex getNodeIndex() const;
    void addPtsToSet (NodeIndex i);
    void addAddrEdge (NodeIndex i);
    void addCopyEdge (NodeIndex i);
    void addLoadEdge (NodeIndex i);
    void addStoreEdge(NodeIndex i);

    void print() const;
    void printPtsToSet() const;

    typedef NodeSet::iterator iterator;
    typedef NodeSet::const_iterator const_iterator;

    //inline iterator begin() { return ptsToSet.begin(); }
    //inline iterator end() { return ptsToSet.end(); }
    inline const_iterator begin() const { return ptsToSet.begin(); }
    inline const_iterator end() const { return ptsToSet.end(); }
    //inline iterator addr_begin() { return addrEdges.begin(); }
    //inline iterator addr_end() { return addrEdges.end(); }
    inline const_iterator addr_begin() const { return addrEdges.begin(); }
    inline const_iterator addr_end() const { return addrEdges.end(); }
    inline llvm::iterator_range<const_iterator> addrs() const {
        return llvm::iterator_range<const_iterator>(addr_begin(), addr_end());
    }
    //inline iterator copy_begin() { return copyEdges.begin(); }
    //inline iterator copy_end() { return copyEdges.end(); }
    inline const_iterator copy_begin() const { return copyEdges.begin(); }
    inline const_iterator copy_end() const { return copyEdges.end(); }
    inline llvm::iterator_range<const_iterator> copys() const {
        return llvm::iterator_range<const_iterator>(copy_begin(), copy_end());
    }
    inline const_iterator load_begin() const { return loadEdges.begin(); }
    inline const_iterator load_end() const { return loadEdges.end(); }
    inline llvm::iterator_range<const_iterator> loads() const {
        return llvm::iterator_range<const_iterator>(load_begin(), load_end());
    }
    inline const_iterator store_begin() const { return storeEdges.begin(); }
    inline const_iterator store_end() const { return storeEdges.end(); }
    inline llvm::iterator_range<const_iterator> stores() const {
        return llvm::iterator_range<const_iterator>(store_begin(), store_end());
    }

private:
    const NodeIndex idx;
    const NodeType type;
    const Value &value;
    NodeSet addrEdges, copyEdges, loadEdges, storeEdges, ptsToSet;
};


} // namespace andr