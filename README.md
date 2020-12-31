# QLogger
Quick logger is designed to be extremely fast and simple to integrate in a C++ projects, the installation, usage and performance test has been mentioned below

## Installation
> Clone the repo and simply use the cmake target to Qlogger:lib in you project
> If you project does not use cmake, clone the repo add -I <repo_path>/qlogger while building a project and simply put `#include <QLogger.h>`

## Usage
> Once Included in the project, we can simple use QLOG(<severity>, "text").
> Severity is as follows `{NONE, CRIT, WARN, ALERT, ERROR, INFO, DATA, DEBUG, COUNT}`
> Threshold severity is runtime configurable via following call: TODO
> The logger is thread safe to use, to dump the logger to a file, you need to call following API from a single thread (this api shouldn't be invoked from multiple thread)

## Performance
> To simple log a text from min 10 char to 500 char, the latecy of logging in around 400ns to 600ns
