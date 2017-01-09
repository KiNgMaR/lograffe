# lograffe
Lograffe is a **structured logger** for modern C++. It is inspired by [logrus](https://github.com/sirupsen/logrus), a similar library for the Go programming language.

Lograffe's focus is on being a really fast and reliable _structured_ logger. If you need a traditional logger with printf-like syntax, lograffe probably is not for you.

## Some design goals

* header-only library
* convenient syntax for structured logging
* least possible overhead when a log level is not active
* for server applications: per-request log levels and sinks, also for multi-threaded processing within one request
* JSON, [logfmt](https://brandur.org/logfmt) and other output formats
* default log level changeable at runtime
* zero-overhead custom log levels

## Status

work-in-progress. Feedback very welcome!

## Examples

```c++
#include <lograffe/lograffe.hpp>
#include <lograffe/alias.hpp> // alias lograffe namespace as logr

// ...

LOG(info) << "A group of animals emerges from the savanna" << logr::fields{
        { "animal", "giraffe" },
        { "size", giraffes.size() }
    };

LOG(warn) << logr::fields{
        { "omg", true },
        { "number", 122 }
    } << "The group's number increased " << "tremendously!";
```
