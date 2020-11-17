// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
	TBitField res(this->BitField);
	return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	TSet res(BitField | s.BitField);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	BitField.SetBit(Elem);
	TSet res(BitField);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField.ClrBit(Elem);
	TSet res(BitField);
	return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet res(BitField & s.BitField);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(~BitField);
	return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	int Elem;
	char ch;
	do { istr >> ch; } while (ch != '{');
	do {
		istr >> Elem; s.InsElem(Elem);
		do { istr >> ch; } while ((ch != ',' && ch != '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	int n = s.GetMaxPower();
	char ch = ' ';
	ostr << '{';
	for (int i = 0; i < n; i++)
		if (s.IsMember(i)) {
			ostr << ch << ' ' << i;
			ch = ',';
		}
	ostr << '}';
	return ostr;
}
