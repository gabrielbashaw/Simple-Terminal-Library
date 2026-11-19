#pragma once

namespace stl {

	class Columns {
	public:
		Columns() = default;
		Columns(unsigned short columns) : _columns(columns) {}
		unsigned short get() const { return _columns; }

	private:
		unsigned short _columns;
	};

	class Rows {
	public:
		Rows() = default;
		Rows(unsigned short rows) : _rows(rows) {}
		unsigned short get() const { return _rows; }

	private:
		unsigned short _rows;
	};

	/// @brief Represents a two-dimensional size using column (X) and row (Y)
	class Size {
	public:
		Size() = default;
		Size(Columns columns, Rows rows) : _columns(columns), _rows(rows) {}

		Columns columns() const { return _columns; }
		Rows rows() const { return _rows; }

	private:
		Columns _columns;
		Rows		_rows;
	};
}
