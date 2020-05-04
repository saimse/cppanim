#include "testsuite.hpp"

#include <atomic>
#include <thread>

namespace cppanim::test {

	TestController& TestController::getInstance()
	{
	        static TestController instance;
		return instance;
	}
	
	TestController::TestController() : units(), resultLock(), results()
	{}

	void TestController::addUnit(Unit *u) { units.push_back(u); }
	void TestController::emplaceUnit(const std::string& uid,
					 Unit::result_t (*run)())
	{ units.push_back(new Unit(uid, run)); }


	std::tuple<int, int, int> TestController::runTests()
	{
		// success / warning / error
		std::atomic_int results[3] = {{0}, {0}, {0}};

                #pragma omp parallel
		{
		        #pragma omp for
			for(auto u : units) {
				auto result = (*u)();
				results[result]++;
				
				resultLock.lock();
				this->results[u] = result;
				resultLock.unlock();
			}
		}
		
		return std::tuple<int, int, int>(results[0].load(),
						 results[1].load(),
						 results[2].load());
	}
	
}
