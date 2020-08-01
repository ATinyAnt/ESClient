

#ifndef ES_REQUEST_H
#define ES_REQUEST_H

#include <string>
#include <vector>
#include <sstream>
#include <stdint.h>


// private
namespace _ES
{

static inline std::string Range(const std::string &field, const std::string &oper, const char *value) {
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{\"" << oper << "\":\"" << value << "\"}}}";
	return ss.str();
}

template<class T>
static inline std::string Range(const std::string &field, const std::string &oper, const T &value) {
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{\"" << oper << "\":" << value << "}}}";
	return ss.str();
}

static inline std::string Range(const std::string &field, const std::string &oper, const char *value, const std::string &other) {
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{\"" << oper << "\":\"" << value << "\"," << other << "}}}";
	return ss.str();
}

template<class T>
static inline std::string Range(const std::string &field, const std::string &oper, const T &value, const std::string &other) {
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{\"" << oper << "\":" << value << "," << other <<  "}}}";
	return ss.str();
}

static inline std::string Range2(const std::string &field, const std::string &cond1, const std::string &cond2, const std::string &other) {
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{" << cond1 << "," << cond2 << "," << other << "}}}";
	return ss.str();
}

}



// interface
namespace ES
{


#define RANGE(Func, Oper) \
	static inline std::string Func(const std::string &field, const std::string &value) {\
		return _ES::Range(field, Oper, value.c_str()); \
	} \
	template <class T> \
	static inline std::string Func(const std::string &field, const T value) { \
		return _ES::Range(field, Oper, value); \
	} \
	static inline std::string Func(const std::string &field, const std::string &value, const std::string &other) {\
		return _ES::Range(field, Oper, value.c_str(), other); \
	}\
	template <class T> \
	static inline std::string Func(const std::string &field, const T value, const std::string &other) { \
		return _ES::Range(field, Oper, value, other); \
	}

#define RANGEEX_STRING(Oper1, Oper2) \
	std::stringstream ss; \
	ss << "{\"range\":{\"" << field << "\":{\""Oper1"\":\"" << value1 << "\",\""Oper2"\":\"" << value2 << "\"}}}"; \
	return ss.str(); 

#define RANGEEX_STRING_OTHER(Oper1, Oper2) \
	std::stringstream ss; \
	ss << "{\"range\":{\"" << field << "\":{\""Oper1"\":\"" << value1 << "\",\""Oper2"\":\"" << value2 << "\"," << other << "}}}"; \
	return ss.str(); 

#define RANGEEX(Func, Oper1, Oper2) \
	static inline std::string Func(const std::string &field, const char *value1, std::string &value2) { \
		RANGEEX_STRING(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const std::string &value1, const char *value2) { \
		RANGEEX_STRING(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const char *value1, const char *value2) { \
		RANGEEX_STRING(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const std::string &value1, const std::string &value2) { \
		RANGEEX_STRING(Oper1, Oper2) \
	}\
	template<class T> \
	static inline std::string Func(const std::string &field, const T value1, const T value2) { \
		std::stringstream ss; \
		ss << "{\"range\":{\"" << field << "\":{\""Oper1"\":" << value1 << ",\""Oper2"\":" << value2 << "}}}"; \
		return ss.str(); \
	}\
	static inline std::string Func(const std::string &field, const char *value1, std::string &value2, const std::string &other) { \
		RANGEEX_STRING_OTHER(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const std::string &value1, const char *value2, const std::string &other) { \
		RANGEEX_STRING_OTHER(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const char *value1, const char *value2, const std::string &other) { \
		RANGEEX_STRING_OTHER(Oper1, Oper2) \
	} \
	static inline std::string Func(const std::string &field, const std::string &value1, const std::string &value2, const std::string &other) { \
		RANGEEX_STRING_OTHER(Oper1, Oper2) \
	}\
	template<class T> \
	static inline std::string Func(const std::string &field, const T value1, const T value2, const std::string &other) { \
		std::stringstream ss; \
		ss << "{\"range\":{\"" << field << "\":{\""Oper1"\":" << value1 << ",\""Oper2"\":" << value2 << "," << other << "}}}"; \
		return ss.str(); \
	}

template <class T>
static inline std::string MakeArray(const std::vector<T> &values) {
	uint32_t size = (uint32_t)values.size();
	if (size == 0) return "[]";

	std::stringstream ss;
	ss << "[";
	for (uint32_t i = 0; i < size - 1; ++i)
	{
		ss << values[i] << ",";
	}
	ss << values[size - 1] << "]";
	return ss.str();
}

static inline std::string MakeArrayString(const std::vector<std::string> &values) {
	uint32_t size = (uint32_t)values.size();
	if (size == 0) return "[]";

	std::stringstream ss;
	ss << "[";
	for (uint32_t i = 0; i < size - 1; ++i)
	{
		ss << "\"" << values[i] << "\",";
	}
	ss << "\"" << values[size - 1] << "\"]";
	return ss.str();
}

template <class T>
static inline std::string MakeObject(const std::vector<T> &values) {
	uint32_t size = (uint32_t)values.size();
	if (size == 0) return "{}";

	std::stringstream ss;
	ss << "{";
	for (uint32_t i = 0; i < size - 1; ++i)
	{
		ss << values[i] << ",";
	}
	ss << values[size - 1] << "}";
	return ss.str();
}

template <class T>
static inline std::string MakeObject(const std::string &key, T value){
	std::stringstream ss;
	ss << "{\"" << key << "\":" << value << "}";
	return ss.str();
}

static inline std::string MakeObjectString(const std::string &key, const std::string &value){
	std::stringstream ss;
	ss << "{\"" << key << "\":\"" << value << "\"}";
	return ss.str();
}

template <class T>
static inline std::string MakePair(const std::string &key, T value){
	std::stringstream ss;
	ss << "\"" << key << "\":" << value;
	return ss.str();
}

static inline std::string MakePairString(const std::string &key, const std::string &value){
	std::stringstream ss;
	ss << "\"" << key << "\":\"" << value << "\"";
	return ss.str();
}

void Escape(const char word, std::string &result)
{
	switch(word)
	{
	case '\\':
		result += "\\\\";
		break;
	case '\"':
		result += "\\\"";
		break;
	case '\r':
	case '\n':
	case '\t':
		return;
	default:
		result.push_back(word);
	}
}

void RegExpEscape(const char word, std::string &result)
{
	switch(word)
	{
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
	case '<':
	case '>':
	case '*':
	case '+':
	case '.':
	case '?':
	case '^':
	case '|':
	case '&':
	case '~':
		result += "\\\\";
		result += word;
		
		break;		
	case '\\':
		result += "\\\\\\\\";
		break;
	case '\"':
		result += "\\\\\\\"";
		break;
	case '\r':
	case '\n':
	case '\t':
		return;
	default:
		result.push_back(word);
	}
}

RANGE(Gt, "gt");
RANGE(Gte, "gte");
RANGE(Lt, "lt");
RANGE(Lte, "lte");

RANGEEX(GtLt, "gt", "lt");
RANGEEX(GtLte, "gt", "lte");
RANGEEX(GteLt, "gte", "lt");
RANGEEX(GteLte, "gte", "lte");

static inline std::string Missing(const std::string &field, const std::string &prefix) {
	std::stringstream ss;
	ss << "{\"missing\":{\"" << field << "\":\"" << prefix << "\"}}";
	return ss.str();
}

static inline std::string Prefix(const std::string &field, const std::string &prefix) {
	std::stringstream ss;
	ss << "{\"prefix\":{\"" << field << "\":\"" << prefix << "\"}}";
	return ss.str();
}

static inline std::string RegExp(const std::string &field, const std::string &regexp) {
	std::stringstream ss;
	ss << "{\"regexp\":{\"" << field << "\":\"" << regexp << "\"}}";
	return ss.str();
}


static inline std::string Term(const std::string &field, const char *value) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":\"" << value << "\"}}";
	return ss.str();
}

static inline std::string Term(const std::string &field, const std::string &value) {
	return Term(field, value.c_str());
}

template <class T>
static inline std::string Term(const std::string &field, const T value) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":" << value << "}}";
	return ss.str();
}

template <class T>
static inline std::string Term(const std::string &field, const char *value, T boost) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":{\"term\":\"" << value << "\",\"boost\":" << boost << "}}}";
	return ss.str();
}

template <class T>
static inline std::string Term(const std::string &field, const std::string &value, T boost) {
	return Term(field, value.c_str(), boost);
}

template <class T, class U>
static inline std::string Term(const std::string &field, const T value, U boost) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":{\"term\":" << value << ",\"boost\":" << boost << "}}}";
	return ss.str();
}

template <class T>
static inline std::string Terms(const std::string &field, const std::vector<T> &values) {	
	std::stringstream ss;
	ss << "{\"terms\":{\"" << field << "\":" << MakeArray(values) << "}}";
	return ss.str();
}

static inline std::string Terms(const std::string &field, const std::vector<std::string> &values) {
	std::stringstream ss;
	ss << "{\"terms\":{\"" << field << "\":\"" << MakeArrayString(values) << "\"}}";
	return ss.str();
}

template <class T, class U = int>
static inline std::string MatchDSL(const std::string &field, const T &value, U boost) {
	std::stringstream ss;
	if (boost != 0)
		ss << "{\"match\":{\"" << field << "\":{\"query\":" << value << ",\"boost\":" << boost << "}}}";
	else
		ss << "{\"match\":{\"" << field << "\":" << value << "}}";
	return ss.str();
}

template <class T = int>
static inline std::string Match(const std::string &field, const char *value, T boost = 0) {
	return MatchDSL(field, "\"" + std::string(value) + "\"", boost);
}

template <class T = int>
static inline std::string Match(const std::string &field, const std::string &value, T boost = 0) {
	return MatchDSL(field, "\"" + value + "\"", boost);
}

template <class T, class U = int>
static inline std::string Match(const std::string &field, T value, U boost = 0) {
	return MatchDSL(field, value, boost);
}

template <class T = int>
static inline std::string MatchAnd(const std::string &field, const std::string &value, T boost = 0) {
	return MatchDSL(field, "\"" + value + "\",\"operator\":\"and\"", boost);
}

static inline std::string Bool(const std::string &fields) {
	std::stringstream ss;
	ss << "{\"bool\":{" << fields << "}}";
	return ss.str();
}

static inline std::string Bool(const std::vector<std::string> &fields) {
	return Bool(MakeObject(fields));
}

static inline std::string Must(const std::vector<std::string> &fields) {
	return MakePair("must", MakeArray(fields));
}

static inline std::string MustNot(const std::vector<std::string> &fields) {
	return MakePair("must_not", MakeArray(fields));
}

static inline std::string Should(const std::vector<std::string> &fields) {
	return MakePair("should", MakeArray(fields));
}

static inline std::string Filter(const std::vector<std::string> &fields) {
	return MakePair("filter", MakeArray(fields));
}

static inline std::string BMust(const std::vector<std::string> &fields) {
	return Bool(Must(fields));
}

static inline std::string BMustNot(const std::vector<std::string> &fields) {
	return Bool(MustNot(fields));
}

static inline std::string BShould(const std::vector<std::string> &fields) {
	return Bool(Should(fields));
}

static inline std::string BFilter(const std::vector<std::string> &fields) {
	return Bool(Filter(fields));
}

static std::string MSearch(const std::string &index, const std::string &type, const std::string &dsl) {
	std::string ret = "{";
	if (!index.empty())
	{
		ret += "\"index\":\"";
		ret += index;
		ret += !type.empty() ? "\"," : "\"";
	}

	if (!type.empty())
	{
		ret += "\"type\":\"";
		ret += type;
		ret += "\"";
	}
	ret += "}\r\n";
	
	return ret + dsl + "\r\n";
}



class Request
{
public:
	inline Request & From(uint32_t from) {
		m_dsl += MakePair("from", from) + ",";
		return *this;
	}

	inline Request & From(uint32_t from, uint32_t size) {
		From(from);
		Size(size);
		return *this;
	}

	inline Request & Size(uint32_t size) {
		m_dsl += MakePair("size", size) + ",";
		return *this;
	}

	inline Request & Source(const std::vector<std::string> &fields) {
		m_dsl += MakePair("_source", MakeArrayString(fields)) + ",";
		return *this;
	}

	inline Request & Sort(const std::vector<std::string> &fields){
		m_dsl += MakePair("sort", MakeArray(fields)) + ",";
		return *this;
	}

	inline std::string Query(const std::string &dsl) {
		std::stringstream ss;
		ss << "{" << m_dsl << "\"query\":" << dsl << "}";
		return ss.str();
	}

	inline Request &operator << (const std::string &dsl){
		m_dsl += dsl;
		return *this;
	}

	// todo nested
	// todo agg
	// todo geo

	inline std::string GetDsl(){return m_dsl;}

private: 
	std::string m_dsl;
};


}


#endif
