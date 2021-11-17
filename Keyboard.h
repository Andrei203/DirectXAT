#pragma once
#include <bitset>
class Keyboard
{
public:
	void SetKey(unsigned int key, bool value);
	void Tick();

	bool GetKeyDown(unsigned int key);
	bool GetKeyUp(unsigned int key);
	bool GetKey(unsigned int key);

	bool inputEnabled = true;

private:
	std::bitset<256U> pendingKeystates;
	std::bitset<256U> keystates;
	std::bitset<256U> prevKeystates;

};

