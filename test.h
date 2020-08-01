
#ifndef TEST_ES_H
#define TEST_ES_H

#include "request.h"

using namespace ES;

namespace TestES
{
	void Fun1()
	{
		Request r;
		std::string dsl = r.Size(10).Source({ "id" }).Query(RegExp("name", ".*Tiny.*"));
		printf("%s:%s\n",  __FUNCTION__, dsl.c_str());
	}

	void Fun2()
	{
		Request r;
		std::string dsl = r.Size(10).Source({"name"}).Query(
			BMust({
				Term("id","2356",1.5)
			})
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun3()
	{
		Request r;
		std::string dsl = r.Size(10).Source({"name"}).Query(
			Lt("id", 567)
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun4()
	{
		Request r;

		std::string dsl = r.Size(10).Source({"name"}).Sort(
			{MakeObject("timestamp",MakeObject("order", "desc"))}
		).Query(
			Lt("id", 567)
		);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun5()
	{
		Request r1;

		std::string dsl1 = r1.Size(10).Source({"name"}).Sort(
			{MakeObject("timestamp",MakeObject("order", "desc"))}
		).Query(
			Lt("id", 567)
		);

		Request r2;

		std::string dsl2 = r2.Size(10).Source({"id"}).Sort(
			{"{\"timestamp\":{\"order\":\"desc\"}}"}
		).Query(
			Gt("id", 567)
		);

		Request m;

		m 
		<< MSearch("", "", dsl1)
		<< MSearch("test_index", "test_type", dsl2);

		std::string dsl = m.Dsl();

		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun6()
	{
		Request r;
		std::string dsl = r.Size(10).Source({ "id" }).Query(MatchAnd("name", "Tiny Ant"));
		printf("%s:%s\n",  __FUNCTION__, dsl.c_str());
	}

	void Fun7()
	{
		Request r;
		std::string dsl = r.From(0).Size(10).Source({ "id" }).Query(RegExp("name", ".*Tiny.*"));
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun8()
	{
		Request r;

		std::string dsl = r.Size(10).Source({ "name" }).Sort(
		{ MakeObject("timestamp",MakeObject("order", "desc")) }
			).Query(
				Gt("id", 567)
				);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}


	void Fun9()
	{
		Request r;

		std::string dsl = r.Size(10).Source({ "name" }).Sort(
		{ MakeObject("timestamp",MakeObject("order", "desc")) }
			).Query(
				Gt("id", "5ab")
				);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun10()
	{
		Request r;
		std::string dsl = r.Size(10).Source({ "name" }).Query(
			BMust({
			Term("id",2356,1.5)
		})
			);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun11()
	{
		Request r;

		std::string dsl = r.Size(10).Source({ "name" }).Sort(
		{ MakeObject("timestamp",MakeObject("order", "desc")) }
			).Query(
				GtLt("id", "5ab", "6ab")
			);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun12()
	{
		std::string dsl = Request().Size(10).Source({ "name" }).Query(
			Nested("child", BMust({Prefix("child.info","nice")}))
				);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun13()
	{
		std::string dsl = Request().Size(10).Source({ "name" }).Sort(
		{
				MakeObject("offer.price", Object().M(
					{
						MakePair("mode", "avg"),
						MakePair("order", "asc")	,
						NestedFilter("offer", Term("offer.color","blue"))
					})
				)
		}).Query(
				Term("product", "chocolate")
			);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}

	void Fun14()
	{
		std::string dsl = Request().Size(10).Query(
			Terms("test", { "product", "chocolate" })
			);
		printf("%s:%s\n", __FUNCTION__, dsl.c_str());
	}
}



#endif