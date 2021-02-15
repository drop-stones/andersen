#include "Andersen.hpp"

#include "llvm/IR/LLVMContext.h"        // LLVMContext
#include "llvm/IRReader/IRReader.h"     // parseIRFile
#include "llvm/Support/SourceMgr.h"     // SMDiagnostic
#include "llvm/Support/raw_ostream.h"   // errs

int main(int argc, char **argv)
{
    if (argc < 2) {
        llvm::errs() << "usage: " << argv[0] << " <IR file>\n";
        exit(1);
    }

    llvm::StringRef ir_file{argv[1]};
    llvm::SMDiagnostic err;
    llvm::LLVMContext ctx;
    const auto mod = llvm::parseIRFile(ir_file, err, ctx);

    andr::Andersen andr;
    andr.runOnModule(*mod);
    return 0;
}