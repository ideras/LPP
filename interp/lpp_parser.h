#if !defined(__LPP_PARSER_H__)
#define __LPP_PARSER_H__

#include <string>
#include <optional>
#include "lpp_lexer.h"
#include "lpp_ast.h"

class LppParser  
{
public:
    LppParser(LppLexer& lexer)
      : lexer(lexer)
    {}
    
    ~LppParser()
    {}

    Ast::NodeUPtr parse();

private:
    Ast::NodeUPtr typeDef();
    Ast::NodeUPtr typeDefinitions();
    Ast::NodeUPtr type();
    Ast::NodeUPtr declarations();
    Ast::NodeUPtr declarationLine();
    Ast::NodeUPtr identifierList();
    Ast::NodeUPtr parameterDecl();
    Ast::NodeUPtr parameterList();
    Ast::NodeUPtr parameterDeclarations();
    Ast::NodeUPtr procDeclarations();

    Ast::NodeUPtr assignStmt();
    Ast::NodeUPtr returnStmt();
    Ast::NodeUPtr writeStmt();
    Ast::NodeUPtr readStmt();
    Ast::NodeUPtr forStmt();
    Ast::NodeUPtr callStmt();
    Ast::NodeUPtr whileStmt();
    Ast::NodeUPtr repeatStmt();
    Ast::NodeUPtr ifStmt();
    Ast::NodeUPtr caseStmt();
    Ast::NodeUPtr literal();
    Ast::NodeUPtr writeFileStmt();
    Ast::NodeUPtr readFileStmt();
    Ast::NodeUPtr closeFileStmt();
    Ast::NodeUPtr openFileStmt();
    Ast::NodeUPtr statement();
    Ast::NodeUPtr statementList();
    Ast::NodeUPtr compoundBlock();

    Ast::NodeUPtr factor();
    Ast::NodeUPtr power();
    Ast::NodeUPtr term();
    Ast::NodeUPtr simpleExpr();
    Ast::NodeUPtr expression();
    Ast::NodeUPtr exprList();
    Ast::NodeUPtr simpleVariable(const std::optional<std::string>& var);
    Ast::NodeUPtr variable(const std::optional<std::string>& var);

    template<typename T>
    bool tokenIs(T tk) {
        return (this->token == tk);
    }

    template<typename T, typename... TArgs>
    bool tokenIs(T first, TArgs... more) {
        return (this->token == first) || tokenIs(more...);
    }

    void skipEOL();
    void skipOptionalEOL();
    void expectEOL();
    std::string expect(Token tk, const std::string& message);

private:
    LppLexer& lexer;
    Token token;
};

#endif // !defined(__LPP_PARSER_H__)
