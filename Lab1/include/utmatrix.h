// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
	  TVector v1(v.StartIndex);
	  for (int i = 0; i < v.StartIndex; i++)
		  in >>v1[i];
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	for (int i = 0; i < v.StartIndex; i++)
		out << '0' << ' ';
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s < 0 || s>MAX_VECTOR_SIZE) throw new exception("Некорректная длина вектора.");
	Size = s;
	if (si<0 || si>MAX_VECTOR_SIZE) throw new exception("Недопустимый индекс первого элемента.");
	StartIndex = si;
	if (s != 0) pVector = new ValType[Size];
	else pVector = NULL;
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	if (pVector != NULL)
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
} 

template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != NULL)
		delete[] pVector;
	pVector = NULL;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	int k = pos - StartIndex;
	if (k<0 || k>Size - 1) throw new exception("Обращение к элементу вне вектора.");
	return pVector[k];
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) return false;
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i])
			return false;
	}
	return true;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if(this==&v) return *this;
	StartIndex = v.StartIndex;
	if (Size != v.Size)
	{
		Size = v.Size;
		if (pVector != NULL)
			delete pVector;
		pVector = new ValType[Size];
	}
	if (pVector != NULL)
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	return *this;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res(Size,StartIndex);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i]+val;
	return res;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] - val;
	return res;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] * val;
	return res;
} 

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size) throw new exception("Нельзя сложить векторы разных размеров");
	if (StartIndex != v.StartIndex) throw new exception("Нельзя сложить векторы с разными начальными индексами");
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] + v.pVector[i];
	return res;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size) throw new exception("Нельзя вычитать векторы разных размеров");
	if (StartIndex != v.StartIndex) throw new exception("Нельзя вычитать векторы с разными начальными индексами");
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] - v.pVector[i];
	return res;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size) throw new exception("Нельзя умножать векторы разных размеров");
	if (StartIndex != v.StartIndex) throw new exception("Нельзя умножать векторы с разными начальными индексами");
	ValType res=0;
	for (int i = 0; i < Size; i++)
		res = res + pVector[i] * v.pVector[i];
	return res;
} 


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s):TVector<TVector<ValType>>(s)
{
	if (s<0 || s>MAX_MATRIX_SIZE) throw new exception("Недопустимый размер матрицы");
	for (int i = 0; i < s; i++)
		pVector[i] = TVector<ValType>(s - i, i);
} 

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType>>(mt){}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) : TVector<TVector<ValType>>(mt)
{
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	return TVector<TVector<ValType>>::operator==(mt);
} 

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return TVector<TVector<ValType>>::operator!=(mt);
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt) {
		StartIndex = mt.StartIndex;
		if (Size != mt.Size)
		{
			Size = mt.Size;
			if (pVector != NULL)
				delete[] pVector;
			pVector = new TVector<ValType>[Size];
		}
		if (pVector != NULL)
			for (int i = 0; i < Size; i++)
				pVector[i] = mt.pVector[i];
	}
	return *this;
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType>>::operator-(mt);
} 

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
