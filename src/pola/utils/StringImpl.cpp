/*
 * StringImpl.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "pola/utils/StringImpl.h"

namespace pola {
namespace utils {

StringImpl::StringImpl() : m_data(nullptr), m_length(0), m_hash(0) {
}
StringImpl::StringImpl(const char* chars, size_t length) : m_length(length), m_hash(0) {
	char* tmp = new char[length + 1];
	memcpy(tmp, chars, length);
	*(tmp + m_length) = 0;
	m_data = tmp;
}
StringImpl::StringImpl(const char* str) : m_length(strlen(str)), m_hash(0) {
	char* tmp = new char[m_length + 1];
	memcpy(tmp, str, m_length);
	*(tmp + m_length) = 0;
	m_data = tmp;
}

StringImpl* StringImpl::emptyString() {
	static sp<StringImpl> emptyS = new StringImpl();
	return emptyS.get();
}
StringImpl* StringImpl::create(const char* chars, size_t length) {
	return new StringImpl(chars, length);
}
StringImpl* StringImpl::create(const char* str) {
	return new StringImpl(str);
}

StringImpl::~StringImpl() {
	if (m_data != nullptr) {
		delete m_data;
	}
	m_data = nullptr;
	m_length = 0;
}
void StringImpl::print() const {
	printf("%s\n", m_data);
}

size_t StringImpl::length() const {
	return m_length;
}

bool StringImpl::isEmpty() const {
	return length() <= 0;
}

char StringImpl::charAt(size_t index) const {
	checkIndex(index);
	return *(m_data + index);
}

const char* StringImpl::characters() const {
	return m_data;
}

char* StringImpl::characters() {
	return m_data;
}

void StringImpl::resize(ssize_t size) {
	if (size < 0) {
		m_length = m_data ? strlen(m_data) : 0;
	} else {
		size_t len = size_t(size);
		if (len == m_length) {
			return;
		}
		char* tmp = new char[len + 1];
		if (!isEmpty()) {
			if (len > m_length) {
				memset(tmp, 1, len);
			}
			memcpy(tmp, m_data, len > m_length ? m_length : len);
			tmp[len] = 0;
			delete m_data;
			m_data = tmp;
			m_length = len;
		} else {
			memset(tmp, 1, len);
			tmp[len] = 0;
			m_data = tmp;
			m_length = len;
		}
	}
}

bool StringImpl::startsWith(const StringImpl& str, size_t start) const {
	size_t len = str.length();
	if (len <= 0 || len + start > length()) {
		return false;
	}
	return !memcmp(m_data + start, str.characters(), len);
}

bool StringImpl::endsWith(const StringImpl& str) const {
	size_t len = str.length();
	if (len <= 0 || len > length()) {
		return false;
	}
	return !memcmp(m_data + (length() - len), str.characters(), len);
}

bool StringImpl::contains(const StringImpl& str) const {
	size_t len = str.length();
	if (len <= 0 || len > length()) {
		return false;
	}
	for (size_t i = 0; i < length() - len; i ++) {
		if (startsWith(str, i)) {
			return true;
		}
	}
	return false;
}

/**
 * operator compares.
 */
bool StringImpl::operator==(const StringImpl& s) const {
	if (length() != s.length()) {
		return false;
	}
	if (length() > 0) {
		return !memcmp(m_data, s.m_data, length());
	}
	return true;
}
bool StringImpl::operator!=(const StringImpl& s) const {
	return !(*this == s);
}
bool StringImpl::operator>(const StringImpl& s) const {
	return compare(s) > 0;
}
bool StringImpl::operator>=(const StringImpl& s) const {
	return compare(s) >= 0;
}
bool StringImpl::operator<(const StringImpl& s) const {
	return compare(s) < 0;
}
bool StringImpl::operator<=(const StringImpl& s) const {
	return compare(s) <= 0;
}

hash_t StringImpl::hash() const {
	int hash = m_hash;
	if (hash == 0) {
		if (length() == 0) {
			return 0;
		}
		size_t len = length();
		for (size_t index = 0; index < len; index ++) {
			hash = JenkinsHashMix(hash, charAt(index));
		}
		hash = JenkinsHashWhiten(hash);
		m_hash = hash;
	}
	return hash;
}

void StringImpl::rehash() const {
	m_hash = 0;
}

int32_t StringImpl::compare(const StringImpl& s) const {
	for (size_t i = 0; i < length() && i < s.length(); i ++) {
		if (charAt(i) > s.charAt(i)) {
			return 1;
		} else if (charAt(i) < s.charAt(i)) {
			return -1;
		}
	}
	return length() - s.length();
}

}
}


