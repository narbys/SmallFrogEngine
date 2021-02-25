#pragma once
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
	};

	class BeepboopCommand : public Command
	{
	public:
		virtual void Execute() override {};
	};
}