#include <vector>
#include <memory>
#include "player.h"
#include "tree.h"
#include "rock.h"
#include "minimap.h"

class EntityHandler {
    private:
        std::unique_ptr<Player> player = std::make_unique<Player>();
        std::vector<std::unique_ptr<Tree>> trees;
        std::vector<std::unique_ptr<Rock>> rocks;
        std::vector<Entity*> visibleEntities;

        Minimap minimap;
    
    public:
        void generateEntities(Map& map);
        void checkEntityCollisions();

        void events(Map& map);
        void update(Map& map);
        void draw(Map& map, Assets& assets);
};