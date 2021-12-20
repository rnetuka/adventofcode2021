//
// Created by rnetuka on 14.12.21.
//

#pragma once

#include <map>
#include <string>
#include "../set.h"
#include "node.h"
#include "edge.h"
#include "path.h"

namespace lib {

    class Graph {
    private:
        set<Node> nodes;
        set<Edge> edges;
    public:
        const Edge& edge(const Node& from, const Node& to) const;

    public:
        void add(const Node& node);
        void connect(const Node& a, const Node& b, int length = 1);
        set<Edge> edges_from(const Node& node) const;
        set<Node> neighbors_of(const Node& node) const;

        Path shortest_path(const Node& start, const Node& end) const;

    };

    using graph = Graph;
    using edge = Edge;

}