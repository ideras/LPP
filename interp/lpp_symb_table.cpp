#include <cstring>
#include "lpp_symb_table.h"
#include "lpp_exception.h"
#include "str_util.h"

int SizeOfType(int nTypeDef)
{
    switch (nTypeDef)
    {
    case TD_ENTERO	: return sizeof(Integer);
        case TD_REAL	: return sizeof(Real);
        case TD_BOOL	: return sizeof(Bool);
        case TD_CHAR	: return sizeof(Char);
    }
    return 0;
}

//Implementacion de la clase ProcDef
const ParamDef *ProcDef::getParam(const std::string& id) const
{
    std::string lower_id = str::lower(id);

    for (const auto& p : param_defs) {
        std::string param_name = str::lower(p->getName());

        if (lower_id == param_name) {
            return p.get();
        }
    }

    return nullptr;
}

void ProcDef::addDeclsToActRecord(ProcActRecord *act_rec)
{
    for (const auto& decl : decls) {
        for (const auto& id : decl.ids) {
            if (!act_rec->containsVar(id)) {
                std::unique_ptr<LppVar> up_var (new TVar(id));
                up_var->setSemType(decl.sem_type, true);

                act_rec->addVar(std::move(up_var));
            }
            else
                throw LPPException(decl.src_line, "Declaracion duplicada de '" + id + "'");
        }
    }
}
//Fin de la implementacion de la clase ProcDef

RecFieldDef* TRecord::getFieldDef(const std::string& id)
{
    std::string lower_id = str::lower(id);

    for (const auto& p : member_list)
    {
        std::string param_name = str::lower(p->getName());

        if (lower_id == param_name)
        {
            return p.get();
        }
    }

    return nullptr;
}

LppVar* SymbolTable::getVar(const std::string& id)
{
    std::string lower_id = str::lower(id);

    auto it = var_map.find(lower_id);

    if (it == var_map.end()) {
        return nullptr;
    }

    return it->second.get();
}

ProcDef *SymbolTable::getSubprg(const std::string &id)
{
    std::string lower_id = str::lower(id);

    auto it = subprg_map.find(lower_id);

    if (it == subprg_map.end()) {
        return nullptr;
    }

    return it->second.get();
}

Subtype *SymbolTable::getSubtype(const std::string& id)
{
    std::string lower_id = str::lower(id);

    auto it = subtype_map.find(lower_id);

    if (it == subtype_map.end()) {
        return nullptr;
    }

    return it->second.get();
}

TRecord *SymbolTable::getRecord(const std::string& id)
{
    std::string lower_id = str::lower(id);

    auto it = record_map.find(lower_id);

    if (it == record_map.end()) {
        return nullptr;
    }

    return it->second.get();
}

void SymbolTable::addVar(std::unique_ptr<LppVar>&& p_var)
{
    std::string lower_key = str::lower(p_var->getName());

    var_map[lower_key] = std::move(p_var);
}

void SymbolTable::addSubprg(std::unique_ptr<ProcDef> &&p_proc)
{
    std::string lower_key = str::lower(p_proc->getName());

    subprg_map[lower_key] = std::move(p_proc);
}

void SymbolTable::addSubtype(std::unique_ptr<Subtype>&& p_subtype)
{
    std::string lower_key = str::lower(p_subtype->getName());

    subtype_map[lower_key] = std::move(p_subtype);
}

void SymbolTable::addRecord(std::unique_ptr<TRecord>&& p_record)
{
    std::string lower_key = str::lower(p_record->getName());

    record_map[lower_key] = std::move(p_record);
}

SemType::SemType(int td)
    : type_cat(td)
{
    size = SizeOfType(type_cat);
}

SemType::SemType(int td, int size)
    : type_cat(td), size(size)
{}

LppVar *ProcActRecord::getVar(const std::string &id)
{
    std::string lower_id = str::lower(id);

    auto it = vars.find(lower_id);

    return (it == vars.end())? nullptr : it->second.get();
}

void ProcActRecord::addVar(std::unique_ptr<LppVar>&& up_var)
{
    std::string lower_key = str::lower(up_var->getName());

    vars[lower_key] = std::move(up_var);
}
