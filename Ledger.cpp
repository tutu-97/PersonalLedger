#include "Ledger.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

Ledger::Ledger(const std::string& filepath) : filename(filepath) {
	loadFromFile();
}

bool Ledger::loadFromFile()
{
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		//文件不存在
		return true;
	}
	records.clear();
	std::string line;
	while (std::getline(infile, line)) {
		if (line.empty()) continue; //跳过空行
		Record rec = Record::fromFileString(line);
		//简单验证日期不为空
		if (!rec.getDate().empty()) {
			records.push_back(rec);
		}
	}
	infile.close();
	return true;
}

bool Ledger::saveToFile() const
{
	std::ofstream outfile(filename,std::ios::trunc);
	if(!outfile.is_open()) {
		std::cerr << "无法打开文件 "<<filename<<" 进行保存数据！" << std::endl;
		return false;
	}
	for (const auto& rec : records) {
		outfile<<rec.toFileString()<<std::endl;

	}
	outfile.close();
	return true;
}

void Ledger::addRecord(const Record& rec) {
	records.push_back(rec);
	saveToFile();
}

bool Ledger::deleteRecord(int index) {
    if (index < 0 || index >= static_cast<int>(records.size())) {
        return false;
    }
    records.erase(records.begin() + index);
    saveToFile();
    return true;
}

void Ledger::showAll() const {
    if (records.empty()) {
        std::cout << "暂无记录。" << std::endl;
        return;
    }
    std::cout << "\n===== 所有记录 =====" << std::endl;
    for (size_t i = 0; i < records.size(); ++i) {
        std::cout << "[" << i << "] ";
        records[i].display();
    }
}

void Ledger::showByCategory(const std::string& category) const {
    bool found = false;
    std::cout << "\n===== 类别 [" << category << "] 的记录 =====" << std::endl;
    for (const auto& rec : records) {
        if (rec.getCategory() == category) {
            rec.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "没有找到该类别的记录。" << std::endl;
    }
}

void Ledger::showStatistics() const {
    double totalIncome = 0.0, totalExpense = 0.0;
    for (const auto& rec : records) {
        double amt = rec.getAmount();
        if (amt > 0) totalIncome += amt;
        else totalExpense += (-amt);  // 支出取正值便于显示
    }
    double balance = totalIncome - totalExpense;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n===== 收支统计 =====" << std::endl;
    std::cout << "总收入: " << totalIncome << std::endl;
    std::cout << "总支出: " << totalExpense << std::endl;
    std::cout << "结余: " << balance << std::endl;
}

int Ledger::getCount() const {
    return records.size();
}

void Ledger::clearAll() {
    records.clear();
    saveToFile();
}
