#include <lp3/sims/EventSimulator.hpp>
#include <lp3/sims/coroutine.hpp>
#include <fmt/core.h>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace sims = lp3::sims;


TEST_CASE("Sending Some Events", "[es-example-1]") {
    sims::EventSimulator simmy;

	std::vector<char> history;

	sims::EventType ON_HURT = 1;

	struct HurtMsg {
		int hp;
		std::string attacker;
	};
	simmy.subscribe<HurtMsg>(ON_HURT, [&history](HurtMsg hm) {
		fmt::print("You wound me for {} hp good sir {}.", hm.hp, hm.attacker);
		history.push_back('c');
	});

	simmy.emit(ON_HURT, HurtMsg{ 320, "Library Man" }, 1000);

	simmy.run([&history]() {
		fmt::print("Cast heal spell!");
		history.push_back('a');
		return std::nullopt;
	}, 10);
	simmy.process_events(3000);

	REQUIRE(2 == history.size());
	REQUIRE('a' == history[0]);
	REQUIRE('c' == history[1]);
}


TEST_CASE("Spawning events during events", "[es-example-2]") {
	fmt::print("Spawning events during events.");
	sims::EventSimulator simmy;

	std::vector<char> history;

	constexpr sims::EventType ON_HURT = 1;
	struct HurtMsg {
		int hp;
		std::string attacker;
	};

	constexpr sims::EventType ON_HEAL = 2;
	struct HealMsg {
		int hp;
		std::string healer;
	};
	simmy.subscribe<HurtMsg>(ON_HURT, [&history](HurtMsg hm) {
		fmt::print("You wound me for {} hp good sir {}.", hm.hp, hm.attacker);
		history.push_back('-');
	});
	simmy.subscribe<HealMsg>(ON_HEAL, [&history](HealMsg hm) {
		fmt::print("HP += {}. Thanks {}!", hm.hp, hm.healer);
		history.push_back('+');
	});

	simmy.emit(ON_HURT, HurtMsg{ 320, "Library Man" }, 1000);

	struct Cow {
		sims::CoroutineState state;
		int hp = 300;
		sims::EventSimulator & c_simmy;

		Cow(sims::EventSimulator & _simmy)
			: c_simmy(_simmy) {}

		std::optional<int> operator() () {
			LP3_COROUTINE_BEGIN(state)
				fmt::print("Cow is waking up.");
				c_simmy.emit(ON_HURT, HurtMsg{ 20, "Cow" }, 20);
				LP3_YIELD(1);
				c_simmy.emit(ON_HURT, HurtMsg{ 40, "Cow" }, 10);
				LP3_YIELD(std::nullopt);
			LP3_COROUTINE_END();
			return std::nullopt;
		}
	} cow(simmy);

	simmy.run(cow, 10);

	simmy.process_events(3000);
	simmy.process_events(3000);

	/*REQUIRE(2 == history.size());
	REQUIRE('a' == history[0]);
	REQUIRE('c' == history[1]);*/
}

