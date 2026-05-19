#include "Record.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//构造函数
Record::Record() :amount(0.0) {}
Record::Record(const std::string& date, const std::string& category, double amount, const std::string& note)
	: date(date), category(category), amount(amount), note(note) {}

//getters
std::string Record::getDate() const {
	return date;
}
std::string Record::getCategory() const {
	return category;
}
double Record::getAmount() const {
	return amount;
}
std::string Record::getNote() const {
	return note;
}

//setters
void Record::setDate(const std::string& d) {
	date = d;
}
void Record::setCategory(const std::string& c) {
	category = c;
}
void Record::setAmount(double a) {
	amount = a;
}
void Record::setNote(const std::string& n) {
	note = n;
}

//显示记录信息
void Record::display() const {
	std::cout << "日期：" << date << " | 类别：" << category << " | 金额：" << amount << " | 备注:" << note << std::endl;
}

//转为文件行格式 日期|类别|金额|备注
std::string Record::toFileString() const {
	std::ostringstream oss;
	oss << date << "|" << category << "|" << amount << "|" << note;
	return oss.str();
}

//从文件行解析创建记录
Record Record::fromFileString(const std::string& line) {
	std::stringstream ss(line);
	std::string date, category, amountStr,note;
	//尝试读取
	if (std::getline(ss, date, '|') && std::getline(ss, category, '|')&& std::getline(ss,amountStr,'|')) {
		double amount = std::stod(amountStr); //转换金额
		std::getline(ss, note); //读取备注
		return Record(date, category, amount, note);
	}

	//如果格式不正确，返回一个空记录
	return Record();
}

