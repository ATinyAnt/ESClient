
a ElsaticSearch client for C++
Only encode the ElsaticSearch's DSL,not include Http module

Example:
```c
Request r;
std::string dsl = r.Size(10).Source({"id"}).Query(Regexp("name", ".*Tiny.*"));
printf("%s\n", dsl.c_str());
// {"size":10,"_source":["id"],"query":{"regexp":{"name":".*Tiny.*"}}}
```
