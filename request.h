

#ifndef ES_REQUEST_H
#define ES_REQUEST_H

#include <string>
#include <vector>
#include <sstream>
#include <stdint.h>

namespace ES
{

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

static inline std::string Range1(const std::string &field, const std::string &cond1, const std::string &other = ""){
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{" << cond1;
	if (!other.empty())
	{
		ss << "," << other;
	}
	ss << "}}}";
	return ss.str();
}

static inline std::string Range2(const std::string &field, const std::string &cond1, const std::string &cond2, const std::string &other = ""){
	std::stringstream ss;
	ss << "{\"range\":{\"" << field << "\":{" << cond1 << "," << cond2;
	if (!other.empty())
	{
		ss << "," << other;
	}
	ss << "}}}";
	return ss.str();
}

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

template <class T>
static inline std::string Term(const std::string &field, T value) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":" << value << "}}";
	return ss.str();
}

static inline std::string Term(const std::string &field, const std::string &value) {
	std::stringstream ss;
	ss << "{\"term\":{\"" << field << "\":\"" << value << "\"}}";
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

template <class T>
static inline std::string Match(const std::string &field, T value) {
	std::stringstream ss;
	ss << "{\"match\":{\"" << field << "\":" << value << "}}";
	return ss.str();
}

static inline std::string Match(const std::string &field, const std::string &value) {
	std::stringstream ss;
	ss << "{\"match\":{\"" << field << "\":\"" << value << "\"}}";
	return ss.str();
}

static inline std::string MatchAnd(const std::string &field, const std::string &value) {
	std::stringstream ss;
	ss << "{\"match\":{\"" << field << "\":{\"query\":\"" << value << "\",\"operator\":\"and\"}}}";
	return ss.str();
}

static inline std::string Bool(const std::string &fields) {
	std::stringstream ss;
	ss << "{\"bool\":{" << fields << "}}";
	return ss.str();
}

static inline std::string Bool(const std::vector<std::string> &fields) {
	std::stringstream ss;
	ss << "{\"bool\":{" << MakeObject(fields) << "}}";
	return ss.str();
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

	Request & Size(uint32_t size) {
		m_dsl += MakePair("size", size) + ",";
		return *this;
	}

	Request & Source(const std::vector<std::string> &fields) {
		m_dsl += MakePair("_source", MakeArrayString(fields)) + ",";
		return *this;
	}

	Request & Sort(const std::vector<std::string> &fields){
		m_dsl += MakePair("sort", MakeArray(fields)) + ",";
		return *this;
	}

	std::string Query(const std::string &dsl) {
		std::stringstream ss;
		ss << "{" << m_dsl << "\"query\":" << dsl << "}";
		return ss.str();
	}

	Request &operator << (const std::string &dsl){
		m_dsl += dsl;
		return *this;
	}

	std::string GetDsl(){return m_dsl;}

private: 
	std::string m_dsl;
};


}


#endif
