#include<iostream>
#include<iomanip>

using namespace std;

const static double TAX_DEDUCTION = 11; // giam tru thue
const static double DEP_FEE = 4.4; // giam tru phi phu thuoc

const float TAX_LIMIT[7] = {0, 0.25, 0.75, 1.65, 3.25, 5.85, 9.85}; // Ham muc thue.
const float TAX_RATE[7] = {0, 5, 10, 18, 32, 52, 80};   // ham muc tang % thue.

double static taxSal[12], sal[12]; // Thue thu nhap theo thang, và luong theo thang.

string name; // ten nguoi dung.
int year = 0, numDep = 0; // nam tinh thue, so nguoi phu thuoc.

double taxableIncome = 0, sumTaxableIncome = 0, taxMonth = 0; // Thu nhap tinh thue, tong thu nhap tinh thue, thue thang.

// main menu
void menu() {
    cout << "--------------------------------------" << endl;
    cout << "|           MENU CHƯƠNG TRÌNH          |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "|  1. Han muc mien tru thue            |" << endl;
    cout << "|  2. Nhap thong tin tinh thue         |" << endl;
    cout << "|  3. Tinh thue TNCN theo thang        |" << endl;
    cout << "|  4. Quyet toan thue TNCN ca nam      |" << endl;
    cout << "|  0. Thoat chuong trinh               |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Moi ban nhap: ";
}

// Hàm generics check nhap gia tri > 0
template <typename T>
T check(T x) {
    cin >> x;
    bool check = true;
    while (check) {
        if (x < 0) {
            cout << "Da nhap sai gia tri, vui long nhap lai :";
            cin >> x;
            check = true;
        } else {
            check = false;
        }
    }
    return x;
}

// 1. Han muc
void taxLimit() {
    cout << "Các trường hợp miễn thuế: \n"
            "Theo Điều 4 của Luật Thuế thu nhập cá nhân và Điều 4 Nghị định 65/2013/NĐ-CP được hướng dẫn chi tiết bởi Điều 3 Thông tư 111/2013/TT-BTC (được sửa đổi bởi khoản 2 Điều 12 và bổ sung bởi khoản 4, 5 Điều 12 Thông tư 92/2015/TT-BTC), các khoản thu nhập được miễn thuế bao gồm:\n"
            "\n"
            "1. Thu nhập từ chuyển nhượng bất động sản (bao gồm cả nhà ở hình thành trong tương lai, công trình xây dựng hình thành trong tương lai theo quy định pháp luật về kinh doanh bất động sản) giữa: vợ với chồng; cha đẻ, mẹ đẻ với con đẻ; cha nuôi, mẹ nuôi với con nuôi; cha chồng, mẹ chồng với con dâu; bố vợ, mẹ vợ với con rể; ông nội, bà nội với cháu nội; ông ngoại, bà ngoại với cháu ngoại; anh chị em ruột với nhau.\n"
            "\n"
            "2. Thu nhập từ chuyển nhượng nhà ở, quyền sử dụng đất ở và tài sản gắn liền với đất ở của cá nhân trong trường hợp người chuyển nhượng chỉ có duy nhất một nhà ở, quyền sử dụng đất ở tại Việt Nam.\n"
            "\n"
            "Xem thêm: 2 trường hợp được miễn thuế khi mua bán nhà đất\n"
            "\n"
            "3. Thu nhập từ giá trị quyền sử dụng đất của cá nhân được Nhà nước giao đất không phải trả tiền hoặc được giảm tiền sử dụng đất theo quy định của pháp luật.\n"
            "\n"
            "4. Thu nhập từ nhận thừa kế, quà tặng là bất động sản (bao gồm cả nhà ở, công trình xây dựng hình thành trong tương lai theo quy định của pháp luật về kinh doanh bất động sản) giữa: vợ với chồng; cha đẻ, mẹ đẻ với con đẻ; cha nuôi, mẹ nuôi với con nuôi; cha chồng, mẹ chồng với con dâu; cha vợ, mẹ vợ với con rể; ông nội, bà nội với cháu nội, ông ngoại, bà ngoại với cháu ngoại; anh chị em ruột với nhau.\n"
            "\n"
            "5. Thu nhập từ chuyển đổi đất nông nghiệp để hợp lý hóa sản xuất nông nghiệp nhưng không làm thay đổi mục đích sử dụng đất của hộ gia đình, cá nhân trực tiếp sản xuất nông nghiệp, được Nhà nước giao để sản xuất.\n"
            "\n"
            "6. Thu nhập của hộ gia đình, cá nhân trực tiếp tham gia vào hoạt động sản xuất nông nghiệp, lâm nghiệp, làm muối, nuôi trồng, đánh bắt thủy sản chưa qua chế biến hoặc chỉ qua sơ chế thông thường chưa chế biến thành sản phẩm khác.\n"
            "\n"
            "Hộ gia đình, cá nhân trực tiếp tham gia vào hoạt động sản xuất theo hướng dẫn tại điểm này phải thỏa mãn đồng thời các điều kiện sau:\n"
            "\n"
            "- Có quyền sử dụng đất, quyền thuê đất, quyền sử dụng mặt nước, quyền thuê mặt nước hợp pháp để sản xuất và trực tiếp tham gia lao động sản xuất nông nghiệp, lâm nghiệp, làm muối, nuôi trồng thủy sản.\n"
            "\n"
            "- Thực tế cư trú tại địa phương nơi diễn ra hoạt động sản xuất nông nghiệp, lâm nghiệp, làm muối, nuôi trồng, đánh bắt thủy sản.\n"
            "\n"
            "Địa phương nơi diễn ra hoạt động sản xuất nông nghiệp, lâm nghiệp, làm muối, nuôi trồng thủy sản theo hướng dẫn này là quận, huyện, thị xã, thành phố thuộc tỉnh (gọi chung là đơn vị hành chính cấp huyện) hoặc huyện giáp ranh với nơi diễn ra hoạt động sản xuất.\n"
            "\n"
            "Riêng đối với hoạt động đánh bắt thủy sản thì không phụ thuộc nơi cư trú.\n"
            "\n"
            "- Các sản phẩm nông nghiệp, lâm nghiệp, làm muối, nuôi trồng đánh bắt thủy sản chưa chế biến thành các sản phẩm khác hoặc mới chỉ sơ chế thông thường là sản phẩm mới được làm sạch, phơi, sấy khô, bóc vỏ, tách hạt, cắt, ướp muối, bảo quản lạnh và các hình thức bảo quản thông thường khác.\n"
            "\n"
            "Hot: Tính thuế thu nhập cá nhân chỉ trong vòng vài giây\n"
            "\n"
            "Miễn thuế thu nhập cá nhân 2020\n"
            "\n"
            "Miễn thuế thu nhập cá nhân 2021 (Ảnh minh họa)\n"
            "7. Thu nhập từ lãi tiền gửi tại tổ chức tín dụng, chi nhánh ngân hàng nước ngoài, lãi từ hợp đồng bảo hiểm nhân thọ; thu nhập từ lãi trái phiếu Chính phủ.\n"
            "\n"
            "8. Thu nhập từ kiều hối được miễn thuế là khoản tiền cá nhân nhận được từ nước ngoài do thân nhân là người Việt Nam định cư ở nước ngoài, người Việt Nam đi lao động, công tác, học tập tại nước ngoài gửi tiền về cho thân nhân ở trong nước;\n"
            "\n"
            "Trường hợp cá nhân nhận được tiền từ nước ngoài do thân nhân là người nước ngoài gửi về đáp ứng điều kiện về khuyến khích chuyển tiền về nước theo quy định của Ngân hàng nhà nước Việt nam thì cũng được miễn thuế.\n"
            "\n"
            "Căn cứ xác định thu nhập được miễn thuế tại điểm này là các giấy tờ chứng minh nguồn tiền nhận từ nước ngoài và chứng từ chi tiền của tổ chức trả hộ (nếu có).\n"
            "\n"
            "9. Thu nhập từ phần tiền lương, tiền công làm việc ban đêm, làm thêm giờ được trả cao hơn so với tiền lương, tiền công làm việc ban ngày, làm việc trong giờ theo quy định của Bộ luật Lao động, cụ thể như sau:\n"
            "\n"
            "- Phần tiền lương, tiền công trả cao hơn do phải làm việc ban đêm, làm thêm giờ được miễn thuế căn cứ vào tiền lương, tiền công thực trả do phải làm đêm, thêm giờ trừ (-) đi mức tiền lương, tiền công tính theo ngày làm việc bình thường.\n"
            "\n"
            "Ví dụ: Ông B có mức lương trả theo ngày làm việc bình thường theo quy định của Bộ luật Lao động là 40.000 đồng/giờ.\n"
            "\n"
            "+ Trường hợp cá nhân làm thêm giờ vào ngày thường, cá nhân được trả 60.000 đồng/giờ thì thu nhập được miễn thuế là:\n"
            "\n"
            "60.000 đồng/giờ - 40.000 đồng/giờ = 20.000 đồng/giờ\n"
            "\n"
            "+ Trường hợp cá nhân làm thêm giờ vào ngày nghỉ hoặc ngày lễ, cá nhân được trả 80.000 đồng/giờ thì thu nhập được miễn thuế là:\n"
            "\n"
            "80.000 đồng/giờ - 40.000 đồng/giờ = 40.000 đồng/giờ\n"
            "\n"
            "- Tổ chức, cá nhân trả thu nhập phải lập bảng kê phản ánh rõ thời gian làm đêm, làm thêm giờ, khoản tiền lương trả thêm do làm đêm, làm thêm giờ đã trả cho người lao động. Bảng kê này được lưu tại đơn vị trả thu nhập và xuất trình khi có yêu cầu của cơ quan thuế.\n"
            "\n"
            "10. Tiền lương hưu do Quỹ bảo hiểm xã hội trả theo quy định của Luật Bảo hiểm xã hội; tiền lương hưu nhận được hàng tháng từ Quỹ hưu trí tự nguyện.\n"
            "\n"
            "11. Thu nhập từ học bổng, bao gồm:\n"
            "\n"
            "- Học bổng nhận được từ ngân sách Nhà nước bao gồm: học bổng của Bộ Giáo dục và Đào tạo, Sở Giáo dục và Đào tạo, các trường công lập hoặc các loại học bổng khác có nguồn từ ngân sách Nhà nước.\n"
            "\n"
            "- Học bổng nhận được từ tổ chức trong nước và ngoài nước (bao gồm cả khoản tiền sinh hoạt phí) theo chương trình hỗ trợ khuyến học của tổ chức đó.\n"
            "\n"
            "12. Thu nhập từ bồi thường hợp đồng bảo hiểm nhân thọ, phi nhân thọ, bảo hiểm sức khỏe; tiền bồi thường tai nạn lao động; tiền bồi thường, hỗ trợ theo quy định của pháp luật về bồi thường, hỗ trợ, tái định cư; các khoản bồi thường Nhà nước và các khoản bồi thường khác theo quy định của pháp luật.\n"
            "\n"
            "13. Thu nhập nhận được từ các quỹ từ thiện được cơ quan Nhà nước có thẩm quyền cho phép thành lập hoặc công nhận, hoạt động vì mục đích từ thiện, nhân đạo, khuyến học không nhằm mục đích thu lợi nhuận.\n"
            "\n"
            "Quỹ từ thiện nêu tại điểm này là quỹ từ thiện được thành lập và hoạt động theo quy định tại Nghị định 30/2012/NĐ-CP (từ ngày 15/01/2020 được thay thế bởi Nghị định 93/2019/NĐ-CP).\n"
            "\n"
            "Căn cứ xác định thu nhập nhận được từ các quỹ từ thiện được miễn thuế tại điểm này là văn bản hoặc quyết định trao khoản thu nhập của quỹ từ thiện và chứng từ chi tiền, hiện vật từ quỹ từ thiện.\n"
            "\n"
            "14. Thu nhập nhận được từ các nguồn viện trợ của nước ngoài vì mục đích từ thiện, nhân đạo dưới hình thức Chính phủ và phi Chính phủ được cơ quan Nhà nước có thẩm quyền phê duyệt.\n"
            "\n"
            "Căn cứ xác định thu nhập được miễn thuế tại điểm này là văn bản của cơ quan Nhà nước có thẩm quyền phê duyệt việc nhận viện trợ.\n"
            "\n"
            "15. Thu nhập từ tiền lương, tiền công của thuyền viên là người Việt Nam nhận được do làm việc cho các hãng tàu nước ngoài hoặc các hãng tàu Việt Nam vận tải quốc tế.\n"
            "\n"
            "16. Thu nhập của cá nhân là chủ tàu, cá nhân có quyền sử dụng tàu và cá nhân làm việc trên tàu có được từ hoạt động cung cấp hàng hóa, dịch vụ trực tiếp phục vụ hoạt động khai thác thủy sản xa bờ. "
         << endl;
}

// 2. Hàm nhập thông tin
void displayInfo() {
    cout << "---------------------- THONG TIN -------------------" << endl;
    cout << left << setw(20) << "| Ten:               " << setw(30) << right << name << "|" << endl;
    cout << left << setw(20) << "| Nam tinh thue:     " << setw(30) << right << year << "|" << endl;
    cout << left << setw(20) << "| So nguoi phu thuoc:" << setw(30) << right << numDep << "|" << endl;
    cout << "----------------------------------------------------" << endl;
}

void enterInfo() {

    cout << "Nhap ten : ";
    cin.ignore();
    getline(cin, name);

    cout << "Nam tinh thue : ";
    year = check(year);
    cout << "So nguoi phu thuoc : ";
    numDep = check(numDep);

    displayInfo();
}

// 3. Tinh thue TNCN theo thang.
// Ham cong thuc tinh thue theo thang
void recipe(int i) {
    taxableIncome = sal[i] - (numDep * DEP_FEE) - TAX_DEDUCTION;

    if (taxableIncome <= 0) {
        taxMonth = 0;
    } else {
        for (int j = 0; j < sizeof(TAX_RATE) / sizeof(TAX_RATE[0]); ++j) {
            if (taxableIncome < TAX_RATE[j + 1]) {
                // rate tinh thue   // muc tru thue
                taxMonth = taxableIncome * (0.05 + 0.05 * j) - TAX_LIMIT[j];
                break;
            }
        }
    }
    sumTaxableIncome += taxableIncome;
    taxSal[i] = taxMonth;
}

// Ham tinh thue TNCN theo cac thang.
double * calIncomeTaxForMonths() {
    if(name.empty()) {
        cout << "Vui long thuc hien nhap thong tin o muc 2 truoc khi tinh thue!" << endl;
        return nullptr;
    }

    int a = 0;
    do {
        cout << "1. Tinh thue voi mot thang trong nam." << endl;
        cout << "2. Tinh thue voi ca 12 thang trong nam." << endl;
        cout << "3. Hien thi cac thang da nop thue. " << endl;
        cout << "0. Quay lai menu." << endl;

        int cnt = 0;
        cin >> a;
        while(a > 4 || a < 0) {
            cout << "Sai gia tri, nhap lai :"; cin >> a;
        }


        switch (a) {
            case 1:{
                int month = 1;
                cout << "Nhap thang : ";
                cin >> month;

                while (month <=0 || month > 12) {
                    cout << "Sai gia tri, vui long nhap lai : ";
                    cin >> month;
                }

                cout << "Nhap luong thang " << month << " la : ";
                double salaryMonth = 0;
                sal[month-1] = check(salaryMonth);

                recipe(month-1);
                // Output ra thuế 12 tháng
                for(int index = 0; index < 12; index++) {
                    if(taxSal[index] != 0) {
                        cout << fixed << setprecision(3);
                        cout << "Thue thang " << index + 1 << " la : " << taxSal[index] << endl;
                    }
                }
                break;
            }

            case 2:{

                for(int i = 0; i < 12; i++) {
                    cout << "Luong thang " << i + 1 << " la : ";
                    sal[i] = check(sal[i]);
                } cout << endl;

                for(int i = 0; i < 12; i++) {
                    recipe(i);
                }
                break;
            }

            case 3: {
                // Output ra thuế 12 tháng
                for(int i = 0; i < 12; i++) {

                    if(taxSal[i] != 0) {
                        cout << fixed << setprecision(3);
                        cout << "Thue thang " << i + 1 << " la: " << taxSal[i] << endl;
                        cnt++;
                    }
                } cout << endl;
                if(cnt == 0) {
                    cout << "Khong co du lieu thue, do chua nhap thu nhap ca nhan." << endl;
                }
                break;
            }
        }
    } while (a!=0);

    return taxSal;
}

// 4. Quyet toan ca nam
// Ham tinh tong thue TNCN da dong trong nam.
double sumTaxIncome() {
    double sum = 0;
    for (double salary : taxSal) {
        sum += salary;
    }
    return sum;
}

// Ham tinh tong TNCN trong ca nam
double sumIncome() {
    double sum = 0;
    for (double i : sal) {
        sum += i;
    }
    return sum;
}

// Ham quyet toan thue TNCN ca nam.
double calculateTax(double income, double rate) {
    return income * rate;
}

void taxForYear() {
    double taxThresholds[] = {60, 120, 216, 384, 624, 960}; // Nguong muc chiu thue
    double rates[] = {0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35}; // ti le theo nguong

    double temp = 0; // thue phai dong

    for (int i = 0; i < sizeof(taxThresholds) / sizeof(taxThresholds[0]); ++i) {
        if (sumTaxableIncome <= taxThresholds[i]) {
            temp += calculateTax(sumTaxableIncome - (i > 0 ? taxThresholds[i - 1] : 0), rates[i]);
            break;
        } else {
            temp += calculateTax(taxThresholds[i] - (i > 0 ? taxThresholds[i - 1] : 0), rates[i]);
        }
    }

    displayInfo(); // hien thi thong tin
    cout << "Tong thu nhap ca nam : " << sumIncome() << endl;
    cout << "Tong thue TNCN da dong : " << sumTaxIncome() << endl;
    cout << "Tong thue phai dong : " << temp << endl;

    if (temp < sumTaxIncome()) {
        cout << "Truy linh: " << sumTaxIncome() - temp << endl;
    } else if (temp == sumTaxIncome()) {
        cout << "Khong phai truy thu, truy linh." << endl;
    } else {
        cout << "Truy thu: " << temp - sumTaxIncome() << endl;
    }
}


int main() {
    int feature = 0;
    do {
        menu();
        feature = check(feature);
        if(feature > 4 ) {
            cout << "Khong co tinh nang nay, vui long xem va nhap lai!!!" << endl;
            continue;
        }
        switch (feature) {
            case 1: {
                // Thông tin về mức thuế
                taxLimit();
                break;
            }
            case 2: {
                // Nhập thông tin
                enterInfo();
                break;
            }
            case 3: {
                // Mảng chứa thuế của 12 tháng
                calIncomeTaxForMonths();

                break;
            }
            case  4: {
                // Thuế cả năm
                taxForYear();
            }
            default: {
                cout << "\nThuc hien xong " << endl;
            }
        }

    } while (feature!=0);
    return 0;
}
// end