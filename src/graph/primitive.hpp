#pragma once

struct SimpleEdge {
    int to;
};
ostream& operator<<(ostream& os, const SimpleEdge& e) {
    return os << "E(" << e.to << ")";
}
