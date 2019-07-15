
a ElsaticSearch client for C++  
Only encode the ElsaticSearch's DSL,not include Http module  

Example:
```c
#include "request.h"

using namespace ES;

Request r;
std::string dsl = r.Size(10).Source({"id"}).Query(RegExp("name", ".*Tiny.*"));
printf("%s\n", dsl.c_str());
// {"size":10,"_source":["id"],"query":{"regexp":{"name":".*Tiny.*"}}}
```
