# include "AGameEntity.hpp"

AGameEntity::AGameEntity() : x(0), y(0), move_ap(0), shoot_ap(0) {
}


AGameEntity::AGameEntity(int x, int y, int move_ap, int shoot_ap) : x(x), y(y), move_ap(move_ap), shoot_ap(shoot_ap) {
}

AGameEntity::AGameEntity(AGameEntity const &instance)
{
	*this = instance;
}

AGameEntity& AGameEntity::operator=(AGameEntity const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->move_ap = rhs.move_ap;
	this->shoot_ap = rhs.shoot_ap;
	return *this;
}

AGameEntity::~AGameEntity() {
}

int		AGameEntity::getX() const {
	return this->x;
}

int		AGameEntity::getY() const {
	return this->y;
}

int		AGameEntity::getMoveAP() const {
	return this->move_ap;
}

int		AGameEntity::getShootAP() const {
	return this->shoot_ap;
}
