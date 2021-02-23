#pragma once
#include "List.h"
#include <Windows.h>

template <typename T>
class Model : public List<T>
{
public:
	Model(List<T> ls1):List<T>(ls1){}

	string toStringVisitor()
	{
		FormString<T> visitor;
		(*this).accept(visitor);
		return visitor.s;
	}
	~Model() {}
};
template <typename T>
class View
{
public:
	View<T>(string s) :data(s) {}
	void changeData(const string s)
	{
		data = s;
	}
	string getData()
	{
		return data;
	}
	virtual void refresh() = 0;
	virtual void text(string) = 0;
private:
	string data;
};
template <typename T>
class WinapiView : public View<T>
{
public:
	HWND hListBox;
	WinapiView<T>(string s, HWND _hListBox) :View<T>(s), hListBox(_hListBox) {}
	void add_front()
	{
		stringstream ss((*this).getData());
		T temp;
		ss >> temp;
		string str = TypeToStr(temp);
		SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
		SendMessage(hListBox, LB_INSERTSTRING, (WPARAM)0, (LPARAM)(LPCSTR)str.c_str());
		SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(hListBox, NULL, TRUE);
	}
	void add_back()
	{
		stringstream ss((*this).getData());
		T temp;
		while (ss >> temp);
		string str = TypeToStr(temp);
		SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
		SendMessage(hListBox, LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)str.c_str());
		SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(hListBox, NULL, TRUE);
	}
	void del_front()
	{
		SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
		SendMessage(hListBox, LB_DELETESTRING, (WPARAM)0, 0L);
		SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(hListBox, NULL, TRUE);
	}
	void del_back()
	{
		SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
		int nIndex = SendMessage(hListBox, LB_GETCOUNT, NULL, 0L);
		nIndex--;
		SendMessage(hListBox, LB_DELETESTRING, (WPARAM)nIndex, 0L);
		SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(hListBox, NULL, TRUE);
	}
	void refresh()
	{
		SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
		SendMessage(hListBox, LB_RESETCONTENT, 0, 0L);
		istringstream iss((*this).getData());
		T temp;
		while (iss >> temp)
		{
			string str = TypeToStr(temp);
			SendMessage(hListBox, LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)str.c_str());
		}
		SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
		InvalidateRect(hListBox, NULL, TRUE);
	}
	void text(string s)
	{
		MessageBox(hListBox, s.c_str(), "", MB_ICONINFORMATION);
	}
	void textout(string s, HDC hdc)
	{
		TextOut(hdc, 30, 300, s.c_str(), s.size());
	}
};

template <typename T>
class Controller
{
public:
	Model<T>& model;
	WinapiView<T>& view;

	Controller(Model<T>& m, WinapiView<T>& v) : model(m), view(v) {}
	void push_front(T a)
	{
		model.PushFront(a);
		view.changeData(model.toStringVisitor());
		view.add_front();
	}
	void push_back(T a)
	{
		model.PushBack(a);
		view.changeData(model.toStringVisitor());
		view.add_back();
	}
	void pop_front()
	{
		model.PopFront();
		view.changeData(model.toStringVisitor());
		view.del_front();
	}
	
	
	void Size()
	{
		int t = model.Size();
		string s = to_string(t);
		view.text(s);
	}
	void Max()
	{
		if (!model.IsEmpty())
		{
			MinMax<T> visitor;
			model.accept(visitor);
			T t = visitor.max;
			string s = Complex_to_string(t);
			view.text(s);
		}
	}
	void Min()
	{
		if (!model.IsEmpty())
		{
			MinMax<T> visitor;
			model.accept(visitor);
			T t = visitor.min;
			string s = Complex_to_string(t);
			view.text(s);
		}
	}
	void Count()
	{
		if (!model.IsEmpty())
		{
			CountElements<T> visitor;
			model.accept(visitor);
			int t = visitor.count;
			string s = to_string(t);
			view.text(s);
		}
	}
	void MinMaxCountOut(HDC hdc)
	{
		{
			MinMax<T> visitor;
			model.accept(visitor);
			T tmin = visitor.min;
			T tmax = visitor.max;

			CountElements<T> vis;
			model.accept(vis);
			int t = vis.count;

			string s = "";
			if (model.IsEmpty())
			{
				s = "[ Empty! ]";
			}
			else
			{
				s += "[ ";
				s += Complex_to_string(tmin);
				s += " ; ";
				s += Complex_to_string(tmax);
				s += " ; ";
				s += to_string(t);
				s += " ]";
			}
			view.textout(s, hdc);
		}
	}
};
