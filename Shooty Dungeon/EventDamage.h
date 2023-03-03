#pragma once

#include "../DragonFly Engine/Event.h"

// String identifier for event
const std::string DAMAGE_EVENT = "damage";

class EventDamage : public df::Event
{
public:
	EventDamage();
};