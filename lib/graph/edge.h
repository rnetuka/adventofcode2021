//
// Created by rnetuka on 16.12.21.
//

#pragma once

#include "../hash.h"
#include "node.h"

namespace lib {

    class Edge {
    public:
        const Node from;
        const Node to;
        const int length;

        Edge();
        Edge(const Node& from, const Node& to, int length = 1);

        bool contains(const Node& node) const;
        bool contains_both(const Node& a, const Node& b) const;
        bool operator==(const Edge& other) const;
    };

}

template <>
struct std::hash<lib::Edge> {

    std::size_t operator()(const lib::Edge& edge) const {
        std::size_t hash = 0;
        lib::hash_combine(hash, edge.from);
        lib::hash_combine(hash, edge.to);
        lib::hash_combine(hash, edge.length);
        return hash;
    }

};