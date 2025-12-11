// src/main.cpp

#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;
using namespace clang::tooling;

static cl::OptionCategory MyToolCategory("CountFnQty");

int main(int argc, const char **argv) {
    // CommonOptionsParser OptionsParser(argc, argv);
    auto ExpectedParser =
        CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }

    CommonOptionsParser &OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}
