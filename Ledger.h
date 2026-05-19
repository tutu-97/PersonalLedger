#ifndef LEDGER_H
#define LEDGER_H


#include <vector>
#include <string>
#include "Record.h"

class Ledger {
private:
	std::vector<Record> records;     // 记录列表
	std::string filename;			  // 数据文件名

	bool loadFromFile();
	bool saveToFile() const;

public:
	Ledger(const std::string& filepath="records.txt");

	void addRecord(const Record& rec);
	bool deleteRecord(int index);
	void showAll() const;
	void showByCategory(const std::string& date) const;
	void showStatistics() const;

	int getCount() const;
	void clearAll();
};


#endif // !LEDGER_H