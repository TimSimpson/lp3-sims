#include <iostream>
#include <lp3/main.hpp>
#include <lp3/sims.hpp>

int _main(lp3::main::PlatformLoop & loop) {
    const std::int64_t ms_per_update = 1000 / 120;  //roughly 32 ms for 60 fps

    lp3::sims::GameClock clock(ms_per_update);


    std::int64_t game_time = 0;
    std::int64_t last_printed_time = 0;
    auto run_game = [&game_time, &last_printed_time](std::int64_t elapsed_time) {
        game_time += elapsed_time;
        const auto time_in_seconds = game_time / 1000;
        if (time_in_seconds > last_printed_time) {
            last_printed_time = time_in_seconds;
            std::cout << "Game time: " << last_printed_time << "s\n";
        }
    };
    return 0;
}

LP3_MAIN(_main)
