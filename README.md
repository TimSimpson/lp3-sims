# lp3-sims

[![Travis Build Status](https://travis-ci.org/TimSimpson/lp3-sims.svg?branch=master)](https://travis-ci.org/TimSimpson/lp3-sims)
[![Build status](https://ci.appveyor.com/api/projects/status/vqcmfp6sflj902o7/branch/master?svg=true)](https://ci.appveyor.com/project/TimSimpson/lp3-sims/branch/master)
[ ![Download](https://api.bintray.com/packages/timsimpson/richter/Lp3-sims%3ATimSimpson/images/download.svg) ](https://bintray.com/timsimpson/richter/lp3-sims%3ATimSimpson/_latestVersion)

This contains some general code useful in simulations or games:

* there's simple [coroutines](include/lp3/sims/coroutine.hpp) implemented with macros which generate switch statements
* a [game clock](include/lp3/sims/Clock.hpp), which simplifies writing code that runs at the same speed regardless of the performance of the underlying hardware
* [timers](include/lp3/sims/Clock.hpp) to measure FPS
