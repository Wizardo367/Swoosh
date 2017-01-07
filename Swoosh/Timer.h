#pragma once

class Timer
{
private:
	// Variables
	float m_LastTime;
public:
	// Constructor
	Timer();
	// Destructor
	~Timer();
	// Methods
	void reset();
	// Function
	float getDeltaTime();
};