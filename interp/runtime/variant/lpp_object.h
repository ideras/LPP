#ifndef LPP_OBJECT_H
#define LPP_OBJECT_H

#include <memory>
#include <string>

enum class LppObjectKind
{
    String,
    Array,
    Record
};

class LppObject
{
public:
    virtual ~LppObject() = default;

    virtual LppObjectKind kind() const = 0;
    virtual std::shared_ptr<LppObject> clone() const = 0;
    virtual std::string toString() const = 0;
};

#endif // LPP_OBJECT_H
