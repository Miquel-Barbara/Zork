#include "Enemy.h"
#include "Player.h"
#include "../Utils.h"

Enemy::Enemy(const string& name, const string& description, map<StatType, StatValue*> stats, vector<string> attackDescription, string deadDescription) : Creature(name, description, stats), attackDescription(attackDescription), deadDescription(deadDescription) {}

void Enemy::Tick() {
	if (IsDead()) return;

    for (Entity* obj : GetCurrentRoom()->GetInventory()) {
		Player* player = dynamic_cast<Player*>(obj);
		if (player) {
			int descriptionToShow = RandomRange(attackDescription.size() - 1);
			cout << attackDescription[descriptionToShow];
			Attack(player);
			return;
		}
    }
}

void Enemy::Die() {
	cout << deadDescription << endl;
	currentRoom->RemoveItem(this);
}

