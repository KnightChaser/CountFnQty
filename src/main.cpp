// src/main.cpp

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// Category for command-line options
static cl::OptionCategory MyToolCategory("CountFnQty");

// Counters
static int FunctionDeclarationCount = 0;
static int FunctionCallCount = 0;

// Callback for function declarations
class FunctionDeclarationHandler : public MatchFinder::MatchCallback {
  public:
    void run(const MatchFinder::MatchResult &Result) override {
        if (Result.Nodes.getNodeAs<clang::FunctionDecl>("func")) {
            FunctionDeclarationCount++;
        }
    }
};

// Callback for function Calls
class FunctionCallHandler : public MatchFinder::MatchCallback {
  public:
    void run(const MatchFinder::MatchResult &Result) override {
        if (Result.Nodes.getNodeAs<clang::CallExpr>("call")) {
            FunctionCallCount++;
        }
    }
};

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

    MatchFinder Finder;
    FunctionDeclarationHandler functionDeclarationHandler;
    FunctionCallHandler functionCallHandler;

    // Match all function declarations
    Finder.addMatcher(functionDecl(isExpansionInMainFile(), // only in main file
                                   isDefinition()           // only definitions
                                   )
                          .bind("func"),
                      &functionDeclarationHandler);

    // Match all function calls
    Finder.addMatcher(callExpr(isExpansionInMainFile() // only in main file
                               )
                          .bind("call"),
                      &functionCallHandler);

    auto ActionFactory = newFrontendActionFactory(&Finder);
    if (int status = Tool.run(ActionFactory.get())) {
        llvm::errs() << "Error during tool execution\n";
        return status;
    }

    llvm::outs() << "Number of function declarations: "
                 << FunctionDeclarationCount << "\n";
    llvm::outs() << "Number of function calls: " << FunctionCallCount << "\n";

    return 0;
}
