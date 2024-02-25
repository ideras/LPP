#include "lpp_ast.h"

namespace Ast
{

std::string Node::kindName() const
{
    switch (getKind()) {
        case NodeKind::Node: return "Node";
        case NodeKind::NodeList: return "NodeList";
        case NodeKind::StrList: return "StrList";
        case NodeKind::Program: return "Program";
        case NodeKind::SubtypeDef: return "SubtypeDef";
        case NodeKind::RecordDef: return "RecordDef";
        case NodeKind::VarDecl: return "VarDecl";
        case NodeKind::IntType: return "IntType";
        case NodeKind::RealType: return "RealType";
        case NodeKind::BoolType: return "BoolType";
        case NodeKind::CharType: return "CharType";
        case NodeKind::StringType: return "StringType";
        case NodeKind::StringTypeSize: return "StringTypeSize";
        case NodeKind::ArrayType: return "ArrayType";
        case NodeKind::UserType: return "UserType";
        case NodeKind::SeqFileType: return "SeqFileType";
        case NodeKind::BinFileType: return "BinFileType";
        case NodeKind::Collection: return "Collection";
        case NodeKind::ProcDef: return "ProcDef";
        case NodeKind::ParamDef: return "ParamDef";
        case NodeKind::BinaryExpr: return "BinaryExpr";
        case NodeKind::LtExpr: return "LtExpr";
        case NodeKind::GtExpr: return "GtExpr";
        case NodeKind::EqExpr: return "EqExpr";
        case NodeKind::NeqExpr: return "NeqExpr";
        case NodeKind::LteExpr: return "LteExpr";
        case NodeKind::GteExpr: return "GteExpr";
        case NodeKind::AddExpr: return "AddExpr";
        case NodeKind::SubExpr: return "SubExpr";
        case NodeKind::MultExpr: return "MultExpr";
        case NodeKind::IDivExpr: return "IDivExpr";
        case NodeKind::DivExpr: return "DivExpr";
        case NodeKind::ModExpr: return "ModExpr";
        case NodeKind::PowExpr: return "PowExpr";
        case NodeKind::OrExpr: return "OrExpr";
        case NodeKind::AndExpr: return "AndExpr";
        case NodeKind::NotExpr: return "NotExpr";
        case NodeKind::NegExpr: return "NegExpr";
        case NodeKind::PlusExpr: return "PlusExpr";
        case NodeKind::FuncCallExpr: return "FuncCallExpr";
        case NodeKind::LhsExpr: return "VarExpr";
        case NodeKind::IndexVar: return "IndexVar";
        case NodeKind::SimpleVar: return "SimpleVar";
        case NodeKind::BoolConstExpr: return "BoolConstExpr";
        case NodeKind::StrConstExpr: return "StrConstExpr";
        case NodeKind::CharConstExpr: return "CharConstExpr";
        case NodeKind::IntConstExpr: return "IntConstExpr";
        case NodeKind::RealConstExpr: return "RealConstExpr";
        case NodeKind::AssignStmt: return "AssignStmt";
        case NodeKind::IfStmt: return "IfStmt";
        case NodeKind::IfStmtCondBlock: return "IfStmtCondBlock";
        case NodeKind::CaseStmt: return "CaseStmt";
        case NodeKind::CaseStmtCondBlock: return "CaseStmtCondBlock";
        case NodeKind::CaseStmtCondRangeValue: return "CaseStmtCondRangeValue";
        case NodeKind::WhileStmt: return "WhileStmt";
        case NodeKind::RepeatStmt: return "RepeatStmt";
        case NodeKind::ForStmt: return "ForStmt";
        case NodeKind::ReadStmt: return "ReadStmt";
        case NodeKind::WriteStmt: return "WriteStmt";
        case NodeKind::OpenFileStmt: return "OpenFileStmt";
        case NodeKind::ReadFileStmt: return "ReadFileStmt";
        case NodeKind::WriteFileStmt: return "WriteFileStmt";
        case NodeKind::CloseFileStmt: return "CloseFileStmt";
        case NodeKind::ReturnStmt: return "ReturnStmt";
        default:
            return "Unknown";
    }
}

} // namespace Ast
