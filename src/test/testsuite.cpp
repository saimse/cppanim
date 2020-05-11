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

       	TestController::~TestController()
	{
		for(auto u : units) delete u;
	}

	void TestController::addUnit(Unit *u) { units.push_back(u); }
	void TestController::emplaceUnit(const std::string& uid,
					 Unit::result_t (*run)())
	{ units.push_back(new Unit(uid, run)); }


	std::tuple<int, int, int> TestController::runTests()
	{
		// success / warning / error
		std::atomic_int results[3] = {{0}, {0}, {0}};

                #if defined(_WIN32) || defined(NO_OMP)
                #pragma omp parallel
		{
		        #pragma omp for
		#endif
		        for(std::size_t i = 0;
			    i < units.size(); i++) {
				auto result = (*units[i])();
				results[result]++;
				
				resultLock.lock();
				this->results[units[i]] = result;
				resultLock.unlock();
			}
		#if defined(_WIN32) || defined(NO_OMP)
		}
		#endif		
		
		return std::tuple<int, int, int>(results[0].load(),
						 results[1].load(),
						 results[2].load());
	}
	
}
