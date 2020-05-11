#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <mutex>

namespace cppanim::test {

//	typedef int (*Unit)(void);
	struct Unit {
		enum result_t { success, warning, error };

		const std::string uid;
		result_t (*run)();

		Unit(const std::string& u, result_t (*r)())
			: uid(u), run(r) {}
		
		result_t operator()() { return run(); }
	};


	class TestController {

		std::vector<Unit*> units;

		std::mutex resultLock;
		std::unordered_map<Unit*, int> results;

	public:

		TestController();
		~TestController();
		
		static TestController& getInstance();

		void addUnit(Unit *u);
		void emplaceUnit(const std::string& uid,
				 Unit::result_t (*run)());
		
		std::tuple<int, int, int> runTests();

	};

}
