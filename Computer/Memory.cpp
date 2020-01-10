#include <mem.h>
#include "../utils.h"
#include "../Complex/ComplexNum.h"
#include "Memory.h"

namespace Computer {
	const std::vector<Field> &FieldMemory::list() const {
		return fields;
	}

	bool FieldMemory::get(const char *name, int start, int end, Complex::ComplexNum &value) const {
		int i = getIndex(name, start, end);
		if (i < 0)
			return false;
		value.copyFrom(fields[i].value);
		return true;
	}

	bool FieldMemory::set(const char *name, int start, int end, const Complex::ComplexNum &value) {
		int i = getIndex(name, start, end);
		if (i > 0) {
			fields[i].value.copyFrom(value);
			return true;
		}
		if (createNew) {
			Field field = Field();
			strncpy(field.name, name, 5);
			field.value.copyFrom(value);
			fields.push_back(field);
			return true;
		}
		return false;
	}

	bool FieldMemory::del(const char *name, int start, int end) {
		int i = getIndex(name, start, end);
		if (i < 0)
			return false;
		if (createNew) {
			fields.erase(fields.begin() + i);
		} else {
			fields[i].value.copyFrom(Complex::C0);
		}
		return true;
	}

	void FieldMemory::clear() {
		if (createNew) {
			fields.clear();
		} else {
			for (auto field : fields) {
				field.value.copyFrom(Complex::C0);
			}
		}
	}

	unsigned int FieldMemory::size() const {
		return fields.size();
	}

	int FieldMemory::getIndex(const char *name, int start, int end) const {
		int len = trim(name, start, end);
		if (len > 0) {
			for (int i = 0; i < fields.size(); i++) {
				const auto field = fields[i];
				if (strlen(field.name) == len && strncasecmp(field.name, name + start, len) == 0) {
					return i;
				}
			}
		}
		return -1;
	}

	bool Memory::get(const char *name, Complex::ComplexNum &value) const {
		return get(name, 0, (int) strlen(name) - 1, value);
	}

	bool Memory::set(const char *name, const Complex::ComplexNum &value) {
		return set(name, 0, (int) strlen(name) - 1, value);
	}
}