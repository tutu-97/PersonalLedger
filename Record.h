#ifndef RECORD_H
#define RECORD_H



#include <string>

class Record {
private:
	std::string date;         //日期 格式为 "YYYY-MM-DD"
	std::string category;     //类别 如 "餐饮", "交通", "收入" 等
	double amount;            //金额 正数表示收入，负数表示支出
	std::string note;         //备注

public:
	//构造函数
	Record();
	Record(const std::string& date, const std::string& category, double amount, const std::string& note);

	//getters
	std::string getDate() const;
	std::string getCategory() const;
	double getAmount() const;
	std::string getNote() const;

	//setters
	void setDate(const std::string& date);
	void setCategory(const std::string& category);
	void setAmount(double amount);
	void setNote(const std::string& note);

	//显示记录信息
	void display() const;

	//序列化和反序列化
	std::string toFileString() const; //将记录转换为文件字符串格式
	static Record fromFileString(const std::string& line); //从文件字符串格式创建记录
};

#endif // RECORD_H