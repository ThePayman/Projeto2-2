#include "stdafx.h"
#include "Player.h"


Player::Player(string set_name) {
	name = set_name;
}

int Player::seconds_taken() {
	return end_time - start_time;
}

void Player::set_score() {
	
}

Player::~Player()
{
}
