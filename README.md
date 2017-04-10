# lograffe
lograffe is a **structured logger** for modern C++. It is inspired by [logrus](https://github.com/sirupsen/logrus) and [zap](https://github.com/uber-go/zap), similar libraries for the Go programming language.

lograffe's focus is on being a really fast and reliable _structured_ logger. If you need a traditional logger with printf-like syntax, lograffe probably is not for you.

## Some design goals

* header-only library
* convenient syntax for structured logging
* least possible overhead when a log level is not active
* for server applications: per-request log levels and sinks, also for multi-threaded processing within one request
* pluggable JSON, [logfmt](https://github.com/go-logfmt/logfmt) output formats
* default log level changeable at runtime
* zero-overhead custom log levels

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

## Status / Roadmap

<table>
<tr><th>Target</th><th>Description</th><th>Status</th></tr>
<tr><td>0.1</td><td>basic functionality, unit tested</td><td>work in progress</td></tr>
<tr><td>0.1</td><td>performance testing + optimizations</td><td>to do</td></tr>
<tr><td>0.5</td><td>support for nested fields</td><td>to do</td></tr>
<tr><td>0.5</td><td>full documentation + examples</td><td>to do</td></tr>
<tr><td>1.0</td><td>further changes based on user feedback</td><td>to do</td></tr>
</table>
