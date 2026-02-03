#include "lpp_proc_info.h"

void ProcFrame::addVar(const std::string &name, const TypeInfoSPtr &type)
{
    LppVarSPtr the_var = std::make_shared<LppVar>(name, type);
    the_var->createValue();

    _vars.add(name, the_var);
}

void ProcFrame::addVar(const std::string &name, const TypeInfoSPtr &type, const LppVariant& val)
{
    LppVarSPtr the_var = std::make_shared<LppVar>(name, type);
    the_var->value() = val;

    _vars.add(name, the_var);
}

ProcFrameUPtr ProcInfo::makeProcFrame(const std::vector<LppVariant> &arg_vals)
{
    ProcFrameUPtr pfrm(new ProcFrame(ret_type));

    int index = 0;
    for (const auto& prm : params()) {
        pfrm->addVar(prm.name(), prm.type(), arg_vals[index]);
        index++;
    }

    for (const auto& var : variables()) {
        pfrm->addVar(var.name(), var.type());
        index++;
    }

    return pfrm;
}

ProcInfoSPtr ProcInfo::create(const std::string &name, const std::initializer_list<Param> &params, const TypeInfoSPtr &rt_type)
{
    return std::make_shared<ProcInfo>(name, params, rt_type);
}
