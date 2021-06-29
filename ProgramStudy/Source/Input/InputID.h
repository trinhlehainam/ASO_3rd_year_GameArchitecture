#pragma once

enum class INPUT_ID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BTN1,
	BTN2,
	BTN3,
	BTN4,
	MAX
};

static INPUT_ID begin(INPUT_ID) { return INPUT_ID::UP; }
static INPUT_ID end(INPUT_ID) { return INPUT_ID::MAX; }

static INPUT_ID operator ++(INPUT_ID& id)
{
	return id = static_cast<INPUT_ID>(static_cast<size_t>(id) + 1);
}

static INPUT_ID operator *(INPUT_ID id) { return id; }
