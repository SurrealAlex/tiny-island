#include "item.h"

class Coconut : public Item {
    public:
    Coconut(int wrldX, int wrldY);
    void events(Map& map) override;
    void update(Map& map) override;
    void draw(Map& map, Assets& assets) override;
};