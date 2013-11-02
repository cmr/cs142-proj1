#pragma once

#include <stdexcept>

template <typename T>
class option {
	T inner;
	bool is_set;

public:
	option(T some) {
		this->inner = some;
		this->is_set = true;
	}

	option() {
		this->is_set = false;
	}

	T& as_ref() {
		if (this->is_set) {
			return &this->inner;
		} else {
			throw std::runtime_error("as_ref on empty option");
		}
	}

	T unwrap() {
		if (this->is_set) {
			this->is_set = false;
			return this->inner;
		} else {
			throw std::runtime_error("unwrap on empty option");
		}
	}

	bool is_some() {
		return this->is_set;
	}
};
