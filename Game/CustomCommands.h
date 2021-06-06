#pragma once
#include "Command.h"
#include "QbertComponent.h"

//Move BottomLeft
class MoveQbertBottomLeftCommand final : public frog::Command
{
public:
	MoveQbertBottomLeftCommand(QbertComponent* qbert)
		: m_pQbert{ qbert }
	{}
	void Execute() override
	{
		m_pQbert->MoveDownLeft();
	}
private:
	QbertComponent* m_pQbert;
	
};

//Move BottomRight
class MoveQbertBottomRightCommand final : public frog::Command
{
public:
	MoveQbertBottomRightCommand(QbertComponent* qbert)
		: m_pQbert{ qbert }
	{}
	void Execute() override
	{
		m_pQbert->MoveDownRight();
	}
private:
	QbertComponent* m_pQbert;
};

//Move UpLeft
class MoveQbertUpLeftCommand final : public frog::Command
{
public:
	MoveQbertUpLeftCommand(QbertComponent* qbert)
		: m_pQbert{ qbert }
	{}
	void Execute() override
	{
		m_pQbert->MoveUpLeft();
	}
private:
	QbertComponent* m_pQbert;
};

//Move UpRight
class MoveQbertUpRightCommand final : public frog::Command
{
public:
	MoveQbertUpRightCommand(QbertComponent* qbert)
		: m_pQbert{ qbert }
	{}
	void Execute() override
	{
		m_pQbert->MoveUpRight();
	}
private:
	QbertComponent* m_pQbert;
};
