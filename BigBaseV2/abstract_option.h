#pragma once

namespace big::ui
{
	enum class OptionAction
	{
		LeftPress,
		RightPress,
		EnterPress
	};

	enum class OptionFlag
	{
		Horizontal = (1 << 0),
		Enterable = (1 << 1),
		BoolAndNumber = (1 << 2),
		BoolOption = (1 << 3),
		Chooseable = (1 << 4),
		Break = (1 << 5),
		Textable = (1 << 6),
		Numberable = (1 << 7),
		Option = (1 << 8),
		Keyboard = (1 << 9),
		BoolAndChoose = (1 << 10),
		Color = (1 << 11),
		ChooseBool = (1 << 12)
	};

	class AbstractOption
	{
	public:
		virtual ~AbstractOption() noexcept = default;

		virtual const char* GetLeftText() = 0;
		virtual const char* GetRightText() = 0;
		virtual const char* GetRightText2() = 0;
		virtual const char* GetRightText3() = 0;
		virtual const char* GetDescription() = 0;
		virtual void HandleAction(OptionAction action) = 0;
		virtual void SetValue(double text) = 0;
		virtual void SetValue(std::string text) = 0;
		virtual bool GetFlag(OptionFlag flag) = 0;
		virtual std::function<void()> GetAction() = 0;
	protected:
		explicit AbstractOption() = default;
		AbstractOption(AbstractOption const&) = default;
		AbstractOption& operator=(AbstractOption const&) = default;
		AbstractOption(AbstractOption&&) = default;
		AbstractOption& operator=(AbstractOption&&) = default;
	};
}
