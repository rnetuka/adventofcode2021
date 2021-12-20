//
// Created by rnetuka on 16.12.21.
//

#include "edge.h"

namespace lib {

    Edge::Edge() : length { 0 } {

    }

    Edge::Edge(const Node& from, const Node& to, int length) : from { from }, to { to }, length { length } {

    }

    bool Edge::contains(const Node& node) const {
        return node == from || node == to;
    }

    bool Edge::contains_both(const Node& a, const Node& b) const {
        return (from == a && to == b) || (from == b && to == a);
    }

    bool Edge::operator==(const Edge& other) const {
        return from == other.from && to == other.to && length == other.length;
    }

}