//
// Created by rnetuka on 16.12.21.
//

#include <algorithm>
#include <optional>
#include <limits>
#include "../algorithm.h"
#include "../map.h"
#include "../set.h"
#include "graph.h"

namespace lib {

    void Graph::add(const Node& node) {
        nodes.insert(node);
    }

    void Graph::connect(const Node& a, const Node& b, int length) {
        nodes.insert(a);
        nodes.insert(b);
        edges.insert({ a, b, length });
    }

    const Edge& Graph::edge(const Node& from, const Node& to) const {
        for (auto& edge : edges)
            if (edge.from == from && edge.to == to)
                return edge;
        throw "No edge found";
    }

    set<Edge> Graph::edges_from(const Node& node) const {
        set<Edge> result;
        for (auto& edge : edges)
            if (edge.from == node)
                result.insert(edge);
        return result;
    }

    set<Node> Graph::neighbors_of(const Node& node) const {
        set<Node> neighbors;
        for (auto& edge : edges_from(node))
            neighbors.insert(edge.to);
        return neighbors;
    }

    Path Graph::shortest_path(const Node& start, const Node& end) const {
        const double infinity = std::numeric_limits<double>::infinity();

        set<Node> unvisited;

        map<Node, double> distances;
        map<Node, std::optional<Node>> previous;

        for (auto& node : nodes) {
            distances[node] = infinity;
            previous[node] = std::nullopt;
            unvisited.insert(node);
        }

        distances[start] = 0;

        while (! unvisited.empty()) {
            Node current = *min_element(unvisited.begin(), unvisited.end(), [&distances](const Node& a, const Node& b) {
                return distances[a] < distances[b];
            });

            unvisited.erase(current);

            for (auto& neighbor : neighbors_of(current)) {
                double alt = distances[current] + edge(current, neighbor).length;
                if (alt < distances[neighbor]) {
                    distances[neighbor] = alt;
                    previous[neighbor] = current;
                }
            }
        }

        double distance = distances[end];

        if (distance == infinity)
            return { };

        Path path { static_cast<int>(distance) };
        Node current = end;
        while (previous[current]) {
            path.prepend(current);
            current = *previous[current];
        }
        path.prepend(start);
        return path;
    }

}