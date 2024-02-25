/*
 * lpp_lex.cpp: Implementation of LPP parser
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include "lpp_exception.h"
#include "lpp_parser.h"
#include "lpp_lexer.h"

Ast::NodeUPtr LppParser::typeDefinitions()
{
    Ast::NodeList::Items defs;

    if (tokenIs(Token::KwTipo, Token::KwRegistro)) {
        Ast::NodeUPtr def = typeDef();
        expectEOL();

        defs.push_back(std::move(def));

        while (tokenIs(Token::KwTipo, Token::KwRegistro)) {
            def = typeDef();
            expectEOL();

            defs.push_back(std::move(def));
        }
    }
    Ast::NodeUPtr def_list = std::make_unique<Ast::NodeList>(std::move(defs));

    return def_list;
}

Ast::NodeUPtr LppParser::typeDef()
{
    int srcline = lexer.getLine();

    switch (token) {
        case Token::KwTipo: {
            token = lexer.getNextToken();

            std::string text = expect(Token::Ident, "Se esperaba un identificador");

            expect(Token::KwEs, "Se esperaba la palabra 'es'");
            
            Ast::NodeUPtr type_n = type();

            Ast::NodeUPtr t = std::make_unique<Ast::SubtypeDef>(text, std::move(type_n));
            t->setSrcLine(srcline);

            return t;
        }
        case Token::KwRegistro: {
            token = lexer.getNextToken();

            std::string text = expect(Token::Ident, "Se esperaba un identificador");
            expectEOL();
            
            Ast::NodeUPtr decls = declarations();

            expect(Token::KwFinRegistro, "Se esperaba la palabra 'fin registro'");
            
            Ast::NodeUPtr t = std::make_unique<Ast::RecordDef>(text, std::move(decls));
            t->setSrcLine(srcline);

            return t;
        }
        default:
            throw LPPException(lexer.getLine(), "Se esperaba la palabra 'registro' o 'tipo'");
    }
}

Ast::NodeUPtr LppParser::declarations()
{
    Ast::NodeList::Items decl_nodes;

    if (tokenIs(Token::KwEntero, Token::KwReal, Token::KwChar, Token::KwBool, Token::KwArreglo, Token::KwCadena, Token::KwArchivo, Token::Ident))
    {
        Ast::NodeUPtr decl = declarationLine();

        decl_nodes.emplace_back(std::move(decl));
        expectEOL();

        while (tokenIs(Token::KwEntero, Token::KwReal, Token::KwChar, Token::KwBool, Token::KwArreglo, Token::KwCadena, Token::KwArchivo, Token::Ident))
        {
            decl = declarationLine();

            decl_nodes.emplace_back(std::move(decl));
            expectEOL();
        }
    }

    return std::make_unique<Ast::NodeList>(std::move(decl_nodes));
}

Ast::NodeUPtr LppParser::declarationLine()
{
    Ast::NodeUPtr type_n = type();

    int line = lexer.getLine();
    Ast::NodeUPtr ident_list = identifierList();

    Ast::NodeUPtr ldecl = std::make_unique<Ast::VarDecl>(std::move(type_n), std::move(ident_list));
    ldecl->setSrcLine(line);

    return ldecl;
}

Ast::NodeUPtr LppParser::type()
{
    int srcline = lexer.getLine();
    Ast::NodeUPtr tn;

    if (tokenIs(Token::KwEntero)) {
        token = lexer.getNextToken();

        tn = std::make_unique<Ast::IntType>();
    }
    else if (tokenIs(Token::KwReal)) {
        token = lexer.getNextToken();

        tn = std::make_unique<Ast::RealType>();
    }
    else if (tokenIs(Token::KwChar)) {
        token = lexer.getNextToken();

        tn = std::make_unique<Ast::CharType>();
    }
    else if (tokenIs(Token::KwBool)) {
        token = lexer.getNextToken();

        tn = std::make_unique<Ast::BoolType>();
    }
    else if (tokenIs(Token::KwCadena)) {
        token = lexer.getNextToken();

        if (tokenIs(Token::OpenBracket)) {
            token = lexer.getNextToken();

            std::string text = expect(Token::IntConst, "Se esperaba un valor entero");

            int size = std::stoi(text);
            expect(Token::CloseBracket, "Se esperaba ']'");

            return std::make_unique<Ast::StringType>(size);
        }

        tn = std::make_unique<Ast::StringType>();
    }
    else if (tokenIs(Token::KwArreglo)) {
        token = lexer.getNextToken();

        expect(Token::OpenBracket, "Se esperaba '['");

        std::string text = expect(Token::IntConst, "Se esperaba un valor entero");


        std::vector<int> dims;

        dims.push_back(std::stoi(text));
        while (tokenIs(Token::Comma)) {
            token = lexer.getNextToken();

            dims.emplace_back(std::stoi(lexer.getText()));

            token = lexer.getNextToken();
        }

        expect(Token::CloseBracket, "Se esperaba ']'");
        expect(Token::KwDe, "Se esperaba la palabra 'de'");
        
        Ast::NodeUPtr elem_type = type();

        tn = std::make_unique<Ast::ArrayType>(std::move(dims), std::move(elem_type));
    }
    else if (tokenIs(Token::KwArchivo)) {
        token = lexer.getNextToken();

        if (tokenIs(Token::KwSecuencial)) {
            token = lexer.getNextToken();

            tn = std::make_unique<Ast::SeqFileType>();
        }
        else if (tokenIs(Token::KwDe)) {
            token = lexer.getNextToken();
            
            Ast::NodeUPtr type_n = type();

            tn = std::make_unique<Ast::BinFileType>(std::move(type_n));
        }
        else {
            throw LPPException(lexer.getLine(), "Se esperaba la palabra 'de' o 'secuencial'");
        }
    }
    else if (tokenIs(Token::Ident)) {
        std::string text = expect(Token::Ident, "");

        tn = std::make_unique<Ast::UserType>(text);
    }
    else {
        throw LPPException(lexer.getLine(), "Se esperaba un tipo de datos");
    }

    tn->setSrcLine(srcline);
    return tn;
}

Ast::NodeUPtr LppParser::identifierList()
{
    Ast::StrList::Items ids;

    if (token != Token::Ident) {
        throw LPPException(lexer.getLine(), "Se esperaba un identificador");
    }
    ids.push_back(lexer.getText());

    token = lexer.getNextToken();
    while (tokenIs(Token::Comma)) {
        token = lexer.getNextToken();

        if (token != Token::Ident) {
            throw LPPException(lexer.getLine(), "Se esperaba un identificador");
        }
        ids.push_back(lexer.getText());

        token = lexer.getNextToken();
    }

    return std::make_unique<Ast::StrList>(std::move(ids));
}

Ast::NodeUPtr LppParser::parse()
{
    token = lexer.getNextToken();
    skipOptionalEOL();
    
    Ast::NodeUPtr type_defs = typeDefinitions();
    
    Ast::NodeUPtr var_decls = declarations();

    Ast::NodeUPtr proc_decls = procDeclarations();
    
    Ast::NodeUPtr stmts = compoundBlock();

    return std::make_unique<Ast::Program>(std::move(type_defs), std::move(var_decls),
                                          std::move(proc_decls), std::move(stmts));
}

Ast::NodeUPtr LppParser::procDeclarations()
{
    Ast::NodeList::Items proc_decls;

    while (tokenIs(Token::KwFuncion, Token::KwProcedimiento)) {
        int srcline = lexer.getLine();
        bool is_function = tokenIs(Token::KwFuncion);

        token = lexer.getNextToken();
        std::string name = expect(Token::Ident, "Se esperaba un identificador");
        
        Ast::NodeUPtr param_defs = parameterDeclarations();

        Ast::NodeUPtr ret_type(nullptr);

        if (is_function) {
            expect(Token::Colon, "Se esperaban ':'");
            ret_type = type();
        }

        expectEOL();
        
        Ast::NodeUPtr var_decls = declarations();
        
        Ast::NodeUPtr stmts = compoundBlock();

        skipEOL();

        Ast::NodeUPtr proc_def = std::make_unique<Ast::ProcDef>(
                                    name, std::move(param_defs), std::move(ret_type),
                                    std::move(var_decls), std::move(stmts)
                                );

        proc_def->setSrcLine(srcline);
        proc_decls.push_back(std::move(proc_def));
    }

    return std::make_unique<Ast::NodeList>(std::move(proc_decls));
}

Ast::NodeUPtr LppParser::parameterDeclarations()
{
    if (tokenIs(Token::OpenPar)) {
        token = lexer.getNextToken();
        
        Ast::NodeUPtr param_defs = parameterList();

        expect(Token::ClosePar, "Se esperaba ')'");

        return param_defs;
    }

    return std::make_unique<Ast::NodeList>();
}

Ast::NodeUPtr LppParser::parameterList()
{
    Ast::NodeUPtr param_def = parameterDecl();

    Ast::NodeList::Items param_defs;

    param_defs.push_back(std::move(param_def));

    while (tokenIs(Token::Comma)) {
        token = lexer.getNextToken();
        
        param_def = parameterDecl();
        param_defs.push_back(std::move(param_def));
    }

    return std::make_unique<Ast::NodeList>(std::move(param_defs));
}

Ast::NodeUPtr LppParser::parameterDecl()
{
    bool is_byref = false;

    if (tokenIs(Token::KwVar)) {
        is_byref = true;

        token = lexer.getNextToken();
    }
    
    Ast::NodeUPtr param_type = type();

    std::string param_name = expect(Token::Ident, "Se esperaba un identificador");

    return std::make_unique<Ast::ParamDef>(is_byref, std::move(param_type), param_name);
}

Ast::NodeUPtr LppParser::expression()
{
    Ast::NodeUPtr expr1 = simpleExpr();

    if (tokenIs(Token::OpRel)) {
        std::string s_oper = expect(Token::OpRel, "");
        
        Ast::NodeUPtr expr2 = simpleExpr();
        if (s_oper.compare("<") == 0)
            return std::make_unique<Ast::LtExpr>(std::move(expr1), std::move(expr2));
        else if (s_oper.compare(">") == 0)
            return std::make_unique<Ast::GtExpr>(std::move(expr1), std::move(expr2));
        else if (s_oper.compare("=") == 0)
            return std::make_unique<Ast::EqExpr>(std::move(expr1), std::move(expr2));
        else if (s_oper.compare("<>") == 0)
            return std::make_unique<Ast::NeqExpr>(std::move(expr1), std::move(expr2));
        else if (s_oper.compare("<=") == 0)
            return std::make_unique<Ast::LteExpr>(std::move(expr1), std::move(expr2));
        else if (s_oper.compare(">=") == 0)
            return std::make_unique<Ast::GteExpr>(std::move(expr1), std::move(expr2));
        else
            throw std::runtime_error("Invalid relational operator '" + s_oper + "'");
    }

    return expr1;
}

Ast::NodeUPtr LppParser::simpleExpr()
{
    Ast::NodeUPtr expr1 = term();

    while (tokenIs(Token::OpAdd, Token::OpBoolOr, Token::OpSub)) {
        Token oper = token;
        token = lexer.getNextToken();

        Ast::NodeUPtr expr2 = term();
        switch (oper) {
            case Token::OpAdd:
                expr1 = std::make_unique<Ast::AddExpr>(std::move(expr1), std::move(expr2));
                break;
            case Token::OpSub:
                expr1 = std::make_unique<Ast::SubExpr>(std::move(expr1), std::move(expr2));
                break;
            case Token::OpBoolOr:
                expr1 = std::make_unique<Ast::OrExpr>(std::move(expr1), std::move(expr2));
                break;
            default:
                break;
        }
    }

    return expr1;
}

Ast::NodeUPtr LppParser::term()
{
    Ast::NodeUPtr expr1 = power();

    while (tokenIs(Token::OpMult, Token::OpDiv, Token::OpIDiv, Token::OpMod, Token::OpBoolAnd)) {
        Token oper = token;
        token = lexer.getNextToken();
        
        Ast::NodeUPtr expr2 = power();

        switch (oper) {
            case Token::OpMult:
                    expr1 = std::make_unique<Ast::MultExpr>(std::move(expr1), std::move(expr2));
                    break;
            case Token::OpDiv:
                    expr1 = std::make_unique<Ast::DivExpr>(std::move(expr1), std::move(expr2));
                    break;
            case Token::OpIDiv:
                    expr1 = std::make_unique<Ast::IDivExpr>(std::move(expr1), std::move(expr2));
                    break;
            case Token::OpMod:
                    expr1 = std::make_unique<Ast::ModExpr>(std::move(expr1), std::move(expr2));
                    break;
            case Token::OpBoolAnd:
                    expr1 = std::make_unique<Ast::AndExpr>(std::move(expr1), std::move(expr2));
                    break;
            default:
                    break;
        }
    }

    return expr1;
}

Ast::NodeUPtr LppParser::power()
{
    Ast::NodeUPtr expr1 = factor();

    while (tokenIs(Token::OpPow)) {
        token = lexer.getNextToken();
        
        Ast::NodeUPtr expr2 = power();

        expr1 = std::make_unique<Ast::PowExpr>(std::move(expr1), std::move(expr2));
    }

    return expr1;
}

Ast::NodeUPtr LppParser::factor()
{
    int srcline = lexer.getLine();

    if (tokenIs(Token::Ident)) {
        std::string text = lexer.getText();

        token = lexer.getNextToken();

        if (tokenIs(Token::OpenPar)) {
            token = lexer.getNextToken();
                    
                    Ast::NodeUPtr expr_list = exprList();
            expect(Token::ClosePar, "Se esperaba ')'");

            auto expn = std::make_unique<Ast::FuncCallExpr>(text, std::move(expr_list));
            expn->setSrcLine(srcline);

            return expn;
        }
        else {
            return variable(text);
        }
    }
    
    if (tokenIs(Token::KwVerdadero, Token::KwFalso))
    {
        bool val = tokenIs(Token::KwVerdadero)? true : false;
        token = lexer.getNextToken();

        return std::make_unique<Ast::BoolConstExpr>(val);
    }

    if (tokenIs(Token::StrLiteral))
    {
        std::string text = lexer.getText();
        token = lexer.getNextToken();

        return std::make_unique<Ast::StrConstExpr>(text);
    }

    if (tokenIs(Token::CharLiteral))
    {
        char val = lexer.getText()[0];
        token = lexer.getNextToken();

        return std::make_unique<Ast::CharConstExpr>(val);
    }

    if (tokenIs(Token::IntConst))
    {
        int val = std::stoi(lexer.getText());
        token = lexer.getNextToken();

        return std::make_unique<Ast::IntConstExpr>(val);
    }

    if (tokenIs(Token::RealConst))
    {
        double val = std::stod(lexer.getText());
        token = lexer.getNextToken();

        return std::make_unique<Ast::RealConstExpr>(val);
    }

    if (tokenIs(Token::OpenPar)) {
        token = lexer.getNextToken();

        Ast::NodeUPtr expr_n = expression();

        expect(Token::ClosePar, "Se esperaba ')'");

        return expr_n;
    }

    if (tokenIs(Token::OpSub, Token::OpAdd, Token::KWNo)) {
        Token oper = token;
        token = lexer.getNextToken();

        Ast::NodeUPtr expr = factor();

        switch (oper) {
            case Token::OpSub:
                return std::make_unique<Ast::NegExpr>(std::move(expr));
            case Token::OpAdd:
                return std::make_unique<Ast::PlusExpr>(std::move(expr));
            case Token::KWNo:
                return std::make_unique<Ast::NotExpr>(std::move(expr));
            default:
                break;
        }
    }

    throw LPPException(lexer.getLine(), "Error de sintaxis en expresion");
}

Ast::NodeUPtr LppParser::variable(const std::optional<std::string>& var)
{
    Ast::NodeUPtr var_node = simpleVariable(var);

    Ast::NodeList::Items var_items;

    var_items.push_back(std::move(var_node));

    while (tokenIs(Token::Dot)) {
        token = lexer.getNextToken();

        var_node = simpleVariable(std::nullopt);
        var_items.push_back(std::move(var_node));
    }

    Ast::NodeUPtr var_list = std::make_unique<Ast::NodeList>(std::move(var_items));
    
    return std::make_unique<Ast::LhsExpr>(std::move(var_list));
}

Ast::NodeUPtr LppParser::simpleVariable(const std::optional<std::string>& var)
{
    int srcline = lexer.getLine();
    std::string var_name = (var.has_value())? var.value() :
                               expect(Token::Ident, "Se esperaba un identificador");

    Ast::NodeUPtr var_node = std::make_unique<Ast::SimpleVar>(var_name);
    var_node->setSrcLine(srcline);

    while (tokenIs(Token::OpenBracket)) {
        token = lexer.getNextToken();
        Ast::NodeList::Items exprs;

        Ast::NodeUPtr expr_n = expression();
        exprs.push_back(std::move(expr_n));

        while (tokenIs(Token::Comma)) {
            token = lexer.getNextToken();

                expr_n = expression();
            exprs.push_back(std::move(expr_n));
        }

        expect(Token::CloseBracket, "Se esperaba ']'");

        Ast::NodeUPtr expr_list = std::make_unique<Ast::NodeList>(std::move(exprs));
        var_node = std::make_unique<Ast::IndexVar>(std::move(var_node), std::move(expr_list));
        var_node->setSrcLine(srcline);
    }

    return var_node;
}

Ast::NodeUPtr LppParser::exprList()
{
    Ast::NodeList::Items exprs;

    if (tokenIs(Token::Ident, Token::IntConst, Token::RealConst, Token::OpenPar, Token::OpSub, Token::KWNo, Token::StrLiteral, Token::CharLiteral))
    {
        Ast::NodeUPtr expr_n = expression();
        exprs.push_back(std::move(expr_n));

        while (tokenIs(Token::Comma)) {
            token = lexer.getNextToken();

            expr_n = expression();
            exprs.push_back(std::move(expr_n));
        }
    }

    return std::make_unique<Ast::NodeList>(std::move(exprs));
}

Ast::NodeUPtr LppParser::compoundBlock()
{
    expect(Token::KwInicio, "Se esperaba la palabra 'inicio'");
    expectEOL();
    
    Ast::NodeUPtr stmts = statementList();

    expect(Token::KwFin, "Se esperaba la palabra 'fin'");

    return stmts;
}

Ast::NodeUPtr LppParser::statementList()
{
    Ast::NodeList::Items stmts;

    if (tokenIs(Token::Ident, Token::KwSi, Token::KwMientras, Token::KwRepita, Token::KwLlamar,
                Token::KwPara, Token::KwLea, Token::KwEscriba, Token::KWRetorne, Token::KwAbrir,
                Token::KwCerrar, Token::KwCaso, Token::KwLeer, Token::KwEscribir))
    {
        Ast::NodeUPtr stmt = statement();
        expectEOL();
        stmts.push_back(std::move(stmt));

        while (tokenIs(Token::Ident, Token::KwSi, Token::KwMientras, Token::KwRepita, Token::KwLlamar,
                       Token::KwPara, Token::KwLea, Token::KwEscriba, Token::KWRetorne, Token::KwAbrir,
                       Token::KwCerrar, Token::KwCaso, Token::KwLeer, Token::KwEscribir))
        {
            Ast::NodeUPtr stmt = statement();
            expectEOL();
            stmts.push_back(std::move(stmt));
        }
    }

    return std::make_unique<Ast::NodeList>(std::move(stmts));
}

Ast::NodeUPtr LppParser::statement()
{
    switch (token) {
        case Token::Ident:
            return assignStmt();
        case Token::KwSi:
            return ifStmt();
        case Token::KwCaso:
            return caseStmt();
        case Token::KwMientras:
            return whileStmt();
        case Token::KwRepita:
            return repeatStmt();
        case Token::KwLlamar:
            return callStmt();
        case Token::KwPara:
            return forStmt();
        case Token::KwLea:
            return readStmt();
        case Token::KwEscriba:
            return writeStmt();
        case Token::KwLeer:
            return readFileStmt();
        case Token::KwEscribir:
            return writeFileStmt();
        case Token::KwAbrir:
            return openFileStmt();
        case Token::KwCerrar:
            return closeFileStmt();
        case Token::KWRetorne:
            return returnStmt();
        default:
            throw LPPException(lexer.getLine(), "Proposicion invalida");
    }
}

Ast::NodeUPtr LppParser::assignStmt()
{
    int srcline = lexer.getLine();
    Ast::NodeUPtr lval = variable(std::nullopt);

    expect(Token::OpAssign, "Se esperaba operador '<-'");

    Ast::NodeUPtr rval = expression();

    Ast::NodeUPtr s = std::make_unique<Ast::AssignStmt>(std::move(lval), std::move(rval));
    s->setSrcLine(srcline);

    return s;
}

Ast::NodeUPtr LppParser::ifStmt()
{
    int srcline = lexer.getLine();
    Ast::NodeList::Items cond_blocks;
    Ast::NodeUPtr else_stmts(nullptr);

    while (true) {
        int srcline = lexer.getLine();
        token = lexer.getNextToken();

        Ast::NodeUPtr cond = expression();

        skipOptionalEOL();
        expect(Token::KwEntonces, "Se esperaba la palabra 'entonces'");
        expectEOL();
        
        Ast::NodeUPtr stmts = statementList();
        Ast::NodeUPtr cond_block =
                std::make_unique<Ast::IfStmt::CondBlock>(std::move(cond), std::move(stmts));

        cond_block->setSrcLine(srcline);
        cond_blocks.push_back(std::move(cond_block));

        if (tokenIs(Token::KwSino)) {
            token = lexer.getNextToken();

            if (tokenIs(Token::KwSi)) {
                continue;
            }
            expectEOL();
            
            else_stmts = statementList();
        }
        break;
    }

    expect(Token::KwFinSi, "Se esperaba la palabra 'fin si'");

    Ast::NodeUPtr cond_block_list = std::make_unique<Ast::NodeList>(std::move(cond_blocks));
    Ast::NodeUPtr stmt =
        std::make_unique<Ast::IfStmt>(std::move(cond_block_list), std::move(else_stmts));

    stmt->setSrcLine(srcline);

    return stmt;
}

Ast::NodeUPtr LppParser::caseStmt()
{
    token = lexer.getNextToken();

    int srcline = lexer.getLine();
    Ast::NodeUPtr var_expr = variable(std::nullopt);

    expectEOL();

    Ast::NodeList::Items cond_blk_items;
    Ast::NodeUPtr else_stmts;

    while (true) {
        Ast::NodeList::Items cond_vals_itms;

        Ast::NodeUPtr lit = literal();
        cond_vals_itms.push_back(std::move(lit));

        while (tokenIs(Token::Comma)) {
            token = lexer.getNextToken();
            lit = literal();
            cond_vals_itms.push_back(std::move(lit));
        }

        expect(Token::Colon, "Se esperaban ':'");
        skipOptionalEOL();
        
        Ast::NodeUPtr stmts = statementList();
        Ast::NodeUPtr cond_blk =
                                std::make_unique<Ast::CaseStmt::CondBlock>(
                                    std::make_unique<Ast::NodeList>(std::move(cond_vals_itms)),
                                    std::move(stmts)
                                );

        cond_blk_items.push_back(std::move(cond_blk));

        if (tokenIs(Token::KwSino)) {
            token = lexer.getNextToken();

            expect(Token::Colon, "Se esperaban ':'");
            skipOptionalEOL();
            
            else_stmts = statementList();

            expect(Token::KwFinCaso, "Se esperaba 'fin caso'");

            break;
        }
        if (tokenIs(Token::KwFinCaso)) {
            token = lexer.getNextToken();
            break;
        }
    }

    Ast::NodeUPtr cond_blks = std::make_unique<Ast::NodeList>(std::move(cond_blk_items));

    Ast::NodeUPtr s =
        std::make_unique<Ast::CaseStmt>(std::move(var_expr), std::move(cond_blks), std::move(else_stmts));

    s->setSrcLine(srcline);

    return s;
}

Ast::NodeUPtr LppParser::literal()
{
    Ast::NodeUPtr lit1;
    switch (token)
    {
        case Token::IntConst:
            lit1 = std::make_unique<Ast::IntConstExpr>(std::stoi(lexer.getText()));
            break;
        case Token::RealConst:
            lit1 = std::make_unique<Ast::RealConstExpr>(std::stod(lexer.getText()));
            break;
        case Token::CharLiteral:
            lit1 = std::make_unique<Ast::CharConstExpr>(lexer.getText()[0]);
            break;
        default:
            throw LPPException(lexer.getLine(), "Se esperaba una constante entera, real o caracter");
    }
    token = lexer.getNextToken();

    if (tokenIs(Token::RangeInd)) {
        token = lexer.getNextToken();

        Ast::NodeUPtr lit2;
        switch (token)
        {
            case Token::IntConst:
                lit2 = std::make_unique<Ast::IntConstExpr>(std::stoi(lexer.getText()));
                break;
            case Token::RealConst:
                lit2 = std::make_unique<Ast::RealConstExpr>(std::stod(lexer.getText()));
                break;
            case Token::CharLiteral:
                lit2 = std::make_unique<Ast::CharConstExpr>(lexer.getText()[0]);
                break;
            default:
                throw LPPException(lexer.getLine(), "Se esperaba una constante entera, real o caracter");
        }
        token = lexer.getNextToken();

        Ast::NodeUPtr litn = std::make_unique<Ast::CaseStmt::CondRangeValue>(std::move(lit1), std::move(lit2));

        return litn;
    }

    return lit1;
}

Ast::NodeUPtr LppParser::whileStmt()
{
    token = lexer.getNextToken();

    Ast::NodeUPtr cond = expression();
    expect(Token::KwHaga, "Se esperaba la palabra 'haga'");
    expectEOL();
    
    Ast::NodeUPtr stmts = statementList();

    expect(Token::KwFinMientras, "Se esperaba 'fin mientras'");

    Ast::NodeUPtr s = std::make_unique<Ast::WhileStmt>(std::move(cond), std::move(stmts));

    return s;
}

Ast::NodeUPtr LppParser::repeatStmt()
{
    token = lexer.getNextToken();
    expectEOL();
    
    Ast::NodeUPtr stmts = statementList();
    expect(Token::KwHasta, "Se esperaba la palabra 'hasta'");

    Ast::NodeUPtr cond = expression();

    Ast::NodeUPtr s = std::make_unique<Ast::RepeatStmt>(std::move(cond), std::move(stmts));

    return s;
}

Ast::NodeUPtr LppParser::callStmt()
{
    int srcline = lexer.getLine();
    token = lexer.getNextToken();

    std::string text = expect(Token::Ident, "Se esperaba un identificador");

    Ast::NodeUPtr args;
    if (tokenIs(Token::OpenPar)) {
        token = lexer.getNextToken();
        
        args = exprList();

        expect(Token::ClosePar, "Se esperaba ')'");
    } else {
        args = std::make_unique<Ast::NodeList>();
    }

    if (token != Token::EndOfLine)
        throw LPPException(lexer.getLine(), "Error de sintaxis en la proposicion");

    Ast::NodeUPtr fce = std::make_unique<Ast::FuncCallExpr>(text, std::move(args));
    fce->setSrcLine(srcline);

    return std::make_unique<Ast::CallStmt>(std::move(fce));
}

Ast::NodeUPtr LppParser::forStmt()
{
    int src_line = lexer.getLine();
    token = lexer.getNextToken();

    Ast::NodeUPtr lhs = variable(std::nullopt);
    expect(Token::OpAssign, "Se esperaba operador '<-'");
    Ast::NodeUPtr expr1 = expression();
    expect(Token::KwHasta, "Se esperaba la palabra 'hasta'");
    Ast::NodeUPtr expr2 = expression();
    expect(Token::KwHaga, "Se esperaba la palabra 'haga'");
    expectEOL();
    Ast::NodeUPtr stmts = statementList();

    expect(Token::KwFinPara, "Se esperaba la palabra 'fin para'");

    Ast::NodeUPtr the_stmt = std::make_unique<Ast::ForStmt>(
                                std::move(lhs),
                                std::move(expr1),
                                std::move(expr2),
                                std::move(stmts)
                                );

    the_stmt->setSrcLine(src_line);

    return the_stmt;
}

Ast::NodeUPtr LppParser::readStmt()
{
    int srcline = lexer.getLine();
    token = lexer.getNextToken();

    Ast::NodeUPtr var = variable(std::nullopt);

    Ast::NodeList::Items ritms;

    ritms.push_back(std::move(var));
    while (tokenIs(Token::Comma)) {
        token = lexer.getNextToken();

        Ast::NodeUPtr var = variable(std::nullopt);

        ritms.push_back(std::move(var));
    }

    Ast::NodeUPtr stmt = std::make_unique<Ast::ReadStmt>(std::make_unique<Ast::NodeList>(std::move(ritms)));
    stmt->setSrcLine(srcline);

    return stmt;
}

Ast::NodeUPtr LppParser::writeStmt()
{
    int srcline = lexer.getLine();
    token = lexer.getNextToken();

    Ast::NodeList::Items expr_itms;
    Ast::NodeUPtr expr_n = expression();

    expr_itms.push_back(std::move(expr_n));

    while (tokenIs(Token::Comma)) {
        token = lexer.getNextToken();
        expr_n = expression();

        expr_itms.push_back(std::move(expr_n));
    }

    Ast::NodeUPtr exprs = std::make_unique<Ast::NodeList>(std::move(expr_itms));
    Ast::NodeUPtr s = std::make_unique<Ast::WriteStmt>(std::move(exprs));
    s->setSrcLine(srcline);

    return s;
}

Ast::NodeUPtr LppParser::returnStmt()
{
    int srcline = lexer.getLine();
    token = lexer.getNextToken();

    if (tokenIs(Token::EndOfLine)) {
        return std::make_unique<Ast::ReturnStmt>();
    } else {
        Ast::NodeUPtr expr_n = expression();

        Ast::NodeUPtr s = std::make_unique<Ast::ReturnStmt>(std::move(expr_n));
        s->setSrcLine(srcline);

        return s;
    }
}

Ast::NodeUPtr LppParser::openFileStmt()
{
    int srcline = lexer.getLine();

    token = lexer.getNextToken();
    Ast::NodeUPtr n_expr = expression();
    expect(Token::KwComo, "Se esperaba la palabra 'como'");
    Ast::NodeUPtr n_var = variable(std::nullopt);

    Ast::OpenFileStmt::Flags oflags;
    if (tokenIs(Token::KwPara)) {
        expect(Token::KwPara, "");

        switch (token) {
            case Token::KwLectura: oflags = Ast::OpenFileStmt::Flags::Read; break;
            case Token::KwEscritura: oflags = Ast::OpenFileStmt::Flags::Write; break;
            default:
                throw LPPException(lexer.getLine(), "Se esperaba la palabra 'lectura' o 'escritura'");
        }

        token = lexer.getNextToken();


        if (tokenIs(Token::Comma)) {
            expect(Token::Comma, "");

            switch (token) {
                case Token::KwLectura:
                    if (oflags == Ast::OpenFileStmt::Flags::Read) {
                        throw LPPException(lexer.getLine(), "No puede especificar la misma operacion dos veces");
                    }
                    break;

                 case Token::KwEscritura:
                    if (oflags == Ast::OpenFileStmt::Flags::Write) {
                        throw LPPException(lexer.getLine(), "No puede especificar la misma operacion dos veces");
                    }
                    break;

                default:
                    throw LPPException(lexer.getLine(), "Se esperaba la palabra 'lectura' o 'escritura'");
            }
            oflags = Ast::OpenFileStmt::Flags::ReadWrite;
            token = lexer.getNextToken();
        }
    }

    Ast::NodeUPtr n_stmt = std::make_unique<Ast::OpenFileStmt>(std::move(n_expr), std::move(n_var), oflags);
    n_stmt->setSrcLine(srcline);

    return n_stmt;
}

Ast::NodeUPtr LppParser::closeFileStmt()
{
    int srcline = lexer.getLine();
    token = lexer.getNextToken();

    Ast::NodeUPtr n_var = variable(std::nullopt);
    Ast::NodeUPtr n_stmt = std::make_unique<Ast::CloseFileStmt>(std::move(n_var));
    n_stmt->setSrcLine(srcline);

    return n_stmt;
}

Ast::NodeUPtr LppParser::readFileStmt()
{
    int srcline = lexer.getLine();

    token = lexer.getNextToken();
    Ast::NodeUPtr n_var = variable(std::nullopt);

    Ast::NodeList::Items itms;
    itms.push_back(std::move(n_var));

    do {
        expect(Token::Comma, "Se esperaba ','");

        n_var = variable(std::nullopt);
        itms.push_back(std::move(n_var));
    } while (tokenIs(Token::Comma));

    Ast::NodeUPtr n_lst = std::make_unique<Ast::NodeList>(std::move(itms));
    n_lst->setSrcLine(srcline);
    Ast::NodeUPtr n_stmt = std::make_unique<Ast::ReadFileStmt>(std::move(n_lst));
    n_stmt->setSrcLine(srcline);

    return n_stmt;
}

Ast::NodeUPtr LppParser::writeFileStmt()
{
    int srcline = lexer.getLine();

    token = lexer.getNextToken();
    Ast::NodeUPtr n_var = variable(std::nullopt);

    Ast::NodeList::Items itms;
    itms.push_back(std::move(n_var));

    do {
        expect(Token::Comma, "Se esperaba ','");

        Ast::NodeUPtr n_expr = expression();
        itms.push_back(std::move(n_expr));
    } while (tokenIs(Token::Comma));

    Ast::NodeUPtr n_lst = std::make_unique<Ast::NodeList>(std::move(itms));
    n_lst->setSrcLine(srcline);
    Ast::NodeUPtr n_stmt = std::make_unique<Ast::WriteFileStmt>(std::move(n_lst));
    n_stmt->setSrcLine(srcline);

    return n_stmt;
}

void LppParser::skipEOL()
{
    token = lexer.getNextToken();
    skipOptionalEOL();
}

void LppParser::skipOptionalEOL()
{
    while (tokenIs(Token::EndOfLine))
        token = lexer.getNextToken();
}

void LppParser::expectEOL()
{
    expect(Token::EndOfLine, "Se esperaba fin de linea");
    while (tokenIs(Token::EndOfLine))
        token = lexer.getNextToken();
}

std::string LppParser::expect(Token tk, const std::string &message)
{
    std::string text = lexer.getText();

    if (token != tk)
        throw LPPException(lexer.getLine(), message);

    token = lexer.getNextToken();

    return text;
}
