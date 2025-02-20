#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;
string passworkSystem = "vanha2301";
// ngày giờ thời gian hiện tại.
string currentTime;
// file data lưu kế hoạch.
vector <string> fileDataPlan;
// Thông báo hệ thống, thông báo chương trình NOTE.
string thongBaoChuongTrinhNote = "%F0%9F%93%A2%3A%20%C4%90%C3%A2y%20l%C3%A0%20th%C3%B4ng%20b%C3%A1o%20t%E1%BB%AB%20h%E1%BB%87%20th%E1%BB%91ng%20th%C3%B4ng%20b%C3%A1o%20%C4%91%E1%BA%BFn%20t%E1%BB%AB%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20GHI%20CH%C3%9A%0A";
// time Now
int dayNow, monthNow, yearNow, hourNow, minNow, secNow;

string DocTinNhan() {
    std::string token = "7713713238:AAFrtM47YMZNQDmZk-xOvERLhmVCrftRmm4";  // Thay bằng token của bạn
    std::string command = "curl -s \"https://api.telegram.org/bot" + token + "/getUpdates\"";

    FILE* pipe = _popen(command.c_str(), "r");  // Dùng _popen trên Windows
    if (!pipe) return "Lỗi khi gọi API!";

    char buffer[1024];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;  // Đọc dữ liệu vào biến result
    }

    _pclose(pipe);  // Đóng pipe

    // Tìm tin nhắn cuối cùng (bằng cách tìm phần tử "text" cuối cùng)
    size_t lastTextPos = result.rfind("\"text\":\"");
    if (lastTextPos == std::string::npos) return "Không có tin nhắn nào!";

    lastTextPos += 8; // Nhảy qua `"text":"`
    size_t end = result.find("\"", lastTextPos); // Tìm dấu `"` đóng
    if (end == std::string::npos) return "Lỗi khi đọc tin nhắn!";

    return result.substr(lastTextPos, end - lastTextPos);
}

void ThongBao(std::string data) {
    std::string token = "7713713238:AAFrtM47YMZNQDmZk-xOvERLhmVCrftRmm4";  // Thay bằng token của bạn
    std::string chat_id = "7352518467";  // Thay bằng Chat ID của bạn
    std::string message = data;

    std::string command = "curl -s -X POST \"https://api.telegram.org/bot" + token +
        "/sendMessage\" -d \"chat_id=" + chat_id +
        "&text=" + message + "\" > nul 2>&1";

    system(command.c_str());  // Gửi thông báo
}
void setupTimeNow() {
    std::time_t now = std::time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << localTime.tm_mday << "/"
        << std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1) << "/"
        << (localTime.tm_year + 1900) << " "
        << std::setw(2) << std::setfill('0') << localTime.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << localTime.tm_min << ":"
        << std::setw(2) << std::setfill('0') << localTime.tm_sec;
    currentTime = timeStream.str();
    dayNow = std::stoi(currentTime.substr(0, 2));
    monthNow = std::stoi(currentTime.substr(3, 2));
    yearNow = std::stoi(currentTime.substr(6, 4));
    hourNow = std::stoi(currentTime.substr(11, 2));
    minNow = std::stoi(currentTime.substr(14, 2));
    secNow = std::stoi(currentTime.substr(17, 2));
}
void CinFileData() {
    //cin file data 
    ifstream cinFile("fileData.txt");
    string subject;
    while (getline(cinFile, subject)) {
        fileDataPlan.push_back(subject);
    }
    cinFile.close();
}
void OutFileData() {
    string time, title, text;
    ofstream outFile("fileData.txt", ios::app);

    cout << "Nhap Thoi Gian: ";
    getline(cin, time);
    outFile << time << endl;

    cout << "Nhap chu de: ";
    getline(cin, title);
    outFile << title << endl;

    cout << "Nhap noi dung: ";
    getline(cin, text);
    outFile << text << endl;
    outFile.close();

    ThongBao("#############################################");
    ThongBao(thongBaoChuongTrinhNote);
    ThongBao("Ban vua cap nhat danh sach va them du lieu.");
    string tmp;
    setupTimeNow();
    tmp = "Thoi gian cap nhat la: " + currentTime;
    ThongBao(tmp);

    tmp = "Time: " + time;
    ThongBao(tmp);

    tmp = "Chu de: " + title;
    ThongBao(tmp);

    tmp = "Noi dung: " + text;
    ThongBao(tmp);

}
void updateFileData() {
    CinFileData();
    setupTimeNow();
    if (hourNow == 0 && minNow == 0 && secNow == 0) {
        ThongBao("Da cap nhat fileDataPlan");
    }
    ofstream data("fileData.txt");
    string dataNow;
    for (int i = 0; i < fileDataPlan.size(); i += 3) {
        dataNow = fileDataPlan[i];
        if (dayNow <= stoi(dataNow.substr(0, 2)) && monthNow <= stoi(dataNow.substr(3, 2)) && yearNow <= stoi(dataNow.substr(6, 4))) {
            data << fileDataPlan[i] << endl;
            data << fileDataPlan[i + 1] << endl;
            data << fileDataPlan[i + 2] << endl;
        }
    }
    data.close();
    CinFileData();

}
void TBFileDataPlan() {
    cout << " Dang chay ham  TBFileDataPlan" << endl;
    //CinFileData();
    setupTimeNow();
    string dataNow;
    for (int i = 0; i < fileDataPlan.size(); i += 3) {
        dataNow = fileDataPlan[i];
        int timeHour_Min_SecNow, timeHour_Min_SecPlan;
        timeHour_Min_SecNow = hourNow * 3600 + minNow * 60 + secNow;
        timeHour_Min_SecPlan = stoi(dataNow.substr(11, 2)) * 3600 + stoi(dataNow.substr(14, 2)) * 60 + stoi(dataNow.substr(17, 2));
        //cout << "loi o day";
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == timeHour_Min_SecPlan) {
            cout << "loi o day";
            string tmp;
            ThongBao("####################################");
            ThongBao(thongBaoChuongTrinhNote);
            tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
            ThongBao(tmp);

            tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
            ThongBao(tmp);

            tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
            ThongBao(tmp);

        }
        // Thong bao truoc 15 phut.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == (timeHour_Min_SecPlan - 900)) {
           string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 15 phút với nội dung.
           ThongBao("%F0%9F%94%90%3AB%E1%BA%A1n%20%C4%91%C3%A3%20nh%E1%BA%ADp%20sai%20m%E1%BA%ADt%20kh%E1%BA%A9u%2C%20xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20l%E1%BA%A1i.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 30 phút.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == (timeHour_Min_SecPlan - 1800)) {
           string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 30 phút với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%2030%20ph%C3%BAt%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 1 tiếng.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == (timeHour_Min_SecPlan - 3600)) {
           string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 1 tiếng với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%201%20ti%E1%BA%BFng%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 3 tiếng.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == (timeHour_Min_SecPlan - 3600 * 3)) {
           string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 3 tiếng với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%203%20ti%E1%BA%BFng%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);

        }
        // Thông báo trước 1 ngày.
        if (dayNow == (stoi(dataNow.substr(0, 2)) - 1) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow == (timeHour_Min_SecPlan)) {
           string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 1day với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%201%20ng%C3%A0y%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);

        }

    }
}
void TongBaoNote(){
    string tinNhanNew;
    tinNhanNew = DocTinNhan();
    TBFileDataPlan();
    //tính năng truy cập vào ghi chú note.
    if (tinNhanNew == "&note") {
        cout << "send message";
        ThongBao("#############################");
        // thông báo hệ thống. chương trình note.
        ThongBao(thongBaoChuongTrinhNote);
        ThongBao("%F0%9F%94%90%3A%20Vui%20l%C3%B2ng%20nh%E1%BA%ADp%20m%E1%BA%ADt%20kh%E1%BA%A9u%20%C4%91%E1%BB%83%20ti%E1%BA%BFn%20h%C3%A0nh%20%C4%91%C4%83ng%20nh%E1%BA%ADp%20v%C3%A0o%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20GHI%20CH%C3%9A");
        Sleep(7000);
        tinNhanNew = DocTinNhan();
        if (tinNhanNew == passworkSystem) {
            ThongBao("%C4%90ang%20ti%E1%BA%BFn%20h%C3%A0nh%20%C4%91%C4%83ng%20nh%E1%BA%ADp...");
            ThongBao("----25%");
            ThongBao("--------50%");
            ThongBao("------------75%");
            ThongBao("----------------100%");
            ThongBao("Xin%20ch%C3%A0o%20admin.%20Ch%C3%A0o%20m%E1%BB%ABng%20b%E1%BA%A1n%20%C4%91%C3%A3%20quay%20tr%E1%BB%9F%20l%E1%BA%A1i.");
            ThongBao("returnmain: thoat ra khoi MUC GHI CHU");
            ThongBao("show: in ra ghi chu hien tai con");
            bool flagShowNoteNow = true;
            while (true) {
                //system("cls");
                TBFileDataPlan();
                setupTimeNow();
                tinNhanNew = DocTinNhan();
                cout << "Dang chay While Note" << endl;

                // trở về thời điểm ban đầu.
                if (tinNhanNew == "&returnmain") {
                    ThongBao("Ban da thoat khoi MUC GHI CHU");
                    return;
                }
                if (tinNhanNew == "&show" && flagShowNoteNow == true) {
                    flagShowNoteNow = false;
                    setupTimeNow();
                    string dataNow;
                    bool flag = false;
                    for (int i = 0; i < fileDataPlan.size(); i += 3) {
                        dataNow = fileDataPlan[i];
                        
                        if (dayNow <= stoi(dataNow.substr(0, 2)) && monthNow <= stoi(dataNow.substr(3, 2)) && yearNow <= stoi(dataNow.substr(6, 4)) && flagShowNoteNow == false) {
                            flag = true;
                            string tmp;

                            tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
                            ThongBao(tmp);

                            tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
                            ThongBao(tmp);

                            tmp = "%F0%9F%97%9FTitle%3A%20" + fileDataPlan[i + 2];
                            ThongBao(tmp);
                        }
                    }
                    if (flag == false) {
                        ThongBao("Khong co thong tin nao.");
                    }

                }
            }
        }
        else {
            //🔐:Bạn đã nhập sai mật khẩu, xin vui lòng nhập lại.
            ThongBao("%F0%9F%94%90%3AB%E1%BA%A1n%20%C4%91%C3%A3%20nh%E1%BA%ADp%20sai%20m%E1%BA%ADt%20kh%E1%BA%A9u%2C%20xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20l%E1%BA%A1i.");
        }
    }
}
int main() {


    // lưu fileData.
    CinFileData();
    //updateFileData();
    while (true) {
        TBFileDataPlan();
        TongBaoNote();

        // gọi hàm thời gian thực.
        //setupTimeNow();
        //system("cls");

        // ghi đè lên fileData để cập nhật dữ liệu.
        //OutFileData();
        //CinFileData();


    }

    return 0;
}
