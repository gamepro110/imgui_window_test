#pragma once

#include <tuple>
#include <type_traits>

namespace ImGUIWindow {
	struct CallbackBase {
		typedef void(*Function)(CallbackBase*);

		CallbackBase(Function fn) :
			func(fn) {
		}

		void Invoke() {
			func(this);
		}

		Function func{ nullptr };
	};

//----------------------------------------------------------------------
	class CallbackVoid : public CallbackBase {
		typedef void(*Function)();

	public:
		CallbackVoid(Function fn) :
			CallbackBase([](CallbackBase* base) { static_cast<CallbackVoid*>(base)->Invoke(); }),
			func(fn)
		{
		}

	private:
		void Invoke() {
			func();
		}

	private:
		Function func{ nullptr };
	};

//----------------------------------------------------------------------
	template<typename ... Args>
	class CallbackArg : public CallbackBase {
		typedef void(*Function)(Args ... args);
		using Arguments = std::tuple<Args...>;

	public:
		CallbackArg(Function fn, Args ... args) :
			CallbackBase([](CallbackBase* base) { static_cast<CallbackArg*>(base)->Invoke(); }),
			func(fn),
			arguments(std::forward<Args>(args)...) {
		}

	private:
		void Invoke() {
			std::apply(func, arguments);
		}

	private:
		Function func{ nullptr };
		Arguments arguments{};
	};

//----------------------------------------------------------------------
	template<typename ... Args>
	class ArgUnwrapper {
	public:
		ArgUnwrapper(Args ... args) :
			argItems(std::make_tuple<Args...>(std::forward<Args>(args)...))
		{}

		template<typename T, int Index>
		T Get() {
			return std::get<Index>(argItems);
		}

	private:
		std::tuple<Args...> argItems;
	};
}
