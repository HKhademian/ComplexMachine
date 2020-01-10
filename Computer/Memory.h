#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "../Complex/ComplexNum.h"

namespace Computer {
	struct Field {
		char name[5] = {0};
		Complex::ComplexNum value;
	};

	class Memory {
	public:
		virtual bool get(const char *name, Complex::ComplexNum &value) const;

		virtual bool get(const char *name, int start, int end, Complex::ComplexNum &value) const = 0;

		virtual bool set(const char *name, const Complex::ComplexNum &value);

		virtual bool set(const char *name, int start, int end, const Complex::ComplexNum &value) = 0;

		virtual bool del(const char *name, int start, int end) = 0;

		virtual void clear() = 0;

		[[nodiscard]] virtual unsigned int size() const = 0;
	};

	class FieldMemory : public Memory {
	private:
		std::vector<Field> fields;

		int getIndex(const char *name, int start, int end) const;

	public:
		bool createNew = true;

		[[nodiscard]] const std::vector<Field> &list() const;

		bool get(const char *name, int start, int end, Complex::ComplexNum &value) const override;

		bool set(const char *name, int start, int end, const Complex::ComplexNum &value) override;

		bool del(const char *name, int start, int end) override;

		void clear() override;

		[[nodiscard]] unsigned int size() const override;
	};
}

#endif
