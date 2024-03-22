#include "stdafx.h"
#include "enemy.h"
enemy::enemy(std::string type, float health, float speed, float bounty, float exp) : type(type), health(health), speed(speed), bounty(bounty), exp(exp){

}
std::string enemy::GetType() {
	return type;
}
float enemy::Gethealth() {
	return health;
}
float enemy::Getspeed() {
	return speed;
}
float enemy::Getbounty() {
	return bounty;
}
float enemy::Getexp() {
	return exp;
}
void enemy::SetPicPath(std::string picPath) {
	this->picPath = picPath;
}