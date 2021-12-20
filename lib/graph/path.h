//
// Created by rnetuka on 16.12.21.
//

#pragma once

#include "../iostream.h"
#include "../vector.h"
#include "node.h"

namespace lib {

    class Path {
    private:
        vector<Node> nodes;

    public:
        const int length;

        Path();
        Path(int length);

        void prepend(const Node& node);
        auto begin() -> decltype(nodes.begin());
        auto end() -> decltype(nodes.end());

        friend ostream& operator<<(ostream& stream, const Path& path);
    };

}