#include "CreatePrivateRoom.h"

CreatePrivateRoom::CreatePrivateRoom(QWidget *parent,int userID)
	: QMainWindow(parent),userID(userID)
{
	ui.setupUi(this);
}

CreatePrivateRoom::~CreatePrivateRoom()
{}

std::string CreatePrivateRoom::generateRandomCode(const int& length)
{
    std::vector<std::pair<int,int>> charSets = {
        {65, 90},  // A-Z
        {97, 122}, // a-z
        {48, 57}   // 0-9
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string randomCode;
    randomCode.reserve(length);

    for (int i = 0; i < length; ++i) {
        int setIndex = std::uniform_int_distribution<int>
            (0, charSets.size() - 1)(gen);
        auto& selectedSet = charSets[setIndex];
        int charCode = std::uniform_int_distribution<int>
            (selectedSet.first, selectedSet.second)(gen);
        randomCode.push_back(static_cast<char>(charCode));
    }

    return randomCode;
}

void CreatePrivateRoom::on_pushButton_generateCode_clicked()
{
    int codeLength = 8;
    QString temp = QString::fromStdString(generateRandomCode(codeLength));
    QLineEdit* generateCodeLineEdit = findChild<QLineEdit*>("lineEdit_generateCode");
    generateCodeLineEdit->setText(temp);
}
