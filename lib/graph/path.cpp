//
// Created by rnetuka on 16.12.21.
//

#include "path.h"

namespace lib {

    Path::Path() : length { 0 } {

    }

    Path::Path(int length) : length { length } {

    }

    void Path::prepend(const Node& node) {
        nodes.push_front(node);
    }

    auto Path::begin() -> decltype(nodes.begin()) {
        return nodes.begin();
    }

    auto Path::end() -> decltype(nodes.end()) {
        return nodes.end();
    }

    ostream& operator<<(ostream& stream, const Path& path) {
        for (int i = 0; i < path.nodes.size(); i++) {
            stream << path.nodes[i];
            if (i < path.nodes.size() - 1)
                stream << " -> ";
        }
        return stream;
    }

}