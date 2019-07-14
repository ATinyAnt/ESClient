
#ifndef TEST_ES_H
#define TEST_ES_H

#include "request.h"

using namespace ES;

namespace TestES
{
	void Fun1()
	{
		Request r;
		std::string dsl = r.Size(10).Source({"name"}).Query(Prefix("id", "441283"));
		printf("%s:%s\n",  __FUNCTION__, dsl.c_str());
	}

	void Fun2()
	{
		Request r;
		std::string dsl = r.Size(10).Source({"name"}).Query(
			BMust({
				Term("id",567)
			})
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun3()
	{
		Request r;
		std::string dsl = r.Size(10).Source({"name"}).Query(
			Range1(
				"id",
				MakePair("lt",567)
			)
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun4()
	{
		Request r;

		std::string dsl = r.Size(10).Source({"name"}).Sort(
			{MakeObject("timestamp",MakeObjectString("order", "desc"))}
		).Query(
			Range1(
				"id",
				MakePair("lt",567)
			)
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun5()
	{
		Request r1;

		std::string dsl1 = r1.Size(10).Source({"name"}).Sort(
			{MakeObject("timestamp",MakeObjectString("order", "desc"))}
		).Query(
			Range1(
				"id",
				MakePair("lt",567)
			)
		);

		Request r2;

		std::string dsl2 = r2.Size(10).Source({"id"}).Sort(
			{"{\"timestamp\":{\"order\":\"desc\"}}"}
		).Query(
			Range1(
				"age",
				MakePair("gt",56)
			)
		);

		Request m;

		m 
		<< MSearch("", "", dsl1)
		<< MSearch("test_index", "test_type", dsl2);

		std::string dsl = m.GetDsl();

		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

}



#endif