// Copyright 2018 Dynarmic Project / 2018 Marssel Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <functional>
#include <iosfwd>

#include "common/types.h"

namespace Marssel::IR {

class LocationDescriptor {
public:
    explicit LocationDescriptor(u64 value) : value(value) {}

    bool operator == (const LocationDescriptor& o) const {
        return value == o.Value();
    }

    bool operator != (const LocationDescriptor& o) const {
        return !operator==(o);
    }

    u64 Value() const { return value; }

private:
    u64 value;
};

std::ostream& operator<<(std::ostream& o, const LocationDescriptor& descriptor);

} // namespace Marssel::IR

namespace std {
template <>
struct less<Marssel::IR::LocationDescriptor> {
    bool operator()(const Marssel::IR::LocationDescriptor& x, const Marssel::IR::LocationDescriptor& y) const {
        return x.Value() < y.Value();
    }
};
template <>
struct hash<Marssel::IR::LocationDescriptor> {
    size_t operator()(const Marssel::IR::LocationDescriptor& x) const {
        return std::hash<u64>()(x.Value());
    }
};
} // namespace std
