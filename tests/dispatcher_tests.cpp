#include <lp3/sims/dispatcher.hpp>
#include <fmt/core.h>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/asserts.hpp"

namespace sims = lp3::sims;


TEST_CASE("Test Dispatching", "[dispatcher_tests]") {
	sims::EventDispatcher dispatcher;
	sims::EventType ATTACKED = 1;
	struct AttackInfo {
		int hp;
		std::string character_id;
	};
	auto on_attack = [](const AttackInfo & info) {
		(void)info;
		fmt::print("Character {} was attacked for {} damage.",
			info.character_id, info.hp);
	};
	dispatcher.subscribe<AttackInfo>(ATTACKED, on_attack);
	dispatcher.send(ATTACKED, AttackInfo{ 35, "Alaghasta the Ninny" });

	dispatcher.subscribe<AttackInfo>(ATTACKED, [](const AttackInfo & info) {
		(void)info;
		fmt::print("I also saw that %s was just attacked for %d damage!",
			info.character_id, info.hp);
	});
	dispatcher.send<AttackInfo>(ATTACKED, { 35, "Burtman the Offender" });

	//dispatcher.subscribe<int>(ATTACKED, [](const int & info) {
	//	fmt::print("I am a bug. %d", info);
	//});

	LP3_SIMS_REQUIRE_ASSERT_FAILURE(dispatcher.send<int>(ATTACKED, 5));

	LP3_SIMS_REQUIRE_ASSERT_FAILURE(
		dispatcher.subscribe<int>(ATTACKED, [](const int & info) {
			(void)info;
			fmt::print("I am a bug. %d", info);
		}));
}


TEST_CASE("Unsubscribe", "[dispatcher_unsubscribe]") {
	sims::EventDispatcher dispatcher;
	sims::EventType ATTACKED = 1;
	int my_hp = 100;
	auto on_attack = [&my_hp](const int hp) {
		fmt::print("HURT! HP -%d", hp);
		my_hp -= hp;
	};

	sims::SubscriptionId id = dispatcher.subscribe<int>(ATTACKED, on_attack);
	dispatcher.send(ATTACKED, 35);
	REQUIRE(65 == my_hp);

	dispatcher.unsubscribe(id);
	dispatcher.send(ATTACKED, 10);
	REQUIRE(55 == my_hp);  // What! still changed?!!!/*

	dispatcher.prune();
	dispatcher.send(ATTACKED, 10);
	REQUIRE(55 == my_hp);  // Ah, no change. Just have to prune.*/
}

