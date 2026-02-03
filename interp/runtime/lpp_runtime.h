#ifndef __LPP_RUNTIME_H__
#define __LPP_RUNTIME_H__

#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <limits>
#include <algorithm>
#include <functional>
#include "lpp_variant.h"

class Terminal;
class LppFileManager;

using IFunc = std::function<LppVariant(std::vector<LppVariant>&)>;

class LppRuntime {
public:
    LppRuntime(Terminal& term, LppFileManager& file_mgr)
      : term(term),
        file_mgr(file_mgr),
        funcs(),
        randEng(56875375),
        randDist(0.0, 1.0)
    { init(); }

    bool contains(const std::string& fname) const;
    LppVariant call(const std::string& fname, std::vector<LppVariant>& argv);

private:
    void init();

private:
    Terminal& term;
    LppFileManager& file_mgr;
    std::unordered_map<std::string, IFunc> funcs;
    std::default_random_engine randEng;
    std::uniform_real_distribution<Lpp::Real> randDist;
};

#endif

