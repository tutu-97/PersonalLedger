#include <iostream>
#include <limits>
#include "Ledger.h"

void showMenu() {
    std::cout << "\n====== 个人记账本 ======" << std::endl;
    std::cout << "1. 添加记录" << std::endl;
    std::cout << "2. 查看所有记录" << std::endl;
    std::cout << "3. 按类别查询" << std::endl;
    std::cout << "4. 显示统计（收入/支出/结余）" << std::endl;
    std::cout << "5. 删除记录" << std::endl;
    std::cout << "0. 退出" << std::endl;
    std::cout << "请选择: ";
}

int main() {
    Ledger ledger("records.txt");
    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字。" << std::endl;
            continue;
        }
        if (choice == 0) break;

        switch (choice) {
        case 1: {
            std::string date, category, note;
            double amount;
            std::cout << "日期 (YYYY-MM-DD): ";
            std::cin >> date;
            std::cout << "类别 (如 餐饮、交通、收入): ";
            std::cin >> category;
            std::cout << "金额 (正数=收入, 负数=支出): ";
            std::cin >> amount;
            std::cout << "备注: ";
            std::cin.ignore();
            std::getline(std::cin, note);
            Record rec(date, category, amount, note);
            ledger.addRecord(rec);
            std::cout << "添加成功！" << std::endl;
            break;
        }
        case 2:
            ledger.showAll();
            break;
        case 3: {
            std::string cat;
            std::cout << "输入类别: ";
            std::cin >> cat;
            ledger.showByCategory(cat);
            break;
        }
        case 4:
            ledger.showStatistics();
            break;
        case 5: {
            ledger.showAll();
            int idx;
            std::cout << "输入要删除的序号: ";
            std::cin >> idx;
            if (ledger.deleteRecord(idx)) {
                std::cout << "删除成功。" << std::endl;
            }
            else {
                std::cout << "删除失败，序号无效。" << std::endl;
            }
            break;
        }
        default:
            std::cout << "无效选项，请重新输入。" << std::endl;
            break;
        }
    }
    std::cout << "感谢使用，再见！" << std::endl;
    return 0;
}